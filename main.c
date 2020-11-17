#include "command_line.h"
#include "deps/argtable3//argtable3.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef COMMAND_VERSION_STRING
#define COMMAND_VERSION_STRING "0.0.1"
#endif

#pragma GCC diagnostic ignored "-Wunused-parameter"

struct arg_str *some_str;

void some_str_callback(int argc, char *argv[]) {
    if (some_str->count == 0) {
        printf("some-str flag empty\n");
        return;
    }
    printf("some-str flag value: %s\n", *some_str->sval);
}

command_handler *new_some_str_command() {
    command_handler *handler = calloc(1, sizeof(command_handler));
    if (handler == NULL) {
        return NULL;
    }
    handler->name = "some-str";
    handler->callback = some_str_callback;
    return handler;
}

int main(int argc, char *argv[]) {
    // default arg setup
    setup_args(COMMAND_VERSION_STRING);
    // custom arg setup
    some_str = arg_strn(NULL, "some-string", "<str>", 0, 1,
                                  "input a random string");

    // declare artable
    void *argtable[] = {some_str,
                        help,
                        version,
                        file,
                        output,
                        command_to_run,
                        end};

    // prepare arguments
    int response = parse_args(argc, argv, argtable);
    switch (response) {
        case 0:
            break;
        case -1:
            arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));
            printf("parse_args failed\n");
            return response;
        case -2: // this means --help was invoked
            return 0;
    }

    // handle help if no other cli arguments were given (aka binary invoked with
    // ./some-binary)
    if (argc == 1) {
        print_help(argv[0], argtable);
        arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));
        return 0;
    }
    // construct the command object
    command_object *pcmd = new_command_object(argc, argv);
    if (pcmd == NULL) {
        printf("failed to get command_object");
        goto EXIT;
    }

    load_command(pcmd, new_some_str_command());

    // END COMMAND INPUT PREPARATION
    int resp = execute(pcmd, (char *)*command_to_run->sval);
    if (resp != 0) {
        // TODO(bonedaddy): figure out if we should log this
        // printf("command run failed\n");
    }
EXIT:
    free_command_object(pcmd);
    arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));
    return resp;
}