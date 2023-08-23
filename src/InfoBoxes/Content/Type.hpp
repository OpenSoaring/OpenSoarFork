// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright The XCSoar Project

#pragma once

namespace InfoBoxFactory
{
  enum Type {
    // 0..9 
    e_HeightGPS, // This is the height above mean sea level reported by...
    e_HeightAGL, // This is the navigation altitude minus the terrain ...
    e_Thermal_30s, // A 30 second rolling average climb rate based of the ...
    e_Bearing, // True bearing of the next waypoint.  For AAT tasks, this ...
    e_GR_Instantaneous, // Instantaneous glide ratio over ground, given by ...
    e_GR_Cruise, // The distance from the top of the last thermal, divided ...
    e_Speed_GPS, // Ground speed measured by the GPS. If this infobox is ...
    e_TL_Avg, // Total altitude gain/loss in the last thermal divided by ...
    e_TL_Gain, // Total altitude gain/loss in the last thermal 
    e_TL_Time, // Time spent circling in the last thermal 
    // 10..19 
    e_MacCready, // The current MacCready setting. This infobox also shows ...
    e_WP_Distance, // The distance to the currently selected waypoint. For ...
    e_WP_AltDiff, // Next Altitude Difference - Arrival altitude at the ...
    e_WP_AltReq, // Additional altitude required to reach the next turn ...
    e_WP_Name, // The name of the currently selected turn point. When this ...
    e_Fin_AltDiff, // Arrival altitude at the final task turn point relative...
    e_Fin_AltReq, // Additional altitude required to finish the task 
    e_SpeedTaskAvg, // Average cross country speed while on current task, ...
    e_Fin_Distance, // Distance to finish around remaining turn points 
    e_Fin_GR_TE, // Deprecated 
    // 20..29 
    e_H_Terrain, // This is the elevation of the terrain above mean sea ...
    e_Thermal_Avg, // Altitude gained/lost in the current thermal, divided ...
    e_Thermal_Gain, // The altitude gained/lost in the current thermal 
    e_Track_GPS, // Magnetic track reported by the GPS. (Touchscreen/PC ...
    e_VerticalSpeed_GPS, // Instantaneous vertical speed, as reported by ...
    e_WindSpeed_Est, // Wind speed estimated by XCSoar. (Touchscreen/PC ...
    e_WindBearing_Est, // Wind bearing estimated by XCSoar. (Touchscreen/PC ...
    e_AA_Time, // Assigned Area Task time remaining. Goes red when time ...
    e_AA_DistanceMax, // Assigned Area Task maximum distance possible ...
    e_AA_DistanceMin, // Assigned Area Task minimum distance possible ...
    // 30..39 
    e_AA_SpeedMax, // Assigned Area Task average speed achievable if flying ...
    e_AA_SpeedMin, // Assigned Area Task average speed achievable if flying ...
    e_AirSpeed_Ext, // Indicated Airspeed reported by a supported external ...
    e_H_Baro, // This is the barometric altitude obtained from a GPS ...
    e_WP_Speed_MC, // The MacCready speed-to-fly for optimal flight to the ...
    e_Climb_Perc, // Percentage of time spent in climb mode. These statist. ...
    e_TimeSinceTakeoff, // Time elapsed since takeoff was detected 
    e_Load_G, // Magnitude of G loading reported by a supported external ...
    e_WP_GR, // The required glide ratio over ground to reach the next ...
    e_TimeLocal, // GPS time expressed in local time zone 
    // 40..49 
    e_TimeUTC, // GPS time expressed in UTC 
    e_Fin_Time, // Estimated time required to complete task, assuming ...
    e_WP_Time, // Estimated time required to reach next waypoint, assuming ...
    e_Act_Speed, // The instantaneous MacCready speed-to-fly, making use of ...
    e_VerticalSpeed_Netto, // Instantaneous vertical speed of air-mass ...
    e_Fin_TimeLocal, // Estimated arrival local time at task completion, ...
    e_WP_TimeLocal, // Estimated arrival local time at next waypoint, ...
    e_WP_BearingDiff, // The difference between the glider's track bearing, ...
    e_Temperature, // Outside air temperature measured by a probe if ...
    e_HumidityRel, // Relative humidity of the air in percent as measured ...
    // 50..59 
    e_Home_Temperature, // Forecast temperature of the ground at the home ...
    e_Fin_AA_Distance, // Assigned Area Task distance around target points ...
    e_AA_SpeedAvg, // Assigned Area Task average speed achievable around ...
    e_LD, // Instantaneous lift/drag ratio, given by the indicated airspeed ...
    e_Speed, // True Airspeed reported by a supported external intelligent ...
    e_Team_Code, // The current Team code for this aircraft. Use this to ...
    e_Team_Bearing, // The bearing to the team aircraft location at the ...
    e_Team_BearingDiff, // The relative bearing to the team aircraft loc ...
    e_Team_Range, // The range to the team aircraft location at the last ...
    e_CC_SpeedInst, // Instantaneous cross country speed while on current ...
    // 60..69 
    e_Home_Distance, // Distance to home waypoint (if defined) 
    e_CC_Speed, // Achieved cross country speed while on current task, ...
    e_AA_TimeDiff, // Difference between estimated task time and AAT ...
    e_Climb_Avg, // Time-average climb rate in all thermals 
    e_RH_Trend, // Task Req. Total Height Trend 
    e_Battery, // Displays percentage of device battery remaining (where ...
    e_Fin_GR, // Geometric gradient to the arrival height above the final ...
    e_Alternate_1_Name, // Displays name and bearing to the best alternate ...
    e_Alternate_2_Name, // Displays name and bearing to the second ...
    e_Alternate_1_GR, // Geometric gradient to the arrival height above ...
    // 70..79 
    e_H_QFE, // Height on automatic QFE. This altitude value is constantly ...
    e_GR_Avg, // The distance made in the configured period of time divided ...
    e_Experimental1, // Experimental1 
    e_OC_Distance, // Online Contest Distance 
    e_Experimental2, // Experimental2 
    e_CPU_Load, // CPU load consumed by XCSoar averaged over 5 seconds 
    e_WP_H, // Absolute arrival altitude at the next waypoint in final glide 
    e_Free_RAM, // Free RAM as reported by OS 
    e_FlightLevel, // Flight Level, also known as pressure altitude 
    e_Barogram, // Trace of altitude during flight
    // 80..89 
    e_Vario_spark, // Trace of vertical speed, as reported by the GPS, or ...
    e_NettoVario_spark, // Trace of vertical speed of air-mass, equal to ...
    e_CirclingAverage_spark, // Trace of average climb rate each turn in ...
    e_ThermalBand, // Graph of average circling climb rate (horizontal axis)...
    e_TaskProgress, // Clock-like display of distance remaining along task, ...
    e_TaskMaxHeightTime, // The contiguous period the ship has been below ...
    e_Fin_ETE_VMG, // Estimated time required to complete task, assuming ...
    e_WP_ETE_VMG, // Estimated time required to reach next waypoint, assum...
    e_Horizon, // Attitude indicator (artificial horizon) display calculated...
    e_NearestAirspaceHorizontal, // The horizontal distance to the nearest ...
    // 90..99 
    e_NearestAirspaceVertical, // The vertical distance to the nearest ...
    e_WP_MC0AltDiff, // Arrival altitude at the next waypoint with MC 0 set...
    e_HeadWind, // The current head wind component. Head wind is calculated ...
    e_TerrainCollision, // The distance to the next terrain collision along ...
    e_NavAltitude, // This is the barometric altitude obtained from a device...
    e_NextLegEqThermal, // The thermal rate of climb on next leg which is ...
    e_HeadWindSimplified, // The current head wind component. The simplified...
    e_CruiseEfficiency, // Efficiency of cruise.  100 indicates perfect MacC...
    e_WindArrow, // Wind speed estimated by XCSoar. Manual adjustment is ...
    e_ThermalAssistant, // A circular thermal assistant that shows the lift ...
    // 100..109
    e_StartOpenLine, // Shows the time left until the start point opens or ...
    e_StartOpenArrivalLine, // Shows the time left until the start point ...
    e_NextRadial, // True bearing from the next waypoint to your position.
    e_ATC_Radial, // Bearing from the selected reference location to your ...
    e_TaskSpeedHour, // The distance to the currently selected waypoint. ...
    e_WP_NominalDistance,  // The nominal distance to the currently select ...
    e_CircleDiameter, // Circle diameter. Displays estimated circle diameter...
    e_TakeOffDistance, // Distance to where take-off was detected.
    e_ContestSpeed, // Instantaneous evaluation of the flown speed accord. ...
    e_Final_MC0_Altitude, // Arrival altitude at the final waypoint with MC0...
    // 110..119 
    e_NextWPArrow, // Arrow pointing to the currently selected waypoint...
    e_WP_Estimation, // Estimated arrival time at next waypoint assuming ...
    e_NonCircling_Climb_Perc, // Percentage of time spent climbing without ...
    e_Climb_Perc_Chart, // Pie chart of time circling and climbing, circling...
    e_NbrSat, // Number of used Sat by GPS module 
    e_ActiveRadio, // Active Radio Frequency 
    e_StandbyRadio, // Standby Radio Frequency 
    e_Thermal_Time, // Time in Thermal
    e_Alternate_2_GR, // Geometric gradient to the arrival height above the ...
    e_HeartRate, // Heart rate in beats per minute.
    // 120.. 
    e_TransponderCode, /* Transponder code */

    e_EngineCHT,  /* Engine Cylinder Head Temperature */
    e_EngineEGT,  /* Engine Exhaust Gas Temperature */
    e_EngineRPM,  /* Engine Revolutions Per Minute */

    e_NUM_TYPES, /* Last item */
    
    e_NUM_AREA_2nd = 500,
    e_DriftAngle = e_NUM_AREA_2nd,
    e_InstantaneousWindSpeed,
    e_InstantaneousWindBearing,
    e_InternalWind,
    e_InternalZigZagWind,

    e_NUM_TYPES_2nd /* Last item 2nd area*/
};

  static constexpr Type NUM_TYPES = e_NUM_TYPES;
  static constexpr Type NUM_TYPES_2nd = e_NUM_TYPES_2nd;
  static constexpr Type MIN_TYPE_VAL = (Type)0;
  static constexpr Type MAX_TYPE_VAL = (Type)(e_NUM_TYPES - 1);

  bool TypeIsValid(Type t);
}
