#!/bin/bash

# Workload
WORKLOAD=hashmap_atomic
# PM Image file
PMIMAGE=/mnt/pmem0/"$WORKLOAD"
TEST_ROOT="$PWD"/..



# Sizes of the workloads
TESTSIZES=(2)

for i in ${TESTSIZES[@]} ; do
	# Remove old pmimage and fifo files
	rm /mnt/pmem0/*
	rm /tmp/*fifo

	TIMING_OUT="$WORKLOAD"_time.txt
	echo "$WORKLOAD" size: "$i" >> $TIMING_OUT
	DEBUG_OUT="$WORKLOAD"_"$i"_debug.txt
	echo "$WORKLOAD" size: "$i" >> $DEBUG_OUT
	echo "runningTestSize $i"
	# Init the pmImage
	./../workloads/hashmap/data_store $WORKLOAD $PMIMAGE $i
	# Generate config file
	CONFIG_FILE="$WORKLOAD"_config_"$i".txt
	rm $CONFIG_FILE
	echo "PINTOOL_PATH $TEST_ROOT/pmrace/pintool/obj-intel64/pintool.so" >> $CONFIG_FILE
	echo "EXEC_PATH $TEST_ROOT/workloads/hashmap/data_store" >> $CONFIG_FILE
	echo "PM_IMAGE $PMIMAGE" >> $CONFIG_FILE
	echo "PRE_FAILURE_COMMAND $TEST_ROOT/workloads/hashmap/data_store $WORKLOAD $PMIMAGE $i" >> $CONFIG_FILE
	echo "POST_FAILURE_COMMAND $TEST_ROOT/workloads/hashmap/data_store $WORKLOAD $PMIMAGE 1" >> $CONFIG_FILE
	# Run realworkload
	# Start PMRace
	./build/app/pmrace $CONFIG_FILE >> $TIMING_OUT 2> $DEBUG_OUT &
	sleep 1
	pin -t "$TEST_ROOT"/pmrace/pintool/obj-intel64/pintool.so -t 1 -f 1 -- "$TEST_ROOT"/workloads/hashmap/data_store $WORKLOAD $PMIMAGE $i > /dev/null
	wait
done
