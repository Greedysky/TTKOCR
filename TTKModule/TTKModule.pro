# =================================================
# * This file is part of the TTK OCR project
# * Copyright (C) 2015 - 2020 Greedysky Studio
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

TEMPLATE = lib
CONFIG += TTK_BUILD_LIB

include(../TTKOCR.pri)

unix:VERSION += $$TTKOCR

win32:TARGET = ../../bin/$$TTKOCR/TTKCore
unix:TARGET = ../lib/$$TTKOCR/TTKCore

INCLUDEPATH += $$PWD

SOURCES += \
    ocrapplicationobject.cpp \
    ocrapplication.cpp


HEADERS  += \
    ocrapplication.h \
    ocrapplicationobject.h
    
    
win32{
    RC_FILE = TTKCore.rc
}
