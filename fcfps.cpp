#include <iomanip>
#include <iostream>

using namespace std;

int main() {
	const int MAX = 20;
	int n, pid[MAX], at[MAX], bt[MAX];
	int start[MAX], ct[MAX], tat[MAX], wt[MAX], rt[MAX];
	int time = 0;
	float totalTat = 0, totalWt = 0;

	cout << "Enter number of processes: ";
	cin >> n;

	if (n <= 0 || n > MAX) {
		cout << "Enter between 1 and " << MAX << " processes.\n";
		return 1;
	}

	for (int i = 0; i < n; i++) {
		pid[i] = i + 1;
		cout << "Enter arrival time and burst time for P" << pid[i] << ": ";
		cin >> at[i] >> bt[i];

		if (at[i] < 0 || bt[i] <= 0) {
			cout << "Arrival time must be 0 or more and burst time must be greater than 0.\n";
			return 1;
		}
	}

	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (at[i] > at[j]) {
				swap(pid[i], pid[j]);
				swap(at[i], at[j]);
				swap(bt[i], bt[j]);
			}
		}
	}

	for (int i = 0; i < n; i++) {
		if (time < at[i]) {
			time = at[i];
		}

		start[i] = time;
		ct[i] = time + bt[i];             // Completion time
		tat[i] = ct[i] - at[i];           // Turnaround time
		wt[i] = tat[i] - bt[i];            // Waiting time
		rt[i] = wt[i];                     // Response time in FCFS
		time = ct[i];
		totalTat += tat[i];
		totalWt += wt[i];
	}

	cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT\n";
	for (int i = 0; i < n; i++) {
		cout << "P" << pid[i] << "\t"
			 << at[i] << "\t"
			 << bt[i] << "\t"
			 << ct[i] << "\t"
			 << tat[i] << "\t"
			 << wt[i] << "\t"
			 << rt[i] << "\n";
	}

	cout << fixed << setprecision(2);
	cout << "\nAverage TAT = " << totalTat / n << "\n";
	cout << "Average WT  = " << totalWt / n << "\n";

	cout << "\nGantt Chart\n|";
	for (int i = 0; i < n; i++) {
		if ((i == 0 && start[i] > 0) || (i > 0 && start[i] > ct[i - 1])) {
			cout << " Idle |";
		}
		cout << " P" << pid[i] << " |";
	}
	cout << "\n" << (start[0] > 0 ? 0 : start[0]);
	if (start[0] > 0) {
		cout << "\t" << start[0];
	}
	for (int i = 0; i < n; i++) {
		if (i > 0 && start[i] > ct[i - 1]) {
			cout << "\t" << start[i];
		}
		cout << "\t" << ct[i];
	}
	cout << '\n';

	return 0;
}
