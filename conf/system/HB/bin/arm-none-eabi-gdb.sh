#!/bin/sh -e

cd "$PAPARAZZI_HOME"

echo AIRCRAFT = $AIRCRAFT
rm -f var/current
ln -s aircrafts/"$AIRCRAFT" var/current

# Called from commandline
# olri arm-none-eabi-gdbtui --command=conf/system/HB/gdbinit-lpc21xx.gdb "$@"
arm-none-eabi-gdb --command=conf/system/HB/gdbinit-lpc21xx.gdb "$@"
