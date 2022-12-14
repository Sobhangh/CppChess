#include "Square.hpp"

#include <ostream>

Square::Square(Index index):i(index),r(index/8),f(index%8)
{
    //(void)index;
}

int Square::HammingDist(const Square& x,const Square& y){
    int xDist = x.file() - y.file();
    if(xDist<0){
        xDist = xDist *(-1);
    }
    int yDist = x.rank() - y.rank();
    if(yDist<0){
        yDist = yDist * (-1);
    }

    return xDist +yDist;
}

Square::Optional Square::fromCoordinates(Coordinate file, Coordinate rank) {
    if(file==0 && rank==0){
        return Square::A1;
    }
    else if (rank==0  && file==1)
    {
        return Square::B1;
    }
     else if (rank==0  && file==2)
    {
        return Square::C1;
    }
     else if (rank==0  && file==3)
    {
        return Square::D1;
    }
     else if (rank==0  && file==4)
    {
        return Square::E1;
    }
     else if (rank==0  && file==5)
    {
        return Square::F1;
    }
     else if (rank==0  && file==6)
    {
        return Square::G1;
    }
     else if (rank==0  && file==7)
    {
        return Square::H1;
    }
     else if (rank==1  && file==0)
    {
        return Square::A2;
    }
     else if (rank==1  && file==1)
    {
        return Square::B2;
    }
     else if (rank==1  && file==2)
    {
        return Square::C2;
    }
     else if (rank==1  && file==3)
    {
        return Square::D2;
    }
     else if (rank==1  && file==4)
    {
        return Square::E2;
    }
     else if (rank==1  && file==5)
    {
        return Square::F2;
    }
     else if (rank==1  && file==6)
    {
        return Square::G2;
    }
     else if (rank==1  && file==7)
    {
        return Square::H2;
    }
     else if (rank==2  && file==0)
    {
        return Square::A3;
    }
     else if (rank==2  && file==1)
    {
        return Square::B3;
    }
     else if (rank==2  && file==2)
    {
        return Square::C3;
    }
     else if (rank==2  && file==3)
    {
        return Square::D3;
    }
     else if (rank==2  && file==4)
    {
        return Square::E3;
    }
     else if (rank==2  && file==5)
    {
        return Square::F3;
    }
     else if (rank==2  && file==6)
    {
        return Square::G3;
    }
     else if (rank==2  && file==7)
    {
        return Square::H3;
    }
     else if (rank==3  && file==0)
    {
        return Square::A4;
    }
     else if (rank==3  && file==1)
    {
        return Square::B4;
    }
     else if (rank==3  && file==2)
    {
        return Square::C4;
    }
     else if (rank==3  && file==3)
    {
        return Square::D4;
    }
     else if (rank==3  && file==4)
    {
        return Square::E4;
    }
     else if (rank==3  && file==5)
    {
        return Square::F4;
    }
     else if (rank==3  && file==6)
    {
        return Square::G4;
    }
     else if (rank==3  && file==7)
    {
        return Square::H4;
    }
     else if (rank==4  && file==0)
    {
        return Square::A5;
    }
     else if (rank==4  && file==1)
    {
        return Square::B5;
    }
     else if (rank==4  && file==2)
    {
        return Square::C5;
    }
     else if (rank==4  && file==3)
    {
        return Square::D5;
    }
     else if (rank==4  && file==4)
    {
        return Square::E5;
    }
     else if (rank==4  && file==5)
    {
        return Square::F5;
    }
     else if (rank==4  && file==6)
    {
        return Square::G5;
    }
     else if (rank==4  && file==7)
    {
        return Square::H5;
    }
     else if (rank==5  && file==0)
    {
        return Square::A6;
    }
     else if (rank==5  && file==1)
    {
        return Square::B6;
    }
     else if (rank==5  && file==2)
    {
        return Square::C6;
    }
     else if (rank==5  && file==3)
    {
        return Square::D6;
    }
     else if (rank==5  && file==4)
    {
        return Square::E6;
    }
     else if (rank==5  && file==5)
    {
        return Square::F6;
    }
     else if (rank==5  && file==6)
    {
        return Square::G6;
    }
     else if (rank==5  && file==7)
    {
        return Square::H6;
    }
     else if (rank==6  && file==0)
    {
        return Square::A7;
    }
     else if (rank==6  && file==1)
    {
        return Square::B7;
    }
     else if (rank==6  && file==2)
    {
        return Square::C7;
    }
     else if (rank==6  && file==3)
    {
        return Square::D7;
    }
     else if (rank==6  && file==4)
    {
        return Square::E7;
    }
     else if (rank==6  && file==5)
    {
        return Square::F7;
    }
     else if (rank==6  && file==6)
    {
        return Square::G7;
    }
     else if (rank==6  && file==7)
    {
        return Square::H7;
    }
     else if (rank==7  && file==0)
    {
        return Square::A8;
    }
     else if (rank==7  && file==1)
    {
        return Square::B8;
    }
     else if (rank==7  && file==2)
    {
        return Square::C8;
    }
     else if (rank==7  && file==3)
    {
        return Square::D8;
    }
     else if (rank==7  && file==4)
    {
        return Square::E8;
    }
     else if (rank==7  && file==5)
    {
        return Square::F8;
    }
     else if (rank==7  && file==6)
    {
        return Square::G8;
    }
     else if (rank==7  && file==7)
    {
        return Square::H8;
    }
    else{
        return std::nullopt;
    }
   
}

Square::Optional Square::fromIndex(Index index) {
    if(index>=64){
        return std::nullopt;
    }
    else{
        return Square::fromCoordinates(index%8,index/8);
    }
}

Square::Optional Square::fromName(const std::string& name) {
    if(name=="a1"){
        return Square::A1;
    }
    else if (name=="a2")
    {
        return Square::A2;
    }
    else if (name=="a3")
    {
        return Square::A3;
    }
    else if (name=="a4")
    {
        return Square::A4;
    }
    else if (name=="a5")
    {
        return Square::A5;
    }
    else if (name=="a6")
    {
        return Square::A6;
    }
    else if (name=="a7")
    {
        return Square::A7;
    }
    else if (name=="a8")
    {
        return Square::A8;
    }
    else if (name=="b1")
    {
        return Square::B1;
    }
    else if (name=="b2")
    {
        return Square::B2;
    }
    else if (name=="b3")
    {
        return Square::B3;
    }
    else if (name=="b4")
    {
        return Square::B4;
    }
    else if (name=="b5")
    {
        return Square::B5;
    }
    else if (name=="b6")
    {
        return Square::B6;
    }
    else if (name=="b7")
    {
        return Square::B7;
    }
    else if (name=="b8")
    {
        return Square::B8;
    }
    else if (name=="c1")
    {
        return Square::C1;
    }
    else if (name=="c2")
    {
        return Square::C2;
    }
    else if (name=="c3")
    {
        return Square::C3;
    }
    else if (name=="c4")
    {
        return Square::C4;
    }
    else if (name=="c5")
    {
        return Square::C5;
    }
    else if (name=="c6")
    {
        return Square::C6;
    }
    else if (name=="c7")
    {
        return Square::C7;
    }
    else if (name=="c8")
    {
        return Square::C8;
    }
    else if (name=="d1")
    {
        return Square::D1;
    }
    else if (name=="d2")
    {
        return Square::D2;
    }
    else if (name=="d3")
    {
        return Square::D3;
    }
    else if (name=="d4")
    {
        return Square::D4;
    }
    else if (name=="d5")
    {
        return Square::D5;
    }
    else if (name=="d6")
    {
        return Square::D6;
    }
    else if (name=="d7")
    {
        return Square::D7;
    }
    else if (name=="d8")
    {
        return Square::D8;
    }
    else if (name=="e1")
    {
        return Square::E1;
    }
    else if (name=="e2")
    {
        return Square::E2;
    }
    else if (name=="e3")
    {
        return Square::E3;
    }
    else if (name=="e4")
    {
        return Square::E4;
    }
    else if (name=="e5")
    {
        return Square::E5;
    }
    else if (name=="e6")
    {
        return Square::E6;
    }
    else if (name=="e7")
    {
        return Square::E7;
    }
    else if (name=="e8")
    {
        return Square::E8;
    }
    else if (name=="f1")
    {
        return Square::F1;
    }
    else if (name=="f2")
    {
        return Square::F2;
    }
    else if (name=="f3")
    {
        return Square::F3;
    }
    else if (name=="f4")
    {
        return Square::F4;
    }
    else if (name=="f5")
    {
        return Square::F5;
    }
    else if (name=="f6")
    {
        return Square::F6;
    }
    else if (name=="f7")
    {
        return Square::F7;
    }
    else if (name=="f8")
    {
        return Square::F8;
    }
    else if (name=="g1")
    {
        return Square::G1;
    }
    else if (name=="g2")
    {
        return Square::G2;
    }
    else if (name=="g3")
    {
        return Square::G3;
    }
    else if (name=="g4")
    {
        return Square::G4;
    }
    else if (name=="g5")
    {
        return Square::G5;
    }
    else if (name=="g6")
    {
        return Square::G6;
    }
    else if (name=="g7")
    {
        return Square::G7;
    }
    else if (name=="g8")
    {
        return Square::G8;
    }
    else if (name=="h1")
    {
        return Square::H1;
    }
    else if (name=="h2")
    {
        return Square::H2;
    }
    else if (name=="h3")
    {
        return Square::H3;
    }
    else if (name=="h4")
    {
        return Square::H4;
    }
    else if (name=="h5")
    {
        return Square::H5;
    }
    else if (name=="h6")
    {
        return Square::H6;
    }
    else if (name=="h7")
    {
        return Square::H7;
    }
    else if (name=="h8")
    {
        return Square::H8;
    }
    return std::nullopt;
}

Square::Coordinate Square::file() const {
    return f;
}

Square::Coordinate Square::rank() const {
    return r;
}

Square::Index Square::index() const {
    return i;
}


const Square Square::A1 = Square( 0 + 0);
const Square Square::B1 = Square( 0 + 1);
const Square Square::C1 = Square( 0 + 2);
const Square Square::D1 = Square( 0 + 3);
const Square Square::E1 = Square( 0 + 4);
const Square Square::F1 = Square( 0 + 5);
const Square Square::G1 = Square( 0 + 6);
const Square Square::H1 = Square( 0 + 7);

const Square Square::A2 = Square( 8 + 0);
const Square Square::B2 = Square( 8 + 1);
const Square Square::C2 = Square( 8 + 2);
const Square Square::D2 = Square( 8 + 3);
const Square Square::E2 = Square( 8 + 4);
const Square Square::F2 = Square( 8 + 5);
const Square Square::G2 = Square( 8 + 6);
const Square Square::H2 = Square( 8 + 7);

const Square Square::A3 = Square(16 + 0);
const Square Square::B3 = Square(16 + 1);
const Square Square::C3 = Square(16 + 2);
const Square Square::D3 = Square(16 + 3);
const Square Square::E3 = Square(16 + 4);
const Square Square::F3 = Square(16 + 5);
const Square Square::G3 = Square(16 + 6);
const Square Square::H3 = Square(16 + 7);

const Square Square::A4 = Square(24 + 0);
const Square Square::B4 = Square(24 + 1);
const Square Square::C4 = Square(24 + 2);
const Square Square::D4 = Square(24 + 3);
const Square Square::E4 = Square(24 + 4);
const Square Square::F4 = Square(24 + 5);
const Square Square::G4 = Square(24 + 6);
const Square Square::H4 = Square(24 + 7);

const Square Square::A5 = Square(32 + 0);
const Square Square::B5 = Square(32 + 1);
const Square Square::C5 = Square(32 + 2);
const Square Square::D5 = Square(32 + 3);
const Square Square::E5 = Square(32 + 4);
const Square Square::F5 = Square(32 + 5);
const Square Square::G5 = Square(32 + 6);
const Square Square::H5 = Square(32 + 7);

const Square Square::A6 = Square(40 + 0);
const Square Square::B6 = Square(40 + 1);
const Square Square::C6 = Square(40 + 2);
const Square Square::D6 = Square(40 + 3);
const Square Square::E6 = Square(40 + 4);
const Square Square::F6 = Square(40 + 5);
const Square Square::G6 = Square(40 + 6);
const Square Square::H6 = Square(40 + 7);

const Square Square::A7 = Square(48 + 0);
const Square Square::B7 = Square(48 + 1);
const Square Square::C7 = Square(48 + 2);
const Square Square::D7 = Square(48 + 3);
const Square Square::E7 = Square(48 + 4);
const Square Square::F7 = Square(48 + 5);
const Square Square::G7 = Square(48 + 6);
const Square Square::H7 = Square(48 + 7);

const Square Square::A8 = Square(56 + 0);
const Square Square::B8 = Square(56 + 1);
const Square Square::C8 = Square(56 + 2);
const Square Square::D8 = Square(56 + 3);
const Square Square::E8 = Square(56 + 4);
const Square Square::F8 = Square(56 + 5);
const Square Square::G8 = Square(56 + 6);
const Square Square::H8 = Square(56 + 7);

std::ostream& operator<<(std::ostream& os, const Square& square) {

    char f='a';
    if(square.file()==0){
        f='a';
    }
    else if (square.file()==1)
    {
        f='b';
    }
    else if (square.file()==2)
    {
        f='c';
    }
    else if (square.file()==3)
    {
        f='d';
    }
    else if (square.file()==4)
    {
        f='e';
    }
    else if (square.file()==5)
    {
        f='f';
    }
    else if (square.file()==6)
    {
        f='g';
    }
    else if (square.file()==7)
    {
        f='h';
    }

    char r ='1';
    if(square.rank()==0){
        r='1';
    }
    else if (square.rank()==1)
    {
        r='2';
    }
    else if (square.rank()==2)
    {
        r='3';
    }
    else if (square.rank()==3)
    {
        r='4';
    }
    else if (square.rank()==4)
    {
        r='5';
    }
    else if (square.rank()==5)
    {
        r='6';
    }
    else if (square.rank()==6)
    {
        r='7';
    }
    else if (square.rank()==7)
    {
        r='8';
    }
    char  crdnt[3] = {f,r,'\0'};
    return os << crdnt;
}

std::string Square::getName() const{
    char F='a';
    if(f==0){
        F='a';
    }
    else if (f==1)
    {
        F='b';
    }
    else if (f==2)
    {
        F='c';
    }
    else if (f==3)
    {
        F='d';
    }
    else if (f==4)
    {
        F='e';
    }
    else if (f==5)
    {
        F='f';
    }
    else if (f==6)
    {
        F='g';
    }
    else if (f==7)
    {
        F='h';
    }

    char R ='1';
    if(r==0){
        R='1';
    }
    else if (r==1)
    {
        R='2';
    }
    else if (r==2)
    {
        R='3';
    }
    else if (r==3)
    {
        R='4';
    }
    else if (r==4)
    {
        R='5';
    }
    else if (r==5)
    {
        R='6';
    }
    else if (r==6)
    {
        R='7';
    }
    else if (r==7)
    {
        R='8';
    }
    char  crdnt[3] = {F,R,'\0'};
    return (std::string)crdnt;
}

bool operator<(const Square& lhs, const Square& rhs) {
    if(lhs.index()<rhs.index()){
        return true;
    }
    return false;
}

bool operator==(const Square& lhs, const Square& rhs) {
    if(lhs.index()==rhs.index()){
        return true;
    }
    return false;
}
