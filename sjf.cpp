#include <iomanip>
#include <iostream>

using namespace std;

int main() {
	const int MAX = 20;
	int n, at[MAX], bt[MAX], ct[MAX], tat[MAX], wt[MAX], rt[MAX];
	bool done[MAX] = {};
	int time = 0, finished = 0;
	float totalTat = 0, totalWt = 0;

	cout << "Enter number of processes: ";
	cin >> n;

	if (n <= 0 || n > MAX) {
		cout << "Enter between 1 and " << MAX << " processes.\n";
		return 1;
	}

	for (int i = 0; i < n; i++) {
		cout << "Enter arrival time and burst time for P" << i + 1 << ": ";
		cin >> at[i] >> bt[i];
		if (at[i] < 0 || bt[i] <= 0) {
			cout << "Invalid time.\n";
			return 1;
		}
	}

	cout << "\nGantt Chart\n|";
	while (finished < n) {
		int shortest = -1;

		for (int i = 0; i < n; i++) {
			if (!done[i] && at[i] <= time &&
				(shortest == -1 || bt[i] < bt[shortest])) {
				shortest = i;
			}
		}

		if (shortest == -1) {
			cout << " Idle |";
			time++;
			continue;
		}

		rt[shortest] = time - at[shortest];
		wt[shortest] = rt[shortest];
		time += bt[shortest];
		ct[shortest] = time;
		tat[shortest] = ct[shortest] - at[shortest];
		totalTat += tat[shortest];
		totalWt += wt[shortest];
		done[shortest] = true;
		finished++;

		cout << " P" << shortest + 1 << " |";
	}

	cout << "\n\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT\n";
	for (int i = 0; i < n; i++) {
		cout << "P" << i + 1 << "\t" << at[i] << "\t" << bt[i]
			 << "\t" << ct[i] << "\t" << tat[i] << "\t"
			 << wt[i] << "\t" << rt[i] << '\n';
	}

	cout << fixed << setprecision(2);
	cout << "\nAverage TAT = " << totalTat / n;
	cout << "\nAverage WT  = " << totalWt / n << '\n';
}
