#include "AI.hpp"

// TODO: code the search function that searches the current board position up to a certain depth 
// and returns a pair consisting of the evaluation and the best move
std::pair<int, Move> AI::search(int depth, const Board &bd) {
    for(auto piece: bd.getPieces()) std::cout << *piece;
    return {depth, Move{1, 0, 0, 2, true, false, false, false, false, ""}};
}

// returns the score in centipawns (1/100 * pawn_value)
int AI::evaluateBoard(const Board &bd) {
    int eval = 0;
    for(auto piece: bd.getPieces()) eval += piece->evaluate(bd) * (piece->getColor() ? 1 : -1);
    return eval;
}