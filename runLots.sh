#!/bin/bash
## Requires being in the same directory as parallel-neuro-sim and hpm_counters
## Requires the get count program to be in a test/ dir
## To run, ./runLots.sh 2>&1 | tee simout.txt

# Script will iterate through configs in this dir
inputdir="configsToRun"
# Neuron output will be put in this dir
outputdir="out"
# Statistics will be put in this dir
statisticsdir="stats"

# This is the verbosity parameter that gets passed to parallel-neuro-sim
verbosity=2

# These two lists are paired together. Elements in runArgs become arguments to parallel-neuro-sim
# while namedArgs become suffixes to output files created when running parallel-neuro-sim with
# their corresponding args in runArgs.
runArgs=( "" "-l" )
namedArgs=( "no-lut" "hard-lut" )

runthis() {
  echo "$@"
  eval "$@"
}

mkdir -p $outputdir
mkdir -p $statisticsdir
for fullfile in `find configsToRun/ -type f`
do
  filename=$(basename -- "$fullfile")
  extension="${filename##*.}"
  filename="${filename%.*}"
  for index in ${!runArgs[*]}
  do
    test/getCount reset > /dev/null
    ./hpm_counters &
    runthis "./parallel-neuro-sim -i ${fullfile} -o ${outputdir}/${filename}_${namedArgs[$index]}.csv -v ${verbosity} ${runArgs[$index]}"
    killall hpm_counters
    while pgrep hpm_counters > /dev/null; do sleep 1; done
    test/getCount
    runthis "mv statistics.csv ${statisticsdir}/stats_${filename}_${namedArgs[$index]}.csv"
  done
done
