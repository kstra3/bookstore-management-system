@echo off
echo ============================================
echo Bookstore Management System - Compilation
echo ============================================
echo.

echo Compiling bookstore.c...
gcc -Wall -Wextra -std=c99 bookstore.c -o bookstore.exe

if %errorlevel% equ 0 (
    echo.
    echo ============================================
    echo Compilation successful!
    echo ============================================
    echo.
    echo Starting the program...
    echo.
    bookstore.exe
) else (
    echo.
    echo ============================================
    echo Compilation failed! Please check errors.
    echo ============================================
    pause
)
