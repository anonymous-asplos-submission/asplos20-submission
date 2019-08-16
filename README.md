# Cross-Failure Bug Detection in Persistent Memory Programs
This is the source code for ASPLOS2020 submission #21

The project was originally named as PMRace, and now renamed as XFDetector. Therefore, the names of function interface and its internal data structures begin with PMRace.

## System Requirement
-Intel Xeon-scalable 2nd Gen (Cascade Lake)<br/>
-Intel DC Persistent Memory (App Direct Mode and mounted as DAX)<br/>
-Linux 18.04<br/>

## Usage
To run the test, run the script in the pmrace directory.
For example, run "pmrace/runHashMapTx.sh" to run hashmap_tx workload test.

