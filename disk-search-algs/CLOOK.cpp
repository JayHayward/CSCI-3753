// CLOOK Disk Scheduling algorithm

#include <bits/stdc++.h>
using namespace std;

int size = 10;
int disk_size = 5000;
int start = 2150;

// Function to perform C-LOOK on the request
// array starting from the given head
void CLOOK(int arr[], int head)
{
	int seek_dist = 0;
	int distance, cur_track;
	vector<int> left, right;
	vector<int> seek_sequence;

	// Tracks on the left of the
	// head will be serviced when
	// once the head comes back
	// to the beggining (left end)
	for (int i = 0; i < size; i++) {
		if (arr[i] < head)
			left.push_back(arr[i]);
		if (arr[i] > head)
			right.push_back(arr[i]);
	}

	// Sorting left and right vectors
	std::sort(left.begin(), left.end());
	std::sort(right.begin(), right.end());

	// First service the requests
	// on the right side of the
	// head
	for (int i = 0; i < right.size(); i++) {
		cur_track = right[i];

		// Appending current track to seek sequence
		seek_sequence.push_back(cur_track);

		// Calculate absolute distance
		distance = abs(cur_track - head);

		// Increase the total count
		seek_dist += distance;

		// Accessed track is now new head
		head = cur_track;
	}

	// Once reached the right end
	// jump to the last track that
	// is needed to be serviced in
	// left direction
	seek_dist += abs(head - left[0]);
	head = left[0];

	// Now service the requests again
	// which are left
	for (int i = 0; i < left.size(); i++) {
		cur_track = left[i];

		// Appending current track to seek sequence
		seek_sequence.push_back(cur_track);

		// Calculate absolute distance
		distance = abs(cur_track - head);

		// Increase the total count
		seek_dist += distance;

		// Accessed track is now the new head
		head = cur_track;
	}

	cout << "Total seek distance = " << seek_dist << endl;
	cout << "Starting head position is: " << start << endl;
	cout << "Seek Sequence is" << endl;

	for (int i = 0; i < seek_sequence.size(); i++) {
		cout << seek_sequence[i] << endl;
	}
}

// Driver code
int main()
{
	// Request array
	int proc[size] = { 2069, 1212, 2296, 2800, 544, 1618, 356, 1523, 4965, 3681 };
	int head = 2150;

	CLOOK(proc, head);

	return 0;
}


//Compile: gcc CLOOK -lstdc++ -o CLOOK.out
