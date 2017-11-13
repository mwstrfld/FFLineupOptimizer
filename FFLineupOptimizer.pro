QT       += core \
            gui \
            widgets
 
CONFIG   += c++11 

SOURCES  += main.cpp \
            CsvParser.cpp \
            LineupOptimizerFrontEnd.cpp \
            Player.cpp

HEADERS  += CsvParser.h \
            LineupOptimizerFrontEnd.h \
            Player.h

FORMS    += LineupOptimizerFrontEnd.ui

TARGET    = FFLineupOptimizer 
TEMPLATE  = app
