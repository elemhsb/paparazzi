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
 * @file subsystems/imu/imu_hbimu.h
 * Driver for the HBIMU SPI1 for the MPU6000 and I2C1 for the HMC5883.
 */

#ifndef IMU_HBIMU_SPI_H
#define IMU_HBIMU_SPI_H

#include "std.h"
#include "generated/airframe.h"
#include "subsystems/imu.h"

#include "subsystems/imu/imu_mpu60x0_defaults.h"
#include "peripherals/mpu60x0_spi.h"
#include "peripherals/hmc58xx.h"

#if !defined IMU_GYRO_P_SIGN & !defined IMU_GYRO_Q_SIGN & !defined IMU_GYRO_R_SIGN
#define IMU_GYRO_P_SIGN   1
#define IMU_GYRO_Q_SIGN   1
#define IMU_GYRO_R_SIGN   1
#endif
#if !defined IMU_ACCEL_X_SIGN & !defined IMU_ACCEL_Y_SIGN & !defined IMU_ACCEL_Z_SIGN
#define IMU_ACCEL_X_SIGN  1
#define IMU_ACCEL_Y_SIGN  1
#define IMU_ACCEL_Z_SIGN  1
#endif
#if !defined IMU_MAG_X_SIGN & !defined IMU_MAG_Y_SIGN & !defined IMU_MAG_Z_SIGN
#define IMU_MAG_X_SIGN 1
#define IMU_MAG_Y_SIGN 1
#define IMU_MAG_Z_SIGN 1
#endif

struct ImuHbimu {
  volatile bool_t gyro_valid;
  volatile bool_t accel_valid;
  volatile bool_t mag_valid;
  struct Mpu60x0_Spi mpu;
  struct Hmc58xx hmc;
};

extern struct ImuHbimu imu_hbimu;

extern void imu_hbimu_event(void);


static inline void ImuEvent(void (* _gyro_handler)(void), void (* _accel_handler)(void), void (* _mag_handler)(void)) {
  imu_hbimu_event();
  if (imu_hbimu.gyro_valid) {
    imu_hbimu.gyro_valid = FALSE;
    _gyro_handler();
  }
  if (imu_hbimu.accel_valid) {
    imu_hbimu.accel_valid = FALSE;
    _accel_handler();
  }
  if (imu_hbimu.mag_valid) {
    imu_hbimu.mag_valid = FALSE;
    _mag_handler();
  }
}

#endif /* IMU_HBIMU_H */
