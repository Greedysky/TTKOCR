#!/bin/sh

dirpath=`dirname $0`
tmp="${dirpath#?}"

if [ "${dirpath%${tmp}}" != "/" ]; then
  dirpath=$PWD/${dirpath}
fi

username=`logname`
if [ "${username}" = "root" ]; then
  homepath=/root
else
  homepath=/home/${username}
fi

packpath=${dirpath}/TTKOCR.desktop
userpath=${homepath}/.local/share/applications
iconpath="${dirpath}/share/pixmaps/ttkocr.png"
execpath="${dirpath}/../TTKOCR"

sh ${dirpath}/make_desktop_raw.sh ${packpath} ${iconpath} ${execpath}

mv -fv ${packpath} ${userpath}
chmod +x ${userpath}
