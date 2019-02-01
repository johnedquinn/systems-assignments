Homework 02
===========

TASK 1
===========

1.
===========
To first check if there were any arguments, I placed an IF statement at the beginning of my ".sh" file. If the number of arguments was equal to 0, then the program would output a message declaring the required syntax by the user. If there were more than 0 arguments, the program would perform the necessary operations.

2.
===========
To handle multiple arguments, I created a FOR loop where variable "i" represented each argument. Then it would extract each argument at a time.

3.
===========
To route the argument to the correct command, I used several cases while manipulating the asterick wildcard. I prefixed every possible file extension with the wildcard to ensure each argument was routed to the appropriate command.

4.
===========
I inserted an if statement to make sure each extraction command worked properly.


TASK 2
===========

1.
===========
I used the -r and -x flags within if statements to check the permissions of the file argument.

2.
===========
I used the strings command to grab every string from the file argument, and I used its output in a FOR loop. This allowed me to loop through every string and save them to a variable.

3.
===========
I created a variable with an initial value of 1, and the only possible way for it to change was if the program returned a token. If the program returned a token, I changed the variable to 0. At the end of the program, I made an IF statement to check the final value of the variable and outputted a sentence declaring if the argument file was cracked or not.

