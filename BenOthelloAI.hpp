// BenOthelloAI.hpp


#include "OthelloAI.hpp"


namespace blponce
{
    class BenOthelloAI : public OthelloAI
    {
    public:
        virtual std::pair<int, int> chooseMove(const OthelloGameState& state);
        std::vector<std::pair<int, int>> possibleMoves(const OthelloGameState& state);
        int search(const OthelloGameState& state, int depth, const OthelloCell myTurn);
        int eval(const OthelloGameState& state);
    };
}
