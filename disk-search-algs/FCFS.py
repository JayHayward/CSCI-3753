# FCFS Disk Scheduling algorithm

size = 10;
def FCFS(arr, head):

	seek_dist = 0
	distance, cur_track = 0, 0

	for i in range(size):
		cur_track = arr[i]

		# calculate absolute distance
		distance = abs(cur_track - head)
		# increase the total distance
		seek_dist += distance
		# accessed track is now new head
		head = cur_track

	print("Total seek distance = {}".format(seek_dist))

	# Seek sequence is unchanged
	print("Starting head position is: {}".format(start))
	print("Seek Sequence is")

	for i in range(size):
		print(arr[i])

if __name__ == '__main__':
	proc = [ 2069, 1212, 2296, 2800, 544, 1618, 356, 1523, 4965, 3681 ]
	start = 2150

	FCFS(proc, start)
