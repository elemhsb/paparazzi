#!/bin/sh -eu

git clone http://repo.or.cz/openocd.git openocd-openocd

(
    cd openocd-openocd
    ./bootstrap
    ./configure --prefix=/opt/openocd/openocd-0.9.0-devel
    make
    sudo mkdir -p /opt/openocd/openocd-0.9.0-devel
    sudo make install
)

rm -rf openocd-openocd

echo done.
exit 0
