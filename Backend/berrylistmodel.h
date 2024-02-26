#ifndef DATAOBJECTMODEL_H
#define DATAOBJECTMODEL_H

#include <QAbstractListModel>
#include <QQmlListProperty>
#include <QQmlEngine>

class Berry;

class BerryListModel : public QAbstractListModel
{
    Q_OBJECT
    QML_NAMED_ELEMENT(BerryList)
    Q_PROPERTY(int count READ count NOTIFY countChanged)

public:
    enum Role {
        Name = Qt::UserRole,
        IconPath
    };

    BerryListModel();

    int count() const { return static_cast<int>(m_data.count()); }
    Q_INVOKABLE Berry* get(int index) const
    {
        if (index >= 0 && index < count())
            return m_data[index];
        return nullptr;
    }

    Berry* getByName(const QString& name) const;

    Q_INVOKABLE void append(Berry* data)
    {
        int index = static_cast<int>(m_data.count());
        beginInsertRows(QModelIndex(), index, index);
        m_data.append(data);
        endInsertRows();
        emit countChanged();
    }

    Q_INVOKABLE void remove(int index, int count = 1)
    {
        beginRemoveRows(QModelIndex(), index, index + count - 1);
        m_data.remove(index);
        endRemoveRows();
        emit countChanged();
    }

    Q_INVOKABLE void clear()
    {
        removeRows(0, count());
        emit countChanged();
    }

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QHash<int,QByteArray> roleNames() const override;

    const QList<Berry*>& list() const { return m_data; }

signals:
    void countChanged();

private:
    QList<Berry*> m_data;
};

#endif // DATAOBJECTMODEL_H
