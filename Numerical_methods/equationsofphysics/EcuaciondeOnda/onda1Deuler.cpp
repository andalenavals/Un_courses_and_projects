
#include <vector>
#include <string>
#include <iomanip> 
#include <iostream> 
#include <cmath> 

#include <TGraph.h>
#include <TGraph2D.h>
#include <TCanvas.h>
#include <TAxis.h>
#include <TMatrix.h>
#include <TMath.h>
using namespace std;
double L=2.;

double f( double x ){
  double n=6.;
  return sin(n*TMath::Pi()*x/L);
}

int main() 
{
  std::string distribution;
  double 
    minx = 0., maxx = L , 
    mint =  0., maxt = 1.;
  int 
    nx = 30, 
    nt = 20;
  double 
    hx = (double)(maxx - minx)/nx, 
    ht = (double)(maxt - mint)/nt;
  double epsilon = 0.001;
  double c2 = 20.;
  double cx=c2*(ht*ht)/(hx*hx);
  
  
  //Initialization
  TVectorF V( 31 );
  for ( int i = 0; i < nx + 1; ++i ) V[ i ] = 0.;
  
  //Boundary conditions
  // V[ 0 ] = f( minx ) ; 
  //V[ nx ] = f( maxx );
  
  //vector<TVectorF> vec;
  vector<vector<double> > vec;
  
  TVectorF V0( V );
  TVectorF V1( V );
  TVectorF Vtmp( V );
  
  
  for ( int i = 1; i < nx; ++i ){
    double x = minx + (double)i*hx;      
    V0[ i ] = f( x );	
  }
  
  for( int n = 1; n <= nt; ++n ){
    for(int i=1; i<nx; i++){
      Vtmp[i]=cx*( V0[i+1] + V0[i-1] - 2.*V0[i]) + 2.*V0[i])+2.*V0;
    Vtmp[i]/=2.;
  }
  V1=V0;
  V0=Vtmp;
  vec.push_back(Vtmp);
}


for( int n = 0; n<(int)vec.size(); ++n ){
  TGraph g( nx+1 );
  int point = 0;;
  for ( int i = 0; i < nx + 1; ++i )
    double x1 = minx + (double)i*hx;            
  g.SetPoint( point, x1, vec.at(n).at(i));
  
  
  double max=0. , min=0.;
  
  if( n == 0 ){
    max = 1.2 * g.GetYaxis() -> GetXmax();
    min = 0.;
  }
  
  g.SetTitle( " " );
  g.GetYaxis() -> SetRangeUser( -max, max );
  TCanvas c( " ", " ", 1000, 1000 );
  c.cd();
  g.Draw( "AC" );    
  c.Print( "difusion.gif+25" );
  std::cout << "Plotting t " << n << std::endl;
  
 }

return 0;
}
