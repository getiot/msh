#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

static int skip = 2;

int command_ls()
{
    DIR *dp;
    struct dirent *ep;

    dp = opendir("./");

    if (dp != NULL) {
        int count = 0;

        while ((ep = readdir(dp))) {
            count++;
            if (count > skip) {
                puts(ep->d_name);
            }
        }
        closedir(dp);
    }
    else {
        perror("Couldn't open the directory");
    }

    return 0;
}