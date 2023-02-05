@echo off
title Cookie Compiler (g++ required)
echo Compiling cookie...
g++ *.cpp -o cookie
echo Compile finished...
echo Run cookie? 
pause
cookie.exe
pause