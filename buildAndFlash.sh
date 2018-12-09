#!/bin/sh
set -e
if [ "$#" -ne 1 ]; then
    echo "Usage: buildAndFlash.sh target"
    exit 1
fi
bazel build -c opt --config=arduino :"$1"
mkdir -p stage
avr-objcopy -O ihex -R .eeprom bazel-bin/"$1" stage/output.hex
avrdude -C toolchains/avrdude.conf -v -patmega328p -carduino -P/dev/ttyACM1 -b115200 -Uflash:w:stage/output.hex:i
