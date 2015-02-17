/*
 * Copyright (C) Heinrich Warmers, Oliver Riesener
 *
 * This file is part of paparazzi
 *
 * paparazzi is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * paparazzi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with paparazzi; see the file COPYING.  If not, see
 * <http://www.gnu.org/licenses/>.
 */
/**
 * @file "modules/meteo/meteo_logger.c"
 * @author Heinrich Warmers, Oliver Riesener
 * collect ins, gps, meteologie data, hires time and log it on sd-card
 */

#include "modules/meteo/meteo_logger.h"

#include "state.h"
#include "autopilot.h"
#include "subsystems/datalink/datalink.h"
#include "subsystems/datalink/downlink.h"
#include "subsystems/chibios-libopencm3/sdLog.h"
#include "subsystems/chibios-libopencm3/chibios_sdlog.h"

#include "subsystems/gps.h"
#include "modules/datalink/extra_pprz_dl.h"

#define LOG_ML 1

/** General structure */
struct MeteoLogger meteo_logger;

static bool_t log_started;
static int conter=0;

/**
 *
 */
void  meteo_logger_init() {
	  log_started = FALSE;
}

/**
 *
 */
void  meteo_logger_periodic() {
#if LOG_ML
  if (pprzLogFile.fs != NULL) {
    if (!log_started) {
      sdLogWriteLog(&pprzLogFile,
                    "autopilot flight time\n");
      log_started = TRUE;
    } else {
/*      sdLogWriteLog(&pprzLogFile, "%d %d %d %d %d %d %d %d %d %d %d %d %d\n",
                    meteo_logger.pressure.data, meteo_logger.temperature.data,
                    meteo_logger.humidity_period, meteo_logger.diff_pressure.data,
                    gps.fix, gps.tow, gps.week,
                    gps.lla_pos.lat, gps.lla_pos.lon, gps.hmsl,
                    gps.gspeed, gps.course, -gps.ned_vel.z);
*/
     conter++;
    	sdLogWriteLog(&pprzLogFile,
                      "%d %d %ld\n",
                      autopilot_flight_time,-gps.ned_vel.z,conter);
       }
  }
#else
#pragma message "LOG_ML not SET"
#endif
}

/**
 *
 */
void meteo_logger_periodic_start() {
}

/**
 *
 */
void meteo_logger_periodic_stop() {
}
