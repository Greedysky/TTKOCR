#!/bin/sh

path=share/applications
if [ ! -d $path ]; then
  mkdir $path
fi

curpath=$PWD/deploy
if [ $# -eq 0 ]; then
  curpath=$PWD
fi

datapath=$path/TTKOCR.desktop
packpath="$curpath/$datapath"
userpath=~/.local/$datapath
iconpath="$curpath/share/pixmaps/ttkocr.png"
execpath="$curpath/../TTKOCR"

echo -n "[Desktop Entry]
Type=Application
Version=3.1.0.0
Name=TTKOCR
Name[zh_CN]=文字识别
Name[zh_TW]=文字識別
GenericName=TTKOCR
GenericName[zh_CN]=文字识别
GenericName[zh_TW]=文字識別
Comment=TTKOCR
Comment[zh_CN]=文字识别
Comment[zh_TW]=文字識別
Icon=$iconpath
Exec=$execpath
Terminal=false
Keywords=multimedia;ocr;
Categories=ocr;Qt;
MimeType=
X-KDE-StartupNotify=false\n" > $packpath

cp -rv $packpath $userpath
chmod +x $userpath
