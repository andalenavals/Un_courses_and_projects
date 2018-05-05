// UnNucleon por LeapFrog
#include <iostream>
#include <cmath>
#include <unistd.h>
#include "Vector.h"
#include "Random64.h"
using namespace std;
unsigned int microseconds=100;
const double mAr = 39.948; // Argon mass; nucleon mass, in [u.m.a] --- should it be in u.m.a unities?
const double Dmin = 3.0; // Maximum distance at which force is present in [Amstrong]
const double Epp = 0.63; // Energy per particle, in [Kelvin]

const double CHI   =0.1786178958448091;
const double LAMBDA=-0.2123418310626054;
const double XI    =-0.06626458266981849;
const double uno_m2LAMBDA_S2=(1-2*LAMBDA)/2;
const double uno_m2_XIplusCHI=(1-2*(XI+CHI));

const double K=1e4;
const double Lx=4, Ly=4;
const int Nx=15, Ny=15; const int N=Nx*Ny;

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
  void Dibujese(double t, int i);
  double Getx(void){return r.x();}; //Funcion inline (macro)
  double Gety(void){return r.y();}; //Funcion inline (macro)
  double Getz(void){return r.z();}; //Funcion inline (macro)
  double GetVx(void){return V.x();}; //Funcion inline (macro)
  double GetVy(void){return V.y();}; //Funcion inline (macro)
  double GetVz(void){return V.z();}; //Funcion inline (macro)
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
void Cuerpo::Dibujese(double t, int i){
  if(i==1)
    cout<<", "<<r.x()<<"+"<<R<<"*cos(t),"<<r.y()<<"+"<<R<<"*sin(t) w l lw 3 t 'time="<<t<<"'";
  else
    cout<<", "<<r.x()<<"+"<<R<<"*cos(t),"<<r.y()<<"+"<<R<<"*sin(t) w l lw 3 notitle";
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
  for(i=0;i<N+4;i++)
    Nucleon[i].BorreFuerza();
  //Hacer todas las parejas de todos
  for(i=0;i<N;i++)
    for(j=i+1;j<N;j++)
      CalculeFuerzaEntre(Nucleon[i],Nucleon[j]);
  //Fuerzas del contenedor
  for(i=0;i<N;i++)
    for(j=N;j<N+4;j++)
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
  //  cout<<"set terminal gif animate"<<endl; 
  //  cout<<"set output 'MiBalon.gif'"<<endl;
  cout<<"set grid"<<endl;
  cout<<"set xrange [-15:15]"<<endl;
  cout<<"set yrange [-15:15]"<<endl;
  cout<<"set size ratio -1"<<endl;
  cout<<"set parametric"<<endl;
  cout<<"set trange [0:7]"<<endl;
  cout<<"set isosamples 12"<<endl;  
}
void InicieCuadro(void){
  cout<<"plot 0,0 notitle";
  //    cout<<" , "<<100/7<<"*t,-9"; //pared abajo
  //    cout<<" , "<<100/7<<"*t,100";
  //    cout<<" , 0,"<<100/7<<"*t";
  //    cout<<" , 100,"<<100/7<<"*t";
}
void TermineCuadro(void){
    cout<<endl;
}

int main(void){
  Cuerpo Nucleon[N+4]; int i,ix,iy;
  Colisionador Hertz;
  Crandom ran2(0);
  double t,Deltat=1e-2;
  double tmax,tdibujo; int ndibujos=5000;
  double m0=mAr,R0=0.1;
  double T,VEL0,Alpha,dx,dy;

  VEL0=sqrt(2*Epp/mAr);
  T=Lx/VEL0;

  InicieAnimacion();
  
  double xinf=-15 , xsup=15 , yinf= -15, ysup = 15;

  //-------------(x0  ,y0  ,z0,Vx0            ,Vy0            ,Vz0,m0,R0);
  //Paredes
  //Pared izq
  Nucleon[N].Inicie(-10000+xinf, 0 ,0,0,0,0,1,10000);
  //Pared drch
  Nucleon[N+1].Inicie(10000 +xsup, 0,0,0,0,0,1,10000);
  //Pared abajo
  Nucleon[N+2].Inicie( 0,-10000 +yinf,0,0,0,0,1,10000);  
  //Pared arriba
  Nucleon[N+3].Inicie(0,10000 + ysup,0,0,0,0,1,10000);




  
  //Nucleones
  dx=(xsup-xinf)/(Nx+1); dy=(ysup-yinf)/(Ny+1);
  for(ix=0;ix<Nx;ix++)
    for(iy=0;iy<Nx;iy++){
      Alpha=2*M_PI*ran2.r();
      Nucleon[iy*Nx+ix].Inicie(xinf + dx*(ix+1) , yinf + dy*(iy+1) , 0 ,VEL0*cos(Alpha),VEL0*sin(Alpha),  0,m0,R0);
    }

  
  tmax=500;
  for(t=0,tdibujo=0;t<tmax;t+=Deltat,tdibujo+=Deltat){
    //cout<<Nucleon[0].Getx()<<" "<<Nucleon[0].Gety()<<endl;
    //Animacion
    
    if(tdibujo>tmax/ndibujos){
      InicieCuadro();
      for(i=0;i<N;i++) Nucleon[i].Dibujese(t,i);
      TermineCuadro();
      tdibujo=0;
      //usleep(microseconds);
    }
    
    //Reducir energia
    if(int(t)>1)
      if(int(t)%20==0)
	for(i=0;i<N;i++) Nucleon[i].Inicie( Nucleon[i].Getx(), Nucleon[i].Gety(), Nucleon[i].Getz(),0,0,0,m0,R0);

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
