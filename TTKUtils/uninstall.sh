#!/bin/sh

username=`logname`
if [ "${username}" = "root" ]; then
  homepath=/root
else
  homepath=/home/${username}
fi

rm -f ${homepath}/.local/share/applications/TTKOCR.desktop
rm -f ${homepath}/.local/share/metainfo/ttkocr.metainfo.xml
