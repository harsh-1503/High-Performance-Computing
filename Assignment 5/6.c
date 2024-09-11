#include <stdio.h>
#include <omp.h>

int main() {
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            for(int i = 2; i < 10; i += 2){
                printf("%d ", i);
            }
            
            printf("Thead id: ");
            printf("%d",omp_get_thread_num());
            printf("\n");
        }
        #pragma omp section
        {
            for(int i = 4; i < 20; i += 4){
                printf("%d ", i);
            }
            printf("Thead id: ");
            printf("%d",omp_get_thread_num());
            printf("\n");
        }
    }
    return 0;
}
