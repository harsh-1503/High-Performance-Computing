#include <stdio.h>
#include <omp.h>

// 1.Write an OpenMP program such that, it should print the name of your family members, such that the names should come from different threads/cores. Also print the respective job id.
int main()
{
    const char *family_members[] = {"Harsh", "Payal", "Mitali", "Mahi"};
    int num_members = sizeof(family_members) / sizeof(family_members[0]);

#pragma omp parallel for
    for (int i = 0; i < num_members; i++)
    {
        int thread_id = omp_get_thread_num();
        printf("Thread %d: %s\n", thread_id, family_members[i]);
    }

    return 0;
}
