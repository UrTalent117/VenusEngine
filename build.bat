@echo off

set LUA_INC=D:\lua-5.4.4\include
set LUA_LIB=D:\lua-5.4.4\lib

if not exist "%LUA_INC%\lua.hpp" (
    echo Error: Lua header files not found. Please install Lua 5.4 and update LUA_INC path in build.bat
    pause
    exit /b 1
)

if not exist "%LUA_LIB%\lua54.lib" (
    echo Error: Lua library not found. Please install Lua 5.4 and update LUA_LIB path in build.bat
    pause
    exit /b 1
)

cl /EHsc /I%LUA_INC% src\main.cpp src\obj.h src\components.h /link %LUA_LIB%\lua54.lib /OUT:VenusEngine.exe

if %errorlevel% equ 0 (
    echo Build successful! VenusEngine.exe created.
) else (
    echo Build failed!
    pause
    exit /b 1
)

pause
