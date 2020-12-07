#include "shell/shell.h"
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

static struct termios old, new1;
void init_termios(int echo) {
    tcgetattr(0, &old);      /* grab old terminal i/o settings */
    new1 = old;              /* make new settings same as old settings */
    new1.c_lflag &= ~ICANON; /* disable buffered i/o */
    new1.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
    tcsetattr(0, TCSANOW, &new1); /* use these new terminal i/o settings now */
}

void reset_termios(void) { tcsetattr(0, TCSANOW, &old); }

int main(void) {
    init_termios(0);

    shell_init();

    while (1) {
        // char currentChar = getchar();
        // shell_update(currentChar);
        shell_update();
    }

    reset_termios();
    return 0;
}