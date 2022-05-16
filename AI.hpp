#pragma once

#ifndef AI_H
#define AI_H

#include "Move.hpp"
#include "Board.hpp"

class AI {    
public:
    static std::pair<int, Move> search(int depth, const Board &bd);
    static int evaluateBoard(const Board &bd);
};

#endif