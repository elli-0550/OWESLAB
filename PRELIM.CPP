#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;

// Process structure to hold process information
struct Process {
    int PID, AT, BT, RT, CT, TT, WT;
    Process(int pid, int at, int bt) 
        : PID(pid), AT(at), BT(bt), RT(bt), CT(0), TT(0), WT(0) {}
};

// TimeQuantum class for calculating appropriate time quantum
class RecommendedTimeQuantum {
public:
    // Calculate quantum based on MEDIAN of burst times
    static int calculateQuantumByMedian(const vector<Process>& processes) {
        if (processes.empty()) return 2;
        
        // Create a copy of burst times and sort them
        vector<int> burstTimes;
        for (const auto& p : processes) {
            burstTimes.push_back(p.BT);
        }
        sort(burstTimes.begin(), burstTimes.end());
        
        int median;
        int size = burstTimes.size();
        
        // If odd number of elements, return middle element
        // If even number of elements, return average of two middle elements
        if (size % 2 == 1) {
            median = burstTimes[size / 2];
        } else {
            median = (burstTimes[size / 2 - 1] + burstTimes[size / 2]) / 2;
        }
        
        return max(2, median);
    }
    
    // Calculate quantum based on average burst time (legacy method)
    static int calculateQuantum(const vector<Process>& processes) {
       
    }
    
    // Calculate quantum based on maximum burst time
    static int calculateQuantumMax(const vector<Process>& processes) {
        if (processes.empty()) return 2;
        
        int maxBurstTime = 0;
        for (const auto& p : processes) {
            maxBurstTime = max(maxBurstTime, p.BT);
        }
        return max(2, maxBurstTime / 2);
    }
};

// Round Robin Scheduling Algorithm
class RoundRobin {
private:
    vector<Process> processes;
    int RecommendedTimeQuantum;
    
public:
    RoundRobin(vector<Process> procs, int quantum) 
        : processes(procs), RecommendedTimeQuantum(quantum) {}
    void execute() {
        queue<int> readyQueue;
        int currentTime = 0;
        int completed = 0;
        
        // Create process pointers
        vector<Process> processCopy = processes;
        vector<bool> inQueue(processCopy.size(), false);
        
        cout << "\n===== ROUND ROBIN SCHEDULING =====" << endl;
        cout << "Time Quantum: " << RecommendedTimeQuantum << endl;
        
        while (completed < (int)processCopy.size()) {
            // Add processes that have arrived
            for (int i = 0; i < (int)processCopy.size(); i++) {
                if (processCopy[i].AT <= currentTime && processCopy[i].RT > 0 && !inQueue[i]) {
                    readyQueue.push(i);
                    inQueue[i] = true;
                }
            }
            
            if (readyQueue.empty()) {
                currentTime++;
                continue;
            }
            
            int idx = readyQueue.front();
            readyQueue.pop();
            inQueue[idx] = false;
            
            int executionTime = min(RecommendedTimeQuantum, processCopy[idx].RT);
            currentTime += executionTime;
            processCopy[idx].RT -= executionTime;
            
            if (processCopy[idx].RT > 0) {
                readyQueue.push(idx);
                inQueue[idx] = true;
            } else {
                processCopy[idx].CT = currentTime;
                completed++;
            }
        }
        
        calculateMetrics(processCopy);
        displayResults(processCopy);
    }
    
private:
    void calculateMetrics(vector<Process>& procs) {
        for (auto& p : procs) {
            p.TT = p.CT - p.AT;
            p.WT = p.TT - p.BT;
        }
    }
    
    void displayResults(const vector<Process>& procs) {
        cout << "\nProcess Results:" << endl;
        cout << "PID\tAT\tBT\tCT\tTAT\tWT" << endl;
        float avgTAT = 0, avgWT = 0;
        
        for (const auto& p : procs) {
            cout << p.PID << "\t" << p.AT << "\t" << p.BT
                 << "\t" << p.CT << "\t" << p.TT 
                 << "\t" << p.WT << endl;
            avgTAT += p.TT;
            avgWT += p.WT;
        }
        
        cout << "\nAverage Turnaround Time: " << avgTAT / procs.size() << endl;
        cout << "Average Waiting Time: " << avgWT / procs.size() << endl;
    }
};

// Shortest Job First Scheduling Algorithm
class ShortestJobFirst {
private:
    vector<Process> processes;
    
public:
    ShortestJobFirst(vector<Process> procs) : processes(procs) {}
    
    void execute() {
        int currentTime = 0;
        vector<bool> completed(processes.size(), false);
        int completedCount = 0;
        
        cout << "\n===== SHORTEST JOB FIRST SCHEDULING =====" << endl;
        
        while (completedCount < (int)processes.size()) {
            int nextProcess = -1;
            int minBurstTime = INT_MAX;
            
            // Find the process with minimum burst time among available processes
            for (int i = 0; i < (int)processes.size(); i++) {
                if (!completed[i] && processes[i].AT <= currentTime) {
                    if (processes[i].BT < minBurstTime) {
                        minBurstTime = processes[i].BT;
                        nextProcess = i;
                    }
                }
            }
            
            if (nextProcess == -1) {
                currentTime++;
                continue;
            }
            
            Process& p = processes[nextProcess];
            currentTime += p.BT;
            p.CT = currentTime;
            completed[nextProcess] = true;
            completedCount++;
        }
        
        calculateMetrics();
        displayResults();
    }
    
private:
    void calculateMetrics() {
        for (auto& p : processes) {
            p.TT = p.CT - p.AT;
            p.WT = p.TT - p.BT;
        }
    }
    
    void displayResults() {
        cout << "\nProcess Results:" << endl;
        cout << "PID\tAT\tBT\tCT\tTAT\tWT" << endl;
        float avgTAT = 0, avgWT = 0;
        
        for (const auto& p : processes) {
            cout << p.PID << "\t" << p.AT << "\t" << p.BT
                 << "\t" << p.CT << "\t" << p.TT 
                 << "\t" << p.WT << endl;
            avgTAT += p.TT;
            avgWT += p.WT;
        }
        
        cout << "\nAverage Turnaround Time: " << avgTAT / processes.size() << endl;
        cout << "Average Waiting Time: " << avgWT / processes.size() << endl;
    }
};

// Shortest Remaining Time First Scheduling Algorithm
class ShortestRemainingTimeFirst {
private:
    vector<Process> processes;
    
public:
    ShortestRemainingTimeFirst(vector<Process> procs) : processes(procs) {}
    
    void execute() {
        int currentTime = 0;
        int completed = 0;
        
        cout << "\n===== SHORTEST REMAINING TIME FIRST SCHEDULING =====" << endl;
        
        while (completed < (int)processes.size()) {
            int nextProcess = -1;
            int minRemainingTime = INT_MAX;
            
            // Find the process with minimum remaining time among available processes
            for (int i = 0; i < (int)processes.size(); i++) {
                if (processes[i].RT > 0 && 
                    processes[i].AT <= currentTime) {
                    if (processes[i].RT < minRemainingTime) {
                        minRemainingTime = processes[i].RT;
                        nextProcess = i;
                    }
                }
            }
            
            if (nextProcess == -1) {
                currentTime++;
                continue;
            }
            
            Process& p = processes[nextProcess];
            p.RT--;
            currentTime++;
            
            if (p.RT == 0) {
                p.CT = currentTime;
                completed++;
            }
        }
        
        calculateMetrics();
        displayResults();
    }
    
private:
    void calculateMetrics() {
        for (auto& p : processes) {
            p.TT = p.CT - p.AT;
            p.WT = p.TT - p.BT;
        }
    }
    
    void displayResults() {
        cout << "\nProcess Results:" << endl;
        cout << "PID\tAT\tBT\tCT\tTAT\tWT" << endl;
        float avgTAT = 0, avgWT = 0;
        
        for (const auto& p : processes) {
            cout << p.PID << "\t" << p.AT << "\t" << p.BT
                 << "\t" << p.CT << "\t" << p.TT 
                 << "\t" << p.WT << endl;
            avgTAT += p.TT;
            avgWT += p.WT;
        }
        
        cout << "\nAverage Turnaround Time: " << avgTAT / processes.size() << endl;
        cout << "Average Waiting Time: " << avgWT / processes.size() << endl;
    }
};

int main() {
    // Create processes with predefined arrival time and burst time
    vector<Process> processes = {
        Process(1, 4, 53),
        Process(2, 2, 43),
        Process(3, 3, 18),
        Process(4, 6, 16),
        Process(5, 1, 44),
        Process(6, 5, 73),
        Process(7, 8, 99),
        Process(8, 7, 27),
    };

    // Calculate time quantum using RecommendedTimeQuantum class - using median
    int quantum = RecommendedTimeQuantum::calculateQuantumByMedian(processes);
    
    cout << "========== CPU SCHEDULING ALGORITHMS ==========" << endl;
    cout << "Processes Information:" << endl;
    cout << "ID\tArrival Time\tBurst Time" << endl;
    for (const auto& p : processes) {
        cout << "P" << p.PID << "\t" << p.AT << "\t\t" << p.BT << endl;
    }
    
    // Execute Round Robin
    RoundRobin rr(processes, quantum);
    rr.execute();
    
    // Reset remaining time for next algorithm
    for (auto& p : processes) {
        p.RT = p.BT;
    }
    
    // Execute Shortest Job First
    ShortestJobFirst sjf(processes);
    sjf.execute();
    
    // Reset remaining time for next algorithm
    for (auto& p : processes) {
        p.RT = p.BT;
    }
    
    // Execute Shortest Remaining Time First
    ShortestRemainingTimeFirst srtf(processes);
    srtf.execute();
    
    return 0;
}

