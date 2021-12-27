
#include <lalr/ParserStateMachine.hpp>
#include <lalr/ParserState.hpp>
#include <lalr/ParserTransition.hpp>
#include <lalr/ParserSymbol.hpp>
#include <lalr/ParserAction.hpp>
#include <lalr/LexerStateMachine.hpp>
#include <lalr/LexerState.hpp>
#include <lalr/LexerTransition.hpp>
#include <lalr/LexerAction.hpp>

namespace
{

using namespace lalr;

extern const LexerAction lexer_actions [];
extern const LexerTransition lexer_transitions [];
extern const LexerState lexer_states [];
extern const LexerAction whitespace_lexer_actions [];
extern const LexerTransition whitespace_lexer_transitions [];
extern const LexerState whitespace_lexer_states [];
extern const ParserAction actions [];
extern const ParserSymbol symbols [];
extern const ParserTransition transitions [];
extern const ParserState states [];

const ParserAction actions [] = 
{
    {0, "begin_element"},
    {1, "end_element"},
    {2, "null_attribute"},
    {3, "boolean_attribute"},
    {4, "integer_attribute"},
    {5, "real_attribute"},
    {6, "string_attribute"},
    {-1, nullptr}
};

const ParserSymbol symbols [] = 
{
    {0, "dot_start", ".start", (SymbolType) 2},
    {1, "dot_end", ".end", (SymbolType) 3},
    {2, "error", "error", (SymbolType) 1},
    {3, "document", "document", (SymbolType) 2},
    {4, "left_curly_brace_terminal", "{", (SymbolType) 1},
    {5, "element", "element", (SymbolType) 2},
    {6, "right_curly_brace_terminal", "}", (SymbolType) 1},
    {7, "begin_element", "begin_element", (SymbolType) 2},
    {8, "contents", "contents", (SymbolType) 2},
    {9, "end_element", "end_element", (SymbolType) 2},
    {10, "colon_terminal", ":", (SymbolType) 1},
    {11, "comma_terminal", ",", (SymbolType) 1},
    {12, "content", "content", (SymbolType) 2},
    {13, "attribute", "attribute", (SymbolType) 2},
    {14, "string", "[\\\"']:string:", (SymbolType) 1},
    {15, "null", "null", (SymbolType) 1},
    {16, "true", "true", (SymbolType) 1},
    {17, "false", "false", (SymbolType) 1},
    {18, "integer", "(\\+|\\-)?[0-9]+", (SymbolType) 1},
    {19, "real", "(\\+|\\-)?[0-9]+(\\.[0-9]+)?((e|E)(\\+|\\-)?[0-9]+)?", (SymbolType) 1},
    {-1, nullptr, nullptr, (SymbolType) 0}
};

const ParserTransition transitions [] = 
{
    {&symbols[3], &states[1], nullptr, 0, 0, -1, (TransitionType) 0, 0},
    {&symbols[4], &states[2], nullptr, 0, 0, -1, (TransitionType) 0, 1},
    {&symbols[1], nullptr, &symbols[0], 1, 0, -1, (TransitionType) 1, 2},
    {&symbols[5], &states[3], nullptr, 0, 0, -1, (TransitionType) 0, 3},
    {&symbols[7], &states[5], nullptr, 0, 0, -1, (TransitionType) 0, 4},
    {&symbols[14], &states[9], nullptr, 0, 0, -1, (TransitionType) 0, 5},
    {&symbols[6], &states[4], nullptr, 0, 0, -1, (TransitionType) 0, 6},
    {&symbols[1], nullptr, &symbols[3], 3, 0, -1, (TransitionType) 1, 7},
    {&symbols[5], &states[17], nullptr, 0, 0, -1, (TransitionType) 0, 8},
    {&symbols[7], &states[5], nullptr, 0, 0, -1, (TransitionType) 0, 9},
    {&symbols[8], &states[7], nullptr, 0, 0, -1, (TransitionType) 0, 10},
    {&symbols[12], &states[16], nullptr, 0, 0, -1, (TransitionType) 0, 11},
    {&symbols[13], &states[18], nullptr, 0, 0, -1, (TransitionType) 0, 12},
    {&symbols[14], &states[10], nullptr, 0, 0, -1, (TransitionType) 0, 13},
    {&symbols[5], &states[17], nullptr, 0, 0, -1, (TransitionType) 0, 14},
    {&symbols[7], &states[5], nullptr, 0, 0, -1, (TransitionType) 0, 15},
    {&symbols[12], &states[15], nullptr, 0, 0, -1, (TransitionType) 0, 16},
    {&symbols[13], &states[18], nullptr, 0, 0, -1, (TransitionType) 0, 17},
    {&symbols[14], &states[10], nullptr, 0, 0, -1, (TransitionType) 0, 18},
    {&symbols[6], &states[14], nullptr, 0, 0, -1, (TransitionType) 0, 19},
    {&symbols[9], &states[8], nullptr, 0, 0, -1, (TransitionType) 0, 20},
    {&symbols[11], &states[6], nullptr, 0, 0, -1, (TransitionType) 0, 21},
    {&symbols[6], nullptr, &symbols[5], 3, 0, -1, (TransitionType) 1, 22},
    {&symbols[11], nullptr, &symbols[5], 3, 0, -1, (TransitionType) 1, 23},
    {&symbols[10], &states[11], nullptr, 0, 0, -1, (TransitionType) 0, 24},
    {&symbols[10], &states[12], nullptr, 0, 0, -1, (TransitionType) 0, 25},
    {&symbols[4], &states[13], nullptr, 0, 0, -1, (TransitionType) 0, 26},
    {&symbols[4], &states[13], nullptr, 0, 0, -1, (TransitionType) 0, 27},
    {&symbols[14], &states[24], nullptr, 0, 0, -1, (TransitionType) 0, 28},
    {&symbols[15], &states[19], nullptr, 0, 0, -1, (TransitionType) 0, 29},
    {&symbols[16], &states[20], nullptr, 0, 0, -1, (TransitionType) 0, 30},
    {&symbols[17], &states[21], nullptr, 0, 0, -1, (TransitionType) 0, 31},
    {&symbols[18], &states[22], nullptr, 0, 0, -1, (TransitionType) 0, 32},
    {&symbols[19], &states[23], nullptr, 0, 0, -1, (TransitionType) 0, 33},
    {&symbols[14], nullptr, &symbols[7], 3, 0, 0, (TransitionType) 1, 34},
    {&symbols[6], nullptr, &symbols[9], 1, 0, 1, (TransitionType) 1, 35},
    {&symbols[11], nullptr, &symbols[9], 1, 0, 1, (TransitionType) 1, 36},
    {&symbols[6], nullptr, &symbols[8], 3, 0, -1, (TransitionType) 1, 37},
    {&symbols[11], nullptr, &symbols[8], 3, 0, -1, (TransitionType) 1, 38},
    {&symbols[6], nullptr, &symbols[8], 1, 0, -1, (TransitionType) 1, 39},
    {&symbols[11], nullptr, &symbols[8], 1, 0, -1, (TransitionType) 1, 40},
    {&symbols[6], nullptr, &symbols[12], 1, 0, -1, (TransitionType) 1, 41},
    {&symbols[11], nullptr, &symbols[12], 1, 0, -1, (TransitionType) 1, 42},
    {&symbols[6], nullptr, &symbols[12], 1, 0, -1, (TransitionType) 1, 43},
    {&symbols[11], nullptr, &symbols[12], 1, 0, -1, (TransitionType) 1, 44},
    {&symbols[6], nullptr, &symbols[13], 3, 0, 2, (TransitionType) 1, 45},
    {&symbols[11], nullptr, &symbols[13], 3, 0, 2, (TransitionType) 1, 46},
    {&symbols[6], nullptr, &symbols[13], 3, 0, 3, (TransitionType) 1, 47},
    {&symbols[11], nullptr, &symbols[13], 3, 0, 3, (TransitionType) 1, 48},
    {&symbols[6], nullptr, &symbols[13], 3, 0, 3, (TransitionType) 1, 49},
    {&symbols[11], nullptr, &symbols[13], 3, 0, 3, (TransitionType) 1, 50},
    {&symbols[6], nullptr, &symbols[13], 3, 0, 4, (TransitionType) 1, 51},
    {&symbols[11], nullptr, &symbols[13], 3, 0, 4, (TransitionType) 1, 52},
    {&symbols[6], nullptr, &symbols[13], 3, 0, 5, (TransitionType) 1, 53},
    {&symbols[11], nullptr, &symbols[13], 3, 0, 5, (TransitionType) 1, 54},
    {&symbols[6], nullptr, &symbols[13], 3, 0, 6, (TransitionType) 1, 55},
    {&symbols[11], nullptr, &symbols[13], 3, 0, 6, (TransitionType) 1, 56},
    {nullptr, nullptr, nullptr, 0, 0, 0, (TransitionType) 0, -1}
};

const ParserState states [] = 
{
    {0, 2, &transitions[0]},
    {1, 1, &transitions[2]},
    {2, 3, &transitions[3]},
    {3, 1, &transitions[6]},
    {4, 1, &transitions[7]},
    {5, 6, &transitions[8]},
    {6, 5, &transitions[14]},
    {7, 3, &transitions[19]},
    {8, 2, &transitions[22]},
    {9, 1, &transitions[24]},
    {10, 1, &transitions[25]},
    {11, 1, &transitions[26]},
    {12, 7, &transitions[27]},
    {13, 1, &transitions[34]},
    {14, 2, &transitions[35]},
    {15, 2, &transitions[37]},
    {16, 2, &transitions[39]},
    {17, 2, &transitions[41]},
    {18, 2, &transitions[43]},
    {19, 2, &transitions[45]},
    {20, 2, &transitions[47]},
    {21, 2, &transitions[49]},
    {22, 2, &transitions[51]},
    {23, 2, &transitions[53]},
    {24, 2, &transitions[55]},
    {-1, 0, nullptr}
};

const LexerAction lexer_actions [] = 
{
    {0, "string"},
    {-1, nullptr}
};

const LexerTransition lexer_transitions [] = 
{
    {34, 35, &lexer_states[10], nullptr},
    {39, 40, &lexer_states[10], nullptr},
    {43, 44, &lexer_states[26], nullptr},
    {44, 45, &lexer_states[9], nullptr},
    {45, 46, &lexer_states[26], nullptr},
    {48, 58, &lexer_states[25], nullptr},
    {58, 59, &lexer_states[8], nullptr},
    {101, 102, &lexer_states[1], nullptr},
    {102, 103, &lexer_states[20], nullptr},
    {110, 111, &lexer_states[12], nullptr},
    {116, 117, &lexer_states[16], nullptr},
    {123, 124, &lexer_states[6], nullptr},
    {125, 126, &lexer_states[7], nullptr},
    {114, 115, &lexer_states[2], nullptr},
    {114, 115, &lexer_states[3], nullptr},
    {111, 112, &lexer_states[4], nullptr},
    {114, 115, &lexer_states[5], nullptr},
    {0, 2147483647, &lexer_states[11], &lexer_actions[0]},
    {117, 118, &lexer_states[13], nullptr},
    {108, 109, &lexer_states[14], nullptr},
    {108, 109, &lexer_states[15], nullptr},
    {114, 115, &lexer_states[17], nullptr},
    {117, 118, &lexer_states[18], nullptr},
    {101, 102, &lexer_states[19], nullptr},
    {97, 98, &lexer_states[21], nullptr},
    {108, 109, &lexer_states[22], nullptr},
    {115, 116, &lexer_states[23], nullptr},
    {101, 102, &lexer_states[24], nullptr},
    {46, 47, &lexer_states[27], nullptr},
    {48, 58, &lexer_states[25], nullptr},
    {69, 70, &lexer_states[29], nullptr},
    {101, 102, &lexer_states[29], nullptr},
    {48, 58, &lexer_states[25], nullptr},
    {48, 58, &lexer_states[28], nullptr},
    {48, 58, &lexer_states[28], nullptr},
    {69, 70, &lexer_states[29], nullptr},
    {101, 102, &lexer_states[29], nullptr},
    {43, 44, &lexer_states[30], nullptr},
    {45, 46, &lexer_states[30], nullptr},
    {48, 58, &lexer_states[31], nullptr},
    {48, 58, &lexer_states[31], nullptr},
    {48, 58, &lexer_states[31], nullptr},
    {-1, -1, nullptr, nullptr}
};

const LexerState lexer_states [] = 
{
    {0, 13, &lexer_transitions[0], nullptr},
    {1, 1, &lexer_transitions[13], nullptr},
    {2, 1, &lexer_transitions[14], nullptr},
    {3, 1, &lexer_transitions[15], nullptr},
    {4, 1, &lexer_transitions[16], nullptr},
    {5, 0, &lexer_transitions[17], &symbols[2]},
    {6, 0, &lexer_transitions[17], &symbols[4]},
    {7, 0, &lexer_transitions[17], &symbols[6]},
    {8, 0, &lexer_transitions[17], &symbols[10]},
    {9, 0, &lexer_transitions[17], &symbols[11]},
    {10, 1, &lexer_transitions[17], nullptr},
    {11, 0, &lexer_transitions[18], &symbols[14]},
    {12, 1, &lexer_transitions[18], nullptr},
    {13, 1, &lexer_transitions[19], nullptr},
    {14, 1, &lexer_transitions[20], nullptr},
    {15, 0, &lexer_transitions[21], &symbols[15]},
    {16, 1, &lexer_transitions[21], nullptr},
    {17, 1, &lexer_transitions[22], nullptr},
    {18, 1, &lexer_transitions[23], nullptr},
    {19, 0, &lexer_transitions[24], &symbols[16]},
    {20, 1, &lexer_transitions[24], nullptr},
    {21, 1, &lexer_transitions[25], nullptr},
    {22, 1, &lexer_transitions[26], nullptr},
    {23, 1, &lexer_transitions[27], nullptr},
    {24, 0, &lexer_transitions[28], &symbols[17]},
    {25, 4, &lexer_transitions[28], &symbols[18]},
    {26, 1, &lexer_transitions[32], nullptr},
    {27, 1, &lexer_transitions[33], nullptr},
    {28, 3, &lexer_transitions[34], &symbols[19]},
    {29, 3, &lexer_transitions[37], nullptr},
    {30, 1, &lexer_transitions[40], nullptr},
    {31, 1, &lexer_transitions[41], &symbols[19]},
    {-1, 0, nullptr, nullptr}
};

const LexerStateMachine lexer_state_machine = 
{
    1, // #actions
    42, // #transitions
    32, // #states
    lexer_actions, // actions
    lexer_transitions, // transitions
    lexer_states, // states
    &lexer_states[0] // start state
};

const LexerAction whitespace_lexer_actions [] = 
{
    {-1, nullptr}
};

const LexerTransition whitespace_lexer_transitions [] = 
{
    {9, 11, &whitespace_lexer_states[0], nullptr},
    {13, 14, &whitespace_lexer_states[0], nullptr},
    {32, 33, &whitespace_lexer_states[0], nullptr},
    {-1, -1, nullptr, nullptr}
};

const LexerState whitespace_lexer_states [] = 
{
    {0, 3, &whitespace_lexer_transitions[0], nullptr},
    {-1, 0, nullptr, nullptr}
};

const LexerStateMachine whitespace_lexer_state_machine = 
{
    0, // #actions
    3, // #transitions
    1, // #states
    whitespace_lexer_actions, // actions
    whitespace_lexer_transitions, // transitions
    whitespace_lexer_states, // states
    &whitespace_lexer_states[0] // start state
};

const ParserStateMachine parser_state_machine = 
{
    "json",
    7, // #actions
    20, // #symbols
    57, // #transitions
    25, // #states
    actions,
    symbols,
    transitions,
    states,
    &symbols[0], // start symbol
    &symbols[1], // end symbol
    &symbols[2], // error symbol
    &states[0], // start state
    &lexer_state_machine, // lexer state machine
    &whitespace_lexer_state_machine // whitespace lexer state machine
};

}

const lalr::ParserStateMachine* json_parser_state_machine = &parser_state_machine;

