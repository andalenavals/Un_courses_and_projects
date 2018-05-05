#include <vector>
#include <string>
#include <iomanip> 
#include <iostream> 
#include <sstream>
#include <cmath> 
#include <time.h> 
#include <stdio.h> 

#include <TFormula.h>
#include <TF1.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TGraph.h>
#include <TStyle.h>

#include <TCanvas.h>
#include <TRandom.h>

using namespace std;

int makeseed(){
  time_t t;
  struct tm birthday;
  birthday.tm_hour = 16;
  birthday.tm_min  = 3;
  birthday.tm_sec  = 1;
  birthday.tm_year = 93;
  birthday.tm_mon  = 12;
  birthday.tm_mday = 22;

  time(&t);
  int sec =  difftime( t, mktime( &birthday ) );
  return sec;
}


int main(){

  int NUMERONUCLEOSX = 10000;
  int NUMERONUCLEOSY = 0;
  int NUMERONUCLEOSZ = 0;
  double PX= 0.2;
  double PY=0.1;
  int NX,NY;
  int tiempo=60;
  TGraph X(tiempo);
  TGraph Y(tiempo);
  TGraph Z(tiempo);
  TRandom r(makeseed());

  for( int t=0 ; t < tiempo ; t++){
    X.SetPoint(t,t,NUMERONUCLEOSX);
    Y.SetPoint(t,t,NUMERONUCLEOSY);
    Z.SetPoint(t,t,NUMERONUCLEOSZ);
    
    NX=NUMERONUCLEOSX;
    NY=NUMERONUCLEOSY;
    for (int i= 0 ; i < NX ;i++){
      double r1=r.Rndm();
      if (r1 <= PX){
	NUMERONUCLEOSX = NUMERONUCLEOSX-1 ;
	NUMERONUCLEOSY = NUMERONUCLEOSY +1;
      }  
    }
    for (int i=0 ;i< NY ; i++){
      double r2=r.Rndm();
      if (r2 <= PY){
	NUMERONUCLEOSY = NUMERONUCLEOSY -1;
	NUMERONUCLEOSZ = NUMERONUCLEOSZ +1 ;
      }
    }
    //cout << " " << NUMERONUCLEOSX << " " << NUMERONUCLEOSY <<endl; 
  
     
  }
	

  
  TCanvas *c=new TCanvas("canvas","canvas",1200,600);
  c->cd();


  X.SetTitle("Desintegracion nuclear");
  X.GetYaxis()->SetTitle("Numero de nucleos");
  X.GetXaxis()->SetTitle("tiempo");
  X.SetMinimum(0);
  X.SetMarkerStyle(10);
  X.SetMarkerColor(2);
  X.SetMarkerSize(1);
  Y.SetMarkerStyle(10);
  Y.SetMarkerColor(3);
  Y.SetMarkerSize(1);
  Z.SetMarkerStyle(10);
  Z.SetMarkerColor(4);
  Z.SetMarkerSize(1);
  X.Draw("acp");
  Y.Draw("pc same");
  Z.Draw("pc same");
  c->Print( "NUCLEOS.pdf" );
  
 
 return 0;
}
