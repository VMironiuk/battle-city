#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "board.h"
#include "movableitem.h"
#include "tile.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<Tile>();
    qmlRegisterUncreatableType<MovableItem>("battlecity.movableitem", 1, 0, "MovableItem",
                                            "Cannot register MovableItem type");

    Board board;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("board", &board);
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
