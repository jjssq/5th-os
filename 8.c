#include <stdio.h>
#define MAX_MEMORY_SIZE 1000 // Maximum available memory size

/*simulate the the following contiguous memory allocation- (a) Worst Fit (b) Best Fit (c) First Fit*/

struct Block
{
    int size;
    int allocated; // 1 if allocated, 0 if free
};
struct Block memory[MAX_MEMORY_SIZE]; // Memory blocks
void initializeMemory()
{
    for (int i = 0; i < MAX_MEMORY_SIZE; i++)
    {
        memory[i].size = 0;
        memory[i].allocated = 0;
    }
}
// Function to allocate memory using Worst Fit
void worstFit(int processSize)
{
    int worstFitIdx = -1;
    int worstFitSize = -1;
    for (int i = 0; i < MAX_MEMORY_SIZE; i++)
    {
        if (!memory[i].allocated && memory[i].size >= processSize)
        {
            if (memory[i].size > worstFitSize)
            {
                worstFitSize = memory[i].size;
                worstFitIdx = i;
            }
        }
    }
    if (worstFitIdx != -1)
    {
        memory[worstFitIdx].allocated = 1;
        printf("Allocated %d units of memory at index %d (Worst Fit).\n", processSize, worstFitIdx);
    }
    else
    {
        printf("Not enough memory available for allocation (Worst Fit).\n");
    }
}
// Function to allocate memory using Best Fit
void bestFit(int processSize)
{
    int bestFitIdx = -1;
    int bestFitSize = MAX_MEMORY_SIZE + 1;
    for (int i = 0; i < MAX_MEMORY_SIZE; i++)
    {
        if (!memory[i].allocated && memory[i].size >= processSize)
        {
            if (memory[i].size < bestFitSize)
            {
                bestFitSize = memory[i].size;
                bestFitIdx = i;
            }
        }
    }
    if (bestFitIdx != -1)
    {
        memory[bestFitIdx].allocated = 1;
        printf("Allocated %d units of memory at index %d (Best Fit).\n", processSize, bestFitIdx);
    }
    else
    {
        printf("Not enough memory available for allocation (Best Fit).\n");
    }
}
// Function to allocate memory using First Fit
void firstFit(int processSize)
{
    for (int i = 0; i < MAX_MEMORY_SIZE; i++)
    {
        if (!memory[i].allocated && memory[i].size >= processSize)
        {
            memory[i].allocated = 1;
            printf("Allocated %d units of memory at index %d (First Fit).\n", processSize, i);
            return;
        }
    }
    printf("Not enough memory available for allocation (First Fit).\n");
}
int main()
{
    initializeMemory();
    // Initialize memory blocks with sizes
    memory[0].size = 200;
    memory[1].size = 300;
    memory[2].size = 100;
    memory[3].size = 150;
    memory[4].size = 250;
    int choice;
    int processSize;
    do
    {
        printf("\nMemory Allocation Algorithms:\n");
        printf("1. Worst Fit\n");
        printf("2. Best Fit\n");
        printf("3. First Fit\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice == 4)
        {
            break;
        }
        printf("Enter process size: ");
        scanf("%d", &processSize);
        switch (choice)
        {
        case 1:
            worstFit(processSize);
            break;
        case 2:
            bestFit(processSize);
            break;
        case 3:
            firstFit(processSize);
            break;
        default:
            printf("Invalid choice.\n");
            break;
        }
    } while (choice != 4);
    return 0;
}


/*
Memory Allocation Algorithms:
1. Worst Fit
2. Best Fit
3. First Fit
4. Exit
Enter your choice: 1
Enter process size: 5
Allocated 5 units of memory at index 1 (Worst Fit).

Memory Allocation Algorithms:
1. Worst Fit
2. Best Fit
3. First Fit
4. Exit
Enter your choice: 2
Enter process size: 10
Allocated 10 units of memory at index 2 (Best Fit).

Memory Allocation Algorithms:
1. Worst Fit
2. Best Fit
3. First Fit
4. Exit
Enter your choice: 3
Enter process size: 6
Allocated 6 units of memory at index 0 (First Fit).

Memory Allocation Algorithms:
1. Worst Fit
2. Best Fit
3. First Fit
4. Exit
Enter your choice: 4
*/