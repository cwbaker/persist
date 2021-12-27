
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
    {2, "nil_attribute"},
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
    {4, "element", "element", (SymbolType) 2},
    {5, "begin_element", "begin_element", (SymbolType) 2},
    {6, "contents", "contents", (SymbolType) 2},
    {7, "end_element", "end_element", (SymbolType) 2},
    {8, "eq_terminal", "=", (SymbolType) 1},
    {9, "left_curly_brace_terminal", "{", (SymbolType) 1},
    {10, "right_curly_brace_terminal", "}", (SymbolType) 1},
    {11, "comma_terminal", ",", (SymbolType) 1},
    {12, "content", "content", (SymbolType) 2},
    {13, "attribute", "attribute", (SymbolType) 2},
    {14, "name", "[A-Za-z_][A-Za-z_0-9]*", (SymbolType) 1},
    {15, "nil", "nil", (SymbolType) 1},
    {16, "true", "true", (SymbolType) 1},
    {17, "false", "false", (SymbolType) 1},
    {18, "integer", "(\\+|\\-)?[0-9]+", (SymbolType) 1},
    {19, "real", "(\\+|\\-)?[0-9]+(\\.[0-9]+)?((e|E)(\\+|\\-)?[0-9]+)?", (SymbolType) 1},
    {20, "string", "[\\\"']:string:", (SymbolType) 1},
    {-1, nullptr, nullptr, (SymbolType) 0}
};

const ParserTransition transitions [] = 
{
    {&symbols[3], &states[1], nullptr, 0, 0, -1, (TransitionType) 0, 0},
    {&symbols[4], &states[2], nullptr, 0, 0, -1, (TransitionType) 0, 1},
    {&symbols[5], &states[3], nullptr, 0, 0, -1, (TransitionType) 0, 2},
    {&symbols[14], &states[7], nullptr, 0, 0, -1, (TransitionType) 0, 3},
    {&symbols[1], nullptr, &symbols[0], 1, 0, -1, (TransitionType) 1, 4},
    {&symbols[1], nullptr, &symbols[3], 1, 0, -1, (TransitionType) 1, 5},
    {&symbols[4], &states[15], nullptr, 0, 0, -1, (TransitionType) 0, 6},
    {&symbols[5], &states[3], nullptr, 0, 0, -1, (TransitionType) 0, 7},
    {&symbols[6], &states[5], nullptr, 0, 0, -1, (TransitionType) 0, 8},
    {&symbols[12], &states[14], nullptr, 0, 0, -1, (TransitionType) 0, 9},
    {&symbols[13], &states[16], nullptr, 0, 0, -1, (TransitionType) 0, 10},
    {&symbols[14], &states[8], nullptr, 0, 0, -1, (TransitionType) 0, 11},
    {&symbols[4], &states[15], nullptr, 0, 0, -1, (TransitionType) 0, 12},
    {&symbols[5], &states[3], nullptr, 0, 0, -1, (TransitionType) 0, 13},
    {&symbols[12], &states[13], nullptr, 0, 0, -1, (TransitionType) 0, 14},
    {&symbols[13], &states[16], nullptr, 0, 0, -1, (TransitionType) 0, 15},
    {&symbols[14], &states[8], nullptr, 0, 0, -1, (TransitionType) 0, 16},
    {&symbols[7], &states[6], nullptr, 0, 0, -1, (TransitionType) 0, 17},
    {&symbols[10], &states[12], nullptr, 0, 0, -1, (TransitionType) 0, 18},
    {&symbols[11], &states[4], nullptr, 0, 0, -1, (TransitionType) 0, 19},
    {&symbols[1], nullptr, &symbols[4], 3, 0, -1, (TransitionType) 1, 20},
    {&symbols[10], nullptr, &symbols[4], 3, 0, -1, (TransitionType) 1, 21},
    {&symbols[11], nullptr, &symbols[4], 3, 0, -1, (TransitionType) 1, 22},
    {&symbols[8], &states[9], nullptr, 0, 0, -1, (TransitionType) 0, 23},
    {&symbols[8], &states[10], nullptr, 0, 0, -1, (TransitionType) 0, 24},
    {&symbols[9], &states[11], nullptr, 0, 0, -1, (TransitionType) 0, 25},
    {&symbols[9], &states[11], nullptr, 0, 0, -1, (TransitionType) 0, 26},
    {&symbols[15], &states[17], nullptr, 0, 0, -1, (TransitionType) 0, 27},
    {&symbols[16], &states[18], nullptr, 0, 0, -1, (TransitionType) 0, 28},
    {&symbols[17], &states[19], nullptr, 0, 0, -1, (TransitionType) 0, 29},
    {&symbols[18], &states[20], nullptr, 0, 0, -1, (TransitionType) 0, 30},
    {&symbols[19], &states[21], nullptr, 0, 0, -1, (TransitionType) 0, 31},
    {&symbols[20], &states[22], nullptr, 0, 0, -1, (TransitionType) 0, 32},
    {&symbols[14], nullptr, &symbols[5], 3, 0, 0, (TransitionType) 1, 33},
    {&symbols[1], nullptr, &symbols[7], 1, 0, 1, (TransitionType) 1, 34},
    {&symbols[10], nullptr, &symbols[7], 1, 0, 1, (TransitionType) 1, 35},
    {&symbols[11], nullptr, &symbols[7], 1, 0, 1, (TransitionType) 1, 36},
    {&symbols[10], nullptr, &symbols[6], 3, 0, -1, (TransitionType) 1, 37},
    {&symbols[11], nullptr, &symbols[6], 3, 0, -1, (TransitionType) 1, 38},
    {&symbols[10], nullptr, &symbols[6], 1, 0, -1, (TransitionType) 1, 39},
    {&symbols[11], nullptr, &symbols[6], 1, 0, -1, (TransitionType) 1, 40},
    {&symbols[10], nullptr, &symbols[12], 1, 0, -1, (TransitionType) 1, 41},
    {&symbols[11], nullptr, &symbols[12], 1, 0, -1, (TransitionType) 1, 42},
    {&symbols[10], nullptr, &symbols[12], 1, 0, -1, (TransitionType) 1, 43},
    {&symbols[11], nullptr, &symbols[12], 1, 0, -1, (TransitionType) 1, 44},
    {&symbols[10], nullptr, &symbols[13], 3, 0, 2, (TransitionType) 1, 45},
    {&symbols[11], nullptr, &symbols[13], 3, 0, 2, (TransitionType) 1, 46},
    {&symbols[10], nullptr, &symbols[13], 3, 0, 3, (TransitionType) 1, 47},
    {&symbols[11], nullptr, &symbols[13], 3, 0, 3, (TransitionType) 1, 48},
    {&symbols[10], nullptr, &symbols[13], 3, 0, 3, (TransitionType) 1, 49},
    {&symbols[11], nullptr, &symbols[13], 3, 0, 3, (TransitionType) 1, 50},
    {&symbols[10], nullptr, &symbols[13], 3, 0, 4, (TransitionType) 1, 51},
    {&symbols[11], nullptr, &symbols[13], 3, 0, 4, (TransitionType) 1, 52},
    {&symbols[10], nullptr, &symbols[13], 3, 0, 5, (TransitionType) 1, 53},
    {&symbols[11], nullptr, &symbols[13], 3, 0, 5, (TransitionType) 1, 54},
    {&symbols[10], nullptr, &symbols[13], 3, 0, 6, (TransitionType) 1, 55},
    {&symbols[11], nullptr, &symbols[13], 3, 0, 6, (TransitionType) 1, 56},
    {nullptr, nullptr, nullptr, 0, 0, 0, (TransitionType) 0, -1}
};

const ParserState states [] = 
{
    {0, 4, &transitions[0]},
    {1, 1, &transitions[4]},
    {2, 1, &transitions[5]},
    {3, 6, &transitions[6]},
    {4, 5, &transitions[12]},
    {5, 3, &transitions[17]},
    {6, 3, &transitions[20]},
    {7, 1, &transitions[23]},
    {8, 1, &transitions[24]},
    {9, 1, &transitions[25]},
    {10, 7, &transitions[26]},
    {11, 1, &transitions[33]},
    {12, 3, &transitions[34]},
    {13, 2, &transitions[37]},
    {14, 2, &transitions[39]},
    {15, 2, &transitions[41]},
    {16, 2, &transitions[43]},
    {17, 2, &transitions[45]},
    {18, 2, &transitions[47]},
    {19, 2, &transitions[49]},
    {20, 2, &transitions[51]},
    {21, 2, &transitions[53]},
    {22, 2, &transitions[55]},
    {-1, 0, nullptr}
};

const LexerAction lexer_actions [] = 
{
    {0, "string"},
    {-1, nullptr}
};

const LexerTransition lexer_transitions [] = 
{
    {34, 35, &lexer_states[30], nullptr},
    {39, 40, &lexer_states[30], nullptr},
    {43, 44, &lexer_states[24], nullptr},
    {44, 45, &lexer_states[9], nullptr},
    {45, 46, &lexer_states[24], nullptr},
    {48, 58, &lexer_states[23], nullptr},
    {61, 62, &lexer_states[6], nullptr},
    {65, 91, &lexer_states[10], nullptr},
    {95, 96, &lexer_states[10], nullptr},
    {97, 101, &lexer_states[10], nullptr},
    {101, 102, &lexer_states[1], nullptr},
    {102, 103, &lexer_states[18], nullptr},
    {103, 110, &lexer_states[10], nullptr},
    {110, 111, &lexer_states[11], nullptr},
    {111, 116, &lexer_states[10], nullptr},
    {116, 117, &lexer_states[14], nullptr},
    {117, 123, &lexer_states[10], nullptr},
    {123, 124, &lexer_states[7], nullptr},
    {125, 126, &lexer_states[8], nullptr},
    {48, 58, &lexer_states[10], nullptr},
    {65, 91, &lexer_states[10], nullptr},
    {95, 96, &lexer_states[10], nullptr},
    {97, 114, &lexer_states[10], nullptr},
    {114, 115, &lexer_states[2], nullptr},
    {115, 123, &lexer_states[10], nullptr},
    {48, 58, &lexer_states[10], nullptr},
    {65, 91, &lexer_states[10], nullptr},
    {95, 96, &lexer_states[10], nullptr},
    {97, 114, &lexer_states[10], nullptr},
    {114, 115, &lexer_states[3], nullptr},
    {115, 123, &lexer_states[10], nullptr},
    {48, 58, &lexer_states[10], nullptr},
    {65, 91, &lexer_states[10], nullptr},
    {95, 96, &lexer_states[10], nullptr},
    {97, 111, &lexer_states[10], nullptr},
    {111, 112, &lexer_states[4], nullptr},
    {112, 123, &lexer_states[10], nullptr},
    {48, 58, &lexer_states[10], nullptr},
    {65, 91, &lexer_states[10], nullptr},
    {95, 96, &lexer_states[10], nullptr},
    {97, 114, &lexer_states[10], nullptr},
    {114, 115, &lexer_states[5], nullptr},
    {115, 123, &lexer_states[10], nullptr},
    {48, 58, &lexer_states[10], nullptr},
    {65, 91, &lexer_states[10], nullptr},
    {95, 96, &lexer_states[10], nullptr},
    {97, 123, &lexer_states[10], nullptr},
    {48, 58, &lexer_states[10], nullptr},
    {65, 91, &lexer_states[10], nullptr},
    {95, 96, &lexer_states[10], nullptr},
    {97, 123, &lexer_states[10], nullptr},
    {48, 58, &lexer_states[10], nullptr},
    {65, 91, &lexer_states[10], nullptr},
    {95, 96, &lexer_states[10], nullptr},
    {97, 105, &lexer_states[10], nullptr},
    {105, 106, &lexer_states[12], nullptr},
    {106, 123, &lexer_states[10], nullptr},
    {48, 58, &lexer_states[10], nullptr},
    {65, 91, &lexer_states[10], nullptr},
    {95, 96, &lexer_states[10], nullptr},
    {97, 108, &lexer_states[10], nullptr},
    {108, 109, &lexer_states[13], nullptr},
    {109, 123, &lexer_states[10], nullptr},
    {48, 58, &lexer_states[10], nullptr},
    {65, 91, &lexer_states[10], nullptr},
    {95, 96, &lexer_states[10], nullptr},
    {97, 123, &lexer_states[10], nullptr},
    {48, 58, &lexer_states[10], nullptr},
    {65, 91, &lexer_states[10], nullptr},
    {95, 96, &lexer_states[10], nullptr},
    {97, 114, &lexer_states[10], nullptr},
    {114, 115, &lexer_states[15], nullptr},
    {115, 123, &lexer_states[10], nullptr},
    {48, 58, &lexer_states[10], nullptr},
    {65, 91, &lexer_states[10], nullptr},
    {95, 96, &lexer_states[10], nullptr},
    {97, 117, &lexer_states[10], nullptr},
    {117, 118, &lexer_states[16], nullptr},
    {118, 123, &lexer_states[10], nullptr},
    {48, 58, &lexer_states[10], nullptr},
    {65, 91, &lexer_states[10], nullptr},
    {95, 96, &lexer_states[10], nullptr},
    {97, 101, &lexer_states[10], nullptr},
    {101, 102, &lexer_states[17], nullptr},
    {102, 123, &lexer_states[10], nullptr},
    {48, 58, &lexer_states[10], nullptr},
    {65, 91, &lexer_states[10], nullptr},
    {95, 96, &lexer_states[10], nullptr},
    {97, 123, &lexer_states[10], nullptr},
    {48, 58, &lexer_states[10], nullptr},
    {65, 91, &lexer_states[10], nullptr},
    {95, 96, &lexer_states[10], nullptr},
    {97, 98, &lexer_states[19], nullptr},
    {98, 123, &lexer_states[10], nullptr},
    {48, 58, &lexer_states[10], nullptr},
    {65, 91, &lexer_states[10], nullptr},
    {95, 96, &lexer_states[10], nullptr},
    {97, 108, &lexer_states[10], nullptr},
    {108, 109, &lexer_states[20], nullptr},
    {109, 123, &lexer_states[10], nullptr},
    {48, 58, &lexer_states[10], nullptr},
    {65, 91, &lexer_states[10], nullptr},
    {95, 96, &lexer_states[10], nullptr},
    {97, 115, &lexer_states[10], nullptr},
    {115, 116, &lexer_states[21], nullptr},
    {116, 123, &lexer_states[10], nullptr},
    {48, 58, &lexer_states[10], nullptr},
    {65, 91, &lexer_states[10], nullptr},
    {95, 96, &lexer_states[10], nullptr},
    {97, 101, &lexer_states[10], nullptr},
    {101, 102, &lexer_states[22], nullptr},
    {102, 123, &lexer_states[10], nullptr},
    {48, 58, &lexer_states[10], nullptr},
    {65, 91, &lexer_states[10], nullptr},
    {95, 96, &lexer_states[10], nullptr},
    {97, 123, &lexer_states[10], nullptr},
    {46, 47, &lexer_states[25], nullptr},
    {48, 58, &lexer_states[23], nullptr},
    {69, 70, &lexer_states[27], nullptr},
    {101, 102, &lexer_states[27], nullptr},
    {48, 58, &lexer_states[23], nullptr},
    {48, 58, &lexer_states[26], nullptr},
    {48, 58, &lexer_states[26], nullptr},
    {69, 70, &lexer_states[27], nullptr},
    {101, 102, &lexer_states[27], nullptr},
    {43, 44, &lexer_states[28], nullptr},
    {45, 46, &lexer_states[28], nullptr},
    {48, 58, &lexer_states[29], nullptr},
    {48, 58, &lexer_states[29], nullptr},
    {48, 58, &lexer_states[29], nullptr},
    {0, 2147483647, &lexer_states[31], &lexer_actions[0]},
    {-1, -1, nullptr, nullptr}
};

const LexerState lexer_states [] = 
{
    {0, 19, &lexer_transitions[0], nullptr},
    {1, 6, &lexer_transitions[19], &symbols[14]},
    {2, 6, &lexer_transitions[25], &symbols[14]},
    {3, 6, &lexer_transitions[31], &symbols[14]},
    {4, 6, &lexer_transitions[37], &symbols[14]},
    {5, 4, &lexer_transitions[43], &symbols[2]},
    {6, 0, &lexer_transitions[47], &symbols[8]},
    {7, 0, &lexer_transitions[47], &symbols[9]},
    {8, 0, &lexer_transitions[47], &symbols[10]},
    {9, 0, &lexer_transitions[47], &symbols[11]},
    {10, 4, &lexer_transitions[47], &symbols[14]},
    {11, 6, &lexer_transitions[51], &symbols[14]},
    {12, 6, &lexer_transitions[57], &symbols[14]},
    {13, 4, &lexer_transitions[63], &symbols[15]},
    {14, 6, &lexer_transitions[67], &symbols[14]},
    {15, 6, &lexer_transitions[73], &symbols[14]},
    {16, 6, &lexer_transitions[79], &symbols[14]},
    {17, 4, &lexer_transitions[85], &symbols[16]},
    {18, 5, &lexer_transitions[89], &symbols[14]},
    {19, 6, &lexer_transitions[94], &symbols[14]},
    {20, 6, &lexer_transitions[100], &symbols[14]},
    {21, 6, &lexer_transitions[106], &symbols[14]},
    {22, 4, &lexer_transitions[112], &symbols[17]},
    {23, 4, &lexer_transitions[116], &symbols[18]},
    {24, 1, &lexer_transitions[120], nullptr},
    {25, 1, &lexer_transitions[121], nullptr},
    {26, 3, &lexer_transitions[122], &symbols[19]},
    {27, 3, &lexer_transitions[125], nullptr},
    {28, 1, &lexer_transitions[128], nullptr},
    {29, 1, &lexer_transitions[129], &symbols[19]},
    {30, 1, &lexer_transitions[130], nullptr},
    {31, 0, &lexer_transitions[131], &symbols[20]},
    {-1, 0, nullptr, nullptr}
};

const LexerStateMachine lexer_state_machine = 
{
    1, // #actions
    131, // #transitions
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
    "lua",
    7, // #actions
    21, // #symbols
    57, // #transitions
    23, // #states
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

const lalr::ParserStateMachine* lua_parser_state_machine = &parser_state_machine;

