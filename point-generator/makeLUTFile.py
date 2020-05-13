#!/usr/bin/env python

import math
import sys

def sigmoid(x):
    return 1/(1+math.exp(-x))

def invcosh(x):
    return 2/(math.exp(x) + math.exp(-x))

def weird(x):
    return 1/(1 + 2*math.exp(x) + math.exp(50.0*x/18))

def getOffset(x, y, slope):
    return y - x*slope

def printFloatArray(arr):
    #print(','.join("{}".format(x) for x in arr))
    print(','.join("{:.4f}".format(x) for x in arr))

if len(sys.argv) != 4:
    print("Incorrect number of arguments. Expected usage:")
    print("{} <sigmoid vMem> <weirdMoid vMem> <icos vMem>".format(sys.argv[0]))
    print("Where each argument is a text file with each vMem on a new line")
    sys.exit(1)

files = sys.argv[1:]
functions = [sigmoid, weird, invcosh]

vMems = []
slopes = []
offsets = []
lastY = -1

for i in range(len(files)):
    vMem = []
    slope = []
    offset = []
    with open(files[i]) as vMemFile:
        for line in vMemFile.readlines():
            line = line.strip()
            if line:
                x = float(line)
                y = functions[i](x)
                vMem.append(x)
                if len(vMem) > 1:
                    dx = (y - lastY)/(vMem[-1] - vMem[-2])
                    slope.append(dx)
                    offset.append(getOffset(x, y, dx))
                lastY = y
    slope.append(slope[-1])
    offset.append(offset[-1])
    vMems.append(vMem)
    slopes.append(slope)
    offsets.append(offset)

for i in range(len(vMems)):
    printFloatArray(vMems[i])
    printFloatArray(offsets[i])
    printFloatArray(slopes[i])
