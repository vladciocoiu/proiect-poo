#pragma once

#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <unordered_set>

#include "Piece.hpp"
#include "MyStack.hpp"

class Piece;

class Board {
private:
    std::unordered_set<std::shared_ptr<Piece>> pieces;
    std::shared_ptr<Piece> blackKing, whiteKing;

    int castleRights; // 4 bytes: 0 for white short, 1 for white long, 2 for black short, 3 for black long
    int enPassantCol;
    bool turn;

    // stacks for irreversible move features in order to restore them when unmaking a move
    MyStack<std::shared_ptr<Piece>> capturedPiecesStack;
    MyStack<int> enPassantColsStack;
    MyStack<int> castleRightsStack;
friend class BoardBuilder;
public:
    // getters and setters
    std::unordered_set<std::shared_ptr<Piece>> getPieces() const { return pieces; };
    void addPiece(std::shared_ptr<Piece> pc) { pieces.insert(pc); };
    void removePiece(std::shared_ptr<Piece> pc) { pieces.erase(pc); }

    std::shared_ptr<Piece> getKing(bool color) { return (color ? whiteKing : blackKing); };
    void setKing(bool color, std::shared_ptr<Piece> k) { if(color) whiteKing = k; else blackKing = k; };

    std::shared_ptr<Piece> popCapturedPiece() { return capturedPiecesStack.pop(); };
    void pushCapturedPiece(std::shared_ptr<Piece> pc) { capturedPiecesStack.push(pc); };

    int popEnPassantCol() { return enPassantColsStack.pop(); };
    void pushEnPassantCol(int col) { enPassantColsStack.push(col); };

    int popCastleRights() { return castleRightsStack.pop(); };
    void pushCastleRights(int rights) { castleRightsStack.push(rights); };

    void switchTurn() { turn = !turn; };
    bool getTurn() const { return turn; };

    void setEnPassantCol(int col) { enPassantCol = col; };
    int getEnPassantCol() const { return enPassantCol; };

    void setCastleRights(int rights) { castleRights = rights; };
    int getCastleRights() const { return castleRights; };

    int computePieceCount() const;

    bool makeMoveFromString(std::string str);
    std::shared_ptr<Piece> findPiece(const Move& mv);

    std::vector<Move> generateAllLegalMoves();

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

// design pattern - builder
class BoardBuilder {
private:
    Board bd;
public:
    BoardBuilder() = default;
    BoardBuilder& epCol(int col) {
        bd.enPassantCol = col;
        return *this;
    }
    BoardBuilder& castleRights(int rights) {
        bd.castleRights = rights;
        return *this;
    }
    BoardBuilder& turn(bool turn) {
        bd.turn = turn;
        return *this;
    }
    BoardBuilder& piece(const Piece &pc) {
        bd.addPiece(pc.clone());
        return *this;
    }
    BoardBuilder& whiteKing(const Piece &pc) {
        bd.setKing(true, pc.clone());
        return *this;
    }
    BoardBuilder& blackKing(const Piece &pc) {
        bd.setKing(false, pc.clone());
        return *this;
    }
    Board build() { return bd; };
};

// design pattern - factory
class BoardFactory {
public:
    static Board initialBoard();
};


#endif