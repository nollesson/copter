cc_toolchain_suite(
    name = "arduino-toolchain",
    toolchains = {
        "avr|gcc": ":cc-compiler-avr-gcc",
    },
    visibility = ["//visibility:public"],
)

filegroup(name = "empty")

cc_toolchain(
    name = "cc-compiler-avr-gcc",
    all_files = ":empty",
    compiler_files = ":empty",
    cpu = "avr",
    dwp_files = ":empty",
    dynamic_runtime_libs = [":empty"],
    linker_files = ":empty",
    objcopy_files = ":empty",
    static_runtime_libs = [":empty"],
    strip_files = ":empty",
    supports_param_files = 1,
    visibility = ["//visibility:public"],
)
