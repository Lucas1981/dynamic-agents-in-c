#!/bin/bash

while true; do
    find ./src -name '*.c' | entr -d make

    # Sleep for a brief period to prevent excessive CPU usage
    sleep 1
done
