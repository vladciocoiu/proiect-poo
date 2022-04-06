#include "Piece.hpp"
#include "Board.hpp"

#include <unordered_map>

// constructor de initializare
Piece::Piece(const std::string& type_, int col_, int row_, bool color_) 
: type{type_}, col{col_}, row{row_}, color{color_} {
    std::cout << "Init Piece\n";
}

// constructor de copiere
Piece::Piece(const Piece& other) : type{other.type}, col{other.col}, row{other.row}, color{other.color} {
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
        << pc.getSquare().first << ", " << pc.getSquare().second << ")" << '\n';
    return os;
}

// generates all pseudo-legal moves
// (doesn't care about leaving the king in check)
// will probably make separate classes for each piece type later
// TODO: code captures and promotions
std::vector<Move> Piece::generatePseudoLegalMoves(const Board& bd) {

    // map for every move offset of every piece type
    static const std::unordered_map<std::string, std::vector<std::pair<int, int>>> OFFSETS = {
        {
            "knight", 
            {
                {1, 2}, {-1, 2}, {1, -2}, {-1, -2},
                {2, 1}, {-2, 1}, {2, -1}, {-2, -1}
            }
        },
        {
            "king", 
            {
                {1, 0}, {-1, 0}, {0, 1}, {0, -1},
                {1, 1}, {-1, 1}, {1, -1}, {-1, -1}
            }
        },
    };

    std::vector<Move> moves;

    // get squares occupied by friendly pieces
    std::set<std::pair<int, int>> occupiedSquares = bd.getOccupiedSquares(color);

    // squares occupied by enemy pieces
    std::set<std::pair<int, int>> enemySquares = bd.getOccupiedSquares(!color);

    if(type == "bishop" || type == "queen") {
        const std::pair<int, int> square = getSquare();
        
        // signs for all 4 directions
        std::vector<std::pair<int, int>> dirs = {{1, 1}, {-1, -1}, {-1, 1}, { 1, -1}};

        // loop through all directions
        for(std::pair<int, int> sign: dirs) {
            for (int offset = 1; offset < 8; offset++) {
                int newRow = square.first + sign.first * offset;
                int newCol = square.second; + sign.second * offset;

                // out of bounds;
                if(newRow >= 8 || newCol >= 8 || newRow < 0 || newCol < 0) break;

                // square is occupied
                if(occupiedSquares.count({ newRow, newCol })) break;

                // add move
                moves.push_back(Move{square.second, square.first, newCol, newRow, color, false, false, false, false, ""});

                // break after finding an enemy piece
                if(enemySquares.count({ newRow, newCol })) break;
            }
        }
    }  
    if(type == "rook" || type == "queen") {
        const std::pair<int, int> square = getSquare();
        
        // signs for all 4 directions
        std::vector<std::pair<int, int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        // loop through all directions
        for(std::pair<int, int> sign: dirs) {
            for (int offset = 1; offset < 8; offset++) {
                int newRow = square.first + sign.first * offset;
                int newCol = square.second; + sign.second * offset;

                // out of bounds;
                if(newRow >= 8 || newCol >= 8 || newRow < 0 || newCol < 0) break;

                // square is occupied
                if(occupiedSquares.count({ newRow, newCol })) break;

                // add move
                moves.push_back(Move{square.second, square.first, newCol, newRow, color, false, false, false, false, ""});

                // break after finding an enemy piece
                if(enemySquares.count({ newRow, newCol })) break;
            }
        }
    }  
    if (type == "pawn") {
        // TODO: code en passant

        // white pawns move to bigger rows, and black pawns to smaller ones
        static const int ROW_OFFSET = (color ? 1 : -1);

        // needed for the 2 square move (pawns can only move 2 squares from their initial row)
        static const int STARTING_ROW = (color ? 1 : 6);

        // the row where the pawn can promote
        // static const int PROMOTION_ROW = (color ? 7 : 0);

        // normal 1 square move
        if(row + ROW_OFFSET >= 0 && row + ROW_OFFSET < 8 && !occupiedSquares.count({row + ROW_OFFSET, col})) {
            moves.push_back(Move{col, row, col, row + ROW_OFFSET, color, false, false, false, false, ""});

            // 2 square move
            // can be possible only if normal move is possible
            if(row == STARTING_ROW && row + 2 * ROW_OFFSET >= 0 
            && row + 2 * ROW_OFFSET < 8 && !occupiedSquares.count({row + ROW_OFFSET, col})) {
                moves.push_back(Move{col, row, col, row + 2 * ROW_OFFSET, color, false, false, false, false, ""});
            }
        }

    } 
    if(type == "king" || type == "knight") {
        for (auto [rowOffset, colOffset]: OFFSETS.at(type)) {

            int newRow = row + rowOffset;
            int newCol = col + colOffset;

            // move is out of bounds, so we skip it
            if(newRow < 0 || newRow >= 8 || newCol < 0 || newCol >= 8) continue;

            // if a friendly piece is on that square, we cannot make the move
            if(occupiedSquares.count({newRow, newCol})) continue;

            // make a new move that isn't a capture / castle / en passant / promotion
            // with the corresponding squares and color
            moves.push_back(Move{col, row, newCol, newRow, color, false, false, false, false, ""});
        }

    }
    // TODO: code castle moves

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
