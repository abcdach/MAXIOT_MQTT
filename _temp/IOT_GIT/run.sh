#!/bin/bash

uname -a | grep x86 > /dev/null 2>&1
if [ $? -eq 0 ]; then
	echo "x86mm"
fi
uname -a | grep arm > /dev/null 2>&1
if [ $? -eq 0 ]; then
	echo "arm"
fi




			