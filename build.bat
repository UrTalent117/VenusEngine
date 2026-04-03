@echo off

rem 设置Lua 5.5路径
set LUA_INC=.
set LUA_LIB=.

rem 检查Lua头文件
if not exist "%LUA_INC%\lua.hpp" (
    echo Error: lua.hpp not found. Please place Lua 5.5 header files in the current directory.
    pause
    exit /b 1
)

rem 检查编译器
set COMPILER=
where cl >nul 2>nul
if %errorlevel% equ 0 (
    set COMPILER=MSVC
) else (
    where g++ >nul 2>nul
    if %errorlevel% equ 0 (
        set COMPILER=MinGW
    )
)

if "%COMPILER%"=="" (
    echo Error: No compiler found. Please install MSVC or MinGW.
    echo For MSVC: Install Visual Studio with C++ development tools.
    echo For MinGW: Install MinGW-w64 and add to PATH.
    pause
    exit /b 1
)

echo Using %COMPILER% compiler...

rem 编译命令
if "%COMPILER%"=="MSVC" (
    if exist "%LUA_LIB%\lua55.lib" (
        cl /EHsc /I%LUA_INC% src\main.cpp /link %LUA_LIB%\lua55.lib /OUT:VenusEngine.exe
    ) else (
        echo Error: lua55.lib not found. Please place Lua 5.5 static library in the current directory.
        pause
        exit /b 1
    )
) else (
    if exist "%LUA_LIB%\liblua55.a" (
        g++ -std=c++11 -I%LUA_INC% src\main.cpp -o VenusEngine.exe %LUA_LIB%\liblua55.a
    ) else (
        echo Error: liblua55.a not found. Please place Lua 5.5 static library in the current directory.
        pause
        exit /b 1
    )
)

rem 检查编译结果
if %errorlevel% equ 0 (
    echo Build successful! VenusEngine.exe created.
    rem 复制Lua DLL
    if exist "%LUA_LIB%\lua55.dll" (
        copy "%LUA_LIB%\lua55.dll" . >nul
        echo Copied lua55.dll to current directory.
    ) else (
        echo Warning: lua55.dll not found. You may need to copy it manually.
    )
) else (
    echo Build failed!
    pause
    exit /b 1
)

pause
