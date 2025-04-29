#!/bin/bash

echo "===== ulimit (user limits) ====="
echo "ulimit -n (open files): $(ulimit -n)"
echo "ulimit -u (max user processes): $(ulimit -u)"
echo "ulimit -v (virtual memory): $(ulimit -v)"
echo "ulimit -f (file size): $(ulimit -f)"
echo "ulimit -t (CPU time): $(ulimit -t)"

echo ""
echo "===== cgroup limits ====="

# CPU quota
CPU_QUOTA=$(cat /sys/fs/cgroup/cpu.max 2>/dev/null || echo "N/A")
echo "CPU max (cgroup): $CPU_QUOTA"

# Memory limit
MEM_LIMIT=$(cat /sys/fs/cgroup/memory.max 2>/dev/null || echo "N/A")
echo "Memory max (cgroup): $MEM_LIMIT"

# Number of PIDs (processes)
PIDS_LIMIT=$(cat /sys/fs/cgroup/pids.max 2>/dev/null || echo "N/A")
echo "PIDs max (cgroup): $PIDS_LIMIT"
