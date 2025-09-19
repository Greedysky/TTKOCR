# ***************************************************************************
# * This file is part of the TTK OCR project
# * Copyright (C) 2015 - 2025 Greedysky Studio
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

QT += core gui
greaterThan(QT_MAJOR_VERSION, 4){ #Qt5
    QT += widgets
}

TEMPLATE = lib
CONFIG += plugin lib

include($$PWD/../../TTKVersion.pri)
include($$PWD/../../TTKBuild.pri)

DESTDIR = $$OUT_PWD/../../bin/$$TTK_VERSION
TARGET = TTKPdf

LIBS += -L$$DESTDIR -lmupdf -lmupdf-third

INCLUDEPATH += $$PWD

HEADERS += $$PWD/document.h

SOURCES += $$PWD/document.cpp

#load extra define
include($$PWD/../TTKThirdParty.pri)

win32:RC_FILE = $$PWD/$${TARGET}.rc
