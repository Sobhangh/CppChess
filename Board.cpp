#include "Board.hpp"

#include <ostream>
#include <cassert>
#include <cmath>
#include <vector>
#include "Piece.hpp"
#include "Square.hpp"

Board::Board():t(PieceColor::White),
                cr(CastlingRights::All),
                EPSquare(std::nullopt)
{
    /**
    board[Piece::wk.numb()]=std::vector<Square*> {new Square(Square::E1)};
    board[Piece::bk.numb()]=std::vector<Square*> {new Square(Square::E8)};

    board[Piece::wq.numb()]=std::vector<Square*> {new Square(Square::D1)};
    board[Piece::bq.numb()]=std::vector<Square*> {new Square(Square::D8)};

    board[Piece::wb.numb()]=std::vector<Square*> {new Square(Square::C1),new Square(Square::F1)};
    board[Piece::bb.numb()]=std::vector<Square*> {new Square(Square::C8),new Square(Square::F8)};

    board[Piece::wn.numb()]=std::vector<Square*> {new Square(Square::B1),new Square(Square::G1)};
    board[Piece::bn.numb()]=std::vector<Square*> {new Square(Square::B8),new Square(Square::G8)};

    board[Piece::wr.numb()]=std::vector<Square*> {new Square(Square::A1),new Square(Square::H1)};
    board[Piece::br.numb()]=std::vector<Square*> {new Square(Square::A8),new Square(Square::H8)};

    board[Piece::wp.numb()]=std::vector<Square*> {new Square(Square::A2),new Square(Square::B2),new Square(Square::C2),new Square(Square::D2),new Square(Square::E2),new Square(Square::F2),new Square(Square::G2) ,new Square(Square::H2)};
    board[Piece::bp.numb()]=std::vector<Square*> {new Square(Square::A7),new Square(Square::B7),new Square(Square::C7),new Square(Square::D7),new Square(Square::E7),new Square(Square::F7),new Square(Square::G7) ,new Square(Square::H7)};
    */
}

Board::~Board(){
    for(auto it = board.begin(); it != board.end();++it){
        unsigned int vecSize = (it->second).size();
        for(unsigned int i = 0; i < vecSize; i++)
        {
            auto e = (it->second)[i];
            (it->second).erase((it->second).begin()+i);
            delete e;  
        }
    }
}

void Board::setPiece(const Square& square, const Piece::Optional& piece) {
   if(piece.has_value()){
        bool added =false;
        bool removed =false;
        for(auto it = board.begin(); it != board.end();++it){
            if(!added && piece.value().numb() == (it->first)){
                board[it->first].push_back(new Square(square));
                added = true;
                if(removed){
                    return;
                }
            }
            else if(!removed)
            {
                unsigned int vecSize = (it->second).size();
                for(unsigned int i = 0; i < vecSize; i++)
                {
                    if(*(it->second)[i]==square){
                        auto e = (it->second)[i];
                        (it->second).erase((it->second).begin()+i);
                        delete e;
                        removed = true;
                        break;
                    }
                }
                if(added){
                    return;
                }
            }
            
        }
        if(!added){
            board[piece.value().numb()]= std::vector<Square*> {new Square(square)};
        }
        
   }
}

void Board::setPiecen(const Square& square, const int piece){
    if(piece>12 || piece<1){
        return;
    }
    for(auto it = board.begin(); it != board.end();++it){
        if(piece == (it->first)){
            board[it->first].push_back(new Square(square));
            return;
        }
    }
    board[piece]= std::vector<Square*> {new Square(square)};
}

void Board::removePiecen(const Square& square, const int piece){
    if(piece>12 || piece<1){
        return;
    }
    for(auto it = board.begin(); it != board.end();++it){
        if(piece == (it->first)){
            unsigned int vecSize = (it->second).size();
            for(unsigned int i = 0; i < vecSize; i++)
            {
                if(*(it->second)[i]==square){
                    auto e = (it->second)[i];
                    (it->second).erase((it->second).begin()+i);
                    delete e;
                    return;
                }
            }
            return;
        }
    }
}

void Board::replacePiecen(const Square& from,const Square& to, const int piece){
    if(piece>12 || piece<1){
        return;
    }
    for(auto it = board.begin(); it != board.end();++it){
        if(piece == (it->first)){
            unsigned int vecSize = (it->second).size();
            for(unsigned int i = 0; i < vecSize; i++)
            {
                if(*(it->second)[i]==from){
                    auto e = (it->second)[i];
                    (it->second)[i] = new Square(to);
                    //(it->second).erase((it->second).begin()+i);
                    delete e;
                    return;
                }
            }
            board[it->first].push_back(new Square(to));
            return;
        }
    }
}
Board::nOp Board::piecen(const Square& square) const{
    for(auto it = board.begin(); it != board.end();++it){
            unsigned int vecSize = (it->second).size();
            for(unsigned int i = 0; i < vecSize; i++)
            {
                if(*(it->second)[i]==square){
                    return (it->first);
                }
            }
    }
    return std::nullopt;
}

Piece::Optional Board::piece(const Square& square) const {
    //(void)square;
    for(auto it = board.begin(); it != board.end();++it){
            unsigned int vecSize = (it->second).size();
            for(unsigned int i = 0; i < vecSize; i++)
            {
                if(*(it->second)[i]==square){
                    if(it->first % 2 ==1){
                        if(it->first ==1){
                            return Piece::wp;
                        }
                        else if (it->first ==3)
                        {
                            return Piece::wn;   
                        }
                        else if (it->first ==5)
                        {
                            return Piece::wb;   
                        }
                        else if (it->first ==7)
                        {
                            return Piece::wr;   
                        }
                        else if (it->first ==9)
                        {
                            return Piece::wq;   
                        }
                        else if (it->first ==11)
                        {
                            return Piece::wk;   
                        }
                        
                    }
                    else{
                        if(it->first ==2){
                            return Piece::bp;
                        }
                        else if (it->first ==4)
                        {
                            return Piece::bn;   
                        }
                        else if (it->first ==6)
                        {
                            return Piece::bb;   
                        }
                        else if (it->first ==8)
                        {
                            return Piece::br;   
                        }
                        else if (it->first ==10)
                        {
                            return Piece::bq;   
                        }
                        else if (it->first ==12)
                        {
                            return Piece::bk;   
                        }
                        
                    }
                }
            }
    }
    return std::nullopt;
}

void Board::setTurn(PieceColor turn) {
    t=turn;
}

PieceColor Board::turn() const {
    return t;
}

void Board::setCastlingRights(CastlingRights cr1) {
    cr |= cr1;
}

CastlingRights Board::castlingRights() const {
    return cr;
}
//has to be either rank 3 or 6
void Board::setEnPassantSquare(const Square::Optional& square) {
    EPSquare = square;
}

Square::Optional Board::enPassantSquare() const {
    return EPSquare;
}

void Board::makeMove(const Move& move) {
    auto movedPiece = Board::piecen(move.from());
    if(!movedPiece.has_value()){
        return;
    }
    auto hitPiece = Board::piecen(move.to());
    if(move.promotion().has_value()){
        if(hitPiece.has_value()){
            removePiecen(move.to(),hitPiece.value());
        }
        removePiecen(move.from(),movedPiece.value());
        setPiecen(move.to(),Piece::getNum(Piece::getColor(movedPiece.value()),move.promotion().value()));
        setEnPassantSquare(std::nullopt);
    }
    else{
        if(movedPiece.value() ==Piece::wp.numb() || movedPiece.value() ==Piece::bp.numb() ){
            auto dif = move.from().rank() - move.to().rank();
            auto fdif = move.from().file() - move.to().file();
            if(dif == 2 && fdif ==0){
                setEnPassantSquare(Square::fromCoordinates(move.from().file(),move.from().rank()+1).value());
            }
            else if ( dif == -2 && fdif ==0)
            {
                setEnPassantSquare(Square::fromCoordinates(move.from().file(),move.from().rank()-1).value());
            }
            else if((fdif==1 || fdif == -1) && !hitPiece.has_value() && move.to() == enPassantSquare() && (dif==1 || dif == -1)){

                if(Piece::getColor(movedPiece.value()) == PieceColor::White){
                    auto s = Square::fromCoordinates(move.to().file(),move.to().rank()-1);
                    if(s.has_value() && Board::piecen(s.value()) ==  Piece::bp.numb()){
                        Board::removePiecen(s.value(),Piece::bp.numb());
                    }
                    
                }
                else{
                    auto s = Square::fromCoordinates(move.to().file(),move.to().rank()+1);
                    if(s.has_value() && Board::piecen(s.value()) ==  Piece::wp.numb()){
                        Board::removePiecen(s.value(),Piece::wp.numb());
                    }
                }
                setEnPassantSquare(std::nullopt);
            }
            else if((fdif==1 || fdif == -1) && (dif==1 || dif == -1)){
                if(Piece::getColor(movedPiece.value()) == PieceColor::White){
                    if(Board::piecen(move.to()) ==  Piece::bp.numb()){
                        Board::removePiecen(move.to(),Piece::bp.numb());
                    }
                    
                }
                else{
                    if(Board::piecen(move.to()) ==  Piece::wp.numb()){
                        Board::removePiecen(move.to(),Piece::wp.numb());
                    }
                }
                setEnPassantSquare(std::nullopt);
            }
            else if ((dif==1 || dif == -1) && fdif ==0)
            {
                setEnPassantSquare(std::nullopt);
            }
            
            else{
                //GIVEN MOVE IS NOT POSSIBLE
                setEnPassantSquare(std::nullopt);
                return;
            }
            Board::replacePiecen(move.from(),move.to(),movedPiece.value());
        }
        else{
            if(hitPiece.has_value()){
                 removePiecen(move.to(),hitPiece.value());
            }
            Board::replacePiecen(move.from(),move.to(),movedPiece.value());
            setEnPassantSquare(std::nullopt);
        }
    }
}

void Board::pseudoLegalMoves(MoveVec& moves) const {
    for(auto it = board.begin(); it != board.end();++it){
            if(Piece::getColor(it->first) == Board::turn()){
                unsigned int vecSize = (it->second).size();
                for(unsigned int i = 0; i < vecSize; i++)
                {
                    Board::pseudoLegalMovesFrom(*(it->second)[i],moves);
                }
            }
            
    }
}


void  Board::PawnpseudoLegalMovesFrom(const Square& from, Board::MoveVec& moves,Piece::Optional& p,const int d) const{
    //Piece::Optional p = Board::piece(from);
    unsigned start =1;
    unsigned end =6;
    if(d==-1){
        start = 6;
        end =1;
    }
    if (from.rank()==start)
                {   
                    auto front = Square::fromCoordinates(from.file(),from.rank()+d).value();
                    if(!Board::piecen(front).has_value()){
                        moves.push_back(Move::Move(from,front));
                        auto frontp = Square::fromCoordinates(from.file(),from.rank()+2*d).value();
                        if(!Board::piecen(frontp).has_value()){
                             moves.push_back(Move::Move(from,frontp));
                        }
                    }
                }
                if(from.rank()==end){
                    auto front = Square::fromCoordinates(from.file(),from.rank()+d).value();
                    if(!Board::piecen(front).has_value()){
                        moves.push_back(Move::Move(from,front,PieceType::Bishop));
                        moves.push_back(Move::Move(from,front,PieceType::Knight));
                        moves.push_back(Move::Move(from,front,PieceType::Rook));
                        moves.push_back(Move::Move(from,front,PieceType::Queen));
                    }
                    auto frontl = Square::fromCoordinates(from.file()-1,from.rank()+d);
                    if(frontl.has_value()){
                        auto frontp = Board::piecen(frontl.value());
                        if(frontp.has_value()){
                            if(Piece::getColor(frontp.value()) !=p.value().color()){
                                moves.push_back(Move::Move(from,frontl.value(),PieceType::Bishop));
                                moves.push_back(Move::Move(from,frontl.value(),PieceType::Knight));
                                moves.push_back(Move::Move(from,frontl.value(),PieceType::Rook));
                                moves.push_back(Move::Move(from,frontl.value(),PieceType::Queen));
                            }
                            
                        }
                    }
                    auto frontr = Square::fromCoordinates(from.file()+1,from.rank()+d);
                    if(frontr.has_value()){
                        auto frontp = Board::piecen(frontr.value());
                        if(frontp.has_value()){
                            if(Piece::getColor(frontp.value())!=p.value().color()){
                                moves.push_back(Move::Move(from,frontr.value(),PieceType::Bishop));
                                moves.push_back(Move::Move(from,frontr.value(),PieceType::Knight));
                                moves.push_back(Move::Move(from,frontr.value(),PieceType::Rook));
                                moves.push_back(Move::Move(from,frontr.value(),PieceType::Queen));
                            }
                        }
                    }
                }
                auto frontr = Square::fromCoordinates(from.file()+1,from.rank()+d);
                auto frontl = Square::fromCoordinates(from.file()-1,from.rank()+d);
                auto front = Square::fromCoordinates(from.file(),from.rank()+d);
                
                //EN Passant cases
                if(frontr.has_value()){
                    auto rp = Board::piecen(frontr.value());
                    if(frontr.value()==Board::enPassantSquare()){
                        if(p.value().color() == PieceColor::White && frontr.value().rank() == 5){
                            moves.push_back(Move::Move(from,frontr.value()));
                        }
                        else if (p.value().color() == PieceColor::Black && frontr.value().rank() == 2)
                        {
                            moves.push_back(Move::Move(from,frontr.value()));
                        }
                        
                        
                    }
                    else if (rp.has_value() && Piece::getColor(rp.value()) != p.value().color())
                    {
                        moves.push_back(Move::Move(from,frontr.value()));
                    }
                    
                }
                if(frontl.has_value()){
                    auto lp = Board::piecen(frontl.value());
                    if(frontl.value()==Board::enPassantSquare()){
                        if(p.value().color() == PieceColor::White && frontl.value().rank() == 5){
                            moves.push_back(Move::Move(from,frontl.value()));
                        }
                        else if (p.value().color() == PieceColor::Black && frontl.value().rank() == 2)
                        {
                            moves.push_back(Move::Move(from,frontl.value()));
                        }
                    }
                    else if (lp.has_value() && Piece::getColor(lp.value()) != p.value().color())
                    {
                        moves.push_back(Move::Move(from,frontl.value()));
                    }
                }
                if(front.has_value() && from.rank()!=start){
                    if(!Board::piecen(front.value()).has_value()){
                        moves.push_back(Move::Move(from,front.value()));
                    }
                }

}

void Board::BishoppseudoLegalMovesFrom(const Square& from, Board::MoveVec& moves,Piece::Optional& p,const int n,const int e) const{
    //Piece::Optional p = Board::piece(from);
    //int i =1;
    auto next = Square::fromCoordinates(from.file()+e,from.rank()+n);
    if(!next.has_value()){
        return;
    }
    auto np = Board::piecen(next.value());
    while(!np.has_value()){

         moves.push_back(Move::Move(from,next.value()));
        //i+=1;
        next = Square::fromCoordinates(next.value().file()+e,next.value().rank()+n);
        if(!next.has_value()){
            break;
        }
        np = Board::piecen(next.value());
    }
    if(next.has_value() && Piece::getColor(np.value()) != p.value().color()){
        moves.push_back(Move::Move(from,next.value()));
    }
}

void Board::KnightpseudoLegalMovesFrom(const Square& from, Board::MoveVec& moves,Piece::Optional& p,const int h,const int v) const{
    auto next = Square::fromCoordinates(from.file()+h,from.rank()+v);
    if(!next.has_value()){
        return;
    }
    auto np = Board::piecen(next.value());
    if(!np.has_value() || Piece::getColor(np.value())!=p.value().color()){
        moves.push_back(Move::Move(from,next.value()));
    }
}

void Board::pseudoLegalMovesFrom(const Square& from,
                                 Board::MoveVec& moves) const {
    Piece::Optional p = Board::piece(from);
   if(p.has_value()){
        if(p.value().color() !=Board::turn()){
            return;
        }
        if(p.value().type()==PieceType::Pawn){
            if(p.value().color() == PieceColor::White){
               Board::PawnpseudoLegalMovesFrom(from,moves,p,1);
            }
            else{
                Board::PawnpseudoLegalMovesFrom(from,moves,p,-1);
            }
        }
        else if (p.value().type()==PieceType::Bishop)
        {
            Board::BishoppseudoLegalMovesFrom(from,moves,p,1,1);
            Board::BishoppseudoLegalMovesFrom(from,moves,p,1,-1);
            Board::BishoppseudoLegalMovesFrom(from,moves,p,-1,1);
            Board::BishoppseudoLegalMovesFrom(from,moves,p,-1,-1);
        }
        else if (p.value().type()==PieceType::Queen)
        {
            Board::BishoppseudoLegalMovesFrom(from,moves,p,1,1);
            Board::BishoppseudoLegalMovesFrom(from,moves,p,1,-1);
            Board::BishoppseudoLegalMovesFrom(from,moves,p,-1,1);
            Board::BishoppseudoLegalMovesFrom(from,moves,p,-1,-1);
            Board::BishoppseudoLegalMovesFrom(from,moves,p,1,0);
            Board::BishoppseudoLegalMovesFrom(from,moves,p,-1,0);
            Board::BishoppseudoLegalMovesFrom(from,moves,p,0,1);
            Board::BishoppseudoLegalMovesFrom(from,moves,p,0,-1);
        }
        else if (p.value().type()==PieceType::Rook){
            Board::BishoppseudoLegalMovesFrom(from,moves,p,1,0);
            Board::BishoppseudoLegalMovesFrom(from,moves,p,-1,0);
            Board::BishoppseudoLegalMovesFrom(from,moves,p,0,1);
            Board::BishoppseudoLegalMovesFrom(from,moves,p,0,-1);
        }
        else if (p.value().type()==PieceType::Knight){
            Board::KnightpseudoLegalMovesFrom(from,moves,p,2,1);
            Board::KnightpseudoLegalMovesFrom(from,moves,p,2,-1);
            Board::KnightpseudoLegalMovesFrom(from,moves,p,-2,1);
            Board::KnightpseudoLegalMovesFrom(from,moves,p,-2,-1);
            Board::KnightpseudoLegalMovesFrom(from,moves,p,1,2);
            Board::KnightpseudoLegalMovesFrom(from,moves,p,1,-2);
            Board::KnightpseudoLegalMovesFrom(from,moves,p,-1,2);
            Board::KnightpseudoLegalMovesFrom(from,moves,p,-1,-2);
        }
   }
}
std::map<const int, std::vector<Square*>> Board::getBoard() const{
    return board;
}

std::ostream& operator<<(std::ostream& os, const Board& board) {
    auto b = board.getBoard();
    std::string s = "";
    for(auto it = b.begin(); it != b.end();++it){
        s +=  (it->first + "={");
            unsigned int vecSize = (it->second).size();
            for(unsigned int i = 0; i < vecSize; i++)
            {
                s+=( (*(it->second)[i]).getName() + ",");
            }
            s+="}";
        
    }
    return os << s;
}
