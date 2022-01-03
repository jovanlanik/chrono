// Chronograph
// Copyright (c) 2019 Jovan Lanik

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define COLOR_ONE "\033[31m"
#define COLOR_TWO "\033[34m"
#define COLOR_OFF "\033[0m"

char top[] = " _________________________________ ";
char bottom[] = "\\_________________________________/";
char left[6][2] = {"/", "|", "|", "|", "|", "|"};
char right[6][2] = {"\\", "|", "|", "|", "|", "|"};
char largeDigit[5][6] = {" aaa ", "f   b", "fgggb", "e   c", "edddc"};
char smallDigit[3][4] = {" a ", "fgb", "edc"};
int table[7][10] = {
	{1, 0, 1, 1, 0, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 0, 0, 1, 1, 1},
	{1, 1, 0, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 1, 1, 0, 1, 1, 0, 1, 0},
	{1, 0, 1, 0, 0, 0, 1, 0, 1, 0},
	{1, 0, 0, 0, 1, 1, 1, 0, 1, 1},
	{0, 0, 1, 1, 1, 1, 1, 0, 1, 1}
};
char days[7][4] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
char separator[] = "  ** ";

void replaceChar(char *string, char old, char new) {
	for(int i = 0; string[i] != '\0'; ++i)
		if(string[i] == old) string[i] = new;
	return;
}

void getLargeNumRow(char *string, int num, int row) {
	strcpy(string, largeDigit[row]);
	for(int i = 0; i < 7; ++i) {
		if(table[i][num]) {
			if(i == 0 || i == 3 || i == 6)
				replaceChar(string, 'a'+i, '_');
			else
				replaceChar(string, 'a'+i, '|');
		}
		else replaceChar(string, 'a'+i, ' ');
	}
	return;
}


void getSmallNumRow(char *string, int num, int row)
{
	strcpy(string, smallDigit[row]);
	for(int i = 0; i < 7; ++i) {
		if(table[i][num]) {
			if(i == 0 || i == 3 || i == 6)
				replaceChar(string, 'a'+i, '_');
			else
				replaceChar(string, 'a'+i, '|');
		}
		else replaceChar(string, 'a'+i, ' ');
	}
	return;
}

int main(int argc, char *argv[]) {
	int digits[8];
	char string[6];
	time_t secs = time(NULL);
	struct tm date = *localtime(&secs);

	digits[0] = date.tm_hour/10;
	digits[1] = date.tm_hour%10;
	digits[2] = date.tm_min/10;
	digits[3] = date.tm_min%10;
	digits[4] = date.tm_sec/10;
	digits[5] = date.tm_sec%10;
	digits[6] = date.tm_mday/10;
	digits[7] = date.tm_mday%10;

	getSmallNumRow(string, digits[6], 0);

	printf(COLOR_TWO"%s\n%s"COLOR_OFF"       "COLOR_ONE"24H"COLOR_OFF"     "COLOR_ONE"%s"COLOR_OFF"        %s",
		top, left[0], days[date.tm_wday], string);

	getSmallNumRow(string, digits[7], 0);
	printf("%s "COLOR_TWO"%s"COLOR_OFF"\n", string, right[0]);
	for(int i = 0; i < 5; ++i) {
		printf(COLOR_TWO"%s"COLOR_OFF, left[i+1]);
		for(int n = 0; n < 4; ++n) {
			if(n == 2) printf("%c ", separator[i]);
			getLargeNumRow(string, digits[n], i);
			printf("%s ", string);
		}
		if(i < 2) {
			getSmallNumRow(string, digits[6], i+1);
			printf("%s", string);
			getSmallNumRow(string, digits[7], i+1);
			printf("%s", string);
		}
		else {
			getSmallNumRow(string, digits[4], i-2);
			printf("%s", string);
			getSmallNumRow(string, digits[5], i-2);
			printf("%s", string);
		}
		printf(" "COLOR_TWO"%s"COLOR_OFF"\n", right[i+1]);
	}
	printf(COLOR_TWO"%s"COLOR_OFF"\n\n", bottom);
	return 0;
}
