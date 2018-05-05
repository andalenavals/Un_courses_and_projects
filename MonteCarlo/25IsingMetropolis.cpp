#include<iostream>
#include<cmath>
#include "Random64.h"
using namespace std;

const int L=8;
const int L2=L*L;

class SpinSystem{
private:
  int s[L][L]; int E,M;
public:
  void InicieTodosAbajo(void);
  void UnPasoDeMetropolis(double kT, Crandom & ran);
  double GetE(void){ return 1.0*E; };
  double GetM(void){ return fabs(1.0*M); };
};

void SpinSystem::InicieTodosAbajo(void){
  for(int i=0; i < L ; i++)  
    for(int j=0; j < L ; j++)
      s[i][j]=-1;
  M=-L2; E=-2*L2;
}

void SpinSystem::UnPasoDeMetropolis(double Beta, Crandom & ran){
  int n ,i ,j; int dE;
  // Escoger un espin al azar
  n=(int) L2*ran.r(); i=2/L;  j=n%L;
  //Calcular cual seria dE si lo volteo
  dE=2*s[i][j]*(s[i][(j+1)%L]+s[i][(j-1+L)%L]+s[i+1][(j+1)%L]+s[(i-1+L)%L][j]);
  //Implementar el A(x'| x) de metropolis
  if(dE<=0)
    {s[i][j] *=-1; E+=dE; M+=2*s[i][j];}
  else if( ran.r()<exp(-dE*Beta) )
   {s[i][j] *=-1; E+=dE; M+=2*s[i][j];}
}

int main(void){
  SpinSystem Ising;
  int Nsamples= 10000;
  int t , mcs , n;
  int teq= (int) 200*pow(L/8.0, 2.7); //z=2.7;
  int tco=(int) 10*pow(L/8.0, 2.7);
  double E , M, SumaM , SumaM2, SumaM4, SumaE, SumaE2, Mprom , M2prom, M4prom, Eprom, E2prom ;
  Crandom ran(29);  


  double kT, Beta;
  for (kT=0.2 ;kT < 4 ; kT+=0.1){
    Beta=1/kT;
    //INICIE
    Ising.InicieTodosAbajo(); 
    SumaM=0;
    //EQUILIBRE
    for(t=0 ; t< teq ; t++)
      for(mcs =0; mcs < L2 ; mcs++)
	Ising.UnPasoDeMetropolis(Beta, ran);
    //TOMAR MUESTRAS
    for(n=0 ; n< Nsamples ; n++){
      E=Ising.GetE(); M=Ising.GetM();  
      SumaM+=M;
      for(t=0;t < tco; t++)
	for(mcs =0; mcs < L2 ; mcs++)
	  Ising.UnPasoDeMetropolis(Beta, ran);
    }
    
    Mprom=SumaM/Nsamples;
    //Imprimer
    cout<<kT<<" "<<Mprom<<endl;      
  }
  
  return 0;
}
