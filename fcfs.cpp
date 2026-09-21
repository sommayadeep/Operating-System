#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    int responseTime;
};

struct GanttEntry {
    string label;
    int startTime;
    int endTime;
};

int main() {
    int processCount;

    cout << "Enter number of processes: ";
    cin >> processCount;

    if (!cin || processCount <= 0) {
        cerr << "Number of processes must be greater than 0.\n";
        return 1;
    }

    vector<Process> processes(processCount);

    for (int index = 0; index < processCount; ++index) {
        processes[index].id = index + 1;
        cout << "Enter AT and BT for P" << processes[index].id << ": ";
        cin >> processes[index].arrivalTime >> processes[index].burstTime;

        if (!cin || processes[index].arrivalTime < 0 || processes[index].burstTime <= 0) {
            cerr << "AT must be 0 or greater and BT must be greater than 0.\n";
            return 1;
        }
    }

    stable_sort(processes.begin(), processes.end(), [](const Process& first, const Process& second) {
        return first.arrivalTime < second.arrivalTime;
    });

    vector<GanttEntry> ganttChart;
    int currentTime = 0;
    double totalTurnaroundTime = 0;
    double totalWaitingTime = 0;

    for (Process& process : processes) {
        if (currentTime < process.arrivalTime) {
            ganttChart.push_back({"Idle", currentTime, process.arrivalTime});
            currentTime = process.arrivalTime;
        }

        process.responseTime = currentTime - process.arrivalTime;
        process.waitingTime = process.responseTime;
        process.completionTime = currentTime + process.burstTime;
        process.turnaroundTime = process.completionTime - process.arrivalTime;

        ganttChart.push_back({"P" + to_string(process.id), currentTime, process.completionTime});
        currentTime = process.completionTime;
        totalTurnaroundTime += process.turnaroundTime;
        totalWaitingTime += process.waitingTime;
    }

    cout << "\nFCFS Scheduling Table\n";
    cout << left << setw(8) << "Process"
         << setw(8) << "AT"
         << setw(8) << "BT"
         << setw(8) << "CT"
         << setw(8) << "TAT"
         << setw(8) << "WT"
         << setw(8) << "RT" << '\n';

    for (const Process& process : processes) {
        cout << left << setw(8) << ("P" + to_string(process.id))
             << setw(8) << process.arrivalTime
             << setw(8) << process.burstTime
             << setw(8) << process.completionTime
             << setw(8) << process.turnaroundTime
             << setw(8) << process.waitingTime
             << setw(8) << process.responseTime << '\n';
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage TAT = " << totalTurnaroundTime / processCount << '\n';
    cout << "Average WT  = " << totalWaitingTime / processCount << '\n';

    cout << "\nGantt Chart\n";
    for (const GanttEntry& entry : ganttChart) {
        cout << "| " << entry.label << ' ';
    }
    cout << "|\n";

    for (const GanttEntry& entry : ganttChart) {
        cout << entry.startTime << "       ";
    }
    cout << ganttChart.back().endTime << '\n';

    return 0;
}