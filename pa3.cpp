#include<bits/stdc++.h>

using namespace std;

vector<int> insertionSort(vector<int> arr){
    int sz = arr.size();
    for(int i=1;i<sz;i++){
        for(int j=0;j<i;j++){
            if(arr[i] < arr[j]){
                int tmp = arr[i];
                for(int k=i;k>j;k--)arr[k] = arr[k-1];
                arr[j] = tmp;
                break;
            }
        }
        if(sz<=100){
            cout << setw(2) << i << " : ";
            for(int t=0;t<sz;t++)cout << arr[t] << ',';
            cout << '\n';
        }
    }

    return arr;
}

int position(vector<int> arr, int l, int r){//return position(index) of pivot
    int pivot = arr[l];
    int i = l+1;
}
vector<int> quickSort(vector<int> arr, int l, int r){
    

    return arr;
}
void radixSort(vector<int> arr){

}

int main(){
    ios::sync_with_stdio(false);cin.tie(0);

    cout << "DS-OO Program3-Demo\n";
    srand(time(NULL));
    double START, END;//sorting time(if sort in 1 ms, will output 0s)

    int inp;
    cin >> inp;
    if(inp<=0){//part 1
        vector<int> v = {168,179,208,306,93,859,984,55,9,271,33};
        cout << "Before : ";
        for(int t=0;t<(int)v.size();t++)cout << v[t] << ',';cout << "\n\n";
        cout << "Insertion sort:\n";
        START = clock();
        vector<int> is = insertionSort(v);//saved for check correction
        END = clock();
        cout << "sorting time : " << (END - START) / CLOCKS_PER_SEC << " s\n\n\n";

        //quick
        cout << "Quick sort:\n";
        cout << "Before : ";
        for(int t=0;t<(int)v.size();t++)cout << v[t] << ',';cout << "\n\n";
        START = clock();
        vector<int> qs = quickSort(v, 0, v.size()-1);
        END = clock();
        cout << "sorting time : " << (END - START) / CLOCKS_PER_SEC << " s\n\n\n";
    }
    else{
        vector<int> v(inp);
        for(int t=0;t<inp;t++)v[t] = rand()%999 +1;

        if(inp<=100){//format 1
            cout << "Before : ";
            for(int t=0;t<(int)v.size();t++)cout << v[t] << ',';cout << "\n\n";
            cout << "Insertion sort:\n";
            START = clock();
            vector<int> is = insertionSort(v);
            END = clock();
            cout << "sorting time : " << (END - START) / CLOCKS_PER_SEC << " s\n\n\n";

            //quick
            cout << "Quick sort:\n";
            cout << "Before : ";
            for(int t=0;t<(int)v.size();t++)cout << v[t] << ',';cout << "\n\n";
        }
        else{
            cout << "Insertion sort:\n";
            START = clock();
            vector<int> is = insertionSort(v);
            END = clock();
            cout << "sorting time : " << (END - START) / CLOCKS_PER_SEC << " s\n\n\n";

            cout << "Quick sort:\n";
        }
    }
}