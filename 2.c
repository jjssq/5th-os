#include <stdio.h>
#include <stdbool.h>
#include <limits.h> // Include the <limits.h> header for INT_MAX

/*simulate the CPU scheduling algorithm Shortest Job First (SJF)*/

// Structure to represent a process
struct Process
{
    int id;         // Process ID
    int burst_time; // Burst time
};
// Function to perform non-preemptive SJF scheduling
void SJF(struct Process processes[], int n)
{
    int waiting_time[n], turnaround_time[n];
    bool completed[n];
    for (int i = 0; i < n; i++)
    {
        completed[i] = false;
    }
    int total_time = 0;      // Total time elapsed
    int completed_count = 0; // Number of completed processes
    while (completed_count < n)
    {
        int shortest_index = -1;
        int shortest_burst = INT_MAX;
        // Find the process with the shortest burst time that has not completed yet
        for (int i = 0; i < n; i++)
        {
            if (!completed[i] && processes[i].burst_time < shortest_burst)
            {
                shortest_burst = processes[i].burst_time;
                shortest_index = i;
            }
        }
        if (shortest_index == -1)
        {
            // No eligible process found, increment the total time
            total_time++;
        }
        else
        {
            // Execute the shortest job
            waiting_time[shortest_index] = total_time;
            total_time += processes[shortest_index].burst_time;
            turnaround_time[shortest_index] = total_time;
            completed[shortest_index] = true;
            completed_count++;
        }
    }
    // Print the results
    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].burst_time, waiting_time[i], turnaround_time[i]);
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
    SJF(processes, n);
    return 0;
}

/*
Enter the number of processes: 5
Enter the burst time for each process:
Process 1: 9
Process 2: 7
Process 3: 8
Process 4: 1
Process 5: 3
Process Burst Time      Waiting Time    Turnaround Time
P1      9               19              28
P2      7               4               11
P3      8               11              19
P4      1               0               1
P5      3               1               4
*/