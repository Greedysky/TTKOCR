# =================================================
# * This file is part of the TTK OCR project
# * Copyright (C) 2015 - 2019 Greedysky Studio
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

equals(QT_MAJOR_VERSION, 4){
CONFIG   += gcc
}
equals(QT_MAJOR_VERSION, 5){
QT       += widgets
}

UI_DIR = ./.build/ui
MOC_DIR = ./.build/moc
OBJECTS_DIR = ./.build/obj
RCC_DIR = ./.build/rcc

include(TTKVersion.pri)
include(TTKBuild.pri)


##openssl lib check
win32:{
    SSL_DEPANDS = $$OUT_PWD/bin/$$TTKOCR/ssleay32.dll
    SSL_DEPANDS = $$replace(SSL_DEPANDS, /, \\)
    exists($$SSL_DEPANDS):LIBS += -L../bin/$$TTKOCR -lssl
}
unix:!mac{
    SSL_DEPANDS = $$OUT_PWD/lib/$$TTKOCR/libssleay32.so
    exists($$SSL_DEPANDS):LIBS += -L../lib/$$TTKOCR -lssl
}

win32{
    equals(QT_MAJOR_VERSION, 5){
        greaterThan(QT_VER_MINOR, 1):QT  += winextras
        msvc{
            LIBS += -lshell32 -luser32
            LIBS += -L../bin/$$TTKOCR -lTTKUi -lTTKExtras -lzlib -lTTKZip
            contains(CONFIG, TTK_BUILD_BY_PDF){
                LIBS += -L../lib/$$TTKOCR -lTTKPdf
            }
            CONFIG +=c++11
            !contains(QMAKE_TARGET.arch, x86_64){
                 #support on windows XP
                 QMAKE_LFLAGS_WINDOWS = /SUBSYSTEM:WINDOWS,5.01
                 QMAKE_LFLAGS_CONSOLE = /SUBSYSTEM:CONSOLE,5.01
            }
        }

        gcc{
            LIBS += -L../bin/$$TTKOCR -lTTKUi -lTTKExtras -lzlib -lTTKZip
            contains(CONFIG, TTK_BUILD_BY_PDF){
                LIBS += -L../lib/$$TTKOCR -lTTKPdf
            }
            QMAKE_CXXFLAGS += -std=c++11
            QMAKE_CXXFLAGS += -Wunused-function
            QMAKE_CXXFLAGS += -Wswitch
        }
    }

    equals(QT_MAJOR_VERSION, 4){
        QT  += multimedia
        gcc{
            LIBS += -L../bin/$$TTKOCR -lTTKUi -lTTKExtras -lzlib -lTTKZip
            contains(CONFIG, TTK_BUILD_BY_PDF){
                LIBS += -L../lib/$$TTKOCR -lTTKPdf
            }
            QMAKE_CXXFLAGS += -std=c++11
            QMAKE_CXXFLAGS += -Wunused-function
            QMAKE_CXXFLAGS += -Wswitch
        }
    }
}

unix:!mac{
    LIBS += -L../lib/$$TTKOCR -lTTKUi -lTTKExtras -lzlib -lTTKZip
    contains(CONFIG, TTK_BUILD_BY_PDF){
        LIBS += -L../lib/$$TTKOCR -lTTKPdf
    }
    QMAKE_CXXFLAGS += -std=c++11
    QMAKE_CXXFLAGS += -Wunused-function
    QMAKE_CXXFLAGS += -Wswitch
}

DEFINES += TTK_LIBRARY

#########################################
HEADERS += \
    $$PWD/ocrglobal.h
INCLUDEPATH += $$PWD
#########################################
include(TTKThirdParty/TTKThirdParty.pri)
#########################################
include(TTKModule/TTKModule.pri)

