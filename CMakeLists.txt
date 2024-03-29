cmake_minimum_required(VERSION 3.21.1)

option(LINK_INSIGHT "Link Qt Insight Tracker library" ON)
option(BUILD_QDS_COMPONENTS "Build design studio components" ON)

enable_testing()
project(PoffinMasterDSApp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 6.2 REQUIRED COMPONENTS Core Gui Qml Quick QuickControls2 LinguistTools)

if (Qt6_VERSION VERSION_GREATER_EQUAL 6.3)
    qt_standard_project_setup()
endif()

# this line should not change, new code sources (qml or cpp) should be placed in modules
qt_add_executable(PoffinMasterDSApp src/main.cpp)

qt_add_resources(PoffinMasterDSApp "configuration"
    PREFIX "/"
    FILES
        qtquickcontrols2.conf
)

add_subdirectory(Backend)

macro(PAD_VERSION_NUMBER project_name digit)
    set(${project_name}_VERSION_CODE_${digit} ${${project_name}_VERSION_${digit}})
    if (${project_name}_VERSION_CODE_${digit} LESS 10)
        set(${project_name}_VERSION_CODE_${digit} 0${${project_name}_VERSION_CODE_${digit}})
    endif()
endmacro()

macro(CREATE_VERSION_CODE project_name)
    pad_version_number(${project_name} MAJOR)
    pad_version_number(${project_name} MINOR)
    pad_version_number(${project_name} PATCH)
    set(${project_name}_VERSION_CODE ${${project_name}_VERSION_CODE_MAJOR}${${project_name}_VERSION_CODE_MINOR}${${project_name}_VERSION_CODE_PATCH})
endmacro()

create_version_code(PoffinMasterDSApp)
message(STATUS "App Version code: ${PoffinMasterDSApp_VERSION_CODE}")

set_target_properties(PoffinMasterDSApp PROPERTIES
    QT_ANDROID_PACKAGE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/android
    QT_ANDROID_MIN_SDK_VERSION 23
    QT_ANDROID_TARGET_SDK_VERSION 33
    QT_ANDROID_VERSION_CODE ${PoffinMasterDSApp_VERSION_CODE}
    QT_ANDROID_VERSION_NAME ${PoffinMasterDSApp_VERSION}
)

target_link_libraries(PoffinMasterDSApp PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::QuickControls2
    backendplugin
)

if (BUILD_QDS_COMPONENTS)
    include(${CMAKE_CURRENT_SOURCE_DIR}/qmlcomponents)
endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/qmlmodules)

if (LINK_INSIGHT)
    include(${CMAKE_CURRENT_SOURCE_DIR}/insight)
endif ()

include(GNUInstallDirs)
install(TARGETS PoffinMasterDSApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# make IDEs aware of the QML import path
set(QML_IMPORT_PATH ${PROJECT_BINARY_DIR}/qml CACHE PATH
    "Path to the custom QML components defined by the project")

# collect sources for translations
# CMAKE SHOULD BE RERUN MANUALLY TO TAKE CHANGES!
file(GLOB_RECURSE QML_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} *.qml)
file(GLOB_RECURSE CPP_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} *.h *.cpp)

qt_add_translations(PoffinMasterDSApp
    TS_FILES
        i18n/lang_en_US.ts
        i18n/lang_fr_FR.ts
    SOURCES ${QML_SOURCES} ${CPP_SOURCES}
    OPTIONS -recursive
)
