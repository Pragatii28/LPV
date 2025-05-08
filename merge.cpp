#include<iostream>
#include<omp.h>
using namespace std;
void merge(int *,int,int,int);

void merge_sort(int *arr,int low,int high)
{
    int mid;
    if(low<high)
    {
        mid=(low+high)/2;
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                merge_sort(arr,low,mid);
            }
            #pragma omp section
            {
                merge_sort(arr,mid+1,high);
            }
        }
        merge(arr,low,high,mid);

    }
}
void merge(int *a, int low,int high, int mid)
{
    int i,j,k,c[50];
    i=low;
    j=mid+1;
    k=low;
    while(i<=mid && j<=high)
    {
        if(a[i]<a[j])
        {
            c[k]=a[i];
            k++;
            i++;
        }
        else
        {    
            c[k]=a[j];
            k++;
            j++;
        }
    }
    while(i<=mid)
    {
        c[k]=a[i];
        k++;
        i++;
    }
    while(j<=high)
    {
        c[k]=a[j];
        k++;
        j++;
    }
    for(int i=low;i<k;i++)
    {
        a[i]=c[i];
    }
}

int main()
{
    omp_set_num_threads(4);
    int *a,n;
    cout<<"\nEnter total no of elements :";
    cin>>n;
    a=new int[n];
    cout<<"Enter elts:\n";
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
    }
    cout<<"Merge sort:\n";
    merge_sort(a,0,n-1);
    cout<<"Sorted Array:\n";
    for(int i=0;i<n;i++)
    {
        cout<<a[i]<<" ";
    }
    return 0;
}