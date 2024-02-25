#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <QJsonObject>
#include <QJsonArray>

// Interface for all serializable objects
class Serializable
{
public:
    virtual ~Serializable() = default;

    // Serialize this object into a json object
    virtual QJsonObject toJson() const = 0;

    // Deserialize an object from a json object
    // Should be specialized in child class files
    template<typename T>
    static T fromJson(const QJsonObject& json)
    {
        Q_UNUSED(json)
        qWarning() << "Trying to deserialize an object from json, but no specialization provided.";
    }

protected:
    static void readInt(const QJsonObject& json, QString field, int& output)
    {
        const QJsonValue value = json[field];
        if (value.isDouble())
            output = value.toInt();
        else
            qWarning() << "No field '" << field << "' found.";
    }
};

template<>
void Serializable::fromJson<void>(const QJsonObject&) = delete;

#endif // SERIALIZABLE_H
