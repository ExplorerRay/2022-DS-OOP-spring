#include<bits/stdc++.h>
//#include "pa1.h"

using namespace std;

//未將飛機加入queue中
//未處理fuel_lv隨時間減少的情形 當減的時候看到有LV是0便直接捨棄(已墜機或起飛)
class runway{
public:
    vector<pair<int,int>> land_queue1;
    vector<pair<int,int>> land_queue2;
    vector<int> tkoff_queue;
    int id_now=-1;
    int tt_plane=0;//total plane on runway(useless???)
};
class statistic{
public:
    int crash_plane=0;
};

class airport{
public:
    int land_number,land_id=1,fuel_lv,total=0;
    int tkoff_number,tkoff_id=0,tk_total=0;
    int dc_rwqe=0;//decide runway and queue只有rw234 [%3==0(rw1) %3==1(rw2)...
    vector<int> eg_queue;//queue of emergent plane's id
    
    //vector<pair<int,int>> land_wait;
    runway rw1,rw2,rw3,rw4;
    statistic stat;

    void print_rwinfo(){
        cout << "Runway1(" << rw1.id_now << ")\n";
        cout << "L1: ";
        for(unsigned int p=0;p<rw1.land_queue1.size();p++){
            cout << '(' << rw1.land_queue1[p].first << ", " << rw1.land_queue1[p].second << "), ";
        }
        cout << '\n';
        cout << "L2: ";
        for(unsigned int p=0;p<rw1.land_queue2.size();p++){
            cout << '(' << rw1.land_queue2[p].first << ", " << rw1.land_queue2[p].second << "), ";
        }
        cout << '\n';
        cout << "T: ";
        for(unsigned int p=0;p<rw1.tkoff_queue.size();p++){
            cout << '(' << rw1.tkoff_queue[p] << "), ";
        }
        cout << "\n\n";

        cout << "Runway2(" << rw2.id_now << ")\n";
        cout << "L1: ";
        for(unsigned int p=0;p<rw2.land_queue1.size();p++){
            cout << '(' << rw2.land_queue1[p].first << ", " << rw2.land_queue1[p].second << "), ";
        }
        cout << '\n';
        cout << "L2: ";
        for(unsigned int p=0;p<rw2.land_queue2.size();p++){
            cout << '(' << rw2.land_queue2[p].first << ", " << rw2.land_queue2[p].second << "), ";
        }
        cout << '\n';
        cout << "T: ";
        for(unsigned int p=0;p<rw2.tkoff_queue.size();p++){
            cout << '(' << rw2.tkoff_queue[p] << "), ";
        }
        cout << "\n\n";

        cout << "Runway3(" << rw3.id_now << ")\n";
        cout << "L1: ";
        for(unsigned int p=0;p<rw3.land_queue1.size();p++){
            cout << '(' << rw3.land_queue1[p].first << ", " << rw3.land_queue1[p].second << "), ";
        }
        cout << '\n';
        cout << "L2: ";
        for(unsigned int p=0;p<rw3.land_queue2.size();p++){
            cout << '(' << rw3.land_queue2[p].first << ", " << rw3.land_queue2[p].second << "), ";
        }
        cout << '\n';
        cout << "T: ";
        for(unsigned int p=0;p<rw3.tkoff_queue.size();p++){
            cout << '(' << rw3.tkoff_queue[p] << "), ";
        }
        cout << "\n\n";

        cout << "Runway4(" << rw4.id_now << ")\n";
        cout << "L1: ";
        for(unsigned int p=0;p<rw4.land_queue1.size();p++){
            cout << '(' << rw4.land_queue1[p].first << ", " << rw4.land_queue1[p].second << "), ";
        }
        cout << '\n';
        cout << "L2: ";
        for(unsigned int p=0;p<rw4.land_queue2.size();p++){
            cout << '(' << rw4.land_queue2[p].first << ", " << rw4.land_queue2[p].second << "), ";
        }
        cout << '\n';
        cout << "T: ";
        for(unsigned int p=0;p<rw4.tkoff_queue.size();p++){
            cout << '(' << rw4.tkoff_queue[p] << "), ";
        }
        cout << "\n\n";
    }

    void run(int step){
        cout << "Step " << step << '\n';
        if(step==1){//land plane coming
            srand((unsigned)time(NULL));
            land_number = rand()%5;//number of landing plane
            total+=land_number;
            cout << "landing plane:";
            srand((unsigned)time(NULL));
            for(int i=0;i<land_number;i++){
                fuel_lv = rand()%10 +1;
                //land_wait.emplace_back(make_pair(land_id,fuel_lv));
                cout << '(' << land_id << ", " << fuel_lv << "), ";
                if(dc_rwqe%3==0){
                    if(rw2.land_queue1.size() <= rw2.land_queue2.size())rw2.land_queue1.emplace_back(make_pair(land_id,fuel_lv));
                    else rw2.land_queue2.emplace_back(make_pair(land_id,fuel_lv));
                    dc_rwqe++;
                }
                else if(dc_rwqe%3==1){
                    if(rw3.land_queue1.size() <= rw3.land_queue2.size())rw3.land_queue1.emplace_back(make_pair(land_id,fuel_lv));
                    else rw3.land_queue2.emplace_back(make_pair(land_id,fuel_lv));
                    dc_rwqe++;
                }
                else{
                    if(rw4.land_queue1.size() <= rw4.land_queue2.size())rw4.land_queue1.emplace_back(make_pair(land_id,fuel_lv));
                    else rw4.land_queue2.emplace_back(make_pair(land_id,fuel_lv));
                    dc_rwqe++;
                }
                //可能可再改 注意tt_plane及else部分

                land_id+=2;
            }
            cout << "\n\n";
            print_rwinfo();
        }
        else if(step==2){//takeoff plane coming
            tkoff_number = rand()%5;//number of takeoff plane
            tk_total += tkoff_number;
            cout << "takeoff plane:";
            for(int i=0;i<tkoff_number;i++){
                cout << '(' << tkoff_id << "), ";
                if((int)rw1.tkoff_queue.size() < tk_total/4 +1 || rw1.tt_plane == 0){
                    rw1.tkoff_queue.emplace_back(tkoff_id);
                    rw1.tt_plane++;
                }
                else if(dc_rwqe%3==0){
                    rw2.tkoff_queue.emplace_back(tkoff_id);
                    rw2.tt_plane++;
                    dc_rwqe++;
                }
                else if(dc_rwqe%3==1){
                    rw3.tkoff_queue.emplace_back(tkoff_id);
                    rw3.tt_plane++;
                    dc_rwqe++;
                }
                else{
                    rw4.tkoff_queue.emplace_back(tkoff_id);
                    rw4.tt_plane++;
                    dc_rwqe++;
                }
                //else 要注意
                tkoff_id+=2;
            }
            cout << "\n\n";
            print_rwinfo();
        }
        else if(step==3){//determine emergent plane
            cout << "emergent plane:";
            for(int i=0;i<(int)rw1.land_queue1.size();i++){
                if(rw1.land_queue1[i].second == 0){
                    cout << '(' << rw1.land_queue1[i].first << ", 0), ";
                    eg_queue.emplace_back(rw1.land_queue1[i].first);
                }
            }
            for(int i=0;i<(int)rw1.land_queue2.size();i++){
                if(rw1.land_queue2[i].second == 0){
                    cout << '(' << rw1.land_queue2[i].first << ", 0), ";
                    eg_queue.emplace_back(rw1.land_queue2[i].first);
                }
            }
            for(int i=0;i<(int)rw2.land_queue1.size();i++){
                if(rw2.land_queue1[i].second == 0){
                    cout << '(' << rw1.land_queue1[i].first << ", 0), ";
                    eg_queue.emplace_back(rw1.land_queue1[i].first);
                }
            }
            for(int i=0;i<(int)rw2.land_queue2.size();i++){
                if(rw2.land_queue2[i].second == 0){
                    cout << '(' << rw2.land_queue2[i].first << ", 0), ";
                    eg_queue.emplace_back(rw2.land_queue2[i].first);
                }
            }
            for(int i=0;i<(int)rw3.land_queue1.size();i++){
                if(rw3.land_queue1[i].second == 0){
                    cout << '(' << rw3.land_queue1[i].first << ", 0), ";
                    eg_queue.emplace_back(rw3.land_queue1[i].first);
                }
            }
            for(int i=0;i<(int)rw3.land_queue2.size();i++){
                if(rw3.land_queue2[i].second == 0){
                    cout << '(' << rw3.land_queue2[i].first << ", 0), ";
                    eg_queue.emplace_back(rw3.land_queue2[i].first);
                }
            }
            for(int i=0;i<(int)rw4.land_queue1.size();i++){
                if(rw4.land_queue1[i].second == 0){
                    cout << '(' << rw4.land_queue1[i].first << ", 0), ";
                    eg_queue.emplace_back(rw4.land_queue1[i].first);
                }
            }
            for(int i=0;i<(int)rw4.land_queue2.size();i++){
                if(rw4.land_queue2[i].second == 0){
                    cout << '(' << rw4.land_queue2[i].first << ", 0), ";
                    eg_queue.emplace_back(rw4.land_queue2[i].first);
                }
            }
            cout << "\n\n";
            print_rwinfo();
        }
        else{//step 4 decide which plane to takeoff or land
            cout << '\n';
            if(eg_queue.size() > 4)stat.crash_plane += eg_queue.size()-4;
            for(int i=0;i<(int)eg_queue.size();i++){
                if(i>=4)break;
                if(i==0)rw1.id_now = eg_queue[i];
                else{
                    if((dc_rwqe+i-1)%3 == 0)rw2.id_now = eg_queue[i];
                    else if((dc_rwqe+i-1)%3 == 1)rw3.id_now = eg_queue[i];
                    else rw4.id_now = eg_queue[i];
                }
            }
            eg_queue.clear();
            
            if(rw1.id_now == -1){
                if(!rw1.tkoff_queue.empty()){
                    rw1.id_now = rw1.tkoff_queue[0];
                    //pop front?
                    for(int i=0;i<(int)rw1.tkoff_queue.size()-1;i++){
                        rw1.tkoff_queue[i]=rw1.tkoff_queue[i+1];
                    }
                    rw1.tkoff_queue.pop_back();
                }
            }
            if(rw2.id_now == -1){
                if(!rw2.land_queue1.empty()){
                    rw2.id_now = rw2.land_queue1[0].first;
                    for(int i=0;i<(int)rw2.land_queue1.size()-1;i++){
                        rw2.land_queue1[i]=rw2.land_queue1[i+1];
                    }
                    rw2.land_queue1.pop_back();
                }
                else if(!rw2.land_queue2.empty()){
                    rw2.id_now = rw2.land_queue2[0].first;
                    for(int i=0;i<(int)rw2.land_queue2.size()-1;i++){
                        rw2.land_queue2[i]=rw2.land_queue2[i+1];
                    }
                    rw2.land_queue2.pop_back();
                }
                else if(!rw2.tkoff_queue.empty()){
                    rw2.id_now = rw2.tkoff_queue[0];
                    for(int i=0;i<(int)rw2.tkoff_queue.size()-1;i++){
                        rw2.tkoff_queue[i]=rw2.tkoff_queue[i+1];    
                    }
                    rw2.tkoff_queue.pop_back();
                }
            }
            if(rw3.id_now == -1){
                if(!rw3.land_queue1.empty()){
                    rw3.id_now = rw3.land_queue1[0].first;
                    for(int i=0;i<(int)rw3.land_queue1.size()-1;i++){
                        rw3.land_queue1[i]=rw3.land_queue1[i+1];
                    }
                    rw3.land_queue1.pop_back();
                }
                else if(!rw3.land_queue2.empty()){
                    rw3.id_now = rw3.land_queue2[0].first;
                    for(int i=0;i<(int)rw3.land_queue2.size()-1;i++){
                        rw3.land_queue2[i]=rw3.land_queue2[i+1];
                    }
                    rw3.land_queue2.pop_back();
                }
                else if(!rw3.tkoff_queue.empty()){
                    rw3.id_now = rw3.tkoff_queue[0];
                    for(int i=0;i<(int)rw3.tkoff_queue.size()-1;i++){
                        rw3.tkoff_queue[i]=rw3.tkoff_queue[i+1];
                    }
                    rw3.tkoff_queue.pop_back();
                }
            }
            if(rw4.id_now == -1){
                if(!rw4.land_queue1.empty()){
                    rw4.id_now = rw4.land_queue1[0].first;
                    for(int i=0;i<(int)rw4.land_queue1.size()-1;i++){
                        rw4.land_queue1[i]=rw4.land_queue1[i+1];
                    }
                    rw4.land_queue1.pop_back();
                }
                else if(!rw4.land_queue2.empty()){
                    rw4.id_now = rw4.land_queue2[0].first;
                    for(int i=0;i<(int)rw4.land_queue2.size()-1;i++){
                        rw4.land_queue2[i]=rw4.land_queue2[i+1];
                    }
                    rw4.land_queue2.pop_back();
                }
                else if(!rw4.tkoff_queue.empty()){
                    rw4.id_now = rw4.tkoff_queue[0];
                    for(int i=0;i<(int)rw4.tkoff_queue.size()-1;i++){
                        rw4.tkoff_queue[i]=rw4.tkoff_queue[i+1];
                    }
                    rw4.tkoff_queue.pop_back();
                }
            }

            //fuel level decrease 
            for(int i=0;i<(int)rw2.land_queue1.size();i++){
                //if(rw2.land_queue1[i].first != rw2.id_now)
                rw2.land_queue1[i].second--;
            }
            for(int i=0;i<(int)rw2.land_queue2.size();i++){
                rw2.land_queue2[i].second--;
            }
            for(int i=0;i<(int)rw3.land_queue1.size();i++){
                rw3.land_queue1[i].second--;
            }
            for(int i=0;i<(int)rw3.land_queue2.size();i++){
                rw3.land_queue2[i].second--;
            }
            for(int i=0;i<(int)rw4.land_queue1.size();i++){
                rw4.land_queue1[i].second--;
            }
            for(int i=0;i<(int)rw4.land_queue2.size();i++){
                rw4.land_queue2[i].second--;
            }
            print_rwinfo();
        }
    }

    void i_output(){
        cout << "Simulation time: 1\n\n";
        for(int t=1;t<=4;t++){
            cout << "Runway" << t << "(-1)\n";
            cout << "L1:\nL2:\nT:\n\n";
        }
    }
};

int main(){
    airport ap;
    ap.i_output();
    ap.run(1);
    ap.run(2);
    ap.run(3);
    ap.run(4);
}