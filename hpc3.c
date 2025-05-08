#include<stdio.h>
#include<omp.h>
int main()
{
    omp_set_num_threads(4);
    double arr[10]={1,2,3,4,5,6,7,8,9,10};
    double max_v=0.0;
    double min_v=100.0;
    float avg=0.0,sum=0.0,sum_val=0.0;
    int i;

    #pragma omp parallel for reduction(min:min_v)
    for (i=0;i<10;i++)
    {
        printf("Thread_id=%d and i=%d\n",omp_get_thread_num(),i);
        if( arr[i]<min_v)
            min_v=arr[i];
    }
    printf("min_value=%f",min_v);
    printf("\n");

    #pragma omp parallel for reduction(max:max_v)
    for (i=0;i<10;i++)
    {
        printf("Thread_id=%d and i=%d\n",omp_get_thread_num(),i);
        if( arr[i]>max_v)
            max_v=arr[i];
    }
    printf("max_value=%f",max_v);
    printf("\n");

    #pragma omp parallel for reduction(+:sum_val)
    for (i=0;i<10;i++)
    {
        printf("Thread_id=%d and i=%d\n",omp_get_thread_num(),i);
        sum_val=sum_val+arr[i];
    }
    printf("sum_value=%f",sum_val);
    printf("\n");

    #pragma omp parallel for reduction(+:sum)
    for (i=0;i<10;i++)
    {
        printf("Thread_id=%d and i=%d\n",omp_get_thread_num(),i);
        sum=sum+arr[i];
    }
    avg=sum/10;
    printf("avg_value=%f",avg);
    printf("\n");

}