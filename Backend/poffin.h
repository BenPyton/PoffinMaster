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

#ifndef POFFIN_H
#define POFFIN_H

#include <QObject>
#include <QQmlEngine>
#include "poffinstatsmodel.h"
#include "serializable.h"

class Poffin : public QObject, public Serializable
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(PoffinStatsModel* stats READ stats NOTIFY cooked)
    Q_PROPERTY(int level READ level NOTIFY cooked)
    Q_PROPERTY(int smoothness READ smoothness NOTIFY cooked)
    Q_PROPERTY(Type type READ type NOTIFY cooked)
    Q_PROPERTY(int count READ count NOTIFY cooked)
    Q_PROPERTY(QString name READ name NOTIFY cooked)
    Q_PROPERTY(QString imageSource READ imageSource NOTIFY cooked)

public:
    enum Type {
        Null,       // empty basket
        Foul,       // at least 2 of the same berries, or all flavors 0 (or failed cook)
        Overripe,   // all flavors at 0
        Normal,     // named after its 2 strongest flavors (e.g. 'Spicy-Bitter Poffin')
        Rich,       // 3+ flavors && level <50
        Mild,       // level 50+
        SuperMild,  // level 95+
    };
    Q_ENUM(Type)

    explicit Poffin(QObject *parent = nullptr);
    virtual ~Poffin() override;

    PoffinStatsModel* stats() { return &m_stats; }
    int smoothness() const { return m_smoothness; }
    int level() const { return m_level; }
    Type type() const { return m_type; }
    int count() const { return m_count; }
    const QString& name() const { return m_name; }
    const QString& imageSource() const { return m_imageSource; }

    void cook(const QList<class Berry*>& basket);

    virtual QJsonObject toJson() const override;
    static Poffin* fromJson(const QJsonObject& json);

signals:
    void cooked();

protected:
    virtual void timerEvent(QTimerEvent* event) override;

private:
    PoffinStatsModel m_stats;
    int m_level {0};
    int m_smoothness {0};
    Type m_type {Type::Null};
    int m_count {0};
    QString m_name {"Null"};
    QString m_imageSource {"Null"};
    int m_timerId {0};
};

/*template<>
Poffin* Serializable::fromJson<Poffin*>(const QJsonObject& json)
{
    return Poffin::fromJson(json);
}*/

#endif // POFFIN_H
