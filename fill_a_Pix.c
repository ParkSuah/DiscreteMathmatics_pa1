#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char* line = NULL;
	char buf[128];
	int matrix[1000][1000];
	size_t len=0;
	int length = 0, height = 0, width = 0, n = 0,bdnum=0, count = 0, done = 0,num=0,count_fin=0;
	char c;

	while (getline(&line, &len, stdin) != EOF) {
		length = strlen(line);
		width = 0;
		for (int i = 0; i < length; i++) {
			if (line[i] == '?') {
				matrix[height][width++] = 0;
			}
			else if (line[i] >= 48 && line[i] <= 57) {
				n = line[i] - '0';
				matrix[height][width++] = n;
			}
			else if (line[i] == '\n') {
				height++;
			}
			else {
				continue;
			}
		}
	}

	FILE* fp = fopen("formula", "w");
	FILE* fp0 = fopen("formula_set", "w");

	int x, y;
	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			fprintf(fp, "(declare-const a%d%d Int)\n", y, x);
			fprintf(fp0, "(declare-const a%d%d Int)\n", y, x);
		}
	}
	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			fprintf(fp, "(assert (and (<= a%d%d 1) (>= a%d%d 0)))\n", y, x, y, x);
			fprintf(fp0, "(assert (and (<= a%d%d 1) (>= a%d%d 0)))\n", y, x, y, x);
		}
	}

	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			if (matrix[y][x] >= 1 && matrix[y][x] <= 9) {
				fprintf(fp, "(assert(= (+ ");
				fprintf(fp0, "(assert(= (+ ");

				for (int b = y - 1; b <= y + 1; b++) {
					for (int a = x - 1; a <= x + 1; a++) {
						if (b >= 0 && b < height && a >= 0 && a < width) {
							fprintf(fp, "a%d%d ", b, a);
							fprintf(fp0, "a%d%d ", b, a);
						}
					}
				}
				fprintf(fp, ") %d))\n", matrix[y][x]);
				fprintf(fp0, ") %d))\n", matrix[y][x]);
			}
		}   //9개의 범위 안에서 더한 값이 그 숫자여야 한다.
	}

	fprintf(fp, "(check-sat)\n(get-model)\n");
	fclose(fp);
	fclose(fp0);

	int i, j, k;
	char b[128];
	char s[128];
	char t[128];
	int board[height][width];
	int board1[height][width];

	FILE* fp3 = popen("z3 formula", "r");
	fscanf(fp3, "%s", buf); //sat
	if (strcmp(buf, "sat") != 0) {
		printf("No Solution.\n");
		pclose(fp3);
		return -1;
	}

	fscanf(fp3, "%s", b);

	for (k = 0; k < width * height; k++) {
		fscanf(fp3, "%s %s %s %s %s", b, s, b, b, t);
		i = s[1] - '0';
		j = s[2] - '0';

		if (strcmp(t, "0)") == 0) {
			board[i][j] = 0;
		}

		if (strcmp(t, "1)") == 0) {
			board[i][j] = 1;
		}
	}
	printf("\n");
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			printf("%d ", board[i][j]);
		}
		printf("\n");
	}
	pclose(fp3);

	y = 0, x = 0;
	int a = 0, d = 0;

	while (count < 4) {
		done = 0;
		for (; y < height; y++) {
			for (; x < width; x++) {
				if (matrix[y][x] >= 1 && matrix[y][x] <= 9) {
					if (count_fin == 0)
					{
						d = y - 1;
						a = x - 1;
					}
					for (d; d <= y + 1; d++) {
						for (a; a <= x + 1; a++) {
							if (d >= 0 && d < height && a >= 0 && a < width) {
								count_fin++;

								if (board[d][a] == 1) {   //1이면 0으로 바꾸기
									done = 1;
									bdnum = 1;

									if (a == x + 1 && d != y + 1) {
										d++;
										a = x - 1;
									}
									else if (a == x + 1 && d == y + 1) {
										count_fin = 0;
										break;
									}
									else {
										a++;
										break;
									}
								}


								if (board[d][a] == 0) {  //0이면 1로 바꾸기
									bdnum = 0;
									done = 1;
									if (a == x + 1 && d != y + 1) {
										d++;
										a = x - 1;
									}
									else if (a == x + 1 && d == y + 1) {
										count_fin = 0;
										break;
									}
									else {
										a++;
										break;
									}
								}



							}  //if 셀의 범위 조건

							if (a == x + 1)
							{
								a = x - 1;
								break;
							}


						}//for문 a
						if (done == 1)
							break;
						if (d == y + 1)
						{
							count_fin = 0;
							break;
						}

					} //for문 d
				} //if(matrix[y][x]>48 && matrix[y][x]<=57)의 끝
				if (done == 1) {
					if (x == width - 1 && count_fin == 0) {
						y++;
						x = 0;
					}
					else if (count_fin == 0) {
						x++;
					}

					break;
				}
				if (x == width - 1) {
					x = 0;
					break;
				}
			} //두번째 for문 끝 x
			if (done == 1)
				break;

		}  //첫 for문 끝 y

		if ((y == height && x == width) || (y == height && x == 00)) {
			break;
		}

		FILE* fp5 = fopen("formula_set", "r");
		FILE* fp2 = fopen("a_formula", "w");
		while (1) {
			c = fgetc(fp5);
			if (!feof(fp5))
				fputc(c, fp2);
			else break;
		}
		if (bdnum == 1) {
			fprintf(fp2, "(assert(= a%d%d 0)) \n", d, a);
			fprintf(fp2, "(check-sat)\n(get-model)\n");
			fclose(fp2);
			fclose(fp5);
		}
		if (bdnum == 0) {
			fprintf(fp2, "(assert(= a%d%d 1)) \n", d, a);
			fprintf(fp2, "(check-sat)\n(get-model)\n");
			fclose(fp2);
			fclose(fp5);
		}

		FILE* fp4 = popen("z3 a_formula", "r");
		fscanf(fp4, "%s", buf);
		if (strcmp(buf, "sat") != 0) {
			pclose(fp4);
			num++;
			continue;
		}
		fscanf(fp4, "%s", b);
		for (k = 0; k < width * height; k++) {
			fscanf(fp4, "%s %s %s %s %s", b, s, b, b, t);
			i = s[1] - '0';
			j = s[2] - '0';

			if (strcmp(t, "0)") == 0) {
				board1[i][j] = 0;
			}

			if (strcmp(t, "1)") == 0) {
				board1[i][j] = 1;
			}
		}
		printf("\n");
		for (i = 0; i < height; i++) {
			for (j = 0; j < width; j++) {
				printf("%d ", board1[i][j]);
			}
			printf("\n");
		}
		pclose(fp4);
		count++;
		num++;
	}//while문의 끝
} //main의 끝
