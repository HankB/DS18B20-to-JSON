/*
Read temperature from DS18B20 sensor, convert to °F and
write to STDOUT in JSON format.
See https://github.com/HankB/DS18B20-to-JSON/blob/main/README.md
for more detail.

Command line arguments
    ds18B20 handle. Any of the values matching '/sys/bus/w1/devices/28*'

Build using
   gcc -Wall -o ds18b20_to_json ds18b20_to_json.c
*/

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

static const uint id_length = 15;           // typical 28-3c01b607c935
static const char *sensor_path = "./test/"; // for testing

void usage(char *progname, int error)
{
    fprintf(stderr, "Usage, %s [DS18B20 ID - required]\n", progname);
    exit(error);
}

int main(int argc, char **argv)
{
    if ((argc != 2) ||                  // DS18B20 ID provided?
        (strlen(argv[1]) != id_length)) // right length?
    {
        usage(argv[0], EINVAL);
    }

    // construct full file path
    uint buf_len = strlen(sensor_path)+id_length+1;
    char *path_buf = malloc(buf_len);
    if(path_buf == 0)
    {
        fprintf(stderr, "can't malloc() memory\n");
        exit(ENOMEM);
    }
    path_buf[0] = 0; // null termiante empty string
    strncpy(path_buf, sensor_path, buf_len);
    strncat(path_buf, argv[1], id_length);
    printf("\"%s\"\n", path_buf);
    exit(0);
}