Homework 05
===========

1) To create the password combinations, I receursively called a permutations function to create every permutation of the alphabet for a certain length. To filter all the combinations to correctly identify the matching passwords, I created a sha1sum() function that hashed a passed string. Using this function within a smash() function, I performed the hash on every permutation and scanned the hashes file to see if there was a match. Then, if there was a match, I saved the matching permutation to a list. To handle processing on multiple cores, I used the multiprocessing package and the pool function. I used the number of specified cores as a parameter. Then I used the functools library to create a new function called subsmash that contained constant parameters of hashes, length, and alphabet. I created a list of prefixes to pass to the subsmash function. I verified that the code was working properly by performing the doc tests, running the code and checking my results alongside the results given by the Sakai page.

2)
| Processes   | Time          |
| 1           | 4m28.703s     |
| 2           | 2m11.319s     |
| 4           | 1m6.032s      |
| 8           | 36.899s       |

3) A more complex alphabet would make a password more difficult to brute-force. This is because adding more characters to the alphabet causes an exponential increase.
