// UnNucleon por LeapFrog
#include <iostream>
#include <cmath>
#include <unistd.h>
#include <vector>
#include "Vector.h"
#include "Random64.h"
using namespace std;
unsigned int microseconds=100;
const double Uext=4*(pow(3,-12)-pow(3,-6));
const double mAr = 39.948; // Argon mass; nucleon mass, in [u.m.a] --- should it be in u.m.a unities?
const double Dmin = 3.0;   // Maximum distance at which force is present in [Amstrong]
const double EppA = 0.6;    // Energy per particle, in [Kelvin]
const double RanEA = 0.01;
const double EppB = 0.8;    // Energy per particle, in [Kelvin]
const double RanEB = 0.01;
const double d=3; //Constante de separacion de clusters
const double densidad= 0.82; //Densidad
const double separac=50;


const double CHI   =0.1786178958448091;
const double LAMBDA=-0.2123418310626054;
const double XI    =-0.06626458266981849;
const double uno_m2LAMBDA_S2=(1-2*LAMBDA)/2;
const double uno_m2_XIplusCHI=(1-2*(XI+CHI));

const double K=1e4;
const int Nx=6, Ny=6, Nz=6; const int N=Nx*Ny*Nz;
const int Mx=6, My=6, Mz=6; const int M=Mx*My*Mz;
const double tredu=30; //Tiempo de compresion de paredes de 0
const double tlib=40; //Instante en el que se libre

const bool gnuplot=true;

class Cuerpo;
class Colisionador;
class Cluster;
class ClusterCalculator;

//-------------------------------------------------------------------------------------
//-------------------------------------CLASE CUERPO------------------------------------
//-------------------------------------------------------------------------------------

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
  void Dibujese(double t, int i, double eppp, int NoClusters, double Ecppp);
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
void Cuerpo::Dibujese(double t, int i, double epppa, int NoClusters, double epppb){
  if(i==0)
    cout<<", "<<r.x()<<"+"<<R<<"*cos(t),"<<r.y()<<"+"<<R<<"*sin(t) w l lw 3 t 'time="<<t<<"'";
  else if(i==1)
    cout<<", "<<r.x()<<"+"<<R<<"*cos(t),"<<r.y()<<"+"<<R<<"*sin(t) w l lw 3 t 'Et/pA="<<epppa<<"'";
  else if(i==2)
    cout<<", "<<r.x()<<"+"<<R<<"*cos(t),"<<r.y()<<"+"<<R<<"*sin(t) w l lw 3 t 'Et/pB= "<<epppb<<"'";
  else if(i==3)
    cout<<", "<<r.x()<<"+"<<R<<"*cos(t),"<<r.y()<<"+"<<R<<"*sin(t) w l lw 3 t 'clusters= "<<NoClusters<<"'";
  else
    cout<<", "<<r.x()<<"+"<<R<<"*cos(t),"<<r.y()<<"+"<<R<<"*sin(t) w l lw 3 notitle";
}
//-------------------------------------------------------------------------------------
//----------------------------------CLASE  COLISIONADOR--------------------------------
//-------------------------------------------------------------------------------------
class Colisionador{
private:
  double ParIz, ParDr, ParAb, ParAr, ParAt, ParAd;
public:
  void CalculeTodasLasFuerzas(Cuerpo * Nucleon);
  void CalculeFuerzaEntre(Cuerpo & Nucleon1, Cuerpo & Nucleon2);
  double CalculePotencialEntre(Cuerpo & Nucleon1, Cuerpo & Nucleon2);
  void CalculeFuerzaContenedor(Cuerpo & Nucleon1, Cuerpo & Nucleon2);
  void ReduzcaParedes(Cuerpo * Nucleon, double ParIzA, double ParDrA, double ParAbA, double ParArA, double ParAtA, double ParAdA, double ParIzB, double ParDrB, double ParAbB, double ParArB, double ParAtB, double ParAdB);
  double CalculeEnergiaCineticaTotalA(Cuerpo * Nucleon);
  double CalculeEnergiaCineticaTotalB(Cuerpo * Nucleon);
  double CalculeEnergiaPotencialTotalA(Cuerpo * Nucleon);
  double CalculeEnergiaPotencialTotalB(Cuerpo * Nucleon);
};
void Colisionador::CalculeTodasLasFuerzas(Cuerpo * Nucleon){
  int i,j;
  //Borrar las fuerzas de todos los planetas
  for(i=0;i<N+M+6+6;i++)
    Nucleon[i].BorreFuerza();
  //Hacer todas las parejas de todos
  for(i=0;i<N+M;i++)
    for(j=i+1;j<N+M;j++)
      CalculeFuerzaEntre(Nucleon[i],Nucleon[j]);
  //Fuerzas del contenedor A
  for(i=0;i<N;i++)
    for(j=N+M;j<N+M+6;j++)
      CalculeFuerzaContenedor(Nucleon[i],Nucleon[j]);
  //Fuerzas del contenedor B
  for(i=N;i<N+M;i++)
    for(j=N+M+6;j<N+M+6+6;j++)
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
double Colisionador::CalculePotencialEntre(Cuerpo & Nucleon1, Cuerpo & Nucleon2){
  vector3D r21;
  double d21,U=0;
  r21=Nucleon2.r-Nucleon1.r; d21=norma(r21);
  if(d21<Dmin)
    U=4*( pow(d21,-12) - pow(d21,-6) )-Uext;
  return U;
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
double Colisionador::CalculeEnergiaCineticaTotalA(Cuerpo * Nucleon){
  double ECTA=0;
  int i;
  for(i=0;i<N;i++)
    ECTA+=0.5*Nucleon[i].m*norma2(Nucleon[i].V);
  return ECTA;
}
double Colisionador::CalculeEnergiaCineticaTotalB(Cuerpo * Nucleon){
  double ECTB=0;
  int i;
  for(i=N;i<N+M;i++)
    ECTB+=0.5*Nucleon[i].m*norma2(Nucleon[i].V);
  return ECTB;
}
double Colisionador::CalculeEnergiaPotencialTotalA(Cuerpo * Nucleon){
  double EPT=0;
  int i,j;
  for(i=0;i<N;i++)
    for(j=0;j<N;j++)
      if(j!=i)
	EPT+=CalculePotencialEntre(Nucleon[i],Nucleon[j]);
  return EPT*0.5;
}
double Colisionador::CalculeEnergiaPotencialTotalB(Cuerpo * Nucleon){
  double EPT=0;
  int i,j;
  for(i=N;i<N+M;i++)
    for(j=N;j<N+M;j++)
      if(j!=i)
	EPT+=CalculePotencialEntre(Nucleon[i],Nucleon[j]);
  return EPT*0.5;
}
void Colisionador::ReduzcaParedes(Cuerpo * Nucleon, double ParIzA, double ParDrA, double ParAbA, double ParArA, double ParAtA, double ParAdA, double ParIzB, double ParDrB, double ParAbB, double ParArB, double ParAtB, double ParAdB){
  Nucleon[N+M   ].Inicie(ParIzA,0     ,0     ,0,0,0,1,10000);
  Nucleon[N+M+1 ].Inicie(ParDrA,0     ,0     ,0,0,0,1,10000);
  Nucleon[N+M+2 ].Inicie(0     ,ParAbA,0     ,0,0,0,1,10000);  
  Nucleon[N+M+3 ].Inicie(0     ,ParArA,0     ,0,0,0,1,10000);
  Nucleon[N+M+4 ].Inicie(0     ,0     ,ParAtA,0,0,0,1,10000);
  Nucleon[N+M+5 ].Inicie(0     ,0     ,ParAdA,0,0,0,1,10000);
  Nucleon[N+M+6 ].Inicie(ParIzB,0     ,0     ,0,0,0,1,10000);
  Nucleon[N+M+7 ].Inicie(ParDrB,0     ,0     ,0,0,0,1,10000);
  Nucleon[N+M+8 ].Inicie(0     ,ParAbB,0     ,0,0,0,1,10000);  
  Nucleon[N+M+9 ].Inicie(0     ,ParArB,0     ,0,0,0,1,10000);
  Nucleon[N+M+10].Inicie(0     ,0     ,ParAtB,0,0,0,1,10000);
  Nucleon[N+M+11].Inicie(0     ,0     ,ParAdB,0,0,0,1,10000);
}



//------------------------------------------------------------------------------------------------
//--------------------------------------------CLUSTER---------------------------------------------
//------------------------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------------------------
//--------------------------------CLUSTER CALCULATION---------------------------------------------
//------------------------------------------------------------------------------------------------

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
  int before=0;
  while( a.Size() > before ){    
    before = a.Size();
    EvaluarNucleones(a, aux);
  }
}

//Pero Hay Fiesta Para todos 
vector<Cluster> ClusterCalculator::DefinirTodosLosClusters(Cluster & a, Cluster & aux){
  vector<Cluster > CLUSTERS ;
  while( aux.Size() > 0){
    a.AgregueMiembro(aux.GetElemento(0)); //Inicializacion del Cluster
    aux.BorrarMiembro(0);
    DefinirCluster(a, aux);
    CLUSTERS.push_back(a);
    a.Clear();    
  }
  return CLUSTERS;
}


//------------------------------------------------------------------------------------------------
//----------------------------------------- ANIMACION---------------------------------------------
//------------------------------------------------------------------------------------------------

void InicieAnimacion(void){
  //cout<<"set terminal gif animate"<<endl; 
  //cout<<"set output 'e0_63-216.gif'"<<endl;
  cout<<"set grid"<<endl;
  cout<<"set xrange [-20:70]"<<endl;
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


//------------------------------------------------------------------------------------------------
//----------------------------------------- MAIN -------------------------------------------------
//------------------------------------------------------------------------------------------------

int main(void){
  Cuerpo Nucleon[N+M+6+6];
  int i,ix,iy,iz,j;
  Colisionador Hertz;
  Crandom ran2(0);
  double t,Deltat=1e-2;
  int paso;
  double tmax,tdibujo; int ndibujos=1000;
  double m0=mAr,R0=0.1;
  double VEL0A,VEL0B,Alpha,Beta,dx,dy,dz;
  vector <Cluster > CLUSTERS;
  
  VEL0A=sqrt(2*EppA/mAr);
  VEL0B=sqrt(2*EppB/mAr);

  Cluster a, Aux;
  ClusterCalculator PRO;
  int NoClusters=1;
  double EneCTA, EnePTA;
  double EneCTB, EnePTB;
  double EneCIdealA, EneCIdealB;
  
  if(gnuplot==true)
    InicieAnimacion();


  
  double Lini=12, Lfin=pow( N/densidad , 1/3.);
  double xinfA=- Lini/2.    , xsupA= Lini/2.    , yinfA= -Lini/2., ysupA= Lini/2., zinfA=-Lini/2., zsupA=Lini/2.;
  double xinfB=-(Lini/2.)+separac, xsupB=(Lini/2.)+separac, yinfB= -Lini/2., ysupB= Lini/2., zinfB=-Lini/2., zsupB=Lini/2.;
  
  double rate=((Lini-Lfin)/2.)/tredu;
  double desp, EPPPA, EPPPB, razonA, razonB;
  double ParIzA=xinfA-10000, ParDrA=xsupA+10000, ParAbA=yinfA-10000, ParArA=ysupA+10000, ParAtA=zinfA-10000, ParAdA=zsupA+10000;
  double ParIzB=xinfB-10000, ParDrB=xsupB+10000, ParAbB=yinfB-10000, ParArB=ysupB+10000, ParAtB=zinfB-10000, ParAdB=zsupB+10000;
  desp=rate*Deltat;

  
  //--------       ----(x0    ,y0    ,z0    ,Vx0,Vy0,Vz0,m0,R0);
  //----Paredes A
  //Pared izq
  Nucleon[N+M  ].Inicie(ParIzA,0     ,0     ,0,0,0,1,10000);
  //Pared drch
  Nucleon[N+M+1].Inicie(ParDrA,0     ,0     ,0,0,0,1,10000);
  //Pared abajo
  Nucleon[N+M+2].Inicie(0     ,ParAbA,0     ,0,0,0,1,10000);  
  //Pared arriba
  Nucleon[N+M+3].Inicie(0     ,ParArA,0     ,0,0,0,1,10000);
  //Pared atras
  Nucleon[N+M+4].Inicie(0     ,0     ,ParAtA,0,0,0,1,10000);
  //Pared adelante
  Nucleon[N+M+5].Inicie(0     ,0     ,ParAdA,0,0,0,1,10000);
  //----Paredes B
  //Pared izq
  Nucleon[N+M+6 ].Inicie(ParIzB,0     ,0     ,0,0,0,1,10000);
  //Pared drch
  Nucleon[N+M+7 ].Inicie(ParDrB,0     ,0     ,0,0,0,1,10000);
  //Pared abajo
  Nucleon[N+M+8 ].Inicie(0     ,ParAbB,0     ,0,0,0,1,10000);  
  //Pared arriba
  Nucleon[N+M+9 ].Inicie(0     ,ParArB,0     ,0,0,0,1,10000);
  //Pared atras
  Nucleon[N+M+10].Inicie(0     ,0     ,ParAtB,0,0,0,1,10000);
  //Pared adelante
  Nucleon[N+M+11].Inicie(0     ,0     ,ParAdB,0,0,0,1,10000);

  
  //Inicie los nucleones en una rejilla con velocidades aleatoria
  //------Nucleo A
  dx=(xsupA-xinfA)/(Nx+1); dy=(ysupA-yinfA)/(Ny+1); dz=(zsupA-zinfA)/(Nz+1);
  for(ix=0;ix<Nx;ix++)
    for(iy=0;iy<Nx;iy++)
      for(iz=0;iz<Nz;iz++){
	Alpha=2*M_PI*ran2.r();
	Beta=(M_PI*ran2.r())-M_PI/2;
	Nucleon[(iz*Nx*Ny)+(iy*Nx)+ix].Inicie(xinfA + dx*(ix+1) , yinfA + dy*(iy+1) , zinfA + dz*(iz+1) , VEL0A*cos(Beta)*cos(Alpha),VEL0A*cos(Beta)*sin(Alpha),VEL0A*sin(Beta),m0,R0);
      }
  //------Nucleo B
  dx=(xsupB-xinfB)/(Mx+1); dy=(ysupB-yinfB)/(My+1); dz=(zsupB-zinfB)/(Mz+1);
  for(ix=0;ix<Mx;ix++)
    for(iy=0;iy<Mx;iy++)
      for(iz=0;iz<Mz;iz++){
	Alpha=2*M_PI*ran2.r();
	Beta=(M_PI*ran2.r())-M_PI/2;
	Nucleon[(iz*Mx*My)+(iy*Mx)+ix + N].Inicie(xinfB + dx*(ix+1) , yinfB + dy*(iy+1) , zinfB + dz*(iz+1) , VEL0B*cos(Beta)*cos(Alpha),VEL0B*cos(Beta)*sin(Alpha),VEL0B*sin(Beta),m0,R0);
      }
 
  tmax=100;
  for(t=0,tdibujo=0,paso=0;t<tmax;t+=Deltat,tdibujo+=Deltat,paso++){

    if( paso%1000 == 0){
      for(i =0 ; i< N+M ; i++){ 
	Aux.InicieCluster(Nucleon[i]); //Se inicia con todos los nucleones
      }
      CLUSTERS = PRO.DefinirTodosLosClusters(a,Aux);
      NoClusters=PRO.GetNumeroDeClusters(CLUSTERS);
      a.Clear();
      Aux.Clear();
      /*
	cout << "time = " << t << endl;
	for(j=0;j<NoClusters;j++)
	cout << j << "\t" << PRO.GetNumeroDeElementosDelCluster(CLUSTERS,j) << endl;
      */
    }
     
    
    if(gnuplot==true){
      if(tdibujo>tmax/ndibujos){
	EneCTA = Hertz.CalculeEnergiaCineticaTotalA(Nucleon);
	EnePTA = Hertz.CalculeEnergiaPotencialTotalA(Nucleon);
	EPPPA=(EneCTA+EnePTA)/(N);
	EneCTB = Hertz.CalculeEnergiaCineticaTotalB(Nucleon);
	EnePTB = Hertz.CalculeEnergiaPotencialTotalB(Nucleon);
	EPPPB=(EneCTB+EnePTB)/(M);
	InicieCuadro();
	for(i=0;i<N+M;i++) Nucleon[i].Dibujese(t,i,EPPPA,NoClusters,EPPPB);
	TermineCuadro();
	tdibujo=0;
	//usleep(microseconds);
      }
    } 
    

    //-------------------------------REDUCTOR DE VELOCIDAD--------------------------------
    // -------mantener energia promedio por particula en el valor Epp +/- RanE------------
    if( (int(t+1)%2==0) && t<tlib){
      EneCTA = Hertz.CalculeEnergiaCineticaTotalA(Nucleon);
      EnePTA = Hertz.CalculeEnergiaPotencialTotalA(Nucleon);
      EPPPA=(EneCTA+EnePTA)/(N);
      EneCTB = Hertz.CalculeEnergiaCineticaTotalB(Nucleon);
      EnePTB = Hertz.CalculeEnergiaPotencialTotalB(Nucleon);
      EPPPB=(EneCTB+EnePTB)/(M);

      if( EPPPA > EppA+RanEA || EPPPA < EppA-RanEA ){
	EneCIdealA=EppA-(EnePTA/N);
	razonA=sqrt(EneCIdealA*N/EneCTA);
	for(i=0;i<N;i++)
	  Nucleon[i].Inicie(Nucleon[i].Getx(),Nucleon[i].Gety(),Nucleon[i].Getz(),Nucleon[i].GetVx()*razonA,Nucleon[i].GetVy()*razonA,Nucleon[i].GetVz()*razonA,m0,R0);
      }
      if( EPPPB > EppB+RanEB || EPPPB < EppB-RanEB ){
	EneCIdealB=EppB-(EnePTB/M);
	razonB=sqrt(EneCIdealB*M/EneCTB);
	for(i=N;i<N+M;i++)
	  Nucleon[i].Inicie(Nucleon[i].Getx(),Nucleon[i].Gety(),Nucleon[i].Getz(),Nucleon[i].GetVx()*razonB,Nucleon[i].GetVy()*razonB,Nucleon[i].GetVz()*razonB,m0,R0);
      }
    }
    //------------------------------------------------------------------------------------
    //---------------------------Reducir paredes------------------------------------------
    if(  (t>1) && (t<tredu)  ){
      ParIzA+=desp, ParDrA-=desp, ParAbA+=desp, ParArA-=desp, ParAtA+=desp, ParAdA-=desp;
      ParIzB+=desp, ParDrB-=desp, ParAbB+=desp, ParArB-=desp, ParAtB+=desp, ParAdB-=desp;
      Hertz.ReduzcaParedes(Nucleon, ParIzA, ParDrA, ParAbA, ParArA, ParAtA, ParAdA, ParIzB, ParDrB, ParAbB, ParArB, ParAtB, ParAdB);
    }
    //------------------------------------------------------------------------------------
    //------------------------- quitar paredes--------------------------------------------
    if( paso==(tlib*100) ){
      Nucleon[N+M   ].Inicie(ParIzA,0     ,0     ,0,0,0,1,1);
      Nucleon[N+M+1 ].Inicie(ParDrA,0     ,0     ,0,0,0,1,1);
      Nucleon[N+M+2 ].Inicie(0     ,ParAbA,0     ,0,0,0,1,1);  
      Nucleon[N+M+3 ].Inicie(0     ,ParArA,0     ,0,0,0,1,1);
      Nucleon[N+M+4 ].Inicie(0     ,0     ,ParAtA,0,0,0,1,1);
      Nucleon[N+M+5 ].Inicie(0     ,0     ,ParAdA,0,0,0,1,1);
      Nucleon[N+M+6 ].Inicie(ParIzB,0     ,0     ,0,0,0,1,1);
      Nucleon[N+M+7 ].Inicie(ParDrB,0     ,0     ,0,0,0,1,1);
      Nucleon[N+M+8 ].Inicie(0     ,ParAbB,0     ,0,0,0,1,1);  
      Nucleon[N+M+9 ].Inicie(0     ,ParArB,0     ,0,0,0,1,1);
      Nucleon[N+M+10].Inicie(0     ,0     ,ParAtB,0,0,0,1,1);
      Nucleon[N+M+11].Inicie(0     ,0     ,ParAdB,0,0,0,1,1);
    }
    //------------------------------------------------------------------------------------
    //-------------------------Acelearar nucleo 1-----------------------------------------
    if( paso==(tlib*100))
      for(i=0;i<N;i++)
	Nucleon[i].Inicie(Nucleon[i].Getx(),Nucleon[i].Gety(),Nucleon[i].Getz(),Nucleon[i].GetVx()+2,Nucleon[i].GetVy(),Nucleon[i].GetVz(),m0,R0);
    //------------------------------------------------------------------------------------

    
    for(i=0;i<N+M;i++) Nucleon[i].Mueva_r(Deltat,CHI);
    Hertz.CalculeTodasLasFuerzas(Nucleon); for(i=0;i<N+M;i++) Nucleon[i].Mueva_V(Deltat,uno_m2LAMBDA_S2);
    for(i=0;i<N+M;i++) Nucleon[i].Mueva_r(Deltat,XI);
    Hertz.CalculeTodasLasFuerzas(Nucleon); for(i=0;i<N+M;i++) Nucleon[i].Mueva_V(Deltat,LAMBDA); 
    for(i=0;i<N+M;i++) Nucleon[i].Mueva_r(Deltat,uno_m2_XIplusCHI);
    Hertz.CalculeTodasLasFuerzas(Nucleon); for(i=0;i<N+M;i++) Nucleon[i].Mueva_V(Deltat,LAMBDA); 
    for(i=0;i<N+M;i++) Nucleon[i].Mueva_r(Deltat,XI);
    Hertz.CalculeTodasLasFuerzas(Nucleon); for(i=0;i<N+M;i++) Nucleon[i].Mueva_V(Deltat,uno_m2LAMBDA_S2);
    for(i=0;i<N+M;i++) Nucleon[i].Mueva_r(Deltat,CHI);    
  }
  return 0;
}
