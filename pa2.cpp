#include<bits/stdc++.h>

using namespace std;

class node{
public:
    char ch;
    int cnt;
    node *left;
    node *right;
};
class comp{
public:
    bool operator()(const pair<int, node*>& a, const pair<int, node*>& b){
        if(a.first == b.first){
            return a.second->ch > b.second->ch;
        }
        else return a.first > b.first;
    }
};

int main(int argc, const char* argv[]){
    priority_queue<pair<int,node*>, vector<pair<int,node*>>, comp> pq;
    fstream inptxt;
    vector<string> all_args;
    all_args.assign(argv, argv + argc); // convert command line argument to string 

    cout << "DSOO-Program2-Demo: ";
    for(auto a : all_args){
        cout << a << " ";
    }
    cout << "\n";
    
	vector<int> chcnt(52,0);//character count 0-25 A-Z  26-51 a-z
    
    if(argc != 2){
        cout << "part1\n";// or cout << '\n';
        chcnt[0]=11;chcnt[1]=5;chcnt[2]=2;chcnt[3]=3;chcnt[4]=12;
        chcnt[5]=3;chcnt[6]=5;chcnt[7]=6;chcnt[8]=8;chcnt[9]=1;
        chcnt[10]=2;chcnt[11]=4;chcnt[12]=8;chcnt[13]=7;chcnt[14]=2;
        chcnt[15]=2;chcnt[16]=1;chcnt[17]=9;chcnt[18]=6;chcnt[19]=2;
        chcnt[20]=4;chcnt[21]=1;chcnt[22]=10;chcnt[23]=10;chcnt[24]=1;
        chcnt[25]=1;
        int c=0;
        node *nn;//new node
        for(int i=0;i<52;i++){
            if(chcnt[i]!=0){
                c++;
                if(i<=25){
                    cout << (char)('A'+i) << " = " << chcnt[i] << " | ";
                    nn = new node;
                    nn->ch = (char)('A'+i);
                    nn->cnt = chcnt[i];
                    pq.emplace(make_pair(chcnt[i], nn));
                }
                else{
                    cout << (char)('a'+i) << " = " << chcnt[i] << " | ";
                    nn = new node;
                    nn->ch = (char)('a'+i);
                    nn->cnt = chcnt[i];
                    pq.emplace(make_pair(chcnt[i], nn));
                }
            }

            if(c%10==0)cout << '\n';
        }
        cout << "\n\n";
    }
    else{
        string filename = argv[1];
        cout << "read file from : " << "test/" << filename << endl;

        inptxt.open(filename, ios::in);
        string inp;
        inptxt >> inp;
        for(int i=0;i<(int)inp.size();i++){
            if(inp[i]<='Z' && inp[i]>='A')chcnt[inp[i]-'A']++;
            else chcnt[inp[i]-'a'+26]++;
        }
    }

    
    
    

    return 0;
}