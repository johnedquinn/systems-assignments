# Homework 07

## Activity 1: Map Library

1. Briefly describe what memory you allocated in `entry_create` and what memory
   you deallocated in `entry_delete`. How did you handle the `recursive` flag?
	- I allocated memory to a pointer to Entry. Within entry I used stdrup for the key and if the type was a STRING, I used stdrup to add memory for the Value.
	- For the `entry_delete` function I created a base case to return if the Entry was NULL. I then called a recursive case (if true) to `entry_delete` the Entry that was next. Then I deleted the allocated memory from Key, from Value (if STRING), and from the pointer to the Entry itself.

2. Briefly describe what memory you allocated in `map_create` and what memory
   you deallocated in `map_delete`. How did you handle the internal entries?
	- I first malloced enough memory to store the Map itself. Then I calloced enough space for the Buckets; I decided to use calloc in this case so that all its entries would be NULL, and therefore its next pointer would also be NULL.
	- In `map_delete` I recursively deleted the entries in each bucket using `entry_delete`. Then I deallocated the memory from the buckets, and then I deallocated the memory used for the Map itself.

3. Briefly describe what memory you allocated, copied, and deallocated in
   `map_resize`. When is this function called and what exactly does it do to
   grow the map?
	- For `map_resize` I allocated enough space for a new buckets array to store the appropriate number of buckets. I then went through each bucket, and grabbed each Entry. With one Entry at a time, I re-determined (using hashing) what bucket (in the new buckets array) the Entry should be placed in, and I inserted it at the front of the linked list there. Upon moving all Entries to the new buckets array, I deallocated the old array of buckets and set the Map's buckets to the new buckets array. I made sure to set the new capacity.
	- This function is called when the `load_factor` of the Map is surpassed. The function grows the map by creating a new array of buckets (larger than the original) to store a larger capacity.

4. Briefly describe how your `map_insert` function works and analyze its **time
   complexity** and **space complexity** in terms of **Big-O notation** (both
   average and worst case).
	- The `map_insert` function uses the search function to check if an Entry with the same Key exists. If so, it goes to that Entry address and updates the Entry. If not, it goes to the appropriate bucket index and inserts at the front of the linked list.
	- The function uses search (which is O(1)). The insert (since it inserts at the beginning of the linked list) is constant time also.
	- The space complexity is O(n).

5. Briefly describe how your `map_search` function works and analyze its **time
   complexity** and **space complexity** in terms of **Big-O notation** (both
   average and worst case).
	- Using the hash table that we created with the `load_factor`, the time complexity should be approximately O(1). The `load_factor` ensures that there should be approximately one element per bucket and therefore the search should be O(1).
	- The space complexity for search is O(1).

6. Briefly describe how your `map_remove` function works and analyze its **time
   complexity** and **space complexity** in terms of Big-O notation (both
   average and worst case).
	- The `map_remove` function creates two pointers, goes to the correct bucket index, and traverses the singly-linked list to find the Entry. If found, the prev Entry will point to the current Entry's next Entry. Then the current Entry will be removed using `entry_delete`.
	- The time complexity for this should still be approximately O(1) because the hash tables makes sure that there is no need to traverse through long lists.
	- The space complexity is also O(1) because two pointers are created, a constant amount.
   
## Activity 2: Freq Utility

1. Based on your experiments, what is the overall trend in terms of **time**
   and **space** as the number of items increases for the different **load
   factors**?

    Are the results surprising to you? Explain why or why not.
    
2. There is no such thing as a **perfect data structure**. Compare this **hash
   table** to the **AVL tree** discussed in your data structures class. What
   are the advantages and disadvantages of both? If you had to use one as the
   underlying data structure for a **map**, which one would you choose and why?

    **Note**: If you are not currently in the data structures class, you can
    simply compare your **hash table** to any other **binary search tree** you
    are familiar with such as a **red-black tree**.
