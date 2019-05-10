# Homework 09

1. As discussed in class, working with **system calls** can be tricky because
   unlike most normal functions, they can fail.  For each of the following
   scenarios involving `moveit`, identify which **system calls** would fail (if
   any) and described you handled that situation:

    - No arguments passed to `moveit`.
    If there were no arguments, I woud fail the `rename` system call in the move_files() function. I also would not be able to pass what is at the index of argv[1], because nothing is there. I handled this situation by displaying a usage message and exiting the program if there were no arguments passed (or equally, argc == 1).

    - `$EDITOR` environmental variable is not set.
    I used the getenv() system call, and it returns NULL if the environmental variable is not found. Therefore, I checked if it returned NULL, and if so I defaulted the EDITOR to "vim", and if not I grabbed the environment variable that is stored.

    - User has run out of processes.
    In the edit_files() function, when I fork to create a new child process, I check if the fork was successful by checking the PID. If the PID < 0, then I know I must have gone over the limit allowed by the machine, so I printed an error message and returned false (the function returns a boolean). Then in my main(), if false is returned I unlink the temporary file, deallocated the string, and return with an EXIT_FAILURE.

    - `$EDITOR` program is not found.
    In the edit_files() function, I used the execlp() system call. If this system call were to fail (if the $EDITOR program is not found), then the system call returns a negative integer. Therefore, if a negative integer is received, it prints an error message and returns false. Then in main(), if false is received, it unlinks the temporary file, deallocates the string, and returns with an EXIT_FAILURE.

    - Temporary file is deleted before moving files.
    In the move_files() function, I used the fopen() system call. If the system call were to fail (maybe the temporary file was deleted), then the system call returns NULL. Therefore, if the program receives a NULL, it prints an error message and returns false. Then in main(), if false is received, it unlinks the temporary file, deallocates the string, and returns with an EXIT_FAILURE.

    - Destination path is not writable.
    In the move_files() function, I used the rename() function to rename the files. This system call returns a negative integer if it encounters an error. Therefore, if the program receives a negative integer, it closes the file and returns false. Then in main(), if it receives false, it unlinks the temporary file, deallocates the string, and returns with an EXIT_FAILURE.

2. As described in the project write-up, the **parent** is doing most of the
   work in `timeit` since it `forks`, `times`, and `waits` for the **child**
   (and possibly kills it), while the child simply calls `exec`.  To distribute
   the work more evenly, **Logan** proposes the following change:

    > Have the **child** set an `alarm` that goes off after the specified
    > `timeout`.  In the signal handler for the `alarm`, simply call `exit`, to
    > terminate the **child**.  This way, the **parent** just needs to `wait`
    > and doesn't need to perform a `kill` (since the **child** will terminate
    > itself after the `timeout`).

    Is this a good idea?  Explain why or why not.

    I wouldn't have the child set an alarm and perform the execution because the child would not be able to keep track of both things. It would be necessary for the child itself to fork and create another child (either one being the alarm-handler or the command executioner). In this case where our program is tasked with keeping a maximum time limit and performing one command execution, it is only necessary to have one child (where the parent keeps track of the time and the child runs the command).
