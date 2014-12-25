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

class Message : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString author READ author WRITE setAuthor NOTIFY authorChanged)
public:
    void setAuthor(const QString &a) {
        if (a != m_author) {
            m_author = a;
            emit authorChanged();
        }
    }
    QString author() const {
        return m_author;
    }
signals:
    void authorChanged();
private:
    QString m_author;
};


int randInt(int low, int high)
{
// Random number between low and high
    return qrand() % ((high + 1) - low) + low;
}

int main(int argc, char *argv[])
{
    /*QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    //Message msg();
    //engine.rootContext()->setContextProperty("msg", &msg);

    //Person ppl();
    //engine.rootContext()->setContextProperty("Person", &ppl);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));*/



    /*QCoreApplication app(argc, argv);
//![0]
    qmlRegisterType<Person>("People", 1,0, "Person");
//![0]

    QQmlEngine engine;
    QQmlComponent component(&engine, QUrl("qrc:main.qml"));
    Person *person = qobject_cast<Person *>(component.create());
    if (person) {
        qWarning() << "The person's name is" << person->name();
        qWarning() << "They wear a" << person->shoeSize() << "sized shoe";
    } else {
        qWarning() << component.errors();
    }*/

    QCoreApplication app(argc, argv);
    QQmlEngine engine;
    Message msg();
    engine.rootContext()->setContextProperty("msg",qvariant_cast<QObject *>(msg));
    QQmlComponent component(&engine, QUrl::fromLocalFile("qrc:/main.qml"));
    component.create();



    Esoinn * es = new Esoinn(2, 20, 2, 1, 2);
    for (int j = 0; j < 4; j++)
        for (int i = 0; i < 100; i++){
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

    //QObject *rect = engine.findChild<QObject*>("VisualStructure");
    //qDebug() << rect;
    //if (rect)
    //    rect->setProperty("width",100);


    /*QDeclarativeView view;
    view.rootContext()->setContextProperty("currentDateTime", QDateTime::currentDateTime());
    view.setSource(QUrl::fromLocalFile("MyItem.qml"));
    view.show();
    QObject *rect = engine.findChild<QObject*>("mainW");
    qDebug() << rect;
    if (rect)
        rect->setProperty("width",100);*/

    //        ->setContextProperty("width", 100);
    // C++
    /*QQuickView view(QUrl::fromLocalFile("main.qml"));

    QVariantList list;
    list << 10 << QColor(Qt::green) << "bottles";

    QVariantMap map;
    map.insert("language", "QML");
    map.insert("released", QDate(2010, 9, 21));

    QMetaObject::invokeMethod(view.rootObject(), "readValues",
            Q_ARG(QVariant, QVariant::fromValue(list)),
            Q_ARG(QVariant, QVariant::fromValue(map)));*/


    /*
    QObject * c = engine.findChild<QObject * >("MainForm");
    c->setProperty("width", 100);
    c->setProperty("color", "green");*/
    return app.exec();

}

