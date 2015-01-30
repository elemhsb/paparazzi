#!/bin/sh -eu

killall openocd ||:
killall st-util ||:
killall telnet ||:

sleep .5

( sleep 5; gnome-terminal --command "telnet localhost 4444" ) &

gnome-terminal --command "/opt/openocd/current/bin/openocd -f board/stm32f4discovery.cfg"

echo done.
exit 0
