#pragma once

#include <NFA.h>
#include <DFA.h>

/// @brief Build equivalent DFA for given NFA using Thompson's algorithm
/// @param nfa NFA without epsilon-transitions. Existence of eps-transitions causes UB.
/// @return DFA accepting same language as original NFA.
DFA ConvertNFAtoDFA(const NFA& nfa);