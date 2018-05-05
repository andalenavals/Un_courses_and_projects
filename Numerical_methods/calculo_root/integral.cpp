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




double funcion(double x){
  double f;
  f=pow(x,6)-14*pow(x,4)+49*pow(x,2)-3;
  //f=pow(x,2)-5*x-2;
  return f;
}

double integral(double min, double max, char tipo){
  double x, sum=0,partes=100;   //duda como llamo a partes del main sin declararlo como parametro de la funcion
  double dx=(max-min)/partes ;
  if (tipo == 'r' ){
    for(int i=0 ; i<partes ; i++){
      x=min+i*dx;
      sum=sum+funcion(x)*dx;
    }
    return sum; 
  }
  else if(tipo== 't'){
    for(int i=0 ; i<partes ; i++){
      x=min+i*dx;
      sum=sum+(funcion(x)+funcion(x+dx))*0.5*dx;
    }
    return sum; 
  }
  else if(tipo=='s'){
    for(int i=0 ; i<partes ; i++){
      x=min+i*dx;
      sum=sum+(funcion(x)+funcion(x+dx)+4*funcion(x+(dx/2.)))*(dx/6.);
    }
     return sum; 
    }

  else{
      return 0;
    }
}


	
int main(){
  
  string minimum,maximum,partitium;
  cout<<"Digite el extremo inferior"<<endl;
  getline(cin,minimum);
  cout<<"Digite el extremo superior"<<endl;
  getline(cin,maximum);
  cout<<"Digite el numero de partes en que divide el intervalo"<<endl;
  getline(cin,partitium);
  double min,max,partes,x;
  stringstream(minimum)>>min;
  stringstream(maximum)>>max;
  stringstream(partitium)>>partes;
  double dx=(max-min)/partes;
  
  cout<<"integral por rectangulos: "<<integral(min,max,'r')<<endl;
  cout<<"integral por trapecios: "<<integral(min,max,'t')<<endl;
  cout<<"integral por simpson: "<<integral(min,max,'s')<<endl;
  
  


 TF1 func("function","pow(x,6)-14*pow(x,4)+49*pow(x,2)-3",min,max);

 TCanvas c("canvas","",500,500);
 c.Divide(1,2);
 
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
    g.SetPoint(i,x,integral(min,x,'s'));
 } 
 g.SetTitle("funcion acumulativa");
 g.Draw("AC");
 

 c.Print("integral.pdf");
 
 return 0;
}

