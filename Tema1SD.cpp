#include <bits/stdc++.h>
#include <chrono>

using namespace std;
using namespace chrono;

ifstream fin("input.txt");
ofstream fout("output.txt");

const int NMAX = (1<<17)+1;
const int INF = (1<<29);
int a[NMAX],n;
vector<int> bucket[NMAX];


///____________________________________________
void concat(int a[],int st,int dr){
    int b[NMAX],c[NMAX];
    int mij=(st+dr)/2;
    int k=0;
    for(int i=st;i<=mij;i++)
        b[++k] = a[i];
    b[++k]=INF;
    k=0;
    for(int i=mij+1;i<=dr;i++)
        c[++k] = a[i];
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
}

void merge_sort(int a[],int st,int dr){
    if(st==dr) return;
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
void RadixSort(int a[],int base){
    long long p = 1;
    long long maxim = 0;
    for(int i=1;i<=n;i++){
        if (a[i]>maxim) maxim=a[i];
    }
    memset(bucket,0,sizeof(bucket));
    while(p<=maxim){
        for(int i=1;i<=n;i++){
            int cifra = (a[i] / p) % base;
            bucket[cifra].insert(bucket[cifra].begin(),a[i]);
        }
        int ind = 0;
        for(int i=0;i<base;i++){
            while(bucket[i].size()!=0){
                a[++ind]=bucket[i].back();
                bucket[i].pop_back();
            }
        }
        p*=base;
    }
}
///______________________________________________

///______________________________________________
void InsertionSort(int a[]){
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

void Calculate_MergeSort_Time(int a[]){
    auto start = high_resolution_clock::now();
    merge_sort(a,1,n);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop-start);
    fout << duration.count() << " microseconds" << '\n';
}

int main() {
    fin >> n;
    for(int i=1;i<=n;i++){
        fin >> a[i];
    }
    ///Calculate_MergeSort_Time(a);
    ///merge_sort(a,1,n);
    ///quicksort(a,1,n);
    ///RadixSort(a,(1<<16));
    ///InsertionSort(a);
    ///ShellSort(a,n);
    ///HeapSort(a,n);
    for(int i=1;i<=n;i++){
        fout << a[i] << ' ';
    }
    return 0;
}
