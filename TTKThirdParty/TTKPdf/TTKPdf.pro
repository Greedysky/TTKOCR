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

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = lib

include($$PWD/../../TTKVersion.pri)
include($$PWD/../../TTKBuild.pri)

DESTDIR = $$OUT_PWD/../../bin/$$TTKPdf
TARGET = TTKPdf

LIBS += -L$$DESTDIR -lmupdf -lfreetype -ljbig2dec -ljpeg -lmujs -lopenjpeg -lz

CONFIG += plugin lib

INCLUDEPATH += $$PWD \
               $$PWD/include \
               $$PWD/src/private \
               $$PWD/mupdf

HEADERS  += \
    $$PWD/include/mupdf-document.h \
    $$PWD/include/mupdf-link.h \
    $$PWD/include/mupdf-outline.h \
    $$PWD/include/mupdf-page.h \
    $$PWD/include/mupdf-qt.h \
    $$PWD/include/mupdf-textbox.h \
    $$PWD/src/private/mupdf-document_p.h \
    $$PWD/src/private/mupdf-link_p.h \
    $$PWD/src/private/mupdf-outline_p.h \
    $$PWD/src/private/mupdf-page_p.h \
    $$PWD/src/private/mupdf-textbox_p.h
    
SOURCES += \
    $$PWD/src/mupdf-document.cpp \
    $$PWD/src/mupdf-link.cpp \
    $$PWD/src/mupdf-outline.cpp \
    $$PWD/src/mupdf-page.cpp \
    $$PWD/src/mupdf-textbox.cpp

#load extra define
include($$PWD/../TTKExtrasDefine.pri)

win32:RC_FILE = TTKPdf.rc
