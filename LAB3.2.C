#include <stdio.h>
#include <stdlib.h>

int main()
{
     int bt[20], wt[20], tat[20], priority[20], i, n, temp;
    float wtavg = 0, tatavg = 0;
  
     printf("\nEnter the number of processes -- ");
    scanf("%d", &n);
    for(i=0; i<n; i++)
    {
        printf("\nEnter Burst Time for Process %d -- ", i);
        scanf("%d", &bt[i]);
        printf("Enter Priority for Process %d (lower number = higher priority) -- ", i);
        scanf("%d", &priority[i]);
    }
    
    // Sort processes by priority (non-preemptive: higher priority first)
    // Assuming lower priority number means higher priority
    for(i=0; i<n-1; i++)
    {
        for(int j=i+1; j<n; j++)
        {
            if(priority[i] > priority[j])
            {
                // Swap burst times
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;
                // Swap priorities
                temp = priority[i];
                priority[i] = priority[j];
                priority[j] = temp;
            }
        }
    }
    
    // Calculate waiting and turnaround times
    wt[0] = 0; // First process waits 0
    tat[0] = bt[0];
    for(i=1; i<n; i++)
    {
        wt[i] = wt[i-1] + bt[i-1];
        tat[i] = tat[i-1] + bt[i];
        wtavg += wt[i];
        tatavg += tat[i];
    }
    wtavg += wt[0]; // Add first process
    tatavg += tat[0];
    
    printf("\t PROCESS \tBURST TIME \t PRIORITY \t WAITING TIME\t TURNAROUND TIME\n");
    for(i=0; i<n; i++)
        printf("\n\t P%d \t\t %d \t\t %d \t\t %d \t\t %d", i, bt[i], priority[i], wt[i], tat[i]);
    printf("\nAverage Waiting Time -- %f", wtavg/n);
    printf("\nAverage Turnaround Time -- %f", tatavg/n);
   return 0;
}