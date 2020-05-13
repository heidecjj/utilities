# Utilities #
This repository contains some useful utilities used for this project

`chisel-python-script` - This folder contains the necessary files to generate Chisel code that creates bundles for all of the different curves. The Python script expects a CSV file containing all the slope values; such a file may be produced using the point-generator tool.

`float2hex.c` - This c file converts a float number to hexadecimal.

`generateNeuronConfigs` - This folder contains the necessary files to generate different neuron configs.

`Makefile` - Type `make float2hex` onto the command line to build the float2hex executable.

`multiplotter.py` - This Python script depends on matplotlib but will produce multi-subplot windows showing the differences in membrane voltage between an original output (specified as the first argument) and new outputs (all further arguments).

`point-generator` - This folder contains the inputs and Python script necessary to build the CSV file expected by `chisel-python-script` and by the software-LUT version of `parallel-neuro-sim`.

`runLots.sh` - This script runs parallel-neuro-sim through many different configs in a row. All you need to do is choose what configs you want to run, start this script on the Rocket Chip, and wait a long time. You need to keep a terminal attached to the ZedBoard while this runs, so I recommend connecting a Raspberry Pi to the ZedBoard and using that to start running this script.

`runSims.sh` - This is a script slightly different from `runLots.sh` in that its purpose is to run multiple different simulation binaries for comparison rather than running multiple neuron configurations. As a much simpler script, it expects a 5-neuron system with 100% coupling that runs for 10 seconds and will run each binary with and without hardware acceleration enabled. It was written for a version of `parallel-neuro-sim` that automatically uses the performance counters, outputting to `statistics.csv`. This script renames all outputs appropriately and deposits them in an output folder.
