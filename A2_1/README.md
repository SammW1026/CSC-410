to run
gcc starwars.c
./starwars

gcc process_sums.c
./process_sums 100000000

gcc seq_sum.c
./seq_sum 100000000

task 2
After forking, the parent and all child processes are scheduled by the operating system.
The OS decides which process runs first, and that order can differ every time.
So the print statements may appear in different orders across runs.

