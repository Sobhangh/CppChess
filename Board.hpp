#ifndef CHESS_ENGINE_BOARD_HPP
#define CHESS_ENGINE_BOARD_HPP

#include "Piece.hpp"
#include "Square.hpp"
#include "Move.hpp"
#include "CastlingRights.hpp"

#include <optional>
#include <iosfwd>
#include <vector>
#include <map>

class Board {
public:

    using Optional = std::optional<Board>;
    using MoveVec = std::vector<Move>;
    using nOp = std::optional<int>;

    Board();
    //~Board();
    void setPiece(const Square& square, const Piece::Optional& piece);
    void setPiecen(const Square& square, const int piece);
    void replacePiecen(const Square& from, const Square& to, const int piece);
    void removePiecen(const Square& square, const int piece);
    Piece::Optional piece(const Square& square) const;
    nOp piecen(const Square& square) const;
    int inCheck(PieceColor t,Square& s) const;

    void setTurn(PieceColor turn);
    PieceColor turn() const;
    void setCastlingRights(CastlingRights cr);
    CastlingRights castlingRights() const;
    void setEnPassantSquare(const Square::Optional& square);
    Square::Optional enPassantSquare() const;
    std::map<const int, std::vector<Square*>> getBoard() const;
    void makeMove(const Move& move);

    void pseudoLegalMoves(MoveVec& moves) const;
    void pseudoLegalMovesFrom(const Square& from, MoveVec& moves) const;
    void PawnpseudoLegalMovesFrom(const Square& from, MoveVec& moves,Piece::Optional& p,const int d) const;
    void BishoppseudoLegalMovesFrom(const Square& from, MoveVec& moves,Piece::Optional& p,const int n,const int e) const;
    void KingpseudoLegalMovesFrom(const Square& from, MoveVec& moves,Piece::Optional& p,const int n,const int e) const;
    void KnightpseudoLegalMovesFrom(const Square& from, MoveVec& moves,Piece::Optional& p,const int h,const int v) const;

private:
        std::map<const int, std::vector<Square*>> board;
        PieceColor t;
        CastlingRights cr;
        Square::Optional EPSquare;
        std::vector<int> cboard;
        /**
        static const int wk = 0;
        static const int bk = 1;
        static const int wq = 2;
        static const int bq = 3;
        static const int wb = 4;
        static const int bb = 5;
        static const int wn = 6;
        static const int bn = 7;
        static const int wr = 8;
        static const int br = 9;
        static const int wp = 10;
        static const int bp = 11;
        */
};

std::ostream& operator<<(std::ostream& os, const Board& board);

#endif
