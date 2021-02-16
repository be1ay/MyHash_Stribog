/*
 * Copyright (c) 2021, Aleksei Belkin <mailbelkin@gmail.com>.
 * All rights reserved.
*/
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include "appcore.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    AppCore appCore(&app);

    app.setOrganizationName("My Organization");
    app.setOrganizationDomain("My Domain");
    QQuickStyle::setStyle("Material");
    QQmlApplicationEngine engine;
    QQmlContext *context = engine.rootContext();
    context->setContextProperty("appCore", &appCore);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    return app.exec();
}
