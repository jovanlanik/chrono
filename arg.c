// Chronograph
// Copyright (c) 2022 Jovan Lanik

// Argument Parsing

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>

#include "arg.h"

char *arg_name = NULL;
auto_arg_t arg_color = AUTO;

static const char *optstr = "-c::hV";

void showUsage(char *name) {
	printf("Usage: %s\n", name);
}

void showHelp(char *name) {
	puts(VERSION_INFO);
	showUsage(name);
	puts(
		"\n"
		"\t-c, --color[=ARG]\tARG is 'auto', 'always' or 'never'\n"
		"\t-h, --help\t\tdisplay this help and exit\n"
		"\t-V, --version\t\tdisplay version information and exit\n"
		"\nReport bugs to <" AUTHOR_EMAIL ">."
	);
}

void parseOptions(int argc, char *argv[]) {
	arg_name = argv[0];
	char opt = 0;
	const struct option options[] = {
		{ .name = "color", .val = 'c', .has_arg = optional_argument },
		{ .name = "help", .val = 'h' },
		{ .name = "version", .val = 'V' },
		{ 0, 0, 0, 0 }
	};
	while((opt = getopt_long(argc, argv, optstr, options, NULL)) != -1) {
		switch(opt) {
			case 'c':
				if(optarg == 0 || strcmp(optarg, "always") == 0) arg_color = ALWAYS;
				else if(strcmp(optarg, "auto") == 0) arg_color = AUTO;
				else if(strcmp(optarg, "never") == 0) arg_color = NEVER;
				break;
			case 'h':
				showHelp(arg_name);
				exit(EXIT_SUCCESS);
			case 'V':
				puts(VERSION_INFO);
				exit(EXIT_SUCCESS);
			case '?':
				exit(EXIT_FAILURE);
		}
	}
	return;
}

