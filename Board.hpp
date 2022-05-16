#pragma once

#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <unordered_set>
#include <stack>

#include "Piece.hpp"

class Piece;

class Board {
private:
    std::unordered_set<std::shared_ptr<Piece>> pieces;

    int castleRights; // 4 bytes: 0 for white short, 1 for white long, 2 for black short, 3 for black long
    int enPassantCol;
    bool turn;

    // stacks for irreversible move features in order to restore them when unmaking a move
    std::stack<std::shared_ptr<Piece>> capturedPiecesStack;
    std::stack<int> enPassantColsStack;
    std::stack<int> castleRightsStack;
public:
    // getters and setters
    std::unordered_set<std::shared_ptr<Piece>> getPieces() const { return pieces; };
    void addPiece(std::shared_ptr<Piece> pc) { pieces.insert(pc); };
    void removePiece(std::shared_ptr<Piece> pc) { pieces.erase(pc); }

    std::shared_ptr<Piece> popCapturedPiece() { const auto& piece = capturedPiecesStack.top(); capturedPiecesStack.pop(); return piece; };
    void pushCapturedPiece(std::shared_ptr<Piece> pc) { capturedPiecesStack.push(pc); };

    int popEnPassantCol() { int col = enPassantColsStack.top(); enPassantColsStack.pop(); return col; };
    void pushEnPassantCol(int col) { enPassantColsStack.push(col); };

    int popCastleRights() { int rights = castleRightsStack.top(); castleRightsStack.pop(); return rights; };
    void pushCastleRights(int rights) { castleRightsStack.push(rights); };

    void switchTurn() { turn = !turn; };
    bool getTurn() const { return turn; };

    void setEnPassantCol(int col) { enPassantCol = col; };
    int getEnPassantCol() const { return enPassantCol; };

    void setCastleRights(int rights) { castleRights = rights; };
    int getCastleRights() const { return castleRights; };


    // constructor de initializare
    Board(const std::unordered_set<std::shared_ptr<Piece>>& pieces_ = {});

    // operator <<
    friend std::ostream& operator<<(std::ostream& os, const Board& bd);

    // method that returns a list of occupied squares 
    // needed for move generation
    std::set<std::pair<int, int>> getOccupiedSquares(bool color) const;


    void makeMove(Piece& piece, const Move& m);

    void unmakeMove(Piece& piece, const Move& m);
};

#endif