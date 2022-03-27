#include<bits/stdc++.h>
//#include "pa1.h"

using namespace std;

//未將飛機加入queue中
//未處理fuel_lv隨時間減少的情形 當減的時候看到有LV是0便直接捨棄(已墜機或起飛)
class runway{
public:
    vector<pair<int,int>> land_queue1;
    vector<pair<int,int>> land_queue2;
    //priority_queue<pair<int,pair<int,int>>, vector<pair<int,pair<int,int>>>, greater<pair<int,pair<int,int>>> > lq1;
    //(fuel_lv ,land id ,enter land queue time)
    vector<int> tkoff_queue;
    int id_now=-1;
};
class statistic{
public:
    int crash_plane=0, eg_plane=0,time_saved=0;
    int wt_land_tm=0,wt_tkoff_tm=0;//wait time of land and takeoff
    int ald_land=0,ald_tkoff=0;//already land and takeoff
};

class airport{
public:
    int land_number,land_id=1,fuel_lv,land_total=0;
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
    void print_statinfo(){
        cout << "average landing waiting time: " << (double)stat.wt_land_tm/land_total << '\n';
        cout << "average takeoff waiting time: " << (double)stat.wt_tkoff_tm/tk_total << '\n';
        cout << "average fuel saved: " << (double)stat.time_saved/stat.ald_land << '\n';
        cout << "total plane in emergency: " << stat.eg_plane << '\n';
        cout << "total plane crashed: " << stat.crash_plane << '\n';
    }

    void run(int step){
        cout << "Step " << step << '\n';
        if(step==1){//land plane coming
            srand((unsigned)time(NULL));
            land_number = rand()%5;//number of landing plane
            land_total+=land_number;
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
                //可能可再改 注意else部分

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
                if((int)rw1.tkoff_queue.size() < (tk_total-stat.ald_tkoff)/4 +1 || rw1.tkoff_queue.size() == 0){
                    rw1.tkoff_queue.emplace_back(tkoff_id);
                }
                else if(dc_rwqe%3==0){
                    rw2.tkoff_queue.emplace_back(tkoff_id);
                    dc_rwqe++;
                }
                else if(dc_rwqe%3==1){
                    rw3.tkoff_queue.emplace_back(tkoff_id);
                    dc_rwqe++;
                }
                else{
                    rw4.tkoff_queue.emplace_back(tkoff_id);
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
            for(int i=0;i<(int)rw2.land_queue1.size();i++){
                if(rw2.land_queue1[i].second == 0){
                    cout << '(' << rw2.land_queue1[i].first << ", 0), ";
                    eg_queue.emplace_back(rw2.land_queue1[i].first);
                    stat.eg_plane++;
                }
            }
            for(int i=0;i<(int)rw2.land_queue2.size();i++){
                if(rw2.land_queue2[i].second == 0){
                    cout << '(' << rw2.land_queue2[i].first << ", 0), ";
                    eg_queue.emplace_back(rw2.land_queue2[i].first);
                    stat.eg_plane++;
                }
            }
            for(int i=0;i<(int)rw3.land_queue1.size();i++){
                if(rw3.land_queue1[i].second == 0){
                    cout << '(' << rw3.land_queue1[i].first << ", 0), ";
                    eg_queue.emplace_back(rw3.land_queue1[i].first);
                    stat.eg_plane++;
                }
            }
            for(int i=0;i<(int)rw3.land_queue2.size();i++){
                if(rw3.land_queue2[i].second == 0){
                    cout << '(' << rw3.land_queue2[i].first << ", 0), ";
                    eg_queue.emplace_back(rw3.land_queue2[i].first);
                    stat.eg_plane++;
                }
            }
            for(int i=0;i<(int)rw4.land_queue1.size();i++){
                if(rw4.land_queue1[i].second == 0){
                    cout << '(' << rw4.land_queue1[i].first << ", 0), ";
                    eg_queue.emplace_back(rw4.land_queue1[i].first);
                    stat.eg_plane++;
                }
            }
            for(int i=0;i<(int)rw4.land_queue2.size();i++){
                if(rw4.land_queue2[i].second == 0){
                    cout << '(' << rw4.land_queue2[i].first << ", 0), ";
                    eg_queue.emplace_back(rw4.land_queue2[i].first);
                    stat.eg_plane++;
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
                if(i==0){rw1.id_now = eg_queue[i];stat.ald_tkoff++;}
                else{
                    if((dc_rwqe+i-1)%3 == 0){rw2.id_now = eg_queue[i];stat.ald_tkoff++;}
                    else if((dc_rwqe+i-1)%3 == 1){rw3.id_now = eg_queue[i];stat.ald_tkoff++;}
                    else {rw4.id_now = eg_queue[i];stat.ald_tkoff++;}
                }
            }
            //stat.ald_tkoff += min((int)eg_queue.size(),4);
            eg_queue.clear();
            
            if(rw1.id_now == -1){
                if(rw1.tkoff_queue.size()!=0){
                    rw1.id_now = rw1.tkoff_queue[0];
                    stat.ald_tkoff++;
                    //pop front?
                    rw1.tkoff_queue.erase(rw1.tkoff_queue.begin());
                }
            }
            if(rw2.id_now == -1){
                if(rw2.land_queue1.size()!=0){
                    rw2.id_now = rw2.land_queue1[0].first;
                    stat.time_saved += rw2.land_queue1[0].second;
                    stat.ald_land++;
                    rw2.land_queue1.erase(rw2.land_queue1.begin());
                }
                else if(rw2.land_queue2.size()!=0){
                    rw2.id_now = rw2.land_queue2[0].first;
                    stat.time_saved += rw2.land_queue2[0].second;
                    stat.ald_land++;
                    rw2.land_queue2.erase(rw2.land_queue2.begin());
                }
                else if(rw2.tkoff_queue.size()!=0){
                    rw2.id_now = rw2.tkoff_queue[0];
                    stat.ald_tkoff++;
                    rw2.tkoff_queue.erase(rw2.tkoff_queue.begin());
                }
            }
            if(rw3.id_now == -1){
                if(rw3.land_queue1.size()!=0){
                    rw3.id_now = rw3.land_queue1[0].first;
                    stat.time_saved += rw3.land_queue1[0].second;
                    stat.ald_land++;
                    rw3.land_queue1.erase(rw3.land_queue1.begin());
                }
                else if(rw3.land_queue2.size()!=0){
                    rw3.id_now = rw3.land_queue2[0].first;
                    stat.time_saved += rw3.land_queue2[0].second;
                    stat.ald_land++;
                    rw3.land_queue2.erase(rw3.land_queue2.begin());
                }
                else if(rw3.tkoff_queue.size()!=0){
                    rw3.id_now = rw3.tkoff_queue[0];
                    stat.ald_tkoff++;
                    rw3.tkoff_queue.erase(rw3.tkoff_queue.begin());
                }
            }
            if(rw4.id_now == -1){
                if(rw4.land_queue1.size()!=0){
                    rw4.id_now = rw4.land_queue1[0].first;
                    stat.time_saved += rw4.land_queue1[0].second;
                    stat.ald_land++;
                    rw4.land_queue1.erase(rw4.land_queue1.begin());
                }
                else if(rw4.land_queue2.size()!=0){
                    rw4.id_now = rw4.land_queue2[0].first;
                    stat.time_saved += rw4.land_queue2[0].second;
                    stat.ald_land++;
                    rw4.land_queue2.erase(rw4.land_queue2.begin());
                }
                else if(rw4.tkoff_queue.size()!=0){
                    rw4.id_now = rw4.tkoff_queue[0];
                    stat.ald_tkoff++;
                    rw4.tkoff_queue.erase(rw4.tkoff_queue.begin());
                }
            }
            stat.wt_land_tm = stat.wt_land_tm + land_total - stat.ald_land;
            stat.wt_tkoff_tm = stat.wt_tkoff_tm + tk_total - stat.ald_tkoff;

            //fuel level decrease and delete planes whose fuel lv=0
            for(int i=0;i<(int)rw2.land_queue1.size();i++){
                //if(rw2.land_queue1[i].first != rw2.id_now)
                if(rw2.land_queue1[i].second == 0)rw2.land_queue1.erase(rw2.land_queue1.begin()+i);
                else rw2.land_queue1[i].second--;
            }
            for(int i=0;i<(int)rw2.land_queue2.size();i++){
                if(rw2.land_queue2[i].second == 0)rw2.land_queue2.erase(rw2.land_queue2.begin()+i);
                else rw2.land_queue2[i].second--;
            }
            for(int i=0;i<(int)rw3.land_queue1.size();i++){
                if(rw3.land_queue1[i].second == 0)rw3.land_queue1.erase(rw3.land_queue1.begin()+i);
                else rw3.land_queue1[i].second--;
            }
            for(int i=0;i<(int)rw3.land_queue2.size();i++){
                if(rw3.land_queue2[i].second == 0)rw3.land_queue2.erase(rw3.land_queue2.begin()+i);
                else rw3.land_queue2[i].second--;
            }
            for(int i=0;i<(int)rw4.land_queue1.size();i++){
                if(rw4.land_queue1[i].second == 0)rw4.land_queue1.erase(rw4.land_queue1.begin()+i);
                else rw4.land_queue1[i].second--;
            }
            for(int i=0;i<(int)rw4.land_queue2.size();i++){
                if(rw4.land_queue2[i].second == 0)rw4.land_queue2.erase(rw4.land_queue2.begin()+i);
                else rw4.land_queue2[i].second--;
            }
            print_rwinfo();
        }
    }

    void i_output(int T){
        cout << "Simulation time: " << T << "\n\n";
        rw1.id_now = -1;
        rw2.id_now = -1;
        rw3.id_now = -1;
        rw4.id_now = -1;
        print_rwinfo();
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    airport ap;
    int simu_time=500;
    bool b=true;
    cout << "How many time unit you want to simulate: " << simu_time << '\n';
    for(int t=1;t<=simu_time;t++){
        ap.i_output(t);
        ap.run(1);
        ap.run(2);
        ap.run(3);
        ap.run(4);
        if(ap.tk_total < ap.stat.ald_tkoff){
            b=false;
        }
    }
    cout << "How many time unit you simulate: " << simu_time << '\n';
    ap.print_statinfo();
    if(!b)cout << "WTF!!!\n";
}