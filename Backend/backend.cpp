/*
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

#include "backend.h"
#include "berry.h"
#include "poffin.h"
#include <QJsonDocument>
#include <QFile>
#include <QQmlFile>
#include <QDirIterator>
#include <QtMath>
#include <QCoreApplication>

Backend::Backend(QObject *parent)
    : QObject{parent}
    , m_poffin{new Poffin {this}}
{
    load(":/Backend/data/backend.json");

    // TODO: avoid the intermediate funcion onBasketChanged?
    QObject::connect(&m_basket, &BerryListModel::countChanged, this, &Backend::onBasketChanged);

    qDebug() << "Backend is loaded!";
}

Backend::~Backend()
{
    qDebug() << "Backend is destroyed...";
}

bool Backend::load(QString path)
{
    QFile file;
    if (QFileInfo::exists(path))
        file.setFileName(path);
    else
        file.setFileName(QQmlFile::urlToLocalFileOrQrc(path));

    if (!file.open(QIODevice::ReadOnly))
    {
        qCritical() << "Can't open file" << path;
        return false;
    }

    QByteArray data = file.readAll();
    QJsonDocument json {QJsonDocument::fromJson(data)};

    if (!json.isObject())
    {
        qCritical() << "Json file's root is not an object.";
        return false;
    }

    return fromJson(json.object());
}

QJsonObject Backend::toJson() const
{
    Q_ASSERT(false);
    return QJsonObject();
}

bool Backend::fromJson(const QJsonObject& json)
{
    QJsonValue value = json["berries"];
    if (!value.isArray())
    {
        qCritical() << "No array 'berries' found.";
        return false;
    }

    QJsonArray array = value.toArray();
    m_berries.clear();
    for (const QJsonValue valueBerry : array)
    {
        if (!valueBerry.isObject())
        {
            qWarning() << "Non-object value in berries array.";
            continue;
        }
        Berry* berry = Berry::fromJson(valueBerry.toObject());
        if (berry == nullptr)
        {
            qWarning() << "Berry was not successfully created.";
            continue;
        }
        berry->setParent(this);
        m_berries.append(berry);
    }

    return true;
}

void Backend::onBasketChanged()
{
    m_poffin->cook(m_basket.list());
}

QString Backend::name() const
{
    return "Cpp Backend";
}

QString Backend::version() const
{
    return QCoreApplication::applicationVersion();
}

QString Backend::qtVersion() const
{
    return QT_VERSION_STR;
}

QString Backend::authorName() const
{
    return "Beno\u00EEt Pelletier";
}

QString Backend::licenseName() const
{
    return "GPLv3";
}

QString Backend::licenseUrl() const
{
    return "https://www.gnu.org/licenses/gpl-3.0.html";
}

QString Backend::sourceUrl() const
{
    return "https://github.com/BenPyton/PoffinMaster";
}

bool Backend::isDebug() const
{
#ifdef QT_DEBUG
    return true;
#else
    return false;
#endif
}
