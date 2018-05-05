#include <iostream>
#include <cmath>
using namespace std;



double IntegralPorSimpson(double a, double b, int N, double f(double x)){
  double integral;
  double h=(b-a)/N;
  double xi;
  double suma;
  suma=0;
 
  for (int i=0; i<=N; i++){
    xi=a+i*h;
    if((i==0) || (i==N) )
      suma +=f(xi);
    else if(i%2==0)
      suma += 2*f(xi);
    else
      suma += 4*f(xi);
  }
  integral=(h/3.)*suma;
  return integral ;
}

double Integrando(double x){
  return sin(x);
}

int main(void){
  double a=0., b=M_PI;
  int N=10;
  cout << IntegralPorSimpson(a , b, N , Integrando ) << endl;
    
  return 0;
}







/*
for(N=2;N)

Error h vs integral  potencia alta error menor
cuadratura de gauss

 */
