#!/bin/sh
cd src
qmake32 -spec linux-g++-32 
make clean
make
cd ..
