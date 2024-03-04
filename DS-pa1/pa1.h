#include<bits/stdc++.h>

using namespace std;

class printout{
public:
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
};