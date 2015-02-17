#!/bin/sh -eu

killall openocd ||:
killall st-util ||:
killall telnet ||:

sleep .5

echo done.
exit 0
