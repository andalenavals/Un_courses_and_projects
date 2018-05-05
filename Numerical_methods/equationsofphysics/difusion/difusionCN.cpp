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
  return exp( -x*x )*exp( -y*y );
  //return pow(sin(pow(x,4)+pow(y,4)),2)/pow((pow(x,4)+pow(y,4)),2);
  //return cos( x*x +y*x);
  //return x*x +y*y; 
  //return (x*x+3*y*x)*exp(1-x*x-y*x); 
  //return exp( -(x+2)*(x+2)/1.5-(y+2)*(y+2)/1.5 ) +4.*exp( -(x-2)*(x-2)/1.5 -(y-2)*(y-2)/1.5) + 2.*exp( (-y*y -x*x)/1.5 ) ;
}

int main() 
{

  double 
    minx = -5., maxx = 5., 
    miny = -5., maxy = 5., 
    mint =  0., maxt = 1.;
  int 
    nx = 10, 
    ny = 10, 
    nt = 50;
  double 
    hx = (double)(maxx - minx)/nx, 
    hy = (double)(maxy - miny)/ny, 
    ht = (double)(maxt - mint)/nt;
  double epsilon = 0.0001;
  double c2 = 20.;

  TMatrix V( nx + 1, ny + 1 );
  for ( int i = 0; i < nx + 1; ++i )
    for ( int j = 0; j < ny + 1; ++j )
      V[ i ][ j ] = 0.;

  //Boundary conditions
  for ( int i = 0; i < nx + 1; ++i ) { V[ i ][ 0 ] = 0. ; V[ i ][ ny ] = 0.; }    
  for ( int j = 0; j < ny + 1; ++j ) { V[ 0 ][ j ] = 0. ; V[ nx ][ j ] = 0.; }    

  //
  std::vector<TMatrix> vec;

  TMatrix Vtmp( V );
  TMatrix Vk( V );

  for ( int i = 0; i < nx+1; ++i )
    for ( int j = 0; j < ny+1; ++j ){
      double x = minx + (double)i*hx;      
      double y = miny + (double)j*hy;
      Vtmp[ i ][ j ] = f( x, y );	
    }
    
  Vk = Vtmp;
  vec.push_back( Vk );
  TMatrix Vn( Vtmp );
  for( int n = 1; n <= nt; ++n ){
    bool convergence = false;
    int niter = 0;
    while ( !convergence ){
      for ( int i = 1; i < nx; ++i ){
	for ( int j = 1; j < ny; ++j ){
	  Vn[ i ][ j ]  = Vk[ i ][ j ]*( 1./ht - c2/hx/hx - c2/hy/hy );
	  Vn[ i ][ j ] += 0.5*c2*( ( Vk[ i+1 ][ j ] + Vk[ i-1 ][ j ] )/hx/hx + ( Vk[ i ][ j+1 ] + Vk[ i ][ j-1 ])/hy/hy );
	  Vn[ i ][ j ] += 0.5*c2*( ( Vtmp[ i+1 ][ j ] + Vtmp[ i-1 ][ j ] )/hx/hx + ( Vtmp[ i ][ j+1 ] + Vtmp[ i ][ j-1 ])/hy/hy );
	  Vn[ i ][ j ] /= ( 1./ht + c2/hx/hx + c2/hy/hy );
	}
      }
      TMatrix diff = Vtmp - Vn;
      
      for ( int i = 0; i < nx; ++i )
	for ( int j = 0; j < ny; ++j )
	  if( fabs( diff[ i ][ j ] ) > epsilon ){
	    convergence = false;
	    break;
	  }
	  else convergence = true;      
      Vtmp = Vn;
      ++niter;
    }
    std::cout<< n << "-" <<niter <<" t-iterations"<< std::endl;
    vec.push_back( Vn );
    Vk = Vn;
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
      max = g.GetZmax();
      min = g.GetZmin();
    }


    g.SetTitle( " " );
    g.SetMaximum( 1 );
    TCanvas c( " ", " ", 1800, 600 );
    c.cd( );
    g.Draw( "SURF" );
    
    c.Print( "difusionCN.gif+50" );
    //std::cout << "Plotting t " << n << std::endl;

  }
  
  return 0;
}
