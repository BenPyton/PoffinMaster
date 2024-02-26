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
    Q_PROPERTY(int maxTotal READ maxTotal NOTIFY cooked)
    Q_PROPERTY(int level READ level NOTIFY cooked)
    Q_PROPERTY(int smoothness READ smoothness NOTIFY cooked)
    Q_PROPERTY(Type type READ type NOTIFY cooked)
    Q_PROPERTY(int count READ count NOTIFY cooked)
    Q_PROPERTY(QString mainFlavor READ mainFlavor NOTIFY cooked)
    Q_PROPERTY(QString subFlavor READ subFlavor NOTIFY cooked)
    Q_PROPERTY(QString name READ name NOTIFY cooked)

public:
    enum Type {
        Null, // empty basket
        Foul, // at least 2 of the same berries, or all flavors 0 (or failed cook)
        Overripe, // all flavors at 0
        Normal, // named after its 2 strongest flavors (e.g. 'Spicy-Bitter Poffin')
        Rich, // 3+ flavors && level <50
        Mild, // level 50+
        SuperMild, // level 95+
    };
    Q_ENUM(Type)

    explicit Poffin(QObject *parent = nullptr);
    virtual ~Poffin() override;

    PoffinStatsModel* stats() { return &m_stats; }
    int maxTotal() const { return m_maxTotal; }
    int smoothness() const { return m_smoothness; }
    int level() const { return m_level; }
    Type type() const { return m_type; }
    int count() const { return m_count; }
    const QString& mainFlavor() const { return m_stats.statName(m_mainFlavor); }
    const QString& subFlavor() const { return m_stats.statName(m_subFlavor); }
    const QString& name() const { return m_name; }

    void cook(const QList<class Berry*>& basket);

    virtual QJsonObject toJson() const override;
    static Poffin* fromJson(const QJsonObject& json);

signals:
    void cooked();
    //void statsChanged();
    //void maxTotalChanged();
    //void smoothnessChanged();
    //void levelChanged();
    //void typeChanged();
    //void countChanged();

private:
    const int MINIMUM_MAXTOTAL {10};
    int m_maxTotal {MINIMUM_MAXTOTAL};
    PoffinStatsModel m_stats;
    int m_level {0};
    int m_smoothness {0};
    Type m_type {Type::Null};
    int m_count {0};
    int m_mainFlavor {0};
    int m_subFlavor {0};
    QString m_name {"Null"};
};

/*template<>
Poffin* Serializable::fromJson<Poffin*>(const QJsonObject& json)
{
    return Poffin::fromJson(json);
}*/

#endif // POFFIN_H
