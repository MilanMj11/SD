#include <bits/stdc++.h>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

const int NMAX = 1005;
const int INF = (1<<29);
int a[NMAX],n;

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

int main() {
    fin >> n;
    for(int i=1;i<=n;i++){
        fin >> a[i];
    }
    merge_sort(a,1,n);
    for(int i=1;i<=n;i++){
        fout << a[i] << ' ';
    }
    return 0;
}
