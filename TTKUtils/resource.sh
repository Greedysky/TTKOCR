#!/bin/sh

SOURCE="$1/_extras"
OUTPUT="$2"

#make output dir
mkdir -p "${OUTPUT}"

#copy
cp -rv "${SOURCE}/TTKInit.sh" "${OUTPUT}/TTKInit.sh"
cp -rv "${SOURCE}/TTKOCR.sh" "${OUTPUT}/../TTKOCR.sh"
cp -rv "${SOURCE}/TTKRoutine.sh" "${OUTPUT}/../TTKRoutine.sh"
cp -rv "${SOURCE}/TTKService.sh" "${OUTPUT}/TTKService.sh"
cp -rv "${SOURCE}/TTKRoutineCopy.sh" "${OUTPUT}/TTKRoutineCopy.sh"

#chmod
chmod +x "${OUTPUT}/TTKInit.sh"
chmod +x "${OUTPUT}/../TTKOCR.sh"
chmod +x "${OUTPUT}/../TTKRoutine.sh"
chmod +x "${OUTPUT}/TTKService.sh"
chmod +x "${OUTPUT}/TTKRoutineCopy.sh"
