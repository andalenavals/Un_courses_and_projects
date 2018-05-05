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
#include <cmath>

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


void ordenar_numeros(double arreglo[][2], int lon){
  double Tempy, Tempx;
  for(int i=0;i<lon;i++)
    for(int j=0;j<lon-1;j++)
      if(arreglo[j][1]<arreglo[j+1][1]){// cambia "<" a ">" para cambiar la manera de ordenar
	Tempy=arreglo[j][1];
	Tempx=arreglo[j][0];
	arreglo[j][1]=arreglo[j+1][1];
	arreglo[j][0]=arreglo[j+1][0];
	arreglo[j+1][1]=Tempy;
	arreglo[j+1][0]=Tempx;
      } 
} 


using namespace std;
int main(){  
  /* string espectro , fondo;
  cout<<"Digite la direccion del Espectro"<<endl;
  getline(cin,espectro);
  cout<<"Digite la direccion del Fondo"<<endl;
  getline(cin,fondo);*/

  gStyle->SetOptStat(kFALSE);
 
  ifstream file1, file2, file1a;
  ofstream file3;
  double column1=0, column2, sizebin=0.,a;
  int np=3,nbin=0,w=0;
  
  // file1.open ( (espectro).c_str(), ios::in );
  file1a.open (  "22Na_5min.dat" , ios::in );
  //file1a.open (  "Ge40_Co60_10min.dat" , ios::in );
  while( !file1a.eof() ){
    file1a >> column1 >> column2;
    nbin+=1;
    if(nbin<=2){
      a=column1;
      sizebin=a-sizebin;
      //cout<<sizebin<<endl;
    }
    //cout<<nbin<<" "<<column1<<" "<<column2 <<endl;
  }
  cout<<sizebin<<" "<<nbin<<endl;
 

  
    
  TGraph g1(nbin);
  double espc[nbin][2];
  file1.open (  "22Na_5min.dat" , ios::in );
  // file1.open (  "Ge40_Co60_10min.dat" , ios::in );
  while( !file1.eof() ){
    file1 >> column1 >> column2;
    g1.SetPoint(w,column1,column2);
    espc[w][1]=column2;
    espc[w][0]=column1;
    w=w+1;
    //cout<<w<<endl;
  }

 
  /* int start=225;
     for(int i=0; i<=start; i++) espc[i][1]=0;*/
  
  
  ordenar_numeros(espc,nbin); 
  int j;
  for(int i=0; i<(np-1) ; i++){
    j=i;
    while(fabs(espc[j][0]-espc[j+1][0])<=(sizebin*(j+1)*4)){
      if(fabs(espc[j][0]-espc[j+1][0])<=(sizebin*(j+1)*4)) espc[j+1][1]=0;
      j=j+1;
    }
    ordenar_numeros(espc,nbin);
  }

  
  // for(int i=0; i<nbin;i++)  cout<<espc[i][0]<<" "<<espc[i][1]<<endl;

  TCanvas *C = new TCanvas("Canvas_1", "Canvas_1",258,84,1178,665);
  C->Range(-250.5,-20.7375,2249.5,186.6375);
  C->SetFillColor(0);
  C->SetBorderMode(0);
  C->SetBorderSize(2);
  C->SetFrameBorderMode(0);
  C->SetFrameBorderMode(0);
  C->cd();
  g1.SetMarkerStyle(10);
  g1.SetMarkerSize(0.3);
  g1.SetMarkerColor(1);
  g1.Draw("ap");

  
  C->Print("ajuste.pdf");
  
  
}


  /* TGraph g2(nbin);
  double df[nbin][2];
  for(int j=1; j<=nbin;j++){
  df[j][1]=(espc[j+1][1]-espc[j-1][1])/2*sizebin;
  df[j][0]=espc[j][0];
  g2.SetPoint(j-1,df[j][0],df[j][1]);
  }

  TGraph g3(nbin);
  double dff[nbin][2];
  for(int j=1; j<=nbin;j++){
    dff[j][1]=(espc[j+1][1]+espc[j-1][1]-2*espc[j][1])/(sizebin*sizebin);
  dff[j][0]=espc[j][0];
  g3.SetPoint(j-1,dff[j][0],dff[j][1]);
  }*/



/*while( !file1.eof() ){
    file1 >> column1 >> column2;
    // std::cout << column1 << " - " << column2 << " - " << column3 << std::endl;
    bin=bin+1;
    h1.SetBinContent( bin, column2 );
    //cout<<bin<<endl;
  }*/
