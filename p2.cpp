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
using namespace std;
#define SystemTime 86400
class car
{
    public:
        car(double carx,double cary);
        car();
        int direction; // dircetion : 0 up 1 right 2 down 3 left
        double x;
        double y;
};
typedef struct Pos
{
    double x;
    double y;
}pos;
car::car(double carx,double cary)
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
}
car::car()  // not use
{
    x = 0;
    y = 0;
    direction = 0;
}
double calGain(pos base,car car){
    double d = sqrt(pow(abs(car.x-base.x),2)+pow(abs(car.y - base.y),2));
    double pathLoss = 32.45 + 20*log10(d);
    return 100.0 - pathLoss;
}

double lambda[3] = {1.0/2.0,1.0/3.0,1.0/5.0};

int main(){
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
    vector<pos>bases;
    bases.resize(4);
    bases[0].x = 330.0;    bases[0].y = 350.0;
    bases[1].x = 640.0;    bases[1].y = 310.0;
    bases[2].x = 360.0;    bases[2].y = 680.0;
    bases[3].x = 660.0;    bases[3].y = 658.0;
    // Do Policy
    vector<car>cars;
    int num_car = 0;
    for(int i=0;i<3;++i){
        cout<<"++++++++++++++++++++++++++\nlambda:"<<lambda[i]<<"\n";
        for(int j=0;j<3;++j){
            cout<<"Second:"<<j<<"\n";
            // cars' move
            // remove cars that arrive out port
            // generate cars
            srand (time(NULL));
            int numberGeneratedCar = 0;
            for(int k=0;k<20;++k){
                double prob = (double)rand() / RAND_MAX; // 0~1
                //cout<<prob<<endl;
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
                cout<<"Random"<<entrypoint<<"\n";
                car tmp(entry[entrypoint].x,entry[entrypoint].y);
                cars.push_back(tmp);
            }
        }
        cout<<"++++++++++++++++++++++++++\n";
    }
    cars.clear();
    return 0;
}