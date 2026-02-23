# DSA_HashTableProject

## Overall Description 
This C++ code is a custom hash table without using any built-in hash table functions. It's implimented using open addressing with some linear probing. For example, if both an apple and banana were at an index of 5, and 6 was empty, the coliding key would be moved to 6. I went this route due to it being simple to implement, and gets around having to use linked lists. 

The hash function used is called a polynomial rolling hash, converting string keys into indexes in the table. It works by using each character in the string towards the hashvalue variable and then multiplying that by 31, spreading it across the table, it it then modulo'd by the table's size to keep the hash value within the table.

The Runtime complexity has an average and best case of 0(1), since more often than not, most instances of putting a key into the table results in no collision, keeping that low time. The worst case is 0(n), this may occur when several collisions occur, and most of the table is used, causing the linear probing to have to search most of the table. 

This segways nicely into the current limitations with the code, as it's simplicity does work quite well for small datasets suck as the example provided in the project guidelines, it's efficiency is not up to par when possible larger datasets are considered. The linear probing method can cause clustering with more data, leading to more freqeunt collisions and increasing the runtime. Another instance of these shortcomings for larger datasets is the lazy deletion method, as it could drag the code's performances when dealing with those possible larger datasets. 

## AI Assistance
Overall, the code was mostly hand-written using the starter C++ code provided. AI was used to help with syntax errors, mainly refortmating the starter code without the optional, that didn't function in the version of c++ I used to build the code. It also assisted in helping format the functionality of the menu, comapared to my intial hard-coded keys, and implementing the togglable debug mode.

## User Guide
The MAIN.cpp file included in the github is all the code, no extra imports or plugins needed, just a C++ complier, could even just copy the code from the file from text alone and copy it into another .cpp file if you so choose.

When you run the code, you'll be greeted with the following main menu:
 ===== Behold the Hash Table =====
        1. Insert (PUT)
        2. Search (GET)
        3. Remove
        4. Print Table
        5. Exit
        6. Toggle Debug Mode
        Enter choice:

You access each of these options by inserting the cooresponding number in the "enter choice:" line.
Option 1 is the Insert/put function. When first entering 1, you'll be greated with "enter key:", this is where you type the name of the table index you want. After pressing enter, you'll be given "Enter value:" where you then enter the cooresponding value you want with the key. Then after pressing enter again, you'll be taken back to the main menu.

Option 2 is the search or get function. When entering 2, you'll get the prompt "enter key:" like option 1, only this time you just enter in the key you're looking for. If it exists, you'll be given it's associated value. If it doesn't exist, you'll be given the error message "key not found" as it returns to the main menu.

Option 3 is the remove function, when entering 3, you'll get "enter key to be removed:", similar to 1 and 2. Just enter the key name to be removed and press enter!. You'll receive the same error as 2 if the key doesnt exist.

Option 4 is the table print. When entering 4, you'll be given a text display something like this:
0.empty
1.empty
2.empty
3.empty
4.empty
5.empty
6.empty
7.empty
8.apple -> 10
9.empty
10.empty
11.empty
12.empty
13.empty
14.empty
15.empty
16.empty

depending on your window size, you may need to scroll to see the full table.

Option 5 exits the code and cancels the runtime. Nothing more to it.

Option 6 toggles the debug mode. When doing the previous operations (besides 5), there will be additional print messages indicating when an action is being performed. To cancel the debug mode, just enter 6 at the main menu again.


## Non-Trivial Test Cases

1. Collision Handling Test
   Put APPLE 10, PUT PLEAP 20, PUT LAPEL 30, PRINT TABLE.

   When the debug mode is active, this will demonstrate how the function handles collisions and properly fixes them with linear probing.

2. Resizing Test
   PUT apple 1, PUT banana 2, PUT grape 3, PUT orange 4, PUT mango 5, PUT lemon 6, PUT lime 7, PUT peach 8, PUT cherry 9, PUT plum 10,  PUT pear 11, PUT kiwi 12, PUT melon 13, PUT berry 14

   once the table reaches 13 in this scenario, the table will resize up from 17 to 34, and will properly describe this when the debug mode is on, but will be imediately noticable if the table is printed. 
