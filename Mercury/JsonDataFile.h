#pragma once

#include <qglobal.h>
#include <qiodevice.h>
#include <qfile.h>
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <qjsonobject.h>

class JsonDataFile 
{
    QJsonDocument doc;

public:
    JsonDataFile() = default;
    ~JsonDataFile() = default;

    bool load(const QString & src)
    {
        bool ret = false;

        QFile file(src);
        if (file.open(QIODevice::ReadOnly))
        {
            QByteArray dt = file.readAll();
            doc = QJsonDocument::fromJson(dt);
            ret = true;
        }

        return ret;
    }

    const QJsonDocument& get() const
    {
        return doc;
    }

    static std::pair<std::string, std::string> extractPairValues(const QJsonValue & val, const QString & name, const char delim = ',')
    {
        auto textVal = val[name].toString().toStdString();
        auto ind = textVal.find_first_of(delim);
        auto first = textVal.substr(0, ind);
        auto second = textVal.substr(++ind, textVal.size());

        return std::make_pair(first, second);
    }
};