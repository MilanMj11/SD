#include <bits/stdc++.h>
#include <chrono>

using namespace std;
using namespace chrono;

ifstream fin("input.txt");
ofstream fout("output.txt");

const long long NMAX = 100000005; /// maxim 10^8 + 5
const long long INF = (1<<29);
long long a[NMAX],aux[NMAX];
list<long long> bucket[(1<<16)+5];


///____________________________________________
void concat(long long a[],long long st,long long dr){
    long long mij = (st+dr)/2;
    long long dim1 = mij-st+1;
    long long dim2 = dr-mij;

    long long *b = new long long[dim1+5];
    long long *c = new long long[dim2+5];

    long long k=0;
    for(long long i=st;i<=mij;i++) b[++k] = a[i];
    b[++k]=INF;
    k=0;
    for(long long i=mij+1;i<=dr;i++) c[++k] = a[i];
    c[++k]=INF;
    long long ind1=1,ind2=1;
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

void merge_sort(long long a[],long long st,long long dr){
    if(st>=dr) return;
    long long mij=(st+dr)/2;
    merge_sort(a,st,mij);
    merge_sort(a,mij+1,dr);
    concat(a,st,dr);
}
///____________________________________________

///____________________________________________
long long partitie(long long a[],long long low,long long high){
    long long pivot = a[high];
    long long i = low-1;
    for(long long j=low;j<high;j++){
        if(a[j] < pivot){
            i++;
            swap(a[i],a[j]);
        }
    }
    swap(a[i+1],a[high]);
    return i+1;
}

void quicksort(long long a[],long long low,long long high){
    if(low < high){
        long long mij = partitie(a,low,high);
        quicksort(a,low,mij-1);
        quicksort(a,mij+1,high);
    }
}
///______________________________________________

///_____________________________________________
void RadixSort(long long a[],long long n,long long base){
    long long p = 1;
    long long maxim = 0;
    for(long long i=1;i<=n;i++){
        if (a[i]>maxim) maxim=a[i];
    }
    //memset(bucket,0,sizeof(bucket));
    while(p<=maxim){
        for(long long i=1;i<=n;i++){
            long long cifra = (a[i] / p) % base;
            bucket[cifra].push_back(a[i]);
        }
        long long ind = 0;
        for(long long i=0;i<base;i++){
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
void InsertionSort(long long a[],long long n){
    long long key=0;
    for(long long i=1;i<=n;i++){
        key = a[i];
        for(long long j=i-1;j>=1;j--){
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
void ShellSort(long long a[],long long n){
    for(long long gap = n/2; gap >= 1; gap /= 2){
        for(long long i = gap; i < n; i++){
            long long nr = a[i];
            long long ind = i;
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
void heapify_arb(long long a[],long long n,long long node){
    if(n==0) return; /// masura precautie
    long long maxim = node;
    long long st = 2*node;
    long long dr = 2*node+1;
    if(st <= n and a[st] > a[maxim])
        maxim = st;
    if(dr <= n and a[dr] > a[maxim])
        maxim = dr;
    if(node != maxim) { /// root not the biggest
        swap(a[node],a[maxim]);
        heapify_arb(a,n,maxim);
    }
}

void HeapSort(long long a[],long long n){
    for(long long i=n/2;i>=1;i--) /// construiesc max-heapul
        heapify_arb(a,n,i);
    for(long long i=n;i>=1;i--){
        swap(a[1],a[i]); /// pun maximul in capat
        /// maximul fiind mereu varful arborelui adica a[1];
        heapify_arb(a,i-1,1); /// get rid of last element
        /// e deja fixat
    }
}
///______________________________________________

long long Calculate_MergeSort_Time(long long a[],long long n){
    for(long long i=1;i<=n;i++) aux[i] = a[i];
    auto start = high_resolution_clock::now();
    merge_sort(a,1,n);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop-start);
    for(long long i=1;i<=n;i++) a[i] = aux[i];
    return duration.count();
}

long long Calculate_QuickSort_Time(long long a[],long long n){
    for(long long i=1;i<=n;i++) aux[i] = a[i];
    auto start = high_resolution_clock::now();
    quicksort(a,1,n);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop-start);
    for(long long i=1;i<=n;i++) a[i] = aux[i];
    return duration.count();
}

long long Calculate_Radix_Time(long long a[],long long n,long long base){
    for(long long i=1;i<=n;i++) aux[i] = a[i];
    auto start = high_resolution_clock::now();
    RadixSort(a,n,base);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop-start);
    for(long long i=1;i<=n;i++) a[i] = aux[i];
    return duration.count();
}

long long Calculate_InsertionSort_Time(long long a[],long long n){
    for(long long i=1;i<=n;i++) aux[i] = a[i];
    auto start = high_resolution_clock::now();
    InsertionSort(a,n);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop-start);
    for(long long i=1;i<=n;i++) a[i] = aux[i];
    return duration.count();
}

long long Calculate_ShellSort_Time(long long a[],long long n){
    for(long long i=1;i<=n;i++) aux[i] = a[i];
    auto start = high_resolution_clock::now();
    ShellSort(a,n);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop-start);
    for(long long i=1;i<=n;i++) a[i] = aux[i];
    return duration.count();
}

long long Calculate_HeapSort_Time(long long a[],long long n){
    for(long long i=1;i<=n;i++) aux[i] = a[i];
    auto start = high_resolution_clock::now();
    HeapSort(a,n);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop-start);
    for(long long i=1;i<=n;i++) a[i] = aux[i];
    return duration.count();
}

long long Calculate_STDSort_Time(long long a[],long long n){
    for(long long i=1;i<=n;i++) aux[i] = a[i];
    auto start = high_resolution_clock::now();
    sort(a+1,a+n+1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop-start);
    for(long long i=1;i<=n;i++) a[i] = aux[i];
    return duration.count();
}

long long Randomize() {
    long long randnumber = 0;
    int digits[20];
    for (int i=18;i>=1;i--){
        digits[i]=rand()%10;
    }
    for(int i=18; i>=1; i--){
        long long power = pow(10, i-1);
        if (power%2 != 0 && power != 1)
            power++;
        randnumber += power * digits[i];
    }
    return randnumber;
}

void generate_input(long long n,long long maxim){
    fout << "N = " << n << ' ' << "Max = " << maxim << '\n';
    if(n > 100000003){
        fout << "Cannot Sort" << '\n';
        return;
    }
    for(long long i=1;i<=n;i++) {
        a[i] = Randomize() % maxim;
    }
    long long time_merge = Calculate_MergeSort_Time(a,n);
    long long time_quick = Calculate_QuickSort_Time(a,n);
    long long time_radix = Calculate_Radix_Time(a,n,(1<<16));
//    long long time_insertion = Calculate_InsertionSort_Time(a,n);
    long long time_shell = Calculate_ShellSort_Time(a,n);
    long long time_heap = Calculate_HeapSort_Time(a,n);
    long long time_std = Calculate_STDSort_Time(a,n);
    fout << "Merge Sort execution time is : " << time_merge << " microseconds" <<'\n';
    fout << "Quick Sort execution time is : " << time_quick << " microseconds" <<'\n';
    fout << "Radix Sort execution time is : " << time_radix << " microseconds" <<'\n';
    fout << "Shell Sort execution time is : " << time_shell << " microseconds" <<'\n';
    fout << "Heap Sort execution time is : " << time_heap << " microseconds" <<'\n';
    fout << "STD Sort execution time is : " << time_std << " microseconds" << '\n';
}

void citire(){
    long long T,n,maxim;
    fin >> T;
    for(long long t=1;t<=T;t++){
        fin >> n >> maxim;
        generate_input(n,maxim);
    }

}

int main() {
    citire();
    ///merge_sort(a,1,n);
    ///quicksort(a,1,n);
    ///RadixSort(a,n,(10));
    ///InsertionSort(a,n);
    ///Shelong longSort(a,n);
    ///HeapSort(a,n);
    return 0;
}
