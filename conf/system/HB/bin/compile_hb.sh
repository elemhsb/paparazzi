#!/bin/sh

cd $PAPARAZZI_HOME
. ./ENV

[ -x ./paparazzi ] || make

for AIRCRAFT in \
   F_HBMINI_V2_MAX1168 \
   F_HBMINI_V2_MPU6000 \
   R_HBMINI_V2_MAX1168 \
   R_HBMINI_V2_MPU6000
do
	bin/clean_ac.sh >/dev/null 2>&1 
	bin/compile.sh 2>&1 | egrep -i 'ap.elf  :|error|warning|\*' | uniq | grep -v waypoint
done
