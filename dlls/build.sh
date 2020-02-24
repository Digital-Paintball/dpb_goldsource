#!/bin/sh
if  test `uname -s` = Linux ; then
make pb_i686.so CC=/opt/gcc-2.95/bin/gcc CPP=/opt/gcc-2.95/bin/g++ OSFLAGS="-fPIC -Dstricmp=strcasecmp -Dstrnicmp=strncasecmp"
else
make pb.dll CC=gcc CPP=g++ OSFLAGS="-DWIN32 -D_WINDOWS"
fi
