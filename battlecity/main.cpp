#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "board.h"
#include "informationpanel.h"
#include "gamecontroller.h"
#include "movableitem.h"
#include "shootableitem.h"
#include "tile.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<Tile>();
    qmlRegisterType<MovableItem>("battlecity.movableitem", 1, 0, "MovableItem");
    qmlRegisterType<ShootableItem>();
    qmlRegisterType<BaseItem>();

    Board *board = GameController::instance().board();
    InformationPanel *informationPanel = GameController::instance().informationPanel();

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("gameController", &GameController::instance());
    engine.rootContext()->setContextProperty("board", board);
    engine.rootContext()->setContextProperty("informationPanel", informationPanel);
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
