#include "Board.hpp"

#include <ostream>
#include <cassert>
#include <cmath>
#include <vector>
#include "Piece.hpp"
#include "Square.hpp"
#include <cmath>
int getIndx(int rank,int file);
bool validIndx(int indx);
Board::Board():t(PieceColor::White),
                cr(CastlingRights::All),
                EPSquare(std::nullopt),
                cboard(64,0)
{
    board[Piece::wk.numb()]=std::vector<int> {};
    board[Piece::bk.numb()]=std::vector<int> {};

    board[Piece::wq.numb()]=std::vector<int> {};
    board[Piece::bq.numb()]=std::vector<int> {};

    board[Piece::wb.numb()]=std::vector<int> {};
    board[Piece::bb.numb()]=std::vector<int> {};

    board[Piece::wn.numb()]=std::vector<int> {};
    board[Piece::bn.numb()]=std::vector<int> {};

    board[Piece::wr.numb()]=std::vector<int> {};
    board[Piece::br.numb()]=std::vector<int> {};

    board[Piece::wp.numb()]=std::vector<int> {};
    board[Piece::bp.numb()]=std::vector<int> {};
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


int getIndx(int rank,int file){
    if(file<0 || file>=8){
        return -1;
    }
    return rank*8 + file;
}

bool validIndx(int indx){
    if(indx<0 || indx>=64){
        return false;
    }
    return true;
}
// TO BE OPTIMIZED
void Board::setPiece(const Square& square, const Piece::Optional& piece) {
   if(piece.has_value()){
        auto indx = square.index();
        cboard[indx] = piece.value().numb();
        bool added =false;
        bool removed =false;
        for(auto it = board.begin(); it != board.end();++it){
            if(!added && piece.value().numb() == (it->first)){
                board[it->first].push_back(indx);
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
                    if((it->second)[i]==(int)indx){
                        //auto e = (it->second)[i];
                        (it->second).erase((it->second).begin()+i);
                        //delete e;
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
            board[piece.value().numb()] = std::vector<int> {(int)indx};
        }
        
   }
}

void Board::setPiecen(const int square, const int piece){
    if(piece>12 || piece<1){
        return;
    }
    if(square>=0 && square<64){
        cboard[square] = piece;
        board[piece].push_back(square);
    }
    
    /**
    for(auto it = board.begin(); it != board.end();++it){
        if(piece == (it->first)){
            board[it->first].push_back(new Square(square));
            return;
        }
    }
    board[piece]= std::vector<Square*> {new Square(square)};*/
}

void Board::removePiecen(const int square, const int piece){
    if(piece>12 || piece<1){
        return;
    }
    if(square<0 || square>63){
        return;
    }
    //auto p = cboard[pos];
    cboard[square] = 0;
    unsigned int vecSize = board[piece].size();
    for(unsigned int i = 0; i < vecSize; i++)
    {
        if(board[piece][i]==square){
            //auto e = board[piece][i];
            board[piece].erase(board[piece].begin()+i);
            //delete e;
            return;
        }
    }
}

//from and to are indexes of the squares
void Board::replacePiecen(const int from,const int to, const int piece){
    if(piece>12 || piece<1){
        return;
    }
    if(from<0 || from>63){
        return;
    }
    if(to<0 || to>63){
        return;
    }
    cboard[to] = piece;
    cboard[from] = 0;
    unsigned int vecSize = board[piece].size();
    for(unsigned int i = 0; i < vecSize; i++)
    {
        if(board[piece][i]==from){
            //auto e = board[piece][i];
            board[piece][i] = to;
            //delete e;
            return;
        }
    }
    board[piece].push_back(to);
    return;

    /**for(auto it = board.begin(); it != board.end();++it){
        if(piece == (it->first)){
            
        }
    }*/
}

//index of the square
Board::nOp Board::piecen(const int square) const{
    if(square<0 || square>63){
        return std::nullopt;
    }
    auto p = cboard[square] ;
    if(p == 0){
        return std::nullopt;
    }
    return p;

}

Piece::Optional Board::piece(const Square& square) const {
    //(void)square;
    auto p = cboard[square.index()] ;
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
    int fromi = move.from().index();
    int toi = move.to().index();
    auto movedPiece = Board::piecen(fromi);
    if(!movedPiece.has_value()){
        return;
    }
    auto hitPiece = Board::piecen(toi);
    if(move.promotion().has_value()){
        if(hitPiece.has_value()){
            removePiecen(move.to().index(),hitPiece.value());
        }
        removePiecen(fromi,movedPiece.value());
        setPiecen(toi,Piece::getNum(Piece::getColor(movedPiece.value()),move.promotion().value()));
        setEnPassantSquare(std::nullopt);
    }
    else{
        if(movedPiece.value() ==Piece::wp.numb() || movedPiece.value() ==Piece::bp.numb() ){
            int dif = move.to().rank() - move.from().rank();
            int fdif = move.from().file() - move.to().file();
            if(dif == 2 && fdif ==0){
                setEnPassantSquare(Square::fromCoordinates(move.from().file(),2).value());
            }
            else if ( dif == -2 && fdif ==0)
            {
                setEnPassantSquare(Square::fromCoordinates(move.from().file(),5).value());
            }
            else if((fdif==1 || fdif == -1) && !hitPiece.has_value() && move.to() == enPassantSquare() && (dif==1 || dif == -1)){

                if(Piece::getColor(movedPiece.value()) == PieceColor::White){
                    auto s = getIndx(move.to().rank()-1,move.to().file());
                    
                    if(validIndx(s) && Board::piecen(s) ==  Piece::bp.numb()){
                        Board::removePiecen(s,Piece::bp.numb());
                    }
                    
                }
                else{
                    auto s = getIndx(move.to().rank()+1,move.to().file());
                    if(validIndx(s) && Board::piecen(s) ==  Piece::wp.numb()){
                        Board::removePiecen(s,Piece::wp.numb());
                    }
                }
                setEnPassantSquare(std::nullopt);
            }
            else if((fdif==1 || fdif == -1) && (dif==1 || dif == -1)){
                if(Piece::getColor(movedPiece.value()) == PieceColor::White){
                    if(Board::piecen(toi) ==  Piece::bp.numb()){
                        Board::removePiecen(toi,Piece::bp.numb());
                    }
                    
                }
                else{
                    if(Board::piecen(toi) ==  Piece::wp.numb()){
                        Board::removePiecen(toi,Piece::wp.numb());
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
            Board::replacePiecen(fromi,toi,movedPiece.value());
            if(hitPiece.has_value()){
                 removePiecen(toi,hitPiece.value());
            }
        }
        else{
            if(hitPiece.has_value()){
                 removePiecen(toi,hitPiece.value());
            }
            Board::replacePiecen(fromi,toi,movedPiece.value());
            setEnPassantSquare(std::nullopt);
            if(movedPiece.value() ==Piece::wk.numb() && (castlingRights() & CastlingRights::White) !=CastlingRights::None){
                int diff = move.from().file() - move.to().file();
                if(abs(diff)==2){
                    if(diff<0){
                        Board::replacePiecen(7,5,Piece::wr.numb());
                    }
                    else{
                        Board::replacePiecen(0,3,Piece::wr.numb());
                    }
                }
                setCastlingRights(castlingRights() & ~CastlingRights::White);
            }
            else if(movedPiece.value() ==Piece::bk.numb() && (castlingRights() & CastlingRights::Black) !=CastlingRights::None){
                int diff = move.from().file() - move.to().file();
                if(abs(diff)==2){
                    if(diff<0){
                        Board::replacePiecen(getIndx(7,7),getIndx(7,5),Piece::br.numb());
                    }
                    else{
                        Board::replacePiecen(getIndx(7,0),getIndx(7,3),Piece::br.numb());
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
                    Board::pseudoLegalMovesFrom(Square::fromIndex((it->second)[i]).value(),moves);
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
                    //auto front = getIndx(from.rank()+d,from.file());
                    if(!Board::piecen(front.index()).has_value()){
                        moves.push_back(Move(from,front));
                        auto frontp = Square::fromCoordinates(from.file(),from.rank()+2*d).value();
                        if(!Board::piecen(frontp.index()).has_value()){
                             moves.push_back(Move(from,frontp));
                        }
                    }
                }
                if(from.rank()==end){
                    auto front = Square::fromCoordinates(from.file(),from.rank()+d).value();
                    if(!Board::piecen(front.index()).has_value()){
                        moves.push_back( Move(from,front,PieceType::Queen));
                        moves.push_back( Move(from,front,PieceType::Rook));
                        moves.push_back( Move(from,front,PieceType::Bishop));
                        moves.push_back( Move(from,front,PieceType::Knight)); 
                    }
                    auto frontl = Square::fromCoordinates(from.file()-1,from.rank()+d);
                    if(frontl.has_value()){
                        auto frontp = Board::piecen(frontl.value().index());
                        if(frontp.has_value()){
                            if(Piece::getColor(frontp.value()) !=p.value().color() && (frontp.value() != Piece::wk.numb() && frontp.value() != Piece::bk.numb())){
                                moves.push_back( Move(from,frontl.value(),PieceType::Queen));
                                moves.push_back( Move(from,frontl.value(),PieceType::Rook));
                                moves.push_back( Move(from,frontl.value(),PieceType::Bishop));
                                moves.push_back( Move(from,frontl.value(),PieceType::Knight)); 
                            }
                            
                        }
                    }
                    auto frontr = Square::fromCoordinates(from.file()+1,from.rank()+d);
                    if(frontr.has_value()){
                        auto frontp = Board::piecen(frontr.value().index());
                        if(frontp.has_value()){
                            if(Piece::getColor(frontp.value())!=p.value().color() && (frontp.value() != Piece::wk.numb() && frontp.value() != Piece::bk.numb())){
                                moves.push_back( Move(from,frontr.value(),PieceType::Queen));
                                moves.push_back( Move(from,frontr.value(),PieceType::Rook));
                                moves.push_back( Move(from,frontr.value(),PieceType::Bishop));
                                moves.push_back( Move(from,frontr.value(),PieceType::Knight));
                            }
                        }
                    }
                }
                auto frontr = Square::fromCoordinates(from.file()+1,from.rank()+d);
                auto frontl = Square::fromCoordinates(from.file()-1,from.rank()+d);
                auto front = Square::fromCoordinates(from.file(),from.rank()+d);
                
                //EN Passant cases
                if(frontr.has_value()){
                    auto rp = Board::piecen(frontr.value().index());
                    if(frontr.value()==Board::enPassantSquare()){
                        if(p.value().color() == PieceColor::White && frontr.value().rank() == 5){
                            moves.push_back( Move(from,frontr.value()));
                        }
                        else if (p.value().color() == PieceColor::Black && frontr.value().rank() == 2)
                        {
                            moves.push_back( Move(from,frontr.value()));
                        }
                        
                        
                    }
                    else if (rp.has_value() && Piece::getColor(rp.value()) != p.value().color() && (rp.value() != Piece::wk.numb() && rp.value() != Piece::bk.numb()))
                    {
                        moves.push_back( Move(from,frontr.value()));
                    }
                    
                }
                if(frontl.has_value()){
                    auto lp = Board::piecen(frontl.value().index());
                    if(frontl.value()==Board::enPassantSquare()){
                        if(p.value().color() == PieceColor::White && frontl.value().rank() == 5){
                            moves.push_back( Move(from,frontl.value()));
                        }
                        else if (p.value().color() == PieceColor::Black && frontl.value().rank() == 2)
                        {
                            moves.push_back( Move(from,frontl.value()));
                        }
                    }
                    else if (lp.has_value() && Piece::getColor(lp.value()) != p.value().color() && (lp.value() != Piece::wk.numb() && lp.value() != Piece::bk.numb()))
                    {
                        moves.push_back( Move(from,frontl.value()));
                    }
                }
                if(front.has_value() && from.rank()!=start){
                    if(!Board::piecen(front.value().index()).has_value()){
                        moves.push_back( Move(from,front.value()));
                    }
                }

}

void Board::KingpseudoLegalMovesFrom(const Square& from, Board::MoveVec& moves,Piece::Optional& p,const int n,const int e) const{
    auto next = Square::fromCoordinates(from.file()+e,from.rank()+n);
    if(!next.has_value()){
        return;
    }
    auto np = Board::piecen(next.value().index());
    if(!np.has_value()){
        moves.push_back( Move(from,next.value()));
    }
    else if(Piece::getColor(np.value()) != p.value().color() && (np.value() != Piece::wk.numb() && np.value() != Piece::bk.numb())){
        moves.push_back( Move(from,next.value()));
    }
}

void Board::BishoppseudoLegalMovesFrom(const Square& from, Board::MoveVec& moves,Piece::Optional& p,const int n,const int e) const{
    //Piece::Optional p = Board::piece(from);
    //int i =1;
    auto next = Square::fromCoordinates(from.file()+e,from.rank()+n);
    if(!next.has_value()){
        return;
    }
    auto np = Board::piecen(next.value().index());
    while(!np.has_value()){

         moves.push_back( Move(from,next.value()));
        //i+=1;
        next = Square::fromCoordinates(next.value().file()+e,next.value().rank()+n);
        if(!next.has_value()){
            break;
        }
        np = Board::piecen(next.value().index());
    }
    if(next.has_value() && Piece::getColor(np.value()) != p.value().color() && (np.value() != Piece::wk.numb() && np.value() != Piece::bk.numb())){
        moves.push_back( Move(from,next.value()));
    }
}

void Board::KnightpseudoLegalMovesFrom(const Square& from, Board::MoveVec& moves,Piece::Optional& p,const int h,const int v) const{
    auto next = Square::fromCoordinates(from.file()+h,from.rank()+v);
    if(!next.has_value()){
        return;
    }
    auto np = Board::piecen(next.value().index());
    if(!np.has_value() || (Piece::getColor(np.value())!=p.value().color() && (np.value() != Piece::wk.numb() && np.value() != Piece::bk.numb()))){
        moves.push_back( Move(from,next.value()));
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
    int ksqrr = sq.rank();
    int ksqrf= sq.file();
    int ksqi = sq.index();

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
        j=-1;
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
                        if(Piece::getColor(pic) == tu){
                            break;
                        }
                        if(pic == r){
                            if((i==0) || j==0){
                                return indx;
                            }
                            break;
                        }
                        else if (pic == b  )
                        {
                            if((i!=0) && j!=0){
                                return indx;
                            }
                            break;
                        }
                        else if(pic == q){
                            if((i==0) || j==0){
                                return indx;
                            }
                            if((i!=0) && j!=0){
                                return indx;
                            }
                            break;
                        }
                        else if (pic==p)
                        {
                            if(s!=1){
                                break;
                            }
                            if(m==1 && i==1 && j!=0){
                                return indx;
                            }
                            if(m==0 && i==-1 && j!=0){
                                return indx;
                            }
                            break;
                        }
                        break;
                        
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
                moves.push_back( Move(from,Square::fromCoordinates(6,from.rank()).value()));
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
                moves.push_back( Move(from,Square::fromCoordinates(2,from.rank()).value()));
            } 
        }
   }
}
std::map<const int, std::vector<int>> Board::getBoard() const{
    return board;
}

std::vector<int> Board::getcBoard() const{
    return cboard;
}

int Board::getHScore(){
    return hscore;
}
void Board::setHScore(int s){
    hscore =s;
}

std::ostream& operator<<(std::ostream& os, const Board& board) {
    auto b = board.getBoard();
    std::string s = "";
    /**for(auto it = b.begin(); it != b.end();++it){
        s +=  (it->first + "={");
            unsigned int vecSize = (it->second).size();
            for(unsigned int i = 0; i < vecSize; i++)
            {
                s+=( (*(it->second)[i]).getName() + ",");
            }
            s+="}";
        
    }*/
    return os << s;
}
