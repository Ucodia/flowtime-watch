#!/usr/bin/env bash

# Find relative path of script location and move to root
ROOT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )"/.. &> /dev/null && pwd )"
cd $ROOT_DIR

# Init git submodules
git submodule update --init
git -C ./sensor-watch submodule update --init

# Hack: I was not able to override the original headers files with the local ones
rm ./sensor-watch/movement/movement_config.h
rm ./sensor-watch/movement/movement_faces.h

# Delete and create release directory
rm -rf ./release
mkdir ./release

# Build each board variant firmwares
for color in RED GREEN BLUE; do
    make -C ./make clean COLOR="$color"
    make -C ./make --silent COLOR="$color"
    cp ./make/build/watch.uf2 "./release/flowtime_watch_${color}.uf2"
done

echo "------------------------------"
echo "📦 Release created in the release/ directory"
ls ./release | xargs -I {} shasum -a 256 ./release/{}