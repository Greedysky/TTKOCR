#!/bin/sh

dirpath=`dirname $0`
tmp="${dirpath#?}"

if [ "${dirpath%${tmp}}" != "/" ]; then
  dirpath=$PWD/${dirpath}
fi

deskpath=${dirpath}/share/applications
if [ ! -d ${deskpath} ]; then
  mkdir -p ${deskpath}
fi

username=`logname`
if [ "${username}" = "root" ]; then
  homepath=/root
else
  homepath=/home/${username}
fi

packvern=3.1.0.0
packpath=${deskpath}/TTKOCR.desktop
userpath=${homepath}/.local/share/applications
iconpath="${dirpath}/share/pixmaps/ttkocr.png"
execpath="${dirpath}/../TTKOCR"

echo -n "[Desktop Entry]
Type=Application
Version=${packvern}
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
Categories=ocr;Qt;
MimeType=
X-KDE-StartupNotify=false\n" > ${packpath}

cp -rv ${packpath} ${userpath}
rm -R ${deskpath}
chmod +x ${userpath}
