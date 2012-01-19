#!/bin/sh
cd src
qmake
make clean
make
cd ..
