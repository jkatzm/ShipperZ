//
//  main.cpp
//  speed_puzzle
//
//  Created by Jordan Katz on 5/21/20.
//  Copyright © 2020 Jordan Katz. All rights reserved.
//

#include "puzzle_state.h"

const auto T0 = std::chrono::high_resolution_clock::now(); // timer

void print_time() {
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - T0);
    std::cout << duration.count() << " sec\n";
}

std::unordered_map<int, std::vector<Piece>> PIECES_AT_POS;
std::vector<Puzzle_State> SOLUTIONS;

void read_python_data(std::string input_filename) {
    std::cout << "Reading data...\n";
    std::ifstream input_file(input_filename);
    assert(input_file.good());
    
    std::string line;
    int x, y, z, n_pieces;
    
    while (!input_file.eof()) {
        input_file >> x >> y >> z >> n_pieces;
        int pos = Coord(x,y,z).to_int();
        for (int i = 0; i < n_pieces; i++) {
            Piece p;
            for (int j = 0; j < N_COORD_PER_PIECE; j++) {
                input_file >> x >> y >> z;
                p.coordinates.push_back(Coord(x,y,z));
            }
            PIECES_AT_POS[pos].push_back(p);
        }
    }
    
    input_file.close();
    std::cout << "Read complete.\n\n";
}

bool solve(Puzzle_State& state, int pos) {
    // TODO: get rid of the bool return signature
    // std::cout << state.num_placed() << '\n';
    
    if (state.is_full() || state.num_placed() == 20) { // TODO: erase 20
        std::cout << "Solution found! ";
        print_time();
        SOLUTIONS.push_back(state);
        return true;
    }
    if (!state.is_solvable(PIECES_AT_POS)) {
        return false;
    }
    int next_vacant = pos;
    while (state.at(Coord(next_vacant)) != 0) {
        next_vacant++;
    }
    for (const Piece& p : PIECES_AT_POS[next_vacant]) {
        if (!state.overlaps(p)) {
            state.merge(p);
            if (solve(state, next_vacant+1)) {
                return true;
            }
            state.unmerge(p);
        }
    }
    return false;
}

void write_solution(std::string output_filename = "") {
    std::cout << "Writing solution...\n";
    if (output_filename == "") {
        for (auto s : SOLUTIONS) {
            s.write(std::cout);
        }
    }
    else {
        std::ofstream output_file(output_filename);
        assert(output_file.good());
        for (auto s : SOLUTIONS) {
            s.write(output_file);
        }
        output_file.close();
    }
    std::cout << "Write complete.\n\n";
}

int main(int argc, const char * argv[]) {
    const std::string python_input_file = "python_output.txt";
    const std::string cpp_output_file = "cpp_output.txt";
    
    Puzzle_State empty_puzzle;
    
    read_python_data(python_input_file);
    std::cout << "Solving...\n";
    solve(empty_puzzle, 0);
    std::cout << "Solve complete.\n\n";
    write_solution(cpp_output_file);
    
    return 0;
}
