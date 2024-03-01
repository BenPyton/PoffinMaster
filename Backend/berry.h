#ifndef BERRY_H
#define BERRY_H

#include <QObject>
#include <QQmlEngine>
#include "serializable.h"

enum class BerryStat : int {
    Spicy = 0,
    Dry,
    Sweet,
    Bitter,
    Sour,
    STAT_COUNT
};

class Berry : public QObject, public Serializable
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QString name MEMBER m_name NOTIFY nameChanged)
    Q_PROPERTY(QString iconPath MEMBER m_iconPath NOTIFY iconPathChanged)

public:
    explicit Berry(QObject *parent = nullptr);
    Berry(QString name, QString iconPath = "");

    QString name() const { return m_name; }
    QString iconPath() const;

    int operator[](BerryStat stat) const { return statValue(stat); }
    int operator[](int stat) const { return statValue(stat); }

    int statValue(BerryStat stat) const
    {
        return statValue(static_cast<int>(stat));
    }

    int statValue(int stat) const
    {
        if (stat < 0 || stat >= static_cast<int>(BerryStat::STAT_COUNT))
            return 0;
        return m_stats[stat];
    }

    int smoothness() const { return m_smoothness; }

    // Serializable
    virtual QJsonObject toJson() const override;
    static Berry* fromJson(const QJsonObject& json);

signals:
    void nameChanged();
    void iconPathChanged();
    void smoothnessChanged();
    void firmnessChanged();

private:
    QString m_name {"NULL"};
    QString m_iconPath {};
    int m_stats[static_cast<int>(BerryStat::STAT_COUNT)] {0};
    int m_smoothness {0};
};

/*template<>
Berry* Serializable::fromJson<Berry*>(const QJsonObject& json)
{
    return Berry::fromJson(json);
}*/

#endif // BERRY_H
