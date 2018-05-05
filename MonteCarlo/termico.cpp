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

  double E1=1000;
  double E2=100;
  int NPARTICULAS1=500;
  int NPARTICULAS2=1000;
  int tiempo=5000;
  TGraph T1(tiempo);
  TGraph T2(tiempo);
  TRandom r(makeseed());

  for( int t=0 ; t < tiempo ; t++){
    T1.SetPoint(t,t,E1);
    T2.SetPoint(t,t,E2);
    double ET=E1+E2;
    double r1=r.Rndm();
    double E1tmp = r1*ET;
    double E2tmp =ET-E1tmp;
    double dE1=E1tmp-E1;
    double dE2=-dE1;
    E1=E1+(double) dE1 /(double)NPARTICULAS1 ;
    E2=E2+ (double) dE2/ (double)NPARTICULAS2;
  }
	

  
  TCanvas *c=new TCanvas("canvas","canvas",1200,600);
  c->cd();

  T1.SetTitle("Equilibrio Termico");
  T1.GetYaxis()->SetTitle("Temperatura");
  T1.GetXaxis()->SetTitle("tiempo");
  T1.SetMinimum(0);
  T1.SetMarkerStyle(10);
  T1.SetMarkerColor(2);
  T1.SetMarkerSize(0.1);
  T2.SetMarkerStyle(10);
  T2.SetMarkerColor(3);
  T2.SetMarkerSize(0.1);
  T1.Draw("acp");
  T2.Draw("pc same");

  c->Print( "termico.pdf" );
  
 
 return 0;
}
