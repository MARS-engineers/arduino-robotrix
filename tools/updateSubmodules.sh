#!/bin/sh
set -e
git submodule update --init --recursive
git submodule foreach --recursive git fetch origin
git submodule foreach --recursive git checkout master
git submodule foreach --recursive git pull origin master