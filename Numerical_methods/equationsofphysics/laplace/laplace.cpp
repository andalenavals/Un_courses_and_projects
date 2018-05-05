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
using namespace std;

int main() 
{
  
  double minx = -1., maxx = 1., miny = -1., maxy = 1.;
  int nx = 100, ny = 100;
  double hx = (double)(maxx - minx)/nx, hy = (double)(maxy - miny)/ny;
  double epsilon = 0.00001;
  double x,y;
  
  //Initialization (antzas)
  TMatrix V( nx + 1, ny + 1 );
  for ( int i = 0; i < nx + 1; ++i )
    for ( int j = 0; j < ny + 1; ++j )
      V[ i ][ j ] = 1;
  
  //Boundary conditions
  for ( int i = 0; i < nx + 1; ++i ) { 
    V[ i ][ 0 ] = 0.  ; V[ i ][ ny ] = 0.;   
  }    
  for ( int j = 0; j < ny + 1; ++j ) { 

    V[ 0 ][ j ] = 0. ; V[ nx ][ j ] = 0.; 
  } 

  TMatrix Vtmp( V );
  TMatrix Vk( V );

  bool convergence = false; 
  int niter = 0;
  
  while( !convergence ){
    for ( int i = 1; i < nx; ++i ){
      for ( int j = 1; j < ny; ++j ){
	Vtmp[ i ][ j ] = 0.5*( hy*hy*( Vk[ i+1 ][ j ] + Vk[ i-1 ][ j ] ) + hx*hx*( Vk[ i ][ j+1 ] + Vk[ i ][ j-1 ]) )/( hx*hx+hy*hy );
	x = minx + (double)i*hx;
	y = miny + (double)j*hy;
	//if( x>-0.5 && x<0.5 && fabs(y-0.5)<0.05) Vtmp[i][j]= 100.;
	if( x*x + y*y < 0.1) Vtmp[i][j]= 100.;
	if( y>-0.5 && y<0.5 && fabs(x+0.5)<0.05) Vtmp[i][j]=-100.;
	//cout<<Vk[i][j]<<endl;
      }
    }
    
    // check convergence (metodo de relajacion)
    TMatrix diff = Vtmp - Vk;
    for ( int i = 1; i < nx; ++i )
      for ( int j = 1; j < ny; ++j )
	if( fabs( diff[ i ][ j ] ) > epsilon ){
	  convergence = false;
	  break;
	}
	else convergence = true;

    Vk = Vtmp;
    ++niter;
    std::cout << "Iteration number " << niter << std::endl;
  }

  TGraph2D g( (nx+1)*(ny+1) );
  int point = 0;
  for ( int i = 0; i < nx + 1; ++i )
    for ( int j = 0; j < ny + 1; ++j ){
      double x = minx + (double)i*hx;      
      double y = miny + (double)j*hy;      
      g.SetPoint( point, x, y, Vk[ i ][ j ] );
      ++point;
    }
 
  TCanvas c( " ", " ", 1000, 1000 );
  c.Divide( 2, 2 );
  g.SetTitle( "" );
  c.cd( 1 );
  g.Draw( "CONT1" );
  c.cd( 2 );
  g.Draw( "SURF3" );
  c.cd( 3 );
  g.Draw( "ARR" );
  c.cd( 4 );
  g.Draw( "SURF1" );
  
  c.Print( "anilllo.pdf" );
  return 0;
}
