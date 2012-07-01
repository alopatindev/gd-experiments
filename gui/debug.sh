#!/bin/sh

cmake CMakeLists.txt && gdb --eval-command=r ./hello
