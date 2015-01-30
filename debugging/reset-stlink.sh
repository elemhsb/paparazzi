#!/bin/sh -eu

make -C $(dirname $0) usbreset

$(lsusb -d 0483:3748 | awk -F '[ :]'  '{ print "/dev/bus/usb/"$2"/"$4 }' | xargs -I {} echo "$(dirname $0)/usbreset {}")

echo done.
exit 0
