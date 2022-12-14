#include "Board.hpp"

#include <ostream>
#include <cassert>
#include <cmath>
#include <vector>
#include "Piece.hpp"
#include "Square.hpp"
#include <cmath>

Board::Board():t(PieceColor::White),
                cr(CastlingRights::All),
                EPSquare(std::nullopt),
                cboard(64,0)
{
    board[Piece::wk.numb()]=std::vector<Square*> {};
    board[Piece::bk.numb()]=std::vector<Square*> {};

    board[Piece::wq.numb()]=std::vector<Square*> {};
    board[Piece::bq.numb()]=std::vector<Square*> {};

    board[Piece::wb.numb()]=std::vector<Square*> {};
    board[Piece::bb.numb()]=std::vector<Square*> {};

    board[Piece::wn.numb()]=std::vector<Square*> {};
    board[Piece::bn.numb()]=std::vector<Square*> {};

    board[Piece::wr.numb()]=std::vector<Square*> {};
    board[Piece::br.numb()]=std::vector<Square*> {};

    board[Piece::wp.numb()]=std::vector<Square*> {};
    board[Piece::bp.numb()]=std::vector<Square*> {};
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

/**Board::~Board(){
    for(auto it = board.begin(); it != board.end();++it){
        unsigned int vecSize = (it->second).size();
        for(unsigned int i = 0; i < vecSize; i++)
        {
            //auto e = (it->second)[i];
            (it->second).erase((it->second).begin()+i);
            //delete e;  
        }
    }
}*/

// TO BE OPTIMIZED
void Board::setPiece(const Square& square, const Piece::Optional& piece) {
   if(piece.has_value()){
        cboard[square.rank()*8 + square.file()] = piece.value().numb();
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
    cboard[square.rank()*8 + square.file()] = piece;
    board[piece].push_back(new Square(square));
    /**
    for(auto it = board.begin(); it != board.end();++it){
        if(piece == (it->first)){
            board[it->first].push_back(new Square(square));
            return;
        }
    }
    board[piece]= std::vector<Square*> {new Square(square)};*/
}

void Board::removePiecen(const Square& square, const int piece){
    if(piece>12 || piece<1){
        return;
    }
    auto pos = square.rank()*8 + square.file();
    //auto p = cboard[pos];
    cboard[pos] = 0;
    unsigned int vecSize = board[piece].size();
    for(unsigned int i = 0; i < vecSize; i++)
    {
        if(*board[piece][i]==square){
            auto e = board[piece][i];
            board[piece].erase(board[piece].begin()+i);
            delete e;
            return;
        }
    }
}

void Board::replacePiecen(const Square& from,const Square& to, const int piece){
    if(piece>12 || piece<1){
        return;
    }
    cboard[to.rank()*8 + to.file()] = piece;
    cboard[from.rank()*8 + from.file()] = 0;
    unsigned int vecSize = board[piece].size();
    for(unsigned int i = 0; i < vecSize; i++)
    {
        if(*board[piece][i]==from){
            auto e = board[piece][i];
            board[piece][i] = new Square(to);
            delete e;
            return;
        }
    }
    board[piece].push_back(new Square(to));
    return;

    /**for(auto it = board.begin(); it != board.end();++it){
        if(piece == (it->first)){
            
        }
    }*/
}
Board::nOp Board::piecen(const Square& square) const{
    auto p = cboard[square.rank()*8 + square.file()] ;
    if(p == 0){
        return std::nullopt;
    }
    return p;
    /**
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
    */
}

Piece::Optional Board::piece(const Square& square) const {
    //(void)square;
    auto p = cboard[square.rank()*8 + square.file()] ;
    if(p == 0 || p>12){
        return std::nullopt;
    }
    if(p % 2 ==1){
        if(p ==1){
                        
            return Piece::wp;
        }
        else if (p ==3)
        {
            return Piece::wn;   
        }
        else if (p ==5)
        {
            return Piece::wb;   
        }
        else if (p ==7)
        {
            return Piece::wr;   
        }
        else if (p ==9)
        {
            return Piece::wq;   
        }
        else
        {
            return Piece::wk;   
        }
                        
    }
    else{
        if(p ==2){
            return Piece::bp;
        }
        else if (p ==4)
        {
            return Piece::bn;   
        }
        else if (p ==6)
        {
            return Piece::bb;   
        }
        else if (p ==8)
        {
            return Piece::br;   
        }
        else if (p ==10)
        {
            return Piece::bq;   
        }
        else
        {
            return Piece::bk;   
        }
                        
    }
                     
    /**for(auto it = board.begin(); it != board.end();++it){
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
    return std::nullopt;*/
}

void Board::setTurn(PieceColor turn) {
    t=turn;
}

PieceColor Board::turn() const {
    return t;
}

void Board::setCastlingRights(CastlingRights cr1) {
    cr = cr1;
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
            auto dif = move.to().rank() - move.from().rank();
            auto fdif = move.from().file() - move.to().file();
            if(dif == 2 && fdif ==0){
                setEnPassantSquare(Square::fromCoordinates(move.from().file(),2).value());
            }
            else if ( dif == -2 && fdif ==0)
            {
                setEnPassantSquare(Square::fromCoordinates(move.from().file(),5).value());
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
            if(movedPiece.value() ==Piece::wk.numb() && (castlingRights() & CastlingRights::White) !=CastlingRights::None){
                int diff = move.from().file() - move.to().file();
                if(abs(diff)==2){
                    if(diff<0){
                        Board::replacePiecen(Square::fromCoordinates(7,0).value(),Square::fromCoordinates(5,0).value(),Piece::wr.numb());
                    }
                    else{
                        Board::replacePiecen(Square::fromCoordinates(0,0).value(),Square::fromCoordinates(3,0).value(),Piece::wr.numb());
                    }
                }
                setCastlingRights(castlingRights() & ~CastlingRights::White);
            }
            else if(movedPiece.value() ==Piece::bk.numb() && (castlingRights() & CastlingRights::Black) !=CastlingRights::None){
                int diff = move.from().file() - move.to().file();
                if(abs(diff)==2){
                    if(diff<0){
                        Board::replacePiecen(Square::fromCoordinates(7,7).value(),Square::fromCoordinates(5,7).value(),Piece::br.numb());
                    }
                    else{
                        Board::replacePiecen(Square::fromCoordinates(0,7).value(),Square::fromCoordinates(3,7).value(),Piece::br.numb());
                    }
                }
                setCastlingRights(castlingRights() & ~CastlingRights::Black);
            }
            else if (movedPiece.value() ==Piece::wr.numb() && move.from().file()==0 && (castlingRights() & CastlingRights::WhiteQueenside) == CastlingRights::WhiteQueenside){
                setCastlingRights(castlingRights() & ~CastlingRights::WhiteQueenside);
            }
            else if (movedPiece.value() ==Piece::wr.numb() && move.from().file()==7 && (castlingRights() & CastlingRights::WhiteKingside) == CastlingRights::WhiteKingside){
                setCastlingRights(castlingRights() & ~CastlingRights::WhiteKingside);
            }
            else if (movedPiece.value() ==Piece::br.numb() && move.from().file()==0 && (castlingRights() & CastlingRights::BlackQueenside) == CastlingRights::BlackQueenside){
                setCastlingRights(castlingRights() & ~CastlingRights::BlackQueenside);
            }
            else if (movedPiece.value() ==Piece::br.numb() && move.from().file()==7 && (castlingRights() & CastlingRights::BlackKingside) == CastlingRights::BlackKingside){
                setCastlingRights(castlingRights() & ~CastlingRights::BlackKingside);
            }
        }
    }
    if(hitPiece.has_value()){
        if (hitPiece.value() ==Piece::wr.numb() && cboard[0]!=Piece::wr.numb() && (castlingRights() & CastlingRights::WhiteQueenside) == CastlingRights::WhiteQueenside){
            setCastlingRights(castlingRights() & ~CastlingRights::WhiteQueenside);
        }
        else if (hitPiece.value() ==Piece::wr.numb() && cboard[7]!=Piece::wr.numb() && (castlingRights() & CastlingRights::WhiteKingside) == CastlingRights::WhiteKingside){
            setCastlingRights(castlingRights() & ~CastlingRights::WhiteKingside);
        }
        else if (hitPiece.value() ==Piece::br.numb() && cboard[56]!=Piece::br.numb() && (castlingRights() & CastlingRights::BlackQueenside) == CastlingRights::BlackQueenside){
            setCastlingRights(castlingRights() & ~CastlingRights::BlackQueenside);
        }
        else if (hitPiece.value() ==Piece::br.numb() && cboard[63]!=Piece::br.numb() && (castlingRights() & CastlingRights::BlackKingside) == CastlingRights::BlackKingside){
            setCastlingRights(castlingRights() & ~CastlingRights::BlackKingside);
        }
    }
    

    if(turn()==PieceColor::White){
        t = PieceColor::Black;
    }
    else{
        t =PieceColor::White;
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
                        moves.push_back(Move::Move(from,front,PieceType::Queen));
                        moves.push_back(Move::Move(from,front,PieceType::Rook));
                        moves.push_back(Move::Move(from,front,PieceType::Bishop));
                        moves.push_back(Move::Move(from,front,PieceType::Knight)); 
                    }
                    auto frontl = Square::fromCoordinates(from.file()-1,from.rank()+d);
                    if(frontl.has_value()){
                        auto frontp = Board::piecen(frontl.value());
                        if(frontp.has_value()){
                            if(Piece::getColor(frontp.value()) !=p.value().color() && (frontp.value() != Piece::wk.numb() || frontp.value() != Piece::bk.numb())){
                                moves.push_back(Move::Move(from,frontl.value(),PieceType::Queen));
                                moves.push_back(Move::Move(from,frontl.value(),PieceType::Rook));
                                moves.push_back(Move::Move(from,frontl.value(),PieceType::Bishop));
                                moves.push_back(Move::Move(from,frontl.value(),PieceType::Knight)); 
                            }
                            
                        }
                    }
                    auto frontr = Square::fromCoordinates(from.file()+1,from.rank()+d);
                    if(frontr.has_value()){
                        auto frontp = Board::piecen(frontr.value());
                        if(frontp.has_value()){
                            if(Piece::getColor(frontp.value())!=p.value().color() && (frontp.value() != Piece::wk.numb() || frontp.value() != Piece::bk.numb())){
                                moves.push_back(Move::Move(from,frontr.value(),PieceType::Queen));
                                moves.push_back(Move::Move(from,frontr.value(),PieceType::Rook));
                                moves.push_back(Move::Move(from,frontr.value(),PieceType::Bishop));
                                moves.push_back(Move::Move(from,frontr.value(),PieceType::Knight));
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
                    else if (rp.has_value() && Piece::getColor(rp.value()) != p.value().color() && (rp.value() != Piece::wk.numb() || rp.value() != Piece::bk.numb()))
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
                    else if (lp.has_value() && Piece::getColor(lp.value()) != p.value().color() && (lp.value() != Piece::wk.numb() || lp.value() != Piece::bk.numb()))
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

void Board::KingpseudoLegalMovesFrom(const Square& from, Board::MoveVec& moves,Piece::Optional& p,const int n,const int e) const{
    auto next = Square::fromCoordinates(from.file()+e,from.rank()+n);
    if(!next.has_value()){
        return;
    }
    auto np = Board::piecen(next.value());
    if(!np.has_value()){
        moves.push_back(Move::Move(from,next.value()));
    }
    else if(Piece::getColor(np.value()) != p.value().color() && (np.value() != Piece::wk.numb() || np.value() != Piece::bk.numb())){
        moves.push_back(Move::Move(from,next.value()));
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
    if(next.has_value() && Piece::getColor(np.value()) != p.value().color() && (np.value() != Piece::wk.numb() || np.value() != Piece::bk.numb())){
        moves.push_back(Move::Move(from,next.value()));
    }
}

void Board::KnightpseudoLegalMovesFrom(const Square& from, Board::MoveVec& moves,Piece::Optional& p,const int h,const int v) const{
    auto next = Square::fromCoordinates(from.file()+h,from.rank()+v);
    if(!next.has_value()){
        return;
    }
    auto np = Board::piecen(next.value());
    if(!np.has_value() || (Piece::getColor(np.value())!=p.value().color() && (np.value() != Piece::wk.numb() || np.value() != Piece::bk.numb()))){
        moves.push_back(Move::Move(from,next.value()));
    }
}

//t is the current turn
int Board::inCheck(PieceColor tu,Square& sq) const{
    int m = Piece::getNumEven(tu);
    int r = Piece::wr.numb();
    int q = Piece::wq.numb();
    int n = Piece::wn.numb();
    int b = Piece::wb.numb();
    int p = Piece::wp.numb();
    //our king
    int k = Piece::bk.numb();
    if(m==1){
        r+=1;
        q+=1;
        n+=1;
        p+=1;
        b+=1;

        k-=1;
    }
    /**if(board[k].size()==0){
        return -1;
    }*/

    //Square ksqr = *board[k][0];
    int ksqrr = sq.rank();
    int ksqrf= sq.file();
    int ksqi = ksqrr*8 + ksqrf;

    int kpos[4] = {-2,-1,1,2};
    for(int kpi:kpos){
        for(int kpj:kpos){
            if(abs(kpi) != abs(kpj)){
                auto knight = Square::fromCoordinates(ksqrf+kpj,ksqrr+kpi);
                if(knight.has_value()){
                    auto pic = cboard[knight.value().index()];
                    if(pic ==n){
                        return knight.value().index();
                    }
                }
            }
        }
    }
    
    int i =-1;
    int j = -1;
    int prev =ksqi;
    int indx =0;
    while(i<2){
        while(j<2){
            if(!(i==0 && j ==0)){
                int s =1;
                prev =ksqi;
                while(true){
                    indx = ksqi + 8*i*s +j*s;
                    if((indx<0 || indx>=64 )){
                        break;
                    }
                    if(abs((prev%8) - ((indx)%8))>1){
                        break;
                    }
                    auto pic = cboard[indx];
                    if(pic!=0){
                        if(Piece::getColor(pic) == t){
                            break;
                        }
                        if(pic == r || pic == q){
                            if((i==0) || j==0){
                                return indx;
                            }
                        }
                        if (pic == b || pic == q)
                        {
                            if((i!=0) && j!=0){
                                return indx;
                            }
                        }
                        else if (pic==p && s==1)
                        {
                            if(m==1 && i==1 && j!=0){
                                return indx;
                            }
                            if(m==0 && i==-1 && j!=0){
                                return indx;
                            }
                        }
                        
                        //king checking each other????
                    }
                    s+=1;
                    prev =indx;
                }
            }
            j+=1;
        }
        i+=1;
    }

    return -1;

    /**for(auto it = board.begin(); it != board.end();++it){
            if(Piece::getColor(it->first) != t && it->first !=Piece::wk.numb() && it->first !=Piece::bk.numb()){
                auto pic = it->first;
                unsigned int vecSize = (it->second).size();
                for(unsigned int i = 0; i < vecSize; i++)
                {
                    int attackr = (it->second)[i]->rank(); 
                    int attackf = (it->second)[i]->file(); 
                    if(pic == r || pic == q){
                        if(ksqrr==attackr){

                        }
                    }
                    if (pic == b || pic == q)
                    {
                        
                    }
                    else if(pic == n){

                    }
                    else{

                    }
                    
                }
            }
            
    }*/
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
        else if (p.value().type()==PieceType::King){

            Board::KingpseudoLegalMovesFrom(from,moves,p,1,1);
            Board::KingpseudoLegalMovesFrom(from,moves,p,1,-1);
            Board::KingpseudoLegalMovesFrom(from,moves,p,-1,1);
            Board::KingpseudoLegalMovesFrom(from,moves,p,-1,-1);
            Board::KingpseudoLegalMovesFrom(from,moves,p,1,0);
            Board::KingpseudoLegalMovesFrom(from,moves,p,-1,0);
            Board::KingpseudoLegalMovesFrom(from,moves,p,0,1);
            Board::KingpseudoLegalMovesFrom(from,moves,p,0,-1);
            
            int c =0;
            int cp =0;
            int cpp = 0;
            if(turn()==PieceColor::White && from.rank()==0 && from.file() == 4 && (cboard[5]==0 && cboard[6]==0) && (castlingRights() & CastlingRights::WhiteKingside) == CastlingRights::WhiteKingside){
                auto esq = Square::fromCoordinates(4,0);
                auto fsq = Square::fromCoordinates(5,0);
                auto gsq =Square::fromCoordinates(6,0);
                if(esq.has_value() && fsq.has_value() && gsq.has_value()){
                    c= Board::inCheck(Board::turn(),esq.value());
                    cp = Board::inCheck(Board::turn(),fsq.value());
                    cpp =Board::inCheck(Board::turn(),gsq.value());
                }
        
            }
            else if (turn()==PieceColor::Black && from.rank()==7 && from.file() == 4 && (cboard[61]==0 && cboard[62]==0) && (castlingRights() & CastlingRights::BlackKingside)== CastlingRights::BlackKingside){
                auto esq = Square::fromCoordinates(4,7);
                auto fsq = Square::fromCoordinates(5,7);
                auto gsq =Square::fromCoordinates(6,7);
                if(esq.has_value() && fsq.has_value() && gsq.has_value()){
                    c= Board::inCheck(Board::turn(),esq.value());
                    cp = Board::inCheck(Board::turn(),fsq.value());
                    cpp =Board::inCheck(Board::turn(),gsq.value());
                }
            }
            if(c==-1 && cp==-1 && cpp==-1){
                moves.push_back(Move::Move(from,Square::fromCoordinates(6,from.rank()).value()));
            }
            c=0;
            cp=0;
            cpp=0;
            if(turn()==PieceColor::White && from.rank()==0 && from.file() == 4 && (cboard[1]==0 && cboard[2]==0 && cboard[3]==0) && (castlingRights() & CastlingRights::WhiteQueenside)  == CastlingRights::WhiteQueenside ){
                auto csq = Square::fromCoordinates(2,0);
                auto dsq = Square::fromCoordinates(3,0);
                auto esq = Square::fromCoordinates(4,0);
                if(esq.has_value() && dsq.has_value() && csq.has_value()){
                    c= Board::inCheck(Board::turn(),esq.value());
                    cp = Board::inCheck(Board::turn(),dsq.value());
                    cpp =Board::inCheck(Board::turn(),csq.value());
                }
            }
            else if (turn()==PieceColor::Black && from.rank()==7 && from.file() == 4 && (cboard[57]==0 && cboard[58]==0 && cboard[59]==0) && (castlingRights() & CastlingRights::BlackQueenside) == CastlingRights::BlackQueenside){
                auto csq = Square::fromCoordinates(2,7);
                auto dsq = Square::fromCoordinates(3,7);
                auto esq = Square::fromCoordinates(4,7);
                if(esq.has_value() && dsq.has_value() && csq.has_value()){
                    c= Board::inCheck(Board::turn(),esq.value());
                    cp = Board::inCheck(Board::turn(),dsq.value());
                    cpp =Board::inCheck(Board::turn(),csq.value());
                }
            }
            if(c==-1 && cp==-1 && cpp==-1  ){
                moves.push_back(Move::Move(from,Square::fromCoordinates(2,from.rank()).value()));
            } 
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
