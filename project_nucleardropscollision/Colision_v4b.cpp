#include <iostream>
#include <cmath>
#include <fstream>
#include <unistd.h>
#include <vector>
#include <string>
#include "Vector.h"
#include "Random64.h"
using namespace std;
unsigned int microseconds=100;
const double Uext=4*(pow(3,-12)-pow(3,-6));
const double mAr = 39.948; // Argon mass; nucleon mass, in [u.m.a] 
const double Dmin = 3.0;   // Maximum distance at which force is present in [Amstrong]
const double Epp0 = 1.0; 
const double Epp = -5.0;     // Energy per particle, in [Kelvin]
const double Ecol = 1;
const double RanE = 0.01;
const double d=3;            //Constante de separacion de clusters
const double densidad= 0.82; //Densidad


const double CHI   =0.1786178958448091;
const double LAMBDA=-0.2123418310626054;
const double XI    =-0.06626458266981849;
const double uno_m2LAMBDA_S2=(1-2*LAMBDA)/2;
const double uno_m2_XIplusCHI=(1-2*(XI+CHI));

const double K=1e4;
const double Lx=100, Ly=100, Lz=100;
const int Nx=6, Ny=6, Nz=6;
const double tredu=30; //Tiempo de compresion de paredes 
const double tlib=50; //Instante en el que se liberan las paredes
const double tcomp=0;

<<<<<<< HEAD
const bool gnuplot=false;
=======
const bool gnuplot=true;
const bool ImprimirDatos=false;
>>>>>>> 4780e9a13ee69dc5f954143fd2bc99385e3a4de5

//---------------------------------------------------------------------------------------
//----------------------------------------- ANIMACION------------------------------------
//---------------------------------------------------------------------------------------
void InicieAnimacion(void){
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

class Cuerpo;
class Colisionador;
class Cluster;
class ClusterCalculator;
class Nucleo;
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
  void AdicioneVelocidad(vector3D V0);
  void Mueva_r(double dt,double CTE);
  void Mueva_V(double dt,double CTE);
  void Dibujese(double t,int i,double et,double ec,double ep,int NoClusters,int N1);
  double Getx(void){return r.x();}; 
  double Gety(void){return r.y();}; 
  double Getz(void){return r.z();}; 
  double GetVx(void){return V.x();}; 
  double GetVy(void){return V.y();}; 
  double GetVz(void){return V.z();};
  double GetV(void){return sqrt(V.x()*V.x()+V.y()*V.y()+V.z()*V.z());}; 
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
void Cuerpo::AdicioneVelocidad(vector3D V0){
  V+=V0;
}
void Cuerpo::Mueva_r(double dt,double CTE){
  r+=V*(CTE*dt);
}
void Cuerpo::Mueva_V(double dt,double CTE){
  V+=F*(CTE*dt/m);
}
void Cuerpo::Dibujese(double t, int i, double et, double ec, double ep, int NoClusters, int N1){
  if(i==0)
    cout<<", "<<r.x()<<"+"<<R<<"*cos(t),"<<r.y()<<"+"<<R<<"*sin(t) w l lc 3 lw 3 t 't="<<t<<"'";
  else if(i==1)
    cout<<", "<<r.x()<<"+"<<R<<"*cos(t),"<<r.y()<<"+"<<R<<"*sin(t) w l lc 3 lw 3 t 'E_T="<<et<<"'";
  else if(i==2)
    cout<<", "<<r.x()<<"+"<<R<<"*cos(t),"<<r.y()<<"+"<<R<<"*sin(t) w l lc 3 lw 3 t 'E_K="<<ec<<"'";
  else if(i==3)
    cout<<", "<<r.x()<<"+"<<R<<"*cos(t),"<<r.y()<<"+"<<R<<"*sin(t) w l lc 3 lw 3 t 'E_P="<<ep<<"'";
  else if(i==4)
    cout<<", "<<r.x()<<"+"<<R<<"*cos(t),"<<r.y()<<"+"<<R<<"*sin(t) w l lc 3 lw 3 t 'clusters= "<<NoClusters<<"'";
  else if(i<N1 && i>4)
    cout<<", "<<r.x()<<"+"<<R<<"*cos(t),"<<r.y()<<"+"<<R<<"*sin(t) w l lc 3 lw 3 notitle";
  else 
    cout<<", "<<r.x()<<"+"<<R<<"*cos(t),"<<r.y()<<"+"<<R<<"*sin(t) w l lc 2 lw 3 notitle";
}
//---------------------------------------------------------------------------------------
//--------------------------------------------CLUSTER------------------------------------
//---------------------------------------------------------------------------------------
class Cluster{
private:
  vector <Cuerpo > cluster;
public:
  void InicieCluster(Cuerpo Nucleon){cluster.push_back(Nucleon);};
  void Clear(void){ cluster.clear();};
  void AgregueMiembro(Cuerpo Nucleon){cluster.push_back(Nucleon);};
  void BorrarMiembro(int j){cluster.erase (cluster.begin()+ j);};
  int Size(void){return cluster.size();}; 
  Cuerpo GetElemento(int i){return cluster[i];};
  friend class ClusterCalculator;
  friend class Colisionador;
};
//---------------------------------------------------------------------------------------
//--------------------------------CLUSTER CALCULATION------------------------------------
//---------------------------------------------------------------------------------------
class ClusterCalculator{
private:
public:
  void EvaluarNucleones(Cluster & a, Cluster & aux);
  void DefinirCluster( Cluster & a, Cluster & aux);
  vector<Cluster> DefinirTodosLosClusters(Cluster & a, Cluster & aux);
  int GetNumeroDeClusters( vector<Cluster > CLUSTERS){return CLUSTERS.size();};
  Cluster GetCluster( vector<Cluster > CLUSTERS, int i){return CLUSTERS[i];};
  int GetNumeroDeElementosDelCluster(vector<Cluster > CLUSTERS , int i ){return CLUSTERS[i].Size()  ;};
  int GetNumeroDeMonomeros(vector<Cluster> CLUSTERS);
  int GetNumeroDeClusterMayor(vector<Cluster> CLUSTERS);
  friend class Cuerpo;
  friend class Cluster;
};
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
void ClusterCalculator::DefinirCluster( Cluster & a, Cluster & aux){
  int before=0;
  while( a.Size() > before ){    
    before = a.Size();
    EvaluarNucleones(a, aux);
  }
}
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
int ClusterCalculator::GetNumeroDeMonomeros(vector<Cluster> CLUSTERS){
  int NoMonomeros=0;
  for(int i =0 ; i< GetNumeroDeClusters(CLUSTERS); i++){
    if(GetNumeroDeElementosDelCluster(CLUSTERS, i) == 1 )
      NoMonomeros +=1;
  }
  return NoMonomeros;
}
int ClusterCalculator::GetNumeroDeClusterMayor(vector<Cluster> CLUSTERS){
  int NoClusterMayor = GetNumeroDeElementosDelCluster(CLUSTERS, 0);
  for(int i =0 ; i< GetNumeroDeClusters(CLUSTERS) ; i++){
    if(GetNumeroDeElementosDelCluster(CLUSTERS, i) >=  NoClusterMayor )
      NoClusterMayor = GetNumeroDeElementosDelCluster(CLUSTERS, i);
  }
  return NoClusterMayor;
}
//-------------------------------------------------------------------------------------
//----------------------------------CLASE  COLISIONADOR--------------------------------
//-------------------------------------------------------------------------------------
class Colisionador{
private:
public:
  void CalculeTodasLasFuerzas(Cuerpo * Nucleon, int N);
  void CalculeFuerzaEntre(Cuerpo & Nucleon1, Cuerpo & Nucleon2);
  double CalculePotencialEntre(Cuerpo & Nucleon1, Cuerpo & Nucleon2);
  double CalculePotencialPared(Cuerpo & Nucleon1, Cuerpo & Nucleon2);
  void CalculeFuerzaContenedor(Cuerpo & Nucleon1, Cuerpo & Nucleon2);
  void ReduzcaParedes(Cuerpo * Nucleon, int N, double desp, double ParIz, double ParDr, double ParAb, double ParAr, double ParAt, double ParAd);
  double CalculeEnergiaCineticaTotal(Cuerpo * Nucleon, int N);
  double CalculeEnergiaPotencialTotal(Cuerpo * Nucleon, int N);
  void DinamicaMolecular(Cuerpo * Nucleon, int N , double Deltat);
  friend class Cluster;
};
void Colisionador::CalculeTodasLasFuerzas(Cuerpo * Nucleon, int N){
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
double Colisionador::CalculePotencialEntre(Cuerpo & Nucleon1, Cuerpo & Nucleon2){
  vector3D r21;
  double d21,U=0;
  r21=Nucleon2.r-Nucleon1.r; d21=norma(r21);
  if(d21<Dmin)
    U=4*( pow(d21,-12) - pow(d21,-6) )-Uext;
  return U;
}
double Colisionador::CalculePotencialPared(Cuerpo & Nucleon1, Cuerpo & Nucleon2){
  vector3D r21,F2;
  double d21,h;
  double Up=0;
  r21=Nucleon2.r-Nucleon1.r; d21=norma(r21); h=(Nucleon2.R+Nucleon1.R)-d21;
  if(0<h)
    Up=2*K*pow(h,2.5)/5.;
  return Up;
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
double Colisionador::CalculeEnergiaCineticaTotal(Cuerpo * Nucleon, int N){
  double ECT=0;
  int i;
  for(i=0;i<N;i++)
    ECT+=0.5*Nucleon[i].m*norma2(Nucleon[i].V);
  return ECT;
}
double Colisionador::CalculeEnergiaPotencialTotal(Cuerpo * Nucleon, int N){
  double EPT=0;
  int i,j;
  for(i=0;i<N;i++)
    for(j=0;j<N;j++)
      if(j!=i)
	EPT+=CalculePotencialEntre(Nucleon[i],Nucleon[j]);
  EPT*=0.5;
  for(i=0;i<N;i++)
    for(j=N;j<N+6;j++)
      EPT+=CalculePotencialPared(Nucleon[i],Nucleon[j]);
  return EPT;
}
void Colisionador::ReduzcaParedes(Cuerpo * Nucleon,int N,  double desp, double ParIz, double ParDr, double ParAb, double ParAr, double ParAt, double ParAd){
  Nucleon[N  ].Inicie(ParIz,0    ,0    ,0,0,0,1,10000);
  Nucleon[N+1].Inicie(ParDr,0    ,0    ,0,0,0,1,10000);
  Nucleon[N+2].Inicie(0    ,ParAb,0    ,0,0,0,1,10000);  
  Nucleon[N+3].Inicie(0    ,ParAr,0    ,0,0,0,1,10000);
  Nucleon[N+4].Inicie(0    ,0    ,ParAt,0,0,0,1,10000);
  Nucleon[N+5].Inicie(0    ,0    ,ParAd,0,0,0,1,10000);
}
void Colisionador::DinamicaMolecular(Cuerpo * Nucleon, int N , double Deltat){
  int i;
  for(i=0;i<N;i++) Nucleon[i].Mueva_r(Deltat,CHI);
  CalculeTodasLasFuerzas(Nucleon, N); for(i=0;i<N;i++) Nucleon[i].Mueva_V(Deltat,uno_m2LAMBDA_S2);
  for(i=0;i<N;i++) Nucleon[i].Mueva_r(Deltat,XI);
  CalculeTodasLasFuerzas(Nucleon, N); for(i=0;i<N;i++) Nucleon[i].Mueva_V(Deltat,LAMBDA);
  for(i=0;i<N;i++) Nucleon[i].Mueva_r(Deltat,uno_m2_XIplusCHI);
  CalculeTodasLasFuerzas(Nucleon, N); for(i=0;i<N;i++) Nucleon[i].Mueva_V(Deltat,LAMBDA);
  for(i=0;i<N;i++) Nucleon[i].Mueva_r(Deltat,XI);
  CalculeTodasLasFuerzas(Nucleon, N); for(i=0;i<N;i++) Nucleon[i].Mueva_V(Deltat,uno_m2LAMBDA_S2);
  for(i=0;i<N;i++) Nucleon[i].Mueva_r(Deltat,CHI);
}
//---------------------------------------------------------------------------------------
//-------------------------------------CLASE NUCLEO--------------------------------------
//---------------------------------------------------------------------------------------
class Nucleo{
private:
public:
  void Estabilizar(Cuerpo * Nucleon, int N, vector3D r);
  void DeleVelocidad(Cuerpo * Nucleon, int N, vector3D V0);
  friend class Cuerpo;
  friend class Cluster;
  friend class Colisionador;
};
void Nucleo::Estabilizar(Cuerpo * Nucleon, int N, vector3D r){
  int i,ix,iy,iz,j;
  Colisionador Hertz;
  Crandom ran2(0);
  double tmax,t,Deltat=1e-2;
  int paso;
  double m0=mAr,R0=0.1;
  double VEL0,Alpha,Beta,dx,dy,dz;
  
  vector <Cluster > CLUSTERS;
  Cluster a, Aux;
  ClusterCalculator PRO;
  int NoClusters=1;
  double EneCT, EnePT;
  
  VEL0=sqrt(2*Epp0/mAr);
  
  double Lini=20, Lfin=pow( N/densidad , 1/3.);
  double xinf=r.x()-Lini/2., xsup=r.x()+Lini/2., yinf= r.y()-Lini/2., ysup =r.y()+ Lini/2., zinf=r.z()-Lini/2., zsup=r.z()+Lini/2.;
  
  double rate=((Lini-Lfin)/2.)/tredu;
  double desp, t1, t2, EPPP, razon;
  double ParIz=xinf-10000, ParDr=xsup+10000, ParAb=yinf-10000, ParAr=ysup+10000, ParAt=zinf-10000, ParAd=zsup+10000;
  desp=rate*Deltat;
  
  //----PAREDES------(x0   ,y0 ,z0,Vx0,Vy0,Vz0,m0,R0);
  Nucleon[N  ].Inicie(ParIz,0    ,0    ,0,0,0,1,10000);   //Pared izq
  Nucleon[N+1].Inicie(ParDr,0    ,0    ,0,0,0,1,10000);   //Pared drch
  Nucleon[N+2].Inicie(0    ,ParAb,0    ,0,0,0,1,10000);   //Pared abajo
  Nucleon[N+3].Inicie(0    ,ParAr,0    ,0,0,0,1,10000);   //Pared arriba
  Nucleon[N+4].Inicie(0    ,0    ,ParAt,0,0,0,1,10000);   //Pared atras
  Nucleon[N+5].Inicie(0    ,0    ,ParAd,0,0,0,1,10000);   //Pared adelante
   
  //inicializacion de nucleones con velocidades aleatorias
  dx=(xsup-xinf)/(Nx+1); dy=(ysup-yinf)/(Ny+1); dz=(zsup-zinf)/(Nz+1);
  for(ix=0;ix<Nx;ix++)
    for(iy=0;iy<Nx;iy++)
      for(iz=0;iz<Nz;iz++){
	Alpha=2*M_PI*ran2.r();
	Beta=(M_PI*ran2.r())-M_PI/2;
	Nucleon[(iz*Nx*Ny)+(iy*Nx)+ix].Inicie(xinf + dx*(ix+1) , yinf + dy*(iy+1) , zinf + dz*(iz+1) , VEL0*cos(Beta)*cos(Alpha),VEL0*cos(Beta)*sin(Alpha),VEL0*sin(Beta),m0,R0);
      }
  
  for(t=0,paso=0;t<=tlib+10;t+=Deltat,paso++){
    //CLUSTERS
    if( paso%100 == 0){
      for(i =0 ; i< N ; i++) Aux.InicieCluster(Nucleon[i]); 
      CLUSTERS = PRO.DefinirTodosLosClusters(a,Aux);
      NoClusters=PRO.GetNumeroDeClusters(CLUSTERS);
      a.Clear();
      Aux.Clear();
    }   
    //ANIMACION
    if(gnuplot==true){
      if(paso%100 == 0){
	EneCT = Hertz.CalculeEnergiaCineticaTotal(Nucleon, N);
	EnePT = Hertz.CalculeEnergiaPotencialTotal(Nucleon, N);
	EPPP=(EneCT+EnePT)/N;
	InicieCuadro();
	for(i=0;i<N;i++) Nucleon[i].Dibujese(t,i,EPPP,EneCT/N,EnePT/N,NoClusters,N);
	TermineCuadro();
	//usleep(microseconds);
      }
    }
    //---------------------------------------------------------------------------------
    // -------mantener energia promedio por particula en el valor Epp +/- RanE---------
    if( paso%10==0 && t<tlib && t>tredu){
      EneCT = Hertz.CalculeEnergiaCineticaTotal(Nucleon,N);
      EnePT = Hertz.CalculeEnergiaPotencialTotal(Nucleon,N);
      EPPP=(EneCT+EnePT)/(N);

      if( EPPP > Epp+RanE ){
	razon=0.9;
	for(i=0;i<N;i++)
	  Nucleon[i].Inicie(Nucleon[i].Getx(),Nucleon[i].Gety(),Nucleon[i].Getz(),Nucleon[i].GetVx()*razon,Nucleon[i].GetVy()*razon,Nucleon[i].GetVz()*razon,m0,R0);
      }
    
      if( EPPP < Epp-RanE ){
	razon=1.1;
	for(i=0;i<N;i++)
	  Nucleon[i].Inicie(Nucleon[i].Getx(),Nucleon[i].Gety(),Nucleon[i].Getz(),Nucleon[i].GetVx()*razon,Nucleon[i].GetVy()*razon,Nucleon[i].GetVz()*razon,m0,R0);
      }
    }
    //-----------------------------------------------------------------------------------
    //---------------------------Reducir paredes-----------------------------------------
    if(  (t>tcomp) && (t<tredu)  ){
      ParIz+=desp, ParDr-=desp, ParAb+=desp, ParAr-=desp, ParAt+=desp, ParAd-=desp;
      Hertz.ReduzcaParedes(Nucleon,N, desp, ParIz, ParDr, ParAb, ParAr, ParAt, ParAd);
    }
    //-----------------------------------------------------------------------------------
    //------------------------- quitar paredes-------------------------------------------
    if( paso==(tlib*100) ){
      Nucleon[N  ].Inicie(ParIz,0    ,0    ,0,0,0,1,1);
      Nucleon[N+1].Inicie(ParDr,0    ,0    ,0,0,0,1,1);
      Nucleon[N+2].Inicie(0    ,ParAb,0    ,0,0,0,1,1);  
      Nucleon[N+3].Inicie(0    ,ParAr,0    ,0,0,0,1,1);
      Nucleon[N+4].Inicie(0    ,0    ,ParAt,0,0,0,1,1);
      Nucleon[N+5].Inicie(0    ,0    ,ParAd,0,0,0,1,1);
    }
    Hertz.DinamicaMolecular(Nucleon, N , Deltat);      
  }
  
}

void Nucleo::DeleVelocidad(Cuerpo * Nucleon, int N,   vector3D V0){
  for(int i=0;i <N;i++)
    Nucleon[i].AdicioneVelocidad(V0);
}
//---------------------------------------------------------------------------------------
//-------------------------------------CLASE IMPRIMIR------------------------------------
//--------------------------------------------------------------------------------------
class Imprimir{
private: ofstream NoClusters, NoMonomeros, NoNucleonesClusterMayor, MonomerosEnergia; 
public:
  void Inicie(string NombreArchivo1, string NombreArchivo2 , string NombreArchivo3,  string NombreArchivo4);
  void Clusters(double x, int y){ NoClusters<<x<<" "<<y<<"\n";};
  void Monomeros(double x, int y){ NoMonomeros<<x<<" "<<y<<"\n";};
  void NucleonesClusterMayor(double x,int y){ NoNucleonesClusterMayor<<x<<" "<<y<<"\n";};
  void MonomerosE( double x){ MonomerosEnergia<<x<<"\n";};
  void Close(void){NoClusters.close(); NoMonomeros.close(); NoNucleonesClusterMayor.close(); MonomerosEnergia.close();};
};

void Imprimir::Inicie( string NombreArchivo1, string NombreArchivo2 , string NombreArchivo3, string NombreArchivo4){
  NoClusters.open(NombreArchivo1.c_str());
  NoMonomeros.open(NombreArchivo2.c_str());
  NoNucleonesClusterMayor.open(NombreArchivo3.c_str());
  MonomerosEnergia.open(NombreArchivo4.c_str());
}
//---------------------------------------------------------------------------------------
//----------------------------------------- MAIN ----------------------------------------
//---------------------------------------------------------------------------------------
int main(void){
  Imprimir Archivo;
<<<<<<< HEAD
  Archivo.Inicie("1_NoClusters_n4.dat", "1_NoMonomeros_n4.dat", "1_NoClusterMayor_n4.dat", "1EnergiasMonomeros.dat");

=======
  if(ImprimirDatos)
    Archivo.Inicie("1_NoClusters_n4.dat", "1_NoMonomeros_n4.dat", "1_NoClusterMayor_n4.dat", "1EnergiasMonomeros.dat");
  
>>>>>>> 4780e9a13ee69dc5f954143fd2bc99385e3a4de5
  int N1=Nx*Ny*Nz, N2=Nx*Ny*Nz, N= N1+N2;
  Cuerpo Nucleon1[N1+6], Nucleon2[N2+6], Nucleon[N+6];
  Colisionador Hertz;
  double t,Deltat=1e-2;
  int paso, i,  NoClusters=1 , NoMonomeros, NoClusterMayor;
  double tmax; int ndibujos=10000;
  double m0=mAr,R0=0.1;
  vector <Cluster > CLUSTERS;
  
  Cluster a, Aux;
  ClusterCalculator PRO;
  Nucleo NUCLEO;
  double EneCT, EnePT, EPPP;
  double Vcol=sqrt(2*Ecol/mAr);
  vector3D V1; V1.cargue(Vcol,0,0);
  vector3D V2; V2.cargue(-Vcol,0,0);
  vector3D r1; r1.cargue(-10,0,0);
  vector3D r2; r2.cargue(10,0,0);
  
  if(gnuplot==true)
    InicieAnimacion();

<<<<<<< HEAD
 
  NUCLEO.Estabilizar( Nucleon1 ,N1,r1);   NUCLEO.Estabilizar( Nucleon2,N2,r2);
  NUCLEO.DeleVelocidad(Nucleon1,N1,V1);  NUCLEO.DeleVelocidad(Nucleon2,N2,V2);
  
  
  for(int j=0 ; j < N1 ; j++){   
    Nucleon[j] = Nucleon1[j];
  }
  for(int j=0 ; j < N2 ; j++){   
    Nucleon[j+N1] = Nucleon2[j];
  }
=======
  NUCLEO.Estabilizar( Nucleon1 ,N1,r1);  NUCLEO.Estabilizar( Nucleon2,N2,r2);
  NUCLEO.DeleVelocidad(Nucleon1,N1,V1);  NUCLEO.DeleVelocidad(Nucleon2,N2,V2);
  
  
  for(int j=0 ; j < N1 ; j++)
    Nucleon[j] = Nucleon1[j];
  
  for(int j=0 ; j < N2 ; j++) 
    Nucleon[j+N1] = Nucleon2[j];
  
>>>>>>> 4780e9a13ee69dc5f954143fd2bc99385e3a4de5
  Nucleon[N  ].Inicie(1e5,0  ,0  ,0,0,0,1,1);
  Nucleon[N+1].Inicie(1e5,0  ,0  ,0,0,0,1,1);
  Nucleon[N+2].Inicie(0  ,1e5,0  ,0,0,0,1,1);
  Nucleon[N+3].Inicie(0  ,1e5,0  ,0,0,0,1,1);
  Nucleon[N+4].Inicie(0  ,0  ,1e5,0,0,0,1,1); 
  Nucleon[N+5].Inicie(0  ,0  ,1e5,0,0,0,1,1);

   
  //EVOLUCION EN EL TIEMPO
<<<<<<< HEAD
  tmax=3000;
=======
  tmax=2000;
>>>>>>> 4780e9a13ee69dc5f954143fd2bc99385e3a4de5
  for(t=tlib+10,paso=0;t<=tmax;t+=Deltat,paso++){    
    //CLUSTERS
    if( paso%100 == 0){
      for(i =0 ; i< N ; i++) Aux.InicieCluster(Nucleon[i]);
      CLUSTERS = PRO.DefinirTodosLosClusters(a,Aux);
      NoClusters = PRO.GetNumeroDeClusters(CLUSTERS);
<<<<<<< HEAD
      NoMonomeros = PRO.GetNumeroDeMonomeros(CLUSTERS);
      NoClusterMayor = PRO.GetNumeroDeClusterMayor(CLUSTERS);
      Archivo.Clusters(t , NoClusters);
      Archivo.Monomeros(t , NoMonomeros);
      Archivo.NucleonesClusterMayor(t , NoClusterMayor);
=======
      if(ImprimirDatos){
	NoMonomeros = PRO.GetNumeroDeMonomeros(CLUSTERS);
	NoClusterMayor = PRO.GetNumeroDeClusterMayor(CLUSTERS);
	Archivo.Clusters(t , NoClusters);
	Archivo.Monomeros(t , NoMonomeros);
	Archivo.NucleonesClusterMayor(t , NoClusterMayor);
      }
>>>>>>> 4780e9a13ee69dc5f954143fd2bc99385e3a4de5
      a.Clear();
      Aux.Clear();
    }
    //ANIMACION   
    if(gnuplot==true){     
<<<<<<< HEAD
      if(paso%100 == 0){
=======
      if(paso%500 == 0){
>>>>>>> 4780e9a13ee69dc5f954143fd2bc99385e3a4de5
	EneCT = Hertz.CalculeEnergiaCineticaTotal(Nucleon, N);
	EnePT = Hertz.CalculeEnergiaPotencialTotal(Nucleon, N);
	EPPP=(EneCT+EnePT)/N;
	InicieCuadro();
	for(i=0;i<N;i++) Nucleon[i].Dibujese(t,i,EPPP,EneCT/N,EnePT/N,NoClusters,N1);
	TermineCuadro();
	//usleep(microseconds);
      }
    }
    Hertz.DinamicaMolecular(Nucleon, N ,  Deltat);    
  }

<<<<<<< HEAD
  for(i=0 ; i< PRO.GetNumeroDeClusters(CLUSTERS); i++){
    if(PRO.GetNumeroDeElementosDelCluster(CLUSTERS, i) == 1 )
      Archivo.MonomerosE(PRO.GetCluster(CLUSTERS, i).GetElemento(0).GetV() );
  }
  Archivo.Close();
=======
  if(ImprimirDatos){
    for(i=0 ; i< PRO.GetNumeroDeClusters(CLUSTERS); i++){
      if(PRO.GetNumeroDeElementosDelCluster(CLUSTERS, i) == 1 )
	Archivo.MonomerosE(PRO.GetCluster(CLUSTERS, i).GetElemento(0).GetV() );
    }
    Archivo.Close();
  }
>>>>>>> 4780e9a13ee69dc5f954143fd2bc99385e3a4de5
  return 0;
}
