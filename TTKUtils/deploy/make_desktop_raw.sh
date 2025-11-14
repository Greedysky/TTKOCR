#!/bin/sh

packpath="$1"
iconpath="$2"
execpath="$3"

echo -n "[Desktop Entry]
Type=Application
Version=1.0
Name=TTKOCR
Name[zh_CN]=文字识别
Name[zh_TW]=文字識別
GenericName=TTKOCR
GenericName[zh_CN]=文字识别
GenericName[zh_TW]=文字識別
Comment=TTKOCR
Comment[zh_CN]=文字识别
Comment[zh_TW]=文字識別
Icon=${iconpath}
Exec=${execpath}
Terminal=false
Keywords=multimedia;ocr;
Categories=Utility;OCR;Qt;
MimeType=
X-KDE-StartupNotify=false\n" > ${packpath}
