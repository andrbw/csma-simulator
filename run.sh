#!/bin/bash

rm -rf result.dat

for lambda in 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1.0 1.1 1.2 1.3 1.4 1.5 1.6 2.0 3.0 4.0 5.0 10.0
do
  ./scenario 1 $lambda 1 100000 1 >> result.dat
done


