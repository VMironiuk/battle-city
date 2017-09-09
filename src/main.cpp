#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "board.h"
#include "collider.h"
#include "gamecontroller.h"
#include "movableitem.h"
#include "tile.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<Tile>();
    qmlRegisterType<MovableItem>("battlecity.movableitem", 1, 0, "MovableItem");

    Board *board = GameController::instance().board();

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("board", board);
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
