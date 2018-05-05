// UnNucleon por LeapFrog
#include <iostream>
#include <cmath>
#include <unistd.h>
#include <vector>
#include "Vector.h"
#include "Random64.h"

using namespace std;
unsigned int microseconds=100;
const double mAr = 39.948; // Argon mass; nucleon mass, in [u.m.a] --- should it be in u.m.a unities?
const double Dmin = 3.0; // Maximum distance at which force is present in [Amstrong]
const double Epp = 0.01; //0.63; // Energy per particle, in [Kelvin]
const double d=1.15; //Constante de separacion de clusters

const double CHI   =0.1786178958448091;
const double LAMBDA=-0.2123418310626054;
const double XI    =-0.06626458266981849;
const double uno_m2LAMBDA_S2=(1-2*LAMBDA)/2;
const double uno_m2_XIplusCHI=(1-2*(XI+CHI));

const double K=1e4;
const double Lx=4, Ly=4;
const int Nx=15, Ny=15; const int N=Nx*Ny;
const bool gnuplot=true;

class Cuerpo;
class Colisionador;
class Cluster;
class ClusterCalculator;
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
  void Dibujese(double t, int i, int NoClusters);
  double Getx(void){return r.x();}; //Funcion inline (macro)
  double Gety(void){return r.y();}; //Funcion inline (macro)
  double Getz(void){return r.z();}; //Funcion inline (macro)
  double GetVx(void){return V.x();}; //Funcion inline (macro)
  double GetVy(void){return V.y();}; //Funcion inline (macro)
  double GetVz(void){return V.z();}; //Funcion inline (macro)
  friend class Colisionador;
  friend class Cluster;
  friend class ClusterCalculator;
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
void Cuerpo::Dibujese(double t, int i, int NoClusters){
  if(i==1)
    cout<<", "<<r.x()<<"+"<<R<<"*cos(t),"<<r.y()<<"+"<<R<<"*sin(t) w l lw 3 t 'time= "<<t<<"'";
  else if(i==2)
    cout<<", "<<r.x()<<"+"<<R<<"*cos(t),"<<r.y()<<"+"<<R<<"*sin(t) w l lw 3 t 'clusters= "<<NoClusters<<"'";
  else
    cout<<", "<<r.x()<<"+"<<R<<"*cos(t),"<<r.y()<<"+"<<R<<"*sin(t) w l lw 3 notitle";
}




//-----------------------Clase colisionador---------------------------------//
//--------------------------------------------------------------------------//
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


//----------------------------------------------
//-------------------Cluster--------------------
//----------------------------------------------
class Cluster{
private:
  vector <Cuerpo > cluster;
public:
  void InicieCluster(Cuerpo Nucleon){cluster.push_back(Nucleon);};
  void Clear(void){ cluster.clear();};
  void AgregueMiembro(Cuerpo Nucleon){cluster.push_back(Nucleon);};
  void BorrarMiembro(int j){cluster.erase (cluster.begin()+ j);};//Borra elemento en la posicion j
  int Size(void){return cluster.size();}; 
  Cuerpo GetElemento(int i){return cluster[i];}; // Empieza desde 0 hasta N-1
  friend class ClusterCalculator;
};
//----------------------------------------------
//---------------ClusterCalculation-------------
//----------------------------------------------
class ClusterCalculator{
private:
public:
  void EvaluarNucleones(Cluster & a, Cluster & aux);
  void DefinirCluster( Cluster & a, Cluster & aux);
  vector<Cluster> DefinirTodosLosClusters(Cluster & a, Cluster & aux);
  int GetNumeroDeClusters( vector<Cluster > CLUSTERS){return CLUSTERS.size();};
  int GetNumeroDeElementosDelCluster(vector<Cluster > CLUSTERS , int i ){return CLUSTERS[i].Size()  ;};
  friend class Cuerpo;
  friend class Cluster;
};

//Un nucleon pregunta ¿Puedo pertenecer a su cluster?
//Este programa hace el primer filtro de bienvenida
void ClusterCalculator::EvaluarNucleones( Cluster & a, Cluster & aux){
  for(int j =0 ; j <   aux.Size() ; j++){
    for(int i = 0 ; i < a.Size() ; i++){
      if(  norma(aux.GetElemento(j).r - a.GetElemento(i).r) < d ){
	a.AgregueMiembro(aux.GetElemento(j));
	aux.BorrarMiembro(j);
	j=j-1;
	break;
      }
    }
  }
}

//Este programa sigue haciendo filtros de bienvenida hasta que se cumple el horario
// Algunos nucleones van tarde (estan lejos) y no son admitidos
void ClusterCalculator::DefinirCluster( Cluster & a, Cluster & aux){
  int before =0 ;
  while( a.Size() > before ){    
    before = a.Size();
    EvaluarNucleones(a, aux);
  }
}

//Pero Hay Fiesta Para todos 
vector<Cluster> ClusterCalculator::DefinirTodosLosClusters(Cluster & a, Cluster & aux){
  vector<Cluster > CLUSTERS ;
  while( aux.Size() > 0){
    a.AgregueMiembro(aux.GetElemento(0));
    aux.BorrarMiembro(0);
    DefinirCluster(a, aux);
    CLUSTERS.push_back(a);
    a.Clear();    
  }
  return CLUSTERS;
}
//----------------Animacion-------------
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
}
void TermineCuadro(void){
    cout<<endl;
}

//------------------Main----------------
//--------------------------------------

int main(void){
  Cuerpo Nucleon[N+4]; int i,ix,iy;
  Colisionador Hertz;
  Crandom ran2(0);
  double t,Deltat=1e-1;
  double tmax,tdibujo; int ndibujos=5000;
  double m0=mAr,R0=0.1;
  double T,VEL0,Alpha,dx,dy;
  VEL0=sqrt(2*Epp/mAr);
  T=Lx/VEL0;
  bool kapa=false;
 
  //Iniciar Definiciones Cluster
  
  Cluster a, Aux;
  ClusterCalculator PRO;
  int NoClusters=1;

  // vector <Cluster > CLUSTERS = PRO.DefinirTodosLosClusters(a,Aux);
  //cout << PRO.GetNumeroDeClusters( CLUSTERS  ) << endl;
  //cout << PRO.GetNumeroDeElementosDelCluster(  CLUSTERS  , 4 )<<endl;
  //cout << CLUSTERS[4].GetElemento(0).Gety()<<endl;
  
  
  //Posicion de las Paredes
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


  if(gnuplot==true)
    InicieAnimacion();
  
  //Nucleones
  dx=(xsup-xinf)/(Nx+1); dy=(ysup-yinf)/(Ny+1);
  for(ix=0;ix<Nx;ix++)
    for(iy=0;iy<Nx;iy++){
      Alpha=2*M_PI*ran2.r();
      Nucleon[iy*Nx+ix].Inicie(xinf + dx*(ix+1) , yinf + dy*(iy+1) , 0 ,VEL0*cos(Alpha),VEL0*sin(Alpha),  0,m0,R0);
    }


  
  tmax=1000;
  for(t=0,tdibujo=0;t<tmax;t+=Deltat,tdibujo+=Deltat){
    //cout<<Nucleon[0].Getx()<<" "<<Nucleon[0].Gety()<<endl;
    //Animacion

    
    if( int (t) % 10 && kapa == false){
      //kapa=true;
      for(i =0 ; i< N ; i++){ // N
	Aux.InicieCluster(Nucleon[i]); //Se inicia con todos los nucleones excepto el que se escogio como cluster inicial
      }
      vector <Cluster > CLUSTERS = PRO.DefinirTodosLosClusters(a,Aux);
      //cout << PRO.GetNumeroDeClusters( CLUSTERS ) << endl;			      
      //cout << CLUSTERS[4].GetElemento(0).Gety()<<endl;
      NoClusters=PRO.GetNumeroDeClusters( CLUSTERS );
      a.Clear();
      Aux.Clear();
    }
    
    
    if(gnuplot==true){
      if(tdibujo>tmax/ndibujos){
	InicieCuadro();
	for(i=0;i<N;i++) Nucleon[i].Dibujese(t,i,NoClusters);
	TermineCuadro();
	tdibujo=0;
	//usleep(microseconds);
      }
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
