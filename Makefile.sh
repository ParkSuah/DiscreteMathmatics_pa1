echo "1) Sudoku"
echo "________________________"
echo ""

gcc sudoku.c -o sudoku
./sudoku

echo ""
echo "________________________"
echo ""

echo "2) Fill A Pix"
echo "________________________"
echo "enter input text"
echo "if you finish to enter, press ctrl + d"
echo ""

gcc fill_a_Pix.c -o fill_a_Pix
./fill_a_Pix

echo ""
echo "________________________"
echo ""
echo "3) Numbrix"
echo "________________________"

gcc numbrix.c -o numbrix
./numbrix input3.txt
