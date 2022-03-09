#include "Piece.hpp"
#include "Board.hpp"

// constructor de initializare
Piece::Piece(const std::string& type_, char col_, char row_, bool color_) 
: type(type_), col(col_), row(row_), color(color_) {
    std::cout << "Init Piece\n";
}

// constructor de copiere
Piece::Piece(const Piece& other) : type(other.type), col(other.col), row(other.row), color(other.color) {
    std::cout << "Copy Piece\n";
}

// operator =
Piece& Piece::operator=(const Piece& other) {
    type = other.type;
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
    os << (pc.color ? "White " : "Black ") << pc.type << " on square ("
        << pc.row << ", " << pc.col << ")" << '\n';
    return os;
}

// generates all pseudo-legal moves
// (doesn't care about leaving the king in check)
// only implemented for knights now, will probably make separate classes for each piece type later
std::vector<Move> Piece::generatePseudoLegalMoves(const Board& bd) {
    std::vector<Move> moves;

    if (type == "knight") {

        // all directions the knight can move to
        const std::pair<char, char> offsets[8] = {
            {1, 2}, {-1, 2}, {1, -2}, {-1, -2},
            {2, 1}, {-2, 1}, {2, -1}, {-2, -1}
        };

        for (std::pair<char, char> offset: offsets) {
            std::set<std::pair<char, char>> occupiedSquares = bd.getOccupiedSquares(color);

            char newRow = row + offset.first;
            char newCol = col + offset.second;

            // move is out of bounds, so we skip it
            if(newRow < 0 || newRow >= 8 || newCol < 0 || newCol >= 8) continue;

            // if a friendly piece is on that square, we cannot make the move
            if(occupiedSquares.count({newRow, newCol})) continue;

            // make a new move that isn't a capture / castle / en passant / promotion
            // with the corresponding start and end squares and color
            moves.push_back(Move{col, row, newCol, newRow, color, false, false, false, false, ""});
        }

    }
    return moves;
}

// method for making a move
// still have to make en passant, captures and castles
// SHOULD ONLY HAVE LEGAL MOVES AS ARGUMENTS
void Piece::makeMove(const Move& m) {
    
    // change piece type if promoted
    if(m.isPromotion()) type = m.getPromotionPiece();

    // change row and col
    row = m.getRowTo();
    col = m.getColTo();
}
