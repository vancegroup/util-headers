#!/bin/sh

PROJECT=$(cd $(dirname $0) && pwd)
astyle -n --recursive "${PROJECT}/util/*.h" --recursive "${PROJECT}/tests/*.cpp"

