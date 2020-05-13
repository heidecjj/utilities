#!/usr/bin/python

import matplotlib.pyplot as plt
import csv
import sys

numPlots = -1
numProcs = len(sys.argv) - 2

margin = 7

def makeVPlots(files):
	plotIndex = 0
	vPlots = [[] for i in range(numPlots)]
	for file in files:
		with open(file, 'r') as inputFile:
			print("Reading {}...".format(file.split('/')[-1]))
			plots = csv.reader(inputFile, delimiter=',')
			maxPlotIndex = 0
			for row in plots:
				if (maxPlotIndex == 0):
					maxPlotIndex = len(row)
				for i in range(1, maxPlotIndex):
					vPlots[plotIndex + i-1].append(float(row[i])) # skip the time for now
			plotIndex += maxPlotIndex - 1

	return vPlots


t = []


origFiles = [sys.argv[1]]
newFiles = sys.argv[2:]

# Sue me.
with open(origFiles[0], 'r') as timeFile:
	plots = csv.reader(timeFile, delimiter=',')
	for row in plots:
		if numPlots is -1:
			numPlots = len(row) - 1
		t.append(float(row[0]))

print("Reading in data for {} neurons from {} processor(s)...".format(numPlots, numProcs))

vPlotsOrig = makeVPlots(origFiles)
vPlotsNew = makeVPlots(newFiles)

for i in range(numPlots):
	plt.subplot(numPlots,1,i+1)
	plt.plot(t, vPlotsOrig[i], label="Original V{}".format(i))
	plt.plot(t, vPlotsNew[i], label="New V{}".format(i))

# for i in range(numPlots):
# 	plt.subplot(10,2,2*i+1)
# 	plt.plot(t, vPlotsOrig[i], label="Original V{}".format(i))
# 	plt.subplot(10,2,2*i+2)
# 	plt.plot(t, vPlotsNew[i], label="New V{}".format(i))

	#plt.legend()

minMargin = margin / 100.0
maxMargin = 1 - minMargin
plt.subplots_adjust(left=minMargin, right=maxMargin, top=maxMargin, bottom=minMargin)
plt.show();
