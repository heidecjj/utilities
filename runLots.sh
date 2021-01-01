#!/bin/bash
## Requires being in the same directory as parallel-neuro-sim and hpm_counters
## Requires the getCount program to be in a test/ dir if you want counts
## To use counts, uncomment the two lines beginning with test/getCount in runall()

## To run, ./runLots.sh [file]
## file is optional; by default, writes to simout.log
## The runall() function removes the need for "2>&1 | tee file" when running old versions of this script.

# Choose a simulation program
simbin=parallel-neuro-sim-fixed-dt

# Equivalent of CMD's ECHO ON, prints every command executed
# runthis() is not necessary with this included
# Significantly increases verbosity of script when included
# set -v

# Script iterates through configs in here
indir="neuron-configs"

# Neuron outputs go here
outdir="out"

# Statistics go here
statsdir="stats"

# Finished neuron configs are moved here
donedir="done-${indir}"

# This is the verbosity parameter that gets passed to parallel-neuro-sim
verbosity=2

### Don't change anything below this line unless the method of running the program changes! ###

# These two lists are paired together. Elements in runArgs become arguments to parallel-neuro-sim
# while nameArgs become suffixes to output files created when running parallel-neuro-sim with
# their corresponding args in runArgs.
runArgs=( "" "-l" )
nameArgs=( "no-lut" "hard-lut" )

# Equivalent of DOS-style ECHO ON
runthis() {
    echo "$@"
    eval "$@"
}

# Function allows for easy logging with a single command
runall() {
    # Count total number of simulations by
    # (number of neuron configs) * (number of runs each)
    totalruns=$(find "${indir}" -type f | wc -l)
    totalruns=$((${totalruns} * ${#runArgs[@]}))
    currentrun=1

    # Run each neuron config
    for fullfile in `find "${indir}" -type f`
    do
        filename=$(basename -- "${fullfile}")
        extension="${filename##*.}"
        filename="${filename%.*}"

        # Run with each LUT config
        for index in ${!runArgs[*]}
        do
            echo "running sim ${currentrun}/${totalruns}: ${filename}, ${nameArgs[${index}]}"
            # test/getCount reset > /dev/null
            ./hpm_counters &
            runthis "./${simbin} -i ${fullfile} -o ${outdir}/${filename}-${nameArgs[${index}]}.csv -v ${verbosity} ${runArgs[${index}]}"
            killall hpm_counters
            while pgrep hpm_counters > /dev/null; do sleep 1; done
            echo "finished sim ${currentrun}/${totalruns}"
            # test/getCount
            runthis "mv statistics.csv ${statsdir}/stats-${filename}-${nameArgs[${index}]}.csv"
            currentrun=$((${currentrun} + 1))
        done

        # Move neuron config to finished directory
        runthis "mv ${fullfile} ${donedir}/${filename}.${extension}"
    done
}

mkdir -p "${outdir}"
mkdir -p "${statsdir}"
mkdir -p "${donedir}"

logfile="$1"
if [[ -z "$logfile" ]]; then
    echo "Give a filename as an argument to change the log location!"
    logfile="simout.log"
fi

echo "Writing to ${logfile}"
runall 2>&1 | tee "${logfile}"
