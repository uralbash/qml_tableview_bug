#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTimer>
#include <QObject>

#include "database.h"
#include "model.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    DataBase database;
    Q_UNUSED(database);
    Model *model = new Model();

    model->setQuery("SELECT " TABLE_DATE ", " TABLE_TIME ", " TABLE_RANDOM ", " TABLE_MESSAGE
                    " FROM " TABLE);

    // Reload model
    QTimer *timer = new QTimer(model);
    QObject::connect(timer, SIGNAL(timeout()), model, SLOT(reloadData()));
    timer->start(2000);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("MY_MODEL", model);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
