#include <stdio.h>
#include <signal.h>

#include "shell.h"
#include "tio.h"

int main()
{
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    backup_tio();
    set_tio();

    signal(SIGINT, sigint_handler);

    int ret = input_loop();
    restore_tio();

    return ret;
}