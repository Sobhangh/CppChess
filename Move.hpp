#ifndef CHESS_ENGINE_MOVE_HPP
#define CHESS_ENGINE_MOVE_HPP

#include "Square.hpp"
#include "Piece.hpp"

#include <iosfwd>
#include <optional>
#include <string>

class Move {
public:

    using Optional = std::optional<Move>;

    Move(const Square& from, const Square& to,
         const std::optional<PieceType>& promotion = std::nullopt);

    static Optional fromUci(const std::string& uci);
    std::string toUci();

    Square from() const;
    Square to() const;
    std::optional<PieceType> promotion() const;

private:
    Square f;
    Square t;
    std::optional<PieceType> prom;

};

std::ostream& operator<<(std::ostream& os, const Move& move);

// Needed for std::map, std::set
bool operator<(const Move& lhs, const Move& rhs);
bool operator==(const Move& lhs, const Move& rhs);

#endif
