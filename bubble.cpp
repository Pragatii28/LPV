#include<iostream>
#include<omp.h>
using namespace std;
void swap(int &a,int &b)
{
    int temp;
    temp=a;
    a=b;
    b=temp;
}

void bubble(int *a,int n)
{
    double start=omp_get_wtime();
    for(int i=0;i<n;i++)
    {
        #pragma omp parallel
        for(int j=i+1;j<n;j++)
        {
            if(a[j]<a[i])
                swap(a[i],a[j]);
        }
    }
    double end=omp_get_wtime();
    double time=end-start;
    cout<<"\nTime Taken="<<time<<endl;
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
    cout<<"Bubble sort:\n";
    bubble(a,n);
    cout<<"Sorted Array:\n";
    for(int i=0;i<n;i++)
    {
        cout<<a[i];
    }
    return 0;
}
