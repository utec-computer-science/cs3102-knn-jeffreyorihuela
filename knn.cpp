#include <iostream>
#include <vector>
#include <time.h>
#include <chrono>
#include <stdio.h>
#include <unistd.h>
#include <utility>
#include <set>
#include <cmath>
using namespace std;

template<typename T>
struct CartesianCoord {
    typedef T value_t;
    value_t x,y;

    CartesianCoord(value_t _x = 0, value_t _y = 0):x(_x), y(_y) {}

    ~CartesianCoord(void) {}

    template<typename _T>
    friend ostream& operator<<(ostream &out, const CartesianCoord<_T> c) {
        out << "(" << c.x<< " , " << c.y << ")";
        return out;
    }

    template<typename _T>
    const bool operator !=(const CartesianCoord<_T> other) {
        if ( other.x != this->x && other.y != this->y) return true;
        else return false;
    }
};

typedef CartesianCoord<int> coord_t;



vector<coord_t> knn (int k, vector<coord_t> &points, const coord_t &q) {
    struct custom_compare {
        bool operator()(pair<coord_t, double> a, pair<coord_t, double> b) {
            return a.second < b.second;
        }
    };

    set<pair<coord_t,double>, custom_compare> aux;
    
    vector<coord_t>::iterator it = points.begin();
    for(; it != points.end(); it++) {
        if(*it != q) {
            double x = (*it).x - q.x;
            double y = (*it).y - q.y;
            double distance = sqrt(x*x + y*y);
            pair<coord_t, double> a;
            a.first = *it;
            a.second = distance;
            aux.insert(a);
        }
    }

    set<pair<coord_t,double>, custom_compare>::iterator set_it = aux.begin();
    vector<coord_t> answ;
    for (int i = 0; i < k; i++) {
        answ.push_back((*set_it).first);
        set_it++;
    }
    return answ;
}

int main() {
    srand(time(NULL));

    vector<coord_t> points;
    for (int i = 0; i < 1000; i++)
        points.push_back(coord_t(rand()%1000, rand()%1000));

    vector<coord_t>::iterator it = points.begin();

    for(; it != points.end(); it++) {
        fflush(stdout);
        cout << "\r" << *it;
        usleep(2000);
    }

    cout << endl;

    vector<coord_t> knns;
    auto start = chrono::high_resolution_clock::now();
    knns = knn(3, points, coord_t(100, 200));
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop-start);
    cout << "Time: " << endl;
    cout << duration.count() << endl;

    cout << "knns" << endl;
    vector<coord_t>::iterator kit = knns.begin();
    for(; kit != knns.end(); kit ++)
        cout << *kit << endl;
}