# Utilities #
This repository contains some useful utilities used for this project

`chisel-python-script` - This folder contains the necessary files to generate Chisel code that creates bundles for all of the different curves.

`float2hex.c` - This c file converts a float number to hexadecimal.

`generateNeuronConfigs` - This folder contains the necessary files to generate different neuron configs.

`Makefile` - Type `make float2hex` onto the command line to build the float2hex executable.

`runLots.sh` - This script runs parallel-neuro-sim through many different configs in a row. All you need to do is choose what configs you want to run, start this script on the Rocket Chip, and wait a long time. You need to keep a terminal attached to the ZedBoard while this runs, so I recommend connecting a Raspberry Pi to the ZedBoard and using that to start running this script.
