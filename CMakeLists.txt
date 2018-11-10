cmake_minimum_required(VERSION 3.4)
project(QClockie)

# version number
set (QCLOCKIE_VERSION_MAJOR 0)
set (QCLOCKIE_VERSION_MINOR 2)
set (QCLOCKIE_VERSION_REVISION 3)

configure_file (
    "${PROJECT_SOURCE_DIR}/src/version_number.h.in"
    "${PROJECT_SOURCE_DIR}/src/version_number.h"
)

# enable automoc for qt
set(CMAKE_AUTOMOC ON)

# set directory containing Qt includes and libraries for MinGW
if(WIN32)
    set(CMAKE_PREFIX_PATH "C:\\Dev\\Qt\\5.7\\mingw53_32")
endif()

# compiler flags
# note: option -D__NO_INLINE__ necessary due to MinGW bug, can maybe removed later
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -mwindows -D__NO_INLINE__")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# source files to be compiled
set(SOURCE_FILES
    src/main.cpp
    src/lib/autostart/AutostartHelper.h
    src/lib/autostart/AutostartHelperWindows.cpp
    src/lib/autostart/AutostartHelperWindows.h
    src/lib/keyboardhook/KeyboardHookWindows.cpp
    src/lib/keyboardhook/KeyboardHookWindows.h
    src/lib/runguard/RunGuard.cpp
    src/lib/runguard/RunGuard.h
    src/tts/TextToSpeechInterface.cpp
    src/tts/TextToSpeechInterface.h
    src/tts/TimeAnnouncement.cpp
    src/tts/TimeAnnouncement.h
    src/alarm/AlarmManager.cpp
    src/alarm/AlarmManager.h
    src/weather/WeatherData.h
    src/weather/YahooWeatherProvider.cpp
    src/weather/YahooWeatherProvider.h
    src/gui/ui_mainwindow.h
    src/gui/MainWindow.cpp
    src/gui/MainWindow.h
    src/gui/devconsole/ui_devconsole.h
    src/gui/devconsole/DevConsoleWidget.cpp
    src/gui/devconsole/DevConsoleWidget.h
    src/gui/settings/ui_settings.h
    src/gui/settings/SettingsWidget.cpp
    src/gui/settings/SettingsWidget.h
    src/settings/SettingsData.h
    src/settings/SettingsManager.cpp
    src/settings/SettingsManager.h)

# call find_package for required Qt packages
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Network REQUIRED)

# set exectuable name
add_executable(QClockie ${SOURCE_FILES})

# link against Qt libraries
target_link_libraries(QClockie Qt5::Core Qt5::Widgets Qt5::Gui Qt5::Network)