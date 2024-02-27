#include "poffin.h"
#include "berry.h"

Poffin::Poffin(QObject *parent)
    : QObject{parent}
{}

Poffin::~Poffin()
{}

void Poffin::cook(const QList<Berry*>& basket)
{
    qDebug() << "-- Cooking!";

    // Explicit cast to avoid warnings later
    static const int NB_STAT = static_cast<int>(BerryStat::STAT_COUNT);
    int basketCount = static_cast<int>(basket.count());

    // Number of resulting poffins is just the number of berries used
    m_count = basketCount;

    /* Smoothness calculation
     * poffin smoothness = Floor(avgSmoothness) - basket.count()
     * ex: {25, 20} = Floor((25+20)/2) - 2 = Floor(22.5) - 2 = 22 - 2 = 20
     */
    int smoothSum = 0;
    for (const Berry* berry: basket)
    {
        smoothSum += berry->smoothness();
    }

    m_smoothness = 0;
    if (basketCount > 0)
        m_smoothness = qFloor(static_cast<float>(smoothSum) / static_cast<float>(basketCount)) - basketCount;

    /* Sum all flavors from the berries
     */
    int statsSum[NB_STAT] = {0};
    for(int i = 0; i < NB_STAT; ++i)
    {
        for (const Berry* berry: basket)
        {
            statsSum[i] += berry->statValue(i);
        }
        qDebug() << "Stat Sum: " << statsSum[i];
    }

    /* Apply flavor calculation as follow:
     * spicy = spicy - dry
     * dry = dry - sweet
     * sweet = sweet - bitter
     * bitter = bitter - sour
     * sour = sour - spicy
     */
    int negativeStatCount = 0;
    for(int i = 0; i < NB_STAT; ++i)
    {
        int value = statsSum[i];
        value -= statsSum[(i+1) % NB_STAT];
        negativeStatCount += (value < 0);
        m_stats.setStatValue(i, value);
        qDebug() << "Stat weakened: " << value;
    }

    /* then for each flavor, substract the number of negative flavors
     * ex: spicy:20 bitter:-10 sour:-10 => spicy:18 bitter:-12 sour:-12
     *
     * then clamp flavors between 0 and 100
     */
    int nbFlavor = 0;
    m_mainFlavor = 0;
    m_subFlavor = 0;
    for(int i = 0; i < NB_STAT; ++i)
    {
        int finalFlavorValue = qBound(0, m_stats.statValue(i) - negativeStatCount, 100);
        m_stats.setStatValue(i, finalFlavorValue);
        qDebug() << "Stat final:" << finalFlavorValue;

        nbFlavor += (finalFlavorValue > 0);
        if (finalFlavorValue > m_stats.statValue(m_mainFlavor))
        {
            m_subFlavor = m_mainFlavor;
            m_mainFlavor = i;
        }
        else if (m_subFlavor == m_mainFlavor || finalFlavorValue > m_stats.statValue(m_subFlavor))
            m_subFlavor = i;
    }
    qDebug() << "Nb Flavor:" << nbFlavor;

    /* Poffin level:
     * this is just the highest flavor value
     */
    m_level = 2; // a poffin can't be less than level 2
    for (const PoffinStat& stat : m_stats.list())
    {
        if (stat.value > m_level)
            m_level = stat.value;
    }
    qDebug() << "Level: " << m_level;
    m_maxTotal = m_level;

    /* Poffin type:
     * Main flavor: highest
     * secondary flavor
     *
     * 2 or more of the same berries in basket => foul poffin! (3 random stats and level 2)
     *
     * 3 falvors => rich poffin
     *
     */
    bool multiBerries = false;
    QList<const Berry*> existingBerries;
    for (const Berry* berry: basket)
    {
        multiBerries |= existingBerries.contains(berry);
        existingBerries.append(berry);
    }

    m_type = Type::Normal;
    if (basketCount <= 0)
        m_type = Type::Null;
    else if (multiBerries)
        m_type = Type::Foul;
    else if (nbFlavor == 0)
        m_type = Type::Overripe;
    else if (m_level >= 95)
        m_type = Type::SuperMild;
    else if (m_level >= 50)
        m_type = Type::Mild;
    else if (nbFlavor == 3)
        m_type = Type::Rich;

    // Update the poffin name
    switch (m_type)
    {
    case Type::Null:
        m_name = "";
        break;
    case Type::Foul:
        m_name = tr("Foul");
        m_level = 2;
        for (int i = 0; i < m_stats.count(); ++i)
            m_stats.setStatValue(i, 0);
        break;
    case Type::Normal:
        if (nbFlavor == 1)
            m_name = mainFlavor();
        else
            m_name = tr("%1-%2").arg(mainFlavor()).arg(subFlavor());
        break;
    case Type::Overripe:
        m_name = tr("Overripe");
        break;
    case Type::Rich:
        m_name = tr("Rich");
        break;
    case Type::Mild:
        m_name = tr("Mild");
        break;
    case Type::SuperMild:
        m_name = tr("Super Mild");
        break;
    }

    emit cooked();
}

QJsonObject Poffin::toJson() const
{
    // TODO
    Q_ASSERT(false);
    return QJsonObject();
}

Poffin* Poffin::fromJson(const QJsonObject& json)
{
    // TODO
    Q_UNUSED(json)
    Q_ASSERT(false);
    return nullptr;
}
