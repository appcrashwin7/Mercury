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
            auto aname = ArrName.toStdString();

            if (!(from[ArrName].isUndefined()) && from[ArrName].isArray())
            {
                const auto& dt = from[ArrName].toArray();
                for (int i = 0; i < dt.size(); i++)
                {
                    auto pair = JsonDataFile::extractPairValues(dt[i], "i");
                    to.emplace_back(StockUnit(Commodities::find(pair.first), std::stoi(pair.second)));
                }
            }
        };

        JsonDataFile dtFile;
        if (dtFile.load(Architecture::dataFile))
        {
            auto doc = dtFile.get();

            if (doc.isArray())
            {
                auto cost = StockT();
                auto input = StockT();
                auto out = StockT();

                for (int i = 0; i < doc.array().size(); i++)
                {
                    if (doc[i].isObject())
                    {
                        if (!(doc[i]["name"].isUndefined()))
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