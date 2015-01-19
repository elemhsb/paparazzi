#!/bin/sh -eu

killall openocd ||:

sleep .5

openocd -f stm32f4discovery.cfg

echo done.
exit 0
