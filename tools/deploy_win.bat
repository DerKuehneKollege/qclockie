@echo off
REM paths
SET QT_BIN_DIR=C:\Dev\Qt\5.6\mingw49_32\bin
SET MINGW_BIN_DIR=C:\Dev\Qt\Tools\mingw492_32\bin
SET TARGET_DIR=D:\Softwareentwicklung\Versionsverwaltung\Mithisoft\QClockie\bin\Deploy
SET TARGET_EXEC=QClockie.exe

REM release or debug
SET MODE=release

REM @echo on

echo ===== Setting up deploy directory =====
echo Deploy directory is %TARGET_DIR%

REM TODO create deploy directory if not existing. if existing clear directory.

echo ===== Copying executables and files =====
REM TODO copy executables
REM TODO copy icons
REM TODO copy assets

echo ===== Copying MinGW DLLs =====
REM TODO copy libgcc_s_dw2-1.dll from %MINGW_BIN_DIR%
REM TODO copy libwinpthread-1.dll from %MINGW_BIN_DIR%
REM TODO copy libstdc++-6.dll from %MINGW_BIN_DIR%

REM TODO copy WindowsSapi.exe

@echo on
echo ===== Deploy for Windows =====
echo Mode: %MODE%
"%QT_BIN_DIR%\windeployqt.exe" --dir %TARGET_DIR% --%MODE% %TARGET_DIR%\%TARGET_EXEC%

@echo off
echo ===== Cleaning up unused libraries =====
REM TODO delete D3Dcompiler_43.dll
REM TODO delete opengl32sw.dll
REM TODO delete libGLESV2.dll

REM TODO create InnoSetup install script

@echo on