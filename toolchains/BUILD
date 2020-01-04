load(":cc_toolchain_config.bzl", "cc_toolchain_config")

cc_toolchain_config(
    name = "avr8-gnu-toolchain-linux_x86_64"
)

cc_toolchain_suite(
    name = "arduino-toolchain",
    toolchains = {
        "avr": ":cc-compiler-avr-gcc",
    },
    visibility = ["//visibility:public"],
)

filegroup(name = "empty")

cc_toolchain(
    name = "cc-compiler-avr-gcc",
    all_files = ":empty",
    compiler_files = ":empty",
    dwp_files = ":empty",
    toolchain_config = ":avr8-gnu-toolchain-linux_x86_64",
    linker_files = ":empty",
    objcopy_files = ":empty",
    strip_files = ":empty",
    supports_param_files = 1,
    visibility = ["//visibility:public"],
)
