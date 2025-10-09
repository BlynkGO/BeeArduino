import os
from os.path import join

Import("env")

# path ของ toolchain relative กับ PROJECT_DIR
toolchain_path = join(env['PROJECT_DIR'], "toolchain", "bin")

# ตั้ง compiler และ PATH
env.Replace(
    CC=join(toolchain_path, "gcc.exe"),
    CXX=join(toolchain_path, "g++.exe"),
    LINK=join(toolchain_path, "g++.exe"),
    AR=join(toolchain_path, "ar.exe"),
    RANLIB=join(toolchain_path, "ranlib.exe"),
)

# เพิ่ม toolchain ลง PATH ของ environment
env["ENV"]["PATH"] = toolchain_path + os.pathsep + env["ENV"].get("PATH", "")
