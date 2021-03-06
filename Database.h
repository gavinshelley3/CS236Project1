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

    void insert(Relation r) {
        dataMap.insert({r.getName(), r});
    }

    unsigned int numRelations() {
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

    unsigned int size() {
        unsigned int count = 0;
        for (auto pairP : dataMap) {
            count += pairP.second.size();
        }
        return count;
    }
};


#endif //CS236PROJECT1_DATABASE_H
