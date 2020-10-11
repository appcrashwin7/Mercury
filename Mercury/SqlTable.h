#pragma once

#include <qstring.h>
#include <vector>
#include <tuple>

class SqlTable
{
    QString name;
    std::vector<std::tuple<QString, QString, bool>> vars;

    bool isEmpty() const
    {
        return name.isEmpty() || vars.empty();
    }
public:
    SqlTable() = default;
    SqlTable(QString tableName, std::vector<std::tuple<QString, QString, bool>> tableVariables)
        :name(std::move(tableName)), vars(std::move(tableVariables))
    {};
    ~SqlTable() = default;

    QString getName() const
    {
        return name;
    }
    void setName(QString newName)
    {
        name = std::move(newName);
    }

    //Return vec<name of var, type of var, var can't be null>
    std::vector<std::tuple<QString, QString, bool>>& getTableVariables()
    {
        return vars;
    }

    QString getCreateQueryStr() const
    {
        QString ret;
        if (isEmpty())
        {
            return ret;
        }

        auto concatVar = [](const std::tuple<QString, QString, bool>& v)->QString
        {
            QString ret;

            ret += std::get<0>(v);
            ret += ' ';
            ret += std::get<1>(v);

            if (std::get<2>(v))
                ret += " NOT NULL";
        };

        ret += "CREATE TABLE IF NOT EXISTS ";
        ret += name;
        ret += '(';

        if (vars.size() == 1)
        {
            ret += concatVar(vars[0]) + ')';
        }
        else
        {
            auto end = vars.end() - 1;
            for (auto t = vars.begin(); t != end; t++)
            {
                ret += concatVar(*t) + ',';
            }

            ret += concatVar(vars.back()) + ")";
        }

        return ret;
    }
    QString getDeleteQueryStr() const
    {
        QString ret;
        if (isEmpty())
            return ret;

        return QString("DELETE FROM ") + name;
    }
    QString getInsertQueryStr() const
    {
        QString ret;
        if (isEmpty())
            return ret;

        ret += "INSERT INTO ";
        ret += name + '(';
        QString valBind = " VALUES (";

        if (vars.size() == 1)
        {
            ret += std::get<0>(vars[0]);
            valBind += "?)";
            ret += valBind;
        }
        else
        {
            auto end = vars.end() - 1;
            for (auto t = vars.begin(); t != end; t++)
            {
                ret += std::get<0>(*t) + ',';
                valBind += "?,";
            }

            ret += std::get<0>(*end) + ')';
            ret += valBind + "?)";
        }
        return ret;
    }
    QString getSelectQueryStr() const
    {
        QString ret;
        if (isEmpty())
            return ret;

        ret += "SELECT ";


        if (vars.size() == 1)
        {
            ret += std::get<0>(vars[0]);
        }
        else
        {
            auto end = vars.end() - 1;
            for (auto t = vars.begin(); t != end; t++)
            {
                ret += std::get<0>(*t) + ", ";
            }
            ret += std::get<0>(*end);
        }
        ret += " FROM " + name;

        return ret;
    }
};