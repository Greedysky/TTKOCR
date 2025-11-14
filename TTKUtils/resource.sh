#!/bin/sh

source="$1/_extras"
output="$2"

#make output dir
mkdir -p "${output}"

#copy
cp -rv "${source}/TTKInit.sh" "${output}/TTKInit.sh"
cp -rv "${source}/TTKOCR.sh" "${output}/../TTKOCR.sh"
cp -rv "${source}/TTKRoutine.sh" "${output}/../TTKRoutine.sh"
cp -rv "${source}/TTKService.sh" "${output}/TTKService.sh"
cp -rv "${source}/TTKRoutineCopy.sh" "${output}/TTKRoutineCopy.sh"

#chmod
chmod +x "${output}/TTKInit.sh"
chmod +x "${output}/../TTKOCR.sh"
chmod +x "${output}/../TTKRoutine.sh"
chmod +x "${output}/TTKService.sh"
chmod +x "${output}/TTKRoutineCopy.sh"
