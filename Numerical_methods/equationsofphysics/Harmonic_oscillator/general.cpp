#include <vector>
#include <string>
#include <iomanip> 
#include <iostream> 

#include <TGraph.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TLegend.h>
#include <TAxis.h>
#include <TMath.h>

int main() 
{
  //harmonic oscilator
  int nsteps = 500;
  double min = 0;
  double max = 100.0*TMath::Pi(); 
  double dt = (max - min)/nsteps;
  //constantes
  double koverm = 0.1;
  double boverm=0.2;
  double Foverm=0.3;
  double omega=0.4;
  //condiciones iniciales
  double x0 = 1.;
  double v0 = 0.;


  double x_tmp, v_tmp, t_tmp;

  TGraph x( nsteps ), v( nsteps );
  double xt = x0;
  double vt = v0;
  for( int i = 0; i < nsteps; ++i )
    {
      double t   = min + (double)i*dt;

      double xF1 = vt;
      double vF1 = -koverm*xt-boverm*vt+Foverm*cos(omega*t);
      x_tmp = xt + 0.5*dt*xF1;
      v_tmp = vt + 0.5*dt*vF1;
      t_tmp = t+0.5*dt;

      double xF2 = v_tmp;
      double vF2 = -koverm*x_tmp-boverm*v_tmp+Foverm*cos(omega*t_tmp);
      x_tmp = xt + 0.5*dt*xF2;
      v_tmp = vt + 0.5*dt*vF2;
      t_tmp = t+0.5*dt;

      double xF3 = v_tmp;
      double vF3 =-koverm*x_tmp-boverm*v_tmp+Foverm*cos(omega*t_tmp);
      x_tmp = xt + dt*xF3;
      v_tmp = vt + dt*vF3;
      t_tmp = t+dt;

      double xF4 = v_tmp;
      double vF4 =-koverm*x_tmp-boverm*v_tmp+Foverm*cos(omega*t_tmp);

      double xtdt = xt+dt*(xF1+2.*xF2+2.*xF3+xF4)/6.;
      double vtdt = vt+dt*(vF1+2.*vF2+2.*vF3+vF4)/6.;
      
      x.SetPoint( i, t, xt );
      v.SetPoint( i, t, vt );
      xt = xtdt;
      vt = vtdt;
    }
  
  TCanvas c( "", "", 800, 600 );
  c.cd();
  c.SetTitle( "" );
  //c.SetLogy();
  //c.Update();
  x.SetLineColor( kBlack );
  x.GetXaxis()->SetTitle("Tiempo");
  x.SetTitle("El oscilador armonico");
  //x.SetMinimum(-1);
  x.Draw("AC");
  v.SetLineColor( kRed );
  v.SetLineStyle( kDashed );
  v.Draw("same");
  

  /* TF1 f("","cos([0]*x)", min, max );
  f.SetParameter(0,sqrt(koverm));
  f.SetLineStyle( kDashed );
  f.SetLineColor( kBlue );
  f.Draw( "SAME" );*/

  TLegend leg( 0.7,0.7,0.9,0.9,"");
  leg.AddEntry( &x, "Posicion", "l");
  leg.AddEntry( &v, "Velocidad", "l");
  //leg.AddEntry(&f,"Posicion analitica", "l");
  leg.Draw("SAME");

  c.Print( "oacasog3.pdf" );
  return 0;
}
