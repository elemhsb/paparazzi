#!/bin/sh

cd $PAPARAZZI_HOME
. ./ENV

echo "*** $AIRCRAFT **** sim ****************************************************************************" | cut -c -79
make AIRCRAFT=$AIRCRAFT clean_ac sim
echo "*** $AIRCRAFT **** sim ****************************************************************************" | cut -c -79;
echo
echo
echo "*** $AIRCRAFT **** ap *****************************************************************************" | cut -c -79
make AIRCRAFT=$AIRCRAFT clean_ac nps
echo "*** $AIRCRAFT **** ap *****************************************************************************" | cut -c -79;
echo
echo
echo "*** $AIRCRAFT **** ap *****************************************************************************" | cut -c -79
make AIRCRAFT=$AIRCRAFT clean_ac ap
echo "*** $AIRCRAFT **** ap *****************************************************************************" | cut -c -79;
echo
echo
