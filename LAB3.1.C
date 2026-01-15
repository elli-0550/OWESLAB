#include <stdio.h>
#include <stdlib.h>

int main()
{
    int bt[20], wt[20], tat[20], i, n, quantum, remaining[20];
    float wtavg = 0, tatavg = 0;
  
    printf("\nEnter the number of processes -- ");
    scanf("%d", &n);
    for(i=0; i<n; i++)
    {
        printf("\nEnter Burst Time for Process %d -- ", i);
        scanf("%d", &bt[i]);
        remaining[i] = bt[i]; // Copy burst times to remaining array
    }
    printf("\nEnter Time Quantum -- ");
    scanf("%d", &quantum);
    
    // Simulate Round Robin Scheduling
    int time = 0; // Current time
    int done = 0; // Number of processes completed
    while(done < n)
    {
        for(i=0; i<n; i++)
        {
            if(remaining[i] > 0)
            {
                if(remaining[i] > quantum)
                {
                    time += quantum;
                    remaining[i] -= quantum;
                }
                else
                {
                    time += remaining[i];
                    wt[i] = time - bt[i]; // Waiting time = Completion time - Burst time
                    remaining[i] = 0;
                    done++;
                }
            }
        }
    }
    
    // Calculate Turnaround Time and averages
    for(i=0; i<n; i++)
    {
        tat[i] = bt[i] + wt[i];
        wtavg += wt[i];
        tatavg += tat[i];
    }
    
    printf("\t PROCESS \tBURST TIME \t WAITING TIME\t TURNAROUND TIME\n");
    for(i=0; i<n; i++)
        printf("\n\t P%d \t\t %d \t\t %d \t\t %d", i, bt[i], wt[i], tat[i]);
    printf("\nAverage Waiting Time -- %f", wtavg/n);
    printf("\nAverage Turnaround Time -- %f", tatavg/n);
   return 0;
}