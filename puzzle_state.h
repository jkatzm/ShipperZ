//
//  puzzle_state.h
//  speed_puzzle
//
//  Created by Jordan Katz on 5/22/20.
//  Copyright © 2020 Jordan Katz. All rights reserved.
//

#ifndef puzzle_state_h
#define puzzle_state_h

#include "primitives.h"

class Puzzle_State {
    int data[5][5][5];
    int n_placed;
    
public:
    Puzzle_State();
    int at(Coord c) const;
    int num_placed() const;
    void write(std::ostream& ofs);
    bool overlaps(const Piece& p) const;
    void merge(const Piece& p);
    void unmerge(const Piece& p);
    bool is_full() const;
    bool is_solvable(const std::unordered_map<int, std::vector<Piece>>& pieces_at_pos) const;
};

#endif /* puzzle_state_h */
