#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE * fp1 = fopen("formula", "w");//출력물
    char buf[128];
    char input[9][9]; //std input
    int c;
    int k = 0;
    int a[9][9] ; // coordinate
    int ast[9][2]; // asterisk coordinate



    char file_name[128];
    printf("Please enter a file name : ");
    scanf("%s", file_name);


    FILE * fp2 = fopen(file_name, "r");

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
                fscanf(fp2, "%s", buf);
                fprintf(fp1, "(declare-const a%d%d Int)\n", i, j);
                fprintf(fp1, "(assert (and (>= a%d%d 1) (<= a%d%d 9)))\n", i,j,i,j); // 1~9 range

                if(strcmp(buf, "*") == 0){
                        ast[k][0] = i;
                        ast[k][1] = j;
                        k++;
                }


                else if(strcmp(buf, "?") != 0){
                           fprintf(fp1, "(assert (= a%d%d %d))\n", i, j, atoi(buf));
                        }
                }

        }
        printf("\n");


   //asterisk constraints
   fprintf(fp1, "(assert (distinct ");
   for(int i = 0; i < k; i++){
        fprintf(fp1, "a%d%d ", ast[i][0], ast[i][1]);
   }
   fprintf(fp1, "))\n\n");

   //row constraints
   for(int i = 0; i < 9; i++){
        fprintf(fp1,"(assert (distinct ");
        for(int j = 0; j < 9; j++){
                fprintf(fp1, "a%d%d ", i, j);
        }
        fprintf(fp1, "))\n");
   }
   fprintf(fp1, "\n");
   //column constraints
   for(int i = 0; i < 9; i++){
        fprintf(fp1, "(assert (distinct ");
        for(int j = 0; j < 9; j++){
                fprintf(fp1, "a%d%d ", j, i);
        }
        fprintf(fp1, "))\n");
   }
   fprintf(fp1, "\n");

   //3x3 subgrid constraint
   for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
                fprintf(fp1, "(assert (distinct ");
                for(int ii = 0; ii < 3; ii++){
                        for(int jj = 0; jj < 3; jj++){
                                fprintf(fp1, "a%d%d ", ii+(3*i), jj+(3*j));
                        }
                }
                fprintf(fp1, "))\n");
        }
   }
   fprintf(fp1, "\n");

   fprintf(fp1, "(check-sat)\n");
   fprintf(fp1, "(get-model)\n");
   fclose(fp1);


   FILE * fp3 = popen("z3 formula", "r");
   fscanf(fp3 , "%s", buf); //sat

   if(strcmp(buf,"sat") != 0){

      printf("No Solution.\n");
      return -1;
   }



   fscanf(fp3 , "%s", buf); //model

   int x,y;

   while(1){
        if(strcmp(buf, ")") == 0)
                break;
        fscanf(fp3, "%s ", buf); //define-fun

        fscanf(fp3, "%s ", buf); //a coordinate
        x = buf[1] - '0';
        y = buf[2] - '0';

        fscanf(fp3, "%s ", buf); // ()

        fscanf(fp3, "%s ", buf); // type

        fscanf(fp3, "%s \n", buf); //value
        a[x][y] = buf[0] - '0';

   }

   pclose(fp3);

   printf("Solution found..\n");

   for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
                printf("%d ", a[i][j]);
        }
        printf("\n");
   }
   return 0;
}
