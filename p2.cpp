#include<iostream>
#include<vector>
using namespace std;
class car
{
    public:
        car(double carx,double cary);
        car();
        int direction;
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
        direction = 3;
    }
    else if(x == 1000){ // toward left
        direction = 2;
    }
    else if(y == 0){   // toward up
        direction = 0;
    }
    else if(y == 1000){ //toward down
        direction = 1;
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
double base::calGain(double carx,double cary){
    return 0.0;
}

double lambda[3] = {1.0/2.0,1.0/3.0,1.0/5.0};

int main(){
    
    return 0;
}