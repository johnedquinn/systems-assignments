Homework 07
===========

# Activity 2 - Questions

1. Describe how the `symbol` is stored in the `Node` **struct** by diagramming
   the memory layout of the following `Node` structure:

        Node *n = node_create('\n', 2, NULL, NULL);

    Be sure to indicate how much memory each `Node` structure occupies and how
    much is allocated for each attribute in the struct.
    
    1. Explain what the code `assert(n->string.letter == '\n')` would result in?
    
    1. Given that `symbol` is a **union** type, is it ever possible for both the
      `letter` and `string` of the symbol `\n` to co-exist (that is, the
      `string` doesn't clobber the `letter`)?
      
        **Hint**: Consider alternative architectures.

2. To construct the Huffman code, you had to utilize both a **priority queue**
   (aka. **min-heap**) and a **Huffman Tree**, both of which were binary trees.
   For the former, you used an **array** representation while for the later you
   used a **linked node** representation.  With this in mind, answer the
   following questions:

    1. Would it have been easier to implement the **priority queue** with a
      **linked node** representation?  Explain why this would be better or
      worse than the **array** representation.

    2. Would it have been easier to implement the **Huffman Tree** with an 
      **array** representation?  Explain why this would be better or worse 
      than the **linked node** representation.

3. Analyze the results of your experiements with you `huff.py` Python script.
   What sort of compression ratios were you able to achieve?  How does this
   compare to standard utilities such as `gzip`, `bzip2`, and `xz`?

    |        FILE        | OLD SIZE | NEW SIZE |   RATIO   |
    |--------------------|----------|----------|-----------|
    |     data/1342-0.txt|   5712512|   3238771|     56.70%|
    |      data/219-0.txt|   1866312|   1065343|     57.08%|
    |       data/84-0.txt|   3579736|   2005500|     56.02%|
    |        data/844.txt|   1139056|    672349|     59.03%|
    |       data/98-0.txt|   6298288|   3575868|     56.78%|
    |       data/data.txt|       328|       127|     38.72%|
    |      data/ideas.txt|      8360|      4934|     59.02%|