// Chronograph
// Copyright (c) 2022 Jovan Lanik

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "arg.h"

static bool color = false;
extern auto_arg_t arg_color;

const char top[] = " _________________________________ ";
const char bottom[] = "\\_________________________________/";
const char left[6][2] = {"/", "|", "|", "|", "|", "|"};
const char right[6][2] = {"\\", "|", "|", "|", "|", "|"};
const char largeDigit[][6] = {" aaa ", "f   b", "fgggb", "e   c", "edddc"};
const char smallDigit[][6] = {" a ", "fgb", "edc"};
const int table[7][10] = {
	{1, 0, 1, 1, 0, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 0, 0, 1, 1, 1},
	{1, 1, 0, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 1, 1, 0, 1, 1, 0, 1, 0},
	{1, 0, 1, 0, 0, 0, 1, 0, 1, 0},
	{1, 0, 0, 0, 1, 1, 1, 0, 1, 1},
	{0, 0, 1, 1, 1, 1, 1, 0, 1, 1},
};
const char days[7][4] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
const char separator[] = "  ** ";

static void replaceChar(char *string, char old, char new) {
	for(int i = 0; string[i] != '\0'; ++i)
		if(string[i] == old) string[i] = new;
	return;
}

static void getDigitNumRow(char *string, int num, int row, const char digit[][6]) {
	strcpy(string, digit[row]);
	for(int i = 0; i < 7; ++i) {
		if(table[i][num]) {
			if(i == 0 || i == 3 || i == 6)
				replaceChar(string, 'a'+i, '_');
			else replaceChar(string, 'a'+i, '|');
		}
		else replaceChar(string, 'a'+i, ' ');
	}
	return;
}

#define getLargeNumRow(s, n, r) getDigitNumRow(s, n, r, largeDigit)
#define getSmallNumRow(s, n, r) getDigitNumRow(s, n, r, smallDigit)

static void setColor(const char *s) { if(color) printf("\033[%sm", s); }
static void clearColor(void) { if(color) fputs("\033[m", stdout); }

int main(int argc, char *argv[]) {
	parseOptions(argc, argv);

	const char *t;
	if(arg_color == ALWAYS || (arg_color == AUTO && (t = getenv("TERM")) && strcmp(t, "dumb")))
		color = true;
	else color = false;

	time_t secs = time(NULL);
	struct tm date = *localtime(&secs);
	int digits[8];

	digits[0] = date.tm_hour / 10;
	digits[1] = date.tm_hour % 10;
	digits[2] = date.tm_min / 10;
	digits[3] = date.tm_min % 10;
	digits[4] = date.tm_sec / 10;
	digits[5] = date.tm_sec % 10;
	digits[6] = date.tm_mday / 10;
	digits[7] = date.tm_mday % 10;

	char string[6];

	getSmallNumRow(string, digits[6], 0);

	setColor("34");
	printf("%s\n%s", top, left[0]);
	clearColor();
	fputs("       ", stdout);
	setColor("31");
	fputs("24H", stdout);
	clearColor();
	fputs("     ", stdout);
	setColor("31");
	fputs(days[date.tm_wday], stdout);
	clearColor();
	printf("        %s", string);

	getSmallNumRow(string, digits[7], 0);

	printf("%s ", string);
	setColor("34");
	fputs(right[0], stdout);
	clearColor();
	putchar('\n');
	
	for(int i = 0; i < 5; ++i) {
		setColor("34");
		fputs(left[i+1], stdout);
		clearColor();
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
		putchar(' ');
		setColor("34");
		fputs(right[i+1], stdout);
		clearColor();
		putchar('\n');
	}
	setColor("34");
	fputs(bottom, stdout);
	clearColor();
	puts("\n");
	return 0;
}

