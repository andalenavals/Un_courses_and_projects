// UnPlaneta por LeapFrog
#include <iostream>
#include <cmath>
#include "Vector.h"
using namespace std;

const double G=1.0;
const double CHI   =0.1786178958448091;
const double LAMBDA=-0.2123418310626054;
const double XI    =-0.06626458266981849;
const double uno_m2LAMBDA_S2=(1-2*LAMBDA)/2;
const double uno_m2_XIplusCHI=(1-2*(XI+CHI));
const int N=2;


class Cuerpo;
class Colisionador;

class Cuerpo{
private:
  vector3D r, V, F;
  double m, R;
public:
  void Inicie(double x0,double y0,double z0, double Vx0,double Vy0,double Vz0, double m0,double R0);
  void BorreFuerza(void);
  void AdicioneFuerza(vector3D F0);
  void Mueva_r(double dt,double CTE);
  void Mueva_V(double dt,double CTE);
  void Dibujese(void);
  double Getx(void){return r.x();}; //Funcion inline (macro)
  double Gety(void){return r.y();}; //Funcion inline (macro)
  double Getz(void){return r.z();}; //Funcion inline (macro)
  friend class Colisionador;
};
void Cuerpo::Inicie(double x0,double y0,double z0, double Vx0,double Vy0,double Vz0, double m0,double R0){
  r.cargue(x0,y0,z0);
  V.cargue(Vx0,Vy0,Vz0);
  m=m0;  R=R0;
}
void Cuerpo::BorreFuerza(void){
  F.cargue(0,0,0);
}

void Cuerpo::AdicioneFuerza(vector3D F0){
  F+=F0;
}

void Cuerpo::Mueva_r(double dt,double CTE){
  r+=V*(CTE*dt);
}
void Cuerpo::Mueva_V(double dt,double CTE){
  V+=F*(CTE*dt/m);
}
void Cuerpo::Dibujese(void){
  cout<<", "<<r.x()<<"+"<<R<<"*cos(t),"<<r.y()<<"+"<<R<<"*sin(t)";
}


class Colisionador{
private:
public:
  void CalculeTodasLasFuerzas(Cuerpo * Planeta);
  void CalculeFuerzaEntre(Cuerpo & Planeta1, Cuerpo & Planeta2);
};
void Colisionador::CalculeTodasLasFuerzas(Cuerpo * Planeta){
  int i, j;
  // Borrar las fuerzas de todos los planetas
  for(i=0 ; i<N; i++)
    Planeta[i].BorreFuerza();
  //Hacer todas las parejas entre planetas y calcular la fuerza en cada pareja
  for(i=0; i<N ; i++)
    for(j=0; j<i; j++)
      CalculeFuerzaEntre(Planeta[i], Planeta[j]);

}
void Colisionador::CalculeFuerzaEntre(Cuerpo & Planeta1, Cuerpo & Planeta2){
  vector3D dr = Planeta2.r -Planeta1.r;
  double aux=-G*Planeta1.m*Planeta2.m*pow(norma2(dr), -1.5);
  vector3D F2=dr*aux;
  Planeta2.AdicioneFuerza(F2);   Planeta1.AdicioneFuerza(F2*(-1));

}


void InicieAnimacion(void){
  //  cout<<"set terminal gif animate"<<endl; 
  //  cout<<"set output 'MiBalon.gif'"<<endl;
  cout<<"unset key"<<endl;
  cout<<"set xrange [-22:22]"<<endl;
  cout<<"set yrange [-22:22]"<<endl;
  cout<<"set size ratio -1"<<endl;
  cout<<"set parametric"<<endl;
  cout<<"set trange [0:7]"<<endl;
  cout<<"set isosamples 12"<<endl;  
}
void InicieCuadro(void){
    cout<<"plot 0,0 ";
}
void TermineCuadro(void){
    cout<<endl;
}








int main(void){
  Cuerpo Planeta[N]; 
  int i;
  Colisionador GravedadDeNewton;
  double t,Deltat=0.5;
  double r=20, m0=10 , m1=1 ; 
  double M=m0+m1;
  double omega=sqrt(G*M/(r*r*r));
  double T=2*M_PI/omega;
  double x0=-m1*r/M ,  x1=r+x0 ;
  double tmax = 5.0*T;
  double tdibujo;
  double V0= 1.0*omega*x0, V1= 1.0*omega*x1 ;
  int ndibujos=10000;



  InicieAnimacion();

  //------------(x0,y0,z0,Vx0,    Vy0,Vz0,m0   ,R0);
  Planeta[0].Inicie(x0 ,0 ,0 ,  0, V0 ,  0 , m0  , 3 );
  Planeta[1].Inicie(x1 ,0 ,0 ,  0, V1 ,  0 , m1  , 1 );

  for(t=0,tdibujo=0;t<tmax;t+=Deltat,tdibujo+=Deltat){ 
    //Animacion
    
    //cout<<Planeta[1].Getx() <<" " << Planeta[1].Gety()<<endl;
    
    if(tdibujo>tmax/ndibujos){
      InicieCuadro();
      for(i=0; i<N; i++) Planeta[i].Dibujese();
      TermineCuadro();
      tdibujo=0;
    }
    

    for(i=0; i< N; i++) Planeta[i].Mueva_r(Deltat,CHI);
    GravedadDeNewton.CalculeTodasLasFuerzas(Planeta);  for(i=0; i< N; i++) Planeta[i].Mueva_V(Deltat,uno_m2LAMBDA_S2);
    for(i=0; i< N; i++) Planeta[i].Mueva_r(Deltat,XI);
    GravedadDeNewton.CalculeTodasLasFuerzas(Planeta); for(i=0; i< N; i++) Planeta[i].Mueva_V(Deltat,LAMBDA); 
    for(i=0; i< N; i++) Planeta[i].Mueva_r(Deltat,uno_m2_XIplusCHI);
    GravedadDeNewton.CalculeTodasLasFuerzas(Planeta); for(i=0; i< N; i++) Planeta[i].Mueva_V(Deltat,LAMBDA); 
    for(i=0; i< N; i++)  Planeta[i].Mueva_r(Deltat,XI);
    GravedadDeNewton.CalculeTodasLasFuerzas(Planeta); for(i=0; i< N; i++) Planeta[i].Mueva_V(Deltat,uno_m2LAMBDA_S2);
    for(i=0; i< N; i++) Planeta[i].Mueva_r(Deltat,CHI);

  }


  return 0;
}
