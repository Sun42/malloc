#!/bin/sh

if [ $HOSTTYPE = "FreeBSD" ]; then
echo "Configuration pour FreeBSD"
setenv toto "titi"
#set toot titi
setenv LD_LIBRARY_PATH "."
#setenv LD_PRELOAD "libmy_malloc_$(HOSTTYPE).so"
fi
if [ $HOSTTYPE = "sun4" ]; then
echo "Configuration pour Sun"
#setenv LD_PRELOAD "libmy_malloc_$(HOSTTYPE).so"
fi
