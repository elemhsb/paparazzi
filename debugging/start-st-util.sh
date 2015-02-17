#!/bin/sh
    killall openocd;
    killall telnet;

(
    killall st-util;
    sleep .5
    # texane-stlink/gdbserver/st-util -v &
    st-util -v &
    sleep .5
)
