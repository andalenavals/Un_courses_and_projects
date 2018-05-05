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
    return 5*sin(n*TMath::Pi()*x/L);
}

int main(){
	double minx =0., maxx=L,
	       mint=0., maxt=5.;
	
	int nx=40, nt=40;
	
	double hx = (double)(maxx - minx)/nx,
	       ht = (double)(maxt - mint)/nt,
	       epsilon=0.01, c2=10, cx=c2*ht*ht/(hx*hx);
	vector<double> V;
	for(int i=0; i < nx +1; i++) V.push_back(0.);
	vector<double> Vn0(V);
	vector<double> Vn1(V);
	vector<double> Vn2(V);
	vector<double> Vtmp(V);
	vector<vector<double> > vec;
	for ( int j = 1; j < nx; ++j ){
      double x = minx + (double)j*hx;
      Vn0[j]=f(x);
    } 
    vec.push_back(Vn0);
    bool convergence = false; 
    int niter = 0;    
    while( !convergence ){
		Vtmp=Vn1;
		for(int i=1; i<nx; i++){
			Vn1[i] = 2.*Vn0[i] + cx*(Vtmp[i+1] + Vtmp[i-1]);
			Vn1[i]/=2. + 2.*cx;
		}
			vector<double> diff(Vn1);
			for(int l=0; l<(int)Vn1.size(); l++)diff[l] = Vn1[l] - Vtmp[l];
			for(int j=1; j<nx; j++){
				if( fabs( diff[j] )>epsilon){
					convergence=false;
					break;
				}
				else convergence=true;
				++niter;
				//std::cout << "Iteration number " << niter << std::endl;
			}
		}
	vec.push_back(Vn1);	
	for(int n=1; n<nt; n++){
    bool convergence = false; 
    int niter = 0;    
    while( !convergence ){
		Vtmp=Vn2;
		for(int i=1; i<nx; i++){
			Vn2[i] = -Vn0[i] + 2.*Vn1[i] + (cx/2.)*(Vtmp[i+1] + Vtmp[i-1] - 2.*Vtmp[i]);
			Vn2[i] += (cx/2.)*(Vn0[i+1] + Vn0[i-1] - 2.*Vn0[i]);
		}			
			vector<double> diff1(Vn2);
			for(int l=0; l<(int)Vn2.size(); l++)diff1[l] = Vn2[l] - Vtmp[l];
			for(int j=1; j<nx; j++){
				if( fabs(diff1[j])>epsilon){
					convergence=false;
					break;
				}
				else convergence=true;
				++niter;
				//	std::cout << "Iteration number " << niter << " " <<n << std::endl;
			}
		}
	
	vec.push_back(Vn2);
	Vn0=Vn1;
	Vn1=Vn2;
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
    c.Print( "onda1.gif+15" );
    std::cout << "Plotting t " << n << std::endl;

}
	
	return 0;
}
