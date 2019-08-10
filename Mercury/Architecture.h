#pragma once

#include "IndustryBuilding.h"

class Architecture
{
    static inline std::vector<IndustryBuilding> dt;
    static inline const QString dataFile = "Buildings.json";

public:
    Architecture() = default;
    ~Architecture() = default;

    static void load()
    {
        auto extractArray = [&](const QJsonValue& from, const QString& ArrName, StockT& to)
        {
            if (from[ArrName].isArray())
            {
                const auto& dt = from[ArrName].toArray();
                for (int i = 0; i < dt.size(); i++)
                {
                    auto textVal = dt[i]["i"].toString().toStdString();
                    auto ind = textVal.find_first_of(',');
                    auto prodName = textVal.substr(0, ind);
                    auto am = std::stoi(textVal.substr(++ind, textVal.size()));

                    to.emplace_back(StockUnit(Commodities::find(prodName), am));
                }
            }
        };

        QFile dtFile(Architecture::dataFile);
        if (dtFile.open(QIODevice::ReadOnly))
        {
            QByteArray dtFileBArr = dtFile.readAll();
            QJsonDocument doc(QJsonDocument::fromJson(dtFileBArr));
            if (doc.isArray())
            {
                auto cost = StockT();
                auto input = StockT();
                auto out = StockT();

                for (int i = 0; i < doc.array().size(); i++)
                {
                    if (doc[i].isObject())
                    {
                        if (!(doc[i]["name"].isNull()))
                        {
                            auto name = doc[i]["name"].toString();
                            extractArray(doc[i], "cost", cost);
                            extractArray(doc[i], "input", input);
                            extractArray(doc[i], "output", out);

                            auto energy = units::megawatt * doc[i]["energyNet"].toInt(-1);
                            auto pop = static_cast<uint32_t>(doc[i]["populationSupport"].toInt());
                            auto infr = doc[i]["infrastructureSupport"].toInt(-1);
                            auto mine = static_cast<uint32_t>(doc[i]["miningOutput"].toInt());
                            auto constr = static_cast<uint32_t>(doc[i]["constructionCap"].toInt());

                            dt.emplace_back(IndustryBuilding(name.toStdString(), input, out, cost,
                                energy, infr, pop, mine, constr));

                            cost.clear();
                            input.clear();
                            out.clear();
                        }
                    }
                }
            }
        }
    }

    static const std::vector<IndustryBuilding> & get()
    {
        return dt;
    }
};