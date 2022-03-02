//
// Created by Gavin on 2/8/2022.
//

#ifndef CS236PROJECT1_RULE_H
#define CS236PROJECT1_RULE_H
#include <iostream>
#include <string>
#include <vector>
#include "Predicate.h"
#include "Parameter.h"

class Rule {
    //rule    	->	headPredicate COLON_DASH predicate predicateList PERIOD
public:
    Predicate HeadPredicate;
    vector<Predicate> predicates;
    Rule() {}


    void setHeadPredicate(Predicate head) {
        HeadPredicate = head;
    }

    Predicate getHeadPredicate() {
        return HeadPredicate;
    }

    void setPredicates(vector<Predicate> vectorPredicates)
    {
        predicates = vectorPredicates;
    }

    vector<Predicate> getPredicates() {
        return predicates;
    }

    void addValue(Predicate value) {
        predicates.push_back(value);
    }

    void addValue(string value) {
        predicates.push_back(Predicate(value));
    }

    string toString() {
        stringstream ss;
        ss << HeadPredicate.toString() << " :- ";
        for (unsigned int i = 0; i < predicates.size(); i++) {
            ss << predicates.at(i).toString();
            if (i != predicates.size() - 1) {
                ss << ",";
            }
        }
        return ss.str();
    }
};


#endif //CS236PROJECT1_RULE_H
