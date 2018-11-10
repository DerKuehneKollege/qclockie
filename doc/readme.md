# QClockie Project Setup

## Windows (x32), MinGW 4.9.2, Qt 5.6

- In CMakeList.txt setup CMAKE_PREFIX_PATH to directory contining Qt (e.g. C:\\Dev\\Qt\\5.6\\mingw49_32\\)
- CLion: Setup CMake output path to ".\bin" (Settings > Build, Execution, Deployment > CMake)

Following files need to be in the directory of the exe file:
- Windows
    - Debug
        - libgcc_s_dw2-1.dll
        - libstdc++-6.dll
        - libwinpthread-1.dll
        - Qt5Cored.dll
        - Qt5Guid.dll
        - Qt5Widgetsd.dll
        - platforms/qwindows.dll
    - Release
        - libgcc_s_dw2-1.dll
        - libstdc++-6.dll
        - libwinpthread-1.dll
        - Qt5Core.dll
        - Qt5Gui.dll
        - Qt5Network.dll
        - Qt5Widgets.dll
        - imageformats/*.dll
        - platforms/qwindows.dll
        
- Command to deploy:
C:\Dev\Qt\5.6\mingw49_32\bin\windeployqt.exe --dir D:\Softwareentwicklung\Versionsverwaltung\mithisoft\QClockie\bin\Release --release