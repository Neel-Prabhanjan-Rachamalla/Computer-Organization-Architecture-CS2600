import subprocess
import os

wd = os.getcwd()
os.chdir("./input")
list_files = subprocess.run(["bash","compile.sh","arithmetic.asm","ICache.txt"])
os.chdir(wd)
list_files = subprocess.run(["g++","processor.cpp"])
list_files = subprocess.run(["./a.out"])


