# ***************************************************************************
# * This file is part of the TTK OCR project
# * Copyright (C) 2015 - 2023 Greedysky Studio
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
# ***************************************************************************

TEMPLATE = app

include($$PWD/../TTKOCR.pri)
include($$PWD/../TTKCommon/TTKApplication/TTKApplication.pri)

TARGET = TTKService

LIBS += -L$$DESTDIR -lTTKCore -lTTKDumper -lTTKConfig

INCLUDEPATH += \
    $$PWD/../TTKConfig \
    $$PWD/../TTKModule \
    $$PWD/../TTKModule/TTKCore/ocrCoreKits \
    $$PWD/../TTKModule/TTKWidget/ocrCoreKits

win32:msvc{
HEADERS += \
    $$PWD/../TTKConfig/ocrconfigobject.h \
    $$PWD/../TTKModule/ocrapplication.h
}

SOURCES += $$PWD/ocrservicemain.cpp

win32:RC_FILE = $$PWD/TTKService.rc
