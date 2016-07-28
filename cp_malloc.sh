#!/bin/sh

cat "mymalloc.c" | sed "s/mymalloc/malloc/" |  sed "s/myrealloc/realloc/" |
sed "s/myfree/free/" | cat > real_malloc.c