#!/bin/bash

# This will run include-what-you-want on all the .c and .h files
for file in ./src/*.{c,h}; do
  include-what-you-use -I/opt/homebrew/include/SDL2 "$file"
done
