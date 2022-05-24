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

int position(vector<int> &arr, int l, int r){//return position(index) of pivot
    int pivot = arr[l];
    int j=l;
    for(int i=l+1;i<=r;i++){
        if(pivot >= arr[i]){
            j++;
        }
    }
    swap(arr[l], arr[j]);

    while(l<j && r>j){
        while(arr[l] <= pivot)l++;

        while(arr[r] > pivot)r--;

        if(l<j && r>j)swap(arr[l++],arr[r--]);
    }

    return j;
}
void quickSort(vector<int> &arr, int l, int r){
    if(l>=r)return;
    int pos = position(arr, l, r);
    if(arr.size()<=100){
        cout << l << '-' << r << " : \n";
        for(int t=0;t<(int)arr.size();t++){cout << arr[t] << ',';}
        cout << '\n';
    }
    quickSort(arr, l, pos-1);
    quickSort(arr, pos+1, r);
}

void radixSort(vector<int> &arr){
    vector<vector<int>> place(10);
    int sz = arr.size(), sd = 1, cnt;
    for(int d=1;d<=3;d++){//digit from low to high
        if(sz<=100){
            if(d==1)cout << "First-pass:\n";
            else if(d==2)cout << "Second-pass\n";
            else cout << "Third-pass\n";
        }

        for(int t=0;t<sz;t++){
            place[(arr[t]/sd)%10].emplace_back(arr[t]);
        }
        cnt=0;
        for(int i=0;i<10;i++){
            if(sz<=100)cout << i << " |";
            for(int j=0;j<(int)place[i].size();j++){
                if(sz<=100)cout << " --> " << place[i][j];
                arr[cnt++] = place[i][j];
            }
            if(sz<=100)cout << '\n';
            place[i].clear();
        }
        if(sz<=100){
            cout << "resulting chain : ";
            for(int t=0;t<sz;t++)cout << arr[t] << ',';
            cout << "\n\n";
        }
        sd*=10;
    }
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
        for(int t=0;t<(int)v.size();t++){cout << v[t] << ',';}cout << "\n\n";
        cout << "Insertion sort:\n";
        START = clock();
        vector<int> is = insertionSort(v);//saved for check correction
        END = clock();
        cout << "sorting time : " << (END - START) / CLOCKS_PER_SEC << " s\n\n\n";

        //quick
        cout << "Quick sort:\n";
        cout << "Before : ";
        for(int t=0;t<(int)v.size();t++){cout << v[t] << ',';}cout << "\n";
        vector<int> qs = v;
        START = clock();
        quickSort(qs, 0, qs.size()-1);
        END = clock();
        cout << "sorting time : " << (END - START) / CLOCKS_PER_SEC << " s\n";
        if(qs == is)cout << "Correct!!\n\n\n";
        else cout << "Not correct\n\n\n";

        //radix
        cout << "Radix sort:\n";
        vector<int> rs = v;
        START = clock();
        radixSort(rs);
        END = clock();
        cout << "sorting time : " << (END - START) / CLOCKS_PER_SEC << " s\n";
        if(rs == is)cout << "Correct!!\n\n\n";
        else cout << "Not correct\n\n\n";
    }
    else{
        vector<int> v(inp);
        for(int t=0;t<inp;t++)v[t] = rand()%999 +1;

        if(inp<=100){//format 1
            cout << "Before : ";
            for(int t=0;t<(int)v.size();t++){cout << v[t] << ',';}cout << "\n\n";
            cout << "Insertion sort:\n";
            START = clock();
            vector<int> is = insertionSort(v);
            END = clock();
            cout << "sorting time : " << (END - START) / CLOCKS_PER_SEC << " s\n\n\n";

            //quick
            cout << "Quick sort:\n";
            cout << "Before : ";
            for(int t=0;t<(int)v.size();t++){cout << v[t] << ',';}cout << "\n";
            vector<int> qs = v;
            START = clock();
            quickSort(qs, 0, qs.size()-1);
            END = clock();
            cout << "sorting time : " << (END - START) / CLOCKS_PER_SEC << " s\n";
            if(qs == is)cout << "Correct!!\n\n\n";
            else cout << "Not correct\n\n\n";

            cout << "Radix sort:\n";
            vector<int> rs = v;
            START = clock();
            radixSort(rs);
            END = clock();
            cout << "sorting time : " << (END - START) / CLOCKS_PER_SEC << " s\n";
            if(rs == is)cout << "Correct!!\n\n\n";
            else cout << "Not correct\n\n\n";
        }
        else{
            cout << "Insertion sort:\n";
            START = clock();
            vector<int> is = insertionSort(v);
            END = clock();
            cout << "sorting time : " << (END - START) / CLOCKS_PER_SEC << " s\n\n\n";

            cout << "Quick sort:\n";
            vector<int> qs = v;
            START = clock();
            quickSort(qs, 0, qs.size()-1);
            END = clock();
            cout << "sorting time : " << (END - START) / CLOCKS_PER_SEC << " s\n";
            if(qs == is)cout << "Correct!!\n\n\n";
            else cout << "Not correct\n\n\n";

            cout << "Radix sort:\n";
            vector<int> rs = v;
            START = clock();
            radixSort(rs);
            END = clock();
            cout << "sorting time : " << (END - START) / CLOCKS_PER_SEC << " s\n";
            if(rs == is)cout << "Correct!!\n\n\n";
            else cout << "Not correct\n\n\n";
        }
    }
}