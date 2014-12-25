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
#include "esoinn.h"
#include "person.h"
#include <QQmlContext>
#include <QVariant>

int randInt(int low, int high)
{
// Random number between low and high
    return qrand() % ((high + 1) - low) + low;
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);


    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    QString qs = "";
    Esoinn * es = new Esoinn(2, 20, 2, 1, 2);
    //generating random data for esoinn
    for (int j = 0; j < 4; j++)
        for (int i = 0; i < 1000; i++){
            double * w = new double[2];

            w[0] = (qrand() % 150) + (j < 2 ? 30 : -180);
            w[1] = (qrand() % 150) + (j % 2 == 1 ? 30 : -180);
            //qDebug() << j << " " << i << "   " << w[0] << " " << w[1] << " " << randInt(5, 150) << endl;
            es->inputSignal(w);
        }
    //getting esoinn structure from double array
    double ** str = es->getStructure();
    for (int i = 1; i < str[0][0] + 1; i++){
        for (int j = 0; j < str[0][0] + 2; j++){
            if (j > 1 && str[i][j] == -1)
                break;
            //qDebug() << str[i][j] << " ";
            qs += QString::number(str[i][j]);
            qs += " " ;
        }
        qs += ",";
        //qDebug() << endl;

    }

    QQmlApplicationEngine engine;
    Person person;
    //adding data into exemplar person
    person.setName(qs);
    //adding exemplar person to qml object "Person"
    engine.rootContext()->setContextProperty("Person", &person);
    //loading main qml file
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();

}

