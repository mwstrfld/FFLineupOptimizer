QT       += core \
            gui \
            widgets
 
CONFIG   += c++11 

SOURCES  += main.cpp \
            AddPlayerDialog.cpp \
            CsvParser.cpp \
            LineupOptimizerFrontEnd.cpp \
            Player.cpp \
            SettingsDialog.cpp

HEADERS  += AddPlayerDialog.h \
            CsvParser.h \
            LineupOptimizerFrontEnd.h \
            Player.h \
            SettingsDialog.h

FORMS    += AddPlayerDialog.ui \
            LineupOptimizerFrontEnd.ui \
            SettingsDialog.ui

RESOURCES = FFLineupOptimizer.qrc

TARGET    = FFLineupOptimizer 
TEMPLATE  = app
