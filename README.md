# DS18B20-to-JSON

Read DS18B20 temperature sensor on a Raspberry Pi and output formatted as JSON.

## Motivation

I need to read two DS18B20 sensors connected to a Raspberry Pi and publish them using MQTT. This is going to be run on a Pi Zero W along with programs that will report values read from several other sensors. For this reason it uis desired to use a compiled executable rather than interpreted script to minimize CPU and RAM load.

## Background

TIL (Today I learned) that the 1 wire protocol implwementation (kernel or WiringPi?) does all of the work and it is only necessary to read a pseudo-file in the `/sys` filesystem to read temperature. Available sensors are also listed in the `/sys` filesystem.

```text
hbarta@nbw:~ $ ls -l /sys/bus/w1/devices
total 0
lrwxrwxrwx 1 root root 0 Apr 25 12:19 28-3c01b607c935 -> ../../../devices/w1_bus_master1/28-3c01b607c935
lrwxrwxrwx 1 root root 0 Apr 26 16:57 28-3c01b607e46b -> ../../../devices/w1_bus_master1/28-3c01b607e46b
lrwxrwxrwx 1 root root 0 Apr 26 16:57 w1_bus_master1 -> ../../../devices/w1_bus_master1
hbarta@nbw:~ $ cat /sys/devices/w1_bus_master1/28-*/temperature 
20500
20937
hbarta@nbw:~ $ 
```

This could be done using a shell script, but since `bash` does not do floating point (to convert milli-degrees C to °F), the whole thing might as well be written in a compiled language. This could be `C`, `C++`, `Rust` or `Go` (among the languages I have used.) The task is simple enough that I might code this in several languages just for the sake of comparison. Subdirectories will be created for the specific implementations and work will proceed there.

My development will be performed on a Pi 4B running the 32 bit variant of RpiOS and executables copied to a Pi 3B which has the sensors connected. The eventual target is a Pi Zero W.

The reason JSON is being dragged in is because the messages published to an MQTT broker are expected to be in JSON format and will look something like:

```text
{"t":1714171865, "temp":69.09,  "device":"DS18B20"}
```

Where `t` is a time stamp in `time_t` seconds.


## Status

* 2024-04-26 Plans
