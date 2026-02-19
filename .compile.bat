@echo off
:: --- CONFIGURATION ---
SET "MSBUILD_PATH=C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\MSBuild\Current\Bin\MSBuild.exe"

:: Check for Community edition if BuildTools isn't found
if not exist "%MSBUILD_PATH%" (
    SET "MSBUILD_PATH=C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe"
)

if not exist "%MSBUILD_PATH%" (
    echo Error: MSBuild not found. Please ensure VS 2022 Build Tools are installed.
    pause
    exit
)

:: --- EXECUTION ---
echo ========================================
echo TARGET: %SLN_PATH%
echo STATUS: Starting Rebuild...
echo ========================================

:: /t:Rebuild cleans and then builds from scratch
:: /m enables multi-node compilation (uses all CPU cores for speed)
"%MSBUILD_PATH%" "%~dp0rAthena.sln" /t:Rebuild /p:Configuration=Release /p:Platform=x64 /m

echo.
echo ========================================
echo DONE! You can close this window.
echo ========================================
pause