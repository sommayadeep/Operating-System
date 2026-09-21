#include <iostream>
using namespace std;

int main() {
    int n, tq;

    cout << "Enter number of processes: ";
    cin >> n;

    int bt[100], rem[100], wt[100], tat[100];

    for (int i = 0; i < n; i++) {
        wt[i] = 0;

        cout << "Enter burst time of P" << i + 1 << ": ";
        cin >> bt[i];

        rem[i] = bt[i];
    }

    cout << "Enter Time Quantum: ";
    cin >> tq;

    int time = 0;
    bool done;

    do {
        done = true;

        for (int i = 0; i < n; i++) {

            if (rem[i] > 0) {
                done = false;

                if (rem[i] > tq) {
                    time += tq;
                    rem[i] -= tq;
                }
                else {
                    time += rem[i];
                    wt[i] = time - bt[i];
                    rem[i] = 0;
                }
            }
        }

    } while (!done);

    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }

    cout << "\nProcess\tBT\tWT\tTAT\n";

    for (int i = 0; i < n; i++) {
        cout << "P" << i + 1 << "\t"
             << bt[i] << "\t"
             << wt[i] << "\t"
             << tat[i] << endl;
    }

    return 0;
}