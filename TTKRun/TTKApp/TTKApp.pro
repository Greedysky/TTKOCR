# =================================================
# * This file is part of the TTK OCR project
# * Copyright (C) 2015 - 2021 Greedysky Studio
#
# * This program is free software; you can redistribute it and/or modify
# * it under the terms of the GNU General Public License as published by
# * the Free Software Foundation; either version 3 of the License, or
# * (at your option) any later version.
#
# * This program is distributed in the hope that it will be useful,
# * but WITHOUT ANY WARRANTY; without even the implied warranty of
# * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# * GNU General Public License for more details.
#
# * You should have received a copy of the GNU General Public License along
# * with this program; If not, see <http://www.gnu.org/licenses/>.
# =================================================

QT       += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include($$PWD/../../TTKVersion.pri)
unix:VERSION += $$TTKOCR

win32:DESTDIR = $$OUT_PWD/../../bin
unix:DESTDIR = $$OUT_PWD/../../lib
TARGET = TTKOCR

TEMPLATE = app

win32:msvc{
    CONFIG +=c++11
}else{
    QMAKE_CXXFLAGS += -std=c++11
}

INCLUDEPATH += \
    $$PWD/../ \
    $$PWD/../../ \
    $$PWD/../../TTKThirdParty \
    $$PWD/../../TTKThirdParty/TTKDumper \
    $$PWD/../../TTKModule/TTKCore/ocrCoreKits

SOURCES += \
    ocrinitobject.cpp \
    ttkrunmain.cpp \
    ttklocalpeer.cpp \
    ttkrunapplication.cpp \
    ttkrunobject.cpp


HEADERS += \
    $$PWD/../ocrrunglobaldefine.h \
    ocrinitobject.h \
    ttkrunobject.h \
    ttklocalpeer.h \
    ttkrunapplication.h


RESOURCES += \
    $$PWD/../../TTKQrc/OCRApp.qrc

win32{
    RC_FILE = TTKApp.rc
}
