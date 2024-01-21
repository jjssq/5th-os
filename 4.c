#include <stdio.h>
#include <stdbool.h>
// Structure to represent a process

/*simulate the CPU scheduling algorithm Round Robin (RR)*/

struct Process
{
    int id;             // Process ID
    int burst_time;     // Burst time
    int remaining_time; // Remaining burst time
};
// Function to perform Round Robin scheduling
void RoundRobin(struct Process processes[], int n, int time_quantum)
{
    int remaining_processes = n;
    int current_time = 0;
    // Create an array to store waiting times for each process
    int waiting_time[n];
    for (int i = 0; i < n; i++)
    {
        waiting_time[i] = 0;
        processes[i].remaining_time = processes[i].burst_time;
    }
    while (remaining_processes > 0)
    {
        for (int i = 0; i < n; i++)
        {
            if (processes[i].remaining_time > 0)
            {
                // Execute the process for the time quantum or its remaining time, whichever is smaller
                int execution_time = (processes[i].remaining_time < time_quantum) ? processes[i].remaining_time : time_quantum;
                // Update the remaining time for the process
                processes[i].remaining_time -= execution_time;
                // Update current time
                current_time += execution_time;
                // Update waiting time for the process
                waiting_time[i] += current_time;
                if (processes[i].remaining_time == 0)
                {
                    remaining_processes--;
                }
            }
        }
    }
    // Calculate turnaround time and print results
    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        int turnaround_time = waiting_time[i] + processes[i].burst_time;
        printf("P%d\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].burst_time, waiting_time[i], turnaround_time);
    }
}
int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process processes[n];
    printf("Enter the burst time for each process:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process %d: ", i + 1);
        processes[i].id = i + 1;
        scanf("%d", &processes[i].burst_time);
    }
    int time_quantum;
    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);
    RoundRobin(processes, n, time_quantum);
    return 0;
}

/*
Enter the number of processes: 5
Enter the burst time for each process:
Process 1: 9
Process 2: 4
Process 3: 4
Process 4: 9
Process 5: 5
Enter the time quantum: 3
Process Burst Time      Waiting Time    Turnaround Time
P1      9               49              58
P2      4               25              29
P3      4               29              33
P4      9               66              75
P5      5               40              45
*/