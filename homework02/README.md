Homework 02
===========

TASK 1
===========

1.
==
To first check if there were any arguments, I placed an IF statement at the beginning of my ".sh" file. If the number of arguments was equal to 0, then the program would output a message declaring the required syntax by the user. If there were more than 0 arguments, the program would perform the necessary operations.

2.
==
To handle multiple arguments, I created a FOR loop where variable "i" represented each argument. Then it would extract each argument at a time.

3.
==
To route the argument to the correct command, I used several cases while manipulating the asterick wildcard. I prefixed every possible file extension with the wildcard to ensure each argument was routed to the appropriate command.

4.
==
I inserted an if statement to make sure each extraction command worked properly.


TASK 2
===========

1.
==
I used the -r and -x flags within if statements to check the permissions of the file argument.

2.
==
I used the strings command to grab every string from the file argument, and I used its output in a FOR loop. This allowed me to loop through every string and save them to a variable.

3.
==
I created a variable with an initial value of 1, and the only possible way for it to change was if the program returned a token. If the program returned a token, I changed the variable to 0. At the end of the program, I made an IF statement to check the final value of the variable and outputted a sentence declaring if the argument file was cracked or not.

TASK 3
===========
I first used the command "nmap -Pn -p 9000-9999 xavier.h4x0r.space". I included the -Pn because the host was offline, and I included -p 9000-9999 to only choose ports within that range. It returned 3 ports to me.
I then curled all ports, but "curl http://xavier.h4x0r.space:9322" worked for me in a way. A troll told me that I needed to find my password which was contained in my lockbox (somewhere in pbui's directories). After scrolling through some of the lockboxes down to the leaf, I found that the lockbox executables were in the form "$NETID.lockbox".
I then searched for my lockbox using "find /escnfs/home/pbui/pub/oracle/lockboxes/ -name 'jquinn13.lockbox'". This returned to me the location of my lockbox which was "/escnfs/home/pbui/pub/oracle/lockboxes/7bcffc2d/7c32effb/fed52a8c/c5fd04c5/6837d3be/jquinn13.lockbox".
Using the crack.sh executable that we created in Task 2, I entered "./crack.sh /escnfs/home/pbui/pub/oracle/lockboxes/7bcffc2d/7c32effb/fed52a8c/c5fd04c5/6837d3be/jquinn13.lockbox" into the command line. It processed my command, and returned "Password is anF1aW5uMTMK\n Token    is 96689f98ce5e3207739ebc21ce9f7f270c822667".
I then remembered that the troll asked me to curl using my password: "curl http://xavier.h4x0r.space:9322/jquinn13/anF1aW5uMTMK". The troll verified my identity, and asked me to go to Slack and give the Bobbit my token with the following syntax: "!verify NETID TOKEN". The Bobbit then told me to deliver the code "d2RodmFhMTM9MTU0ODk5ODcxNw==" to the port 9803.
I used "curl http://xavier.h4x0r.space:9803" but it told me to contact the Oracle through a more primitive form of communication. I eventually tried "telnet xavier.h4x0r.space 9803" and I finally encountered the Oracle. I inputted my name and the secret code given to me by the Hobbit. Journey completed.

