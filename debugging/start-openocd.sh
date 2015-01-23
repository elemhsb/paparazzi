#!/bin/sh -eu

killall openocd ||:
killall telnet ||:

sleep .5

( sleep 5; gnome-terminal --command "telnet localhost 4444" ) &

gnome-terminal --command "/opt/local/bin/openocd -f $(dirname $0)/stm32f4discovery.cfg"

echo done.
exit 0
