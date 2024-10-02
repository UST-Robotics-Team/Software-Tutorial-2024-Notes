@echo off
setlocal enabledelayedexpansion

if not exist "result" (
    mkdir result
)

echo -------------------------------------------------------------------------------------------------------

if not exist "result\hw1" (
    mkdir result\hw1
)

set success=1

echo Compiling HW1...
echo Running gcc -o homework1.exe .\hw1\main.c

gcc -o homework1.exe .\hw1\main.c
if errorlevel 1 (
    echo Sorry, HW1 fails to compile...
    set success=0
) else (
    echo Compilation Succeed!
)

if !success! equ 1 (
    echo Generating output... [Use Ctrl+C to stop if your code is stuck in an infinite loop]
    set hw1_tests=9

    for /L %%i in (1,1,!hw1_tests!) do (
        echo testing\hw1\input0%%i.txt | homework1.exe > result\hw1\out0%%i.txt
        type testing\hw1\input0%%i.txt | homework1.exe > result\hw1\out0%%i.txt
    )

    echo Done generating output for HW1, please use the VSCode diffchecker tool to check the output. Good luck!
)

echo -------------------------------------------------------------------------------------------------------

if not exist "result\hw2" (
    mkdir result\hw2
)

set success=1

echo Compiling HW2...
echo Running gcc -o homework2.exe .\hw2\main.c

gcc -o homework2.exe .\hw2\main.c
if errorlevel 1 (
    echo Sorry, HW2 fails to compile...
    set success=0
) else (
    echo Compilation Succeed!
)

if !success! equ 1 (
    echo Generating output... [Use Ctrl+C to stop if your code is stuck in an infinite loop]
    set hw2_tests=3

    for /L %%i in (1,1,!hw2_tests!) do (
        type testing\hw2\input0%%i.txt | homework2.exe > result\hw2\out0%%i.txt
    )

    echo Done generating output for HW2, please use the VSCode diffchecker tool to check the output. Good luck!
)

echo -------------------------------------------------------------------------------------------------------

if not exist "result\hw3" (
    mkdir result\hw3
)

set success=1

echo Compiling HW3...
echo Running gcc -o homework3.exe .\hw3\main.c .\hw3\utility.c .\hw3\utility.h

gcc -o homework3.exe .\hw3\main.c .\hw3\utility.c .\hw3\utility.h
if errorlevel 1 (
    echo Sorry, HW3 fails to compile...
    set success=0
) else (
    echo Compilation Succeed!
)

if !success! equ 1 (
    echo Generating output... [Use Ctrl+C to stop if your code is stuck in an infinite loop]
    set hw3_tests=3

    for /L %%i in (1,1,!hw3_tests!) do (
        type testing\hw3\input0%%i.txt | homework3.exe > result\hw3\out0%%i.txt
    )

    echo Done generating output for HW3, please use the VSCode diffchecker tool to check the output. Good luck!
)

echo -------------------------------------------------------------------------------------------------------

if not exist "result\hwb1" (
    mkdir result\hwb1
)

set success=1

echo Compiling HW Bonus 1...
echo Running gcc -o homeworkb1.exe .\hwb1\main.c

gcc -o homeworkb1.exe .\hwb1\main.c
if errorlevel 1 (
    echo Sorry, Homework Bonus 1 fails to compile...
    set success=0
) else (
    echo Compilation Succeed!
)

if !success! equ 1 (
    echo Generating output... [Use Ctrl+C to stop if your code is stuck in an infinite loop]
    set hwb1_tests=2

    for /L %%i in (1,1,!hwb1_tests!) do (
        type testing\hwb1\input0%%i.txt | homeworkb1.exe > result\hwb1\out0%%i.txt
    )

    echo Done generating output for HW Bonus 1, please use the VSCode diffchecker tool to check the output. Good luck!
)

echo -------------------------------------------------------------------------------------------------------