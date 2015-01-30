#!/bin/sh -eu

st-flash --reset write $PAPARAZZI_HOME/var/aircrafts/current/ap/ap.bin 0x08000000

echo done.
exit 0

