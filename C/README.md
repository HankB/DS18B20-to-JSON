# DS18B20 to JSON in C

## Requirements

* use `raspi-config` to enable 1-wire interface.
* Install `WiringPi` (is really needed?)
* Build tools (`build-essential`)

## Status

* 2024-04-27 Initial coding complete, testing with disk file.
* 2024-04-27 Test on actual H/W not successful. Complete path of the temperature not implemented.

## Build

```text
gcc -Wall -o ds18b20_to_json ds18b20_to_json.c
```

## Usage

```text
ds18b20_to_json [device ID, required]
ds18b20_to_json 28-3c01b607e46
```

### Test

Add `-D TEST` to build command line to test with a local file.

```text
gcc -D TEST -Wall -o ds18b20_to_json ds18b20_to_json.c
```
