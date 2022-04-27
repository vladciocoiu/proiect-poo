#include "AI.hpp"

// TODO: code the search function that searches the current board position up to a certain depth 
// and returns a pair consisting of the evaluation and the best move
std::pair<int, Move> AI::search(int depth, const Board &bd) {
    int x = depth;
    for(auto piece: bd.getPieces()) x += piece->getSquare().first;
    return {x, Move{1, 0, 0, 2, true, false, false, false, false, ""}};
}


// TODO: code the evaluate function that evaluates the current position on the board and returns the score
int AI::evaluate(const Board &bd) {
    int x = 0;
    for(auto piece: bd.getPieces()) x += piece->getSquare().first;
    return x;
}