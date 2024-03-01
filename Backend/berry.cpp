#include "berry.h"

#define READ_JSON_VALUE(FIELD_NAME, FIELD_TYPE, OUT_VAR)\
if (const QJsonValue v = json[FIELD_NAME]; v.is##FIELD_TYPE())\
    OUT_VAR = v.to##FIELD_TYPE();\
else\
    qWarning() << "No field '" << FIELD_NAME << "' found.";

Berry::Berry(QObject *parent)
    : QObject{parent}
{}


Berry::Berry(QString name, QString iconPath)
    : QObject{nullptr}, m_name{name}, m_iconPath{iconPath}
{
}

QString Berry::iconPath() const
{
    return "images/berries/" + m_name.toLower() + ".png";
}

QJsonObject Berry::toJson() const
{
    // TODO
    Q_ASSERT(false);
    return QJsonObject();
}

Berry* Berry::fromJson(const QJsonObject& json)
{
    Berry* result = new Berry();

    READ_JSON_VALUE("name", String, result->m_name)
    READ_JSON_VALUE("iconPath", String, result->m_iconPath)

    QJsonArray jsonStats;
    READ_JSON_VALUE("stats", Array, jsonStats)

    readInt(json, "smoothness", result->m_smoothness);

    if (jsonStats.count() != static_cast<int>(BerryStat::STAT_COUNT))
    {
        qWarning() << "Wrong number of element in 'stats' array.";
    }
    else
    {
        for (int i = 0; i < jsonStats.count(); ++i)
        {
            if (!jsonStats[i].isDouble())
                qWarning() << "Stat value in not a number.";
            else
                result->m_stats[i] = jsonStats[i].toInt();
        }
    }

    return result;
}
