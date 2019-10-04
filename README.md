# DiscreteMathmatics_pa1 (Group 6)
Solve Puzzles with SMT Solver
==================================
We used SMT-solver Z3 to solve these puzzles. When we write program for each of the following three puzzles, that programs automatically finds solutions using the Z3 SMT solver.
# 1. Puzzle1. Sudoku
 In Sudoku*, there is a variant of Sudoku which has a 9x9 grid with nine 3x3 sub-grids, each cell that has a number in 1 to 9 and certain cells that contain asterisk sign ( * ) with unique one value in 1 to 9. 
##### -Input : The input should be a file written in 9x9 grid and consist of numbers between 1 to 9, sign ‘ ? ’ and ‘ * ’. 
* Numbers from 1 to 9 in one column cannot be duplicated.
* Numbers from 1 to 9 in one row cannot be duplicated.
* Numbers from 1 to 9 cannot be duplicated for nine 3x3 grids.
* The numbers cannot be duplicated between ＇＊＇characters.
* Unknown cells should be filled with a ‘?’ character.
* Every cells should be separated with a space bar character.

##### Ex) 
    gcc sudoku.c -o sudoku
    ./sudoku
    Please enter a file name : (enter the filename)
##### inputfile example
    ? 2 ? 5 ? * ? 9 ?
    8 ? ? 2 ? 3 ? ? 6
    ? 3 ? ? 6 ? * 7 ?
    * ? ? ? * ? 6 ? ?
    5 4 ? ? ? ? ? 1 9
    ? ? 2 ? ? ? 7 ? ?
    ? 9 * ? 3 ? ? 8 ?
    2 ? ? 8 ? 4 ? * 7
    ? 1 ? 9 ? 7 ? 6 ?

##### -Output : Output of this program is grid filled by number. If it has any solution of the input file, it prints out one of the answers that satisfy the conditions. If it has no solution or the input file has any error, it prints out ‘No solution’.
##### Output Example
    Solution found..
    6 2 1 5 7 8 3 9 4
    8 7 9 2 4 3 1 5 6
    4 3 5 1 6 9 2 7 8
    1 8 7 4 9 5 6 2 3
    5 4 3 7 2 6 8 1 9
    9 6 2 3 8 1 7 4 5
    7 9 4 6 3 2 5 8 1
    2 5 6 8 1 4 9 3 7
    3 1 8 9 5 7 4 6 2


# 2. Puzzle2. Fill-a-Pix
##### It is a program that makes the sum of cells around clue number and those around clue number become the value of clue number.
##### -Input : Two conditions must be observed when input is entered.
* Input should be read as standard input.
* The size of the input should not be greater than 1000 * 1000
* Each cell must be clue number or not.
* ? : no clue number
* 0-9 : a clue number

Enter values one by one on the keyboard and press “ctrl+D” when you are done.
##### EX) 
    gcc fill_a_Pix.c – fillaPix => build
    ./fillaPix
##### Standard input Example (You have to enter this in person)
    ? ? ? 3 ? 
    2 ? ? ? ?
    ? ? 4 ? ?

##### -Output : Output is printed in black(1) or white(0) and if there is no solution then print out “No solution”. If there are multiple solution, print out a maximum of five solutions.
##### Output Example
    0 0 0 0 1
    1 0 0 1 1
    0 1 1 1 0
    
    1 0 0 1 0
    0 0 1 1 0
    1 0 1 1 0
    
    1 0 0 0 1
    0 0 1 1 0
    1 0 1 1 0
    
    0 0 0 0 1
    0 1 0 1 1
    0 1 1 0 0 
    
    0 0 0 0 1
    1 1 1 1 0 
    0 0 1 0 0


# 3. Puzzle3. Numbrix
##### Numbrix is a logic puzzle that fills in the blanks of a given grid(N by M). The number entered in grid is 1 to NxM. The completed grid is connected by a line in order from the smallest to the largest.
##### -Input : The input is a given grid has several numbers. There are two conditions for input file.
* The size of the input should not be greater than 100 * 100.
* Enter ? when no number given.

##### Ex) 
    gcc numbrix.c -o numbrix
    ./numbrix input
##### Inputfile Example
    ?   ?   ?   ?   ?   ?
    ?   ?  20  13   ?   ?
    ?  26   ?   ?   9   ?
    ?  25   ?   ?  10   ?
    ?   ?  23  36   ?   ?
    ?   ?   ?   ?   ?   ?

##### -Output : Output of this program is a grid filled by number. If there is no valid result for given input, the output shows ‘No Solution’.
##### Output Example
    17  16  15  14   7   6
    18  19  20  13   8   5
    27  26  21  12   9   4
    28  25  22  11  10   3
    29  24  23  36  35   2
    30  31  32  33  34   1


# Makefile
Three files were grouped into a single makefile.

* Execute three programs (sudoku, fill a pix, numbrix)
   : $ make exe
    
* remove the object files and formulas
   : $ make clean
    
##### Ex)
    $ make exe
    ./makefile.sh
    
    1) Sudoku
    ________________________
    
    Please enter a file name : input1
    
    Solution found..
    6 2 1 5 7 8 3 9 4
    8 7 9 2 4 3 1 5 6
    4 3 5 1 6 9 2 7 8
    1 8 7 4 9 5 6 2 3
    5 4 3 7 2 6 8 1 9
    9 6 2 3 8 1 7 4 5
    7 9 4 6 3 2 5 8 1
    2 5 6 8 1 4 9 3 7
    3 1 8 9 5 7 4 6 2
    
    ________________________
    
    2) Fill A Pix
    ________________________
    enter input text
    if you finish to enter, press ctrl + d
    
    ? ? ? 3 ?
    2 ? ? ? ?
    ? ? 4 ? ?
    
    0 0 0 0 1
    1 0 0 1 1
    0 1 1 1 0
    
    1 0 0 1 0
    0 0 1 1 0
    1 0 1 1 0
    
    1 0 0 0 1
    0 0 1 1 0
    1 0 1 1 0
    
    0 0 0 0 1
    0 1 0 1 1
    0 1 1 0 0
    
    0 0 0 0 1
    1 1 1 1 0
    0 0 1 0 0
    
    ________________________
    
    3) Numbrix
    ________________________
    0  0  0  0  0  0
    0  0 20 13  0  0
    0 26  0  0  9  0
    0 25  0  0 10  0
    0  0 23 36  0  0
    0  0  0  0  0  0
    sat
    17 18 29 14  5  6
    16 19 20 13  8  7
    27 26 21 12  9 30
    28 25 22 11 10 31
    2 24 23 36 35 34
    3  4  1 15 32 33
    
***
    
# Group member
21400636 Lim Yechan

21500388 An Jane

21500706 Jee Sungmin

21600062 Kim Miso

21800147 Kim Youyoung

21800294 Park Suah
