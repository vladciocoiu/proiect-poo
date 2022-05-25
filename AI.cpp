#include "AI.hpp"
#include "King.hpp"

// search function that calls alphaBeta and returns the score and the best move
std::pair<int, Move> AI::search(int depth, Board &bd) {
    const int INF = 1000000;
    static const int MATE_SCORE = 1000;

    // placeholder
    std::pair<int, Move> res = {-INF-1, Move{0, 0, 0, 0, 0, 0, 0 ,0, 0, ""}};

    int alpha = -INF, beta = INF;

     // check if game is over
    std::vector<Move> allMoves = bd.generateAllLegalMoves();
    if(!allMoves.size()) {
        std::shared_ptr<King> king = std::dynamic_pointer_cast<King>(bd.getKing(bd.getTurn()));

        if(king->isInCheck(bd)) res.first = -MATE_SCORE; // checkmate
        else res.first = 0; // stalemate
    }

    for(auto pc: bd.getPieces()) {
        if(pc->getColor() != bd.getTurn()) continue;
        std::vector<Move> moves = pc->generateLegalMoves(bd);
        for(auto mv: moves) {

            // make each move on the board
            bd.makeMove(*pc, mv);

            // recursively calculate the score after each move
            int score = -alphaBeta(-beta, -alpha, depth - 1, bd);

            // update alpha
            if(score > alpha) alpha = score;

            // update result
            if(score > res.first) res = {score, mv};

            // unmake the move
            bd.unmakeMove(*pc, mv);
        }
    }

    return res;
}

// returns the static score of the board in centipawns (1/100 * pawn_value)
int AI::evaluateBoard(const Board &bd) {
    int eval = 0;
    for(auto piece: bd.getPieces()) eval += piece->evaluate(bd) * (piece->getColor() == bd.getTurn() ? 1 : -1);
    return eval;
}

// alpha-beta algorithm that returns the score
int AI::alphaBeta(int alpha, int beta, int depth, Board &bd) {
    static const int MATE_SCORE = 1000;

    if(depth == 0) return AI::evaluateBoard(bd); // no depth left, just return the static evaluation

    // check if game is over
    std::vector<Move> allMoves = bd.generateAllLegalMoves();
    if(!allMoves.size()) {
        std::shared_ptr<King> king = std::dynamic_pointer_cast<King>(bd.getKing(bd.getTurn()));

        if(king->isInCheck(bd)) return -MATE_SCORE; // checkmate
        return 0; // stalemate
    }

    // make every move
    for(auto pc: bd.getPieces()) {
        if(pc->getColor() != bd.getTurn())  continue;
        std::vector<Move> moves = pc->generateLegalMoves(bd);
        for(auto mv: moves) {
            bd.makeMove(*pc, mv);

            // recursively calculate the score after each move
            int score = -alphaBeta(-beta, -alpha, depth - 1, bd);

            bd.unmakeMove(*pc, mv);

            if(score >= beta) return beta; // beta cutoff

            if(score > alpha) alpha = score; // update alpha
        }
    }
    return alpha;
}