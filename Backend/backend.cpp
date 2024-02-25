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
    load(":/qt/qml/content/data/backend.json");

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
        qCritical() << "Can't open file" << file.fileName();
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
