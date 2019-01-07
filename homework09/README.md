Homework 09
===========

1. As discussed in class, working with **system calls** can be tricky because
   unlike most normal functions, they can fail.  For each of the following
   scenarios involving `doit`, identify which **system calls** would fail (if
   any) and described you handled that situation:

    - No arguments passed to `doit`.

    - `$EDITOR` environmental variable is not set.

    - User has run out of processes.

    - `$EDITOR` program is not found.

    - Temporary file is deleted before moving files.

    - Destination path is not writable.

2. As described in the project write-up, the **parent** is doing most of the
   work in `timeit` since it `forks`, `times`, and `waits` for the **child**
   (and possibly kills it), while the child simply calls `exec`.  To distribute
   the work more evenly, **Bill** proposes the following change:

    > Have the **child** set an `alarm` that goes off after the specified
    > `timeout`.  In the signal handler for the `alarm`, simply call `exit`, to
    > terminate the **child**.  This way, the **parent** just needs to `wait`
    > and doesn't need to perform a `kill` (since the **child** will terminate
    > itself after the `timeout`).

    Is this a good idea?  Explain why or why not.
