cc_binary(
    name = "FlashLed",
    srcs = ["FlashLed.cpp"],
)

cc_binary(
    name = "EchoSerial",
    srcs = ["EchoSerial.cpp"],
    deps = ["//Libraries/ArduinoCore"],
)

cc_binary(
    name = "RunPwm",
    srcs = ["RunPwm.cpp"],
    deps = ["//Libraries/ArduinoCore"],
)

cc_binary(
    name = "RunStepper",
    srcs = ["RunStepper.cpp"],
    deps = ["//Libraries/ArduinoCore"],
)

cc_binary(
    name = "EchoBluetooth",
    srcs = ["EchoBluetooth.cpp"],
    deps = ["//Libraries/ArduinoCore"],
)

cc_binary(
    name = "ScanTwiAddresses",
    srcs = ["ScanTwiAddresses.cpp"],
    deps = [
        "//Hal:Twi",
        "//Libraries/ArduinoCore",
    ],
)

cc_binary(
    name = "StreamSensor",
    srcs = ["StreamSensor.cpp"],
    deps = [
        "//Hal:Twi",
        "//Libraries/ArduinoCore",
    ],
)

