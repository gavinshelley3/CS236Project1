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

class Relation {

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

    Relation select(unsigned int index, const string &value) const {
        Relation output(name, scheme);
        for (auto &tuple : tuples) {
            if (tuple.at(index) == value) {
                output.addTuple(tuple);
            }
        }
        return output;
    }

    Relation select(unsigned int index1, unsigned int index2) {
        Relation output(name, scheme);
        for (Tuple tuple : tuples) {
            if (tuple.at(index1) == tuple.at(index2)) {
                output.addTuple(tuple);
            }
        }
        return output;
    }

    Relation project(vector<unsigned int> colsToKeep) {
        Relation output(name);
        Scheme contentsScheme;
        for (unsigned int i = 0; i < colsToKeep.size(); i++) {
            if (colsToKeep.at(i) <= scheme.size()) {
                contentsScheme.push_back(scheme.at(colsToKeep.at(i)));
            }
        }
        output.setScheme(contentsScheme);
        for (Tuple tuple : tuples) {
            Tuple contentsTuple;
            for (unsigned int i = 0; i < colsToKeep.size(); i++) {
                if (colsToKeep.at(i) <= tuple.size()) {
                    contentsTuple.push_back(tuple.at(colsToKeep.at(i)));
                }
            }
            output.addTuple(contentsTuple);
        }
        return output;
    }

    Relation rename(vector<string> newNames) {
        Relation output(name, newNames, tuples);
        return output;
    }

    Relation natJoin(Relation r1, Relation r2) {
        Relation output;
        output.setName(r1.getName() + "+" + r2.getName());
        //Identify overlap in the schemes(header)
        vector<pair<unsigned int, unsigned int>> overlap;
        vector<unsigned int> uniqueColumns;


        for (unsigned int i = 0; i < r2.getScheme().size(); i++) {
            bool isUnique = true;
            for (unsigned int j = 0; j < r1.getScheme().size(); j++) {
                if (r2.getScheme().at(i) == r1.getScheme().at(j)) {
                    overlap.push_back({j,i});
                    isUnique = false;
                }
            }
            if (isUnique) {
                uniqueColumns.push_back(i);
            }
        }

        //Combine your schemes
        output.setScheme(combineSchemes(r1.getScheme(), r2.getScheme(), uniqueColumns));

        //For each tuple
        for (Tuple t1 : r1.getTuples()) {
            for (Tuple t2 : r2.getTuples()) {
                if (canJoin(t1, t2, overlap)) {
                    output.addTuple(combineTuples(t1, t2, uniqueColumns));
                }
            }
        }

                return output;
    }

    Scheme combineSchemes(const Scheme& s1, const Scheme& s2, vector<unsigned int> uniqueColumns) {
        Scheme output;
        for (unsigned int i = 0; i < s1.size(); i++) {
            output.push_back(s1.at(i));
        }

        for (unsigned int i = 0; i < uniqueColumns.size(); i++) {
            output.push_back(s2.at(uniqueColumns.at(i)));
        }
        return output;
    }

    bool canJoin(Tuple& t1, Tuple& t2, vector<pair<unsigned int, unsigned int>> &overlap) {
        for (pair<unsigned int, unsigned int> p : overlap) {
            if (t1.at(p.first) != t2.at(p.second)) {
                return false;
            }
        }
        return true;
    }

    Tuple combineTuples(Tuple& t1, Tuple& t2, vector<unsigned int> uniqueColumns) {
        Tuple output;
        for (unsigned int i = 0; i < t1.size(); i++) {
            output.push_back(t1.at(i));
        }

        for (unsigned int i = 0; i < uniqueColumns.size(); i++) {
            output.push_back(t2.at(uniqueColumns.at(i)));
        }
        return output;
    }

    void unionize(Relation toAdd) {
        if (this->scheme != toAdd.getScheme()) {
            throw "Cannot combine b/c the schemes are different!";
        }
        for (Tuple tuple : toAdd.getTuples()) {
            if (addTuple(tuple)) {
                if (tuple.size() > 0) {
                    cout << "  " << tuple.toString(scheme) << endl;
                }
            }
        }
    }

    bool addTuple(const Tuple &tuple) {
        return tuples.insert(tuple).second;
    }

    unsigned int size() {
        return tuples.size();
    }

    string toString() const {
        stringstream out;
        for (Tuple tuple : tuples) {
            if (tuple.size() != 0) {
                out << "  " << tuple.toString(scheme) << endl;
            }
        }
        return out.str();
    }

    const string &getName() const {
        return name;
    }

    void setName(const string &name) {
        Relation::name = name;
    }

    const Scheme &getScheme() const {
        return scheme;
    }

    void setScheme(const Scheme &scheme) {
        Relation::scheme = scheme;
    }

    const set<Tuple> &getTuples() const {
        return tuples;
    }
};

#endif //CS236PROJECT1_RELATION_H
