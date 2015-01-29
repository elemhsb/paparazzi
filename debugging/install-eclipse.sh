#!/bin/sh -eu

# wget http://www.eclipse.org/downloads/download.php?file=/technology/epp/downloads/release/kepler/SR2/eclipse-cpp-kepler-SR2-linux-gtk-x86_64.tar.gz&mirror_id=580

rm /opt/eclipse/kepler

tar -C /opt/eclipse -xf eclipse-cpp-kepler-SR2-linux-gtk-x86_64.tar.gz

cd /opt/eclipse
mv eclipse kepler
rm current
ln -s kepler current

echo done.
exit 0
