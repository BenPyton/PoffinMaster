// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QTranslator>
#include <QLocale>
#include <QString>

#include "app_environment.h"
#include "import_qml_components_plugins.h"
#include "import_qml_plugins.h"

using namespace Qt::Literals::StringLiterals;

int main(int argc, char *argv[])
{
    set_qt_environment();

    QQuickStyle::setStyle("Material");

    QGuiApplication app(argc, argv);

    QTranslator translator;
    if (translator.load(QLocale::system(), u"lang"_s, u"_"_s, u":/i18n"_s))
    {
        app.installTranslator(&translator);
        qDebug() << "Translation installed successfully!";
    }
    else
    {
        qCritical() << "Translation not loaded!";
    }

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/qt/qml/Main/main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    engine.addImportPath(QCoreApplication::applicationDirPath() + "/qml");
    engine.addImportPath(":/");

    engine.load(url);

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
