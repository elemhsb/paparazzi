#!/bin/sh -eu

# https://launchpad.net/gcc-arm-embedded

wget https://launchpad.net/gcc-arm-embedded/4.9/4.9-2014-q4-major/+download/gcc-arm-none-eabi-4_9-2014q4-20141203-linux.tar.bz2

sudo tar -C /opt/arm -xf gcc-arm-none-eabi-4_9-2014q4-20141203-linux.tar.bz2

echo done.
exit 0
