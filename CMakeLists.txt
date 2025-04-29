cmake_minimum_required(VERSION 3.27)


project(Interpreter CXX)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)


set(LEXER_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/lexer.l")
set(PARSER_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/parser.y")


set(LEXER_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}")
set(PARSER_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}")


flex_target(LEXER ${LEXER_SOURCE} ${LEXER_OUTPUT_DIR}/lexer.cpp
           DEFINES_FILE ${LEXER_OUTPUT_DIR}/lexer.hpp)
bison_target(PARSER ${PARSER_SOURCE} ${PARSER_OUTPUT_DIR}/parser.tab.cpp
            DEFINES_FILE ${PARSER_OUTPUT_DIR}/parser.tab.hpp
            COMPILE_FLAGS "-v --language=c++ -Wconflicts-sr -Wcounterexamples")

add_flex_bison_dependency(LEXER PARSER)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

# Create executable
add_executable(interpreter
    ${BISON_PARSER_OUTPUTS}
    ${FLEX_LEXER_OUTPUTS}
    driver.cpp
    interpreter.cpp
    operation.cpp
    expression.cpp
    statement.cpp
    visitor.cpp
    exception.cpp
)

set_target_properties(interpreter PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)