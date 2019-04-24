#!/bin/bash
MAX=67108864
MODE=1
ARCHIVO=data_mergesort.dat
rm -f ./$ARCHIVO
for ((N=2; N<=$MAX; N=N*2))
do
  if [ $MODE = 0 ]
  then
    ./main $N
  elif [ $MODE = 1 ]
  then
    ./main $N >> $ARCHIVO
  else
    echo $N
  fi
done
