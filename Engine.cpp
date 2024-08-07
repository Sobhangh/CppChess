#include "Engine.hpp"
#include <algorithm> 
#include <tuple> 
#include <vector> 

class myEngine: public Engine{

    std::optional<HashInfo> hashInfo()  const override{
        return std::nullopt;
    }

    void setHashSize(std::size_t size) override {
        (void)size;
    }


    std::string name() const override{
        return "KINGSG";
    }
    std::string version() const override{
        return "1";
    }
    std::string author() const override{
        return "SOBHAN GHARANFOLI";
    }

    void newGame() override{

    }

    PrincipalVariation pv(
        const Board& board,
        const TimeInfo::Optional& timeInfo = std::nullopt
    ) override {
        (void)timeInfo;
        auto b =  Board(board);
        auto ngmx = negamax(b,6,-1*INF,INF,1);
        auto p = PrincipalVariation();
        /**auto v = Board::MoveVec();
        for(auto it=std::get<0>(ngmx).size()-1;it>=0;--it){
            v.push_back(std::get<0>(ngmx)[it]);
        }*/
        std::reverse(std::get<0>(ngmx).begin(),std::get<0>(ngmx).end());
        p.makeMoveVc(std::get<0>(ngmx));
        if(std::get<1>(ngmx) == -1*INF ){ //|| std::get<1>(ngmx) == INF
            p.setMate(true);
            p.setScore(std::get<0>(ngmx).size());
        }
        else{
            p.setMate(false);
            p.setScore(std::get<1>(ngmx));
        }
        return p;
    }

   
    
    const int INF = 1000000;
    const int CHECK = 20;

    std::tuple<std::vector<Move>,int> negamax(Board& node, int depth, int a, int b, int color) {
        if (depth == 0){ //or node is a terminal node then
            auto pv =std::make_tuple(std::vector<Move>(),heuristic(node,node.turn()));
            return pv;
        } 
        Square::Optional ksq = std::nullopt;
        PieceColor t = PieceColor::White;
        if(node.turn() == PieceColor::White){
            auto ksqarr = node.getBoard()[Piece::bk.numb()];
            if(ksqarr.size()==0){
                return std::make_tuple(std::vector<Move>(),-5*INF);
            }
            ksq = Square::fromIndex(ksqarr[0]);
            t = PieceColor::Black;
        }
        else{
            auto ksqarr =node.getBoard()[Piece::wk.numb()];
            if(ksqarr.size()==0){
                return std::make_tuple(std::vector<Move>(),-5*INF);
            }
            ksq = Square::fromIndex(ksqarr[0]);
        }
        if(!ksq.has_value()){
            return std::make_tuple(std::vector<Move>(),-5*INF);
        }
        
        std::vector<Move> childNodes =std::vector<Move>();
        generateMoves(childNodes,node);
        auto eps = node.enPassantSquare();
        if(eps.has_value()){
            orderMoves(eps.value().index(),childNodes,node.turn(),node.getcBoard(),ksq.value().rank(),ksq.value().file());
        }
        else{
            orderMoves(-2,childNodes,node.turn(),node.getcBoard(),ksq.value().rank(),ksq.value().file());
        }
        
        auto value = -1*INF;
        std::tuple<std::vector<Move>,int> pvmax;
        bool allcheck =true;
        //bool prune =false;
        for(auto child : childNodes){
            auto nb =   Board(node);
            nb.makeMove(child);
            bool inch = false;
            if(node.turn() == PieceColor::White){
                auto ksqarr =nb.getBoard()[Piece::wk.numb()];
                if(ksqarr.size()==0){
                    return std::make_tuple(std::vector<Move>(),-5*INF);
                }
                ksq = Square::fromIndex(ksqarr[0]);
                if(nb.inCheck(PieceColor::White,ksq.value())!=-1){
                    inch =true;
                }
            }
            else{
                auto ksqarr = nb.getBoard()[Piece::bk.numb()];
                if(ksqarr.size()==0){
                    return std::make_tuple(std::vector<Move>(),-5*INF);
                }
                ksq = Square::fromIndex(ksqarr[0]);
                if(nb.inCheck(PieceColor::Black,ksq.value())!=-1){
                    inch =true;
                }
            }
            if(!inch){
                allcheck =false;
                nb.setTurn(t);
                auto pv = negamax(nb, depth - 1, -1*b, -1*a, -1*color);
                int v = -1*std::get<1>(pv);
                //if(v != -1 * CHECK && v != -1* INF ){
                //    allcheck =false;
                //}
                //value= std::max(value,v);
                if(v>value){
                    value = v;
                    pvmax =std::make_tuple(std::get<0>(pv),v);
                    std::get<0>(pvmax).push_back(child);
                }
                if(v==-1*INF && value==v){
                    pvmax =std::make_tuple(std::vector<Move>(),-1*INF);
                    //std::get<0>(pvmax).push_back(child);
                }
                a= std::max(a, value);
                if( a >= b){
                    //prune =true;
                    break ;
                } 
            }
            
        } 
        //STALEMATE CHECK: IF ALL THE VALUES OF A MOVE IS A CHECK WHILE CURRENT BOARD IS NOT A CHECK: ITS SCORE WOULD BE ZERO
        //CHECKMATE CHECK IF CURRENT BOARD IS IN CHECK AND ALL THE NEXT GENERATED MOVES ARE ALSO CHECK
        if(allcheck){
            Square::Optional ks = std::nullopt;
            PieceColor tu = PieceColor::White;
            if(node.turn()==PieceColor::White){
                auto ksqarr =node.getBoard()[Piece::wk.numb()];
                if(ksqarr.size()==0){
                    return std::make_tuple(std::vector<Move>(),-5*INF);
                }
                ks = Square::fromIndex(ksqarr[0]);
                if(node.inCheck(tu,ks.value())!=-1){
                    auto pv =std::make_tuple(std::vector<Move>(),-1*INF);
                    return pv;
                }
                auto pv =std::make_tuple(std::vector<Move>(),0);
                return pv;
            }
            else{
                tu=PieceColor::Black;
                auto ksqarr =node.getBoard()[Piece::bk.numb()];
                if(ksqarr.size()==0){
                    return std::make_tuple(std::vector<Move>(),-5*INF);
                }
                ks = Square::fromIndex(ksqarr[0]);
                if(node.inCheck(tu,ks.value())!=-1){
                    auto pv =std::make_tuple(std::vector<Move>(),-1*INF);
                    return pv;
                }
                auto pv =std::make_tuple(std::vector<Move>(),0);
                return pv;
            }
        }
        return pvmax;
    }

    void generateMoves(std::vector<Move>& boardVc,Board& b){
        /**auto mv= MoveVec();
        b.pseudoLegalMoves(mv);
        for(auto m : mv){
            auto nb =  Board(b);
            nb.makeMove(m);
            auto score = heuristic(nb)*color;
            nb.setHScore(score);
            boardVc.push_back(std::make_tuple(nb,m));
        }*/
        auto mv= Board::MoveVec();
        b.pseudoLegalMoves(mv);
        for(auto m : mv){
            boardVc.push_back(m);
        }

    }

    bool compB(Board& a,Board& b){
        if(a.getHScore()>=b.getHScore()){
            return true;
        }
        return false;
    }

    static int distance(int fromr,int fromf, int tor,int tof, int piece){
        if(piece<1 || piece>12){
            return 0;
        }
        int h = std::abs((int)(fromr - tor));
        int w = std::abs((int)(fromf - tof));
        if(piece == Piece::wn.numb() || piece == Piece::bn.numb()){
            return h+w;
        }
        if(w==0){
            return h;
        }
        if(h==0){
            return w;
        }
        return h;
    }

    static int checkMove(int piece,int tor,int tof,PieceColor c,std::vector<int> cb,const int kingr,const int kingf){
        int indx = tor*8 + tof;
        if(indx<0|| indx>63){
            return 0;
        }
        if(piece <= 0 || piece>12){
            return 0;
        }
        const int score =5;
        const int bscore =3;
        if(c==PieceColor::White){
            if ( piece==Piece::wp.numb())
            {
                if((kingr-tor==1 && std::abs(kingf-tof)==1)){
                    return bscore;
                }
            }
        }
        else{
            if ( piece==Piece::bp.numb())
            {
                if((tor-kingr==1 && std::abs(kingf-tof)==1)){
                    return bscore;
                }
            }

        }
        if( piece==Piece::wn.numb() ||  piece==Piece::bn.numb()){
            if((std::abs(tor-kingr)==2 && std::abs(tof-kingf)==1) ||  (std::abs(tor-kingr)==1 && std::abs(tof-kingf)==2)){
                return score;
            }
        }
        if( piece==Piece::wr.numb() ||  piece==Piece::wq.numb() ||  piece==Piece::br.numb() ||  piece==Piece::bq.numb()){
            int diff = kingf-tof;
            int difr = kingr-tor;
            if(diff==0 ){
                if(abs(difr)==1){
                    return bscore;
                }
                int i =0;
                if(difr>0){
                    i =8;
                }
                else{
                    i=-1*8;
                }
                int s = tor*8 +i+ kingf;
                int ki = kingr*8 + kingf;
                bool con = true;
                while(s!=ki){
                    if(s<0 || s> 63 ||cb[s]!=0){
                        con = false;
                        break;
                    }
                    s +=i;
                }
                if(con){
                    return score;
                }
            }
            else if (difr==0)
            {   
                if(std::abs(diff)==1){
                    return bscore;
                }
                int i =0;
                if(diff>0){
                    i=1;
                }
                else{
                    i=-1;
                }
                int s =kingr*8 + (tof+i);
                const int ki = kingr*8 + kingf;
                bool con = true;
                while(s!=ki){
                    if(s<0 || s> 63 || cb[s]!=0){
                        con = false;
                        break;
                    }
                    s+=i;
                }
                if(con){
                    return score;
                }
            }
            return 0;
        }
        if( piece==Piece::wb.numb() ||  piece==Piece::wq.numb() ||  piece==Piece::bb.numb() ||  piece==Piece::bq.numb()){
            int diff = kingf-tof;
            int difr = kingr-tor;
            const int ki = kingr*8 + kingf;
            bool con = true;
            if(std::abs(difr)== std::abs(diff)){
                if(std::abs(difr)==1){
                    return bscore;
                }
                int i =0;
                int j=0;
                if(difr>0){
                    i=8;
                }
                else{
                    i = -1*8;
                }
                if(diff>0){
                    j=1;
                }
                else{
                    j=-1;
                }
                int s = tor*8 + i +tof + j;
                while(s!=ki){
                    if( s<0 || s> 63 || cb[s]!=0){
                        con = false;
                        break;
                    }
                    s+=(i+j);
                }
                if(con){
                    return score;
                }
            }
        }
        return 0;
        
    }

    //int surroudning
    //give the color: if move is towards the other side then it is better than towrards your own side
    void orderMoves(const int epsi,std::vector<Move>& boardVc, PieceColor c,std::vector<int> cb,const int kr,const int kf){
        std::sort(boardVc.begin(),boardVc.end(),[epsi,c,cb,kr,kf](Move& a,Move& b){
        if(a.promotion().has_value() && !b.promotion().has_value()){
            return true;
        }
        if(b.promotion().has_value() && !a.promotion().has_value()){
            return false;
        }
        if(a.promotion().has_value() && b.promotion().has_value()){
            if(a.promotion().value() == PieceType::Queen && b.promotion().value() != PieceType::Queen){
                return true;
            }
            return false;
        }

        int pieca= cb[a.from().index()];
        int piecb = cb[b.from().index()];
        int hita = cb[a.to().index()];
        int hitb = cb[b.to().index()];
        int score =0;
        if(cb[a.to().index()] >  cb[b.to().index()]){
            score += (cb[a.to().index()]);
        }
        else if(cb[a.to().index()] <  cb[b.to().index()]){
            score -= (cb[b.to().index()]);
        }
        if(pieca == Piece::wp.numb() || pieca == Piece::wp.numb() ){
            if((int)a.to().index()==epsi){
                score+=8;
            }
        }
        if(piecb == Piece::wp.numb() || piecb == Piece::wp.numb() ){
            if((int)b.to().index()==epsi){
                score-=8;
            }
        }
        //hitting a pawn that is close to promotion.
        if(hita == Piece::wp.numb() && a.to().rank()==6){
            score +=3;
        }
        if(hitb == Piece::wp.numb() && b.to().rank()==6){
            score -=3;
        }
        if(hita == Piece::bp.numb() && a.to().rank()==1){
            score +=3;
        }
        if(hitb == Piece::bp.numb() && b.to().rank()==1){
            score -=3;
        }

        //score += (cb[a.to().index()]-cb[b.to().index()]);
        if(c == PieceColor::White){
            int cda = std::abs((int)a.to().rank()-5);
            int cdb = std::abs((int)b.to().rank()-5);
            score+= cdb-cda;
            int kindx = kr*8+kf;
            if(kindx>=0 && kindx<64){
                if(cb[kindx]==Piece::bk.numb()){
                    score += (checkMove(pieca,a.to().rank(),a.to().file(),c,cb,kr,kf) - checkMove(piecb,b.to().rank(),b.to().file(),c,cb,kr,kf));
                }
            }
            
            
        }
        else{
            int cda = std::abs((int)a.to().rank()-2);
            int cdb = std::abs((int)b.to().rank()-2);
            score+= cdb-cda;
            int kindx = kr*8+kf;
            if(kindx>=0 && kindx<64){
                if(cb[kindx]==Piece::wk.numb()){
                    score += (checkMove(pieca,a.to().rank(),a.to().file(),c,cb,kr,kf) - checkMove(piecb,b.to().rank(),b.to().file(),c,cb,kr,kf));
                }
            }
            
        }
        
        score += (distance(a.from().rank(),a.from().file(),a.to().rank(),a.to().file(),pieca)- distance(b.from().rank(),b.from().file(),b.to().rank(),b.to().file(),piecb));
        //score += (Square::HammingDist(a.from(),a.to())- Square::HammingDist(b.from(),b.to()));
        /**if(Square::HammingDist(a.from(),a.to())> Square::HammingDist(b.from(),b.to())){

            return true;
        }*/
        if(score>0){
            return true;
        }
        return false;
    }
    );
    }

    bool allInChk(Board& b,PieceColor c,Square::Optional ksq){
        b.setTurn(c);
        std::vector<Move> childNodes =std::vector<Move>();
        generateMoves(childNodes,b);
        bool allcheck = true;
        for(auto child:childNodes){
            auto nb = Board(b);
            nb.makeMove(child);
            if(nb.inCheck(c, ksq.value())==-1){
                allcheck =false;
                break;
            }
        }
        if(allcheck){
            return true;
        }
        return false;
    }

    int heuristic(Board& b,PieceColor c){
        int score =0;
        if(c==PieceColor::White){
            auto ksqarr = b.getBoard()[Piece::wk.numb()];
            if(ksqarr.size()==0){
                return -5*INF;
            }
            Square::Optional ksq = Square::fromIndex(ksqarr[0]);
            if(b.inCheck(PieceColor::White, ksq.value())!=-1){
                auto nb = Board(b);
                bool allcheck = allInChk(nb,PieceColor::White,ksq);
                if(allcheck){
                    return -1*INF;
                }
                score+= (-1*5);
            }
            auto bksqarr =  b.getBoard()[Piece::bk.numb()];
            if(bksqarr.size()==0){
                return -5*INF;
            }
            Square::Optional bksq = Square::fromIndex(bksqarr[0]);
            if(b.inCheck(PieceColor::Black, bksq.value())!=-1){
                score+= 10*CHECK;
            }
        }
        else{
            auto ksqarr =  b.getBoard()[Piece::bk.numb()];
            if(ksqarr.size()==0){
                return -5*INF;
            }
            Square::Optional ksq = Square::fromIndex(ksqarr[0]);
            if(b.inCheck(PieceColor::Black, ksq.value())!=-1){
                auto nb = Board(b);
                bool allcheck = allInChk(nb,PieceColor::Black,ksq);
                if(allcheck){
                    return -1*INF;
                }
                score+= (-1*5);
                //score+= -1*CHECK;
            }
            auto bksqarr = b.getBoard()[Piece::wk.numb()];
            if(bksqarr.size()==0){
                return -5*INF;
            }
            Square::Optional bksq = Square::fromIndex(bksqarr[0]);
            if(b.inCheck(PieceColor::White, bksq.value())!=-1){
                score+= 10*CHECK;
            }
        }
        //king protection:front left and right.
        int wkprtct = 0;
        int wki = b.getBoard()[Piece::wk.numb()][0];
        int wkif =wki+8;
        if(wkif<64){
            if(b.getcBoard()[wkif]!=0 ){
                if(Piece::getColor(b.getcBoard()[wkif])==PieceColor::White){
                    wkprtct += 3;
                }
                
            }
            int wkil = wkif-1;
            if(wkif%8!=0){
                if(b.getcBoard()[wkil]!=0){
                    if(Piece::getColor(b.getcBoard()[wkil])==PieceColor::White){
                        wkprtct += 1;
                    }
                    
                }
            }
            int wkir = wkif+1;
            if(wkif%8!=7){
                if(b.getcBoard()[wkir]!=0){
                    if(Piece::getColor(b.getcBoard()[wkir])==PieceColor::White){
                        wkprtct += 1;
                    }
                }
            }
        }
        int bkprtct = 0;
        int bki = b.getBoard()[Piece::bk.numb()][0];
        int bkif =bki-8;
        if(bkif>=0){
            if(b.getcBoard()[bkif]!=0){
                if(Piece::getColor(b.getcBoard()[bkif])==PieceColor::Black){
                    bkprtct += 3;
                }
            }
            int bkil = bkif-1;
            if(bkif%8!=0){
                if(b.getcBoard()[bkil]!=0){
                    if(Piece::getColor(b.getcBoard()[bkil])==PieceColor::Black){
                        bkprtct += 1;
                    }
                }
            }
            int bkir = bkif+1;
            if(bkif%8!=7){
                if(b.getcBoard()[bkir]!=0){
                    if(Piece::getColor(b.getcBoard()[bkir])==PieceColor::Black){
                        bkprtct += 1;
                    }
                }
            }
        }

        //center control
        int bi = 2*8+2;
        int ii =0;
        int j =0;
        int wcrtl =0;
        int bcrtl =0;
        int wpawn =0;
        int bpawn =0;
        while(ii<4){
            int s = bi + 8*ii;
            while(j<4){
                if(b.getcBoard()[s]!=0){
                    int ctr =1;
                    if(b.getcBoard()[s] == Piece::wp.numb()  ){
                        ctr=0;
                        wpawn+=1;
                    }
                    else if(b.getcBoard()[s] == Piece::bp.numb()){
                        ctr=0;
                        bpawn+=1;
                    }
                    else if(b.getcBoard()[s] == Piece::wk.numb() || b.getcBoard()[s] == Piece::bk.numb()){
                        ctr = 0;
                    }

                    if(Piece::getColor(b.getcBoard()[s])==PieceColor::Black){
                        bcrtl += ctr;
                    }
                    else{
                        wcrtl += ctr;
                    }
                }
                j+=1;
                s+=1;
            }
            j=0;
            ii+=1;
        }
        wcrtl += (wpawn/2);
        bcrtl += (bpawn/2);
        
        if(c==PieceColor::White){
            int i=1;
            //"contextualizing" the differences. Not losing pieces is beter.
            //int ps =0;
            while(i<12){
                if(i==Piece::wp.numb()){
                    int pas = b.getBoard()[i].size();;
                    //ps += pas;
                    score+=(pas - b.getBoard()[i+1].size())*2;
                }
                else if (i==Piece::wn.numb())
                {
                    int ns = b.getBoard()[i].size();
                    score+=(ns - b.getBoard()[i+1].size()) * 5;
                    //ps += (ns*2);
                }
                else if (i==Piece::wb.numb())
                {
                    int bs = b.getBoard()[i].size();
                    score+=(bs - b.getBoard()[i+1].size()) * 8;
                    //ps+= (bs*4);
                }
                else if (i==Piece::wr.numb())
                {
                    int rs = b.getBoard()[i].size();
                    score+=(rs - b.getBoard()[i+1].size()) * 8;
                    //ps+= (rs*4);
                }
                else if (i==Piece::wq.numb())
                {
                    int qs = b.getBoard()[i].size();
                    score+=(qs - b.getBoard()[i+1].size()) * 18;
                    //ps += (qs*6);
                }
                
                i+=2;
            }
            score +=(wkprtct-bkprtct);
            score += (wcrtl - bcrtl);
            //score += ps;
            /**b.setTurn(PieceColor::Black);
            auto opmobility = std::vector<Move>();
            generateMoves(opmobility,b);
            score -= (opmobility.size())/2;
            b.setTurn(PieceColor::White);
            auto mobility = std::vector<Move>();
            generateMoves(mobility,b);
            score += (mobility.size())/2;*/

        }
        else{
            int i=2;
            //int ps =0;
            while(i<=12){
                if(i==Piece::bp.numb()){
                    int pas = b.getBoard()[i].size();
                    //ps+= pas;
                    score+=(pas - b.getBoard()[i-1].size())*2;
                }
                else if (i==Piece::bn.numb())
                {
                    int ns = b.getBoard()[i].size();
                    score+=(ns - b.getBoard()[i-1].size()) * 5;
                    //ps+=(ns*2);
                }
                else if (i==Piece::bb.numb())
                {
                    int bs = b.getBoard()[i].size();
                    score+=(bs - b.getBoard()[i-1].size()) * 8;
                    //ps += (bs*4);
                }
                else if (i==Piece::br.numb())
                {
                    int rs = b.getBoard()[i].size();
                    score+=(rs - b.getBoard()[i-1].size()) * 8;
                    //ps+=(rs*4);
                }
                else if (i==Piece::bq.numb())
                {
                    int qs = b.getBoard()[i].size();
                    score+=(qs - b.getBoard()[i-1].size()) * 18;
                    //ps += (qs *6);
                }
                
                i+=2;
            }
            score +=(bkprtct-wkprtct);
            score += (bcrtl - wcrtl);
            //score += ps;
            /**b.setTurn(PieceColor::White);
            auto opmobility = std::vector<Move>();
            generateMoves(opmobility,b);
            score -= (opmobility.size())/2;
            b.setTurn(PieceColor::Black);
            auto mobility = std::vector<Move>();
            generateMoves(mobility,b);
            score += (mobility.size())/2;*/
        }
        return score;

    }
};
/**std::optional<HashInfo> Engine::hashInfo() const {
    return std::nullopt;
}

void Engine::setHashSize(std::size_t) {}*/


 //checking if the previous move leads to a check situation.
/**if(t==PieceColor::Black){
            //t=PieceColor::Black;
            ksq = Square::fromIndex(node.getBoard()[Piece::bk.numb()][0]);
            int ch = node.inCheck(t,ksq.value());
            if(ch!=-1){
                auto mvs =std::vector<Move>();
                node.setTurn(PieceColor::Black);
                generateMoves(mvs,node);
                bool allcheck =true;
                for(auto m : mvs){
                    auto nbrd =   Board(node);
                    nbrd.setTurn(PieceColor::Black);
                    nbrd.makeMove(m);
                    ksq = Square::fromIndex(nbrd.getBoard()[Piece::bk.numb()][0]);
                    if(nbrd.inCheck(t,ksq.value())==-1){
                        allcheck =false;
                        break;
                    }
                }
                if(allcheck){
                    auto pv =std::make_tuple(std::vector<Move>(),INF);
                    return pv;
                }
                else{
                    auto pv =std::make_tuple(std::vector<Move>(),CHECK);
                    return pv;
                }
                
            }
        }
        else{
            ksq = Square::fromIndex(node.getBoard()[Piece::wk.numb()][0]);
            if(node.inCheck(t,ksq.value())!=-1){
                auto mvs =std::vector<Move>();
                node.setTurn(PieceColor::White);
                generateMoves(mvs,node);
                bool allcheck =true;
                for(auto m : mvs){
                    auto nbrd =   Board(node);
                    nbrd.setTurn(PieceColor::White);
                    nbrd.makeMove(m);
                    ksq = Square::fromIndex(nbrd.getBoard()[Piece::wk.numb()][0]);
                    if(nbrd.inCheck(t,ksq.value())==-1){
                        allcheck =false;
                        break;
                    }
                }
                if(allcheck){
                    auto pv =std::make_tuple(std::vector<Move>(),INF);
                    return pv;
                }
                else{
                    auto pv =std::make_tuple(std::vector<Move>(),CHECK);
                    return pv;
                }
            }
        }
        
        if(depth==5){
                doNOthing(depth);
            }
            if(depth==4){
                doNOthing(depth);
            }
            if(depth==3){
                doNOthing(depth);
            }
            if(depth==2){
                doNOthing(depth);
            }
            if(depth==1){
                doNOthing(depth);
            }
    int doNOthing(int a){
        return a;
    }
        
        */