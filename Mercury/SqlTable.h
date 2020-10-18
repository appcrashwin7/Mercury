#pragma once

#include <qstring.h>
#include <vector>
#include <tuple>

//vec < name of var, type of var, var can't be null>
using SqlTableVariables = std::vector<std::tuple<QString, QString, bool>>;

class SqlTable
{
    QString name;
    QString namePostfix;

    SqlTableVariables vars;

    QString varsNamesChainStr;
    QString varsValChainStr;
    QString varsChainStr;

    bool isEmpty() const
    {
        return name.isEmpty() || vars.empty();
    }
    void genVarsChain()
    {
        auto concatVar = [](const std::tuple<QString, QString, bool>& v)->QString
        {
            QString ret;

            ret += std::get<0>(v);
            ret += ' ';
            ret += std::get<1>(v);

            if (std::get<2>(v))
                ret += " NOT NULL";

            return ret;
        };

        varsChainStr += '(';

        if (vars.size() == 1)
        {
            varsChainStr += concatVar(vars[0]) + ')';
        }
        else
        {
            auto end = vars.end() - 1;
            for (auto t = vars.begin(); t != end; t++)
            {
                varsChainStr += concatVar(*t) + ',';
            }

            varsChainStr += concatVar(vars.back()) + ")";
        }
    }
    void genVarsNamesChain()
    {
        QString valBind = " VALUES (";

        if (vars.size() == 1)
        {
            varsNamesChainStr += std::get<0>(vars[0]);
            valBind += "?)";
        }
        else
        {
            auto end = vars.end() - 1;
            for (auto t = vars.begin(); t != end; t++)
            {
                varsNamesChainStr += std::get<0>(*t) + ',';
                valBind += "?,";
            }

            varsNamesChainStr += std::get<0>(*end);
            valBind += +"?)";
        }
        varsValChainStr += valBind;
    }
public:
    SqlTable() = default;
    SqlTable(QString tableName, SqlTableVariables tableVariables)
        :name(std::move(tableName)), vars(std::move(tableVariables))
    {
        genVarsChain();
        genVarsNamesChain();
    };
    ~SqlTable() = default;

    QString getName() const
    {
        return name;
    }
    void setName(QString newName)
    {
        name = std::move(newName);
    }

    QString getNamePostfix() const
    {
        return namePostfix;
    }
    void setNamePostfix(QString newPostfix)
    {
        namePostfix = std::move(newPostfix);
    }
    void setNamePostfix(std::vector<size_t> ids)
    {
        namePostfix.clear();
        if (ids.empty())
        {
            namePostfix = "";
            return;
        }

        for (auto i : ids)
        {
            namePostfix += "_";
            namePostfix += QString::number(i);
        }
    }

    const SqlTableVariables& getTableVariables() const
    {
        return vars;
    }
    void setTableVariables(SqlTableVariables newVars)
    {
        vars = std::move(newVars);
        if (!vars.empty())
        {
            genVarsChain();
            genVarsNamesChain();
        }
    }

    QString getCreateQueryStr() const
    {
        if (isEmpty())
           return "";

        return "CREATE TABLE IF NOT EXISTS " + name +
            namePostfix + varsChainStr;
    }
    QString getDeleteQueryStr() const
    {
        if (isEmpty())
            return "";

        return "DELETE FROM " + name + namePostfix;
    }
    QString getInsertQueryStr() const
    {
        if (isEmpty())
            return "";

        return "INSERT INTO " + name +
            namePostfix + "(" + varsNamesChainStr + ")" +
            varsValChainStr;
    }
    QString getSelectQueryStr() const
    {
        if (isEmpty())
            return "";

        return "SELECT " + varsNamesChainStr +
            " FROM " + name + namePostfix;
    }
};