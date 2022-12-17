#include "PrincipalVariation.hpp"

#include <ostream>


bool PrincipalVariation::isMate() const {
    return m;
}

int PrincipalVariation::score() const {
    return s;
}

std::size_t PrincipalVariation::length() const {
    return pv.size();
}

PrincipalVariation::MoveIter PrincipalVariation::begin() const {
    return pv.begin();
}

PrincipalVariation::MoveIter PrincipalVariation::end() const {
    return pv.end();
}

void PrincipalVariation::makeMoveVc(std::vector<Move> p){
    pv=p;
}

 void PrincipalVariation::setScore(int score){
    s=score;
 }
void PrincipalVariation::setMate(bool mt){
    m=mt;
}
std::ostream& operator<<(std::ostream& os, const PrincipalVariation& pv) {
    (void)pv;
    return os;
}
