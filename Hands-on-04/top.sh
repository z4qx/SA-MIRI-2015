#!/bin/bash

for (( c=1; c<=5; c++ )) ; do

top -n 1 -b -u $USER 
sleep 2

done 

