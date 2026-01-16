#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

class Process {
public:
int pid;
int arrivalTime;
int burstTime;
int completionTime;
int turnaroundTime;
int waitingTime;

Process(int id, int arrival, int burst) {
pid = id;
arrivalTime = arrival;
burstTime = burst;
completionTime = 0;
turnaroundTime = 0;
waitingTime = 0;
}
};

void printHeader() {
cout << "\n" << string(75, '=') << endl;
cout << "FIRST-COME-FIRST-SERVE (FCFS) SCHEDULING SIMULATION" << endl;
cout << string(75, '=') << endl;
}

void printTableHeader() {
cout << "\n" << left
<< setw(10) << "Process"
<< setw(15) << "Arrival Time"
<< setw(15) << "Burst Time"
<< setw(20) << "Completion Time"
<< setw(20) << "Turnaround Time"
<< setw(15) << "Waiting Time"
<< endl;
cout << string(95, '-') << endl;
}

void printProcess(Process &p) {
cout << left
<< setw(10) << p.pid
<< setw(15) << p.arrivalTime
<< setw(15) << p.burstTime
<< setw(20) << p.completionTime
<< setw(20) << p.turnaroundTime
<< setw(15) << p.waitingTime
<< endl;
}

void simulateFCFS(vector<Process> &processes) {
int currentTime = 0;
double totalTAT = 0;
double totalWT = 0;
int n = processes.size();

printHeader();
cout << "\nProcess execution order: ";

// Simulate FCFS scheduling
for(int i = 0; i < n; i++) {
// If CPU is idle and process hasn't arrived yet
if(currentTime < processes[i].arrivalTime) {
currentTime = processes[i].arrivalTime;
}

// Process starts execution
cout << "P" << processes[i].pid << " ";

// Calculate completion time
currentTime += processes[i].burstTime;
processes[i].completionTime = currentTime;

// Calculate turnaround time and waiting time
processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;

// Update totals
totalTAT += processes[i].turnaroundTime;
totalWT += processes[i].waitingTime;
}

// Print results table
printTableHeader();
for(int i = 0; i < n; i++) {
printProcess(processes[i]);
}

// Calculate and display averages
cout << "\n" << string(50, '=') << endl;
cout << fixed << setprecision(2);
cout << "\nAverage Turnaround Time (ATT): " << totalTAT / n << endl;
cout << "Average Waiting Time (AWT): " << totalWT / n << endl;
cout << "\nNote: All processes arrive at time 0 (FCFS with zero arrival times)" << endl;
}

int main() {
// Create processes with given burst times (all arriving at time 0)
// Process ID, Arrival Time, Burst Time
vector<Process> processes;

// Add processes with given burst times: 3,5,4,3,2,1,0,7,8,1
processes.push_back(Process(1, 0, 3));
processes.push_back(Process(2, 0, 5));
processes.push_back(Process(3, 0, 4));
processes.push_back(Process(4, 0, 3));
processes.push_back(Process(5, 0, 2));
processes.push_back(Process(6, 0, 1));
processes.push_back(Process(7, 0, 0));
processes.push_back(Process(8, 0, 7));
processes.push_back(Process(9, 0, 8));
processes.push_back(Process(10, 0, 1));

// Run FCFS simulation
simulateFCFS(processes);

// Additional simulation with different arrival times
cout << "\n\n" << string(75, '=') << endl;
cout << "FCFS SIMULATION WITH VARIABLE ARRIVAL TIMES" << endl;
cout << string(75, '=') << endl;

// Clear and create new processes with variable arrival times
processes.clear();
processes.push_back(Process(1, 0, 3));
processes.push_back(Process(2, 2, 5)); // Arrives at time 2
processes.push_back(Process(3, 4, 4)); // Arrives at time 4
processes.push_back(Process(4, 6, 3)); // Arrives at time 6
processes.push_back(Process(5, 8, 2)); // Arrives at time 8
processes.push_back(Process(6, 10, 1)); // Arrives at time 10
processes.push_back(Process(7, 12, 0)); // Arrives at time 12
processes.push_back(Process(8, 14, 7)); // Arrives at time 14
processes.push_back(Process(9, 16, 8)); // Arrives at time 16
processes.push_back(Process(10, 18, 1)); // Arrives at time 18

// Reset and run simulation with variable arrivals
vector<Process> sortedProcesses = processes;

// FCFS processes by arrival time
cout << "\nProcess execution order (by arrival time): ";
printTableHeader();

int currentTime = 0;
double totalTAT = 0;
double totalWT = 0;
int n = sortedProcesses.size();

for(int i = 0; i < n; i++) {
if(currentTime < sortedProcesses[i].arrivalTime) {
currentTime = sortedProcesses[i].arrivalTime;
}

cout << "P" << sortedProcesses[i].pid << " ";

currentTime += sortedProcesses[i].burstTime;
sortedProcesses[i].completionTime = currentTime;
sortedProcesses[i].turnaroundTime = sortedProcesses[i].completionTime - sortedProcesses[i].arrivalTime;
sortedProcesses[i].waitingTime = sortedProcesses[i].turnaroundTime - sortedProcesses[i].burstTime;

totalTAT += sortedProcesses[i].turnaroundTime;
totalWT += sortedProcesses[i].waitingTime;

printProcess(sortedProcesses[i]);
}

cout << "\n" << string(50, '=') << endl;
cout << fixed << setprecision(2);
cout << "\nAverage Turnaround Time (ATT): " << totalTAT / n << endl;
cout << "Average Waiting Time (AWT): " << totalWT / n << endl;

return 0;
}