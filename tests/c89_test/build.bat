@echo off

clang -std=c89 -O0 -g -Wextra -Wno-unused-parameter -fdiagnostics-absolute-paths c89_test.c -o c89_test.exe