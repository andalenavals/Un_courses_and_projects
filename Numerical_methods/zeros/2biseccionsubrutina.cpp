

#include <iostream>
#include <cmath>
using namespace std;

const double Err=1e-7;

double f(double x){
  return sin(x)/x;
}

double CeroPorBiseccion(double a, double b){
  double fa, fb;
  double m, fm;

  fa=f(a);
  fb=f(b);
 
  while((b-a)>Err ){
     m=(a+b)/2.;
     fm=f(m);
     
    if(fa*fm<0){
      b=m;
      fb=fm;
    }
    
    else{
      a=m;
      fa=fm;
    }   
  }

  return (a+b)/2. ;
 
}


int main(void){
  double a=4., b=8.;

  cout<<"El cero esta en x= "<< CeroPorBiseccion( a,  b) << " , y ahi la funcion vale f(x)=" << f( CeroPorBiseccion( a,  b)) <<endl;

  return 0;
}

