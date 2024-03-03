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
