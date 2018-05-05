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
int npeaks = 30;
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


int main(int argc, char** argv){  

  ifstream file1, file2, file1a;
  ifstream * in;
  ofstream file3;
  double column1, column2;
  int bin=0,nbin=0;

  cout<<"MIRA ABAJO"<<endl;
  cout<<argv[2]<<endl;
  cout<<"MIRA ARRIBA"<<endl;
  
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

  file1.open (  argv[1] , ios::in );  
  TH1I *h1= new TH1I( "h1", "Espectro", nbin , 1, nbin);
  h1->SetTitle("Espectro");
  h1->GetYaxis()->SetTitle("Cuentas/Canal");
  h1->GetYaxis()->CenterTitle();
  h1->GetXaxis()->SetTitle("Canal");
  h1->GetXaxis()->CenterTitle();
  h1->GetXaxis()->SetRangeUser(min,max);
 
  while( !file1.eof() ){
    file1 >> column1 >> column2;
    bin=bin+1;
    h1->SetBinContent( bin, column2 );
    //cout<<bin<<" "<<" "<<column2 <<endl;
    //cout<<bin<<endl;
  }

  TCanvas *C = new TCanvas("Canvas_1", "Canvas_1",258,84,1178,665);
  C->Range(-250.5,-20.7375,2249.5,186.6375);
  C->SetFillColor(0);
  C->SetBorderMode(0);
  C->SetBorderSize(2);
  C->SetFrameBorderMode(0);
  C->SetFrameBorderMode(0);
  C->Divide(1,2);
    C->cd(1);
  h1->SetLineColor(kGreen);
  h1->Draw("");

  int npeaks=10;
  TSpectrum *s=new TSpectrum(npeaks);
  //int nfound = s->Search(h1);
  int nfound = s->Search(h1,5,"",0.008);
  cout<<"Found"<<" "<<nfound  <<" "<<"candidate peaks to fit"<<endl;
  TH1 *hb = s->Background(h1,20, "same");
  C->Update();
 
  C->cd(2);  
  TH1F *h2 = (TH1F*)h1->Clone("h2");
  h2->SetTitle("Ajuste del Espectro");

  TF1 *fline = new TF1("fline","pol1",1,nbin);
  h1->Fit("fline","qn");
  //Loop on all found peaks. Eliminate peaks at the background level
  double parameter[2000];
  parameter[0] = fline->GetParameter(0);
  parameter[1] = fline->GetParameter(1);
  npeaks = 0;
  float *xpeaks = s->GetPositionX();
  for (int p=0;p<nfound;p++) {
    float xp = xpeaks[p];
    int bin = h1->GetXaxis()->FindBin(xp);
    float yp = h1->GetBinContent(bin);
    // if (xp < 800) continue;
    if (yp-TMath::Sqrt(yp) < fline->Eval(xp)) continue;
    parameter[3*npeaks+2] = yp;
    parameter[3*npeaks+3] = xp;
    parameter[3*npeaks+4] = 3;
    npeaks++;
    cout<<xp<<endl;
  }
   

  printf("Found %d useful peaks to fit\n",npeaks);
  TF1 *fit = new TF1("fit",fpeaks,0,nbin,2+3*npeaks);
  fit->SetParameters(parameter);
  fit->SetNpx(nbin);
  h2->Draw("");

  h2->Fit("fit"); 
  
  
  C->Print("espectro.pdf");

 file3.open("Parametros.dat");
 file3 << "i" <<  "\t" << " Altura "  <<"\t" <<"Media"<< "\t" <<" RMS " << "\t" <<"FWHM " << "\t" <<"Cuentas" << endl;
 file3 << "********************************************************************************" <<  endl;
 //i-esimo Pico , Altura , Media , desviacion estandar
 for(int i =1 ; i <= npeaks ; ++i ){
   file3 << i << "\t" <<  fit->GetParameter(3*i-1) << " \t "<< fit->GetParameter(3*i)  <<"\t " << fit->GetParameter(3*i+1) <<"\t " << 2.3482*fit->GetParameter(3*i+1) <<"\t " << sqrt(2*TMath::Pi())*fit->GetParameter(3*i-1)*fit->GetParameter(3*i+1) <<endl;
 }
file3 << "********************************************************************************" <<  endl;
 
 file3.close();
  


  
  
}
  




