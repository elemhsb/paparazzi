#!/bin/sh -eu

sudo apt-get -q0 install -y qt4-dev-tools

git clone https://github.com/fpoussin/QStlink2.git fpoussin-QStlink2

(
    cd fpoussin-QStlink2
    git submodule init
    git submodule update

    qmake-qt4
    make
    sudo make install
)

rm -fr fpoussin-QStlink2

sudo reload udev

echo done.
exit 0
