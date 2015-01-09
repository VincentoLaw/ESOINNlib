#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtDebug>


#include <QQuickView>
#include <QVariantList>
#include <QQmlComponent>
#include <QGuiApplication>
#include <QCoreApplication>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QDebug>
#include <QtGlobal>
#include <QTime>
#include <QObject>
#include "ESOINNLibSources/esoinn.h"
#include "dataExchanger.h"
#include <QQmlContext>
#include <QVariant>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    //Start of esoinn is in this class (dataExchanger) and it starts on click button LEARN
    dataExchanger dataEx;
    engine.rootContext()->setContextProperty("dataEx", &dataEx);
    //loading main qml file
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    return app.exec();

}

