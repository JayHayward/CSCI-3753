# SSTF disk scheduling

def calculateDifference(queue, head, diff):
	for i in range(len(diff)):
		diff[i][0] = abs(queue[i] - head)

def findMin(diff):

	index = 0
	minimum = 999999999

	for i in range(len(diff)):
		if (not diff[i][1] and
				minimum > diff[i][0]):
			minimum = diff[i][0]
			index = i
	return index

def shortestSeekTimeFirst(request, head):
		if (len(request) == 0):
			return
		l = len(request)
		diff = [0] * l

		# initialize array
		for i in range(l):
			diff[i] = [0, 0]

		seek_dist = 0
		seek_sequence = [0] * (l + 1)

		for i in range(l):
			seek_sequence[i] = head
			calculateDifference(request, head, diff)
			index = findMin(diff)

			diff[index][1] = True
			seek_dist += diff[index][0]
			head = request[index]

		# for last accessed track
		seek_sequence[len(seek_sequence) - 1] = head

		print("Total seek distance = {}".format(seek_dist))
		print("Starting head position is: {}".format(start))
		print("Seek Sequence is")

		for i in range(l):
			print(seek_sequence[i+1])

if __name__ =="__main__":

	proc = [ 2069, 1212, 2296, 2800, 544, 1618, 356, 1523, 4965, 3681 ]
	start = 2150
	shortestSeekTimeFirst(proc, start)
