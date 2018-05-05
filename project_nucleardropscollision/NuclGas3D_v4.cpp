// UnNucleon por LeapFrog
#include <iostream>
#include <cmath>
#include <unistd.h>
#include "Vector.h"
#include "Random64.h"
using namespace std;
unsigned int microseconds=100;
const double mAr = 39.948; // Argon mass; nucleon mass, in [u.m.a] --- should it be in u.m.a unities?
const double Dmin = 3.0;   // Maximum distance at which force is present in [Amstrong]
const double Epp = 0.63;    // Energy per particle, in [Kelvin]
const double RanE = 0.01;

const double CHI   =0.1786178958448091;
const double LAMBDA=-0.2123418310626054;
const double XI    =-0.06626458266981849;
const double uno_m2LAMBDA_S2=(1-2*LAMBDA)/2;
const double uno_m2_XIplusCHI=(1-2*(XI+CHI));

const double K=1e4;
const double Lx=100, Ly=100, Lz=100;
const int Nx=6, Ny=6, Nz=6; const int N=Nx*Ny*Nz;

const bool gnuplot=true;

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
  void Dibujese(double t, int i, double eppp);
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
void Cuerpo::Dibujese(double t, int i, double eppp){
  if(i==1)
    cout<<", "<<r.y()<<"+"<<R<<"*cos(t),"<<r.z()<<"+"<<R<<"*sin(t) w l lw 3 t 'time="<<t<<"'";
  else if(i==2)
    cout<<", "<<r.y()<<"+"<<R<<"*cos(t),"<<r.z()<<"+"<<R<<"*sin(t) w l lw 3 t 'eppp="<<eppp<<"'";
  else
    cout<<", "<<r.y()<<"+"<<R<<"*cos(t),"<<r.z()<<"+"<<R<<"*sin(t) w l lw 3 notitle";
}
//-----------------------Clase colisionador---------------------------------//
class Colisionador{
private:
  double ParIz, ParDr, ParAb, ParAr, ParAt, ParAd;
public:
  void CalculeTodasLasFuerzas(Cuerpo * Nucleon);
  void CalculeFuerzaEntre(Cuerpo & Nucleon1, Cuerpo & Nucleon2);
  void CalculeFuerzaContenedor(Cuerpo & Nucleon1, Cuerpo & Nucleon2);
  void ReduzcaParedes(Cuerpo * Nucleon, double desp, double ParIz, double ParDr, double ParAb, double ParAr, double ParAt, double ParAd);
  double CalculeEnergiaCineticaTotal(Cuerpo * Nucleon);
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
double Colisionador::CalculeEnergiaCineticaTotal(Cuerpo * Nucleon){
  double ECT=0;
  int i;
  for(i=0;i<N;i++)
    ECT+=0.5*Nucleon[i].m*norma2(Nucleon[i].V);
  return ECT;
}
void Colisionador::ReduzcaParedes(Cuerpo * Nucleon, double desp, double ParIz, double ParDr, double ParAb, double ParAr, double ParAt, double ParAd){
  Nucleon[N  ].Inicie(ParIz,0    ,0    ,0,0,0,1,10000);
  Nucleon[N+1].Inicie(ParDr,0    ,0    ,0,0,0,1,10000);
  Nucleon[N+2].Inicie(0    ,ParAb,0    ,0,0,0,1,10000);  
  Nucleon[N+3].Inicie(0    ,ParAr,0    ,0,0,0,1,10000);
  Nucleon[N+4].Inicie(0    ,0    ,ParAt,0,0,0,1,10000);
  Nucleon[N+5].Inicie(0    ,0    ,ParAd,0,0,0,1,10000);
}
//-------------------------------------
void InicieAnimacion(void){
  //  cout<<"set terminal gif animate"<<endl; 
  //  cout<<"set output 'MiBalon.gif'"<<endl;
  cout<<"set grid"<<endl;
  cout<<"set xrange [-20:20]"<<endl;
  cout<<"set yrange [-20:20]"<<endl;
  cout<<"set size ratio -1"<<endl;
  cout<<"set parametric"<<endl;
  cout<<"set trange [0:7]"<<endl;
  cout<<"set isosamples 12"<<endl;  
}
void InicieCuadro(void){
  cout<<"plot 0,0 notitle";
}
void TermineCuadro(void){
    cout<<endl;
}

int main(void){
  Cuerpo Nucleon[N+6]; int i,ix,iy,iz;
  Colisionador Hertz;
  Crandom ran2(0);
  double t,Deltat=1e-2;
  double tmax,tdibujo; int ndibujos=10000;
  double m0=mAr,R0=0.1;
  double VEL0,Alpha,Beta,dx,dy,dz;
  
  VEL0=sqrt(2*Epp/mAr);

  if(gnuplot==true)
    InicieAnimacion();

  double Lini=20, Lfin=6.41, tredu=200.;
  double xinf=-Lini/2., xsup=Lini/2., yinf= -Lini/2., ysup = Lini/2., zinf=-Lini/2., zsup=Lini/2.;
  
  double rate=((Lini-Lfin)/2.)/tredu;
  double desp, t1, t2, EPPP, razon, tlib;
  double ParIz=xinf-10000, ParDr=xsup+10000, ParAb=yinf-10000, ParAr=ysup+10000, ParAt=zinf-10000, ParAd=zsup+10000;
  t1=25.; t2=75.;
  tlib=250;
  desp=rate*Deltat;

  //-----------------(x0      ,y0      ,z0,Vx0            ,Vy0            ,Vz0,m0,R0);
  //Paredes
  //Pared izq
  Nucleon[N  ].Inicie(ParIz,0    ,0    ,0,0,0,1,10000);
  //Pared drch
  Nucleon[N+1].Inicie(ParDr,0    ,0    ,0,0,0,1,10000);
  //Pared abajo
  Nucleon[N+2].Inicie(0    ,ParAb,0    ,0,0,0,1,10000);  
  //Pared arriba
  Nucleon[N+3].Inicie(0    ,ParAr,0    ,0,0,0,1,10000);
  //Pared atras
  Nucleon[N+4].Inicie(0    ,0    ,ParAt,0,0,0,1,10000);
  //Pared adelante
  Nucleon[N+5].Inicie(0    ,0    ,ParAd,0,0,0,1,10000);

  //Nucleons
  dx=(xsup-xinf)/(Nx+1); dy=(ysup-yinf)/(Ny+1); dz=(zsup-zinf)/(Nz+1);
  for(ix=0;ix<Nx;ix++)
    for(iy=0;iy<Nx;iy++)
      for(iz=0;iz<Nz;iz++){
	Alpha=2*M_PI*ran2.r();
	Beta=(M_PI*ran2.r())-M_PI/2;
	Nucleon[(iz*Nx*Ny)+(iy*Nx)+ix].Inicie(xinf + dx*(ix+1) , yinf + dy*(iy+1) , zinf + dz*(iz+1) , VEL0*cos(Beta)*cos(Alpha),VEL0*cos(Beta)*sin(Alpha),VEL0*sin(Beta),m0,R0);
      }
  
  tmax=6200;
  for(t=0,tdibujo=0;t<tmax;t+=Deltat,tdibujo+=Deltat){
    
    if(gnuplot==true){
    //Animacion
      if(tdibujo>tmax/ndibujos){
	EPPP= Hertz.CalculeEnergiaCineticaTotal(Nucleon)/N;
	InicieCuadro();
	for(i=0;i<N;i++) Nucleon[i].Dibujese(t,i,EPPP);
	TermineCuadro();
	tdibujo=0;
	usleep(microseconds);
      }
    }

    //cout << t << "\t" << Hertz.CalculeEnergiaCineticaTotal(Nucleon)/N << endl;
    
    //------------------------------------------------------------------------------------
    // -------mantener energia promedio por particula en el valor Epp +/- RanE------------
    if( (int(t+1)%5==0) && t<tlib){
      EPPP=Hertz.CalculeEnergiaCineticaTotal(Nucleon)/N;
      if( EPPP > Epp+RanE || EPPP < Epp-RanE ){
	razon=sqrt(Epp/EPPP);
	for(i=0;i<N;i++)
	  Nucleon[i].Inicie(Nucleon[i].Getx(),Nucleon[i].Gety(),Nucleon[i].Getz(),Nucleon[i].GetVx()*razon,Nucleon[i].GetVy()*razon,Nucleon[i].GetVz()*razon,m0,R0);
      }
    }
    //------------------------------------------------------------------------------------
    //---------------------------Reducir paredes------------------------------------------
    if(  (t>1) && (t<tredu)  ){
      ParIz+=desp, ParDr-=desp, ParAb+=desp, ParAr-=desp, ParAt+=desp, ParAd-=desp;
      Hertz.ReduzcaParedes(Nucleon, desp, ParIz, ParDr, ParAb, ParAr, ParAt, ParAd);
    }
    /*
    if(  (t>t2) && (t<t2+25.)  ){
      ParIz+=desp, ParDr-=desp, ParAb+=desp, ParAr-=desp, ParAt+=desp, ParAd-=desp;
      Hertz.ReduzcaParedes(Nucleon, desp, ParIz, ParDr, ParAb, ParAr, ParAt, ParAd);
    }
    */
    //------------------------------------------------------------------------------------
    //------------------------- quitar paredes--------------------------------------------
    if( int(t)==tlib ){
      Nucleon[N  ].Inicie(ParIz,0    ,0    ,0,0,0,1,1);
      Nucleon[N+1].Inicie(ParDr,0    ,0    ,0,0,0,1,1);
      Nucleon[N+2].Inicie(0    ,ParAb,0    ,0,0,0,1,1);  
      Nucleon[N+3].Inicie(0    ,ParAr,0    ,0,0,0,1,1);
      Nucleon[N+4].Inicie(0    ,0    ,ParAt,0,0,0,1,1);
      Nucleon[N+5].Inicie(0    ,0    ,ParAd,0,0,0,1,1);
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
