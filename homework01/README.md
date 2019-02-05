Homework 01
===========

Activity 01
----------

| Command                               | Elapsed Time  |
|-------------------------------------- | ------------- |
| time cp -r /usr/share/pixmaps images  | 0.349 s       |
| time mv images/ pixmaps               | 0.005 s       |
| time mv pixmaps /tmp/jquinn13-pixmaps | 0.205 s       |
| time rm -r /tmp/jquinn13-pixmaps/     | 0.003 s       |

1) Using the mv command can be used for either renaming a file/directory or moving a file/directory to a new location. Renaming a file does not require the movement of information; the renaming function of “mv” merely changes the filename and does not alter the inode. The moving function of “mv” has to allocate space and copy the original file/directory; this function deletes the inode and creates a new one, therefore leading a longer elapsed time.

2) Removing a file deletes the inode, while moving a file deletes and creates a new inode. The latter operation has more operations to do, leading to a longer elapsed time. 

Activity 02
-----------

1) bc < math.txt

2) (bc < math.txt) > results.txt

3) (bc < math.txt) 2> /dev/null > results.txt

4) cat math.txt | bc

5) (bc < math.txt) 2> /dev/null | tee results.txt

6) Pipelines are more efficient because you can minimize the amount of processes to perform actions. For example, if you use find ~ -type f | xargs stat, the find process will minimize the number of files being processed before the other processes are used.


Activity 03
----------

1) grep "/sbin/nologin" /etc/passwd | wc -l

2) ps -A | grep "bash" | wc -l

3) du /etc 2> /dev/null | sort -rn | head -5

4) who | cut -d " " -f 1 | sort | uniq | wc -l


Activity 04
-----------

1)
	a) Cntrl-c makes the troll taunt again. Cntrl-z only stops it. kill $PID doesn't do anything.

	b) kill -9 $PID

2) 
	a) kill -9 $(ps x | grep /TROLL | cut -d ' ' -f 2)

	b) kill -9 $PID

3) kill -TERM $PID taunts me; kill -1 $PID gave me messages that weren't necessarily taunting; kill -10 $PID had cool green letters coming down screen; kill -12 $PID showed me starwars.



