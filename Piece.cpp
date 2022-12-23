#include "Piece.hpp"

#include <ostream>

Piece::Piece(PieceColor color, PieceType type) : c(color),t(type),num(getNum(color,type))
{

}

PieceColor Piece::getColor(int num){
    if(num % 2 ==1){
        return PieceColor::White;
    }
    return PieceColor::Black;
}

//Returns the modulo of the number by 2
int Piece::getNumEven(PieceColor c){
    if(c ==PieceColor::White){
        return 1;
    }
    return 0;
}


char Piece::getCharFNum(int num){
    if(num<1 || num>12){
        return '0';
    }

    if(num==1){
        return 'P';
    }
    else if(num==3){
        return 'N';
    }
    else if(num==5){
        return 'B';
    }
    else if(num==7){
        return 'R';
    }
    else if(num==9){
        return 'Q';
    }
    else if(num==11){
        return 'K';
    }


    if(num==2){
        return 'p';
    }
    else if(num==4){
        return 'n';
    }
    else if(num==6){
        return 'b';
    }
    else if(num==8){
        return 'r';
    }
    else if(num==10){
        return 'q';
    }
    else if(num==12){
        return 'k';
    }
    return '0';
}
int Piece::getNum(PieceColor color, PieceType type){
    if(color == PieceColor::White){
        if(type == PieceType::Pawn){
            return 1;
        }
        else if (type == PieceType::Knight)
        {
            return 3;
        }
        else if (type == PieceType::Bishop)
        {
            return 5;
        }
        else if (type == PieceType::Rook)
        {
            return 7;
        }
        else if (type == PieceType::Queen)
        {
            return 9;
        }
        else if (type == PieceType::King)
        {
            return 11;
        }
    }
    else{
        if(type == PieceType::Pawn){
            return 2;
        }
        else if (type == PieceType::Knight)
        {
            return 4;
        }
        else if (type == PieceType::Bishop)
        {
            return 6;
        }
        else if (type == PieceType::Rook)
        {
            return 8;
        }
        else if (type == PieceType::Queen)
        {
            return 10;
        }
        else if (type == PieceType::King)
        {
            return 12;
        }
    }
    return 0;
}

Piece::Optional Piece::fromSymbol(char symbol) {
    if(symbol =='P'){
        return Piece(PieceColor::White,PieceType::Pawn);
    }
    else if (symbol =='p')
    {
       return Piece(PieceColor::Black,PieceType::Pawn);
    }
    else if (symbol =='K')
    {
       return Piece(PieceColor::White,PieceType::King);
    }
    else if (symbol =='k')
    {
       return Piece(PieceColor::Black,PieceType::King);
    }
    else if (symbol =='B')
    {
       return Piece(PieceColor::White,PieceType::Bishop);
    }
    else if (symbol =='b')
    {
       return Piece(PieceColor::Black,PieceType::Bishop);
    }
     else if (symbol =='R')
    {
       return Piece(PieceColor::White,PieceType::Rook);
    }
     else if (symbol =='r')
    {
       return Piece(PieceColor::Black,PieceType::Rook);
    }
       else if (symbol =='Q')
    {
       return Piece(PieceColor::White,PieceType::Queen);
    }
        else if (symbol =='q')
    {
       return Piece(PieceColor::Black,PieceType::Queen);
    }
      else if (symbol =='N')
    {
       return Piece(PieceColor::White,PieceType::Knight);
    }
        else if (symbol =='n')
    {
       return Piece(PieceColor::Black,PieceType::Knight);
    }
    return std::nullopt;
}

PieceColor Piece::color() const {
    //WOULD IT BE TRANSFORM IN TO CONSTANT??????
    return c;
}

PieceType Piece::type() const {
    return t;
}

int Piece::numb() const {
    return num;
}

char Piece::typeChar(PieceType t){
    if(t == PieceType::Bishop){
        return 'b';
    }
    else if (t == PieceType::King)
    {
        return 'k';
    }
    else if (t == PieceType::Knight)
    {
        return 'n';
    }
    else if (t == PieceType::Pawn)
    {
        return 'p';
    }
    else if (t == PieceType::Queen)
    {
        return 'q';
    }
    else{
        return 'r';
    }
}

const Piece Piece::wp = Piece(PieceColor::White,PieceType::Pawn); 
const Piece Piece::wb = Piece(PieceColor::White,PieceType::Bishop);
const Piece Piece::wk = Piece(PieceColor::White,PieceType::King); 
const Piece Piece::wn = Piece(PieceColor::White,PieceType::Knight);
const Piece Piece::wq = Piece(PieceColor::White,PieceType::Queen); 
const Piece Piece::wr = Piece(PieceColor::White,PieceType::Rook);
const Piece Piece::bp = Piece(PieceColor::Black,PieceType::Pawn); 
const Piece Piece::bb = Piece(PieceColor::Black,PieceType::Bishop);
const Piece Piece::bk = Piece(PieceColor::Black,PieceType::King); 
const Piece Piece::bn = Piece(PieceColor::Black,PieceType::Knight);
const Piece Piece::bq = Piece(PieceColor::Black,PieceType::Queen); 
const Piece Piece::br = Piece(PieceColor::Black,PieceType::Rook);

bool operator==(const Piece& lhs, const Piece& rhs) {
    if(lhs.color()==rhs.color() && lhs.type()==rhs.type()){
        return true;
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, const Piece& piece) {
    if(piece.color()==PieceColor::White){
        if(piece.type()==PieceType::Bishop){
            return os << 'B';
        }
        else if (piece.type()==PieceType::King)
        {
            return os << 'K';
        }
        else if (piece.type()==PieceType::Knight)
        {
            return os << 'N';
        }
        else if (piece.type()==PieceType::Pawn)
        {
            return os << 'P';
        }
        else if (piece.type()==PieceType::Queen)
        {
            return os << 'Q';
        }
        else 
        {
            return os << 'R';
        }
    }
    else{
        if(piece.type()==PieceType::Bishop){
            return os << 'b';
        }
        else if (piece.type()==PieceType::King)
        {
            return os << 'k';
        }
        else if (piece.type()==PieceType::Knight)
        {
            return os << 'n';
        }
        else if (piece.type()==PieceType::Pawn)
        {
            return os << 'p';
        }
        else if (piece.type()==PieceType::Queen)
        {
            return os << 'q';
        }
        else 
        {
            return os << 'r';
        }
    }
}

PieceColor operator!(PieceColor color) {
    if(color==PieceColor::Black){
        return PieceColor::White;
    }
    return PieceColor::Black;
}
