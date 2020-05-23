//
//  primitives.h
//  speed_puzzle
//
//  Created by Jordan Katz on 5/22/20.
//  Copyright © 2020 Jordan Katz. All rights reserved.
//

#ifndef primitives_h
#define primitives_h

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <cassert>
#include <chrono>

const int MAX_POS = 125;
const int N_TOTAL_PIECES = 25;
const int N_COORD_PER_PIECE = 5;

struct Coord {
    int x, y, z;
    
    Coord(int x_in, int y_in, int z_in) : x(x_in), y(y_in), z(z_in) {}
    
    Coord(int pos) {
        assert(0 <= pos && pos < MAX_POS);
        this->x = pos / 25;
        this->y = pos % 25 / 5;
        this->z = pos % 25 % 5;
    }
    
    int to_int() {
        return 25*this->x + 5*this->y + this->z;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Coord& c) {
        os << "(" << c.x << "," << c.y << "," << c.z << ") ";
        return os;
    }
};

struct Piece {
    std::vector<Coord> coordinates; // coordinates.size() == N_COORD_PER_PIECE
};

#endif /* primitives_h */
