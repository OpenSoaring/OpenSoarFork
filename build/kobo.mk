$(eval $(call pkg-config-library,LIBCRYPTO,libcrypto))

KOBO_MENU_SOURCES = \
	$(SRC)/Version.cpp \
	$(SRC)/Asset.cpp \
	$(SRC)/Formatter/HexColor.cpp \
	$(SRC)/Hardware/CPU.cpp \
	$(SRC)/Hardware/DisplayDPI.cpp \
	$(SRC)/Hardware/RotateDisplay.cpp \
	$(SRC)/Screen/Layout.cpp \
	$(SRC)/ui/control/TerminalWindow.cpp \
	$(SRC)/Look/TerminalLook.cpp \
	$(SRC)/Look/DialogLook.cpp \
	$(SRC)/Look/ButtonLook.cpp \
	$(SRC)/Look/CheckBoxLook.cpp \
	$(SRC)/Renderer/TwoTextRowsRenderer.cpp \
	$(SRC)/Gauge/LogoView.cpp \
	$(SRC)/Dialogs/DialogSettings.cpp \
	$(SRC)/Dialogs/WidgetDialog.cpp \
	$(SRC)/Dialogs/HelpDialog.cpp \
	$(SRC)/Dialogs/Message.cpp \
	$(SRC)/Dialogs/Error.cpp \
	$(SRC)/Dialogs/LockScreen.cpp \
	$(SRC)/Dialogs/TextEntry.cpp \
	$(SRC)/Dialogs/KnobTextEntry.cpp \
	$(SRC)/Dialogs/TouchTextEntry.cpp \
	$(SRC)/Dialogs/SimulatorPromptWindow.cpp \
	$(TEST_SRC_DIR)/Fonts.cpp \
	$(TEST_SRC_DIR)/FakeLanguage.cpp \
	$(TEST_SRC_DIR)/FakeLogFile.cpp \
	$(SRC)/Kobo/WPASupplicant.cpp \
	$(SRC)/Kobo/Model.cpp \
	$(SRC)/Kobo/System.cpp \
	$(SRC)/Kobo/Kernel.cpp \
	$(SRC)/Kobo/NetworkDialog.cpp \
	$(SRC)/Kobo/SystemDialog.cpp \
	$(SRC)/Kobo/ToolsDialog.cpp \
	$(SRC)/Kobo/WPASupplicant.cpp \
	$(SRC)/Kobo/WifiDialog.cpp \
	$(SRC)/Kobo/FakeSymbols.cpp \
	$(SRC)/Kobo/KoboMenu.cpp
KOBO_MENU_DEPENDS = WIDGET FORM SCREEN EVENT RESOURCE ASYNC LIBNET OS IO THREAD MATH UTIL LIBCRYPTO
KOBO_MENU_STRIP = y

$(eval $(call link-program,KoboMenu,KOBO_MENU))

ifeq ($(TARGET),UNIX)
OPTIONAL_OUTPUTS += $(KOBO_MENU_BIN)
endif

ifeq ($(TARGET_IS_KOBO),y)

KOBO_POWER_OFF_SOURCES = \
	$(TEST_SRC_DIR)/Fonts.cpp \
	$(TEST_SRC_DIR)/FakeLogFile.cpp \
	$(SRC)/Hardware/RotateDisplay.cpp \
	$(SRC)/Hardware/DisplayDPI.cpp \
	$(SRC)/Hardware/Battery.cpp \
	$(SRC)/Screen/Layout.cpp \
	$(SRC)/Logger/FlightParser.cpp \
	$(SRC)/Renderer/FlightListRenderer.cpp \
	$(SRC)/FlightInfo.cpp \
	$(SRC)/Kobo/Model.cpp \
	$(SRC)/Kobo/PowerOff.cpp
KOBO_POWER_OFF_LDADD = $(FAKE_LIBS)
KOBO_POWER_OFF_DEPENDS = SCREEN EVENT RESOURCE IO ASYNC OS MATH UTIL TIME
KOBO_POWER_OFF_STRIP = y
$(eval $(call link-program,PowerOff,KOBO_POWER_OFF))
OPTIONAL_OUTPUTS += $(KOBO_POWER_OFF_BIN)

BITSTREAM_VERA_DIR ?= $(shell \
if [ -d /usr/share/fonts/truetype/ttf-bitstream-vera ]; then \
	echo /usr/share/fonts/truetype/ttf-bitstream-vera; \
elif [ -d /usr/share/fonts/bitstream-vera ]; then \
	echo /usr/share/fonts/bitstream-vera; \
fi)
BITSTREAM_VERA_NAMES = Vera VeraBd VeraIt VeraBI VeraMono
BITSTREAM_VERA_FILES = $(patsubst %,$(BITSTREAM_VERA_DIR)/%.ttf,$(BITSTREAM_VERA_NAMES))

THIRDPARTY_TOOL_NAMES = simple_usbmodeswitch
THIRDPARTY_TOOL_FILES = $(addprefix $(THIRDPARTY_LIBS_ROOT)/bin/,$(THIRDPARTY_TOOL_NAMES))

KOBO_KERNEL_DIR = /opt/kobo/kernel

CA_URL = https://curl.se/ca/cacert-2022-04-26.pem
CA_ALTERNATIVE_URL = $(CA_URL)
CA_MD5 = aa5ac583708ca35225ac2d230f4acb62

CA_DOWNLOAD = $(DOWNLOAD_DIR)/$(notdir $(CA_URL))

$(CA_DOWNLOAD): | $(DOWNLOAD_DIR)/dirstamp
	@$(NQ)echo "  GET     $@"
	$(Q)./build/download.py $(CA_URL) $(CA_ALTERNATIVE_URL) $(CA_MD5) $(DOWNLOAD_DIR)

# /mnt/onboard/.kobo/KoboRoot.tgz is a file that is picked up by
# /etc/init.d/rcS, extracted to / on each boot; we can use it to
# install XCSoar
$(TARGET_OUTPUT_DIR)/KoboRoot.tgz: $(XCSOAR_BIN) \
	$(KOBO_MENU_BIN) $(KOBO_POWER_OFF_BIN) \
	$(BITSTREAM_VERA_FILES) \
	$(topdir)/kobo/inittab $(topdir)/kobo/rcS $(topdir)/kobo/udev.rules \
	$(CA_DOWNLOAD)
	@$(NQ)echo "  TAR     $@"
	$(Q)rm -rf $(@D)/KoboRoot
	$(Q)install -m 0755 -d $(@D)/KoboRoot/etc/udev/rules.d $(@D)/KoboRoot/opt/xcsoar/bin $(@D)/KoboRoot/opt/xcsoar/lib/kernel $(@D)/KoboRoot/opt/xcsoar/share/fonts $(@D)/KoboRoot/etc/ssl/certs
	$(Q)install -m 0755 $(XCSOAR_BIN) $(KOBO_MENU_BIN) $(KOBO_POWER_OFF_BIN) $(topdir)/kobo/rcS $(@D)/KoboRoot/opt/xcsoar/bin
	$(Q)install -m 0755 --strip --strip-program=$(STRIP) $(THIRDPARTY_TOOL_FILES) $(@D)/KoboRoot/opt/xcsoar/bin
	$(Q)if test -f $(KOBO_KERNEL_DIR)/uImage.kobo; then install -m 0644 $(KOBO_KERNEL_DIR)/uImage.kobo $(@D)/KoboRoot/opt/xcsoar/lib/kernel; fi
	$(Q)if test -f $(KOBO_KERNEL_DIR)/uImage.otg; then install -m 0644 $(KOBO_KERNEL_DIR)/uImage.otg $(@D)/KoboRoot/opt/xcsoar/lib/kernel; fi
	$(Q)if test -f $(KOBO_KERNEL_DIR)/uImage.glohd; then install -m 0644 $(KOBO_KERNEL_DIR)/uImage.glohd $(@D)/KoboRoot/opt/xcsoar/lib/kernel; fi
	$(Q)if test -f $(KOBO_KERNEL_DIR)/uImage.glohd.otg; then install -m 0644 $(KOBO_KERNEL_DIR)/uImage.glohd.otg $(@D)/KoboRoot/opt/xcsoar/lib/kernel; fi
	$(Q)if test -f $(KOBO_KERNEL_DIR)/uImage.aura2; then install -m 0644 $(KOBO_KERNEL_DIR)/uImage.aura2 $(@D)/KoboRoot/opt/xcsoar/lib/kernel; fi
	$(Q)if test -f $(KOBO_KERNEL_DIR)/uImage.aura2.otg; then install -m 0644 $(KOBO_KERNEL_DIR)/uImage.aura2.otg $(@D)/KoboRoot/opt/xcsoar/lib/kernel; fi
	$(Q)if test -f $(KOBO_KERNEL_DIR)/ClaraHD_OTG_Drivers.tgz; then tar -xzf $(KOBO_KERNEL_DIR)/ClaraHD_OTG_Drivers.tgz -C $(@D)/KoboRoot/opt/xcsoar/lib; fi
	$(Q)install -m 0644 $(topdir)/kobo/inittab $(@D)/KoboRoot/etc
	$(Q)install -m 0644 $(topdir)/kobo/udev.rules $(@D)/KoboRoot/etc/udev/rules.d/99-xcsoar.rules
	$(Q)install -m 0644 $(BITSTREAM_VERA_FILES) $(@D)/KoboRoot/opt/xcsoar/share/fonts
	$(Q)install -T -m 0644 $(CA_DOWNLOAD) $(@D)/KoboRoot/etc/ssl/certs/ca-certificates.crt
	$(Q)fakeroot tar czfC $@ $(@D)/KoboRoot .

endif
