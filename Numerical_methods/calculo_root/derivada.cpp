#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>
#include "TF1.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TAxis.h"
#include "TGraph.h"
 
using namespace std;

double dx, df, ddf, x;
//vector<double> df,ddf, x;

double funcion(double x){
  double f;
  f=pow(x,6)-14*pow(x,4)+49*pow(x,2)-3;
  //f=pow(x,2)-5*x-2;
  return f;
}

int main(){

  string minimum,maximum,partitium;
  cout<<"digite el extremo inferior"<<endl;
  getline(cin,minimum);
  cout<<"digite el extremo superior"<<endl;
  getline(cin,maximum);
  cout<<"Digite el numero de partes en que divide el intervalo"<<endl;
  getline(cin,partitium);
  double min,max,partes;
  stringstream(minimum)>>min;
  stringstream(maximum)>>max;
  stringstream(partitium)>>partes;
  dx=(max-min)/partes ;

 TF1 func("function","pow(x,6)-14*pow(x,4)+49*pow(x,2)-3",min,max);

 TCanvas c("canvas","",500,500);
 c.Divide(1,3);
 
 c.cd(1);
 func.SetTitle("funcion");
 func.GetXaxis()->SetTitle("eje x");
 func.GetXaxis()->CenterTitle();
 func.GetYaxis()->SetTitle("eje y");
 func.GetYaxis()->CenterTitle();
 func.SetLineColor(kBlue);
 func.Draw();
 
 c.cd(2);
 TGraph g(1);
 for(int i=0; i<partes ; i++){
    x=min+i*dx;
    df=(funcion(x+dx)-funcion(x-dx))/2*dx;
    g.SetPoint(i,x,df);
  } 
 g.SetTitle("primera derivada");
 g.Draw("AC");
 

 c.cd(3);
 TGraph h(1);
 for(int i=0; i<partes ; i++){
   x=min+i*dx;
   ddf=(funcion(x+dx)+funcion(x-dx)-2*funcion(x))/(dx*dx);
   h.SetPoint(i,x,ddf);
 } 
 h.SetTitle("segunda derivada");
 h.Draw("AC");
 
 c.Print("derivada.pdf");

return 0;
}

