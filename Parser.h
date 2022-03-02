//
// Created by Gavin on 2/6/2022.
//

#ifndef CS236PROJECT1_PARSER_H
#define CS236PROJECT1_PARSER_H
#include <iostream>
#include <string>
#include <vector>
#include "Token.h"
#include "DatalogProgram.h"
#include "Predicate.h"
#include "Parameter.h"
#include "Rule.h"
using namespace std;

class Parser {
private:
    vector<Token> tokens;
    unsigned int index = 0;
    DatalogProgram DataProg = DatalogProgram();

    string match(TokenType type) {
        if (tokens.at(index).getType() == type) {
            //cout << tokens.at(index).toString() << endl;
            string returnVal = "";
            returnVal = tokens.at(index).getValue();
            index++;
            return returnVal;
        }
        else {
            throw tokens.at(index);
        }
        return "";
    }

public:
    Parser(const vector<Token>& tokens) : tokens(tokens) { }

    void parse() {
        if (tokens.at(index).getType() == TokenType::SCHEMES) {
            match(TokenType::SCHEMES);
            if (tokens.at(index).getType() == TokenType::COLON) {
                match(TokenType::COLON);
                vector<Predicate> Schemes;
                Schemes.push_back(scheme());
                schemeList(Schemes);
                DataProg.setSchemes(Schemes);
            }
            else {
                throw tokens.at(index);
            }
        }
        else if (tokens.at(index).getType() != TokenType::SCHEMES){
            throw tokens.at(index);
        }

        if (tokens.at(index).getType() == TokenType::FACTS) {
            match(TokenType::FACTS);
            if (tokens.at(index).getType() == TokenType::COLON) {
                match(TokenType::COLON);
                vector<Predicate> Facts;
                factList(Facts);
                DataProg.setFacts(Facts);
            }
            else {
                throw tokens.at(index);
            }
        }
        else {
            throw tokens.at(index);
        }

        if (tokens.at(index).getType() == TokenType::RULES) {
            match(TokenType::RULES);
            if (tokens.at(index).getType() == TokenType::COLON) {
                match(TokenType::COLON);
                vector <Rule> Rules;
                ruleList(Rules);
                DataProg.setRules(Rules);
            }
            else {
                throw tokens.at(index);
            }
        }
        else {
            throw tokens.at(index);
        }

        if (tokens.at(index).getType() == TokenType::QUERIES) {
            match(TokenType::QUERIES);
            if (tokens.at(index).getType() == TokenType::COLON) {
                match(TokenType::COLON);
                vector <Predicate> Queries;
                Queries.push_back(query());
                queryList(Queries);
                DataProg.setQueries(Queries);
            }
            else {
                throw tokens.at(index);
            }
        }
        else {
            throw tokens.at(index);
        }
        match(TokenType::E_O_F);
    }


    //scheme -> ID LEFT_PAREN ID idList RIGHT_PAREN
    Predicate scheme() {
        if (tokens.at(index).getType() == TokenType::ID) {
            Predicate Scheme(match(TokenType::ID));
            match(TokenType::LEFT_PAREN);
            Scheme.addValue(match(TokenType::ID));
            idList(Scheme);
            match(TokenType::RIGHT_PAREN);
            return Scheme;
        }
        else {
            throw tokens.at(index);
        }
    }

    //schemeList	->	scheme schemeList | lambda
    void schemeList(vector<Predicate> &Schemes) {
        if (tokens.at(index).getType() == TokenType::ID) {
            Schemes.push_back(scheme());
            schemeList(Schemes);
        }
        else {
            return;
        }
    }


    //fact    	->	ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
    Predicate fact() {
        if(tokens.at(index).getType() == TokenType::ID) {
            Predicate Fact(match(TokenType::ID));
            match(TokenType::LEFT_PAREN);
            Fact.addValue(match(TokenType::STRING));
            stringList(Fact);
            match(TokenType::RIGHT_PAREN);
            match(TokenType::PERIOD);
            return Fact;
        }
        else {
            throw tokens.at(index);
        }
    }

    //factList	->	fact factList | lambda
    void factList(vector<Predicate> &Facts) {
        if (tokens.at(index).getType() == TokenType::ID) {
            Facts.push_back(fact());
            factList(Facts);
        }
        else {
            return;
        }
    }


    //rule    	->	headPredicate COLON_DASH predicate predicateList PERIOD
    Rule rule() {
        if(tokens.at(index).getType() == TokenType::ID) {
            //cout << "---> Rule" << endl;
            vector<Predicate> vectorPredicates;
            Predicate HeadPredicate = headPredicate();
            match(TokenType::COLON_DASH);
            //predicate	->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN
            Predicate PredicateRule;
            vectorPredicates.push_back(predicates());
            predicateList(vectorPredicates);
            match(TokenType::PERIOD);
            Rule Rules;
            Rules.setHeadPredicate(HeadPredicate);
            Rules.setPredicates(vectorPredicates);
            //cout << "<--- Rule" << endl;
            return Rules;
        }
        else {
            throw tokens.at(index);
        }
    }

    //ruleList	->	rule ruleList | lambda
    void ruleList(vector<Rule> &Rules) {
        if (tokens.at(index).getType() == TokenType::ID) {
            Rules.push_back(rule());
            ruleList(Rules);
        }
        else {
            return;
        }
    }


    //query	    ->      predicate Q_MARK
    Predicate query() {
        if(tokens.at(index).getType() == TokenType::ID) {
            Predicate query = predicates();
            match(TokenType::Q_MARK);
            return query;
        }
        else {
            throw tokens.at(index);
        }
    }

    //queryList	->	query queryList | lambda
    void queryList(vector<Predicate> &Queries) {
        if (tokens.at(index).getType() == TokenType::ID) {
            Queries.push_back(query());
            queryList(Queries);
        }
        else {
            return;
        }
    }


    //headPredicate	->	ID LEFT_PAREN ID idList RIGHT_PAREN
    Predicate headPredicate() {
        if(tokens.at(index).getType() == TokenType::ID) {
            Predicate HeadPredicate(match(TokenType::ID));
            match(TokenType::LEFT_PAREN);
            HeadPredicate.addValue(match(TokenType::ID));
            idList(HeadPredicate);
            match(TokenType::RIGHT_PAREN);
            return HeadPredicate;
        }
        else {
            throw tokens.at(index);
        }
    }

    //predicate	->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN
    Predicate predicates() {
        if (tokens.at(index).getType() == TokenType::ID) {
            Predicate PredicateRule(match(TokenType::ID));
            match(TokenType::LEFT_PAREN);
            PredicateRule.addValue(parameter());
            parameterList(PredicateRule);
            match(TokenType::RIGHT_PAREN);
            return PredicateRule;
        }
        else {
            throw tokens.at(index);
        }
    }

    //predicateList	->	COMMA predicate predicateList | lambda
    void predicateList(vector<Predicate> &Predicates) {
        if(tokens.at(index).getType() == TokenType::COMMA) {
            match(TokenType::COMMA);
            Predicates.push_back(predicates());
            predicateList(Predicates);
        }
        else {
            return;
        }
    }


    //parameter	->	STRING | ID
    Parameter parameter() {
        if (tokens.at(index).getType() == TokenType::STRING || tokens.at(index).getType() == TokenType::ID) {
            Parameter returnVal;
            returnVal.setValue(tokens.at(index).getValue());
            index++;
            return returnVal;
        }
        else {
            throw tokens.at(index);
        }
    }

    //parameterList	-> 	COMMA parameter parameterList | lambda
    void parameterList(Predicate &Parameters) {
        if(tokens.at(index).getType() == TokenType::COMMA) {
            match(TokenType::COMMA);
            Parameters.addValue(parameter());
            parameterList(Parameters);
        }
        else {
            return;
        }
    }

    //stringList	-> 	COMMA STRING stringList | lambda
    void stringList(Predicate& P) {
        if(tokens.at(index).getType() == TokenType::COMMA) {
            match(TokenType::COMMA);
            P.addValue(match(TokenType::STRING));
            stringList(P);
        }
        else {
            return;
        }
    }

    //idList -> COMMA ID idList | lambda
    void idList(Predicate& P) {
        if(tokens.at(index).getType() == TokenType::COMMA) {
            match(TokenType::COMMA);
            P.addValue(match(TokenType::ID));
            idList(P);
        }
        else {
            return;
        }
    }

    DatalogProgram getDatalogProgram() {
        return DataProg;
    }
};


#endif //CS236PROJECT1_PARSER_H
