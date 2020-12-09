#include "shell_command_utils.h"
#include "shell_config.h"

/* ************************************************************************** */

// prints all registered commands
void shell_help(int argc, char **argv) {
    sh_println("-----------------------------------------------");
    print_command_list();
    sh_println("-----------------------------------------------");
}

/* -------------------------------------------------------------------------- */

void shell_arg_test(int argc, char **argv) {
    sh_println("-----------------------------------------------");
    sh_println("SHELL ARG PARSING TEST UTILITY");
    if (argc == 1) {
        sh_println("This command has no special arguments.");
        sh_println("It is designed to test the TuneOS shell's arg parsing.");
        sh_println("Use it like this:");
        sh_println("\"$ test command arg1 arg2 arg3\"");
        sh_println("");
        sh_println("To get this response:");
        sh_println("Received 4 arguments for test command");
        sh_println("1 - \"command\" [len:7]");
        sh_println("2 - \"arg1\" [len:4]");
        sh_println("3 - \"arg2\" [len:4]");
        sh_println("4 - \"arg3\" [len:4]");
    } else {
        printf("Received %d arguments for test command\r\n", argc - 1);

        // Prints: <argNum> - "<string>" [len:<length>]
        for (uint8_t i = 1; i < argc; i++) {
            // printf("%u - \"%s\" [len:%u]\r\n", i, argv[i], str_len(argv[i]));
            printf("%u - \"", i);
            sh_print(argv[i]);
            printf("\" [len:%u]\r\n", (uint16_t)strlen(argv[i]));
        }
    }
    sh_println("-----------------------------------------------");
}

/* -------------------------------------------------------------------------- */

// JSON object definitions

void shell_version(int argc, char **argv) {
    sh_println("");
    printf("Chitin v%s", SHELL_VERSION);
    sh_println("");
    printf("Compiled on %s at %s", __DATE__, __TIME__);
    sh_println("");
}
