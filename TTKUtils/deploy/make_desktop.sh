#!/bin/sh

path=share/applications
if [ ! -d $path ]; then
  mkdir $path
fi

datapath=$path/TTKOCR.desktop
packpath="$PWD/$datapath"
userpath=~/.local/$datapath
iconpath="$PWD/share/pixmaps/ttkocr.png"
execpath="$PWD/../TTKOCR"

echo -n "[Desktop Entry]
Type=Application
Version=2.8.0.0
Name=TTKOCR
Name[zh_CN]=OCR
Name[zh_TW]=OCR
GenericName=TTKOCR
GenericName[zh_CN]=OCR
GenericName[zh_TW]=OCR
Comment=TTKOCR
Comment[zh_CN]=OCR
Comment[zh_TW]=OCR
Icon=$iconpath
Exec=$execpath
Terminal=false
Keywords=multimedia;ocr;
Categories=ocr;Qt;
MimeType=
X-KDE-StartupNotify=false\n" > $packpath

cp -rv $packpath $userpath
chmod +x $userpath
