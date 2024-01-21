#include <stdio.h>
#include <stdlib.h>

/*simulate all file allocation strategies - (a) Sequential (b) Indexed (c) Linked*/

#define MAX_BLOCKS 1000 // Maximum number of blocks

// Structure for block in linked allocation
struct LinkedBlock
{
    int data;
    struct LinkedBlock *next;
};

// Function to simulate sequential file allocation
void sequentialFileAllocation(int blocks[], int n, int fileSize)
{
    int startBlock = -1;
    for (int i = 0; i < n; i++)
    {
        if (blocks[i] == 0)
        { // Check if the block is free
            if (startBlock == -1)
            {
                startBlock = i;
            }
            fileSize--;
            blocks[i] = 1; // Allocate the block
            if (fileSize == 0)
            {
                break;
            }
        }
    }
    if (fileSize == 0)
    {
        printf("Sequential File Allocation: File allocated from block %d to block %d.\n", startBlock, startBlock + fileSize);
    }
    else
    {
        printf("Sequential File Allocation: Not enough contiguous space available.\n");
    }
}

// Function to simulate indexed file allocation
void indexedFileAllocation(int blocks[], int n, int indexBlock, int fileSize)
{
    if (blocks[indexBlock] == 0)
    {                           // Check if the index block is free
        blocks[indexBlock] = 1; // Allocate the index block
        int allocatedBlocks[fileSize];
        for (int i = 0; i < fileSize; i++)
        {
            allocatedBlocks[i] = -1; // Initialize allocated blocks to -1
        }
        for (int i = 0; i < fileSize; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (blocks[j] == 0)
                {                           // Check if the block is free
                    blocks[j] = 1;          // Allocate the block
                    allocatedBlocks[i] = j; // Store the allocated block
                    break;
                }
            }
        }
        printf("Indexed File Allocation: File allocated with index block %d and data blocks: ", indexBlock);
        for (int i = 0; i < fileSize; i++)
        {
            if (allocatedBlocks[i] != -1)
            {
                printf("%d ", allocatedBlocks[i]);
            }
        }
        printf("\n");
    }
    else
    {
        printf("Indexed File Allocation: Index block is already allocated.\n");
    }
}

// Function to simulate linked file allocation
void linkedFileAllocation(struct LinkedBlock *blocks[], int n, int fileSize)
{
    struct LinkedBlock *startBlock = NULL;
    struct LinkedBlock *currentBlock = NULL;
    for (int i = 0; i < n; i++)
    {
        if (blocks[i] == NULL)
        { // Check if the block is free
            if (startBlock == NULL)
            {
                startBlock = (struct LinkedBlock *)malloc(sizeof(struct LinkedBlock));
                currentBlock = startBlock;
            }
            else
            {
                currentBlock->next = (struct LinkedBlock *)malloc(sizeof(struct LinkedBlock));
                currentBlock = currentBlock->next;
            }
            currentBlock->data = i;
            currentBlock->next = NULL;
            fileSize--;
            if (fileSize == 0)
            {
                break;
            }
        }
    }
    if (fileSize == 0)
    {
        printf("Linked File Allocation: File allocated with blocks: ");
        currentBlock = startBlock;
        while (currentBlock != NULL)
        {
            printf("%d ", currentBlock->data);
            currentBlock = currentBlock->next;
        }
        printf("\n");
    }
    else
    {
        printf("Linked File Allocation: Not enough blocks available.\n");
    }
}

int main()
{
    int blocks[MAX_BLOCKS] = {0}; // Initialize blocks as free
    int n;                        // Total number of blocks
    int fileSize;                 // Size of the file to be allocated
    int indexBlock;               // Index block for indexed allocation

    printf("Enter the total number of blocks: ");
    scanf("%d", &n);

    printf("Enter the size of the file to be allocated: ");
    scanf("%d", &fileSize);

    printf("Enter the index block for indexed allocation (0-%d): ", n - 1);
    scanf("%d", &indexBlock);

    if (n <= 0 || fileSize <= 0 || indexBlock < 0 || indexBlock >= n)
    {
        printf("Invalid input.\n");
        return 1;
    }

    sequentialFileAllocation(blocks, n, fileSize);
    indexedFileAllocation(blocks, n, indexBlock, fileSize);

    // Linked allocation requires an array of pointers to linked blocks
    struct LinkedBlock *linkedBlocks[MAX_BLOCKS] = {NULL};
    linkedFileAllocation(linkedBlocks, n, fileSize);

    return 0;
}


/*
Enter the total number of blocks: 10
Enter the size of the file to be allocated: 5
Enter the index block for indexed allocation (0-9): 2
Sequential File Allocation: File allocated from block 0 to block 0.
Indexed File Allocation: Index block is already allocated.
Linked File Allocation: File allocated with blocks: 0 1 2 3 4
*/