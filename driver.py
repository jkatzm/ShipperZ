import pandas as pd
import sys

from visualize import *

def write_data(output_filename):
	print("writing data...")
	ALL_POSSIBLE_PIECES = all_possible_pieces()
	PIECES_AT_COORD = {c : [p for p in ALL_POSSIBLE_PIECES if c in p] for c in product(range(5), repeat=3)}

	with open(output_filename, "w+") as f:
		for coord,pieces in PIECES_AT_COORD.items():
			coord_str = str(coord).replace('(',' ').replace(')',' ').replace(', ', ' ').strip(' ') 
			f.write(coord_str + ' ')
			f.write(str(len(pieces)) + '\n')

			for voxel in pieces:
				voxel_str = str(voxel).replace('(',' ').replace(')',' ').replace(', ', ' ').strip(' ').replace('  ','')
				
				if coord == (4,4,4) and voxel == pieces[-1]:
					f.write(voxel_str) # avoid space at end of file, easie for C++ read

				else:
					f.write(voxel_str + '\n')

	f.close()
	print("write complete.")
	return

def read_cpp_solution(input_filename):
	solution = np.zeros((5,5,5), dtype=int)

	data = pd.read_csv(input_filename, header=None, sep=" ")
	data = data.dropna(axis=1)

	for i in range(5):
		for j in range(5):
			line = data.iloc[5*i + j]
			for k in range(5):
				solution[i][j][k] = int(line.iloc[k])

	return solution

def main():
	print('Number of arguments:', len(sys.argv), 'arguments.')
	print('Argument List:', str(sys.argv))

	if sys.argv[1] == 'w': # output
		python_output_file = "python_output.txt"
		write_data(python_output_file)
	
	elif sys.argv[1] == 'r': # input
		cpp_input_file = "cpp_output.txt"
		solution = read_cpp_solution(cpp_input_file)
		visualize(solution)

	else:
		print("error")

	return

if __name__ == "__main__": 
    main() 
