#!/bin/sh

if [ -z "$2" ]; then
	echo "Usage: $0 package version"
	exit 1
fi

EXEC=$1
VER=$2

TMP=/tmp/
DIST=${EXEC}-${VER}

rm -rf ${TMP}/${DIST}
mkdir ${TMP}/${DIST}
find . | grep -v /CVS | grep -v /.gdb | grep -v .bz2$ | cpio -pv ${TMP}/${DIST}
tar cvI -f ${TMP}/${DIST}.tar.bz2 -C ${TMP} ${DIST}
rm -rf ${TMP}/${DIST}

echo "Archive ${TMP}/${DIST}.tar.bz2 was created"
