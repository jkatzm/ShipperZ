import numpy as np
from scipy.spatial.transform import Rotation
from itertools import product

def shift_positive(piece):
	assert(type(piece) == np.matrix)

	for i in range(3): # 3 dimensions
		min_i = min(piece[:,i])
		if min_i < 0:
			piece[:,i] += abs(min_i)
	return

def rotation_set(piece):
	assert(type(piece) == np.matrix)
	# e.g. for piece == PENTOMINO: returns the 24 possible orientations of the base piece in 3-space
	# ((0, 0, 0), (0, 0, 1), (0, 0, 2), (0, 1, 2), (0, 1, 3))
	#							...
	# ((0, 2, 0), (0, 3, 0), (1, 0, 0), (1, 1, 0), (1, 2, 0))
	rotated = set()
	
	for g in Rotation.create_group("O"): # octahedral group
		rotated_piece = (piece * g.as_matrix()).astype(int)
		shift_positive(rotated_piece)
		coord_list = [tuple(coord.A1) for coord in rotated_piece]
		rotated.add(tuple(sorted(coord_list)))
	
	return sorted(rotated)

def all_possible_pieces():
	# returns the 960 possible pieces in the 5x5x5 cube-space:
	# ((0, 0, 0), (0, 0, 1), (0, 0, 2), (0, 1, 2), (0, 1, 3))
	#							...
	# ((4, 3, 3), (4, 3, 4), (4, 4, 1), (4, 4, 2), (4, 4, 3))
	PENTOMINO = np.matrix([(0, 0, 0), (1, 0, 0), (2, 0, 0), (2, 1, 0), (3, 1, 0)])
	all_possible = set()

	def legal_translations(pos):
		for piece in rotation_set(PENTOMINO):
			translated_piece = np.array(piece) + pos
			if np.all(0 <= translated_piece) and np.all(translated_piece < 5):
				coord_list = [tuple(coord) for coord in translated_piece]
				all_possible.add(tuple(sorted(coord_list)))
		return
	
	for pos in product(range(5), repeat=3):
		legal_translations(pos)

	return sorted(all_possible)

