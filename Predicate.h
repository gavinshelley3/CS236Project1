//
// Created by Gavin on 2/8/2022.
//

#ifndef CS236PROJECT1_PREDICATE_H
#define CS236PROJECT1_PREDICATE_H
#include <iostream>
#include <string>
#include <vector>
#include "Parameter.h"

class Predicate {
    //predicate	->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN
public:
    string name;
    vector<Parameter> parameters;
    Predicate() {}
    Predicate(const string &name) : name(name) {
        this->name = name;
        this->parameters = parameters;
    }

    void addValue(Parameter value) {
        parameters.push_back(value);
    }

    vector<Parameter> getParameters() {
        return parameters;
    }

    string toString() {
        stringstream ss;
        ss << name << "(";
        for (unsigned int i = 0; i < parameters.size(); i++) {
            ss << parameters.at(i).toString();
            if (i != parameters.size() - 1) {
                ss << ",";
            }
        }
        ss << ")";
        return ss.str();
        }

    const string &getName() const {
        return name;
    }

    void setName(const string &name) {
        Predicate::name = name;
    }

    void setParameters(const vector<Parameter> &parameters) {
        Predicate::parameters = parameters;
    }
};


#endif //CS236PROJECT1_PREDICATE_H
