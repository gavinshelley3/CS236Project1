#include <iostream>
#include <string>
#include <vector>
#include "Token.h"
#include "Scanner.h"
#include "Parser.h"
#include "DatalogProgram.h"
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
        while (!scanner.input.empty()) {
            Token currToken = scanner.scanToken(total);
            if (currToken.getType() != TokenType::COMMENT) {
                tokens.push_back(currToken);
            }
        }

        Parser parser = Parser(tokens);
        parser.parse();
        DatalogProgram DataProg = parser.getDatalogProgram();
        Database database;
        Interpreter interpreter(DataProg, database);
        interpreter.run();



//    Scheme scheme1( { "A", "B" } );
//    Scheme scheme2( { "B", "C" } );
//
//    Tuple tuple1( {"'1'", "'2'"} );
//    Tuple tuple2( {"'3'", "'4'"} );
//
//    Scheme scheme3( { "X", "Y" } );
//    Scheme scheme4( { "X", "Y", "Z" } );
//
//    Tuple tuple3( {"'1'", "'4'"} );
//    Tuple tuple4( {"'1'", "'2'", "'4'"} );
//
//
//    vector<pair<unsigned int, unsigned int>> overlap;
//    vector<unsigned int> uniqueColumns;
//
//    for (unsigned int i = 0; i < scheme4.size(); i++) {
//        bool isUnique = true;
//        for (unsigned int j = 0; j < scheme3.size(); j++) {
//            if (scheme4.at(i) == scheme3.at(j)) {
//                overlap.push_back({i,j});
//                isUnique = false;
//            }
//        }
//        if (isUnique) {
//            uniqueColumns.push_back(i);
//        }
//    }
//
//    Relation temp;
//    cout << temp.canJoin(tuple1, tuple2, overlap) << endl;
//    cout << temp.canJoin(tuple1, tuple2, overlap) << endl;
//    cout << temp.canJoin(tuple1, tuple4, overlap) << endl;
//    cout << temp.canJoin(tuple3, tuple4, overlap) << endl;
//
//
//    Relation studentRelation("students", Scheme( {"ID", "Name", "Major"} ));
//
//    vector<string> studentValues[] = {
//            {"'42'", "'Ann'", "'CS'"},
//            {"'64'", "'Ned'", "'EE'"},
//    };
//
//    for (auto& value : studentValues)
//        studentRelation.addTuple(Tuple(value));
//
////    studentRelation.join(studentRelation);
//
//
//
//    Relation courseRelation("courses", Scheme( {"ID", "Course"} ));
//
//    vector<string> courseValues[] = {
//            {"'42'", "'CS 100'"},
//            {"'32'", "'CS 232'"},
//    };
//
//    for (auto& value : courseValues)
//        courseRelation.addTuple(Tuple(value));
//
//    studentRelation.join(courseRelation);


    return 0;
}
