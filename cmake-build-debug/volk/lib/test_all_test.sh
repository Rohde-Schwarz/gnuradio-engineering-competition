#!/bin/sh
export IFS=:
export srcdir="/home/zhiwei/WorkSpace/gnuradio/volk/lib"
export PATH="$1:$PATH"
export LD_LIBRARY_PATH="$*:$LD_LIBRARY_PATH"
test_all 
