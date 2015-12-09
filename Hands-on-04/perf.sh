#!/bin/bash
if [ -z "$PMI_RANK" ] ; then

  perf stat $@ 2> $1.out.perf

else 
  perf stat $@ 2> $1.$PMI_RANK.perf

fi

