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

  int NUMEROPARTICULAS =1000;
  int tiempo=4000;
  int ND= 1000;
  TGraph D(tiempo);
  TGraph I(tiempo);
  TRandom r(makeseed());

  for( int t=0 ; t < tiempo ; t++)
    {
      //cout<<makeseed()<<endl;
      double p = (double) ND / (double )NUMEROPARTICULAS;
      double r1=r.Rndm();
      if(r1 <= p) ND=ND-1 ;
      else ND = ND+1;      
      D.SetPoint(t,t,ND);
      I.SetPoint(t,t,NUMEROPARTICULAS - ND);
      cout << r1 << " "<< p << " " << ND << " " << (NUMEROPARTICULAS -ND) <<endl;      
    }


  
  TCanvas *c=new TCanvas("canvas","canvas",1200,600);
  c->cd();

  D.Draw("ap");
  D.SetTitle("Difusion de un gas");
  D.GetYaxis()->SetTitle("Numero de particulas");
  D.GetXaxis()->SetTitle("tiempo");
  D.SetMinimum(0);
  I.Draw("p same");
  c->Print( "gas.pdf" );
  
 
 return 0;
}
