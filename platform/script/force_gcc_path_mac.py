import os
from os.path import join
Import("env")

# macOS ใช้ clang++/gcc native
gcc_path = "/usr/bin/clang++"  # หรือ "/usr/local/bin/g++-12" หากใช้ Homebrew gcc

env.Replace(
    CC=gcc_path.replace("clang++","clang"),  # CC ต้องเป็น C compiler
    CXX=gcc_path,
    LINK=gcc_path,
    AR="ar",
    RANLIB="ranlib"
)

# PATH ของ macOS
env["ENV"]["PATH"] = os.environ.get("PATH", "")
print("[force_gcc_path_mac.py] Using compiler:", gcc_path)
