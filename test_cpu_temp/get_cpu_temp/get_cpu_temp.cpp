#include <stdio.h>
#include <stdlib.h>
 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
 
#define TEMP_PATH "/sys/class/thermal/thermal_zone0/temp"

bool get_cpu_temp(double & temp)
{
    bool ok = false;

    char buf[32];
    int fd = open(TEMP_PATH, O_RDONLY);
    if (fd >= 0)
    {
        if (read(fd, buf, sizeof(buf)) > 0)
        {
            temp = atoi(buf) / 1000.0;
            ok = true;
        }
        else
            fprintf(stderr, "read temp file FAILED\n");

        int n = close(fd);
        if (n != 0)
        {
            fprintf(stderr, "close temp file FAILED");
            ok = false;
        }
    }
    else
        fprintf(stderr, "open temp file FAILED\n");
    
    return ok;
}
