#ifndef CHESS_ENGINE_PRINCIPALVARIATION_HPP
#define CHESS_ENGINE_PRINCIPALVARIATION_HPP

#include "Move.hpp"
#include "Piece.hpp"

#include <iosfwd>
#include <cstddef>
#include <vector>

class PrincipalVariation {
public:

    using MoveIter = std::vector<Move>::const_iterator;

    bool isMate() const;
    int score() const;

    std::size_t length() const;
    MoveIter begin() const;
    MoveIter end() const;
    void makeMoveVc(std::vector<Move> pv);
    void setScore(int s);
    void setMate(bool m);
    Move::Optional getMove(int i) const;
private:
    int s;
    bool m;
    std::vector<Move> pv;
};

std::ostream& operator<<(std::ostream& os, const PrincipalVariation& pv);

#endif
