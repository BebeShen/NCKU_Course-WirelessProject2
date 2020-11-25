#include<iostream>
#include<vector>
#include<cmath>
#include<ctime>
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
class base
{
    public:
        base();
        base(double bx,double by);
        double x;
        double y;
        double power;
        //int getP();
        double calGain(double x,double y);
};
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
base::base(){
    x=0;y=0;
}
base::base(double bx,double by){
    x = bx;
    y = by;
}
double calGain(base base,car car){
    double d = sqrt(pow(abs(car.x-base.x),2)+pow(abs(car.y - base.y),2));
    double pathLoss = 32.45 + 20*log10(d);
    return 100.0 - pathLoss;
}

double lambda[3] = {1.0/2.0,1.0/3.0,1.0/5.0};

int main(){
    int entry_x[9] = {100,200,300,400,500,600,700,800,900}; // y = 0 or 1000
    int entry_y[9] = {100,200,300,400,500,600,700,800,900}; // x = 0 or 1000
    vector<car*>cars;
    int num_car = 0;
    for(int i=0;i<3;++i){
        for(int j=0;j<SystemTime;++j){
            // remove cars that arrive out port : free()
            // generate cars: malloc, realloc 
            srand (time(NULL));
            int numberGeneratedCar = 0;
            for(int k=0;k<1000;++k){
                double prob = (double)rand() / RAND_MAX; // 0~1
                cout<<prob<<endl;
                if(prob<=lambda[i]){
                    ++numberGeneratedCar;
                    ++num_car;
                }
            }
            cars.resize(num_car);
            for(int k=0;k<numberGeneratedCar;++k){
                car* tmp = (car*)malloc(sizeof(car));
                int xORy = rand()%(1-0+1); 
                int entryPoint = rand() % (3 - 0 + 1);
                cars[num_car];
            }
        }
        cout<<"lambda:"<<lambda[i]<<endl;
    }
    return 0;
}