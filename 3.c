#include <stdio.h>
// Structure to represent a process

/*simulate the CPU scheduling algorithm - priority scheduling*/

struct Process
{
    int id;         // Process ID
    int burst_time; // Burst time
    int priority;   // Priority
};
// Function to perform Priority scheduling
void PriorityScheduling(struct Process processes[], int n)
{
    int waiting_time[n], turnaround_time[n];
    // Sort the processes based on priority (higher priority has lower value)
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (processes[j].priority > processes[j + 1].priority)
            {
                // Swap processes
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
    // Calculate waiting time and turnaround time
    waiting_time[0] = 0;
    turnaround_time[0] = processes[0].burst_time;
    for (int i = 1; i < n; i++)
    {
        waiting_time[i] = waiting_time[i - 1] + processes[i - 1].burst_time;
        turnaround_time[i] = waiting_time[i] + processes[i].burst_time;
    }
    // Print the results
    printf("Process\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].burst_time, processes[i].priority, waiting_time[i], turnaround_time[i]);
    }
}
int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process processes[n];
    printf("Enter the burst time and priority for each process:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process %d (Burst Time & Priority): ", i + 1);
        processes[i].id = i + 1;
        scanf("%d %d", &processes[i].burst_time, &processes[i].priority);
    }
    PriorityScheduling(processes, n);
    return 0;
}


/*
Enter the number of processes: 5
Enter the burst time and priority for each process:
Process 1 (Burst Time & Priority): 6 9
Process 2 (Burst Time & Priority): 6 1
Process 3 (Burst Time & Priority): 3 8
Process 4 (Burst Time & Priority): 9 2
Process 5 (Burst Time & Priority): 3 5
Process Burst Time      Priority        Waiting Time    Turnaround Time
P2      6               1               0               6
P4      9               2               6               15
P5      3               5               15              18
P3      3               8               18              21
P1      6               9               21              27
*/