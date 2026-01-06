/*
Read temperature from DS18B20 sensor, convert to °F and
write to STDOUT in JSON format.
See https://github.com/HankB/DS18B20-to-JSON/blob/main/README.md
for more detail.

Command line arguments
    ds18B20 handle. Any of the values matching '/sys/bus/w1/devices/28*'

Build using
   gcc -Wall -o ds18b20_to_json ds18b20_to_json.c
   gcc -D TEST -Wall -o ds18b20_to_json ds18b20_to_json.c
*/

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static const uint id_length = 15; // typical 28-3c01b607c935

#if defined TEST
static const char *sensor_path = "./test/"; // for testing
#else
static const char *sensor_path = "/sys/bus/w1/devices/"; // actual path
#endif

static const char *sensor_temp = "/temperature"; // file name 

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
    uint buf_len = strlen(sensor_path) + id_length + strlen(sensor_temp) + 1;
    char *path_buf = malloc(buf_len);
    if (0 == path_buf)
    {
        fprintf(stderr, "can't malloc() memory\n");
        exit(ENOMEM);
    }
    path_buf[0] = 0; // null termiante empty string
    strncpy(path_buf, sensor_path, strlen(sensor_path));
    strncat(path_buf, argv[1], id_length);
    strncat(path_buf, sensor_temp, strlen(sensor_temp));

    FILE *f = fopen(path_buf, "r"); // open for read

    if (0 == f)
    {
        perror(path_buf);
        free(path_buf);
        return errno;
    }
    free(path_buf);

    uint raw_val;
    int rc = fscanf(f, "%d", &raw_val);
    fclose(f);

    if (1 != rc)
    {
        fprintf(stderr, "Can't read all values: %d\n", rc);
        return -1;
    }

    printf("{\"t\":%lld, \"temp\":%.2f, \"device\":\"DS18B20\", \"DS18B20_ID\":\"%s\"}", (long long)time(0), (float)raw_val * 9 / 5000 + 32, argv[1]);

    exit(0);
}
