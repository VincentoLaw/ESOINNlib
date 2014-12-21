#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtDebug>
#include <QTime>
#include <QtGlobal>
#include "esoinn.h"

int randInt(int low, int high)
{
// Random number between low and high
    return qrand() % ((high + 1) - low) + low;
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    QObject * c = engine.findChild<QObject * >("MainForm");
    c->setProperty("color", "red");
    Esoinn * es = new Esoinn(2, 20, 2, 1, 2);
    for (int j = 0; j < 4; j++)
        for (int i = 0; i < 1000; i++){
            double * w = new double[2];
            QTime time = QTime::currentTime();
            qsrand((uint)time.msec());
            w[0] = (qrand() % 100) + (j < 2 ? 50 : -150);
            w[1] = (qrand() % 100) + (j % 2 == 1 ? 50 : -150);
            //qDebug() << j << " " << i << "   " << w[0] << " " << w[1] << " " << randInt(5, 100) << endl;
            es->inputSignal(w);
        }
    double ** str = es->getStructure();
    for (int i = 1; i < str[0][0] + 1; i++){
        for (int j = 0; j < str[0][0] + 2; j++){
            if (j > 1 && str[i][j] == -1)
                break;
            qDebug() << str[i][j] << " ";
        }
        qDebug() << endl;

    }

    return app.exec();
}

