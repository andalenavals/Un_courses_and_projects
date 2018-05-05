#include <iostream>
#include <cstdlib>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
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


using namespace std;

int main(int argc, char** argv){  
  gStyle->SetOptStat(kFALSE);
  ifstream file1, file2, file1a;
  ifstream * in;
  ofstream file3;
  double column1, column2;
  int bin=0,nbin=0,bin1 =0,bin2=0;

  
 if (argc < 2){
    cerr << "error, please write the input filename ..." << endl;
    exit(1);
  }

  if (argc > 4){
    cerr << "too many parameters" << endl;
    exit(1);
  }

  in= new ifstream(argv[1], ios_base::in);
  if (!in){
    cerr << "input file open error" << endl;
    exit(1);
  }
  
 
  //*******************************************************
  //** Find the number of Channels
  //*******************************************************
  file1a.open (  argv[1], ios::in );
    while( !file1a.eof() ){
    file1a >> column1 >> column2;
    nbin+=1;
    //cout<<nbin<<" "<<column1<<" "<<column2 <<endl;
  }
  cout<<"The Spectrum has "<<nbin<<" Channels" <<endl;
 

  
    double min,max;
    if (string(argv[2]) == "manual") {
    string minimum,maximum;
    cout<<"digite el extremo inferior"<<endl;
    getline(cin,minimum);
    cout<<"digite el extremo superior"<<endl;
    getline(cin,maximum);
    stringstream(minimum)>>min;
    stringstream(maximum)>>max;
   }
    else {
	min=1;
	max= nbin;
      }
    
    // cout<< min << " "<< max <<endl;


   
  //*******************************************************
  //** Convertir Canales en energia
  //*******************************************************  

    double pendiente,corte;
    string pen,cor;
    cout<<"digite la pendiente"<<endl;
    getline(cin,pen);
    cout<<"digite el corte"<<endl;
    getline(cin,cor);
    stringstream(pen)>>pendiente;
    stringstream(cor)>>corte;


    //TCanvas *C = new TCanvas("MyCanvas","", 800,500);
    TCanvas *C = new TCanvas("Canvas_1", "Canvas_1",258,84,1178,665);
    C->Range(-250.5,-20.7375,2249.5,186.6375);
    C->SetFillColor(0);
    C->SetBorderMode(0);
    C->SetBorderSize(2);
    C->SetFrameBorderMode(0);
    C->SetFrameBorderMode(0);
    //C->SetLogy();
    // C->SetLogx()
    
  file1.open (  argv[1] , ios::in );  
  TH1I *h1= new TH1I( "h1", "Espectro", nbin , 1, nbin);
  h1->SetTitle("");
  h1->GetYaxis()->SetTitle("Cuentas/Energia [keV]^{-1}");
  h1->GetYaxis()->CenterTitle();
  h1->GetXaxis()->SetTitle("Energia [keV]");
  h1->GetXaxis()->CenterTitle();
  h1->GetXaxis()->SetRangeUser(min,max);
  //h1->SetMaximum(100);
  //h1->SetMinimum(1);

  while( !file1.eof() ){
    file1 >> column1 >> column2;
    bin=bin+1;
    //h1->SetBinContent(  bin, column2 );
     h1->SetBinContent( pendiente*bin+corte,column2 );
    // h1->SetBinContent( bin , (column2) /36. ) ;
    //cout<<bin<<" "<<" "<<column2 <<endl;
    //cout<<bin<<endl;
  }


  file2.open (  "modeloa.dat" , ios::in );
  TH1I *h2= new TH1I( "h2", "Espectro2", nbin , 1, nbin);
  while( !file2.eof() ){
    file2 >> column1 >> column2;
    bin2=bin2+1;
    h2->SetBinContent(  bin2, column2 );
    h2->GetXaxis()->SetRangeUser(min,max);
    //cout<<bin2<<" "<<" "<<column2 <<endl;
    //cout<<bin<<endl;
  }



  
  h1->Draw("p");
  h2->Draw("same");
  C->Print("canalenergia.pdf");

  return 0; 
  
}
  




