// Chronograph
// Copyright (c) 2022 Jovan Lanik

// Argument Parsing

#define VERSION_INFO "Chronograph - Display time and date in the terminal"
#define AUTHOR_EMAIL "jox969@gmail.com"

typedef enum {
	AUTO,
	ALWAYS,
	NEVER
} auto_arg_t;

void showUsage(char *name);
void showHelp(char *name);
void parseOptions(int argc, char *argv[]);

