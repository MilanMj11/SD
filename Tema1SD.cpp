#include <bits/stdc++.h>

using namespace std;

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

int main() {
    fin >> n;
    for(int i=1;i<=n;i++){
        fin >> a[i];
    }
    ///merge_sort(a,1,n);
    ///quicksort(a,1,n);
    ///RadixSort(a,(1<<16));
    ///InsertionSort(a);
    for(int i=1;i<=n;i++){
        fout << a[i] << ' ';
    }
    return 0;
}
