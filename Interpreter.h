//
// Created by Gavin on 2/28/2022.
//

#ifndef CS236PROJECT1_INTERPRETER_H
#define CS236PROJECT1_INTERPRETER_H
#include "Database.h"
#include "DatalogProgram.h"

class Interpreter {
private:
    DatalogProgram program;
    Database database;

public:
    Interpreter(DatalogProgram program) : program(program) {}

    void run() {
//          Evaluate Schemes
    evalSchemes();
//          Evaluate Facts
    evalFacts();
//          Evaluate Rules

//          Evaluate Queries

    }

    void evalSchemes() {
        for (Predicate p : program.getSchemes()) {
            Relation newRelation;
            vector<string> contents;
            for (Parameter param : p.getParameters()) {
                contents.push_back(param.toString());
            }
            newRelation.setScheme(Scheme(contents));
            newRelation.setName(p.getName());
            database.insert(newRelation);
        }

//     For each scheme s in program.schemes
//          Make a new relation
//          Make a new scheme newScheme
//          Set name of relation to name of s
//          For each parameter p in s
//              Push-back p.toString into newScheme
//          Add newScheme into r
//          Add r to database
    }

    void evalFacts() {
        for (Predicate p : program.getFacts()) {
            Relation r = database.getRelationByRef(p.getName());
            vector<string> contents;
            for (Parameter param : p.getParameters()) {
                contents.push_back(param.toString());
            }
            r.addTuple(Tuple{contents});
        }
//     For each fact f in program.facts
//          Get relation r by reference from the database
//          Make a new tuple t
//          For each parameter p in f
//              Push_back p.toString into t
//          Add t into r
    }

    void evalRules() {
//          For each scheme s in program.schemes
//          Make a new relation
//          Make a new scheme newScheme
//          Set name of relation to name of s
//          For each parameter p in s
//          Add p.toString into newScheme
//          Add newScheme into r
//          Add r to database
    }


    void evalQueries() {
        for (Predicate p : program.getQueries()) {
            evaluatePredicate(p);
            Relation r = evaluatePredicate(p);
            cout << r.toString();
        }
//          For each scheme s in program.schemes
//          Make a new relation
//          Make a new scheme newScheme
//          Set name of relation to name of s
//          For each parameter p in s
//          Add p.toString into newScheme
//          Add newScheme into r
//          Add r to database
    }


    Relation evaluatePredicate(Predicate predicate) {
        Relation currRelation = database.getRelationCopy(predicate.getName());
        vector<unsigned int> colsToKeep;
        vector<string> names;
        for (unsigned int i = 0; i < predicate.getParameters().size(); i++) {
            Parameter currParem = predicate.getParameters().at(i);
            if (currParem.toString().at(0) == '\'') {
                currRelation = currRelation.select(i, currParem.toString());
            }
            else {
                bool seenBefore = false;
                //loop that checks through names and if currParam is found set seenBefore to true
                for (unsigned int j = 0; j < names.size(); j++) {
                    if (predicate.getParameters().at(i).toString() == names.at(j)) {
                        seenBefore = true;
                    }
                    if (seenBefore) {
                        currRelation = currRelation.select(i, j);
                    }
                    else {
                        colsToKeep.push_back(i);
                        names.push_back(currParem.toString());
                    }
                }
            }
        }
        //project(colToKeep)
        //rename(names)
        return currRelation;
    }
};


#endif //CS236PROJECT1_INTERPRETER_H
