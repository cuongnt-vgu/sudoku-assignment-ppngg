#include "naked_triples.h"

bool isElementPresent(int element, int *array, int size) {
    for (int i = 0; i < size; i++) {
        if (array[i] == element) {
            return true;
        }
    }
    return false;
}

int find_naked_triple_values(Cell **p_cells, int *naked_triple_values)
{
    int counter = 0;
    for (int i = 0; i < BOARD_SIZE; i++){
        if(p_cells[i]->num_candidates > 1 && p_cells[i]->num_candidates < 4)
        {
            int combo[3] = {0};
            int index = 0;
            int *candidates = get_candidates(p_cells[i]);
            int len = p_cells[i]->num_candidates;
            for(int j = 0; j < len; j++)
            {
                if(!isElementPresent(candidates[j], combo, 3))
                {
                    combo[index] = candidates[j];
                    index++;
                }
                if(index == 3)
                {
                    break;
                }
            }
        }
    }
    return counter;
}
void find_naked_triple(Cell **p_cells, NakedTriple *naked_pairs, int *p_counter)
{
    return;
}
int naked_triples(SudokuBoard *p_board){
    return 0;
}