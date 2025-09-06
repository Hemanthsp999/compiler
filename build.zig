const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const compiler = b.addStaticLibrary(.{ .name = "compiler for fun", .target = target, .optimize = optimize });

    const c_source_files: [1][]const u8 = .{"./lexical/lexi.c"};

    compiler.linkLibC();
    for (c_source_files) |file| {
        compiler.addCSourceFile(.{ .file = b.path(file), .flags = &.{
            "-g",
            "-Wall",
            "-Wextra",
            "-Werror",
            "-I",
            "-IRegression",
        } });
    }

    b.installArtifact(compiler);

    const test_exe = b.addExecutable(.{ .name = "test", .target = target, .optimize = optimize });

    test_exe.linkLibrary(compiler);
    test_exe.linkSystemLibrary("m");

    test_exe.addCSourceFile(.{ .file = b.path("./main.c"), .flags = &.{
        "-g",
        "-Wall",
        "-Wextra",
        "-Werror",
        "-I",
        "-IRegression",
    } });

    b.installArtifact(test_exe);
    const test_step = b.step("test", "Run the test");
    const run_test = b.addRunArtifact(test_exe);
    test_step.dependOn(&run_test.step);
}
