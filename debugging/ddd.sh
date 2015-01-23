#!/bin/sh -eu

killall st-util ||:
# texane-stlink/st-flash erase

./start-st-util.sh

ddd --debugger "/opt/arm/gcc-arm-none-eabi-4_7-2013q3/bin/arm-none-eabi-gdb  -x st-util.gdb"

echo done.
exit 0
