#!/bin/bash

while true; do
    find ./src -name '*.c' | entr -d make
done
