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

using namespace std;
int main(){  
  /* string espectro , fondo;
  cout<<"Digite la direccion del Espectro"<<endl;
  getline(cin,espectro);
  cout<<"Digite la direccion del Fondo"<<endl;
  getline(cin,fondo);*/

  gStyle->SetOptStat(kFALSE);
 
  ifstream file1, file2,file1a;
  ofstream file3;
  double column1=0, column2;
  int np=2,nbin=0,w=0,w1=0;
 

  file1a.open (  "Ge40_Co60_10min.dat" , ios::in );
  while( !file1a.eof() ){
    file1a >> column1 >> column2;
    nbin+=1;
    //cout<<nbin<<" "<<column1<<" "<<column2 <<endl;
  }
  //cout<<nbin<<endl;
 
      
  double espc[nbin][2];
  file1.open (  "Ge40_Co60_10min.dat" , ios::in );
  while( !file1.eof() ){
    file1 >> column1 >> column2;
    espc[w][1]=column2;
    espc[w][0]=column1;
    w=w+1;
    //cout<<w<<endl;
  }

  double back[nbin][2];
  file2.open (  "Ge40_Background_10min.dat" , ios::in );
  while( !file2.eof() ){
    file2 >> column1 >> column2;
    back[w1][1]=column2;
    back[w1][0]=column1;
    w1=w1+1;
    //cout<<w1<<endl; 
  }


  file3.open("resta.dat");
  for(int i=0; i<nbin;i++){
    //cout <<espc[i][0]<<" " <<espc[i][1]-back[i][1] <<endl;
    file3 << espc[i][0] <<" "  << espc[i][1]-back[i][1]<<"\n";
  }
  file3.close();
 
 


  return 0;  
}




