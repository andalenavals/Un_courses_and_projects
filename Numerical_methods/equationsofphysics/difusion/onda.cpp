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
double L=20.;

double f( double x ){
	double n=8.;
    return 5.*sin(n*TMath::Pi()*x/L);
}

int main(){
	double minx =0., maxx=L,
	       mint=0., maxt=10.;
	
	int nx=100, nt=50;
	
	double hx = (double)(maxx - minx)/nx,
	       ht = (double)(maxt - mint)/nt,
	       epsilon=0.001, c2=10, cx=c2*ht*ht/(hx*hx);
	vector<double> V;
	for(int i=0; i < nx +1; i++) V.push_back(0.);
	vector<double> Vn0(V);
	vector<double> Vn1(V);
	vector<double> Vn2(V);
	vector<vector<double> > vec;
	for ( int j = 1; j < nx; ++j ){
      double x = minx + (double)j*hx;
      Vn1[j]=f(x);
    }
    for( int n = 1; n <= nt; ++n ){
		for(int i=1; i<nx; i++){
			Vn2[i]=cx*( Vn1[i+1] + Vn1[i-1] - 2.*Vn1[i]) + 2.*Vn1[i];
			Vn2[i]/=2.;
		}
		Vn0=Vn1;
		Vn1=Vn2;
		vec.push_back(Vn2);
	}
	
	 for( int n = 0; n<(int)vec.size(); ++n ){
    TGraph g( nx+1 );
    int point = 0;
    for ( int i = 0; i < nx + 1; ++i ){
	double x1 = minx + (double)i*hx;      
	g.SetPoint( point, x1, vec.at(n).at(i));
	++point;
    }
    double max = 0.; 
    double min = 0.;
    
    
    if( n == 0 ){
      max = 1.2 * g.GetYaxis() -> GetXmax();
      min = 0;
    }

    g.SetTitle( " " );
    g.GetXaxis() -> SetRangeUser( 0, 20);
    g.GetYaxis() -> SetRangeUser( -10.2, 10.2);
    g.GetYaxis() -> SetTitle("Amplitud");
    g.GetYaxis() -> CenterTitle();
    g.GetXaxis() -> SetTitle("Posicion");
    g.GetXaxis() -> CenterTitle();
    TCanvas c( " ", " ", 1000, 1000 );
    c.cd();
    g.Draw( "AC" );    
    c.Print( "onda.gif+25" );
    std::cout << "Plotting t " << n << std::endl;

}
	
	return 0;
}
