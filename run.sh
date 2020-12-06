#!/bin/bash
cp $1 graph_data.txt
echo  >> graph_data.txt
make all
./matcher < $1
python visualize.py
