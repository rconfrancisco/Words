# Words
*Sample programs to process words in a file*
<br>
The word program reads a file from standard in and printouts the 10 most frequent words.
<br>
The first and only parameter is how many words you wish to display.
<br>
The program reads each word, normalizes it, puts into a hash map (trie would be faster)
<br>
then use a MaxHeap (priority queue) to print sort numbers and print out the most frequent.
<br>
<tt>./Word 17 < Words.txt</tt> 
<br>
Will printout the 17 most frequent words.
