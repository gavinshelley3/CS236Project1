#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cctype>
#include <cstdio>
#include "Token.h"
#include "Scanner.h"
#include "Parser.h"
#include "DatalogProgram.h"
#include "Rule.h"
#include "Predicate.h"
#include "Parameter.h"
#include "Scheme.h"
#include "Tuple.h"
#include "Relation.h"
#include "Database.h"
#include "Interpreter.h"
using namespace std;

int main(int argc, char *argv[])
{
        // check command line arguments
        if (argc != 2) {
            cout << "usage: " << argv[0] << " input_file" << endl;
            return 1;
        }

        // open file
        string fileName = argv[1];
        ifstream ifs (fileName);
        //    cout << fileName << endl;
        ifs.open(fileName);
        if (!ifs.is_open()) {
            cout << "File " << fileName << " could not be found or opened." << endl;
            return 1;
        }
        else {
            //		cout << "File opened" << endl;
        }

        string scanLines;
        stringstream ss;
        ss << ifs.rdbuf(); // reading data
        scanLines = ss.str();


        Scanner scanner = scanLines;
        vector<Token> tokens;


        int total = 0;
        if (scanner.input.empty()) {
            //        cout << scanner.scanToken(total).toString() << endl;
            //        total ++;
        }
        while (!scanner.input.empty()) {
            Token currToken = scanner.scanToken(total);
            if (currToken.getType() != TokenType::COMMENT) {
                tokens.push_back(currToken);
            }
        }

        Parser parser = Parser(tokens);

        try {
            parser.parse();
            DatalogProgram DataProg = parser.getDatalogProgram();
//            cout << /*"Success!\n" <<*/ DataProg.toString();
            Database database;
            Interpreter interpreter(DataProg, database);
            interpreter.run();
            interpreter.print();
        }
        catch (Token errorToken) {
            cout << /*"Failure!\n  " <<*/ errorToken.toString() << endl;
        }



//    vector<string> names = {"ID", "Name", "Major"};
//
//    Scheme scheme(names);
//
//    Relation relation("student", scheme);
//
//    vector<string> values[] = {
//        {"'16'", "'Ann'", "'CS'"},
//        {"'32'", "'Bob'", "'CS'"},
//        {"'64'", "'Ned'", "'EE'"},
//        {"'52'", "'Jim'", "'EE'"},
//    };
//
//    for (auto &value : values)
//    {
//        Tuple tuple(value);
//        cout << tuple.toString(scheme) << endl;
//        relation.addTuple(tuple);
//    }
//
//    cout << "relation:" << endl;
//    cout << relation.toString();
//
//    Relation result = relation.select(2, "'CS'");
//    vector<unsigned int> projectVec = {{0},{2}};
//    Relation projection = relation.project(projectVec);
//    Relation projectionSelect = result.project(projectVec);
//    Relation rename = relation.rename({{"'Number'"}, {"'Student'"}, {"'Studying:'"}});
//
//
//
//    cout << "select Major='CS' result:" << endl;
//    cout << result.toString();
//    cout << "project {0,1} result:" << endl;
//    cout << projection.toString();
//    cout << "projectSelect {0,1} result:" << endl;
//    cout << projectionSelect.toString();
//    cout << "rename result:" << endl;
//    cout << rename.toString();
//
//    cout << Database.toString();
    return 0;
}
