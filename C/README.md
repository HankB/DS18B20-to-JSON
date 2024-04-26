# DS18B20 to JSON in C

## Requirements

* use `raspi-config` to emable 1-wire interface.
* Install `WiringPi` (is really needed?)
* Build tools (`build-essential`)

## Build

```text
   gcc -Wall -o ds18b20_to_json ds18b20_to_json.c
```

## Usage

```text
ds18b20_to_json [device ID, required]
ds18b20_to_json 28-3c01b607e46
```
