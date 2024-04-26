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

int main(int argc, char** argv)
{
    printf("hello world\n");
}