################################################################################
#                                                                              #
#    Copyright 2012 Alexander Vorobyev (Voral)                                 #
#    http://va-soft.ru/                                                        #
#                                                                              #
#    This file is part of basetest.                                            #
#                                                                              #
#    Basetest is free software: you can redistribute it and/or modify          #
#    it under the terms of the GNU General Public License as published by      #
#    the Free Software Foundation, either version 3 of the License, or         #
#    (at your option) any later version.                                       #
#                                                                              #
#    Basetest is distributed in the hope that it will be useful,               #
#    but WITHOUT ANY WARRANTY; without even the implied warranty of            #
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             #
#    GNU General Public License for more details.                              #
#                                                                              #
#    You should have received a copy of the GNU General Public License         #
#    along with basetest.  If not, see <http://www.gnu.org/licenses/>.         #
#                                                                              #
################################################################################

TEMPLATE = app
TARGET =basetest

DEPENDPATH += .
DESTDIR = ../bin
UNAME = $$system(uname -m)
linux-g++-32 {
   DESTDIR = ../bin32
   message(For x86)
   equals(UNAME,"x86_64"){
		message(on x86-64 system)
		LIBS += -L/home/alex/QtSDK32/Desktop/Qt/474/gcc/lib
   }
}
linux-g++-64{
	message(For x86_64)
	DESTDIR = ../bin64
}

QT += core gui
QT -= phonon
OBJECTS_DIR += ../.obj
MOC_DIR += ../.moc
RCC_DIR += ../.rcc
ICON = ./ico/icon.icns

# Input
SOURCES += main.cpp \
	mainwindow.cpp \
	vconfdlg.cpp
HEADERS += mainwindow.h \
	vconfdlg.h

TRANSLATIONS = trans/basetest_ru.ts \
	trans/basetest_en.ts \
	trans/basetest_cs.ts

RESOURCES = basetest.qrc

OTHER_FILES += \
	history.txt
