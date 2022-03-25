#include<bits/stdc++.h>
//#include "pa1.h"

using namespace std;

//未將飛機加入queue中
class runway{
public:
    vector<pair<int,int>> land_queue1;
    vector<pair<int,int>> land_queue2;
    vector<int> tkoff_queue;
    int id_now=-1;
    int tt_plane=0;//total plane on runway
};

class airport{
public:
    int land_number,land_id=1,fuel_lv,total=0;
    int tkoff_number,tkoff_id=0,tk_total=0;
    vector<int> eg_queue;
    //vector<pair<int,int>> land_wait;
    runway rw1,rw2,rw3,rw4;

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
    /*vector<pair<int,int>> decide_que(){
        if((int)rw2.land_queue1.size() < total/3 || rw2.land_queue1.size() == 0)return rw2.land_queue1;
        else if((int)rw3.land_queue1.size() < total/3 || rw3.land_queue1.size() == 0)return rw3.land_queue1;
        else if((int)rw4.land_queue1.size() < total/3 || rw4.land_queue1.size() == 0)return rw4.land_queue1;
        else if((int)rw2.land_queue2.size() < total/3 || rw2.land_queue2.size() == 0)return rw2.land_queue2;
        else if((int)rw3.land_queue2.size() < total/3 || rw3.land_queue2.size() == 0)return rw3.land_queue2;
        else if((int)rw4.land_queue2.size() < total/3 || rw4.land_queue2.size() == 0)return rw4.land_queue2;
        else return rw2.land_queue1;
    } doesn't work*/
    void run(int step){
        cout << "Step " << step << '\n';
        if(step==1){//land plane coming
            srand((unsigned)time(NULL));
            land_number = rand()%5;//number of landing plane
            total+=land_number;
            cout << "landing plane:";
            srand((unsigned)time(NULL));
            for(int i=0;i<land_number;i++){
                fuel_lv = rand()%11;
                //land_wait.emplace_back(make_pair(land_id,fuel_lv));
                cout << '(' << land_id << ", " << fuel_lv << "), ";
                if((int)rw2.land_queue1.size() < total/3 || rw2.land_queue1.size() == 0){
                    rw2.land_queue1.emplace_back(make_pair(land_id,fuel_lv));
                    rw2.tt_plane++;
                }
                else if((int)rw3.land_queue1.size() < total/3 || rw3.land_queue1.size() == 0){
                    rw3.land_queue1.emplace_back(make_pair(land_id,fuel_lv));
                    rw3.tt_plane++;
                }
                else if((int)rw4.land_queue1.size() < total/3 || rw4.land_queue1.size() == 0){
                    rw4.land_queue1.emplace_back(make_pair(land_id,fuel_lv));
                    rw4.tt_plane++;
                }
                else if((int)rw2.land_queue2.size() < total/3 || rw2.land_queue2.size() == 0){
                    rw2.land_queue2.emplace_back(make_pair(land_id,fuel_lv));
                    rw2.tt_plane++;
                }
                else if((int)rw3.land_queue2.size() < total/3 || rw3.land_queue2.size() == 0){
                    rw3.land_queue2.emplace_back(make_pair(land_id,fuel_lv));
                    rw3.tt_plane++;
                }
                else if((int)rw4.land_queue2.size() < total/3 || rw4.land_queue2.size() == 0){
                    rw4.land_queue2.emplace_back(make_pair(land_id,fuel_lv));
                    rw4.tt_plane++;
                }
                else rw2.land_queue1.emplace_back(make_pair(land_id,fuel_lv));
                //可能可再改 注意tt_plane及else部分

                land_id+=2;
            }
            cout << "\n\n";
            print_rwinfo();
        }
        else if(step==2){//takeoff plane coming
            srand((unsigned)time(NULL));
            tkoff_number = rand()%5;//number of takeoff plane
            tk_total += tkoff_number;
            cout << "takeoff plane:";
            for(int i=0;i<tkoff_number;i++){
                cout << '(' << tkoff_id << "), ";
                if((int)rw1.tkoff_queue.size() < tk_total/4 || rw1.tt_plane == 0){
                    rw1.tkoff_queue.emplace_back(tkoff_id);
                    rw1.tt_plane++;
                }
                else if((int)rw2.tkoff_queue.size() < tk_total/4 || rw2.tt_plane == 0){
                    rw2.tkoff_queue.emplace_back(tkoff_id);
                    rw2.tt_plane++;
                }
                else if((int)rw3.tkoff_queue.size() < tk_total/4 || rw3.tt_plane == 0){
                    rw3.tkoff_queue.emplace_back(tkoff_id);
                    rw3.tt_plane++;
                }
                else{
                    rw4.tkoff_queue.emplace_back(tkoff_id);
                    rw4.tt_plane++;
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
}