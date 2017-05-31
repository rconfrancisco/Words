# Words
*Sample programs to process words in a file*
<br>
The word program reads a file and printouts the 10 most frequent words.
<br> 
Usage: 
<br> 
./Word[options]
<br> 
-f filename - required
<br> 
-n words - default 10
<br> 
-h help this menu
The first and only parameter is how many words you wish to display.
<br>
The program reads each word, normalizes it, puts into a hash map (trie would be faster)
<br>
then use a MaxHeap (priority queue) to print sort numbers and print out the most frequent.
<br>
<tt>./Word -n 17 -f Words.txt
<br>
Will printout the 17 most frequent words found in the file Words.txt.
