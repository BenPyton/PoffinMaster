/* Copyright 2021 The Qt Company Ltd.
 * Copyright 2024 Benoit Pelletier
 *
 * This file is part of Poffin Master.
 * Poffin Master is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 3
 * as published by the Free Software Foundation.
 *
 * Poffin Master is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Poffin Master. If not, see <https://www.gnu.org/licenses/>.
 */

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QTranslator>
#include <QLocale>
#include <QString>
#include <QResource>

#include "app_environment.h"
#include "import_qml_components_plugins.h"
#include "import_qml_plugins.h"

#ifdef QT_DEBUG
#include <QDirIterator>
#endif

using namespace Qt::Literals::StringLiterals;

void RegisterResourceFile(const char* resourceFile)
{
    if (QResource::registerResource(resourceFile))
        qDebug() << "Resource file '" << resourceFile << "' registered successfully!";
    else
        qCritical() << "Resource file '" << resourceFile << "' not registered.";
}

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

    // Import external resources to the application
    RegisterResourceFile("assets:/berry_images.rcc");
    RegisterResourceFile("assets:/poffin_images.rcc");

#ifdef QT_DEBUG
    // List all resources available
    QDirIterator it(":", QDirIterator::Subdirectories);
    while (it.hasNext()) {
        qDebug() << it.next();
    }
#endif

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
