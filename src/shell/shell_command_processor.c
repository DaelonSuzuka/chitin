#include "shell_command_processor.h"
#include "serial_port.h"
#include "shell.h"
#include <string.h>

/* ************************************************************************** */

// returns an initialized shell_args_t object
shell_args_t new_args(void) {
    shell_args_t args;
    memset(&args, 0, sizeof(shell_args_t));

    return args;
}

/* ************************************************************************** */

shell_command_t commandList[10] = {0};
uint8_t number_of_commands = 0;

uint8_t calculate_number_of_commands(void) { return number_of_commands; }

void register_command(shell_program_t program, const char *command) {
    commandList[number_of_commands].program = program;
    commandList[number_of_commands].command = command;
    number_of_commands++;
}

// Print all registered shell commands
void print_command_list(void) {
    for (uint8_t i = 0; i < calculate_number_of_commands(); i++) {
        println(commandList[i].command);
    }
}

/* -------------------------------------------------------------------------- */

extern void shell_help(int argc, char **argv);
extern void shell_arg_test(int argc, char **argv);
extern void shell_version(int argc, char **argv);

void command_processer_init(void) {
    register_command(shell_help, "help"); //
    register_command(shell_arg_test, "test"); //
    register_command(shell_version, "version"); //
}

/* ************************************************************************** */

// returns the index in list whose command matches the given string
int8_t find_command_in_list(char *string) {
    for (uint8_t i = 0; i < calculate_number_of_commands(); i++) {
        // If string matches one on the list
        if (!strcmp(string, commandList[i].command)) {
            return i;
        }
    }
    return -1;
}

// parses a line's buffer into a shell_args_t object
shell_args_t parse_shell_line(shell_line_t *line) {
    shell_args_t args = new_args();

    char *token = strtok(&line->buffer[0], " ");
    while (token != NULL && args.argc < CONFIG_SHELL_MAX_COMMAND_ARGS) {
        args.argv[args.argc++] = token;
        token = strtok(NULL, " ");
    }

    return args;
}

int8_t process_shell_command(shell_line_t *line) {
    shell_args_t args = parse_shell_line(line);

    // figure out which command matches the received string
    int8_t command = find_command_in_list(args.argv[0]);

    // if we found a valid command, execute it
    if (command != -1) {
        commandList[command].program(args.argc, args.argv);

        return 0;
    }
    return -1;
}