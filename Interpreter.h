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
//          Print
    print();
//          Evaluate Queries
//        for (Predicate p : program.getQueries())
//        {
//            Relation r = evalPredicate(p);
//            cout << r.toString();
//        }
    evalQueries();
    }

    vector<string> toVector(vector<Parameter> vectorOfParameters)
    {
        vector<string> vecParam;
        for (unsigned int i = 0; i < vectorOfParameters.size(); i++)
        {
            vecParam.push_back(vectorOfParameters.at(i).getValue());
        }
        return vecParam;
    }


    void evalSchemes() {
        for (auto &scheme : program.getSchemes()) {
            Relation newRelation(scheme.getName(), toVector(scheme.getParameters()));
            database.insert(newRelation);
        }

//        for (Predicate p : program.getSchemes()) {
//            Relation newRelation;
//            vector<string> contents;
//            for (Parameter param : p.getParameters()) {
//                contents.push_back(param.getValue());
////                cout << param.toString() << endl;
//            }
//            newRelation.setScheme(Scheme(contents));
//            newRelation.setName(p.getName());
//            database.insert(newRelation);
//        }
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
        }


//        for (Predicate p : program.getFacts()) {
//            Relation r = database.getRelationByRef(p.getName());
//            vector<string> contents;
//            for (Parameter param : p.getParameters()) {
//                contents.push_back(param.getValue());
////                cout << param.toString() << endl;
//            }
//            r.addTuple(Tuple(contents));
////            cout << r.toString() << endl;
//            database.insert(r);
//        }
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
        for (auto &query : program.getQueries()) {
            Relation queryEval = evaluatePredicate(query);
            database.insert(queryEval);
            cout << query.toString() << "? ";
            if (queryEval.size() > 0) {
                cout << "Yes(" << queryEval.size() << ")" << endl;
            }
            else {
                cout << "No" << endl;
            }
            cout << queryEval.toString();
        }



//        for (Predicate p : program.getQueries()) {
////            cout << p.toString() << "? " << endl;
//            Relation r = evaluatePredicate(p);
////            cout << "queries " << r.toString() << " queries" << endl;
////            Relation currentRelation = database.getRelationCopy(p.getName());
//            database.insert(r);
//
//        }
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
                currRelation = currRelation.select(i, currParem.getValue());
            } else {
                for (unsigned int j = 0; j < predicate.getParameters().size(); j++) {
                    if (currParem.getValue() == predicate.getParameters().at(j).getValue()) {
                        currRelation = currRelation.select(i, j);
                    }
                }
            }
        }
        vector<unsigned int> newColsToKeep;
        vector<string> newNames;
        for (unsigned int i = 0; i < predicate.getParameters().size(); i++) {
            bool seenBefore = false;
            Parameter value = predicate.getParameters().at(i);
            if (predicate.getParameters().at(i).at(0) != '\'') {
                //loop that checks through names and if currParam is found set seenBefore to true
                for (unsigned int j = 0; j < names.size(); j++) {
                    if (value.getValue() == newNames.at(j)) {
                        seenBefore = true;
                    }
//                    if (predicate.getParameters().at(j).getValue() == currParem.getValue()) {
//                        currRelation = currRelation.select(i,j);
//                    }
//                    if (predicate.getParameters().at(i).getValue() == names.at(j)) {
//                        seenBefore = true;
//                    }
                    if (!seenBefore) {
                        newColsToKeep.push_back(i);
                        newNames.push_back(predicate.getParameters().at(i).getValue());
//                        colsToKeep.push_back(i);
//                        names.push_back(predicate.getParameters().at(i).getValue());
//                        currRelation = currRelation.select(i, newColsToKeep.at(j));
                    }
//                    else {
//                        colsToKeep.push_back(i);
//                        names.push_back(predicate.getParameters().at(i).getValue());
////                        currRelation = currRelation.select(i, colsToKeep.at(j));
////                        colsToKeep.push_back(i);
////                        names.push_back(currParem.toString());
//                    }
                }
            }
        }
//        colsToKeep = {0, 1};
        //project(colToKeep)
        currRelation = currRelation.project(newColsToKeep);
        //rename(names)
//        currRelation = currRelation.rename(names);
        return currRelation;
    }

    Relation evalPredicate(Predicate predicate)
    {
        Relation currentRelation = database.getRelationCopy(predicate.getName());
        vector<unsigned int> columnsToKeep;
        vector<string> names;

        for (unsigned int i = 0; i < predicate.getParameters().size(); i++)
        {
            Parameter currentParameter = predicate.getParameters().at(i);

            if (currentParameter.toString().at(0) == '\'')
            {
                currentRelation = currentRelation.select(i, currentParameter.toString());
            }
            else
            {
                bool seenBefore = false;
                int indexFound = 0;
                // Loop that checks through names and if currParam is found set seenBefore to true, set index found to index at which it is seen

                if (seenBefore)
                {
                    currentRelation = currentRelation.select(i, columnsToKeep.at(indexFound)); // FOR SELECT WITH TWO INTS
                }

                else
                {

                    columnsToKeep.push_back(i);
                    names.push_back(currentParameter.toString());
                }
            }
        }

        // project(columnsToKeep);
        // rename(names);
        return currentRelation;
    }

    DatalogProgram getDatalogProgram() {
        return program;
    }

    Database getDatabase() {
        return database;
    }

    string print() {
        stringstream ss;
//        ss << database.toString();
//        ss << "Queries(" << queries.size() << "):" << endl;
//        for (unsigned int i = 0; i < database.numRelations(); i++) {
//            for (auto &database : database.numRelations()) {
//
////            Relation numQueries = evaluatePredicate();
//            if (database.numRelations() > 0) {
//                ss << database.at(database.numRelations()).toString() << "? ";// << endl;
//                ss << "";
//            }
//        }
        return ss.str();


//        Relation queryEvaluated = database.evaluateQuery(query);
//
//        cout << query.toString() << "? ";
//
//        if (queryEvaluated.size() > 0)
//        {
//            cout << "Yes(" << queryEvaluated.size() << ")" << endl;
//        }
//
//        else
//        {
//            cout << "No" << endl;
//        }
//
//        cout << queryEvaluated.toString();
//    }
    }

};


#endif //CS236PROJECT1_INTERPRETER_H
