#include <stdio.h>
#include <stdlib.h>

/* implement page replacement techniques - (a) First in First Out (b) Least Recently Used (c) Optimal*/

#define MAX_FRAMES 3 // Maximum number of frames in memory

// Function to find the index of the page that will be replaced in the future (Optimal Algorithm)
int findOptimalReplacement(int pages[], int frames[], int n, int current)
{
    int index = -1, farthest = -1;
    for (int i = 0; i < MAX_FRAMES; i++)
    {
        int j;
        for (j = current + 1; j < n; j++)
        {
            if (frames[i] == pages[j])
            {
                if (j > farthest)
                {
                    farthest = j;
                    index = i;
                }
                break;
            }
        }
        if (j == n)
            return i;
    }
    return (index == -1) ? 0 : index;
}

// Function to simulate the FIFO page replacement algorithm
void fifoPageReplacement(int pages[], int n)
{
    int frames[MAX_FRAMES];
    int front = 0, rear = -1;
    int pageFaults = 0;

    for (int i = 0; i < MAX_FRAMES; i++)
    {
        frames[i] = -1; // Initialize frames as empty
    }

    for (int i = 0; i < n; i++)
    {
        int currentPage = pages[i];
        int isPageInFrames = 0;

        // Check if the current page is already in frames
        for (int j = 0; j < MAX_FRAMES; j++)
        {
            if (frames[j] == currentPage)
            {
                isPageInFrames = 1;
                break;
            }
        }

        // If the page is not in frames, replace the page at the front and add the new page
        if (!isPageInFrames)
        {
            pageFaults++;
            rear = (rear + 1) % MAX_FRAMES;
            frames[rear] = currentPage;
        }
    }

    printf("FIFO Page Replacement Algorithm:\n");
    printf("Total Page Faults: %d\n", pageFaults);
}

// Function to simulate the LRU page replacement algorithm
void lruPageReplacement(int pages[], int n)
{
    int frames[MAX_FRAMES];
    int pageFaults = 0;

    for (int i = 0; i < MAX_FRAMES; i++)
    {
        frames[i] = -1; // Initialize frames as empty
    }

    for (int i = 0; i < n; i++)
    {
        int currentPage = pages[i];
        int isPageInFrames = 0;

        // Check if the current page is already in frames
        for (int j = 0; j < MAX_FRAMES; j++)
        {
            if (frames[j] == currentPage)
            {
                isPageInFrames = 1;

                // Move the current page to the front (most recently used)
                for (int k = j; k > 0; k--)
                {
                    frames[k] = frames[k - 1];
                }
                frames[0] = currentPage;
                break;
            }
        }

        // If the page is not in frames, replace the least recently used page
        if (!isPageInFrames)
        {
            pageFaults++;

            for (int j = MAX_FRAMES - 1; j > 0; j--)
            {
                frames[j] = frames[j - 1];
            }
            frames[0] = currentPage;
        }
    }

    printf("LRU Page Replacement Algorithm:\n");
    printf("Total Page Faults: %d\n", pageFaults);
}

// Function to simulate the Optimal page replacement algorithm
void optimalPageReplacement(int pages[], int n)
{
    int frames[MAX_FRAMES];
    int pageFaults = 0;

    for (int i = 0; i < MAX_FRAMES; i++)
    {
        frames[i] = -1; // Initialize frames as empty
    }

    for (int i = 0; i < n; i++)
    {
        int currentPage = pages[i];
        int isPageInFrames = 0;

        // Check if the current page is already in frames
        for (int j = 0; j < MAX_FRAMES; j++)
        {
            if (frames[j] == currentPage)
            {
                isPageInFrames = 1;
                break;
            }
        }

        // If the page is not in frames, find the page to replace using the Optimal Algorithm
        if (!isPageInFrames)
        {
            pageFaults++;
            int replaceIndex = findOptimalReplacement(pages, frames, n, i);
            frames[replaceIndex] = currentPage;
        }
    }

    printf("Optimal Page Replacement Algorithm:\n");
    printf("Total Page Faults: %d\n", pageFaults);
}

int main()
{
    int n, pages[MAX_FRAMES];

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    printf("Enter the page sequence: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &pages[i]);
    }

    fifoPageReplacement(pages, n);
    lruPageReplacement(pages, n);
    optimalPageReplacement(pages, n);

    return 0;
}