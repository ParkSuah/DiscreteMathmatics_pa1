# DiscreteMathmatics_pa1
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

###### Ex) 
    gcc sudoku.c -o sudoku
    ./sudoku
    Please enter a file name : (enter the filename.txt)
###### inputfile.txt example
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


# 2. Puzzle2. Fill-a-Pix
##### It is a program that makes the sum of cells around clue number and those around clue number become the value of clue number.
##### -Input : Two conditions must be observed when input is entered.
* Input should be read as standard input.
* The size of the input should not be greater than 1000 * 1000
* Each cell must be clue number or not.
* ? : no clue number
* 0-9 : a clue number

Enter values one by one on the keyboard and press “ctrl+D” when you are done.
###### EX) 
    gcc fill_a_Pix.c – fillaPix => build
    ./fillaPix
    ? ? ? 3 ? 
    2 ? ? ? ?
    ? ? 4 ? ?

##### -Output : Output is printed in black(1) or white(0) and if there is no solution then print out “No solution”. If there are multiple solution, print out a maximum of five solutions.

# 3. Puzzle3. Numbrix
##### Numbrix is a logic puzzle that fills in the blanks of a given grid(N by M). The number entered in grid is 1 to NxM. The completed grid is connected by a line in order from the smallest to the largest.
##### -Input : The input is a given grid has several numbers. There are two conditions for input file.
* The size of the input should not be greater than 100 * 100.
* Enter ? when no number given.

###### Ex) 
    gcc numbrix.c -o numbrix
    ./numbrix input.txt
###### inputfile.txt example
    ?   ?   ?   ?   ?   ?
    ?   ?  20  13   ?   ?
    ?  26   ?   ?   9   ?
    ?  25   ?   ?  10   ?
    ?   ?  23  36   ?   ?
    ?   ?   ?   ?   ?   ?

##### -Output : Output of this program is a grid filled by number. If there is no valid result for given input, the output shows ‘No Solution’.
