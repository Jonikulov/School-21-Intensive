#!/bin/bash

# Read a single key press
read -n 1 key

if [ "$key" = "a" ]; then
    exit 10
elif [ "$key" = "z" ]; then
    exit 11
elif [ "$key" = "k" ]; then
    exit 20
elif [ "$key" = "m" ]; then
    exit 21
else exit 0
fi