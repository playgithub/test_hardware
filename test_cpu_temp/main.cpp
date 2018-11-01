#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <pthread.h>
#include <sys/sysinfo.h>
 
#include "get_cpu_temp/get_cpu_temp.h"

void print_usage(const char * app_name, int cpu_core_count);
void * thread_func(void * arg);

int main(int argc, const char * argv[]) 
{
    int cpu_core_count = get_nprocs();
    if (cpu_core_count <= 0)
    {
        fprintf(stderr, "get cpu core count FAILED");
        return -1;
    }

    if (argc > 2)
    {
        print_usage(argv[0], cpu_core_count);
        return -1;
    }

    int thread_count = cpu_core_count;

    if (argc == 2)
    {
        thread_count = atoi(argv[1]);
        if (thread_count <= 0 || thread_count > cpu_core_count)
        {
            print_usage(argv[0], cpu_core_count);
            return -1;
        }
    }

    pthread_t * threads = new pthread_t[thread_count];
    for (int i = 0; i < thread_count; ++i)
    {
        int n = pthread_create(threads+i, nullptr, &thread_func, nullptr);
        if (n != 0)
        {
            fprintf(stderr, "pthread_create FAILED");
            return -1;
        }
    }

    while (true)
    {
        double temp;
        bool ok = get_cpu_temp(temp);
        if (ok)
        {
            printf("threads: %d temp: %.2f\n", thread_count, temp);
            if (temp > 80.0)
            {
                printf("The CPU is too hot!\n");
                break;
            }
            sleep(1);
        }
        else
        {
            fprintf(stderr, "output_temp FAILED");
            break;
        }
    }

    delete []threads;

    return 0;
}

void print_usage(const char * app_name, int cpu_core_count)
{
    printf("\nUSAGE:\n%s thread_count\nthread_count: [1, %d]\n\n", app_name, cpu_core_count);
}

void * thread_func(void * arg)
{
    while (true);
}

