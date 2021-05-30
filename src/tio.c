#include <unistd.h>
#include <termios.h>
#include <signal.h>

static struct termios backup_tio_settings;

void backup_tio()
{
    tcgetattr(STDIN_FILENO, &backup_tio_settings);
}

void set_tio()
{
    struct termios new_tio;

    new_tio = backup_tio_settings;
    new_tio.c_lflag &= (~ICANON & ~ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
}

void restore_tio()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &backup_tio_settings);
}