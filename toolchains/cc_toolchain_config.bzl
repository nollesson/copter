load("@bazel_tools//tools/cpp:cc_toolchain_config_lib.bzl", "tool_path", "feature", "flag_set", "flag_group")
load("@bazel_tools//tools/build_defs/cc:action_names.bzl", "ACTION_NAMES")

def _impl(ctx):
    tool_paths = [
        tool_path(
            name = "ar",
            path = "/usr/bin/avr-ar"
          ),
          tool_path(
            name = "compat-ld",
            path = "/usr/bin/avr-ld"
         ),
          tool_path(
            name = "cpp",
            path = "/usr/bin/avr-cpp"
         ),
          tool_path(
            name = "gcc",
            path = "/usr/bin/avr-gcc"
         ),
          tool_path(
            name = "gcov",
            path = "/usr/bin/avr-gcov"
         ),
          tool_path(
            name = "ld",
            path = "/usr/bin/avr-ld"
         ),
          tool_path(
            name = "nm",
            path = "/usr/bin/avr-gcc-nm"
         ),
          tool_path(
            name = "objcopy",
            path = "/usr/bin/avr-objcopy"
         ),
          tool_path(
            name = "objdump",
            path = "/usr/bin/avr-objdump"
         ),
          tool_path(
            name = "strip",
            path = "/usr/bin/avr-strip"
         )]

    toolchain_cpp_flags_feature = feature(
        name = "toolchain_cpp_flags",
        enabled = True,
        flag_sets = [
            flag_set(
                actions = [
                    ACTION_NAMES.preprocess_assemble,
                    ACTION_NAMES.c_compile,
                    ACTION_NAMES.cpp_compile,
                ],
                flag_groups = [
                    flag_group(
                        flags = [
                            "-g3",
                            "-Wall",
                            "-Wextra",
                            "-pedantic",
                            "-Werror",
                            "-std=c++1y",
                            "-Wno-builtin-macro-redefined",
                            "-D__DATE__=\"redacted\"",
                            "-D__TIMESTAMP__=\"redacted\"",
                            "-D__TIME__=\"redacted\"",
                            "-DF_CPU=16000000L",
                            "-mmcu=atmega328p",
                            "-Os",
                            "-DNDEBUG",
                            "-funsigned-bitfields",
                            "-funsigned-char",
                            "-fshort-enums",
                            "-fpack-struct",
                        ],
                    ),
                ],
            ),
        ],
    )

    toolchain_cpp_link_feature = feature(
        name = "toolchain_cpp_link_flags",
        enabled = True,
        flag_sets = [
            flag_set(
                actions = [
                    ACTION_NAMES.cpp_link_executable,
                ],
                flag_groups = [
                    flag_group(
                        flags = [
                            "-mmcu=atmega328p",
                        ],
                    ),
                ],
            ),
        ],
    )

    return cc_common.create_cc_toolchain_config_info(
        ctx = ctx,
        toolchain_identifier = "avr8-gnu-toolchain-linux_x86_64",
        host_system_name = "x86_64-pc-linux-gnu",
        target_system_name = "avr",
        target_cpu = "avr",
        target_libc = "avr",
        compiler = "gcc",
        abi_version = "avr",
        abi_libc_version = "avr",
        tool_paths = tool_paths,
        features = [toolchain_cpp_flags_feature, toolchain_cpp_link_feature],
        cxx_builtin_include_directories = [
            "/usr/lib/gcc/avr/5.4.0/include",
            "/usr/lib/gcc/avr/5.4.0/avr/5.4.0/include-fixed",
            "/usr/lib/avr/include",
        ]
    )

cc_toolchain_config = rule(
    implementation = _impl,
    attrs = {},
    provides = [CcToolchainConfigInfo],
)
