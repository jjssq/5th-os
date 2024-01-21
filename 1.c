#include <stdio.h>
/*simulate the CPU scheduling algorithm First Come First Serve (FCFS)*/

// Function to calculate waiting time and turnaround time for FCFS scheduling
void findWaitingTime(int n, int bt[], int wt[])
{
    wt[0] = 0; // Waiting time for the first process is always 0
    // Calculate waiting time for each process
    for (int i = 1; i < n; i++)
    {
        wt[i] = wt[i - 1] + bt[i - 1];
    }
}
void findTurnaroundTime(int n, int bt[], int wt[], int tat[])
{
    // Calculate turnaround time for each process
    for (int i = 0; i < n; i++)
    {
        tat[i] = bt[i] + wt[i];
    }
}
void findAverageTime(int n, int bt[])
{
    int wt[n], tat[n];
    // Calculate waiting time and turnaround time
    findWaitingTime(n, bt, wt);
    findTurnaroundTime(n, bt, wt, tat);
    // Calculate average waiting time and average turnaround time
    float total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++)
    {
        total_wt += wt[i];
        total_tat += tat[i];
    }
    float avg_wt = total_wt / n;
    float avg_tat = total_tat / n;
    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t\t%d\t\t%d\n", i + 1, bt[i], wt[i], tat[i]);
    }
    printf("Average Waiting Time: %.2f\n", avg_wt);
    printf("Average Turnaround Time: %.2f\n", avg_tat);
}
int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int burst_time[n];
    printf("Enter the burst time for each process:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
    }
    findAverageTime(n, burst_time);
    return 0;
}

/**
Enter the number of processes: 5
Enter the burst time for each process:
Process 1: 9
Process 2: 7
Process 3: 8
Process 4: 6
Process 5: 5
Process Burst Time      Waiting Time    Turnaround Time
P1      9               0               9
P2      7               9               16
P3      8               16              24
P4      6               24              30
P5      5               30              35
Average Waiting Time: 15.80
Average Turnaround Time: 22.80
*/