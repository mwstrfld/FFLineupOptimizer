QT       += core \
            gui \
            widgets
 
CONFIG   += c++11 

SOURCES  += main.cpp \
            AddPlayerDialog.cpp \
            CsvParser.cpp \
            LineupOptimizerFrontEnd.cpp \
            Player.cpp

HEADERS  += AddPlayerDialog.h \
            CsvParser.h \
            LineupOptimizerFrontEnd.h \
            Player.h

FORMS    += AddPlayerDialog.ui \
            LineupOptimizerFrontEnd.ui

RESOURCES = FFLineupOptimizer.qrc

TARGET    = FFLineupOptimizer 
TEMPLATE  = app
