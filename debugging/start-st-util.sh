#!/bin/sh
    killall openocd;

(
    killall st-util;
    sleep .5
    texane-stlink/gdbserver/st-util -v &
    sleep .5
)
