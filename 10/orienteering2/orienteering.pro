TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    cli.cpp \
    main.cpp \
    orienteeringmap.cpp \
    parser.cpp \
    point_info.cpp

HEADERS += \
    cli.hh \
    orienteeringmap.hh \
    parser.hh \
    point_info.hh


