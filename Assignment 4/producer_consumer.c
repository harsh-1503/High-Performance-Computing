#include <stdio.h>
#include <omp.h>
#define MAX_SIZE 10

int queue[MAX_SIZE];
int item_count = 0;

void produce_item(int data)
{
#pragma omp critical
    {
        queue[item_count] = data;
        item_count++;
        printf("Produced: %d\n", data);
    }
}

int consume_item()
{
    int data;
#pragma omp critical
    {
        item_count--;
        data = queue[item_count];
        printf("Consumed: %d\n", data);
    }
    return data;
}

int main()
{
    int index;
    int total_items = 20;

#pragma omp parallel
    {
#pragma omp sections
        {
#pragma omp section
            {
                for (index = 0; index < total_items; index++)
                {
                    while (item_count == MAX_SIZE)
                        ; // Wait if queue is full
                    produce_item(index);
                }
            }

#pragma omp section
            {
                for (index = 0; index < total_items; index++)
                {
                    while (item_count == 0)
                        ; // Wait if queue is empty
                    consume_item();
                }
            }
        }
    }

    return 0;
}
