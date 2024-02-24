#include "poffinstatsmodel.h"

PoffinStatsModel::PoffinStatsModel(QObject *parent)
    : QAbstractListModel{parent}
{
    m_data.append({"Spicy", 0, 0, QColor(240, 128, 48), "Coolness"});
    m_data.append({"Dry", 0, 0, QColor(104, 144, 240), "Beauty"});
    m_data.append({"Sweet", 0, 0, QColor(248, 88, 136), "Cuteness"});
    m_data.append({"Bitter", 0, 0, QColor(120, 200, 80), "Cleverness"});
    m_data.append({"Sour", 0, 0, QColor(248, 208, 48), "Toughness"});
}

QVariant PoffinStatsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        qWarning() << "[PoffinStatsModel] Invalid index";
        return QVariant();
    }

    int i = index.row();
    if (i < 0 && i >= m_data.count())
    {
        qWarning() << "[PoffinStatsModel] Index out of bounds";
        return QVariant();
    }

    const PoffinStat& data = m_data.at(i);

    switch(role)
    {
    case Role::Label:
        return data.label;
    case Role::Key:
        return data.key;
    case Role::Value:
        return data.value;
    case Role::Color:
        return data.color;
    case Role::BonusText:
        return data.bonusText;
    default:
        qWarning() << "[PoffinStatsModel] Unkown role";
    }
    return QVariant();
}

int PoffinStatsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return static_cast<int>(m_data.count());
}

QHash<int,QByteArray> PoffinStatsModel::roleNames() const
{
    static QHash<int, QByteArray> _roleNames = {
        {Role::Label, "label"},
        {Role::Key, "key"},
        {Role::Value, "value"},
        {Role::Color, "color"},
        {Role::BonusText, "bonusText"}
    };
    return _roleNames;
}

bool PoffinStatsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
    {
        qWarning() << "[PoffinStatsModel] Invalid index";
        return false;
    }

    int i = index.row();
    if (i < 0 && i >= m_data.count())
    {
        qWarning() << "[PoffinStatsModel] Index out of bounds";
        return false;
    }

    PoffinStat& data = m_data[i];

    switch(role)
    {
    case Role::Label:
        data.label = value.toString();
        break;
    case Role::Key:
        data.key = value.toInt();
        break;
    case Role::Value:
        data.value = value.toInt();
        break;
    case Role::Color:
        data.color = QColor::fromRgba(value.toUInt());
        break;
    default:
        qWarning() << "[PoffinStatsModel] Unkown role";
        return false;
    }
    QList<int> roles = {role};
    emit dataChanged(index, index, roles);
    return true;
}
