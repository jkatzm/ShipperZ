//
//  puzzle_state.cpp
//  speed_puzzle
//
//  Created by Jordan Katz on 5/22/20.
//  Copyright © 2020 Jordan Katz. All rights reserved.
//

#include "puzzle_state.h"

Puzzle_State::Puzzle_State() {
    this->n_placed = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 5; k++) {
                this->data[i][j][k] = 0;
            }
        }
    }
}

int Puzzle_State::at(Coord c) const {
    return this->data[c.x][c.y][c.z];
}

int Puzzle_State::num_placed() const {
    return this->n_placed;
}

void Puzzle_State::write(std::ostream& ofs) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 5; k++) {
                ofs << this->data[i][j][k] << ' ';
            }
            ofs << '\n';
        }
        ofs << '\n';
    }
    ofs << '\n';
}

bool Puzzle_State::overlaps(const Piece& p) const {
    for (auto c : p.coordinates) {
        if (this->at(c) != 0) {
            return true;
        }
    }
    return false;
}

void Puzzle_State::merge(const Piece& p) {
    this->n_placed++;
    for (auto c : p.coordinates) {
        this->data[c.x][c.y][c.z] = this->n_placed;
    }
}

void Puzzle_State::unmerge(const Piece& p) {
    this->n_placed--;
    for (auto c : p.coordinates) {
        this->data[c.x][c.y][c.z] = 0;
    }
}

bool Puzzle_State::is_full() const {
    return this->n_placed == N_TOTAL_PIECES;
}

bool Puzzle_State::is_solvable(const std::unordered_map<int, std::vector<Piece>>& pieces_at_pos) const {
    for (int pos = 0; pos < MAX_POS; pos++) {
        if (this->at(Coord(pos)) == 0) { // exlore each empty space
            int n_legal_moves = 0;
            for (const Piece& p : pieces_at_pos.at(pos)) {
                if (!this->overlaps(p)) {
                    n_legal_moves++;
                }
            }
            if (n_legal_moves == 0) {
                return false;
            }
        }
    }
    return true;
}
