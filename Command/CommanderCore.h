#pragma once

#ifndef COMMANDER_MAX_OPTIONS
#define COMMANDER_MAX_OPTIONS 32
#endif

#ifndef COMMANDER_MAX_ARGS
#define COMMANDER_MAX_ARGS 32
#endif

struct command;
typedef void (*command_callback_t)(struct command* self);

typedef struct {
	int optional_arg;
	int required_arg;
	char* argname;
	char* large;
	const char* small;
	const char* large_with_arg;
	const char* description;
	command_callback_t cb;
} command_option_t;


typedef struct command {
	void* data;
	const char* usage;
	const char* arg;
	const char* name;
	const char* version;
	int option_count;
	command_option_t options[COMMANDER_MAX_OPTIONS];
	int argc;
	char* argv[COMMANDER_MAX_ARGS];
	char** nargv;
} command_t;

void command_init(command_t* self, const char* name, const char* version);

void command_free(command_t* self);

void command_help(command_t* self);

void command_option(command_t* self, const char* small, const char* large, const char* desc, command_callback_t cb);

void command_parse(command_t* self, int argc, char** argv);