# ***************************************************************************
# * This file is part of the TTK OCR project
# * Copyright (C) 2015 - 2026 Greedysky Studio
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

cmake_minimum_required(VERSION 3.18.0)

project(TTKPdf)

set(HEADER_FILES
  document.h
)

set(SOURCE_FILES
  document.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/mupdf/include)

set(QT_LINK_LIBS PRIVATE mupdf mupdf-third)

if(TTK_QT_VERSION VERSION_EQUAL "4")
  list(APPEND QT_LINK_LIBS ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
elseif(TTK_QT_VERSION VERSION_EQUAL "5")
  list(APPEND QT_LINK_LIBS Qt5::Core Qt5::Gui)
elseif(TTK_QT_VERSION VERSION_EQUAL "6")
  list(APPEND QT_LINK_LIBS Qt6::Core Qt6::Gui)
endif()

if(TTK_BUILD_SHARED)
  add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${HEADER_FILES})
else()
  add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})
endif()
target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/mupdf/build/release)
target_link_libraries(${PROJECT_NAME} ${QT_LINK_LIBS})
