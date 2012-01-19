#!/bin/sh
#gzip -9
VERSION="1.2-1"
PLATFORM="amd64"
SRCDIR=../../bin64

DEBNAME=basetest_${VERSION}_$PLATFORM.deb

URDIR=`pwd | sed -rn "s/.*\/([^\/]*)$/\1/gp"`;
echo $URDIR
SIZE=`du basetest --exclude=DEBIAN -s | sed -rn "s/^([0-9]+).*/\1/gp"`

cp $SRCDIR/basetest basetest/usr/bin/basetest
#cp control basetest/DEBIAN/control
echo "Version: $VERSION" > basetest/DEBIAN/control
echo "Architecture: $PLATFORM" >> basetest/DEBIAN/control
echo "Installed-Size: $SIZE" >> basetest/DEBIAN/control
cat control >> basetest/DEBIAN/control
cd basetest
md5deep -r usr -l > DEBIAN/md5sums
cd ..
fakeroot dpkg-deb --build basetest
mv basetest.deb $DEBNAME
lintian $DEBNAME
alien --to-rpm --scripts ./$DEBNAME
alien --to-tgz --scripts ./$DEBNAME
mv *.tgz tgz64/
