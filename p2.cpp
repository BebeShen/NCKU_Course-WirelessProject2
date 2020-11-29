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
// #define SysUnitTime 0.1
#define SysUnitTime 0.04
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
    double d = sqrt(pow(abs(car.x-base.x),2)+pow(abs(car.y - base.y),2));
    double pathLoss = 33.0 + 20.0*log10(d);
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
    d[0] = 33.0 + 20.0*log10(sqrt(pow(abs(x-bases[0].x),2)+pow(abs(y - bases[0].y),2)));d[0] = 100.0-d[0];
    d[1] = 33.0 + 20.0*log10(sqrt(pow(abs(x-bases[1].x),2)+pow(abs(y - bases[1].y),2)));d[1] = 100.0-d[1];
    d[2] = 33.0 + 20.0*log10(sqrt(pow(abs(x-bases[2].x),2)+pow(abs(y - bases[2].y),2)));d[2] = 100.0-d[2];
    d[3] = 33.0 + 20.0*log10(sqrt(pow(abs(x-bases[3].x),2)+pow(abs(y - bases[3].y),2)));d[3] = 100.0-d[3];
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

double lambda[3];

int main(){
    // initailize lambda
    lambda[0] = 1.0-exp(-(1.0/2.0)*SysUnitTime);
    lambda[1] = 1.0-exp(-(1.0/3.0)*SysUnitTime);
    lambda[2] = 1.0-exp(-(1.0/5.0)*SysUnitTime);
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
    char powerfilepath[] = "M_at_15_60.txt";
    double T = 7.4;
    double E = 17.65;
    double M = 23.5;
    // output to file for image
    fstream outFile;
    // fstream powerFile;
    char outputfilepath[] = "data.csv";
    outFile.open(outputfilepath,ios::out);
    for(int p=0;p<4;++p){
        // powerfilepath[5] = p + '0';
        // powerFile.open(powerfilepath,ios::out);
        int handoff[86400] = {0};
        int Power[86400] = {0};
        int num_cars_total = 0;
        double car_power_sec = 0.0;
        double car_power_total = 0.0;
        for(int i=0;i<3;++i){   // lambda
            // reset handoff to 0
            num_cars_total = 0;
            car_power_total = 0.0;
            memset(handoff,0,sizeof(handoff));
            vector<car>cars;
            int num_car = 0, maxG;    // record the number of cars in maze
            double G[4]; // store receive Gain of car with base
            srand (time(NULL));
            for(int j=0;j<SystemTime;++j){ // second(86400)
                car_power_sec = 0.0;
                if(j%10000==0)cout<<j<<"Second"<<"\n";
                // remove cars that arrive out port
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
                // Calculate receive Gain
                // size change with cars , but capacity remain the memory , so capacity must greater or equal than size 
                for(int k=0;k<cars.size();++k){
                    G[0] = calGain(bases.at(0),cars.at(k));
                    G[1] = calGain(bases.at(1),cars.at(k));
                    G[2] = calGain(bases.at(2),cars.at(k));
                    G[3] = calGain(bases.at(3),cars.at(k));
                    maxG = find_max(G);
                    if(p == 0 && cars.at(k).base != maxG){
                        // Best Policy
                        handoff[j]++;
                        cars.at(k).base = maxG;
                    }
                    else if (p == 1 && cars.at(k).base != maxG && G[maxG] > G[cars.at(k).base]+T){
                        // Threshold Policy
                        handoff[j]++;
                        cars.at(k).base = maxG;
                    }
                    else if(p == 2 && cars.at(k).base != maxG && G[cars.at(k).base]<E){
                        // Entropy Policy
                        handoff[j]++;
                        cars.at(k).base = maxG;
                    }
                    else if(p == 3 && cars.at(k).base != maxG && (G[maxG]>M && G[cars.at(k).base]<E)){
                        // My Policy: Next Power Gain larger than M
                        handoff[j]++;
                        cars.at(k).base = maxG;
                    }
                    // store cars' power every sec to calculate mean power
                    car_power_sec += G[cars.at(k).base];
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
                if(num_car>cars.size()){
                    cars.reserve(num_car);
                }
                for(int k=0;k<numberGeneratedCar;++k){
                    // Generate rand formula：int x = rand() % (max - min + 1) + min, min <= x <= max;
                    int entrypoint = rand()%(35 - 0 + 1) + 0;
                    car tmp(entry[entrypoint].x,entry[entrypoint].y);
                    tmp.move();
                    cars.push_back(tmp);
                }
                num_cars_total += num_car;
                car_power_total += car_power_sec;
                // if(j%2000==0)cout<<"number of cars :"<<num_car<<",car's size:"<<cars.size()<<"\n";
            }
            for(int k=0;k<SystemTime-1;++k){
                outFile<<handoff[k]<<",";
            }outFile<<handoff[SystemTime-1]<<"\n";
            // find T & E & M
            // if(p==3){
            //     powerFile<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
            //     powerFile<<"Cars' Power in total:"<<car_power_total<<"\n";
            //     powerFile<<"Number of cars in a day:"<<num_cars_total<<"\n";
            //     powerFile<<"------------------------------------------------------\n";
            //     for(int k=0;k<SystemTime-1;k+=rand()%(1000 - 500 + 1))powerFile<<handoff[k]<<" ";
            //     powerFile<<"\n------------------------------------------------------\n";
            //     powerFile<<"(T = "<<E<<")'s mean Power at lambda["<<i<<"] = Pmin:"<<car_power_total/num_cars_total<<"\n";
            //     powerFile<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
            // }
            cars.clear();
        }
        // powerFile.close();
    }
    outFile.close();
    return 0;
}