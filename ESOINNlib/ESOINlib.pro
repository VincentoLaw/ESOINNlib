TEMPLATE = app

QT += qml quick

SOURCES +=ESOINNLibSources/cluster.cpp \
    ESOINNLibSources/connection.cpp \
    ESOINNLibSources/esoinn.cpp \
    ESOINNLibSources/neuron.cpp \
    main.cpp \
    dataExchanger.cpp \
    ESOINNLibSources/hasharray.cpp \
    ESOINNLibSources/cellgrid.cpp


RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    ESOINNLibSources/cluster.h \
    ESOINNLibSources/connection.h \
    ESOINNLibSources/esoinn.h \
    ESOINNLibSources/neuron.h \
    dataExchanger.h \
    hasharray.h \
    ESOINNLibSources/hasharray.h \
    ESOINNLibSources/cellgrid.h
