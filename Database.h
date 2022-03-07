//
// Created by Gavin on 2/28/2022.
//

#ifndef CS236PROJECT1_DATABASE_H
#define CS236PROJECT1_DATABASE_H
#include "Relation.h"
#include <map>

class Database {
    map<string, Relation> dataMap;

public:

    Relation& getRelationByRef(string relName) {
        return dataMap.at(relName);
    }

    Relation getRelationCopy(string relName) {
        return dataMap.at(relName);
    }

    void insert(string relName, Relation r) {
        dataMap.insert({relName, r});
    }

    unsigned int numTuples() {
        unsigned int i = 0;
        for (auto p : dataMap) {
            i += p.second.size();
        }
        return i;
    }


    string toString() {
        stringstream out;
        for (pair<string, Relation> relationEntry : dataMap) {
            out << relationEntry.first << endl;
            out << relationEntry.second.toString();
        }
        return out.str();
    }
};


#endif //CS236PROJECT1_DATABASE_H
