#include <iostream> //define cout
#include <cmath>
using namespace std;//using directive
//or 
using std::cout;
using std::cin;

double power(double base, int expo){
    double result=1;
    for(int i =0; i<expo; i++){
        result =result*base;
    }

    return result;
}
void keplers(){
//there is no response heree. It is a void function
//also for every output given epsilon and paramters we can loop through the reccursion index k 

}
void print_pow(double base, int expo){
    
    double Mypower= power(base, expo);
    cout<< base<<" raised to the "<< expo<< " power is: "<<Mypower<<std::endl;
}
int main(){
    char x= 'A';
    cout<<(int)x<<endl;
}

//take note of the array and vector implementation
