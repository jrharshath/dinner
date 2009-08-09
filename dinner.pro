QT       -= gui

TEMPLATE = app
TARGET = dinner
CONFIG += console
CONFIG -= app_bundle

INCLUDEPATH = include/ 
HEADERS += include/Error.h include/ErrorCode.h include/Statement.h include/InputParser.h include/StatementParser.h
SOURCES += src/main.cpp src/Error.cpp src/ErrorCode.cpp src/Statement.cpp src/InputParser.cpp src/StatementParser.cpp

