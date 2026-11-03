#!/bin/bash

cat input

g++ sol.cpp -o wal

PYTHON_OUT=$(python3 sc.py < input)
CPP_OUT=$(./wal < input)

if [ $PYTHON_OUT = $CPP_OUT ]; then
    echo "Same"
else
    echo "Diff"
    # echo $CPP_OUT
    echo ""
    # echo $PYTHON_OUT
fi