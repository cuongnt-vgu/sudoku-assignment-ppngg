#include "naked_triples.h"

int find_naked_triple_values(Cell **p_cells, int *naked_triple_values)
{
    int counter = 0;
    /*
    (123) (123) (123) - {3/3/3} (in terms of candidates per cell)
    (123) (123) (12) - {3/3/2} (or some combination thereof)
    (123) (12) (23) - {3/2/2}
    (12) (23) (13) - {2/2/2}
    */
    // Case 1: (123) (123) (123)
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
void find_naked_triple(Cell **p_cells, naked *naked_pairs, int *p_counter);
int naked_triples(SudokuBoard *p_board);