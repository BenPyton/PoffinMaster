#include "poffin.h"
#include "berry.h"
#include <QRandomGenerator>

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
        //qDebug() << "Stat Sum: " << statsSum[i];
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
        //qDebug() << "Stat weakened: " << value;
    }

    /* then for each flavor, substract the number of negative flavors
     * ex: spicy:20 bitter:-10 sour:-10 => spicy:18 bitter:-12 sour:-12
     *
     * then clamp flavors between 0 and 100
     */
    int nbFlavor = 0;
    int mainFlavor = 0;
    int subFlavor = 0;
    for(int i = 0; i < NB_STAT; ++i)
    {
        int finalFlavorValue = qBound(0, m_stats.statValue(i) - negativeStatCount, 100);
        m_stats.setStatValue(i, finalFlavorValue);
        //qDebug() << "Stat final:" << finalFlavorValue;

        nbFlavor += (finalFlavorValue > 0);
        if (finalFlavorValue > m_stats.statValue(mainFlavor))
        {
            subFlavor = mainFlavor;
            mainFlavor = i;
        }
        else if (subFlavor == mainFlavor || finalFlavorValue > m_stats.statValue(subFlavor))
            subFlavor = i;
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

    if (m_timerId != 0)
        killTimer(m_timerId);

    QString poffinWord = tr("poffin");
    static QString s_imageFolder = "images/poffins/";

    // Update the poffin name
    switch (m_type)
    {
    case Type::Null:
        m_name = "";
        m_imageSource = "";
        break;
    case Type::Foul:
        m_name = tr("foul %1").arg(poffinWord);
        m_imageSource = s_imageFolder + "foul.png";
        m_level = 2;
        m_timerId = startTimer(1000);
        for (int i = 0; i < m_stats.count(); ++i)
            m_stats.setStatValue(i, 0);
        break;
    case Type::Normal:
        if (nbFlavor == 1)
        {
            const char* flavorName = m_stats.statName(mainFlavor);
            m_name = tr("%2 %1").arg(poffinWord).arg(PoffinStatsModel::tr(flavorName));
            m_imageSource = s_imageFolder + flavorName + ".png";
        }
        else
        {
            const char* mainFlavorName = m_stats.statName(mainFlavor);
            const char* subFlavorName = m_stats.statName(subFlavor);
            m_name = tr("%2-%3 %1").arg(poffinWord).arg(PoffinStatsModel::tr(mainFlavorName)).arg(PoffinStatsModel::tr(subFlavorName));
            m_imageSource = s_imageFolder + mainFlavorName + "-" + subFlavorName + ".png";
        }
        break;
    case Type::Overripe:
        m_name = tr("overripe %1").arg(poffinWord);
        m_imageSource = s_imageFolder + "overripe.png";
        m_level = 2;
        m_timerId = startTimer(1000);
        break;
    case Type::Rich:
        m_name = tr("rich %1").arg(poffinWord);
        m_imageSource = s_imageFolder + "rich.png";
        break;
    case Type::Mild:
        m_name = tr("mild %1").arg(poffinWord);
        m_imageSource = s_imageFolder + "mild.png";
        break;
    case Type::SuperMild:
        m_name = tr("super mild %1").arg(poffinWord);
        m_imageSource = s_imageFolder + "supermild.png";
        break;
    }

    // Capitalized first letter of each word
    bool wasLetter = false;
    for (qsizetype i = 0; i < m_name.size(); ++i)
    {
        bool isLetter = m_name[i].isLetter();
        if (isLetter && !wasLetter)
            m_name[i] = m_name[i].toUpper();
        wasLetter = isLetter;
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

void Poffin::timerEvent(QTimerEvent* event)
{
    Q_UNUSED(event)
    int nbRandomStat = 1;
    if (m_type == Type::Foul)
        nbRandomStat = 2;
    else if (m_type == Type::Overripe)
        nbRandomStat = 3;

    QList<int> statIndices = {0, 1, 2, 3, 4};
    while (statIndices.count() > nbRandomStat)
    {
        qsizetype k = static_cast<qsizetype>(QRandomGenerator::global()->generate() % static_cast<quint32>(statIndices.count()));
        statIndices.removeAt(k);
    }

    for (int i = 0; i < m_stats.count(); ++i)
    {
        m_stats.setStatValue(i, (statIndices.contains(i)) ? m_level : 0);
    }
}
