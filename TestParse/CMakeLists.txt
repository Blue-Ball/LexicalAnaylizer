cmake_minimum_required(VERSION 3.10)
project(lexical_analyzer)

set(CMAKE_CXX_STANDARD 14)

# include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

add_executable(${PROJECT_NAME} main.cpp TokenCodes.h Token.h Token.cpp LexicalAnalyzer.h LexicalAnalyzer.cpp)
