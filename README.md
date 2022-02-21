# xv6-os-scheduler
CFS and SFJ Scheduler implementation for xv6 risc5 


# Features

## System call for changing scheduler

The following line represents the function call
```
void chsched(int scheduler_type);
```
Where ``scheduler_type`` can be
  - 0 for Shortest job first - Non-Preemptive 
  - 1 for Shortest job first - Preemptive
  - 2 for Completely fair scheduler


## Shortest job first

Features implementation of Shortest job first algorithm using next formula as prediction
```
Tau(i+1) = a * T(i) + (1 - a) * Tau(i)
```
Where Tau is predicted time while T is real time while that process had context(was running). Default value is 0.

Context will switch to next process once the running process is suspended(for example goes to sleep)

Preemptive and Non-Preemptive are different, preemptive will check for shortest job at every interrupt while non-preemptive will do so only when running process is suspended.

## Completely fair scheduler

Features implementation of Completely fair scheduler used in Linux 2.6

Process will get context for given time T, which is calculated by dividing time it spent as runnable without context and number of processes avaliable in scheduler. Once the time slice T runs out the process will lose his context and will be switched

## Load-Balancing

The implementation of load balancing is present in both SJF and CFS. The load-balancing will work if there are more than 2 cpu-s(cpu cores) and will balance across multiple cores. Load-Balancing works if there are no processes on given cpu(cpu core), it will search for cpu(cpu core) with most processes and will take that process. This way the number of cache misses is reduced but all cpu-s(cpu cores) will be working. 
