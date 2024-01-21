#include <stdio.h>

/*banker's algorithm for deadlock avoidance*/

// Maximum number of processes and resources
#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

// Function to check if the system is in a safe state
int isSafe(int available[], int max[][MAX_RESOURCES], int allocation[][MAX_RESOURCES], int need[][MAX_RESOURCES], int processes, int resources)
{
    int work[MAX_RESOURCES];
    int finish[MAX_PROCESSES] = {0}; // Initialize all processes as unfinished

    // Initialize the work array to available resources
    for (int i = 0; i < resources; i++)
    {
        work[i] = available[i];
    }

    int safeSequence[MAX_PROCESSES];
    int count = 0; // Count of safe processes

    while (count < processes)
    {
        int found = 0;

        for (int i = 0; i < processes; i++)
        {
            if (!finish[i])
            {
                int j;
                for (j = 0; j < resources; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        break;
                    }
                }

                if (j == resources)
                {
                    // Process i can complete its execution
                    for (int k = 0; k < resources; k++)
                    {
                        work[k] += allocation[i][k];
                    }

                    safeSequence[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (!found)
        {
            // No process found that can be executed, meaning the system is not in a safe state
            return 0;
        }
    }

    // If all processes can complete execution, the system is in a safe state
    printf("Safe Sequence: ");
    for (int i = 0; i < processes; i++)
    {
        printf("%d ", safeSequence[i]);
    }
    printf("\n");

    return 1;
}

int main()
{
    int processes, resources;
    int max[MAX_PROCESSES][MAX_RESOURCES];
    int allocation[MAX_PROCESSES][MAX_RESOURCES];
    int available[MAX_RESOURCES];
    int need[MAX_PROCESSES][MAX_RESOURCES];

    printf("Enter the number of processes: ");
    scanf("%d", &processes);

    printf("Enter the number of resources: ");
    scanf("%d", &resources);

    printf("Enter the maximum resource instances for each process:\n");
    for (int i = 0; i < processes; i++)
    {
        for (int j = 0; j < resources; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the allocated resource instances for each process:\n");
    for (int i = 0; i < processes; i++)
    {
        for (int j = 0; j < resources; j++)
        {
            scanf("%d", &allocation[i][j]);
            need[i][j] = max[i][j] - allocation[i][j]; // Calculate the need matrix
        }
    }

    printf("Enter the available resource instances:\n");
    for (int i = 0; i < resources; i++)
    {
        scanf("%d", &available[i]);
    }

    if (isSafe(available, max, allocation, need, processes, resources))
    {
        printf("System is in a safe state.\n");
    }
    else
    {
        printf("System is in an unsafe state (potential deadlock).\n");
    }

    return 0;
}

/*
Enter the number of processes: 2
Enter the number of resources: 2
Enter the maximum resource instances for each process:
1
5
6
3
Enter the allocated resource instances for each process:
3
6
4
8
Enter the available resource instances:
3
3
Safe Sequence: 0 1        
System is in a safe state.
*/