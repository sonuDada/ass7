#include <stdio.h>
void FCFS(int pages[], int n, int fsize)
{
    int frame[fsize];
    int miss = 0;
    int hit = 0;
    int current = 0;
    for (int i = 0; i < fsize; i++)
    {
        frame[i] = -1;
    }
    for (int i = 0; i < n; i++)
    {
        int flag = 0;
        for (int j = 0; j < fsize; j++)
        {
            if (pages[i] == frame[j])
            {
                flag = 1;
                hit++;
                break;
            }
        }
        if (flag == 1)
        {
            continue;
        }
        frame[current] = pages[i];
        miss++;
        current = (current + 1) % fsize;
    }
    printf("Miss : %d\nHit : %d\n", miss, hit);
}
void Optimal(int pages[], int n, int fsize)
{
    int frame[fsize];
    int miss = 0;
    int hit = 0;
    int last_occurance_index = fsize;
    int current = 0;
    for (int i = 0; i < fsize; i++)
    {
        frame[i] = -1;
    }
    for (int i = 0; i < n; i++)
    {
        int flag = 0;
        for (int j = 0; j < fsize; j++)
        {
            if (pages[i] == frame[j])
            {
                hit++;
                flag = 1;
                break;
            }
        }
        if (flag == 1)
            continue;
        if (frame[current] == -1)
        {
            miss++;
            frame[current] = pages[i];
            current = (current + 1) % fsize;
            continue;
        }
        int prev = -1;
        for (int j = 0; j < fsize; j++)
        {
            int temp = 999;
            for (int k = i; k < n; k++)
            {
                if (frame[j] == pages[k])
                {
                    temp = k;
                    break;
                }
            }
            if (temp == 999)
            {
                last_occurance_index = j;
                break;
            }
            else if (temp > prev)
            {
                last_occurance_index = j;
                prev = temp;
            }
        }
        frame[last_occurance_index] = pages[i];
        miss++;
    }
    printf("Miss: %d\nHit: %d\n", miss, hit);
}
void LRU(int pages[], int n, int fsize)
{
    int frame[fsize];
    int oldest_page_index;
    int hit = 0;
    int miss = 0;
    int current = 0;
    for (int i = 0; i < fsize; i++)
        frame[i] = -1;
    for (int i = 0; i < n; i++)
    {
        int flag = 0;
        for (int j = 0; j < fsize; j++)
        {
            if (frame[j] == pages[i])
            {
                flag = 1;
                hit++;
                break;
            }
        }
        if (flag == 1)
            continue;
        if (frame[current] == -1)
        {
            miss++;
            frame[current] = pages[i];
            current = (current + 1) % fsize;
        }
        else
        {
            int prev = 999;
            for (int j = 0; j < fsize; j++)
            {
                int temp = -1;
                for (int k = i; k >= 0; k--)
                {
                    if (frame[j] == pages[k])
                    {
                        temp = k;
                        break;
                    }
                }
                if (temp == -1)
                {
                    oldest_page_index = j;
                    break;
                }
                if (temp < prev)
                {
                    prev = temp;
                    oldest_page_index = j;
                }
            }
            frame[oldest_page_index] = pages[i];
            miss++;
        }
    }
    printf("Miss: %d\nHit: %d\n", miss, hit);
}
int main()
{
    int n, fsize;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter frame size : ");
    scanf("%d", &fsize);
    int pages[n];
    printf("Enter page sizes : ");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);
    FCFS(pages,n,fsize);
    // Optimal(pages,n,fsize);
    // LRU(pages, n, fsize);
    return 0;
}
