TEMPLATE = app

QT += qml quick

SOURCES +=  neuron.cpp\
    cluster.cpp \
    connection.cpp \
    esoinn.cpp \
    main.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    cluster.h \
    connection.h \
    neuron.h \
    esoinn.h
