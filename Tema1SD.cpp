#include <bits/stdc++.h>
#include <chrono>

using namespace std;
using namespace chrono;

ifstream fin("input.txt");
ofstream fout("output.txt");

const int NMAX = (1<<17)+1;
const int INF = (1<<29);
int a[NMAX],n;
list<int> bucket[NMAX];


///____________________________________________
void concat(int a[],int st,int dr){
    int mij = (st+dr)/2;
    int dim1 = mij-st+1;
    int dim2 = dr-mij;

    int *b = new int[dim1+5];
    int *c = new int[dim2+5];

    int k=0;
    for(int i=st;i<=mij;i++) b[++k] = a[i];
    b[++k]=INF;
    k=0;
    for(int i=mij+1;i<=dr;i++) c[++k] = a[i];
    c[++k]=INF;
    int ind1=1,ind2=1;
    k=st-1;
    while(true){
        if(b[ind1]==INF and c[ind2]==INF) break;
        if(b[ind1]<c[ind2] or c[ind2]==INF){
            a[++k] = b[ind1];
            ind1++;
            continue;
        }
        if(b[ind1]>=c[ind2] or b[ind1]==INF){
            a[++k] = c[ind2];
            ind2++;
            continue;
        }
    }
    delete[] b;
    delete[] c;
}

void merge_sort(int a[],int st,int dr){
    if(st>=dr) return;
    int mij=(st+dr)/2;
    merge_sort(a,st,mij);
    merge_sort(a,mij+1,dr);
    concat(a,st,dr);
}
///____________________________________________

///____________________________________________
int partitie(int a[],int low,int high){
    int pivot = a[high];
    int i = low-1;
    for(int j=low;j<high;j++){
        if(a[j] < pivot){
            i++;
            swap(a[i],a[j]);
        }
    }
    swap(a[i+1],a[high]);
    return i+1;
}

void quicksort(int a[],int low,int high){
    if(low < high){
        int mij = partitie(a,low,high);
        quicksort(a,low,mij-1);
        quicksort(a,mij+1,high);
    }
}
///______________________________________________

///_____________________________________________
void RadixSort(int a[],int n,int base){
    long long p = 1;
    long long maxim = 0;
    for(int i=1;i<=n;i++){
        if (a[i]>maxim) maxim=a[i];
    }
    //memset(bucket,0,sizeof(bucket));
    while(p<=maxim){
        for(int i=1;i<=n;i++){
            int cifra = (a[i] / p) % base;
            bucket[cifra].push_back(a[i]);
        }
        int ind = 0;
        for(int i=0;i<base;i++){
            while(!bucket[i].empty()){
                a[++ind] = *(bucket[i].begin());
                bucket[i].erase(bucket[i].begin());
            }
        }
        p*=base;
    }
}
///______________________________________________

///______________________________________________
void InsertionSort(int a[],int n){
    int key=0;
    for(int i=1;i<=n;i++){
        key = a[i];
        for(int j=i-1;j>=1;j--){
            if(key < a[j]) {
                swap(a[j],a[j+1]);
                key = a[j];
            }
            else break;
        }
    }
}
///______________________________________________

///______________________________________________
void ShellSort(int a[],int n){
    for(int gap = n/2; gap >= 1; gap /= 2){
        for(int i = gap; i < n; i++){
            int nr = a[i];
            int ind = i;
            while(ind >= gap and a[ind-gap] > nr){
                a[ind] = a[ind-gap];
                ind -= gap;
            }
            a[ind] = nr;
        }
    }
}
///______________________________________________


///______________________________________________
void heapify_arb(int a[],int n,int node){
    if(n==0) return; /// masura precautie
    int maxim = node;
    int st = 2*node;
    int dr = 2*node+1;
    if(st <= n and a[st] > a[maxim])
        maxim = st;
    if(dr <= n and a[dr] > a[maxim])
        maxim = dr;
    if(node != maxim) { /// root not the biggest
        swap(a[node],a[maxim]);
        heapify_arb(a,n,maxim);
    }
}

void HeapSort(int a[],int n){
    for(int i=n/2;i>=1;i--) /// construiesc max-heapul
        heapify_arb(a,n,i);
    for(int i=n;i>=1;i--){
        swap(a[1],a[i]); /// pun maximul in capat
        /// maximul fiind mereu varful arborelui adica a[1];
        heapify_arb(a,i-1,1); /// get rid of last element
        /// e deja fixat
    }
}
///______________________________________________

long long Calculate_MergeSort_Time(int a[],int n){
    int aux[NMAX];
    for(int i=1;i<=n;i++) aux[i] = a[i];
    auto start = high_resolution_clock::now();
    merge_sort(a,1,n);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop-start);
    for(int i=1;i<=n;i++) a[i] = aux[i];
    return duration.count();
}

long long Calculate_QuickSort_Time(int a[],int n){
    int aux[NMAX];
    for(int i=1;i<=n;i++) aux[i] = a[i];
    auto start = high_resolution_clock::now();
    quicksort(a,1,n);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop-start);
    for(int i=1;i<=n;i++) a[i] = aux[i];
    return duration.count();
}

long long Calculate_Radix_Time(int a[],int n,int base){
    int aux[NMAX];
    for(int i=1;i<=n;i++) aux[i] = a[i];
    auto start = high_resolution_clock::now();
    RadixSort(a,n,base);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop-start);
    for(int i=1;i<=n;i++) a[i] = aux[i];
    return duration.count();
}

long long Calculate_InsertionSort_Time(int a[],int n){
    int aux[NMAX];
    for(int i=1;i<=n;i++) aux[i] = a[i];
    auto start = high_resolution_clock::now();
    InsertionSort(a,n);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop-start);
    for(int i=1;i<=n;i++) a[i] = aux[i];
    return duration.count();
}

long long Calculate_ShellSort_Time(int a[],int n){
    int aux[NMAX];
    for(int i=1;i<=n;i++) aux[i] = a[i];
    auto start = high_resolution_clock::now();
    ShellSort(a,n);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop-start);
    for(int i=1;i<=n;i++) a[i] = aux[i];
    return duration.count();
}

long long Calculate_HeapSort_Time(int a[],int n){
    int aux[NMAX];
    for(int i=1;i<=n;i++) aux[i] = a[i];
    auto start = high_resolution_clock::now();
    HeapSort(a,n);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop-start);
    for(int i=1;i<=n;i++) a[i] = aux[i];
    return duration.count();
}

int main() {
    fin >> n;
    for(int i=1;i<=n;i++){
        fin >> a[i];
    }
    long long time_merge = Calculate_MergeSort_Time(a,n);
    long long time_quick = Calculate_QuickSort_Time(a,n);
    long long time_radix = Calculate_Radix_Time(a,n,(1<<16));
    long long time_insertion = Calculate_InsertionSort_Time(a,n);
    long long time_shell = Calculate_ShellSort_Time(a,n);
    long long time_heap = Calculate_HeapSort_Time(a,n);
    fout << time_merge << '\n';
    fout << time_quick << '\n';
    fout << time_radix << '\n';
    fout << time_insertion << '\n';
    fout << time_shell << '\n';
    fout << time_heap << '\n';
    ///merge_sort(a,1,n);
    ///quicksort(a,1,n);
    ///RadixSort(a,n,(10));
    ///InsertionSort(a,n);
    ///ShellSort(a,n);
    ///HeapSort(a,n);

    for(int i=1;i<=n;i++){
        fout << a[i] << ' ';
    }
    return 0;
}
