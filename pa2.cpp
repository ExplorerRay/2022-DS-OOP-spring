#include<bits/stdc++.h>

using namespace std;

class node{
public:
    char ch='\0';
    int cnt;
    node *left = nullptr;
    node *right = nullptr;
    bool visited = false;
    string cd="\0";
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
    
    int wepl=0;
	vector<int> chcnt(52,0);//character count 0-25 A-Z  26-51 a-z
    vector<string> chcd(52,"\0");//character and their huffman code
    
    if(argc != 2){
        cout << '\n';
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
                    cout << (char)('a'+i-26) << " = " << chcnt[i] << " | ";
                    nn = new node;
                    nn->ch = (char)('a'+i-26);
                    nn->cnt = chcnt[i];
                    pq.emplace(make_pair(chcnt[i], nn));
                }
                if(c%10==0)cout << '\n';
            }
        }
        cout << "\n\n";

        pair<int,node*> fir,sec;//construct huffman tree
        node *parent;
        while(pq.size()>=2){
            fir = pq.top();
            pq.pop();
            sec = pq.top();
            pq.pop();
            parent = new node;
            parent->cnt = fir.first + sec.first;
            parent->left = fir.second;
            parent->right = sec.second;
            pq.emplace(make_pair(parent->cnt, parent));
        }
 
        node *root = pq.top().second, *tp;
        queue<node*> que;
        que.emplace(root);
        root->visited = true;
        while(!que.empty()){//traversal the tree
            tp=que.front();
            if(tp->left->visited == false){
                if(tp->left->ch=='\0'){
                    tp->left->cd = tp->cd + '0';
                    que.emplace(tp->left);
                }
                else{
                    if(tp->left->ch<='Z' && tp->left->ch>='A'){
                        chcd[tp->left->ch-'A']= tp->cd + '0';
                    }
                    else{
                        chcd[tp->left->ch-'a'+26]= tp->cd + '0';
                    }
                }
                tp->left->visited = true;
            }
            if(tp->right->visited == false){
                if(tp->right->ch=='\0'){
                    tp->right->cd = tp->cd + '1';
                    que.emplace(tp->right);
                }
                else{
                    if(tp->right->ch<='Z' && tp->right->ch>='A'){
                        chcd[tp->right->ch-'A']= tp->cd + '1';
                    }
                    else{
                        chcd[tp->right->ch-'a'+26]= tp->cd + '1';
                    }
                }
                tp->right->visited = true;
            }
            que.pop();
        }
        for(int x=0;x<52;x++){
            if(chcd[x]!="\0"){
                wepl = wepl + chcnt[x]*chcd[x].size();
                if(x<=25){
                    cout << (char)(x+'A') << " : " << chcd[x] << '\n';
                }
                else{
                    cout << (char)(x+'a'-26) << " : " << chcd[x] << '\n';
                }
            }
        }
        cout << "\nWEPL : " << wepl << '\n';
    }
    else{
        string filename = argv[1];
        //cout << "read file from : " << "test/" << filename << endl;

        inptxt.open(filename, ios::in);
        if(!inptxt.is_open())return 0;
        string inp;
        inptxt >> inp;
        cout << "characters : " << inp << "\n\n";
        for(int i=0;i<(int)inp.size();i++){
            if(inp[i]<='Z' && inp[i]>='A')chcnt[inp[i]-'A']++;
            else chcnt[inp[i]-'a'+26]++;
        }
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
                    cout << (char)('a'+i-26) << " = " << chcnt[i] << " | ";
                    nn = new node;
                    nn->ch = (char)('a'+i-26);
                    nn->cnt = chcnt[i];
                    pq.emplace(make_pair(chcnt[i], nn));
                }
                if(c%10==0)cout << '\n';
            }
        }
        cout << "\n\n";

        pair<int,node*> fir,sec;//construct huffman tree
        node *parent;
        while(pq.size()>=2){
            fir = pq.top();
            pq.pop();
            sec = pq.top();
            pq.pop();
            parent = new node;
            parent->cnt = fir.first + sec.first;
            parent->left = fir.second;
            parent->right = sec.second;
            pq.emplace(make_pair(parent->cnt, parent));
        }

        node *root = pq.top().second, *tp;
        queue<node*> que;
        que.emplace(root);
        root->visited = true;
        while(!que.empty()){//traversal the tree
            tp=que.front();
            if(tp->left->visited == false){
                if(tp->left->ch=='\0'){
                    tp->left->cd = tp->cd + '0';
                    que.emplace(tp->left);
                }
                else{
                    if(tp->left->ch<='Z' && tp->left->ch>='A'){
                        chcd[tp->left->ch-'A']= tp->cd + '0';
                    }
                    else{
                        chcd[tp->left->ch-'a'+26]= tp->cd + '0';
                    }
                }
                tp->left->visited = true;
            }
            if(tp->right->visited == false){
                if(tp->right->ch=='\0'){
                    tp->right->cd = tp->cd + '1';
                    que.emplace(tp->right);
                }
                else{
                    if(tp->right->ch<='Z' && tp->right->ch>='A'){
                        chcd[tp->right->ch-'A']= tp->cd + '1';
                    }
                    else{
                        chcd[tp->right->ch-'a'+26]= tp->cd + '1';
                    }
                }
                tp->right->visited = true;
            }
            que.pop();
        }
        for(int x=0;x<52;x++){
            if(chcd[x]!="\0"){
                wepl = wepl + chcnt[x]*chcd[x].size();
                if(x<=25){
                    cout << (char)(x+'A') << " : " << chcd[x] << '\n';
                }
                else{
                    cout << (char)(x+'a'-26) << " : " << chcd[x] << '\n';
                }
            }
        }

        inptxt >> inp;
        cout << "\nHuffman code : " << inp << '\n';
        cout << "decode : ";
        node *nw = root;
        for(int x=0;x<(int)inp.size();x++){
            if(inp[x]=='0')nw = nw->left;
            else nw = nw->right;

            if(nw->ch!='\0'){
                cout << nw->ch;
                nw = root;
            }
        }
        if(nw != root)cout << " -wrong decode-";

        cout << "\nWEPL : " << wepl << '\n';
    }

    return 0;
}