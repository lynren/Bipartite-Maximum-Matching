#!/bin/bash
cp $1 graph_data.txt
echo  >> graph_data.txt
./a.out < $1
python visualize.py
