#pragma once

#include <NFA.h>
#include <REGTree.h>

/// @brief Creates NFA from REGTree
/// @param tree REGTree the NFA will be built on
/// @return Built NFA
NFA GetNFAFromREG(const REGTree tree);