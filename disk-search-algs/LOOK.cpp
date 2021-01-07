// LOOK Disk Scheduling algorithm

#include <bits/stdc++.h>
using namespace std;


int size = 10;
int disk_size = 5000;
int start = 2150;

void LOOK(int arr[], int head, string direction)
{
	int seek_dist = 0;
	int distance, cur_track;
	vector<int> left, right;
	vector<int> seek_sequence;

	// appending values which are
	// currently at left and right
	// direction from the head.
	for (int i = 0; i < size; i++) {
		if (arr[i] < head)
			left.push_back(arr[i]);
		if (arr[i] > head)
			right.push_back(arr[i]);
	}

	// sorting left and right vectors
	// for servicing tracks in the
	// correct sequence.
	std::sort(left.begin(), left.end());
	std::sort(right.begin(), right.end());

	// run the while loop two times.
	// one by one scanning right
	// and left side of the head
	int run = 2;
	while (run--) {
		if (direction == "left") {
			for (int i = left.size() - 1; i >= 0; i--) {
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
			// reversing the direction
			direction = "right";
		}
		else if (direction == "right") {
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
			// reversing the direction
			direction = "left";
		}
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
	string direction = "right";

	LOOK(proc, head, direction);

	return 0;
}


//Compile: gcc LOOK.cpp -lstdc++ -o LOOK.out
