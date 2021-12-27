
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
    {2, "attribute"},
    {-1, nullptr}
};

const ParserSymbol symbols [] = 
{
    {0, "dot_start", ".start", (SymbolType) 2},
    {1, "dot_end", ".end", (SymbolType) 3},
    {2, "error", "error", (SymbolType) 1},
    {3, "lt_terminal", "<", (SymbolType) 1},
    {4, "gt_terminal", ">", (SymbolType) 1},
    {5, "document", "document", (SymbolType) 2},
    {6, "prolog", "prolog", (SymbolType) 2},
    {7, "element", "element", (SymbolType) 2},
    {8, "lt__question_xml_terminal", "<?xml", (SymbolType) 1},
    {9, "attributes", "attributes", (SymbolType) 2},
    {10, "question__gt_terminal", "?>", (SymbolType) 1},
    {11, "begin_element", "begin_element", (SymbolType) 2},
    {12, "end_element", "end_element", (SymbolType) 2},
    {13, "slash__gt_terminal", "/>", (SymbolType) 1},
    {14, "elements", "elements", (SymbolType) 2},
    {15, "lt__slash_terminal", "</", (SymbolType) 1},
    {16, "name", "[A-Za-z_:][A-Za-z0-9_:\\\\.-]*", (SymbolType) 1},
    {17, "attribute", "attribute", (SymbolType) 2},
    {18, "eq_terminal", "=", (SymbolType) 1},
    {19, "value", "[\\\"']:string:", (SymbolType) 1},
    {-1, nullptr, nullptr, (SymbolType) 0}
};

const ParserTransition transitions [] = 
{
    {&symbols[3], nullptr, &symbols[6], 0, 0, -1, (TransitionType) 1, 0},
    {&symbols[5], &states[1], nullptr, 0, 0, -1, (TransitionType) 0, 1},
    {&symbols[6], &states[2], nullptr, 0, 0, -1, (TransitionType) 0, 2},
    {&symbols[8], &states[4], nullptr, 0, 0, -1, (TransitionType) 0, 3},
    {&symbols[1], nullptr, &symbols[0], 1, 0, -1, (TransitionType) 1, 4},
    {&symbols[3], &states[12], nullptr, 0, 0, -1, (TransitionType) 0, 5},
    {&symbols[7], &states[3], nullptr, 0, 0, -1, (TransitionType) 0, 6},
    {&symbols[11], &states[9], nullptr, 0, 0, -1, (TransitionType) 0, 7},
    {&symbols[1], nullptr, &symbols[5], 2, 0, -1, (TransitionType) 1, 8},
    {&symbols[9], &states[5], nullptr, 0, 0, -1, (TransitionType) 0, 9},
    {&symbols[10], nullptr, &symbols[9], 0, 2, -1, (TransitionType) 1, 10},
    {&symbols[16], &states[22], nullptr, 0, 0, -1, (TransitionType) 0, 11},
    {&symbols[17], &states[21], nullptr, 0, 0, -1, (TransitionType) 0, 12},
    {&symbols[10], &states[6], nullptr, 0, 0, -1, (TransitionType) 0, 13},
    {&symbols[16], &states[22], nullptr, 0, 0, -1, (TransitionType) 0, 14},
    {&symbols[17], &states[20], nullptr, 0, 0, -1, (TransitionType) 0, 15},
    {&symbols[3], nullptr, &symbols[6], 3, 0, -1, (TransitionType) 1, 16},
    {&symbols[3], &states[12], nullptr, 0, 0, -1, (TransitionType) 0, 17},
    {&symbols[7], &states[19], nullptr, 0, 0, -1, (TransitionType) 0, 18},
    {&symbols[11], &states[9], nullptr, 0, 0, -1, (TransitionType) 0, 19},
    {&symbols[14], &states[8], nullptr, 0, 0, -1, (TransitionType) 0, 20},
    {&symbols[15], nullptr, &symbols[14], 0, 1, -1, (TransitionType) 1, 21},
    {&symbols[3], &states[12], nullptr, 0, 0, -1, (TransitionType) 0, 22},
    {&symbols[7], &states[18], nullptr, 0, 0, -1, (TransitionType) 0, 23},
    {&symbols[11], &states[9], nullptr, 0, 0, -1, (TransitionType) 0, 24},
    {&symbols[15], &states[15], nullptr, 0, 0, -1, (TransitionType) 0, 25},
    {&symbols[4], nullptr, &symbols[9], 0, 2, -1, (TransitionType) 1, 26},
    {&symbols[9], &states[10], nullptr, 0, 0, -1, (TransitionType) 0, 27},
    {&symbols[13], nullptr, &symbols[9], 0, 2, -1, (TransitionType) 1, 28},
    {&symbols[16], &states[22], nullptr, 0, 0, -1, (TransitionType) 0, 29},
    {&symbols[17], &states[21], nullptr, 0, 0, -1, (TransitionType) 0, 30},
    {&symbols[4], &states[7], nullptr, 0, 0, -1, (TransitionType) 0, 31},
    {&symbols[12], &states[11], nullptr, 0, 0, -1, (TransitionType) 0, 32},
    {&symbols[13], &states[14], nullptr, 0, 0, -1, (TransitionType) 0, 33},
    {&symbols[16], &states[22], nullptr, 0, 0, -1, (TransitionType) 0, 34},
    {&symbols[17], &states[20], nullptr, 0, 0, -1, (TransitionType) 0, 35},
    {&symbols[1], nullptr, &symbols[7], 3, 0, -1, (TransitionType) 1, 36},
    {&symbols[3], nullptr, &symbols[7], 3, 0, -1, (TransitionType) 1, 37},
    {&symbols[15], nullptr, &symbols[7], 3, 0, -1, (TransitionType) 1, 38},
    {&symbols[16], &states[13], nullptr, 0, 0, -1, (TransitionType) 0, 39},
    {&symbols[4], nullptr, &symbols[11], 2, 2, 0, (TransitionType) 1, 40},
    {&symbols[13], nullptr, &symbols[11], 2, 2, 0, (TransitionType) 1, 41},
    {&symbols[16], nullptr, &symbols[11], 2, 2, 0, (TransitionType) 1, 42},
    {&symbols[1], nullptr, &symbols[12], 1, 0, 1, (TransitionType) 1, 43},
    {&symbols[3], nullptr, &symbols[12], 1, 0, 1, (TransitionType) 1, 44},
    {&symbols[15], nullptr, &symbols[12], 1, 0, 1, (TransitionType) 1, 45},
    {&symbols[16], &states[16], nullptr, 0, 0, -1, (TransitionType) 0, 46},
    {&symbols[4], &states[17], nullptr, 0, 0, -1, (TransitionType) 0, 47},
    {&symbols[1], nullptr, &symbols[12], 5, 1, 1, (TransitionType) 1, 48},
    {&symbols[3], nullptr, &symbols[12], 5, 1, 1, (TransitionType) 1, 49},
    {&symbols[15], nullptr, &symbols[12], 5, 1, 1, (TransitionType) 1, 50},
    {&symbols[3], nullptr, &symbols[14], 2, 0, -1, (TransitionType) 1, 51},
    {&symbols[15], nullptr, &symbols[14], 2, 0, -1, (TransitionType) 1, 52},
    {&symbols[3], nullptr, &symbols[14], 1, 0, -1, (TransitionType) 1, 53},
    {&symbols[15], nullptr, &symbols[14], 1, 0, -1, (TransitionType) 1, 54},
    {&symbols[4], nullptr, &symbols[9], 2, 0, -1, (TransitionType) 1, 55},
    {&symbols[10], nullptr, &symbols[9], 2, 0, -1, (TransitionType) 1, 56},
    {&symbols[13], nullptr, &symbols[9], 2, 0, -1, (TransitionType) 1, 57},
    {&symbols[16], nullptr, &symbols[9], 2, 0, -1, (TransitionType) 1, 58},
    {&symbols[4], nullptr, &symbols[9], 1, 0, -1, (TransitionType) 1, 59},
    {&symbols[10], nullptr, &symbols[9], 1, 0, -1, (TransitionType) 1, 60},
    {&symbols[13], nullptr, &symbols[9], 1, 0, -1, (TransitionType) 1, 61},
    {&symbols[16], nullptr, &symbols[9], 1, 0, -1, (TransitionType) 1, 62},
    {&symbols[18], &states[23], nullptr, 0, 0, -1, (TransitionType) 0, 63},
    {&symbols[19], &states[24], nullptr, 0, 0, -1, (TransitionType) 0, 64},
    {&symbols[4], nullptr, &symbols[17], 3, 0, 2, (TransitionType) 1, 65},
    {&symbols[10], nullptr, &symbols[17], 3, 0, 2, (TransitionType) 1, 66},
    {&symbols[13], nullptr, &symbols[17], 3, 0, 2, (TransitionType) 1, 67},
    {&symbols[16], nullptr, &symbols[17], 3, 0, 2, (TransitionType) 1, 68},
    {nullptr, nullptr, nullptr, 0, 0, 0, (TransitionType) 0, -1}
};

const ParserState states [] = 
{
    {0, 4, &transitions[0]},
    {1, 1, &transitions[4]},
    {2, 3, &transitions[5]},
    {3, 1, &transitions[8]},
    {4, 4, &transitions[9]},
    {5, 3, &transitions[13]},
    {6, 1, &transitions[16]},
    {7, 5, &transitions[17]},
    {8, 4, &transitions[22]},
    {9, 5, &transitions[26]},
    {10, 5, &transitions[31]},
    {11, 3, &transitions[36]},
    {12, 1, &transitions[39]},
    {13, 3, &transitions[40]},
    {14, 3, &transitions[43]},
    {15, 1, &transitions[46]},
    {16, 1, &transitions[47]},
    {17, 3, &transitions[48]},
    {18, 2, &transitions[51]},
    {19, 2, &transitions[53]},
    {20, 4, &transitions[55]},
    {21, 4, &transitions[59]},
    {22, 1, &transitions[63]},
    {23, 1, &transitions[64]},
    {24, 4, &transitions[65]},
    {-1, 0, nullptr}
};

const LexerAction lexer_actions [] = 
{
    {0, "string"},
    {-1, nullptr}
};

const LexerTransition lexer_transitions [] = 
{
    {34, 35, &lexer_states[19], nullptr},
    {39, 40, &lexer_states[19], nullptr},
    {47, 48, &lexer_states[14], nullptr},
    {58, 59, &lexer_states[17], nullptr},
    {60, 61, &lexer_states[6], nullptr},
    {61, 62, &lexer_states[18], nullptr},
    {62, 63, &lexer_states[7], nullptr},
    {63, 64, &lexer_states[12], nullptr},
    {65, 91, &lexer_states[17], nullptr},
    {95, 96, &lexer_states[17], nullptr},
    {97, 101, &lexer_states[17], nullptr},
    {101, 102, &lexer_states[1], nullptr},
    {102, 123, &lexer_states[17], nullptr},
    {45, 47, &lexer_states[17], nullptr},
    {48, 59, &lexer_states[17], nullptr},
    {65, 91, &lexer_states[17], nullptr},
    {92, 93, &lexer_states[17], nullptr},
    {95, 96, &lexer_states[17], nullptr},
    {97, 114, &lexer_states[17], nullptr},
    {114, 115, &lexer_states[2], nullptr},
    {115, 123, &lexer_states[17], nullptr},
    {45, 47, &lexer_states[17], nullptr},
    {48, 59, &lexer_states[17], nullptr},
    {65, 91, &lexer_states[17], nullptr},
    {92, 93, &lexer_states[17], nullptr},
    {95, 96, &lexer_states[17], nullptr},
    {97, 114, &lexer_states[17], nullptr},
    {114, 115, &lexer_states[3], nullptr},
    {115, 123, &lexer_states[17], nullptr},
    {45, 47, &lexer_states[17], nullptr},
    {48, 59, &lexer_states[17], nullptr},
    {65, 91, &lexer_states[17], nullptr},
    {92, 93, &lexer_states[17], nullptr},
    {95, 96, &lexer_states[17], nullptr},
    {97, 111, &lexer_states[17], nullptr},
    {111, 112, &lexer_states[4], nullptr},
    {112, 123, &lexer_states[17], nullptr},
    {45, 47, &lexer_states[17], nullptr},
    {48, 59, &lexer_states[17], nullptr},
    {65, 91, &lexer_states[17], nullptr},
    {92, 93, &lexer_states[17], nullptr},
    {95, 96, &lexer_states[17], nullptr},
    {97, 114, &lexer_states[17], nullptr},
    {114, 115, &lexer_states[5], nullptr},
    {115, 123, &lexer_states[17], nullptr},
    {45, 47, &lexer_states[17], nullptr},
    {48, 59, &lexer_states[17], nullptr},
    {65, 91, &lexer_states[17], nullptr},
    {92, 93, &lexer_states[17], nullptr},
    {95, 96, &lexer_states[17], nullptr},
    {97, 123, &lexer_states[17], nullptr},
    {47, 48, &lexer_states[16], nullptr},
    {63, 64, &lexer_states[8], nullptr},
    {120, 121, &lexer_states[9], nullptr},
    {109, 110, &lexer_states[10], nullptr},
    {108, 109, &lexer_states[11], nullptr},
    {62, 63, &lexer_states[13], nullptr},
    {62, 63, &lexer_states[15], nullptr},
    {45, 47, &lexer_states[17], nullptr},
    {48, 59, &lexer_states[17], nullptr},
    {65, 91, &lexer_states[17], nullptr},
    {92, 93, &lexer_states[17], nullptr},
    {95, 96, &lexer_states[17], nullptr},
    {97, 123, &lexer_states[17], nullptr},
    {0, 2147483647, &lexer_states[20], &lexer_actions[0]},
    {-1, -1, nullptr, nullptr}
};

const LexerState lexer_states [] = 
{
    {0, 13, &lexer_transitions[0], nullptr},
    {1, 8, &lexer_transitions[13], &symbols[16]},
    {2, 8, &lexer_transitions[21], &symbols[16]},
    {3, 8, &lexer_transitions[29], &symbols[16]},
    {4, 8, &lexer_transitions[37], &symbols[16]},
    {5, 6, &lexer_transitions[45], &symbols[2]},
    {6, 2, &lexer_transitions[51], &symbols[3]},
    {7, 0, &lexer_transitions[53], &symbols[4]},
    {8, 1, &lexer_transitions[53], nullptr},
    {9, 1, &lexer_transitions[54], nullptr},
    {10, 1, &lexer_transitions[55], nullptr},
    {11, 0, &lexer_transitions[56], &symbols[8]},
    {12, 1, &lexer_transitions[56], nullptr},
    {13, 0, &lexer_transitions[57], &symbols[10]},
    {14, 1, &lexer_transitions[57], nullptr},
    {15, 0, &lexer_transitions[58], &symbols[13]},
    {16, 0, &lexer_transitions[58], &symbols[15]},
    {17, 6, &lexer_transitions[58], &symbols[16]},
    {18, 0, &lexer_transitions[64], &symbols[18]},
    {19, 1, &lexer_transitions[64], nullptr},
    {20, 0, &lexer_transitions[65], &symbols[19]},
    {-1, 0, nullptr, nullptr}
};

const LexerStateMachine lexer_state_machine = 
{
    1, // #actions
    65, // #transitions
    21, // #states
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
    "xml",
    3, // #actions
    20, // #symbols
    69, // #transitions
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

const lalr::ParserStateMachine* xml_parser_state_machine = &parser_state_machine;

