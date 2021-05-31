/* Autor: Milica Popović Datum: 26.05.2021. */

#include "Simplification.h"

std::stack<Variable*>* doSimplification(InterferenceGraph* ig, int degree)
{
    std::stack<Variable*>* simplificationStack = new std::stack<Variable*>();

    // copy of interference graph, from which nodes will be removed
    InterferenceGraph* igCopy = new InterferenceGraph();    
    igCopy->size = ig->size;
    igCopy->variables = ig->variables;
    igCopy->values.resize(ig->size);

    for (int i = 0; i < ig->size; ++i)
    {
        igCopy->values[i].resize(ig->size);
    }

    for (int i = 0; i < igCopy->size; i++)
    {
        for (int j = 0; j < igCopy->size; j++)
        {
            igCopy->values[i][j] = ig->values[i][j];
        }
    }
        
    std::vector<int> usedVars;
    for (int k = 0; k < igCopy->size; k++) 
    {
        int maxPos = -1;   // postion of node that will be removed
        int maxRemovableRank = -1;  // rank of node that will be removed
        for (int i = 0; i < igCopy->size; i++) 
        {
            int nodeRank = 0;   
            for (int j = 0; j < igCopy->size; j++) 
            {
                if (igCopy->values[i][j] == __INTERFERENCE__)
                {
                    nodeRank++;
                }
            }
            if (nodeRank > maxRemovableRank && nodeRank < degree && find(usedVars.begin(), usedVars.end(), i) == usedVars.end()) 
            {
                maxPos = i;
                maxRemovableRank = nodeRank;
            }
        }

        // unable to remove node - spill detected
        if (maxPos == -1)
            throw std::runtime_error("Spill detected!");  

        usedVars.push_back(maxPos);

        // remove node from graph
        for (int i = 0; i < igCopy->size; i++) 
        {
            igCopy->values[i][maxPos] = __REMOVED__;
            igCopy->values[maxPos][i] = __REMOVED__;
        }
        igCopy->values[maxPos][maxPos] = __REMOVED__;

        for (Variables::iterator it = igCopy->variables->begin(); it != igCopy->variables->end(); it++) 
        {
            // push removed variable to simplification stack
            if ((*it)->pos() == maxPos) 
            {
                simplificationStack->push(*it);
                break;
            }
        }
    }
    return simplificationStack;
}

void printSimplificationStack(std::stack<Variable*>* st)
{
    std::cout << "\n*** SIMPLIFICATION STACK ***\n\n";
    std::deque<Variable*> temp;
    while (!st->empty()) 
    {
        std::cout << st->top()->name() << std::endl;
        temp.push_back(st->top());
        st->pop();
    }
    std::cout << std::endl;
    while (!temp.empty()) 
    {
        st->push(temp.back());
        temp.pop_back();
    }
}
