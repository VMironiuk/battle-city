#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "board.h"
#include "informationpanel.h"
#include "gamecontroller.h"
#include "gameresult.h"
#include "movableitem.h"
#include "shootableitem.h"
#include "tile.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<Base::Tile>();
    qmlRegisterType<Base::MovableItem>("battlecity.movableitem", 1, 0, "MovableItem");
    qmlRegisterType<Base::ShootableItem>();
    qmlRegisterType<Base::BaseItem>();
    qmlRegisterType<Utils::GameResult>("battlecity.gameresult", 1, 0, "GameResult");

    Base::Board *board = Controller::GameController::instance().board();
    Base::InformationPanel *informationPanel = Controller::GameController::instance()
            .informationPanel();
    Utils::GameResult *gameResult = Controller::GameController::instance().gameResult();

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("gameController",
                                             &Controller::GameController::instance());
    engine.rootContext()->setContextProperty("board", board);
    engine.rootContext()->setContextProperty("informationPanel", informationPanel);
    engine.rootContext()->setContextProperty("gameResult", gameResult);
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
