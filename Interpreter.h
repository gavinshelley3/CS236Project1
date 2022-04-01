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

    Interpreter(const Database &database) : database(database) {}

    Interpreter(const DatalogProgram &program, const Database &database) : program(program), database(database) {}

    void run() {
//          Evaluate Schemes
    evalSchemes();
//          Evaluate Facts
    evalFacts();
//          Evaluate Rules
    evalRules();
//          Evaluate Queries
    evalQueries();
    }


    void evalSchemes() {
        for (auto &scheme : program.getSchemes()) {
            Relation newRelation(scheme.getName(), toVector(scheme.getParameters()));
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
        for (auto &tuple : program.getFacts()) {
            Relation &r = database.getRelationByRef(tuple.getName());
            vector<Parameter> params = tuple.getParameters();
            Tuple tup = Tuple(toVector(params));
            r.addTuple(tup);
            database.insert(r);
        }
//     For each fact f in program.facts
//          Get relation r by reference from the database
//          Make a new tuple t
//          For each parameter p in f
//              Push_back p.toString into t
//          Add t into r
    }

    void evalRules() {
        evalRuleList(program.getRules());
        unsigned int before = 0;
        unsigned int after = 0;
        do {
            before = database.size();
            singlePass(program.getRules());
            after = database.size();
        }
        while(before != after);
    }


    void evalQueries() {
        for (auto &query : program.getQueries()) {
            Relation queryEval = evaluatePredicate(query);
//            cout << query.toString() << "? ";
//            if (queryEval.size() > 0) {
//                cout << "Yes(" << queryEval.size() << ")" << endl;
//            }                                                                         //Project 3 Print Out
//            else {
//                cout << "No" << endl;
//            }
//            cout << queryEval.toString();
        }
    }


    Relation evaluatePredicate(Predicate predicate) {
        Relation currRelation = database.getRelationCopy(predicate.getName());
        vector<unsigned int> colsToKeep;
        vector<string> names;
        for (unsigned int i = 0; i < predicate.getParameters().size(); i++) {
            Parameter currParem = predicate.getParameters().at(i);
            if (currParem.at(0) == '\'') {
                currRelation = currRelation.select(i, currParem.getValue());
            } else {
                bool seenBefore = false;
                for (unsigned int j = 0; j < names.size(); j++) {
                    if (currParem.getValue() == names.at(j)) {
                        seenBefore = true;
                    }
                }
                for (unsigned int k = 0; k < predicate.getParameters().size(); k++) {
                    if (currParem.getValue() == predicate.getParameters().at(k).getValue()) {
                        currRelation = currRelation.select(i, k);
                    }
                }
                if (!seenBefore) {
                    colsToKeep.push_back(i);
                    names.push_back(currParem.getValue());
                }
            }
        }
        currRelation = currRelation.project(colsToKeep);
        currRelation = currRelation.rename(names);
        return currRelation;
    }

    void evalRuleListFixedPointAlg(vector<Rule> rules) {

    }

    void evalRuleList(vector<Rule> rules) {
        for (Rule currRule : rules) {
            vector<Relation> bodyRelations;
            for (Predicate currPredicate : currRule.getPredicates()) {
                Relation currRelation = evaluatePredicate(currPredicate);
                bodyRelations.push_back(currRelation);
            }
            Relation resultRelation = bodyRelations.at(0);
            for (unsigned int i = 1; i < bodyRelations.size(); i++) {
                resultRelation = resultRelation.natJoin(resultRelation, bodyRelations.at(i));
            }

            //Project
            string name = currRule.getHeadPredicate().getName();
            resultRelation = resultRelation.rename(database.getRelationByRef(name).getScheme());

            database.getRelationByRef(name).unionize(resultRelation);
        }
    }

    void singlePass(vector<Rule> rules) {
        for (Rule currRule : rules) {
            //join all the body predicates together in a single rule
                //for each body predicate p call evaluatePredicate(p)
                //join all those together into relation currRelation

            //project()
                //remove unused variables based on the head predicate
                //loop that loops through all parameters of the head predicate and matches it to each individual ID in the scheme of the result/currRule
                //project on vector of indexes that are the same
            //rename()
                //rename to have data that the original table had in the database
                    //go to database and get relation out based on name of head predicate
                    //rename to what that name was
                //take every tuple and put it into database and if tuple was unique print it out
            //unionize()
                //print current Tuple if and only if it is unique
        }
    }

    vector<string> toVector(vector<Parameter> vectorOfParameters) {
        vector<string> vecParam;
        for (unsigned int i = 0; i < vectorOfParameters.size(); i++)
        {
            vecParam.push_back(vectorOfParameters.at(i).getValue());
        }
        return vecParam;
    }

    DatalogProgram getDatalogProgram() {
        return program;
    }

    Database getDatabase() {
        return database;
    }
};


#endif //CS236PROJECT1_INTERPRETER_H
