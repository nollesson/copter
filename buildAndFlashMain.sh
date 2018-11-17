#!/bin/sh
bazel build -c opt --config=arduino :main
mkdir -p stage
avr-objcopy -O ihex -R .eeprom bazel-bin/main stage/output.hex
avrdude -C toolchains/avrdude.conf -v -patmega328p -carduino -P/dev/ttyACM1 -b115200 -Uflash:w:stage/output.hex:i
