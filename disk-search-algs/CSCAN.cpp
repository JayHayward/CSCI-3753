// C-SCAN Disk Scheduling algorithm

#include <bits/stdc++.h>
using namespace std;

int size = 10;
int disk_size = 5000;
int start = 2150;

void CSCAN(int arr[], int head)
{
	int seek_dist = 0;
	int distance, cur_track;
	vector<int> left, right;
	vector<int> seek_sequence;

	// appending end values
	// which has to be visited
	// before reversing the direction
	left.push_back(0);
	right.push_back(disk_size - 1);

	// tracks on the left of the
	// head will be serviced when
	// once the head comes back
	// to the beggining (left end).
	for (int i = 0; i < size; i++) {
		if (arr[i] < head)
			left.push_back(arr[i]);
		if (arr[i] > head)
			right.push_back(arr[i]);
	}

	// sorting left and right vectors
	std::sort(left.begin(), left.end());
	std::sort(right.begin(), right.end());

	// first service the requests
	// on the right side of the
	// head.
	for (int i = 0; i < right.size(); i++) {
		cur_track = right[i];
		// appending current track to seek sequence
		seek_sequence.push_back(cur_track);

		// calculate absolute distance
		distance = abs(cur_track - head);

		// increase the total count
		seek_dist += distance;

		// accessed track is now new head
		head = cur_track;
	}

	// once reached the right end
	// jump to the beggining.
	head = 0;

	// Now service the requests again
	// which are left.
	for (int i = 0; i < left.size(); i++) {
		cur_track = left[i];

		// appending current track to seek sequence
		seek_sequence.push_back(cur_track);

		// calculate absolute distance
		distance = abs(cur_track - head);

		// increase the total count
		seek_dist += distance;

		// accessed track is now the new head
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

	// request array
	int proc[size] = { 2069, 1212, 2296, 2800, 544, 1618, 356, 1523, 4965, 3681 };
	int head = 2150;

	CSCAN(proc, head);

	return 0;
}


//Compile: gcc CSCAN.cpp -lstdc++ -o CSCAN.out
