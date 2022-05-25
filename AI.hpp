#pragma once

#ifndef AI_H
#define AI_H

#include "Move.hpp"
#include "Board.hpp"

class AI {    
public:
    static int alphaBeta(int alpha, int beta, int depth, Board &bd);
    static std::pair<int, Move> search(int depth, Board &bd);
    static int evaluateBoard(Board &bd);
};

#endif