//
// Created by Gavin on 2/8/2022.
//

#ifndef CS236PROJECT1_DATALOGPROGRAM_H
#define CS236PROJECT1_DATALOGPROGRAM_H
#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include "Predicate.h"
#include "Parameter.h"
#include "Rule.h"

class DatalogProgram {
public:
    vector<Predicate> schemes;
    vector<Predicate> facts;
    vector<Rule> rules;
    vector<Predicate> queries;
    DatalogProgram() { }
    DatalogProgram(const vector<Predicate> &schemes, const vector<Predicate> &facts, const vector<Rule> &rules,
                   const vector<Predicate> &queries) : schemes(schemes), facts(facts), rules(rules), queries(queries) {
        this->schemes = schemes;
        this->facts = facts;
        this->rules = rules;
        this->queries = queries;
    }

    void setSchemes(vector<Predicate> input) {
        schemes = input;
    }

    vector<Predicate> getSchemes() {
        return schemes;
    }

    void setFacts(vector<Predicate> input) {
        facts = input;
    }

    vector<Predicate> getFacts() {
        return facts;
    }

    void setQueries(vector<Predicate> input) {
        queries = input;
    }

    vector<Predicate> getQueries() {
        return queries;
    }

    void setRules(vector<Rule> input) {
        rules = input;
    }

    vector<Rule> getRules() {
        return rules;
    }

    set<string> getDomain() {
        set<string> domain;

        for (unsigned int i = 0; i < facts.size(); i++) {
            Predicate fact = facts.at(i);
            vector<Parameter> parameters = fact.getParameters();
            for (unsigned int j = 0; j < parameters.size(); j++) {
                Parameter parameter = parameters.at(j);
                string parameterValue = parameter.getValue();
                if (!(domain.find(parameterValue) != domain.end())) {
                    domain.insert(parameterValue);
                }
            }
        }
        return domain;
    }

    string toString() {
        stringstream ss;
        set domain = getDomain();
        ss << "Schemes(" << schemes.size() << "):" << endl;
        for (unsigned int i = 0; i < schemes.size(); i++) {
            ss << "  " << schemes.at(i).toString() << endl;
        }

        ss << "Facts(" << facts.size() << "):" << endl;
        for (unsigned int i = 0; i < facts.size(); i++) {
            ss << "  " << facts.at(i).toString() << "." << endl;
        }

        ss << "Rules(" << rules.size() << "):" << endl;
        for (unsigned int i = 0; i < rules.size(); i++) {
            ss << "  " << rules.at(i).toString() << "." << endl;
        }

        ss << "Queries(" << queries.size() << "):" << endl;
        for (unsigned int i = 0; i < queries.size(); i++) {
            ss << "  " << queries.at(i).toString() << "?" << endl;
        }

        ss << "Domain(" << domain.size() << "):" << endl;
        set<string>::iterator itr;
        for (itr = domain.begin(); itr != domain.end(); itr++) {
            ss << "  " << *itr << endl;
        }

        return ss.str();
    }

/*datalogProgram	->	SCHEMES COLON scheme schemeList
		                FACTS COLON factList
		                RULES COLON ruleList
		                QUERIES COLON query queryList
			            EOF

schemeList	    ->	    scheme schemeList | lambda
factList	    ->	    fact factList | lambda
ruleList	    ->	    rule ruleList | lambda
queryList 	    ->	    query queryList | lambda

scheme   	    -> 	    ID LEFT_PAREN ID idList RIGHT_PAREN
fact    	    ->	    ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
rule    	    ->	    headPredicate COLON_DASH predicate predicateList PERIOD
query	        ->      predicate Q_MARK

headPredicate	->	    ID LEFT_PAREN ID idList RIGHT_PAREN
predicate	    ->	    ID LEFT_PAREN parameter parameterList RIGHT_PAREN

predicateList	->	    COMMA predicate predicateList | lambda
parameterList	-> 	    COMMA parameter parameterList | lambda
stringList	    -> 	    COMMA STRING stringList | lambda
idList  	    -> 	    COMMA ID idList | lambda

parameter	    ->	    STRING | ID*/


};


#endif //CS236PROJECT1_DATALOGPROGRAM_H
