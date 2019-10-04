#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
   int numbrix[100][100];
   int height = 1, width = 1;
   int i, j;
   int n, m;
   int heit = 0;
   int wid = 1;      //real width
   char z;

   FILE* file = fopen(argv[1], "r");
   if (file == 0) {
      printf("Could not open file\n");
   }

   char temp[300];
   while (fgets(temp, sizeof(temp), file)) {           // count hcnt -> height
      heit++;
   }
   fseek(file, 0, SEEK_SET);

   z = getc(file);
   for (j = 1; j <= heit; j++) {
      width = 1;
      for (i = 1; ; i++) {
         if (z == 32) z = getc(file);
         else if (z >= 48 && z <= 57) {    // 1 <= z <= 9일경우에 (assert (ayx = z)) //////////////////////////:
            n = z - '0';
            z = getc(file);
            if (z >= 48 && z <= 57) {  // 또 숫자면 십의 자리 숫자인 것이다.
               m = z - '0';
               numbrix[height][width] = n * 10 + m;
               printf("%2d ", numbrix[height][width]);
               z = getc(file);
               width++;
            }

            else if (z == 32) {        // " "인 경우이다.
               numbrix[height][width] = n;
               z = getc(file);
               printf("%2d ", numbrix[height][width]);
               width++;
            }
         }

         else if (z == '?') {     // 받은 문자가 "?"일 경우 "0"를 넣기.
            numbrix[height][width] = 0;
            printf("%2d ", numbrix[height][width]);
            width++;
            z = getc(file);
         }

         else if (z == '\n') { // 받은 문자가 "\n"일 경우에 height 높이고 다음문자로 넘어가기.
            height++;
            z = getc(file);
            wid = width - 1;
            printf("\n");
            break;
         }
      }
      wid = width - 1;
   }
   fclose(file);

   //  x= wid;
   //  y= heit

   FILE* fp = fopen("formula", "w");
   int x, y;

   // declare-const
   for (y = 1; y <= heit; y++)
      for (x = 1; x <= wid; x++)
         fprintf(fp, "(declare-const a%d%d Int)\n", y, x);
   for (y = 1; y <= heit; y++) {
      for (x = 1; x <= wid; x++) {
         if (numbrix[y][x] != 0)
            fprintf(fp, "(assert (= a%d%d %d))\n", y, x, numbrix[y][x]);
      }
   }
   // value scope is 0 < n <= 36
   for (y = 1; y <= heit; y++)
      for (x = 1; x <= wid; x++)
         fprintf(fp, "(assert (and (< 0 a%d%d) (<= a%d%d %d)))\n", y, x, y, x, heit * wid);

   // 서로 다른 값이어야 한다.
   fprintf(fp, "(assert (distinct");
   for (y = 1; y <= heit; y++)
      for (x = 1; x <= wid; x++)
         fprintf(fp, " a%d%d", y, x);
   fprintf(fp, "))\n");


   //수정한부분 (1, 36 이외에 -> 해결_중앙, x축, y축) _ 검사받기
   //주위에 n-1이 있다.
   // n값이 1, 36이 아닐 경우 주위에 n-1 혹은 n+1이 반드시 있다.
   for (y = 2; y <= heit - 1; y++) {
      for (x = 2; x <= wid - 1; x++) {
         fprintf(fp, "(assert (and (or");
         fprintf(fp, " (= (- a%d%d 1) a%d%d)", y, x, y - 1, x);
         fprintf(fp, " (= (- a%d%d 1) a%d%d)", y, x, y + 1, x);
         fprintf(fp, " (= (- a%d%d 1) a%d%d)", y, x, y, x - 1);
         fprintf(fp, " (= (- a%d%d 1) a%d%d)", y, x, y, x + 1);
         fprintf(fp, ") (or");
         fprintf(fp, " (= (+ a%d%d 1) a%d%d)", y, x, y - 1, x);
         fprintf(fp, " (= (+ a%d%d 1) a%d%d)", y, x, y + 1, x);
         fprintf(fp, " (= (+ a%d%d 1) a%d%d)", y, x, y, x - 1);
         fprintf(fp, " (= (+ a%d%d 1) a%d%d)", y, x, y, x + 1);
         fprintf(fp, ")))\n");
      }
   }

   // x축일 경우
   for (y = 1; y <= heit; y = heit) {
      for (x = 2; x <= wid - 1; x++) {
         if (y == 1) {
            fprintf(fp, "(assert (and (or");
            fprintf(fp, " (= (- a%d%d 1) a%d%d)", y, x, y, x - 1);
            fprintf(fp, " (= (- a%d%d 1) a%d%d)", y, x, y + 1, x);
            fprintf(fp, " (= (- a%d%d 1) a%d%d)", y, x, y, x + 1);
            fprintf(fp, ") (or");
            fprintf(fp, " (= (+ a%d%d 1) a%d%d)", y, x, y, x - 1);
            fprintf(fp, " (= (+ a%d%d 1) a%d%d)", y, x, y + 1, x);
            fprintf(fp, " (= (+ a%d%d 1) a%d%d)", y, x, y, x + 1);
            fprintf(fp, ")))\n");
         }
         else if (y == heit) {
            fprintf(fp, "(assert (and (or");
            fprintf(fp, " (= (- a%d%d 1) a%d%d)", y, x, y - 1, x);
            fprintf(fp, " (= (- a%d%d 1) a%d%d)", y, x, y, x + 1);
            fprintf(fp, " (= (- a%d%d 1) a%d%d)", y, x, y, x - 1);
            fprintf(fp, ") (or");
            fprintf(fp, " (= (+ a%d%d 1) a%d%d)", y, x, y - 1, x);
            fprintf(fp, " (= (+ a%d%d 1) a%d%d)", y, x, y, x + 1);
            fprintf(fp, " (= (+ a%d%d 1) a%d%d)", y, x, y, x - 1);
            fprintf(fp, ")))\n");
         }
      }
      if (x == wid && y == heit)
         break;
   }

   // y축일 경우
      for (x = 1; x <= wid; x = wid) {
         for (y = 2; y <= heit - 1; y++) {
         if (x == 1) {
            fprintf(fp, "(assert (and (or");
            fprintf(fp, " (= (- a%d%d 1) a%d%d)", y, x, y, x + 1);
            fprintf(fp, " (= (- a%d%d 1) a%d%d)", y, x, y + 1, x);
            fprintf(fp, " (= (- a%d%d 1) a%d%d)", y, x, y - 1, x);
            fprintf(fp, ") (or");
            fprintf(fp, " (= (+ a%d%d 1) a%d%d)", y, x, y, x + 1);
            fprintf(fp, " (= (+ a%d%d 1) a%d%d)", y, x, y + 1, x);
            fprintf(fp, " (= (+ a%d%d 1) a%d%d)", y, x, y - 1, x);
            fprintf(fp, ")))\n");
         }
         else if (x == wid) {
            fprintf(fp, "(assert (and (or");
            fprintf(fp, " (= (- a%d%d 1) a%d%d)", y, x, y, x - 1);
            fprintf(fp, " (= (- a%d%d 1) a%d%d)", y, x, y + 1, x);
            fprintf(fp, " (= (- a%d%d 1) a%d%d)", y, x, y - 1, x);
            fprintf(fp, ") (or");
            fprintf(fp, " (= (+ a%d%d 1) a%d%d)", y, x, y, x - 1);
            fprintf(fp, " (= (+ a%d%d 1) a%d%d)", y, x, y + 1, x);
            fprintf(fp, " (= (+ a%d%d 1) a%d%d)", y, x, y - 1, x);
            fprintf(fp, ")))\n");
         }
      }

      if (x == wid && y == heit)
         break;
   }


   // 코너일 경우
   for (y = 1; y <= heit; y = y+heit-1) {
      for (x = 1; x <= wid; x = x+wid-1) {
         if (x == y) {
            if (x == 1) {
               fprintf(fp, "(assert (and (or");
               fprintf(fp, " (= (- a%d%d 1) a%d%d)", y, x, y + 1, x);
               fprintf(fp, " (= (- a%d%d 1) a%d%d)", y, x, y, x + 1);
               fprintf(fp, ") (or");
               fprintf(fp, " (= (+ a%d%d 1) a%d%d)", y, x, y + 1, x);
               fprintf(fp, " (= (+ a%d%d 1) a%d%d)", y, x, y, x + 1);
               fprintf(fp, ")))\n");
            }
            else {
               fprintf(fp, "(assert (and (or");
               fprintf(fp, " (= (- a%d%d 1) a%d%d)", y, x, y - 1, x);
               fprintf(fp, " (= (- a%d%d 1) a%d%d)", y, x, y, x - 1);
               fprintf(fp, ") (or");
               fprintf(fp, " (= (+ a%d%d 1) a%d%d)", y, x, y - 1, x);
               fprintf(fp, " (= (+ a%d%d 1) a%d%d)", y, x, y, x - 1);
               fprintf(fp, ")))\n");
            }
         }
         else {
            if (x > y) {
               fprintf(fp, "(assert (and (or");
               fprintf(fp, " (= (- a%d%d 1) a%d%d)", y, x, y + 1, x);
               fprintf(fp, " (= (- a%d%d 1) a%d%d)", y, x, y, x - 1);
               fprintf(fp, ") (or");
               fprintf(fp, " (= (+ a%d%d 1) a%d%d)", y, x, y + 1, x);
               fprintf(fp, " (= (+ a%d%d 1) a%d%d)", y, x, y, x - 1);
               fprintf(fp, ")))\n");
            }
            else {
               fprintf(fp, "(assert (and (or");
               fprintf(fp, " (= (- a%d%d 1) a%d%d)", y, x, y - 1, x);
               fprintf(fp, " (= (- a%d%d 1) a%d%d)", y, x, y, x + 1);
               fprintf(fp, ") (or");
               fprintf(fp, " (= (+ a%d%d 1) a%d%d)", y, x, y - 1, x);
               fprintf(fp, " (= (+ a%d%d 1) a%d%d)", y, x, y, x + 1);
               fprintf(fp, ")))\n");
            }
         }
         if (x == wid)
            break;
      }
      if (x == wid && y == heit)
         break;
   }


   fprintf(fp, "(check-sat)\n(get-model)\n");
   fclose(fp);

   i = 0; j = 0;
   int k, temp2;
   char board[heit][wid];

   char temp1[10];
   char b[128];
   char s[128];
   char t[128];
   char buf[128];

   FILE* fpp = popen("z3 formula", "r");
   fscanf(fpp, "%s", buf);
   printf("%s\n", buf);

   if (strcmp(buf, "sat") != 0) {
      printf("No Solution.\n");
      pclose(fpp);
      return -1;
   }

   fscanf(fpp, "%s", b);

   for (k = 0; k < heit * wid; k++) {
      fscanf(fpp, "%s %s %s %s %s", b, s, b, b, t);
      i = s[1] - '0';
      j = s[2] - '0';

      int length = strlen(t);

      for (int i = 0; i < length - 1; i++) {
         temp1[i] = t[i];
      }
      temp1[length - 1] = '\0';
      temp2 = atoi(temp1);

      board[i][j] = temp2;
   }

   for (i = 1; i <= heit; i++) {
      for (j = 1; j <= wid; j++) {
         printf("%2d ", board[i][j]);
      }
      printf("\n");
   }

}
