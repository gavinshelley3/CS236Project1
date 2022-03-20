//
// Created by Gavin on 2/28/2022.
//

#ifndef CS236PROJECT1_RELATION_H
#define CS236PROJECT1_RELATION_H
#include <vector>
#include <string>
#include <set>
#include <sstream>
#include "Tuple.h"
using namespace std;

class Relation
{

private:
    string name;
    Scheme scheme;
    set<Tuple> tuples;

public:
    Relation(const string &name, const Scheme &scheme, const set<Tuple> &tuples) : name(name), scheme(scheme), tuples(tuples) {}

    Relation(const string &name, const set<Tuple> &tuples) : name(name), tuples(tuples) {}

    Relation(const Scheme &scheme, const set<Tuple> &tuples) : scheme(scheme), tuples(tuples) {}

    Relation(const string &name, const Scheme &scheme): name(name), scheme(scheme) {}

    Relation(const string &name) : name(name) {}

    Relation() {}

    Relation select(unsigned int index, const string &value) const
    {
//        cout << "select 1" << endl;
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
//        cout << "select 2" << endl;
        Relation output(name, scheme);
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
//        cout << "project" << endl;
        Relation output(name);
        Scheme contentsScheme;
        for (Tuple tuple : tuples) {
            Tuple contentsTuple;
            for (unsigned int i = 0; i < colsToKeep.size(); i++) {
                if (colsToKeep.at(i) <= tuple.size()) {
                    contentsTuple.push_back(tuple.at(colsToKeep.at(i)));
                }
            }
            Tuple tempTuple(contentsTuple);
            output.addTuple(tempTuple);
        }
        for (unsigned int i = 0; i < colsToKeep.size(); i++) {
            if (colsToKeep.at(i) <= scheme.size()) {
                contentsScheme.push_back(scheme.at(colsToKeep.at(i)));
                Scheme tempScheme(contentsScheme);
                output.setScheme(tempScheme);
            }
        }
        return output;
    }

    Relation rename(vector<string> newNames)
    {
//        cout << "rename" << endl;
        Relation output(name, newNames, tuples);
        return output;
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
        for (Tuple tuple : tuples) {
            if (tuple.size() != 0) {
                out << "  " << tuple.toString(scheme) << endl;
            }
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
