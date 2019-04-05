# Homework 08

## Strace Output 

### `search`
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 70.90    0.016047           3      5241           lstat
 17.78    0.004023           5       746           getdents
  5.53    0.001252           3       394        21 openat
  4.96    0.001122           3       375           close
  0.35    0.000079           3        30           brk
  0.23    0.000051           3        20           write
  0.08    0.000018           6         3           fstat
  0.07    0.000015           4         4           mprotect
  0.05    0.000011           1         8           mmap
  0.04    0.000008           8         1           munmap
  0.01    0.000003           3         1         1 ioctl
  0.01    0.000003           3         1           `arch_prctl`
  0.00    0.000000           0         1           read
  0.00    0.000000           0         2           open
  0.00    0.000000           0         1         1 access
  0.00    0.000000           0         1           execve
------ ----------- ----------- --------- --------- ----------------
100.00    0.022632                  6829        23 total

### `find`
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 36.93    0.007501           2      3264           fcntl
 18.53    0.003763           3      1409           close
 17.33    0.003520           5       746           getdents
 11.05    0.002245           3       767           newfstatat
  6.14    0.001247           3       395        21 openat
  4.49    0.000913           2       385           fstat
  2.65    0.000539           5       118           write
  1.10    0.000223           9        24        13 open
  0.58    0.000118           5        25           mmap
  0.36    0.000074           5        14           mprotect
  0.23    0.000046           5        10           read
  0.16    0.000033           4         9           brk
  0.13    0.000026           7         4           munmap
  0.05    0.000010           5         2         1 access
  0.05    0.000010           5         2         2 statfs
  0.04    0.000009           3         3         2 ioctl
  0.02    0.000005           5         1         1 stat
  0.02    0.000005           5         1           execve
  0.02    0.000005           5         1           fchdir
  0.02    0.000004           2         2           `rt_sigaction`
  0.01    0.000003           3         1           `rt_sigprocmask`
  0.01    0.000003           3         1           uname
  0.01    0.000003           3         1           getrlimit
  0.01    0.000003           3         1           `arch_prctl`
  0.01    0.000002           2         1           `set_tid_address`
  0.01    0.000002           2         1           `set_robust_list`
------ ----------- ----------- --------- --------- ----------------
100.00    0.020312                  7188        40 total

## Questions

1. Describe the differences you see between the number and type of system calls
   used by your utility as compared to the standard Unix program.
- With the ./bin/search, there were 16 unique system calls and overall 6829 system calls. With find, there were 26 unique system calls and 7188 total system calls. With the standard Unix program, the system calls seem to be more specific (they used calls such as `rt_sigaction` and `set_tid_address`) while ./bin/search used only the basic calls.

2. Did you notice anything surprising about the trace of your utility or the
   trace of the standard Unix program? Which implementations are faster or more
   efficient?  Explain.
- In terms of pure speed, it seems that the Unix standard program is a bit faster, although they use more calls and attract more errors. The calls it uses must access the data more efficiently. My program however uses less calls and attracts fewer errors, which may be because I used basic system calls.
