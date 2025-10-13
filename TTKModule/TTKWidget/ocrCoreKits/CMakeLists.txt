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

cmake_minimum_required(VERSION 3.18.0)

set_property(GLOBAL PROPERTY TTK_WIDGET_CORE_KITS_HEADER_FILES
  ${TTK_WIDGET_CORE_DIR}/ocrabstractmovedialog.h
  ${TTK_WIDGET_CORE_DIR}/ocrabstractmovewidget.h
  ${TTK_WIDGET_CORE_DIR}/ocrgiflabelwidget.h
  ${TTK_WIDGET_CORE_DIR}/ocrgrabwidget.h
  ${TTK_WIDGET_CORE_DIR}/ocrwidgetrenderer.h
)

set_property(GLOBAL PROPERTY TTK_WIDGET_CORE_KITS_SOURCE_FILES
  ${TTK_WIDGET_CORE_DIR}/ocrabstractmovedialog.cpp
  ${TTK_WIDGET_CORE_DIR}/ocrabstractmovewidget.cpp
  ${TTK_WIDGET_CORE_DIR}/ocrgiflabelwidget.cpp
  ${TTK_WIDGET_CORE_DIR}/ocrgrabwidget.cpp
  ${TTK_WIDGET_CORE_DIR}/ocrwidgetrenderer.cpp
)
