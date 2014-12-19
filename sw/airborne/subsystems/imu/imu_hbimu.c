/*
 * Copyright (C) 2013 Felix Ruess <felix.ruess@gmail.com>
 * Copyright (C) 2014 Oliver Riesener <Oliver.Riesener@hs-bremen.de>
 *
 * This file is part of paparazzi.
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
 * along with paparazzi; see the file COPYING.  If not, write to
 * the Free Software Foundation, 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

/**
 * @file subsystems/imu/imu_hbmini.c
 * Driver for the HBMINI SPI1 for the MPU6000 and I2C1 for the HMC5883.
 */

#include "subsystems/imu.h"

#include "mcu_periph/spi.h"
#include "peripherals/hmc58xx_regs.h"

/* MPU60x0 gyro/accel internal lowpass frequency */
#if !defined HBIMU_LOWPASS_FILTER && !defined  HBIMU_SMPLRT_DIV
#if (PERIODIC_FREQUENCY == 60) || (PERIODIC_FREQUENCY == 120)
/* Accelerometer: Bandwidth 44Hz, Delay 4.9ms
 * Gyroscope: Bandwidth 42Hz, Delay 4.8ms sampling 1kHz
 */
#define HBIMU_LOWPASS_FILTER MPU60X0_DLPF_42HZ
#define HBIMU_SMPLRT_DIV 9
PRINT_CONFIG_MSG("Gyro/Accel output rate is 100Hz at 1kHz internal sampling")
#elif PERIODIC_FREQUENCY == 512
/* Accelerometer: Bandwidth 260Hz, Delay 0ms
 * Gyroscope: Bandwidth 256Hz, Delay 0.98ms sampling 8kHz
 */
#define HBIMU_LOWPASS_FILTER MPU60X0_DLPF_256HZ
#define HBIMU_SMPLRT_DIV 3
PRINT_CONFIG_MSG("Gyro/Accel output rate is 2kHz at 8kHz internal sampling")
#else
#error Non-default PERIODIC_FREQUENCY: please define HBIMU_LOWPASS_FILTER and HBIMU_SMPLRT_DIV.
#endif
#endif
PRINT_CONFIG_VAR(HBIMU_LOWPASS_FILTER);
PRINT_CONFIG_VAR(HBIMU_SMPLRT_DIV);

#ifndef HBIMU_GYRO_RANGE
#define HBIMU_GYRO_RANGE MPU60X0_GYRO_RANGE_2000
#endif
PRINT_CONFIG_VAR(HBIMU_GYRO_RANGE)

#ifndef HBIMU_ACCEL_RANGE
#define HBIMU_ACCEL_RANGE MPU60X0_ACCEL_RANGE_16G
#endif
PRINT_CONFIG_VAR(HBIMU_ACCEL_RANGE)

struct ImuHbimu imu_hbimu;

void imu_impl_init(void) {
  imu_hbimu.accel_valid = FALSE;
  imu_hbimu.gyro_valid = FALSE;
  imu_hbimu.mag_valid = FALSE;

  /* MPU is on spi1 and CS is SLAVE2 */
  mpu60x0_spi_init(&imu_hbimu.mpu, &spi1, SPI_SLAVE5);
  // change the default configuration
  imu_hbimu.mpu.config.smplrt_div = HBIMU_SMPLRT_DIV;
  imu_hbimu.mpu.config.dlpf_cfg = HBIMU_LOWPASS_FILTER;
  imu_hbimu.mpu.config.gyro_range = HBIMU_GYRO_RANGE;
  imu_hbimu.mpu.config.accel_range = HBIMU_ACCEL_RANGE;

  /* initialize mag on i2c1 and set default options */
  hmc58xx_init(&imu_hbimu.hmc, &i2c1, HMC58XX_ADDR);
}

void imu_periodic(void) {
  mpu60x0_spi_periodic(&imu_hbimu.mpu);

  // Read HMC58XX at 50Hz (main loop for rotorcraft: 512Hz)
  RunOnceEvery(10, hmc58xx_periodic(&imu_hbimu.hmc));
}

void imu_hbimu_event(void) {
  mpu60x0_spi_event(&imu_hbimu.mpu);
  if (imu_hbimu.mpu.data_available) {
    RATES_ASSIGN(imu.gyro_unscaled,
        -imu_hbimu.mpu.data_rates.rates.p,
        imu_hbimu.mpu.data_rates.rates.q,
        -imu_hbimu.mpu.data_rates.rates.r);
    VECT3_ASSIGN(imu.accel_unscaled,
        -imu_hbimu.mpu.data_accel.vect.x,
        imu_hbimu.mpu.data_accel.vect.y,
        -imu_hbimu.mpu.data_accel.vect.z);
    int16_t te = (int16_t) imu_hbimu.mpu.temp;
    imu.temp_unscaled = te;
    imu.temp = (int32_t) ((float) (te) / 34 + 365.3);  // store for temperature correction
#define OLRI 1
#if OLRI // FIXME -30 - 80 Grad ??? wenn , warum dann nicht -30 oder 80 als min / max
        if( (-300 > imu.temp || imu.temp > 800) ) {  // kills temp hangs from out of range
          imu.temp = 373;// set hard default value
          imu.temp_unscaled = (imu.temp-365.3)/34;// recalc unscaled temp
        }
#endif // OLRI
    imu_hbimu.mpu.data_available = FALSE;
    imu_hbimu.gyro_valid = TRUE;
    imu_hbimu.accel_valid = TRUE;
  }

  /* HMC58XX event task */
  hmc58xx_event(&imu_hbimu.hmc);
  if (imu_hbimu.hmc.data_available) {
    imu.mag_unscaled.x = -imu_hbimu.hmc.data.vect.y;
    imu.mag_unscaled.y = -imu_hbimu.hmc.data.vect.x;
    imu.mag_unscaled.z = imu_hbimu.hmc.data.vect.z;
    imu_hbimu.hmc.data_available = FALSE;
    imu_hbimu.mag_valid = TRUE;
  }
}

