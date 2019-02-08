Homework 03
===========

Activity 01
==
1) Using the template provided by the class website, an IF statement checks if the first argument is "-h"; if found, the program will return a message for syntax help. I used another IF statement to check if an argument is provided. If a number is provided as the first argument, it will use that number as the rotation number. If no number is provided, the rotation number is defaulted to 13.

2) I created the source set to resemble the following syntax: [abc...xyzABC...XYZ]. I did this by declaring variables $LOWERCASE and $UPPERCASE. I concatenated these by using echo.

3) I constructed the target set to contain 26 lowercase letters at the front and 26 uppercase letters appended to the rear. I started by only focusing on the lowercase letters. I rotated the string by the inputted amount, $ROT, by cutting the string in half at the $ROT bit. I stored the two halves as $FIRSTLOWER and $LASTLOWER. I then concatenated them (in their reverse order) using echo and saving the string as $TOTALLOWER. I then used a normal "echo" and "tr" pipeline to create an uppercase version of $TOTALLOWER, called $TOTALUPPER. The source set then echoed the $TOTALLOWER and $TOTALUPPER as a concatenated string. This would allow the "tr" command to function properly (with lowercase being rotated with only lowercase letters, and vice-versa).

4) The source set echoed the normal [abc...xyzABC...XYZ], while the target set echoed a rotated version of this (while keeping the 26 lowercase letters at the anterior end and the uppercase letters at the posterior). These were both inputted into the "tr" command at the bottom of the script -- essentially creating the translation parameters for whatever string is passed to the command.

Activity 02
==
1) I parsed the command line arguments by using a while loop that looped while there were arguments. I used the shift command after each loop to pop off the 1st argument after it was processed by a case statement. In order to correctly grab the "-d" argument and the proceeding delimeter, I placed a shift within that same case. I saved the necessary variables as DELIM (saving the delimiter) and BOOL (to be used at the end of my program to decide what to execute).

2) To remove comments I used sed to search for the DELIM and I replaced it and everything after it with nothing.

3) I removed empty lines by using sed to find an instance where a whitespace was at the beginning of a line and it contained only spaces. Then it deleted the line.

4) Depending on the values for DELIM and BOOl, which depended on the command line options, one of two sed operations would be implemented. If the "-W" argument was passed, empty lines would not be deleted.

Activity 03
==
1) I parsed the command line argumens by using a while loop that looped while there were arguments. I used the shift command after each loop to pop off the 1st argument after it was processed by a case statement. In order to correctly grab "-c"'s proceeding argument and "-s"'s proceeding argument, a shift command needed to be placed within those respective case statements. I saved the proceeding arguments as CITY and STATE respectively to be used later on in the script.

2) I curled the appropriate URL, and used grep to search the HTML. I noticed that the only appropriate zip codes were wrapped in "/"s, so I used that in a first grep, then I outputted those numbers by themselves without the "/"s.

3) The only time the state is necessary to filter is within the URL. That was quite simple -- just appending the state name to the URL followed by a "/". However, multi-word states had issues, so I checked those URLs and I noticed there are "%20"s where spaces are in the URL. So I used command substitution to replace all spaces with a "%20" in the state name. Filtering by city was similar to how I filtered for zip codes. I searched for "/CITY/" because I noticed that city names were surrounded by "/"s. This made it much more simple. I thought New York, New York would be an issue, but their HTML had "/NY/" in the HTML to account for the state name.

