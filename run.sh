#!/bin/bash
cp $1 graph_data.txt
{ if [ ! -e matcher ]; then make all; fi } &> /dev/null
./matcher < $1
python visualize.py
