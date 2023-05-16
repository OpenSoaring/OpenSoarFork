// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright The XCSoar Project

#include "StringConverter.hpp"
#include "util/Compiler.h"
#include "util/UTF8.hpp"

#include <cassert>
#include <cstring>
#include <stdexcept>

#ifdef _UNICODE
#include "system/Error.hxx"
#include <stringapiset.h>
#endif

#ifdef _UNICODE

static constexpr void
iso_latin_1_to_tchar(TCHAR *dest, const char *src) noexcept
{
    do {
      *dest++ = (unsigned char)*src;
    } while (*src++ != '\0');
}

#endif

/**
 * Does the given string start with the UTF-8 byte order mark?  This
 * is often a prefix which marks a file/string as UTF-8.
 */
[[gnu::pure]]
static bool
IsByteOrderMark(const char *s) noexcept
{
  return s[0] == (char)0xef && s[1] == (char)0xbb && s[2] == (char)0xbf;
}

[[gnu::pure]]
static char *
SkipByteOrderMark(char *s) noexcept
{
  return IsByteOrderMark(s) ? s + 3 : nullptr;
}

char *
StringConverter::DetectStrip(char *src) noexcept
{
  assert(src != nullptr);

  // Check if there is byte order mark in front
  if (charset == Charset::AUTO || charset == Charset::UTF8) {
    if (char *p = SkipByteOrderMark(src); p != nullptr) {
      src = p;

      /* switch to UTF-8 now */
      charset = Charset::UTF8;
    }
  }

  if (charset == Charset::AUTO && !ValidateUTF8(src))
    /* invalid UTF-8 sequence detected: switch to ISO-Latin-1 */
    charset = Charset::ISO_LATIN_1;

  return src;
}

TCHAR *
StringConverter::Convert(char *narrow)
{
  narrow = DetectStrip(narrow);

#ifdef _UNICODE
  size_t narrow_length = strlen(narrow);

  TCHAR *t = tbuffer.get(narrow_length + 1);
  assert(t != nullptr);

  if (narrow_length == 0) {
    t[0] = _T('\0');
    return t;
  }

  switch (charset) {
  case Charset::ISO_LATIN_1:
    iso_latin_1_to_tchar(t, narrow);
    break;

  default:
    int length = MultiByteToWideChar(CP_UTF8, 0, narrow, narrow_length,
                                     t, narrow_length);
    if (length == 0)
      throw MakeLastError("Failed to convert string");

    t[length] = _T('\0');

    break;
  }

  return t;
#else
  switch (charset) {
    size_t buffer_size;
    const char *utf8;

  case Charset::ISO_LATIN_1:
    buffer_size = strlen(narrow) * 2 + 1;
    utf8 = Latin1ToUTF8(narrow, tbuffer.get(buffer_size), buffer_size);
    if (utf8 == nullptr)
      throw std::runtime_error("Latin-1 to UTF-8 conversion failed");

    return const_cast<char *>(utf8);

  case Charset::UTF8:
    if (!ValidateUTF8(narrow))
      /* abort on invalid UTF-8 sequence */
      throw std::runtime_error("Invalid UTF-8");

    /* fall through ... */
    gcc_fallthrough;

  case Charset::AUTO:
    return narrow;
  }

  /* unreachable */
  gcc_unreachable();
#endif
}
