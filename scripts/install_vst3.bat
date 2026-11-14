@echo off
setlocal enabledelayedexpansion

echo ===================================================
echo   MYSTICALAND SHELL VST3 - AUTOMATED INSTALLER
echo ===================================================
echo.

set "SOURCE_DIR=%~dp0..\build\Products\Shell\MysticalandShell_artefacts\Release\VST3\Mysticaland Shell.vst3"
set "DEST_DIR=C:\Program Files\Common Files\VST3"
set "TARGET=%DEST_DIR%\Mysticaland Shell.vst3"
set "BACKUP_DIR=%DEST_DIR%\Mysticaland_Backup_%date:~-4,4%%date:~-7,2%%date:~-10,2%"

if not exist "%SOURCE_DIR%" (
    echo [ERROR] Compiled VST3 bundle not found at:
    echo "%SOURCE_DIR%"
    echo Please build the project in Release configuration first!
    pause
    exit /b 1
)

echo [INFO] Target destination: %DEST_DIR%

:: Check for existing installation and back up
if exist "%TARGET%" (
    echo [INFO] Existing installation detected. Creating backup...
    mkdir "%BACKUP_DIR%" 2>nul
    xcopy /E /I /Y "%TARGET%" "%BACKUP_DIR%\Mysticaland Shell.vst3" >nul
    if %errorlevel% equ 0 (
        echo [OK] Backed up previous release to %BACKUP_DIR%
    ) else (
        echo [WARN] Could not create backup. Administrative privileges may be required.
    )
)

echo [INFO] Installing Mysticaland Shell.vst3...
xcopy /E /I /Y "%SOURCE_DIR%" "%TARGET%" >nul

if %errorlevel% equ 0 (
    echo.
    echo ===================================================
    echo   INSTALLATION SUCCESSFUL!
    echo ===================================================
    echo Mysticaland Shell.vst3 is now installed.
    echo Rescan your plugins in your DAW (FL Studio, Ableton, Reaper, etc.)
) else (
    echo.
    echo [ERROR] Installation failed.
    echo Please re-run this script as Administrator (Right click -> Run as administrator).
)

echo.
pause
