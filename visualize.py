import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from random import sample

from generate_data import *

N_TOTAL_PIECES = 25
RANDOM_COLORS = ['#'+''.join(sample('0123456789ABCDEF',6)) for i in range(N_TOTAL_PIECES + 1)]

def animate_all_possible_shapes():
	ALL_POSSIBLE_PIECES = all_possible_pieces()

	fig = plt.figure(figsize=(7, 7))
	ax = fig.gca(projection='3d')

	def voxelfy(piece):
		voxels = np.zeros((5,5,5), dtype=int)
		for i,j,k in piece:
			voxels[i][j][k] = 1
		return voxels

	def animate(voxels):
		ax.clear()
		ax.voxels(voxels, edgecolor='k')

	voxels_array = np.array([voxelfy(piece) for piece in ALL_POSSIBLE_PIECES])
	ani = FuncAnimation(fig, animate, frames=voxels_array, interval=1)
	plt.show()


def visualize_state(data, close=False):
	assert(type(data) == np.ndarray)
	assert(data.shape == (5,5,5))

	fig = plt.figure(figsize=(7, 7))
	ax = fig.gca(projection='3d')

	voxel_colors = np.empty(data.shape, dtype=object)
	for i in range(N_TOTAL_PIECES + 1):
		voxel_colors[data == i] = RANDOM_COLORS[i]

	ax.voxels(data, edgecolor='k', facecolors=voxel_colors)

	if close:
		plt.show(block=False)
		plt.pause(0.0000001)
		plt.close()
	else:
		plt.show()
	return


def animate_solution(data, framerate=1000):
	assert(type(data) == np.ndarray)
	assert(data.shape == (5,5,5))

	fig = plt.figure(figsize=(7, 7))
	ax = fig.gca(projection='3d')

	# def init():
		# print("hello")
		# ax.clear()

	def animate(voxels):
		if voxels[0][0][0]:
			ax.clear()
		ax.voxels(voxels, edgecolor='k')

	voxels_array = np.array([data == i for i in range(N_TOTAL_PIECES + 1)])
	ani = FuncAnimation(fig, animate, frames=voxels_array, interval=framerate)
	plt.show()







	'''

	solution_list = np.array([])
	partial_solution = np.empty(data.shape, dtype=object)
	partial_colors = np.empty(data.shape, dtype=object)

	for i in range(N_TOTAL_PIECES):
		partial_solution[data == i] = i
		partial_colors[partial_solution == i] = RANDOM_COLORS[i]
		# solution_list.append(i)
		np.append(solution_list, partial_solution)
	'''








