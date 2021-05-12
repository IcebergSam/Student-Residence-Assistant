cmake_minimum_required(VERSION 3.5)

project(GUIcopy LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

if(ANDROID)
  add_library(GUIcopy SHARED
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
  )
else()
  add_executable(GUIcopy
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    checklist.cpp
    checklist.h
    checklist.ui
    checklistitem.cpp
    checklistitem.h
    checklistitemeditor.cpp
    checklistitemeditor.h
    checklistitemeditor.ui
    note.cpp
    note.h
    noteeditor.cpp
    noteeditor.h
    noteeditor.ui
    notepad.cpp
    notepad.h
    notepad.ui
    alerter.cpp
    alerter.h
    alert.cpp
    alert.h
    lockable.cpp
    lockable.h
    calendar.cpp
    calendar.h
    calendar.ui
    calevent.cpp
    calevent.h
    caleventoption.cpp
    caleventoption.h
    caleventoption.ui
    editeventdialog.cpp
    editeventdialog.h
    editeventdialog.ui
    timer.cpp
    timer.h
    timer.ui
    studytimer.cpp
    studytimer.h
    studytimer.ui
    setinfo.cpp
    setinfo.h
    setinfo.ui
    languageparser.cpp
    languageparser.h
    voicecommand.cpp
    voicecommand.h
  )
endif()

target_link_libraries(GUIcopy PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
