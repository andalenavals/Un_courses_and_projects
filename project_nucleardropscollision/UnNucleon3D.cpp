// 
#include <iostream>
#include <cmath>
#include <unistd.h>
#include "Vector.h"
using namespace std;
unsigned int microseconds=100;

const double CHI   =0.1786178958448091;
const double LAMBDA=-0.2123418310626054;
const double XI    =-0.06626458266981849;
const double uno_m2LAMBDA_S2=(1-2*LAMBDA)/2;
const double uno_m2_XIplusCHI=(1-2*(XI+CHI));

const double mAr = 39.948; // Argon mass; nucleon mass, in [u.m.a] --- should it be in u.m.a unities?
const double Dmin = 3.0; // Maximum distance at which force is present in [Amstrong]
const double Epp = 0.63; // Energy per particle, in [Kelvin]
const double K=1e4;
const double Lx=100, Ly=100, Lz=100;
const int N=1;
//const int Nx=5, Ny=5; const int N=Nx*Ny;


class Cuerpo;
class Colisionador;
//----------------------------Clase cuepo-------------------------------------//
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
  double GetFx(void){return F.x();}; //Funcion inline (macro)
  double GetFy(void){return F.y();}; //Funcion inline (macro)
  double GetFz(void){return F.z();}; //Funcion inline (macro)
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
  cout<<", "<<r.x()<<"+"<<R<<"*cos(v)*cos(u),"<<r.y()<<"+"<<R<<"*cos(v)*sin(u),"<<r.z()<<"+"<<R<<"*sin(v)";
}
//-----------------------Clase colisionador---------------------------------//
class Colisionador{
private:
public:
  void CalculeTodasLasFuerzas(Cuerpo * Nucleon);
  void CalculeFuerzaEntre(Cuerpo & Nucleon1, Cuerpo & Nucleon2);
  void CalculeFuerzaContenedor(Cuerpo & Nucleon1, Cuerpo & Nucleon2);
};
void Colisionador::CalculeTodasLasFuerzas(Cuerpo * Nucleon){
  int i,j;
  //Borrar las fuerzas de todos los planetas
  for(i=0;i<N+6;i++)
    Nucleon[i].BorreFuerza();
  //Hacer todas las parejas de todos
  for(i=0;i<N;i++)
    for(j=i+1;j<N;j++)
      CalculeFuerzaEntre(Nucleon[i],Nucleon[j]);
  //Fuerzas del contenedor
  for(i=0;i<N;i++)
    for(j=N;j<N+6;j++)
      CalculeFuerzaContenedor(Nucleon[i],Nucleon[j]);
}
void Colisionador::CalculeFuerzaEntre(Cuerpo & Nucleon1, Cuerpo & Nucleon2){
  vector3D r21,n,F2;
  double d21,Fn;
  r21=Nucleon2.r-Nucleon1.r; d21=norma(r21);
  if(d21<Dmin){
    Fn=24*( 2*pow(d21,-13) - pow(d21,-7) ); n=r21/d21; F2=n*Fn;
    Nucleon2.AdicioneFuerza(F2);  Nucleon1.AdicioneFuerza(F2*(-1));
  }
}
void Colisionador::CalculeFuerzaContenedor(Cuerpo & Nucleon1, Cuerpo & Nucleon2){
  vector3D r21,n,F2;
  double d21,h,Fn;
  r21=Nucleon2.r-Nucleon1.r; d21=norma(r21); h=(Nucleon2.R+Nucleon1.R)-d21;
  if(h>0){
    Fn=K*pow(h,1.5); n=r21/d21; F2=n*Fn;
    Nucleon2.AdicioneFuerza(F2);  Nucleon1.AdicioneFuerza(F2*(-1));
  }
}
//-------------------------------------
void InicieAnimacion(void){
  cout<<"unset key"<<endl;
  cout<<"unset xtics"<<endl;
  cout<<"unset ytics"<<endl;
  cout<<"unset ztics"<<endl;
  cout<<"set xrange [-10:110]"<<endl;
  cout<<"set yrange [-10:110]"<<endl;
  cout<<"set zrange [-10:110]"<<endl;
  cout<<"set parametric"<<endl;
  
  cout<<"set cbrange [0.9:1]"<<endl;
  cout<<"set ticslevel 0"<<endl;
  cout<<"unset colorbox"<<endl;
  cout<<"set urange [0:2*pi]"<<endl;
  cout<<"set vrange [-pi/2:pi/2]"<<endl;
  cout<<"set isosamples 10,9"<<endl;
  cout<<"set view equal xyz"<<endl;

}
void InicieCuadro3D(void){
    cout<<"splot 'cube.txt' u 1:2:3:(1) w l lc 8";
}
void InicieCuadro(void){
    cout<<"plot 0,0 ";
    cout<<" , "<<100/7<<"*t,0";
    cout<<" , "<<100/7<<"*t,100";
    cout<<" , 0,"<<100/7<<"*t";
    cout<<" , 100,"<<100/7<<"*t";
}
void TermineCuadro(void){
    cout<<endl;
}


int main(void){
  Cuerpo Nucleon[N+6]; int i;
  Colisionador Hertz;
  double t,Deltat=1e-2;
  double tmax,tdibujo; int ndibujos=1000;
  double m0=mAr,R0=3;
  double T,VEL0=sqrt(2*Epp/mAr),Alpha=M_PI/3;

  T=Lx/VEL0;

  tmax=10*T;

  

  InicieAnimacion();

  //----------- -----(x0  ,y0  ,z0,Vx0            ,Vy0            ,Vz0,m0,R0);
  //Paredes
  //Pared izq
  Nucleon[N].Inicie(-10000,Ly/2,0,0,0,0,1,10000);
  //Pared drch
  Nucleon[N+1].Inicie(Lx+10000,Ly/2,0,0,0,0,1,10000);
  //Pared abajo
  Nucleon[N+2].Inicie(Lx/2,-10000,0,0,0,0,1,10000);  
  //Pared arriba
  Nucleon[N+3].Inicie(Lx/2,Ly+10000,0,0,0,0,1,10000);
  //Pared adelante
  Nucleon[N+4].Inicie(Lx/2    ,Ly/2    ,Lz+10000,0,0,0,1,10000);
  //Pared atras
  Nucleon[N+5].Inicie(Lx/2    ,Ly/2    ,-10000  ,0,0,0,1,10000);
  
  //Nucleons
  //---------------(x0  ,y0  ,z0   ,Vx0            ,Vy0            ,Vz0            ,m0,R0);
  Nucleon[0].Inicie(Lx/2,Ly/2,Lz/2 ,VEL0*1,VEL0*2,VEL0*3,m0,R0);
  //Nucleon[1].Inicie(4*Lx/5,Ly/2,0 ,-VEL0,0  ,  0,m0,R0);
  for(t=0,tdibujo=0;t<tmax;t+=Deltat,tdibujo+=Deltat){
    //cout<<Nucleon[0].Getx()<<" "<<Nucleon[0].Gety()<<endl;
    
    //Animacion
    
    if(tdibujo>tmax/ndibujos){
     InicieCuadro3D();
     for(i=0;i<N;i++) Nucleon[i].Dibujese();
     TermineCuadro();
     tdibujo=0;
     usleep(microseconds);
    }
    
    for(i=0;i<N;i++) Nucleon[i].Mueva_r(Deltat,CHI);
    Hertz.CalculeTodasLasFuerzas(Nucleon); for(i=0;i<N;i++) Nucleon[i].Mueva_V(Deltat,uno_m2LAMBDA_S2);
    for(i=0;i<N;i++) Nucleon[i].Mueva_r(Deltat,XI);
    Hertz.CalculeTodasLasFuerzas(Nucleon); for(i=0;i<N;i++) Nucleon[i].Mueva_V(Deltat,LAMBDA); 
    for(i=0;i<N;i++) Nucleon[i].Mueva_r(Deltat,uno_m2_XIplusCHI);
    Hertz.CalculeTodasLasFuerzas(Nucleon); for(i=0;i<N;i++) Nucleon[i].Mueva_V(Deltat,LAMBDA); 
    for(i=0;i<N;i++) Nucleon[i].Mueva_r(Deltat,XI);
    Hertz.CalculeTodasLasFuerzas(Nucleon); for(i=0;i<N;i++) Nucleon[i].Mueva_V(Deltat,uno_m2LAMBDA_S2);
    for(i=0;i<N;i++) Nucleon[i].Mueva_r(Deltat,CHI);
  }
  return 0;
}
