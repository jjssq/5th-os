#include <stdio.h>
#include <stdlib.h>

/*simulate Reader-Writers problem using semaphores*/

// Initialize a mutex to 1
int mutex = 1;

// Number of full slots as 0
int full = 0;

// Number of empty slots as size of buffer
int empty = 10, x = 0;

// Function to produce an item and add it to the buffer
void Writer()
{
    // Decrease mutex value by 1
    --mutex;

    // Check if there is an empty slot in the buffer
    if (empty != 0)
    {
        // Increase the number of full slots by 1
        ++full;

        // Decrease the number of empty slots by 1
        --empty;

        // Item produced
        x++;
        printf("\nWriter produces item %d", x);
    }
    else
    {
        printf("\nBuffer is full!");
    }

    // Increase mutex value by 1
    ++mutex;
}

// Function to consume an item and remove it from buffer
void Reader()
{
    // Decrease mutex value by 1
    --mutex;

    // Check if there is a filled slot in the buffer
    if (full != 0)
    {
        // Decrease the number of full slots by 1
        --full;

        // Increase the number of empty slots by 1
        ++empty;

        printf("\nReader consumes item %d", x);
        x--;
    }
    else
    {
        printf("\nBuffer is empty!");
    }

    // Increase mutex value by 1
    ++mutex;
}

// Driver Code
int main()
{
    int n, i;

    printf("\n1. Press 1 for Writer\n2. Press 2 for Reader\n3. Press 3 for Exit");

// Using '#pragma omp parallel for' can give wrong value due to synchronization issues.
// 'critical' specifies that the code is executed by only one thread at a time, i.e., only one thread enters
// the critical section at a given time
#pragma omp parallel for
    for (i = 1; i > 0; i++)
    {
        printf("\nEnter your choice:");
        scanf("%d", &n);

        // Switch Cases
        switch (n)
        {
        case 1:
            // If mutex is 1 and empty is non-zero, then it is possible to produce
            if ((mutex == 1) && (empty != 0))
            {
                Writer();
            }
            else
            {
                printf("Buffer is full!");
            }
            break;

        case 2:
            // If mutex is 1 and full is non-zero, then it is possible to consume
            if ((mutex == 1) && (full != 0))
            {
                Reader();
            }
            else
            {
                printf("Buffer is empty!");
            }
            break;

        // Exit Condition
        case 3:
            exit(0);
            break;
        }
    }

    return 0;
}


/*
1. Press 1 for Writer
2. Press 2 for Reader
3. Press 3 for Exit  
Enter your choice:2  
Buffer is empty!  
Enter your choice:1

Writer produces item 1
Enter your choice:1   

Writer produces item 2
Enter your choice:2   

Reader consumes item 2
Enter your choice:1   

Writer produces item 2
Enter your choice:2   

Reader consumes item 2
Enter your choice:2   

Reader consumes item 1
Enter your choice:2
Buffer is empty!
Enter your choice:3
*/