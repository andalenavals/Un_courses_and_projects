#include <iostream>
#include <cstdlib>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <istream>
#include <complex>
#include <iomanip>
#include <vector>

#include "TF1.h"
#include "TH1.h"
#include <TH1F.h>
#include "TCanvas.h"
#include "TMath.h"
#include "TAxis.h"
#include "TGraph.h"
#include "TPad.h"
#include "TGaxis.h"
#include "TRandom.h"
#include "TStyle.h"
#include "TColor.h"
#include "TPaveText.h"
#include "TPaveStats.h"
#include "TList.h"
#include "TLegend.h"
#include <TLatex.h>
#include "TSpectrum.h"
#include "TVirtualFitter.h"

using namespace std;
/*int npeaks = 30;
double fpeaks(double *x, double *parameter) {
   double result = parameter[0] + parameter[1]*x[0];
   for (int p=0 ; p<npeaks ; p++) {
      double norm  = parameter[3*p+2];
      double mean  = parameter[3*p+3];
      double sigma = parameter[3*p+4];
      result += norm*TMath::Gaus(x[0],mean,sigma);
   }
   return result;
}
*/

 void ordenar_numeros(double arreglo[], int lon){
        int Temp;
         for(int i=0;i<lon;i++)
                for(int j=0;j<lon-1;j++)
                    if(arreglo[j]<arreglo[j+1]){// cambia "<" a ">" para cambiar la manera de ordenar
                        Temp=arreglo[j];
                        arreglo[j]=arreglo[j+1];
                        arreglo[j+1]=Temp;
		    }
 }





int main(){

  //string v[4]={22Na_5min.dat, 54Mn_5min.dat, 60Co_5min.dat, 137Cs_5min.dat}

  


  //gStyle->SetOptStat(kFALSE);
 
  ifstream file1, file2, file1a;
  ofstream file3;
  double column1, column2;
  int bin=0,nbin=0, q=0;
  double peaks[7];
  double E[7]={1785.5, 1332.5, 1274.5, 1173.5, 834.8, 661.7, 511.0};


  for(int k=0; k<4; k++){
  
    if (k==0) file1a.open (  "22Na_5min.dat" , ios::in );
    if (k==1) file1a.open (  "54Mn_5min.dat" , ios::in );
    if (k==2) file1a.open ( "60Co_5min.dat" , ios::in );
    if (k==3) file1a.open (  "137Cs_5min.dat" , ios::in );
  
    nbin=0;
    while( !file1a.eof() ){
    file1a >> column1 >> column2;
    nbin+=1;
    //cout<<nbin<<" "<<column1<<" "<<column2 <<endl;
  }
    //cout<<nbin<<endl;
  
  if (k==0) file1.open (  "22Na_5min.dat" , ios::in ); //3
  if (k==1) file1.open (  "54Mn_5min.dat" , ios::in ); //1
  if (k==2) file1.open (  "60Co_5min.dat" , ios::in ); //2
  if (k==3) file1.open (  "137Cs_5min.dat" , ios::in );//1
  
  
  TH1I *h1= new TH1I( "h1", "Espectro", nbin , 1, nbin);
  TH1I *h2= new TH1I( "h2", "Espectro", nbin , 1, nbin);
  TH1I *h3= new TH1I( "h3", "Espectro", nbin , 1, nbin);
  TH1I *h4= new TH1I( "h4", "Espectro", nbin , 1, nbin);
  
  bin=0;
  if (k==0){
  while( !file1.eof() ){
    file1 >> column1 >> column2;
    bin=bin+1;
    h1->SetBinContent( bin, column2 );
  }
  }
  
  if (k==1){
    while( !file1.eof() ){
      file1 >> column1 >> column2;
      bin=bin+1;
      h2->SetBinContent( bin, column2 );
    }
  }
  
  if (k==2){
    while( !file1.eof() ){
      file1 >> column1 >> column2;
      bin=bin+1;
      h3->SetBinContent( bin, column2 );
    }
  }
  
     if (k==3){
       while( !file1.eof() ){
	 file1 >> column1 >> column2;
	 bin=bin+1;
	 h4->SetBinContent( bin, column2 );
       }
     }
     
     int npeaks;
     if (k==0) npeaks=3;
     if (k==1) npeaks=1;
     if (k==2) npeaks=2;
     if (k==3) npeaks=1;

      TSpectrum *s=new TSpectrum(npeaks);
      int nfound;
      
     if (k==0){
       // TSpectrum *s=new TSpectrum(npeaks);
       nfound = s->Search(h1,5,"",0.008);
     }
     
     if (k==1){
       //TSpectrum *s=new TSpectrum(npeaks);
       nfound = s->Search(h2,5,"",0.008);
     }
     
     if (k==2){
       // TSpectrum *s=new TSpectrum(npeaks);
       nfound = s->Search(h3,5,"",0.008);
     }
     
     if (k==3){
       //TSpectrum *s=new TSpectrum(npeaks);
       nfound = s->Search(h4,5,"",0.008);
     }
    
 
  float *xpeaks = s->GetPositionX();
  for (int p=0;p<nfound;p++) {
    float xp = xpeaks[p];
    int bin = h1->GetXaxis()->FindBin(xp);
    float yp = h1->GetBinContent(bin);
    // if (xp < 800) continue;
    // if (yp-TMath::Sqrt(yp) < fline->Eval(xp)) continue;
    peaks[q]=xpeaks[p];
    q=q+1;
    cout<<xp<<endl;
  }
  
  if (k==0) file1a.close ( );
  if (k==1) file1a.close ( );
  if (k==2) file1a.close ( );
  if (k==3) file1a.close ( );

  if (k==0) file1.close ( );
  if (k==1) file1.close ( );
  if (k==2) file1.close ( );
  if (k==3) file1.close ( );

  }
  // ordenar_numeros(E,7);
  ordenar_numeros(peaks,7);

  TCanvas c ("","",600,600);
  TGraph g (7);
  TF1 fit ("fit","pol1",0.,1400.);
  c.cd();
  for(int t=0; t<7;t++){
    g.SetPoint(t, peaks[t], E[t]);
    cout<<"Energia-canal: "<<E[t]<<" "<<peaks[t]<<endl;
  }
  g.SetMarkerStyle(10);
  g.SetMarkerSize(1);
  g.SetMarkerColor(1);
  g.Draw("AP");
  g.Fit("fit");
  c.Print("calibracion.pdf");
 
  return 0;

}




