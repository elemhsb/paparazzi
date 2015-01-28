#!/bin/sh -eu

sudo apt-get -q0 install -y qt4-dev-tools

git clone https://github.com/fpoussin/QStlink2.git fpoussin-QStlink2

(
    cd fpoussin-QStlink2
    git submodule init
    git submodule update

    qmake-qt4
    cat <<EOF | patch -p1
diff --git a/res/devices.xml b/res/devices.xml
index c65d23a..1ddd65c 100644
--- a/res/devices.xml
+++ b/res/devices.xml
@@ -260,7 +260,7 @@
       <CR_SER>0x1</CR_SER>
       <SR_PER>0x1</SR_PER>
       <CR_PGSIZE>0x8</CR_PGSIZE>
-      <sram_size>0x4000</sram_size>
+      <sram_size>0x30000</sram_size>
     </device>
 
     <device type="STM32F42x/43x" regtype="STM32F4" coretype="CM4F">
EOF
    make
    sudo make install
)

rm -fr fpoussin-QStlink2

sudo reload udev

echo done.
exit 0
