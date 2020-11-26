/**
 * Author：@bebeshen
 * Program Language：c++
 * Description：
 * Compile Command：`g++ p2.cpp -O3 -o p2.exe`
 * Run Command：`./p2.exe`
 * 
 * 
 **/ 
#include<iostream>
#include<vector>
#include<cmath>
#include<ctime>
#include<fstream>
#include<cstring>
#include<algorithm>
using namespace std;
#define SystemTime 86400
class car
{
    public:
        int direction; // dircetion : 0 up 1 right 2 down 3 left
        int base;
        int x;
        int y;
        car(int carx,int cary);
        car();
        int init_base();
        void move();
};
typedef struct Pos
{
    double x;
    double y;
}pos;
vector<pos>bases;
double calGain(pos base,car car){
    double d = sqrt(pow(abs((double)car.x-base.x),2)+pow(abs((double)car.y - base.y),2));
    double pathLoss = 32.45 + 20*log10(d);
    return 100.0 - pathLoss;
}
int find_max(double arr[]){
    double tmp = max(max(max(arr[0],arr[1]),arr[2]),arr[3]);
    if(tmp == arr[0])return 0;
    else if (tmp == arr[1]) return 1;
    else if (tmp == arr[2]) return 2;
    else if (tmp == arr[3]) return 3;
    else return -1;
}
car::car(int carx,int cary)
{
    x = carx;
    y = cary;
    if(x == 0){ // toward right
        direction = 1;
    }
    else if(x == 1000){ // toward left
        direction = 3;
    }
    else if(y == 0){   // toward up
        direction = 0;
    }
    else if(y == 1000){ //toward down
        direction = 2;
    }
    base = init_base();
}
car::car()  // not use
{
    x = 0;
    y = 0;
    direction = 0;
}
int car::init_base(){
    double d[4];
    d[0] = sqrt(pow(abs(x-bases[0].x),2)+pow(abs(y - bases[0].y),2));
    d[1] = sqrt(pow(abs(x-bases[1].x),2)+pow(abs(y - bases[1].y),2));
    d[2] = sqrt(pow(abs(x-bases[2].x),2)+pow(abs(y - bases[2].y),2));
    d[3] = sqrt(pow(abs(x-bases[3].x),2)+pow(abs(y - bases[3].y),2));
    return find_max(d);
}
void car::move(){
    switch (direction)
    {
        case 0: // move up
            y += 10;
            break;
        case 1: // move right
            x += 10;
            break;
        case 2: // move down
            y -= 10;
            break;
        case 3:
            x -= 10;
            break;
        default:
            break;
    }
    // Reorder for prevent turn at init
    if(x%100 == 0 && y%100 == 0){
        double prob = (double)rand() / RAND_MAX;
        if(prob<=0.6){  // toward
            direction = direction;
        }
        else if(prob<=0.8){
            ++direction;    // turn right
        }else{
            --direction;    // turn left
        }
        if(direction<0)direction=3; // up(0) turn left(-1) = left(3)
        if(direction>3)direction=0; // left(3) turn right(+1) = up(0) 
    }
}

double lambda[3] = {1.0/2.0,1.0/3.0,1.0/5.0};

int main(){
    // // output to file for image
    // fstream outFile("data.txt",ios::out);
    // initialize entry
    vector<pos>entry;
    entry.resize(36);
    for (int i = 0; i < 9; ++i)
    {
        entry[i].x = 0.0;
        entry[i].y = ((double)i+1.0)*100.0;
        entry[i+9].x = 1000.0;
        entry[i+9].y = ((double)i+1.0)*100.0;
        entry[i+18].x = ((double)i+1.0)*100.0;
        entry[i+18].y = 0.0;
        entry[i+27].x = ((double)i+1.0)*100.0;
        entry[i+27].y = 1000.0;
    }
    // initialize bases station
    bases.resize(4);
    bases[0].x = 330.0;    bases[0].y = 350.0;
    bases[1].x = 640.0;    bases[1].y = 310.0;
    bases[2].x = 360.0;    bases[2].y = 680.0;
    bases[3].x = 660.0;    bases[3].y = 658.0;
    // Do Policy
    int handoff[86400] = {0};
    for(int i=0;i<1;++i){   // lambda
        // reset handoff to 0
        memset(handoff,0,sizeof(handoff));
        vector<car>cars;
        int num_car = 0, maxG;    // record the number of cars in maze
        double G[4]; // store receive Gain of car with base
        // cout<<"++++++++++++++++++++++++++\nlambda:"<<lambda[i]<<"\n";
        srand (time(NULL));
        for(int j=0;j<500;++j){ // second(86400)
            if(j%1000==0)cout<<"Second:"<<j<<"\n";
            // remove cars that arrive out port
            // Bug here: index out of range by erase
            int num_remove = 0;
            for(int k=num_car-1;k>=0;--k){
                if(cars.at(k).x == 0 || cars.at(k).y == 0 || cars.at(k).x == 1000 || cars.at(k).y == 1000){
                    num_car--;
                    num_remove++;
                    cars.erase(cars.begin()+k);
                }
            }
            // cars' move
            for(int k=0;k<num_car;++k){
                cars.at(k).move();
            }
            // cout<<"number of cars :"<<num_car<<"\ncar's size:"<<cars.size()<<"\n";
            // Calculate receive Gain
            // size change with cars , but capacity remain the memory , so capacity must greater or equal than size 
            for(int k=0;k<cars.size();++k){
                G[0] = calGain(bases.at(0),cars.at(k));
                G[1] = calGain(bases.at(1),cars.at(k));
                G[2] = calGain(bases.at(2),cars.at(k));
                G[3] = calGain(bases.at(3),cars.at(k));
                maxG = find_max(G);
                // Best Policy
                if(cars.at(k).base != maxG){
                    // cout<<cars.at(k).base<<" "<<maxG<<"\n";
                    handoff[j]++;
                    cars.at(k).base = maxG;
                }
            }
            // generate cars
            int numberGeneratedCar = 0;
            for(int k=0;k<1000;++k){    // 1000 ms = 1 s
                double prob = (double)rand() / RAND_MAX; // 0~1
                if(prob<=lambda[i]){
                    ++numberGeneratedCar;
                    ++num_car;
                }
            }
            cout<<"number of cars :"<<num_car<<",car's size:"<<cars.size()<<"\n";
            if(num_car>cars.size()){
                cars.reserve(num_car);
            }
            for(int k=0;k<numberGeneratedCar;++k){
                // Generate rand formula：int x = rand() % (max - min + 1) + min, min <= x <= max;
                int entrypoint = rand()%(35 - 0 + 1) + 0;
                car tmp(entry[entrypoint].x,entry[entrypoint].y);
                // cout<<"generate car:"<<tmp.x<<" "<<tmp.y<<"\n";
                cars.push_back(tmp);
            }
            cout<<"After ,number of cars :"<<num_car<<",car's size:"<<cars.size()<<"\n";
        }
        cars.clear();
    }
    return 0;
}