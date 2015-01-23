#!/bin/sh -eu

# xJ2pV947Fg

mkdir -p windows

#smbmount -o user=elemhsb //V-WINDOWS7/Users/riesener/Documents/paparazzi windows
smbmount -o user=elemhsb,uid=1000 //192.168.26.126/Users/riesener/Documents/paparazzi windows

echo done.
exit 0
