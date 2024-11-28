cmake_minimum_required(VERSION 3.16)

project(TextualFileIO VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(QT_QML_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR})

if(CMAKE_BUILD_TYPE STREQUAL RELEASE)
    set(CMAKE_CXX_FLAGS_RELEASE "-Ofast")
endif()

find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)

qt6_policy(SET QTP0001 NEW)
qt_standard_project_setup()

# Uncomment the next line and replace "..." with the extension plugins root path of your choice
#set(PLUGINS_PATH ...)

qt6_add_qml_module(textualfileioplugin
    URI "MyModules.IO.TextualFileIO"
    VERSION 1.0

    PLUGIN_TARGET textualfileioplugin

    OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/MyModules/IO/TextualFileIO/"
)

target_sources(textualfileioplugin PRIVATE
               textualfileio.cpp
               textualfileio.hpp)

target_include_directories(textualfileioplugin PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(textualfileioplugin PRIVATE Qt6::Quick)

#target_link_libraries(textualfileioplugin
#    PRIVATE Qt6::Core Qt6::Qml Qt6::Quick)


install(TARGETS textualfileioplugin
        RUNTIME DESTINATION "${PLUGINS_PATH}/MyModules/IO/TextualFileIO/"
        LIBRARY DESTINATION "${PLUGINS_PATH}/MyModules/IO/TextualFileIO/")

 install(FILES ${CMAKE_CURRENT_BINARY_DIR}/MyModules/IO/TextualFileIO/qmldir
        ${CMAKE_CURRENT_BINARY_DIR}/MyModules/IO/TextualFileIO/textualfileioplugin.qmltypes
        ${CMAKE_CURRENT_BINARY_DIR}/MyModules/IO/TextualFileIO/textualfileioplugin_qml_module_dir_map.qrc
        DESTINATION "${PLUGINS_PATH}/MyModules/IO/TextualFileIO/")
