@echo off

set LUA_INC=D:\lua-5.5\include
set LUA_LIB=D:\lua-5.5

if not exist "%LUA_INC%\lua.hpp" (
    echo Error: Lua header files not found. Please update LUA_INC path in build.bat
    pause
    exit /b 1
)

where cl >nul 2>nul
if %errorlevel% equ 0 (
    echo Using MSVC compiler...
    if exist "%LUA_LIB%\lua55.lib" (
        set LUA_LIB_FILE=%LUA_LIB%\lua55.lib
    ) else if exist "%LUA_LIB%\lua54.lib" (
        set LUA_LIB_FILE=%LUA_LIB%\lua54.lib
    ) else (
        echo Error: Lua .lib file not found. Please install Lua with static library
        pause
        exit /b 1
    )
    cl /EHsc /I%LUA_INC% src\main.cpp src\obj.h src\components.h /link %LUA_LIB_FILE% /OUT:VenusEngine.exe
) else (
    where g++ >nul 2>nul
    if %errorlevel% equ 0 (
        echo Using MinGW compiler...
        if exist "%LUA_LIB%\liblua55.a" (
            set LUA_LIB_FILE=%LUA_LIB%\liblua55.a
        ) else if exist "%LUA_LIB%\liblua54.a" (
            set LUA_LIB_FILE=%LUA_LIB%\liblua54.a
        ) else (
            echo Error: Lua .a file not found. Please install Lua with static library
            pause
            exit /b 1
        )
        g++ -std=c++11 -I%LUA_INC% src\main.cpp -o VenusEngine.exe %LUA_LIB_FILE%
    ) else (
        echo Error: No compiler found. Please install MSVC or MinGW
        pause
        exit /b 1
    )
)

if %errorlevel% equ 0 (
    echo Build successful! VenusEngine.exe created.
    if exist "%LUA_LIB%\lua55.dll" (
        copy "%LUA_LIB%\lua55.dll" . >nul
        echo Copied lua55.dll to current directory
    ) else if exist "%LUA_LIB%\lua54.dll" (
        copy "%LUA_LIB%\lua54.dll" . >nul
        echo Copied lua54.dll to current directory
    )
) else (
    echo Build failed!
    pause
    exit /b 1
)

pause
