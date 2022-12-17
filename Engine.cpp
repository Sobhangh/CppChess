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
        auto ngmx = negamax(b,5,-1*INF,INF,1);
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
    const int CHECK = 100;

    std::tuple<std::vector<Move>,int> negamax(Board& node, int depth, int a, int b, int color) {
        if (depth == 0){ //or node is a terminal node then
            auto pv =std::make_tuple(std::vector<Move>(),heuristic(node,node.turn()));
            return pv;
        } 
        Square::Optional ksq = std::nullopt;
        PieceColor t = PieceColor::White;
        if(node.turn() == PieceColor::White){
            t = PieceColor::Black;
        }
        
        std::vector<Move> childNodes =std::vector<Move>();
        generateMoves(childNodes,node);
        orderMoves(childNodes,node.turn(),node.getcBoard());
        auto value = -1*INF;
        std::tuple<std::vector<Move>,int> pvmax;
        bool allcheck =true;
        //bool prune =false;
        for(auto child : childNodes){
            auto nb =   Board(node);
            nb.makeMove(child);
            bool inch = false;
            if(node.turn() == PieceColor::White){
                ksq = Square::fromIndex(nb.getBoard()[Piece::wk.numb()][0]);
                if(nb.inCheck(PieceColor::White,ksq.value())!=-1){
                    inch =true;
                }
            }
            else{
                ksq = Square::fromIndex(nb.getBoard()[Piece::bk.numb()][0]);
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
                ks = Square::fromIndex(node.getBoard()[Piece::wk.numb()][0]);
                if(node.inCheck(tu,ks.value())!=-1){
                    auto pv =std::make_tuple(std::vector<Move>(),-1*INF);
                    return pv;
                }
                auto pv =std::make_tuple(std::vector<Move>(),0);
                return pv;
            }
            else{
                tu=PieceColor::Black;
                ks = Square::fromIndex(node.getBoard()[Piece::bk.numb()][0]);
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

    bool comp(Move& a,Move& b){
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
        if(Square::HammingDist(a.from(),a.to())> Square::HammingDist(b.from(),b.to())){
            return true;
        }
        return false;
    }
    //give the color: if move is towards the other side then it is better than towrards your own side
    void orderMoves(std::vector<Move>& boardVc, PieceColor c,std::vector<int> cb){
        std::sort(boardVc.begin(),boardVc.end(),[c,cb](Move& a,Move& b){
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
        int score =0;
        if(cb[a.to().index()] >  cb[b.to().index()]){
            score += (cb[a.to().index()]);
        }
        else if(cb[a.to().index()] <  cb[b.to().index()]){
            score -= (cb[b.to().index()]);
        }

        if(c == PieceColor::White){
            int cda = std::abs((int)a.to().rank()-5);
            int cdb = std::abs((int)b.to().rank()-5);
            score+= cdb-cda;
        }
        else{
            int cda = std::abs((int)a.to().rank()-2);
            int cdb = std::abs((int)b.to().rank()-2);
            score+= cdb-cda;
        }
        score += (Square::HammingDist(a.from(),a.to())- Square::HammingDist(b.from(),b.to()));
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



    int heuristic(Board& b,PieceColor c){
        int score =0;
        if(c==PieceColor::White){
            Square::Optional ksq = Square::fromIndex(b.getBoard()[Piece::wk.numb()][0]);
            if(b.inCheck(PieceColor::White, ksq.value())!=-1){
                score+= -1*CHECK;
            }
            Square::Optional bksq = Square::fromIndex(b.getBoard()[Piece::bk.numb()][0]);
            if(b.inCheck(PieceColor::Black, bksq.value())!=-1){
                score+= CHECK;
            }
        }
        else{
            Square::Optional ksq = Square::fromIndex(b.getBoard()[Piece::bk.numb()][0]);
            if(b.inCheck(PieceColor::Black, ksq.value())!=-1){
                score+= -1*CHECK;
            }
            Square::Optional bksq = Square::fromIndex(b.getBoard()[Piece::wk.numb()][0]);
            if(b.inCheck(PieceColor::White, bksq.value())!=-1){
                score+= CHECK;
            }
        }
        
        if(c==PieceColor::White){
            int i=1;
            while(i<=12){
                if(i==Piece::wp.numb()){
                    score+=(b.getBoard()[i].size() - b.getBoard()[i+1].size());
                }
                else if (i==Piece::wn.numb())
                {
                    score+=(b.getBoard()[i].size() - b.getBoard()[i+1].size()) * 3;
                }
                else if (i==Piece::wb.numb())
                {
                    score+=(b.getBoard()[i].size() - b.getBoard()[i+1].size()) * 5;
                }
                else if (i==Piece::wr.numb())
                {
                    score+=(b.getBoard()[i].size() - b.getBoard()[i+1].size()) * 5;
                }
                else if (i==Piece::wq.numb())
                {
                    score+=(b.getBoard()[i].size() - b.getBoard()[i+1].size()) * 9;
                }
                
                i+=2;
            }
            b.setTurn(PieceColor::Black);
            auto opmobility = std::vector<Move>();
            generateMoves(opmobility,b);
            score -= (opmobility.size())/2;
            b.setTurn(PieceColor::White);
            auto mobility = std::vector<Move>();
            generateMoves(mobility,b);
            score += (mobility.size())/2;
        }
        else{
            int i=2;
            while(i<=12){
                if(i==Piece::bp.numb()){
                    score+=(b.getBoard()[i].size() - b.getBoard()[i-1].size());
                }
                else if (i==Piece::bn.numb())
                {
                    score+=(b.getBoard()[i].size() - b.getBoard()[i-1].size()) * 3;
                }
                else if (i==Piece::bb.numb())
                {
                    score+=(b.getBoard()[i].size() - b.getBoard()[i-1].size()) * 5;
                }
                else if (i==Piece::br.numb())
                {
                    score+=(b.getBoard()[i].size() - b.getBoard()[i-1].size()) * 5;
                }
                else if (i==Piece::bq.numb())
                {
                    score+=(b.getBoard()[i].size() - b.getBoard()[i-1].size()) * 9;
                }
                
                i+=2;
            }
            b.setTurn(PieceColor::White);
            auto opmobility = std::vector<Move>();
            generateMoves(opmobility,b);
            score -= (opmobility.size())/2;
            b.setTurn(PieceColor::Black);
            auto mobility = std::vector<Move>();
            generateMoves(mobility,b);
            score += (mobility.size())/2;
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
        }*/