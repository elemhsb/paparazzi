#!/bin/sh

# destination dir
sudo mkdir -p /opt/openocd/openocd-0.8.0

# download
[ -s openocd-0.8.0.tar.bz2 ] || \
	wget http://sourceforge.net/projects/openocd/files/openocd/0.8.0/openocd-0.8.0.tar.bz2

# extract
[ -s openocd-0.8.0 ] || \
	tar xf openocd-0.8.0.tar.bz2

# config, compile, install
(
    cd openocd-0.8.0
    ./configure --prefix=/opt/openocd/openocd-0.8.0
    make
    sudo make install
)

# current links
sudo rm /opt/openocd/current
sudo ln -s openocd-0.8.0 /opt/openocd/current

# clean local
rm -r openocd-0.8.0*

echo done.
exit 0
