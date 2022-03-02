//
// Created by Gavin on 2/28/2022.
//

#ifndef CS236PROJECT1_RELATION_H
#define CS236PROJECT1_RELATION_H
#include <vector>
#include <string>
#include <set>
#include "Tuple.h"
//#include "Scheme.h"
using namespace std;

class Relation
{

private:
    string name;
    Scheme scheme;
    set<Tuple> tuples;

public:
    Relation(const string &name, const Scheme &scheme)
        : name(name), scheme(scheme) {}

    Relation() {}

    Relation select(unsigned int index, const string &value) const
    {
        Relation output(name, scheme);
        for (auto &tuple : tuples)
        {
            if (tuple.at(index) == value)
            {
                output.addTuple(tuple);
            }
        }
        return output;
    }

    Relation select(unsigned int index1, unsigned int index2)
    {
        Relation output;
        output.setName(name);
        output.setScheme(scheme);

        for (Tuple tuple : tuples)
        {
            if (tuple.at(index1) == tuple.at(index2))
            {
                output.addTuple(tuple);
            }
        }
        return output;
    }

    Relation project(vector<unsigned int> colsToKeep)
    {
        Relation output;
        output.setName(name);
        output.setScheme(scheme);

        for (unsigned int i; i < tuples.size(); i++)
        {
            for (unsigned int i; i < colsToKeep.size(); i++)
            {
                if (colsToKeep.at(i) == tuple.at(i))
                {
                    output.addTuple(tuple);
                }
            }
        }
        return output;
    }

    Relation rename(vector<string> newNames)
    {
        return Relation();
    }

    bool addTuple(const Tuple &tuple)
    {
        return tuples.insert(tuple).second;
    }

    unsigned int size()
    {
        return tuples.size();
    }

    string toString() const
    {
        stringstream out;
        for (auto &tuple : tuples)
            if (tuple.size() != 0)
            {
                out << "  " << tuple.toString(scheme) << endl;
            }
        return out.str();
    }

    const string &getName() const
    {
        return name;
    }

    void setName(const string &name)
    {
        Relation::name = name;
    }

    const Scheme &getScheme() const
    {
        return scheme;
    }

    void setScheme(const Scheme &scheme)
    {
        Relation::scheme = scheme;
    }
};

#endif //CS236PROJECT1_RELATION_H
