# DS18B20 to JSON in C

## Requirements

* use `raspi-config` to enable 1-wire interface.
* Build tools (`build-essential`)

## Status

* 2026-01-06 Fix segfault and working on 32 bit Pi, TEST works on 64 bit desktop.
* 2026-01-06 Builds on RPiOS Trixie (32 bit) and segfaults. Fix in progress.
* 2024-04-27 Initial coding complete, tested and working on actual H/W.

## Build

```text
gcc -Wall -o ds18b20_to_json ds18b20_to_json.c
```

## Usage

Identify connected sensors using:

```text
hbarta@nbw:~ $ ls -l /sys/bus/w1/devices/
total 0
lrwxrwxrwx 1 root root 0 Apr 25 12:19 28-3c01b607c935 -> ../../../devices/w1_bus_master1/28-3c01b607c935
lrwxrwxrwx 1 root root 0 Apr 26 16:57 28-3c01b607e46b -> ../../../devices/w1_bus_master1/28-3c01b607e46b
lrwxrwxrwx 1 root root 0 Apr 26 16:57 w1_bus_master1 -> ../../../devices/w1_bus_master1
hbarta@nbw:~ $ 
```

Sensor IDs here are `28-3c01b607c935` and `28-3c01b607e46b`. Temperature can be read from `/sys/bus/w1/devices/`\<sensor ID>`temperature`.

```text
hbarta@nbw:~ $ cat /sys/bus/w1/devices/28-3c01b607c935/temperature
20625
hbarta@nbw:~ $ 
```

Execute the program, passing the desired sensor ID.

```text
ds18b20_to_json [device ID, required]
ds18b20_to_json 28-3c01b607e46
```

### Test

Add `-D TEST` to build command line to test with a local file.

```text
gcc -D TEST -Wall -o ds18b20_to_json ds18b20_to_json.c
```
