#include "Simplification.h"

std::stack<Variable*>* doSimplification(InterferenceGraph* ig, int degree)
{
    std::stack<Variable*>* retval = new std::stack<Variable*>();
    InterferenceGraph* igCopy = new InterferenceGraph();
    igCopy->size = ig->size;
    igCopy->variables = ig->variables;

    igCopy->values.resize(ig->size);
    for (int i = 0; i < ig->size; ++i)
        igCopy->values[i].resize(ig->size);

    for (int i = 0; i < igCopy->size; i++)
        for (int j = 0; j < igCopy->size; j++)
            igCopy->values[i][j] = ig->values[i][j];

    std::vector<int> used;
    for (int k = 0; k < igCopy->size; k++) {
        int max_pos = -1;
        int max_count = -1;
        for (int i = 0; i < igCopy->size; i++) {
            int counter = 0;
            for (int j = 0; j < igCopy->size; j++) {
                if (igCopy->values[i][j] == __INTERFERENCE__) 
                    counter++;
            }
            if (counter > max_count && counter < degree && find(used.begin(), used.end(), i) == used.end()) {
                max_pos = i;
                max_count = counter;
            }
        }

        if (max_pos == -1) return NULL;
        used.push_back(max_pos);

        for (int i = 0; i < igCopy->size; i++) {
            igCopy->values[i][max_pos] = __REMOVED__;
            igCopy->values[max_pos][i] = __REMOVED__;
        }
        igCopy->values[max_pos][max_pos] = __REMOVED__;

        for (Variables::iterator it = igCopy->variables->begin(); it != igCopy->variables->end(); it++) {
            if ((*it)->pos() == max_pos) {
                retval->push(*it);
                break;
            }
        }
    }
    return retval;
}

void printSimplificationStack(std::stack<Variable*>* st)
{
    std::cout << "\n*** SIMPLIFICATION STACK ***\n\n";
    std::deque<Variable*> temp;
    while (!st->empty()) {
        std::cout << st->top()->name() << std::endl;
        temp.push_back(st->top());
        st->pop();
    }
    std::cout << std::endl;
    while (!temp.empty()) {
        st->push(temp.back());
        temp.pop_back();
    }
}
