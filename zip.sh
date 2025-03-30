#!/bin/zsh

rm -f lens.zip
find . -name "*.h" -depth 1 -o -name "*.cpp" -depth 1 | zip lens.zip -@

