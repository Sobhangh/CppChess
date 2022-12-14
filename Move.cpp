#include "Move.hpp"

#include <ostream>

int angle4(int x,int y);
bool equalDistAndAngle(const Move& lhs, const Move& rhs);

Move::Move(const Square& from, const Square& to,
           const std::optional<PieceType>& promotion):f(from),t(to),prom(promotion)
{
   
}

Move::Optional Move::fromUci(const std::string& uci) {
    if(uci.length()>=4 && uci.length()<=5){
        char fr[3] ={uci[0],uci[1],'\0'};
        char too[3] ={uci[2],uci[3],'\0'};
        std::optional<Square> F = Square::fromName(fr);
        std::optional<Square> T = Square::fromName(too);
        if(F == std::nullopt || T ==std::nullopt){
            return std::nullopt;
        }
        Square Fr = (Square)F.value();
        Square To = (Square)T.value();
        if(uci.length()==5){
            if(Piece::fromSymbol(uci[4]).has_value()){
                std::optional<PieceType> pr = Piece::fromSymbol(uci[4]).value().type();
                return Move::Move(Fr,To,pr);
            }
             return std::nullopt;
        }
        return Move::Move(Fr,To);
    }
    
    
    return std::nullopt;
}

Square Move::from() const {
    return f;
}

Square Move::to() const {
    return t;
}

std::optional<PieceType> Move::promotion() const {
    return prom;
}

std::ostream& operator<<(std::ostream& os, const Move& move) {
    Square F = move.from();
    Square T = move.to();
    auto t=  T.getName();
    auto f= F.getName();
    if(move.promotion().has_value()){
        char p = Piece::typeChar(move.promotion().value());
        return os << (f+t+p);
    }
    return os<<(f+t);
}

bool equalDistAndAngle(const Move& lhs, const Move& rhs){
    if(lhs.to().rank()< rhs.to().rank()){
        return true;
    }
    else if (lhs.to().rank()> rhs.to().rank())
    {
        return false;
    }
    else{
        if(lhs.to().file()< rhs.to().file()){
            return true;
        }
        return false;
    }  
}
bool operator<(const Move& lhs, const Move& rhs) {
    int DistLhs = Square::HammingDist(lhs.from(),lhs.to());
    int DistRhs = Square::HammingDist(rhs.from(),rhs.to());
    if(DistLhs<DistRhs){
        return true;
    }
    if(DistLhs==DistRhs){
        if(lhs.from() == rhs.from() && lhs.to()==rhs.to() ){
            //Other possibilities for promotions?????
            return false;
        }
        //first compare rank : the higher the rank higher the move, if equal compare their file.
        if(DistLhs==0){
            return equalDistAndAngle(lhs,rhs);
        }
        int lhsXDist = lhs.to().file()-lhs.from().file();
        int lhsYDist = lhs.to().rank()-lhs.from().rank();
        int rhsXDist = rhs.to().file()-rhs.from().file();
        int rhsYDist = rhs.to().rank()-rhs.from().rank();
        int lhsAngle = angle4(lhsXDist,lhsYDist);
        int rhsAngle = angle4(rhsXDist,rhsYDist);
        // The lower the angle number the higher the move.
        if(lhsAngle>rhsAngle){
            return true;
        }
        else if(rhsAngle>lhsAngle){
            return false;
        }
        else{
            if(lhsAngle ==1 || lhsAngle == 2){
                if(lhsXDist<rhsXDist){
                    return true;
                }
                else if (lhsXDist>rhsXDist)
                {
                    return false;
                }
                else{
                    return equalDistAndAngle(lhs,rhs);
                }
                
            }
            else{
                if(lhsXDist>rhsXDist){
                    return true;
                }
                else if (lhsXDist<rhsXDist)
                {
                    return false;
                }
                else{
                    return equalDistAndAngle(lhs,rhs);
                }
            }
        }
    }
    
    return false;
}

int angle4(int x,int y){
    if(x>0 && y>=0){
        return 1;
    }
    if(x<=0 && y>0){
        return 2;
    }
    if(x<0 && y<=0){
        return 3;
    }
    if(x>=0 && y<0){
        return 4;
    }
    if (x==0 && y==0)
    {
        return 0;
    }
    return 0;
    
}   

bool operator==(const Move& lhs, const Move& rhs) {
    if(lhs.from() == rhs.from() && lhs.to()==rhs.to() ){
        if(lhs.promotion().has_value() != rhs.promotion().has_value()){
            return false;
        }
        if(lhs.promotion().has_value()){
            if(lhs.promotion().value() == rhs.promotion().value()){
                return true;
            }
            return false;
        }
        return true;
    }
    return false;
}
