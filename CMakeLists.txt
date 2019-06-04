cmake_minimum_required( VERSION 3.12.0 )

project( FFLineupOptimizer )

set( CMAKE_CXX_STANDARD 11 )

set( CMAKE_AUTOMOC ON )
set( CMAKE_AUTOUIC ON )

find_package( Qt5Core REQUIRED )
find_package( Qt5Gui REQUIRED )
find_package( Qt5Widgets REQUIRED )

set( SOURCES
     ./main.cpp
     ./AddPlayerDialog.cpp
     ./CsvParser.cpp
     ./LineupOptimizerFrontEnd.cpp
     ./Player.cpp
     ./SettingsDialog.cpp )

set( HEADERS
     ./AddPlayerDialog.h
     ./CsvParser.h
     ./LineupOptimizerFrontEnd.h
     ./Player.h
     ./SettingsDialog.h )

set( UI
     ./AddPlayerDialog.ui
     ./LineupOptimizerFrontEnd.ui
     ./SettingsDialog.ui )

qt5_add_resources( RESOURCES FFLineupOptimizer.qrc )

add_executable( FFLineupOptimizer
                ${HEADERS}
                ${SOURCES}
                ${UI}
                ${RESOURCES} )

# After refactoring, may want to switch to target_include_directories()
set( CMAKE_INCLUDE_CURRENT_DIR ON )

target_link_libraries( FFLineupOptimizer
                       Qt5::Core
                       Qt5::Gui
                       Qt5::Widgets )
