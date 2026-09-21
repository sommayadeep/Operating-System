#include <iostream>
using namespace std;

int main() {
    int n;

    cout << "Enter number of processes: ";
    cin >> n;

    int bt[100], priority[100], wt[100], tat[100];
    int p[100];

    // Input
    for (int i = 0; i < n; i++) {
        p[i] = i + 1;

        cout << "\nEnter Burst Time of P" << i + 1 << ": ";
        cin >> bt[i];

        cout << "Enter Priority of P" << i + 1 << ": ";
        cin >> priority[i];
    }

    // Sort according to priority
    // Smaller priority number = higher priority
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {

            if (priority[i] > priority[j]) {

                // Swap priority
                int temp = priority[i];
                priority[i] = priority[j];
                priority[j] = temp;

                // Swap burst time
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                // Swap process number
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    // Calculate Waiting Time
    wt[0] = 0;

    for (int i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1];
    }

    // Calculate Turnaround Time
    for (int i = 0; i < n; i++) {
        tat[i] = wt[i] + bt[i];
    }

    // Output
    cout << "\nProcess\tBT\tPriority\tWT\tTAT\n";

    for (int i = 0; i < n; i++) {
        cout << "P" << p[i] << "\t"
             << bt[i] << "\t"
             << priority[i] << "\t\t"
             << wt[i] << "\t"
             << tat[i] << endl;
    }

    return 0;
}