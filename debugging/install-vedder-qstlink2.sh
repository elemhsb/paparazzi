#!/bin/sh -eu

unzip -x vedder-qstlink2.zip
mv qstlink2 vedder-qstlink2

(
    cd vedder-qstlink2
    qmake-qt4
)

echo done.
exit 0
