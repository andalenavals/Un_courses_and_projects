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
#include <TVectorF.h>

#include <TMath.h>

double f( double x ){
  return exp( -(x)*(x)/0.5 );
  //  return exp( -(x-2.)*(x-2.)/0.1 )+exp(-(x+2.)*(x+2.)/0.1);
}

int main() 
{
  double 
    minx = -4., maxx = 4., 
    mint =  0., maxt = 1.55;
  int 
    nx = 50, 
    nt = 50;
  double 
    hx = (double)(maxx - minx)/nx, 
    ht = (double)(maxt - mint)/nt;
  double c2 = 0.5;

  TVectorF V( nx + 1 );
  for ( int i = 0; i < nx + 1; ++i ) V[ i ] = 0.;

  //Boundary conditions
  V[ 0 ]  = f( minx );
  V[ nx ] = f( maxx );     

  //
  std::vector<TVectorF> vec;

  TVectorF Vtmp( V );
  TVectorF Vk( V );

  for ( int i = 1; i < nx; ++i ){
    double x = minx + (double)i*hx;      
    Vtmp[ i ] = f( x );	
  }
    
  Vk = Vtmp;
    
  vec.push_back( Vk );
  TVectorF Vn( Vk );
  for( int n = 1; n <= nt; ++n ){
    for ( int i = 1; i < nx; ++i ){
      Vn[ i ]  = Vk[ i ];
      Vn[ i ] += ( Vk[ i+1 ] - 2.*Vk[ i ] + Vk[ i-1 ] )*c2*ht/hx/hx;
    }
    vec.push_back( Vn );
    Vk = Vn;
  }
  
  
  double max = 0.; 
  double min = 0.;

  for( int n = 0; n<(int)vec.size(); ++n ){
    TGraph g( nx+1 );
    int point = 0;
    Vtmp = vec[ n ];
    for ( int i = 0; i < nx + 1; ++i ){
      double x = minx + (double)i*hx;     
      g.SetPoint( point, x, Vtmp[ i ] );
    ++point;
  }
    
    if( n == 0 ){
      max = 1.2 * g.GetMaximum();
      min = 0.;
    }
    
    g.SetTitle( " " );
    g.GetYaxis() -> SetRangeUser( -max, max );
    TCanvas c( " ", " ", 1000, 1000 );
    c.cd();
    g.Draw( "AC" );    
    c.Print( "difusion1D.gif+25" );
    std::cout << "Plotting t " << n << std::endl;

  }
  
  return 0;
}
