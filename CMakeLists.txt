cmake_minimum_required(VERSION 3.20)
project(CS236Project1)

set(CMAKE_CXX_STANDARD 17)

add_executable(CS236Project1 main.cpp Token.h Scanner.h Parser.h DatalogProgram.h Rule.h Predicate.h Parameter.h Scheme.h Tuple.h Relation.h Database.h Interpreter.h)
