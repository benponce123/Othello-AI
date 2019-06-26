// benOthelloAI.cpp



#include <ics46/factory/DynamicFactory.hpp>
#include "BenOthelloAI.hpp"
#include "OthelloCell.hpp"

ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI, blponce::BenOthelloAI, "Ben's Othello AI (Required)");


std::pair<int, int> blponce::BenOthelloAI::chooseMove(const OthelloGameState& state)
{
    std::vector<std::pair<int, int>> moves = possibleMoves(state);
    std::pair<int, int> bestMove;
    OthelloCell myTurn;
    int searchResult, bestResult;

    if (state.isBlackTurn())
    {
        myTurn = OthelloCell::black;
    }
    else
    {
        myTurn = OthelloCell::white;
    }

    for (int i = 0; i < moves.size(); i++)
    {
        std::unique_ptr<OthelloGameState> stateClone = state.clone();
        stateClone->makeMove(moves[i].first, moves[i].second);
        searchResult = search(*stateClone, 3, myTurn);

        if (i == 0)
            bestResult = searchResult;

        if (searchResult >= bestResult)
        {
            bestResult = searchResult;
            bestMove.first = moves[i].first;
            bestMove.second = moves[i].second;
        }
    }

    return bestMove;
}


std::vector<std::pair<int, int>> blponce::BenOthelloAI::possibleMoves(const OthelloGameState& state)
{
    std::vector<std::pair<int, int>> moves;
    for (int i = 0; i < state.board().width(); i++)
    {
        for (int j = 0; j < state.board().height(); j++)
        {
            if (state.isValidMove(i, j))
            {
                moves.push_back(std::make_pair(i, j));
            }
        }
    }
    
    return moves;
}


int blponce::BenOthelloAI::search(const OthelloGameState& state, int depth, const OthelloCell myTurn)
{
    OthelloCell turn;
    std::vector<std::pair<int, int>> moves = possibleMoves(state);

    if (state.isBlackTurn())
    {
        turn = OthelloCell::black;
    }
    else
    {
        turn = OthelloCell::white;
    }

    if (depth == 0)
    {
        return eval(state);
    }

    else
    {
        if (turn == myTurn)
        {
            int max;

            for (int i = 0; i < moves.size(); i++)
            {
                std::unique_ptr<OthelloGameState> stateClone = state.clone();
                stateClone->makeMove(moves[i].first, moves[i].second);
                int result = search(*stateClone, depth - 1, myTurn);

                if (i == 0)
                {
                    max = result;
                }
                else if (result >= max)
                {
                    max = result;
                }
            }
            return max;
        }
        else
        {
            int min;

            for (int j = 0; j < moves.size(); j++)
            {
                std::unique_ptr<OthelloGameState> stateClone = state.clone();
                stateClone->makeMove(moves[j].first, moves[j].second);
                int result = search(*stateClone, depth - 1, myTurn);

                if (j == 0)
                {
                    min = result;
                }
                else if (result <= min)
                { 
                    min = result;
                }
            }
            return min;
        }
    }

    return 0;
}


int blponce::BenOthelloAI::eval(const OthelloGameState& state)
{
    int eval;

    if (state.isBlackTurn())
    {
        eval = state.blackScore() - state.whiteScore();
    }
    else
    {
        eval = state.whiteScore() - state.blackScore();
    }

    return eval;
}


