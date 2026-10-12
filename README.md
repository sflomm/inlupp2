# Inlupp 1
***
This is a README file for Assignement 1 of the IOOPM-course
## Running tests
***
Use the following terminal commands to run different tests:
1.  To run testfiles
```bash
# runs testfile for linked_list.c and linked_list_iterator.c
make linked_test 
# runs testfile for hash_table.c and hash_table_iterator.c
make hash_test
# runs both of the above
make test
# runs the freq_count file with hash_table_struct.h as input file
make freq
# to run all three
make all
```
2. To run the above through valgrind
```bash
make valgrind_list
make valgrind_hash
make valgrind
make valgrind_freq
```
3. To remove compiled files
```bash
make clean
```
## Pointers as keys or values
***
The hashtable implementation does not take ownership of keys and values that are some sort of pointer. Other fields of elem_t are owned by the hashtable.

## The ioopm_hash_table_remove function
***
The default return value of this function when it fails to remove an entry(can't find key) is the int 0. Do the following to check that an entry has been removed:
```bash
ioopm_hash_table_size(ht); // will be a value
ioopm_hash_table_remove(ht, key); // returns 0 if fail or if entry's value was 0
ioopm_hash_table_size(ht); // if successfull removal above, will be decreased by 1
```
## The freq_count.c file
***
Can be used to count occurences of words in a file, usage would look as such:
```bash
(compiled version of freq_count) (name of file to count words in)
```
## Coverage
***
We used gcov to collect coverage data.\
Use this make command:
```bash
make cov
```
Should get the following data:
| FILE          | Lines         |  Exec   | Cover   | Branch  | Taken |
| ------------- | ------------- | ------- | ------- | ------- | ----- |
| hash_table.c  | 73            | 73      | 100%    |    22   | 100%  |
| hash_table_iterator.c | 36    | 36      | 100%    |    12   | 100%  |

| FILE          | Lines         |  Exec   | Cover   | Branch  | Taken |
| ------------- | ------------- | ------- | ------- | ------- | ----- |
| linked_list.c  | 91           | 91      | 100%    |   16    | 100%  |
| linked_list_iterator.c | 27   | 27      | 100%    |   0     | ----- |

## Initial Profiling Results 
***
We used the profiling tool gprof, to see the results for each text file write the command "make freq_NAME". 
NAME is replaced with the desired text file to run (small, 1k, 10k or 16k).
### For each input, what are the top 3 functions?
***
small: cmp_freq_words, find_previous_entry, string_knr_hash\
1k: simple_knr_eq, find_previous_entry, string_knr_hash\
10k: simple_knr_eq, find_previous_entry, string_knr_hash\
16k: simple_knr_eq, cmp_freq_words, find_previous_entry
### For each input, are the top 3 functions in your code (that you have written), or is it in library functions?
***
We wrote the simple_knr_eq function and find_previous_entry, the rest was from the freq_count template.
### Are the top 3 functions in your code consistent across the inputs? Why? Why not?
***
* find_previous_entry was in top 3 for all the texts.\
Why? It needs to find the previous entry to search through the hash table. This function is used in our functions ioopm_hash_table_insert and ioopm_hash_table_lookup. 
* simple_knr_eq was number 1 for the texts 1k, 10k and 16k words and very close for the text small. It was the same for simple_knr_hash.\
Why? These functions are used to create the hash table and 
they are used everytime we call find_previous_entry.
* cmp_freq_words was called significantly more times for the texts small and 16k.\
Why? This is because the percentage of unique words are higher compared to the the texts 1k and 10k. For every unique word (key) this function is called. 
#### Text files - Amount of unique words and amount of each:
***
small: 27 words, one of each\
1k: 23 words, 38-48 of each\
10k: 199 words, 4-164 of each\
16k: 4370 words, 1-? of each (first 1000 is singles)\
(It wasn't possible to see the full list of words for 16k)
### Is there some kind of trend? (Possibly several)
***
Yes, which functions are called more depends on the relation between the total amount of words and amount of unique words. 
The function cmp_freq_words compares each unique word and checks the word's total frequency to put it at the correct placement in the ranked list. For example, the texts small and 1k have few unique words and therefore this function isn't called as much as for the texts 10k and 16k. The same goes for the function advance_iterator_state which needs to advance for every unique word and therefore is called more often for text files 10k and 16k.
### Do the results correspond with your expectations?
***
Yes. 
### Based on these results, do you see a way to make your program go faster?
***
We could implement a load factor implementation for the hash_table, which could increase the amount of buckets dynamically as the hash_table fills up. This would reduce the length of the linked lists in each bucket. This gets more complex and won't be too usefull for small texts.