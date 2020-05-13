#!/bin/sh

for SIM in "$@"
do
	SHORT=`echo $SIM | cut -c 5-`
	echo "Running ${SIM} unaccelerated"
	./$SIM -v 0 -i config100c5n10s.json -o out/out100c5n10s_${SHORT}.csv
	if [ -f "statistics.csv" ]; then
		mv statistics.csv out/stats_${SIM}.csv
	fi
	echo "Running ${SIM} accelerated"
	./$SIM -v 0 -i config100c5n10s.json -o out/out100c5n10s_${SHORT}_acc.csv -l
	if [ -f "statistics.csv" ]; then
		mv statistics.csv out/stats_${SIM}_acc.csv
	fi
done
