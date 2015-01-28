#!/bin/sh

mkdir -p /opt/openocd/openocd-0.8.0

(

cd open*
./configure --prefix=/opt/openocd/openocd-0.8.0
make
make install

)

echo done.
exit 0
