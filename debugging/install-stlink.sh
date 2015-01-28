#!/bin/sh -eu

sudo apt-get -q0 install -y pkg-config libusb-1.0-0 libusb-1.0-0-dev

git clone https://github.com/texane/stlink texane-stlink

(
    cd texane-stlink

    ./autogen.sh
    ./configure --prefix=/opt/local
    make
    sudo make install
    sudo cp -n 49-stlinkv2*.rules /etc/udev/rules.d ||:
)

rm -fr texane-stlink

sudo reload udev

echo done.
exit 0
