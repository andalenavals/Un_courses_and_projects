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


double f( double x, double y ){
  return exp( -x*x - y*y );
}

int main() 
{
  //std::string distribution;
  double 
    minx = -5., maxx = 5., 
    miny = -5., maxy = 5.,
    mint =  0., maxt = 1.;
  int 
    nx = 30, 
    ny = 30, 
    nt = 100;
  double 
    hx = (double)(maxx - minx)/nx, 
    hy = (double)(maxy - miny)/ny, 
    ht = (double)(maxt - mint)/nt;
  double epsilon = 0.0001;
  double c2 = 20.;
  double 
    k1 = c2*ht/(hx*hx),
    k2 = c2*ht/(hy*hy),
    k3 = 1 + c2*ht*((1/(hx*hx))+(1/(hy*hy)));

  TMatrix V( nx + 1, ny + 1 );
  for ( int i = 0; i < nx + 1; ++i )
    for ( int j = 0; j < ny + 1; ++j )
      V[ i ][ j ] = 0.;

  //Boundary conditions
  for ( int i = 0; i < nx + 1; ++i ) { V[ i ][ 0 ] = 0. ; V[ i ][ ny ] = 0.; }    
  for ( int i = 0; i < ny + 1; ++i ) { V[ 0 ][ i ] = 0. ; V[ nx ][ i ] = 0.; }    

  //
  std::vector<TMatrix> vec;

  TMatrix Vtmp( V );
  TMatrix Vk( V );

  bool convergence = false; 
  int niter = 0;    
  

  for ( int i = 1; i < nx; ++i ){
    for ( int j = 1; j < ny; ++j ){
      double x = minx + (double)i*hx;      
      double y = miny + (double)j*hy;      
      Vtmp[ i ][ j ] = f( x, y );	
    }
  }
  Vk = Vtmp;
    
  vec.push_back( Vk );
  TMatrix Vn( Vk );
  for( int n = 1; n <= nt; ++n ){
	convergence = false; 
    niter = 0; 
    //Vk = vec[n-1];
	while( !convergence ){
       
    for ( int i = 1; i < nx; ++i ){
      for ( int j = 1; j < ny; ++j ){
	/*Vn[ i ][ j ]  = Vk[ i ][ j ];
	Vn[ i ][ j ] += (( 0.5*Vk[ i+1 ][ j ] - Vk[ i ][ j ] + 0.5*Vk[ i-1 ][ j ] + 0.5*Vtmp[i+1][j] + 0.5*Vtmp[i-1][j])*k1);
	Vn[ i ][ j ] += (( 0.5*Vk[ i ][ j+1 ] - Vk[ i ][ j ] + 0.5*Vk[ i ][ j-1 ] + 0.5*Vtmp[i][j+1] + 0.5*Vtmp[i][j-1])*k2);
	Vn[ i ][ j ] /= k3;*/
	
	Vn[ i ][ j ]  = Vk[ i ][ j ]*( 1./ht - c2/hx/hx - c2/hy/hy );
	Vn[ i ][ j ] += 0.5*c2*( ( Vk[ i+1 ][ j ] + Vk[ i-1 ][ j ] )/hx/hx + ( Vk[ i ][ j+1 ] + Vk[ i ][ j-1 ])/hy/hy );
    Vn[ i ][ j ] += 0.5*c2*( ( Vtmp[ i+1 ][ j ] + Vtmp[ i-1 ][ j ] )/hx/hx + ( Vtmp[ i ][ j+1 ] + Vtmp[ i ][ j-1 ])/hy/hy );
	Vn[ i ][ j ] /= ( 1./ht + c2/hx/hx + c2/hy/hy );
      }
    }
    
    
    
        TMatrix diff = Vn - Vtmp;
    for ( int i = 1; i < nx; ++i )
      for ( int j = 1; j < ny; ++j )
	if( fabs( diff[ i ][ j ] ) > epsilon ){
	  convergence = false;
	  break;
	}
	else convergence = true; 
    ++niter;
    Vtmp = Vn;
    std::cout << "Iteration number " << niter << " " <<n << std::endl;
  }
   vec.push_back( Vn );   
   Vk=Vn;
}
  
  double max = 0.; 
  double min = 0.;

  for( int n = 0; n<(int)vec.size(); ++n ){
    TGraph2D g( (nx+1)*(ny+1) );
    int point = 0;
    Vtmp = vec[ n ];
    for ( int i = 0; i < nx + 1; ++i )
      for ( int j = 0; j < ny + 1; ++j ){
	double x = minx + (double)i*hx;      
	double y = miny + (double)j*hy;      
	g.SetPoint( point, x, y, Vtmp[ i ][ j ] );
	++point;
      }
    
    if( n == 0 ){
      /*max = 1.2 * g.GetZaxis() -> GetXmax();
      min = -1.2;*/
      max = 1.;
      min = 0.;
    }

    g.SetTitle( " " );
    g.GetZaxis() -> SetRangeUser( 0., 1. );
    TCanvas c( " ", " ", 1000, 1000 );
    c.cd();
    g.Draw( "SURF1" );    
    c.Print( "difusion.gif+25" );
    std::cout << "Plotting t " << n << std::endl;
}

  
  return 0;
}
