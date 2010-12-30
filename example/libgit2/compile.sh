#!/bin/bash
gcc -o ${1%.c} -D_FILE_OFFSET_BITS=64 -lgit2 ${1}
