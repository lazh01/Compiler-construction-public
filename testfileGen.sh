#!/bin/bash

# random char and numbers, fixed length
for i in {1..3}; do for x in {1..10};
  do cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 32 | head -n 1 >> t_rdm_$i.txt;
done done;
# random length char and numbers, random length
for i in {1..3}; do for x in {1..10};
  do
  rand=$RANDOM
  let "rand %= 31"
  let "rand += 1"
  cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w $rand | head -n 1 >> t_rdmv_$i.txt;
done done;
# same chars, random length
for i in {1..3}; do for x in {1..10};
  do
  rand=$RANDOM
  let "rand %= 31"
  let "rand += 1"
  cat /dev/urandom | tr -dc 'aA' | fold -w $rand | head -n 1 >> t_smv_$i.txt;
done done;


# random numbers
# for i in {1..10}; do
#   for x in {1..5000}; do
#     echo $RANDOM >> t_$i.dat;
#   done
# done;
