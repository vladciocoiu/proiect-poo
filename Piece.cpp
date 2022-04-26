#include "Piece.hpp"
#include "Board.hpp"
#include "King.hpp"

#include <unordered_map>

// constructor de initializare
Piece::Piece(int col_, int row_, bool color_) 
: col{col_}, row{row_}, color{color_} {
    std::cout << "Init Piece\n";
}

// constructor de copiere
Piece::Piece(const Piece& other) : col{other.col}, row{other.row}, color{other.color} {
    std::cout << "Copy Piece\n";
}

// operator =
Piece& Piece::operator=(const Piece& other) {
    col = other.col;
    row = other.row;
    color = other.color;
    std::cout << "= Piece\n";
    return *this;
}

// destructor
Piece::~Piece() {
    std::cout << "Destr Piece\n";
}

// operator <<
std::ostream& operator<<(std::ostream& os, const Piece& pc) {
    os << (pc.color ? "White " : "Black ") << " on square ("
        << pc.getSquare().first << ", " << pc.getSquare().second << ")" << '\n';
    return os;
}

// make the move and check if the friendly king is in check
std::vector<Move> Piece::generateLegalMoves(const King& friendlyKing, std::vector<Move> pseudoLegalMoves, const Board& bd) {
    std::vector<Move> moves;

    for(const auto &move: pseudoLegalMoves) {
        makeMove(move);

        if(!friendlyKing.isInCheck(bd)) moves.push_back(move);

        unmakeMove(move);
    }

    return moves;
}

// method for making a move
// still have to make en passant, captures and castles
// SHOULD ONLY HAVE LEGAL MOVES AS ARGUMENTS
void Piece::makeMove(const Move& m) {
    
    // change piece type if promoted
    // if(m.isPromotion()) type = m.getPromotionPiece();

    // change row and col
    row = m.getRowTo();
    col = m.getColTo();
}

void Piece::unmakeMove(const Move& m) {
    int r = m.getRowTo();
    std::cout << r << '\n';
}
