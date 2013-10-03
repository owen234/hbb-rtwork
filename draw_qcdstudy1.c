
#include "TCanvas.h"
#include "TLine.h"
#include "TBox.h"
#include "TH1.h"
#include "TH2.h"
#include "TStyle.h"
#include "TF1.h"

#include "histio.c"

   void draw_qcdstudy1( const char* infile = "outputfiles/qcd_study1.root" ) {

      gDirectory -> Delete("h*") ;

      gStyle -> SetOptStat("MRi") ;
      gStyle -> SetPadBottomMargin( 0.15 ) ;

      loadHist( infile ) ;

      TLine* line = new TLine() ;
      TBox* box = new TBox() ;
      box -> SetFillStyle(0) ;
      double hmax ;
      double hmin(0.1) ;

      TF1* func(0x0) ;


      //====== HT plots ----------------------------------------------------------------------------------------

      TH1F* h_ht_qcd1 = (TH1F*) gDirectory -> FindObject( "h_ht_qcd1" ) ;
      if ( h_ht_qcd1 == 0x0 ) { printf("\n\n\n *** missing histograms in %s\n\n", infile ) ; return ; }
      TH1F* h_ht_qcd2 = (TH1F*) gDirectory -> FindObject( "h_ht_qcd2" ) ;
      TH1F* h_ht_qcd3 = (TH1F*) gDirectory -> FindObject( "h_ht_qcd3" ) ;
      TH1F* h_ht_qcd  = (TH1F*) gDirectory -> FindObject( "h_ht_qcd" ) ;
      TH1F* h_ht_ttbar  = (TH1F*) gDirectory -> FindObject( "h_ht_ttbar" ) ;

      TCanvas* c_ht_qcd = new TCanvas( "c_ht_qcd", "QCD, HT", 700, 500 ) ;
      h_ht_qcd -> SetLineWidth(2) ;
      h_ht_qcd1 -> SetLineWidth(2) ;
      h_ht_qcd2 -> SetLineWidth(2) ;
      h_ht_qcd3 -> SetLineWidth(2) ;
      h_ht_qcd1 -> SetLineColor(2) ;
      h_ht_qcd2 -> SetLineColor(3) ;
      h_ht_qcd3 -> SetLineColor(4) ;
      h_ht_qcd -> SetXTitle( "HT (GeV)" ) ;
      h_ht_qcd -> SetTitleSize( 0.060, "x" ) ;

      h_ht_qcd -> Draw("hist") ;
      h_ht_qcd -> Draw("same") ;
      h_ht_qcd1 -> Draw("same") ;
      h_ht_qcd2 -> Draw("same") ;
      h_ht_qcd3 -> Draw("same") ;
      h_ht_qcd1 -> Draw("hist same") ;
      h_ht_qcd2 -> Draw("hist same") ;
      h_ht_qcd3 -> Draw("hist same") ;
      h_ht_qcd -> Draw("same hist") ;
      h_ht_qcd -> Draw("same") ;

      c_ht_qcd -> SaveAs( "outputfiles/h_ht_qcd.pdf" ) ;

      TCanvas* c_ht_ttbar = new TCanvas( "c_ht_ttbar", "ttbar, HT", 700, 500 ) ;
      h_ht_ttbar -> SetLineWidth(2) ;
      h_ht_ttbar -> SetXTitle( "HT (GeV)" ) ;
      h_ht_ttbar -> SetTitleSize( 0.060, "x" ) ;

      h_ht_ttbar -> Draw("hist") ;
      h_ht_ttbar -> Draw("same") ;

      c_ht_ttbar -> SaveAs( "outputfiles/h_ht_ttbar.pdf" ) ;

      //====== Ave mass plots ----------------------------------------------------------------------------------------

      TCanvas* c_avem = new TCanvas( "c_avem", "Ave mass", 700, 500 ) ;


      TH1F* h_avem_nometsig_nobtag_nomindphi = (TH1F*) gDirectory -> FindObject( "h_avem_nometsig_nobtag_nomindphi" ) ;
      TH1F* h_avem_nometsig_nobtag           = (TH1F*) gDirectory -> FindObject( "h_avem_nometsig_nobtag" ) ;
      TH1F* h_avem_nometsig                  = (TH1F*) gDirectory -> FindObject( "h_avem_nometsig" ) ;
      TH1F* h_avem_nobtag                    = (TH1F*) gDirectory -> FindObject( "h_avem_nobtag" ) ;
      TH1F* h_avem_allcuts                   = (TH1F*) gDirectory -> FindObject( "h_avem_allcuts" ) ;
      TH1F* h_avem_ttbar_allcuts             = (TH1F*) gDirectory -> FindObject( "h_avem_ttbar_allcuts" ) ;

     //-----

      h_avem_nometsig_nobtag_nomindphi -> SetLineWidth(2) ;
      h_avem_nometsig_nobtag_nomindphi -> SetLineColor(2) ;
      h_avem_nometsig_nobtag_nomindphi -> SetXTitle( "<m_{jj}> (GeV)" ) ;

      hmax = 1.2 * ( h_avem_nometsig_nobtag_nomindphi->GetMaximum() ) ;
      h_avem_nometsig_nobtag_nomindphi -> SetMaximum( hmax ) ;
      h_avem_nometsig_nobtag_nomindphi -> Draw( "hist" ) ;
      line -> SetLineStyle(1) ;
      line -> DrawLine( 100., 0., 100., hmax ) ;
      line -> DrawLine( 140., 0., 140., hmax ) ;
      line -> SetLineStyle(2) ;
      line -> DrawLine(  90., 0.,  90., hmax ) ;
      line -> DrawLine( 150., 0., 150., hmax ) ;
      h_avem_nometsig_nobtag_nomindphi -> Draw( "same" ) ;

      c_avem -> Update() ; c_avem -> Draw() ;
      c_avem -> SaveAs( "outputfiles/h_avem_nometsig_nobtag_nomindphi.pdf" ) ;


     //-----

      h_avem_ttbar_allcuts -> SetLineWidth(2) ;
      h_avem_ttbar_allcuts -> SetLineColor(4) ;
      h_avem_ttbar_allcuts -> SetXTitle( "<m_{jj}> (GeV)" ) ;
      hmax = 1.2 * ( h_avem_ttbar_allcuts->GetMaximum() ) ;
      h_avem_ttbar_allcuts -> SetMaximum( hmax ) ;

      h_avem_ttbar_allcuts -> Draw( "hist" ) ;
      line -> SetLineStyle(1) ;
      line -> DrawLine( 100., 0., 100., hmax ) ;
      line -> DrawLine( 140., 0., 140., hmax ) ;
      line -> SetLineStyle(2) ;
      line -> DrawLine(  90., 0.,  90., hmax ) ;
      line -> DrawLine( 150., 0., 150., hmax ) ;
      h_avem_ttbar_allcuts -> Draw( "same" ) ;

      c_avem -> Update() ; c_avem -> Draw() ;
      c_avem -> SaveAs( "outputfiles/h_avem_ttbar_allcuts.pdf" ) ;



     //-----

      h_avem_nometsig_nobtag -> SetLineWidth(2) ;
      h_avem_nometsig_nobtag -> SetLineColor(1) ;
      h_avem_nometsig_nobtag -> SetMarkerStyle(20) ;
      h_avem_nometsig_nobtag -> SetXTitle( "<m_{jj}> (GeV)" ) ;

      h_avem_nometsig_nobtag_nomindphi -> Scale( (h_avem_nometsig_nobtag->Integral())/(h_avem_nometsig_nobtag_nomindphi->Integral()) ) ;

      hmax = 1.2 * ( h_avem_nometsig_nobtag->GetMaximum() ) ;
      h_avem_nometsig_nobtag -> SetMaximum( hmax ) ;
      h_avem_nometsig_nobtag -> Draw( ) ;
      line -> SetLineStyle(1) ;
      line -> DrawLine( 100., 0., 100., hmax ) ;
      line -> DrawLine( 140., 0., 140., hmax ) ;
      line -> SetLineStyle(2) ;
      line -> DrawLine(  90., 0.,  90., hmax ) ;
      line -> DrawLine( 150., 0., 150., hmax ) ;
      h_avem_nometsig_nobtag_nomindphi -> Draw( "hist same" ) ;
      h_avem_nometsig_nobtag_nomindphi -> Draw( "same" ) ;
      h_avem_nometsig_nobtag -> Draw( "same" ) ;

      c_avem -> Update() ; c_avem -> Draw() ;
      c_avem -> SaveAs( "outputfiles/h_avem_nometsig_nobtag.pdf" ) ;


     //-----

      h_avem_nometsig -> SetLineWidth(2) ;
      h_avem_nometsig -> SetLineColor(1) ;
      h_avem_nometsig -> SetMarkerStyle(20) ;
      h_avem_nometsig -> SetXTitle( "<m_{jj}> (GeV)" ) ;

      h_avem_nometsig_nobtag_nomindphi -> Scale( (h_avem_nometsig->Integral())/(h_avem_nometsig_nobtag_nomindphi->Integral()) ) ;

      hmax = 1.2 * ( h_avem_nometsig->GetMaximum() ) ;
      h_avem_nometsig -> SetMaximum( hmax ) ;
      h_avem_nometsig -> Draw( ) ;
      line -> SetLineStyle(1) ;
      line -> DrawLine( 100., 0., 100., hmax ) ;
      line -> DrawLine( 140., 0., 140., hmax ) ;
      line -> SetLineStyle(2) ;
      line -> DrawLine(  90., 0.,  90., hmax ) ;
      line -> DrawLine( 150., 0., 150., hmax ) ;
      h_avem_nometsig_nobtag_nomindphi -> Draw( "hist same" ) ;
      h_avem_nometsig_nobtag_nomindphi -> Draw( "same" ) ;
      h_avem_nometsig -> Draw( "same" ) ;

      c_avem -> Update() ; c_avem -> Draw() ;
      c_avem -> SaveAs( "outputfiles/h_avem_nometsig.pdf" ) ;


     //-----

      h_avem_nobtag -> SetLineWidth(2) ;
      h_avem_nobtag -> SetLineColor(1) ;
      h_avem_nobtag -> SetMarkerStyle(20) ;
      h_avem_nobtag -> SetXTitle( "<m_{jj}> (GeV)" ) ;

      h_avem_nometsig_nobtag_nomindphi -> Scale( (h_avem_nobtag->Integral())/(h_avem_nometsig_nobtag_nomindphi->Integral()) ) ;

      hmax = 1.2 * ( h_avem_nobtag->GetMaximum() ) ;
      h_avem_nobtag -> SetMaximum( hmax ) ;
      h_avem_nobtag -> Draw( ) ;
      line -> SetLineStyle(1) ;
      line -> DrawLine( 100., 0., 100., hmax ) ;
      line -> DrawLine( 140., 0., 140., hmax ) ;
      line -> SetLineStyle(2) ;
      line -> DrawLine(  90., 0.,  90., hmax ) ;
      line -> DrawLine( 150., 0., 150., hmax ) ;
      h_avem_nometsig_nobtag_nomindphi -> Draw( "hist same" ) ;
      h_avem_nometsig_nobtag_nomindphi -> Draw( "same" ) ;
      h_avem_nobtag -> Draw( "same" ) ;

      c_avem -> Update() ; c_avem -> Draw() ;
      c_avem -> SaveAs( "outputfiles/h_avem_nobtag.pdf" ) ;


     //-----

      h_avem_allcuts -> SetLineWidth(2) ;
      h_avem_allcuts -> SetLineColor(1) ;
      h_avem_allcuts -> SetMarkerStyle(20) ;
      h_avem_allcuts -> SetXTitle( "<m_{jj}> (GeV)" ) ;

      h_avem_nometsig_nobtag_nomindphi -> Scale( (h_avem_allcuts->Integral())/(h_avem_nometsig_nobtag_nomindphi->Integral()) ) ;

      hmax = 1.2 * ( h_avem_allcuts->GetMaximum() ) ;
      h_avem_allcuts -> SetMaximum( hmax ) ;
      h_avem_allcuts -> Draw( ) ;
      line -> SetLineStyle(1) ;
      line -> DrawLine( 100., 0., 100., hmax ) ;
      line -> DrawLine( 140., 0., 140., hmax ) ;
      line -> SetLineStyle(2) ;
      line -> DrawLine(  90., 0.,  90., hmax ) ;
      line -> DrawLine( 150., 0., 150., hmax ) ;
      h_avem_nometsig_nobtag_nomindphi -> Draw( "hist same" ) ;
      h_avem_nometsig_nobtag_nomindphi -> Draw( "same" ) ;
      h_avem_allcuts -> Draw( "same" ) ;

      c_avem -> Update() ; c_avem -> Draw() ;
      c_avem -> SaveAs( "outputfiles/h_avem_allcuts.pdf" ) ;

     //-----

      h_avem_nometsig_nobtag_nomindphi -> Scale( 1./(h_avem_nometsig_nobtag_nomindphi->Integral()) ) ;
      h_avem_ttbar_allcuts             -> Scale( 1./(h_avem_ttbar_allcuts->Integral()) ) ;

      hmax = 1.2 * ( h_avem_ttbar_allcuts -> GetMaximum() ) ;
      h_avem_ttbar_allcuts -> SetMaximum( hmax ) ;

      h_avem_ttbar_allcuts -> Draw() ;
      line -> SetLineStyle(1) ;
      line -> DrawLine( 100., 0., 100., hmax ) ;
      line -> DrawLine( 140., 0., 140., hmax ) ;
      line -> SetLineStyle(2) ;
      line -> DrawLine(  90., 0.,  90., hmax ) ;
      line -> DrawLine( 150., 0., 150., hmax ) ;
      h_avem_nometsig_nobtag_nomindphi -> Draw( "hist same" ) ;
      h_avem_nometsig_nobtag_nomindphi -> Draw( "same" ) ;
      h_avem_ttbar_allcuts -> Draw( "hist same" ) ;

      c_avem -> Update() ; c_avem -> Draw() ;
      c_avem -> SaveAs( "outputfiles/h_avem_qcd_ttbar_shapecomp.pdf" ) ;








      //====== Delta mass plots ----------------------------------------------------------------------------------------

      TCanvas* c_deltam = new TCanvas( "c_deltam", "Delta mass", 700, 500 ) ;

      TH1F* h_deltam_nometsig_nobtag_nomindphi = (TH1F*) gDirectory -> FindObject( "h_deltam_nometsig_nobtag_nomindphi" ) ;
      TH1F* h_deltam_nometsig_nobtag           = (TH1F*) gDirectory -> FindObject( "h_deltam_nometsig_nobtag" ) ;
      TH1F* h_deltam_nometsig                  = (TH1F*) gDirectory -> FindObject( "h_deltam_nometsig" ) ;
      TH1F* h_deltam_nobtag                    = (TH1F*) gDirectory -> FindObject( "h_deltam_nobtag" ) ;
      TH1F* h_deltam_allcuts                   = (TH1F*) gDirectory -> FindObject( "h_deltam_allcuts" ) ;
      TH1F* h_deltam_ttbar_allcuts             = (TH1F*) gDirectory -> FindObject( "h_deltam_ttbar_allcuts" ) ;

     //-----

      h_deltam_nometsig_nobtag_nomindphi -> SetLineWidth(2) ;
      h_deltam_nometsig_nobtag_nomindphi -> SetLineColor(2) ;
      h_deltam_nometsig_nobtag_nomindphi -> SetXTitle( "#Delta m_{jj} (GeV)" ) ;

      hmax = 1.2 * ( h_deltam_nometsig_nobtag_nomindphi->GetMaximum() ) ;
      h_deltam_nometsig_nobtag_nomindphi -> SetMaximum( hmax ) ;
      h_deltam_nometsig_nobtag_nomindphi -> Draw( "hist" ) ;
      line -> SetLineStyle(1) ;
      line -> DrawLine( 20., 0., 20., hmax ) ;
      line -> SetLineStyle(2) ;
      line -> DrawLine( 30., 0., 30., hmax ) ;
      h_deltam_nometsig_nobtag_nomindphi -> Draw( "same" ) ;

      c_deltam -> Update() ; c_deltam -> Draw() ;
      c_deltam -> SaveAs( "outputfiles/h_deltam_nometsig_nobtag_nomindphi.pdf" ) ;


     //-----

      h_deltam_ttbar_allcuts -> SetLineWidth(2) ;
      h_deltam_ttbar_allcuts -> SetLineColor(4) ;
      h_deltam_ttbar_allcuts -> SetXTitle( "#Delta m_{jj} (GeV)" ) ;
      hmax = 1.2 * ( h_deltam_ttbar_allcuts->GetMaximum() ) ;
      h_deltam_ttbar_allcuts -> SetMaximum( hmax ) ;

      h_deltam_ttbar_allcuts -> Draw( "hist" ) ;
      line -> SetLineStyle(1) ;
      line -> DrawLine( 20., 0., 20., hmax ) ;
      line -> SetLineStyle(2) ;
      line -> DrawLine( 30., 0., 30., hmax ) ;
      h_deltam_ttbar_allcuts -> Draw( "same" ) ;

      c_deltam -> Update() ; c_deltam -> Draw() ;
      c_deltam -> SaveAs( "outputfiles/h_deltam_ttbar_allcuts.pdf" ) ;



     //-----

      h_deltam_nometsig_nobtag -> SetLineWidth(2) ;
      h_deltam_nometsig_nobtag -> SetLineColor(1) ;
      h_deltam_nometsig_nobtag -> SetMarkerStyle(20) ;
      h_deltam_nometsig_nobtag -> SetXTitle( "#Delta m_{jj} (GeV)" ) ;

      h_deltam_nometsig_nobtag_nomindphi -> Scale( (h_deltam_nometsig_nobtag->Integral())/(h_deltam_nometsig_nobtag_nomindphi->Integral()) ) ;

      hmax = 1.2 * ( h_deltam_nometsig_nobtag->GetMaximum() ) ;
      h_deltam_nometsig_nobtag -> SetMaximum( hmax ) ;
      h_deltam_nometsig_nobtag -> Draw( ) ;
      line -> SetLineStyle(1) ;
      line -> DrawLine( 20., 0., 20., hmax ) ;
      line -> SetLineStyle(2) ;
      line -> DrawLine( 30., 0., 30., hmax ) ;
      h_deltam_nometsig_nobtag_nomindphi -> Draw( "hist same" ) ;
      h_deltam_nometsig_nobtag_nomindphi -> Draw( "same" ) ;
      h_deltam_nometsig_nobtag -> Draw( "same" ) ;

      c_deltam -> Update() ; c_deltam -> Draw() ;
      c_deltam -> SaveAs( "outputfiles/h_deltam_nometsig_nobtag.pdf" ) ;


     //-----

      h_deltam_nometsig -> SetLineWidth(2) ;
      h_deltam_nometsig -> SetLineColor(1) ;
      h_deltam_nometsig -> SetMarkerStyle(20) ;
      h_deltam_nometsig -> SetXTitle( "#Delta m_{jj} (GeV)" ) ;

      h_deltam_nometsig_nobtag_nomindphi -> Scale( (h_deltam_nometsig->Integral())/(h_deltam_nometsig_nobtag_nomindphi->Integral()) ) ;

      hmax = 1.2 * ( h_deltam_nometsig->GetMaximum() ) ;
      h_deltam_nometsig -> SetMaximum( hmax ) ;
      h_deltam_nometsig -> Draw( ) ;
      line -> SetLineStyle(1) ;
      line -> DrawLine( 20., 0., 20., hmax ) ;
      line -> SetLineStyle(2) ;
      line -> DrawLine( 30., 0., 30., hmax ) ;
      h_deltam_nometsig_nobtag_nomindphi -> Draw( "hist same" ) ;
      h_deltam_nometsig_nobtag_nomindphi -> Draw( "same" ) ;
      h_deltam_nometsig -> Draw( "same" ) ;

      c_deltam -> Update() ; c_deltam -> Draw() ;
      c_deltam -> SaveAs( "outputfiles/h_deltam_nometsig.pdf" ) ;


     //-----

      h_deltam_nobtag -> SetLineWidth(2) ;
      h_deltam_nobtag -> SetLineColor(1) ;
      h_deltam_nobtag -> SetMarkerStyle(20) ;
      h_deltam_nobtag -> SetXTitle( "#Delta m_{jj} (GeV)" ) ;

      h_deltam_nometsig_nobtag_nomindphi -> Scale( (h_deltam_nobtag->Integral())/(h_deltam_nometsig_nobtag_nomindphi->Integral()) ) ;

      hmax = 1.2 * ( h_deltam_nobtag->GetMaximum() ) ;
      h_deltam_nobtag -> SetMaximum( hmax ) ;
      h_deltam_nobtag -> Draw( ) ;
      line -> SetLineStyle(1) ;
      line -> DrawLine( 20., 0., 20., hmax ) ;
      line -> SetLineStyle(2) ;
      line -> DrawLine( 30., 0., 30., hmax ) ;
      h_deltam_nometsig_nobtag_nomindphi -> Draw( "hist same" ) ;
      h_deltam_nometsig_nobtag_nomindphi -> Draw( "same" ) ;
      h_deltam_nobtag -> Draw( "same" ) ;

      c_deltam -> Update() ; c_deltam -> Draw() ;
      c_deltam -> SaveAs( "outputfiles/h_deltam_nobtag.pdf" ) ;


     //-----

      h_deltam_allcuts -> SetLineWidth(2) ;
      h_deltam_allcuts -> SetLineColor(1) ;
      h_deltam_allcuts -> SetMarkerStyle(20) ;
      h_deltam_allcuts -> SetXTitle( "#Delta m_{jj} (GeV)" ) ;

      h_deltam_nometsig_nobtag_nomindphi -> Scale( (h_deltam_allcuts->Integral())/(h_deltam_nometsig_nobtag_nomindphi->Integral()) ) ;

      hmax = 1.2 * ( h_deltam_allcuts->GetMaximum() ) ;
      h_deltam_allcuts -> SetMaximum( hmax ) ;
      h_deltam_allcuts -> Draw( ) ;
      line -> SetLineStyle(1) ;
      line -> DrawLine( 20., 0., 20., hmax ) ;
      line -> SetLineStyle(2) ;
      line -> DrawLine( 30., 0., 30., hmax ) ;
      h_deltam_nometsig_nobtag_nomindphi -> Draw( "hist same" ) ;
      h_deltam_nometsig_nobtag_nomindphi -> Draw( "same" ) ;
      h_deltam_allcuts -> Draw( "same" ) ;

      c_deltam -> Update() ; c_deltam -> Draw() ;
      c_deltam -> SaveAs( "outputfiles/h_deltam_allcuts.pdf" ) ;

     //-----

      h_deltam_nometsig_nobtag_nomindphi -> Scale( 1./(h_deltam_nometsig_nobtag_nomindphi->Integral()) ) ;
      h_deltam_ttbar_allcuts             -> Scale( 1./(h_deltam_ttbar_allcuts->Integral()) ) ;

      hmax = 1.2 * ( h_deltam_ttbar_allcuts -> GetMaximum() ) ;
      h_deltam_ttbar_allcuts -> SetMaximum( hmax ) ;

      h_deltam_ttbar_allcuts -> Draw() ;
      line -> SetLineStyle(1) ;
      line -> DrawLine( 20., 0., 20., hmax ) ;
      line -> SetLineStyle(2) ;
      line -> DrawLine( 30., 0., 30., hmax ) ;
      h_deltam_nometsig_nobtag_nomindphi -> Draw( "hist same" ) ;
      h_deltam_nometsig_nobtag_nomindphi -> Draw( "same" ) ;
      h_deltam_ttbar_allcuts -> Draw( "hist same" ) ;

      c_deltam -> Update() ; c_deltam -> Draw() ;
      c_deltam -> SaveAs( "outputfiles/h_deltam_qcd_ttbar_shapecomp.pdf" ) ;



      //====== Delta mass vs Ave mass plots ----------------------------------------------------------------------------------------

      TCanvas* c_dmvsam = new TCanvas( "c_dmvsam", "Delta mass vs ave mass", 700, 500 ) ;

      TH2F* h_deltam_vs_avem_nometsig_nobtag_nomindphi = (TH2F*) gDirectory -> FindObject( "h_deltam_vs_avem_nometsig_nobtag_nomindphi" ) ;
      TH2F* h_deltam_vs_avem_ttbar_allcuts             = (TH2F*) gDirectory -> FindObject( "h_deltam_vs_avem_ttbar_allcuts" ) ;

      h_deltam_vs_avem_nometsig_nobtag_nomindphi -> SetFillColor(2) ;
      h_deltam_vs_avem_nometsig_nobtag_nomindphi -> SetLineColor(1) ;

      h_deltam_vs_avem_ttbar_allcuts -> SetFillColor(4) ;
      h_deltam_vs_avem_ttbar_allcuts -> SetLineColor(1) ;

      h_deltam_vs_avem_nometsig_nobtag_nomindphi -> SetXTitle( "<m_{jj}> (GeV)" ) ;
      h_deltam_vs_avem_nometsig_nobtag_nomindphi -> SetYTitle( "#Delta m_{jj} (GeV)" ) ;

      h_deltam_vs_avem_ttbar_allcuts -> SetXTitle( "<m_{jj}> (GeV)" ) ;
      h_deltam_vs_avem_ttbar_allcuts -> SetYTitle( "#Delta m_{jj} (GeV)" ) ;

      h_deltam_vs_avem_nometsig_nobtag_nomindphi -> Draw("box") ;
      box->DrawBox( 100., 0., 140., 20. ) ;
      box->DrawBox(  90., 0., 150., 30. ) ;
      c_dmvsam -> Update() ; c_dmvsam -> Draw() ;
      c_dmvsam -> SaveAs( "outputfiles/h_deltam_vs_avem_nometsig_nobtag_nomindphi.pdf" ) ;

      h_deltam_vs_avem_ttbar_allcuts -> Draw("box") ;
      box->DrawBox( 100., 0., 140., 20. ) ;
      box->DrawBox(  90., 0., 150., 30. ) ;
      c_dmvsam -> Update() ; c_dmvsam -> Draw() ;
      c_dmvsam -> SaveAs( "outputfiles/h_deltam_vs_avem_ttbar_allcuts.pdf" ) ;




      //====== METsig plots ----------------------------------------------------------------------------------------

      TCanvas* c_metsig = new TCanvas( "c_metsig", "METsig", 700, 500 ) ;

      TH1F* h_metsig_sigsb_nobtag_nomindphi_ub = (TH1F*) gDirectory -> FindObject( "h_metsig_sigsb_nobtag_nomindphi_ub" ) ;
      TH1F* h_metsig_sigsb_nobtag_fb = (TH1F*) gDirectory -> FindObject( "h_metsig_sigsb_nobtag_fb" ) ;
      TH1F* h_metsig_sigsb_2b_fb = (TH1F*) gDirectory -> FindObject( "h_metsig_sigsb_2b_fb" ) ;
      TH1F* h_metsig_sigsb_3b_fb = (TH1F*) gDirectory -> FindObject( "h_metsig_sigsb_3b_fb" ) ;
      TH1F* h_metsig_sigsb_4b_fb = (TH1F*) gDirectory -> FindObject( "h_metsig_sigsb_4b_fb" ) ;
      TH1F* h_metsig_ttbar_allcuts_ub = (TH1F*) gDirectory -> FindObject( "h_metsig_ttbar_allcuts_ub" ) ;
      TH1F* h_metsig_ttbar_sigsb_allcuts_fb = (TH1F*) gDirectory -> FindObject( "h_metsig_ttbar_sigsb_allcuts_fb" ) ;

      h_metsig_sigsb_nobtag_nomindphi_ub -> SetLineWidth(2) ;
      h_metsig_sigsb_nobtag_nomindphi_ub -> SetLineColor(2) ;
      h_metsig_sigsb_nobtag_nomindphi_ub -> SetXTitle( "METsig" ) ;
      h_metsig_sigsb_nobtag_fb -> SetLineWidth(2) ;
      h_metsig_sigsb_nobtag_fb -> SetLineColor(2) ;
      h_metsig_sigsb_nobtag_fb -> SetXTitle( "METsig" ) ;
      h_metsig_sigsb_2b_fb -> SetLineWidth(2) ;
      h_metsig_sigsb_2b_fb -> SetMarkerStyle(20) ;
      h_metsig_sigsb_2b_fb -> SetXTitle( "METsig" ) ;
      h_metsig_sigsb_3b_fb -> SetLineWidth(2) ;
      h_metsig_sigsb_3b_fb -> SetMarkerStyle(20) ;
      h_metsig_sigsb_3b_fb -> SetXTitle( "METsig" ) ;
      h_metsig_sigsb_4b_fb -> SetLineWidth(2) ;
      h_metsig_sigsb_4b_fb -> SetMarkerStyle(20) ;
      h_metsig_sigsb_4b_fb -> SetXTitle( "METsig" ) ;

      h_metsig_ttbar_allcuts_ub -> SetLineWidth(2) ;
      h_metsig_ttbar_allcuts_ub -> SetLineColor(4) ;
      h_metsig_ttbar_allcuts_ub -> SetXTitle( "METsig" ) ;
      h_metsig_ttbar_sigsb_allcuts_fb -> SetLineWidth(2) ;
      h_metsig_ttbar_sigsb_allcuts_fb -> SetLineColor(4) ;
      h_metsig_ttbar_sigsb_allcuts_fb -> SetXTitle( "METsig" ) ;


      //-----

      hmax = 1.2 * ( h_metsig_sigsb_nobtag_nomindphi_ub -> GetMaximum() ) ;
      h_metsig_sigsb_nobtag_nomindphi_ub -> SetMaximum( hmax ) ;

      h_metsig_sigsb_nobtag_nomindphi_ub -> Draw( "hist" ) ;
      h_metsig_sigsb_nobtag_nomindphi_ub -> Draw( "same" ) ;
      line -> DrawLine(  30., 0.,  30., hmax ) ;
      line -> DrawLine(  50., 0.,  50., hmax ) ;
      line -> DrawLine( 100., 0., 100., hmax ) ;
      line -> DrawLine( 150., 0., 150., hmax ) ;

      c_metsig -> Update() ; c_metsig -> Draw() ;
      c_metsig -> SaveAs( "outputfiles/h_metsig_sigsb_nobtag_nomindphi_ub-liny.pdf" ) ;


      //-----

      hmax = 1.2 * ( h_metsig_ttbar_allcuts_ub -> GetMaximum() ) ;
      h_metsig_ttbar_allcuts_ub -> SetMaximum( hmax ) ;

      h_metsig_ttbar_allcuts_ub -> Draw( "hist" ) ;
      h_metsig_ttbar_allcuts_ub -> Draw( "same" ) ;
      line -> DrawLine(  30., 0.,  30., hmax ) ;
      line -> DrawLine(  50., 0.,  50., hmax ) ;
      line -> DrawLine( 100., 0., 100., hmax ) ;
      line -> DrawLine( 150., 0., 150., hmax ) ;

      c_metsig -> Update() ; c_metsig -> Draw() ;
      c_metsig -> SaveAs( "outputfiles/h_metsig_ttbar_allcuts_ub-liny.pdf" ) ;


      //-----

      hmax = 1.2 * ( h_metsig_sigsb_nobtag_fb -> GetMaximum() ) ;
      h_metsig_sigsb_nobtag_fb -> SetMaximum( hmax ) ;

      h_metsig_sigsb_nobtag_fb -> Draw( "hist" ) ;
      h_metsig_sigsb_nobtag_fb -> Draw( "same" ) ;

      c_metsig -> Update() ; c_metsig -> Draw() ;
      c_metsig -> SaveAs( "outputfiles/h_metsig_sigsb_nobtag_fb-liny.pdf" ) ;


      //-----

      hmax = 1.2 * ( h_metsig_ttbar_sigsb_allcuts_fb -> GetMaximum() ) ;
      h_metsig_ttbar_sigsb_allcuts_fb -> SetMaximum( hmax ) ;

      h_metsig_ttbar_sigsb_allcuts_fb -> Draw( "hist" ) ;
      h_metsig_ttbar_sigsb_allcuts_fb -> Draw( "same" ) ;

      c_metsig -> Update() ; c_metsig -> Draw() ;
      c_metsig -> SaveAs( "outputfiles/h_metsig_ttbar_sigsb_allcuts_fb-liny.pdf" ) ;


      gPad -> SetLogy(1) ;

      //-----

      hmax = 2.0 * ( h_metsig_sigsb_nobtag_nomindphi_ub -> GetMaximum() ) ;
      h_metsig_sigsb_nobtag_nomindphi_ub -> SetMaximum( hmax ) ;
      h_metsig_sigsb_nobtag_nomindphi_ub -> SetMinimum( hmin ) ;

      h_metsig_sigsb_nobtag_nomindphi_ub -> Draw( "hist" ) ;
      h_metsig_sigsb_nobtag_nomindphi_ub -> Draw( "same" ) ;
      line -> DrawLine(  30., 0.,  30., hmax ) ;
      line -> DrawLine(  50., 0.,  50., hmax ) ;
      line -> DrawLine( 100., 0., 100., hmax ) ;
      line -> DrawLine( 150., 0., 150., hmax ) ;

      c_metsig -> Update() ; c_metsig -> Draw() ;
      c_metsig -> SaveAs( "outputfiles/h_metsig_sigsb_nobtag_nomindphi_ub-logy.pdf" ) ;


      //-----

      hmax = 2.0 * ( h_metsig_ttbar_allcuts_ub -> GetMaximum() ) ;
      h_metsig_ttbar_allcuts_ub -> SetMaximum( hmax ) ;
      h_metsig_ttbar_allcuts_ub -> SetMinimum( hmin ) ;

      h_metsig_ttbar_allcuts_ub -> Draw( "hist" ) ;
      h_metsig_ttbar_allcuts_ub -> Draw( "same" ) ;
      line -> DrawLine(  30., 0.,  30., hmax ) ;
      line -> DrawLine(  50., 0.,  50., hmax ) ;
      line -> DrawLine( 100., 0., 100., hmax ) ;
      line -> DrawLine( 150., 0., 150., hmax ) ;

      c_metsig -> Update() ; c_metsig -> Draw() ;
      c_metsig -> SaveAs( "outputfiles/h_metsig_ttbar_allcuts_ub-logy.pdf" ) ;


      //-----

      hmax = 2.0 * ( h_metsig_sigsb_nobtag_fb -> GetMaximum() ) ;
      h_metsig_sigsb_nobtag_fb -> SetMaximum( hmax ) ;
      h_metsig_sigsb_nobtag_fb -> SetMinimum( hmin ) ;

      h_metsig_sigsb_nobtag_fb -> Draw( "hist" ) ;
      h_metsig_sigsb_nobtag_fb -> Draw( "same" ) ;

      c_metsig -> Update() ; c_metsig -> Draw() ;
      c_metsig -> SaveAs( "outputfiles/h_metsig_sigsb_nobtag_fb-logy.pdf" ) ;


      //-----

      hmax = 2.0 * ( h_metsig_ttbar_sigsb_allcuts_fb -> GetMaximum() ) ;
      h_metsig_ttbar_sigsb_allcuts_fb -> SetMaximum( hmax ) ;
      h_metsig_ttbar_sigsb_allcuts_fb -> SetMinimum( hmin ) ;

      h_metsig_ttbar_sigsb_allcuts_fb -> Draw( "hist" ) ;
      h_metsig_ttbar_sigsb_allcuts_fb -> Draw( "same" ) ;

      c_metsig -> Update() ; c_metsig -> Draw() ;
      c_metsig -> SaveAs( "outputfiles/h_metsig_ttbar_sigsb_allcuts_fb-logy.pdf" ) ;


      gPad -> SetLogy(0) ;






      //--- METsig in analysis bins, loose vs tight comparisons.

      //------

      h_metsig_sigsb_nobtag_fb -> Scale( (h_metsig_sigsb_2b_fb->Integral())/(h_metsig_sigsb_nobtag_fb->Integral()) ) ;

      hmax = 1.2 * ( h_metsig_sigsb_2b_fb->GetMaximum() ) ;
      h_metsig_sigsb_2b_fb -> SetMaximum( hmax ) ;
      h_metsig_sigsb_2b_fb -> Draw( ) ;
      h_metsig_sigsb_nobtag_fb -> Draw( "hist same" ) ;
      h_metsig_sigsb_nobtag_fb -> Draw( "same" ) ;
      h_metsig_sigsb_2b_fb -> Draw( "same" ) ;

      c_metsig -> Update() ; c_metsig -> Draw() ;
      c_metsig -> SaveAs( "outputfiles/h_metsig_sigsb_2b_fb.pdf" ) ;


      //------

      h_metsig_sigsb_nobtag_fb -> Scale( (h_metsig_sigsb_3b_fb->Integral())/(h_metsig_sigsb_nobtag_fb->Integral()) ) ;

      hmax = 1.2 * ( h_metsig_sigsb_3b_fb->GetMaximum() ) ;
      h_metsig_sigsb_3b_fb -> SetMaximum( hmax ) ;
      h_metsig_sigsb_3b_fb -> Draw( ) ;
      h_metsig_sigsb_nobtag_fb -> Draw( "hist same" ) ;
      h_metsig_sigsb_nobtag_fb -> Draw( "same" ) ;
      h_metsig_sigsb_3b_fb -> Draw( "same" ) ;

      c_metsig -> Update() ; c_metsig -> Draw() ;
      c_metsig -> SaveAs( "outputfiles/h_metsig_sigsb_3b_fb.pdf" ) ;


      //------

      h_metsig_sigsb_nobtag_fb -> Scale( (h_metsig_sigsb_4b_fb->Integral())/(h_metsig_sigsb_nobtag_fb->Integral()) ) ;

      hmax = 1.2 * ( h_metsig_sigsb_4b_fb->GetMaximum() ) ;
      h_metsig_sigsb_4b_fb -> SetMaximum( hmax ) ;
      h_metsig_sigsb_4b_fb -> Draw( ) ;
      h_metsig_sigsb_nobtag_fb -> Draw( "hist same" ) ;
      h_metsig_sigsb_nobtag_fb -> Draw( "same" ) ;
      h_metsig_sigsb_4b_fb -> Draw( "same" ) ;

      c_metsig -> Update() ; c_metsig -> Draw() ;
      c_metsig -> SaveAs( "outputfiles/h_metsig_sigsb_4b_fb.pdf" ) ;



      //====== Nbtag plots ----------------------------------------------------------------------------------------

      TCanvas* c_nbtag = new TCanvas( "c_nbtag", "Nbtag", 700, 500 ) ;

      gPad -> SetGridy(1) ;

      TH1F* h_nb_sigsb_nometsig_nomindphi = (TH1F*) gDirectory -> FindObject( "h_nb_sigsb_nometsig_nomindphi" ) ;
      TH1F* h_nb_sigsb_nometsig = (TH1F*) gDirectory -> FindObject( "h_nb_sigsb_nometsig" ) ;
      TH1F* h_nb_sigsb_metsig30 = (TH1F*) gDirectory -> FindObject( "h_nb_sigsb_metsig30" ) ;
      TH1F* h_nb_ttbar_sigsb_allcuts = (TH1F*) gDirectory -> FindObject( "h_nb_ttbar_sigsb_allcuts" ) ;

      h_nb_sigsb_nometsig_nomindphi -> SetLineWidth(2) ;
      h_nb_sigsb_nometsig_nomindphi -> SetLineColor(2) ;
      h_nb_sigsb_nometsig_nomindphi -> SetXTitle("Nbtag category") ;
      h_nb_sigsb_nometsig -> SetLineWidth(2) ;
      h_nb_sigsb_nometsig -> SetMarkerStyle(20) ;
      h_nb_sigsb_nometsig -> SetXTitle("Nbtag category") ;
      h_nb_sigsb_metsig30 -> SetLineWidth(2) ;
      h_nb_sigsb_metsig30 -> SetMarkerStyle(20) ;
      h_nb_sigsb_metsig30 -> SetXTitle("Nbtag category") ;

      h_nb_ttbar_sigsb_allcuts -> SetLineWidth(2) ;
      h_nb_ttbar_sigsb_allcuts -> SetLineColor(4) ;
      h_nb_ttbar_sigsb_allcuts -> SetXTitle("Nbtag category") ;

      //-----

      gPad -> SetLogy(0) ;

      hmax = 1.2 * ( h_nb_sigsb_nometsig_nomindphi -> GetBinContent(3) ) ;
      h_nb_sigsb_nometsig_nomindphi -> SetMaximum( hmax ) ;

      h_nb_sigsb_nometsig_nomindphi -> Draw( "hist" ) ;
      h_nb_sigsb_nometsig_nomindphi -> Draw( "same" ) ;

      c_nbtag -> Update() ; c_nbtag -> Draw() ;
      c_nbtag -> SaveAs( "outputfiles/h_nb_sigsb_nonbtag_nomindphi-liny.pdf" ) ;


      //-----

      gPad -> SetLogy(1) ;

      h_nb_sigsb_nometsig_nomindphi -> SetMaximum( 2.0*(h_nb_sigsb_nometsig_nomindphi->GetBinContent(3)) ) ;
      h_nb_sigsb_nometsig_nomindphi -> SetMinimum( 0.3*(h_nb_sigsb_nometsig_nomindphi->GetBinContent(5)) ) ;

      h_nb_sigsb_nometsig_nomindphi -> Draw( "hist" ) ;
      h_nb_sigsb_nometsig_nomindphi -> Draw( "same" ) ;

      c_nbtag -> Update() ; c_nbtag -> Draw() ;
      c_nbtag -> SaveAs( "outputfiles/h_nb_sigsb_nonbtag_nomindphi-logy.pdf" ) ;



      //-----

      gPad -> SetLogy(0) ;

      hmax = 1.2 * ( h_nb_ttbar_sigsb_allcuts -> GetBinContent(3) ) ;
      h_nb_ttbar_sigsb_allcuts -> SetMaximum( hmax ) ;

      h_nb_ttbar_sigsb_allcuts -> Draw( "hist" ) ;
      h_nb_ttbar_sigsb_allcuts -> Draw( "same" ) ;

      c_nbtag -> Update() ; c_nbtag -> Draw() ;
      c_nbtag -> SaveAs( "outputfiles/h_nb_ttbar_sigsb_allcuts-liny.pdf" ) ;


      //-----

      gPad -> SetLogy(1) ;

      h_nb_ttbar_sigsb_allcuts -> SetMaximum( 2.0*(h_nb_ttbar_sigsb_allcuts->GetBinContent(3)) ) ;
      h_nb_ttbar_sigsb_allcuts -> SetMinimum( 0.3*(h_nb_ttbar_sigsb_allcuts->GetBinContent(5)) ) ;

      h_nb_ttbar_sigsb_allcuts -> Draw( "hist" ) ;
      h_nb_ttbar_sigsb_allcuts -> Draw( "same" ) ;

      c_nbtag -> Update() ; c_nbtag -> Draw() ;
      c_nbtag -> SaveAs( "outputfiles/h_nb_ttbar_sigsb_allcuts-logy.pdf" ) ;


      //------ QCD vs ttbar Nbtag shape comparisons.

      //-----

      gPad -> SetLogy(0) ;

      h_nb_ttbar_sigsb_allcuts -> Scale( 1./(h_nb_ttbar_sigsb_allcuts->Integral(3,5)) ) ;
      h_nb_sigsb_nometsig_nomindphi -> Scale( 1./(h_nb_sigsb_nometsig_nomindphi->Integral(3,5)) ) ;

      printf("\n\n ttbar Nbtag PDF:\n" ) ;
      h_nb_ttbar_sigsb_allcuts->Print("all") ;

      printf("\n\n QCD Nbtag PDF:\n" ) ;
      h_nb_sigsb_nometsig_nomindphi->Print("all") ;

      h_nb_ttbar_sigsb_allcuts      -> SetMaximum( 1.1 ) ;
      h_nb_sigsb_nometsig_nomindphi -> SetMaximum( 1.1 ) ;
      h_nb_ttbar_sigsb_allcuts      -> SetMinimum( 0.  ) ;
      h_nb_sigsb_nometsig_nomindphi -> SetMinimum( 0.  ) ;

      h_nb_ttbar_sigsb_allcuts -> Draw( "hist" ) ;
      h_nb_ttbar_sigsb_allcuts -> Draw( "same" ) ;
      h_nb_sigsb_nometsig_nomindphi -> Draw( "hist same" ) ;
      h_nb_sigsb_nometsig_nomindphi -> Draw( "same" ) ;

      c_nbtag -> Update() ; c_nbtag -> Draw() ;
      c_nbtag -> SaveAs( "outputfiles/h_nb_qcd-ttbar-shape-comp-liny.pdf" ) ;

      //-----

      h_nb_ttbar_sigsb_allcuts      -> SetMaximum( 1.5*( h_nb_ttbar_sigsb_allcuts->GetBinContent(4)) ) ;
      h_nb_ttbar_sigsb_allcuts -> Draw( "hist" ) ;
      h_nb_ttbar_sigsb_allcuts -> Draw( "same" ) ;
      h_nb_sigsb_nometsig_nomindphi -> Draw( "hist same" ) ;
      h_nb_sigsb_nometsig_nomindphi -> Draw( "same" ) ;

      c_nbtag -> Update() ; c_nbtag -> Draw() ;
      c_nbtag -> SaveAs( "outputfiles/h_nb_qcd-ttbar-shape-comp-liny-zoom.pdf" ) ;

      //-----

      gPad -> SetLogy(1) ;

      h_nb_ttbar_sigsb_allcuts      -> SetMaximum( 1.5 ) ;
      h_nb_sigsb_nometsig_nomindphi -> SetMaximum( 1.5 ) ;
      h_nb_ttbar_sigsb_allcuts      -> SetMinimum( 0.01  ) ;
      h_nb_sigsb_nometsig_nomindphi -> SetMinimum( 0.01  ) ;

      h_nb_ttbar_sigsb_allcuts -> Draw( "hist" ) ;
      h_nb_ttbar_sigsb_allcuts -> Draw( "same" ) ;
      h_nb_sigsb_nometsig_nomindphi -> Draw( "hist same" ) ;
      h_nb_sigsb_nometsig_nomindphi -> Draw( "same" ) ;

      c_nbtag -> Update() ; c_nbtag -> Draw() ;
      c_nbtag -> SaveAs( "outputfiles/h_nb_qcd-ttbar-shape-comp-logy.pdf" ) ;



      //---- QCD loose vs tight comparisons


      //------

      gPad -> SetLogy(0) ;

      h_nb_sigsb_nometsig_nomindphi -> Scale( (h_nb_sigsb_nometsig->Integral(3,5))/(h_nb_sigsb_nometsig_nomindphi->Integral(3,5)) ) ;

      hmax = 1.2 * ( h_nb_sigsb_nometsig->GetBinContent(3) ) ;
      h_nb_sigsb_nometsig -> SetMaximum( hmax ) ;
      h_nb_sigsb_nometsig -> SetMinimum( 0. ) ;
      h_nb_sigsb_nometsig -> Draw( ) ;
      h_nb_sigsb_nometsig_nomindphi -> Draw( "hist same" ) ;
      h_nb_sigsb_nometsig_nomindphi -> Draw( "same" ) ;
      h_nb_sigsb_nometsig -> Draw( "same" ) ;

      c_nbtag -> Update() ; c_nbtag -> Draw() ;
      c_nbtag -> SaveAs( "outputfiles/h_nb_sigsb_nometsig-liny.pdf" ) ;

      //------

      hmax = 1.5 * ( h_nb_sigsb_nometsig->GetBinContent(4) ) ;
      h_nb_sigsb_nometsig -> SetMaximum( hmax ) ;
      h_nb_sigsb_nometsig -> SetMinimum( 0. ) ;
      h_nb_sigsb_nometsig -> Draw( ) ;
      h_nb_sigsb_nometsig_nomindphi -> Draw( "hist same" ) ;
      h_nb_sigsb_nometsig_nomindphi -> Draw( "same" ) ;
      h_nb_sigsb_nometsig -> Draw( "same" ) ;

      c_nbtag -> Update() ; c_nbtag -> Draw() ;
      c_nbtag -> SaveAs( "outputfiles/h_nb_sigsb_nometsig-liny-zoom.pdf" ) ;


      //------

      gPad -> SetLogy(0) ;

      h_nb_sigsb_nometsig_nomindphi -> Scale( (h_nb_sigsb_metsig30->Integral(3,5))/(h_nb_sigsb_nometsig_nomindphi->Integral(3,5)) ) ;

      hmax = 1.2 * ( h_nb_sigsb_nometsig_nomindphi->GetBinContent(3) ) ;
      h_nb_sigsb_metsig30 -> SetMaximum( hmax ) ;
      h_nb_sigsb_metsig30 -> SetMinimum( 0. ) ;
      h_nb_sigsb_metsig30 -> Draw( ) ;
      h_nb_sigsb_nometsig_nomindphi -> Draw( "hist same" ) ;
      h_nb_sigsb_nometsig_nomindphi -> Draw( "same" ) ;
      h_nb_sigsb_metsig30 -> Draw( "same" ) ;

      c_nbtag -> Update() ; c_nbtag -> Draw() ;
      c_nbtag -> SaveAs( "outputfiles/h_nb_sigsb_metsig30-liny.pdf" ) ;

      //------

      hmax = 1.5 * ( h_nb_sigsb_nometsig_nomindphi->GetBinContent(4) ) ;
      h_nb_sigsb_metsig30 -> SetMaximum( hmax ) ;
      h_nb_sigsb_metsig30 -> SetMinimum( 0. ) ;
      h_nb_sigsb_metsig30 -> Draw( ) ;
      h_nb_sigsb_nometsig_nomindphi -> Draw( "hist same" ) ;
      h_nb_sigsb_nometsig_nomindphi -> Draw( "same" ) ;
      h_nb_sigsb_metsig30 -> Draw( "same" ) ;

      c_nbtag -> Update() ; c_nbtag -> Draw() ;
      c_nbtag -> SaveAs( "outputfiles/h_nb_sigsb_metsig30-liny-zoom.pdf" ) ;


      //====== SIG/SB ratios ----------------------------------------------------------------------------------------

      TCanvas* c_sigsbratio = new TCanvas( "c_sigsbratio", "SIG/SB", 700, 500 ) ;

      gPad -> SetGridy(1) ;

      TH1F* h_metsig_sigsb_ratio_nobtag_nomindphi_fb = (TH1F*) gDirectory -> FindObject( "h_metsig_sigsb_ratio_nobtag_nomindphi_fb" ) ;
      TH1F* h_metsig_sigsb_ratio_nobtag_fb = (TH1F*) gDirectory -> FindObject( "h_metsig_sigsb_ratio_nobtag_fb" ) ;
      TH1F* h_nb_sigsb_ratio_nometsig_nomindphi = (TH1F*) gDirectory -> FindObject( "h_nb_sigsb_ratio_nometsig_nomindphi" ) ;
      TH1F* h_nb_sigsb_ratio_nometsig = (TH1F*) gDirectory -> FindObject( "h_nb_sigsb_ratio_nometsig" ) ;
      TH1F* h_nb_sigsb_ratio_metsig30 = (TH1F*) gDirectory -> FindObject( "h_nb_sigsb_ratio_metsig30" ) ;
      TH1F* h_metsig_ttbar_sigsb_ratio_allcuts_fb = (TH1F*) gDirectory -> FindObject( "h_metsig_ttbar_sigsb_ratio_allcuts_fb" ) ;
      TH1F* h_nb_ttbar_sigsb_ratio_allcuts = (TH1F*) gDirectory -> FindObject( "h_nb_ttbar_sigsb_ratio_allcuts" ) ;

      gStyle -> SetOptStat(0) ;
      gStyle -> SetOptFit(1) ;

      h_metsig_sigsb_ratio_nobtag_nomindphi_fb -> SetLineWidth(2) ;
      h_metsig_sigsb_ratio_nobtag_fb -> SetLineWidth(2) ;
      h_nb_sigsb_ratio_nometsig_nomindphi -> SetLineWidth(2) ;
      h_nb_sigsb_ratio_nometsig -> SetLineWidth(2) ;
      h_nb_sigsb_ratio_metsig30 -> SetLineWidth(2) ;

      h_metsig_sigsb_ratio_nobtag_nomindphi_fb -> SetLineColor(2) ;
      h_metsig_sigsb_ratio_nobtag_fb -> SetLineColor(2) ;
      h_nb_sigsb_ratio_nometsig_nomindphi -> SetLineColor(2) ;
      h_nb_sigsb_ratio_nometsig -> SetLineColor(2) ;
      h_nb_sigsb_ratio_metsig30 -> SetLineColor(2) ;

      h_metsig_sigsb_ratio_nobtag_nomindphi_fb -> SetMarkerStyle(20) ;
      h_metsig_sigsb_ratio_nobtag_fb -> SetMarkerStyle(20) ;
      h_nb_sigsb_ratio_nometsig_nomindphi -> SetMarkerStyle(20) ;
      h_nb_sigsb_ratio_nometsig -> SetMarkerStyle(20) ;
      h_nb_sigsb_ratio_metsig30 -> SetMarkerStyle(20) ;

      h_metsig_sigsb_ratio_nobtag_nomindphi_fb -> SetMarkerSize(1.5) ;
      h_metsig_sigsb_ratio_nobtag_fb -> SetMarkerSize(1.5) ;
      h_nb_sigsb_ratio_nometsig_nomindphi -> SetMarkerSize(1.5) ;
      h_nb_sigsb_ratio_nometsig -> SetMarkerSize(1.5) ;
      h_nb_sigsb_ratio_metsig30 -> SetMarkerSize(1.5) ;

      h_metsig_sigsb_ratio_nobtag_nomindphi_fb -> SetMarkerColor(2) ;
      h_metsig_sigsb_ratio_nobtag_fb -> SetMarkerColor(2) ;
      h_nb_sigsb_ratio_nometsig_nomindphi -> SetMarkerColor(2) ;
      h_nb_sigsb_ratio_nometsig -> SetMarkerColor(2) ;
      h_nb_sigsb_ratio_metsig30 -> SetMarkerColor(2) ;

      h_metsig_sigsb_ratio_nobtag_nomindphi_fb -> SetMaximum(0.25) ;
      h_metsig_sigsb_ratio_nobtag_fb -> SetMaximum(0.25) ;
      h_nb_sigsb_ratio_nometsig_nomindphi -> SetMaximum(0.25) ;
      h_nb_sigsb_ratio_nometsig -> SetMaximum(0.25) ;
      h_nb_sigsb_ratio_metsig30 -> SetMaximum(0.25) ;

      h_metsig_sigsb_ratio_nobtag_nomindphi_fb -> SetMinimum(0.0) ;
      h_metsig_sigsb_ratio_nobtag_fb -> SetMinimum(0.0) ;
      h_nb_sigsb_ratio_nometsig_nomindphi -> SetMinimum(0.0) ;
      h_nb_sigsb_ratio_nometsig -> SetMinimum(0.0) ;
      h_nb_sigsb_ratio_metsig30 -> SetMinimum(0.0) ;

      h_nb_sigsb_ratio_nometsig_nomindphi -> SetXTitle("Nbtag category") ;
      h_nb_sigsb_ratio_nometsig -> SetXTitle("Nbtag category") ;
      h_nb_sigsb_ratio_metsig30 -> SetXTitle("Nbtag category") ;



      h_nb_ttbar_sigsb_ratio_allcuts -> SetXTitle("Nbtag category") ;

      h_metsig_ttbar_sigsb_ratio_allcuts_fb -> SetLineWidth(2) ;
      h_nb_ttbar_sigsb_ratio_allcuts -> SetLineWidth(2) ;

      h_metsig_ttbar_sigsb_ratio_allcuts_fb -> SetLineColor(4) ;
      h_nb_ttbar_sigsb_ratio_allcuts -> SetLineColor(4) ;

      h_metsig_ttbar_sigsb_ratio_allcuts_fb -> SetMarkerStyle(24) ;
      h_nb_ttbar_sigsb_ratio_allcuts -> SetMarkerStyle(24) ;

      h_metsig_ttbar_sigsb_ratio_allcuts_fb -> SetMarkerSize(1.5) ;
      h_nb_ttbar_sigsb_ratio_allcuts -> SetMarkerSize(1.5) ;

      h_metsig_ttbar_sigsb_ratio_allcuts_fb -> SetMarkerColor(4) ;
      h_nb_ttbar_sigsb_ratio_allcuts -> SetMarkerColor(4) ;

      h_metsig_ttbar_sigsb_ratio_allcuts_fb -> SetMaximum(0.25) ;
      h_nb_ttbar_sigsb_ratio_allcuts -> SetMaximum(0.25) ;

      h_metsig_ttbar_sigsb_ratio_allcuts_fb -> SetMinimum(0.0) ;
      h_nb_ttbar_sigsb_ratio_allcuts -> SetMinimum(0.0) ;




      h_metsig_ttbar_sigsb_ratio_allcuts_fb -> Fit( "pol0" ) ;
      func = h_metsig_ttbar_sigsb_ratio_allcuts_fb -> GetFunction( "pol0" ) ;
      func -> SetLineColor(4) ;
      c_sigsbratio -> Update() ; c_sigsbratio -> Draw() ;
      c_sigsbratio -> SaveAs( "outputfiles/h_metsig_ttbar_sigsb_ratio_allcuts_fb.pdf" ) ;

      h_nb_ttbar_sigsb_ratio_allcuts -> Fit( "pol0" ) ;
      func = h_nb_ttbar_sigsb_ratio_allcuts -> GetFunction( "pol0" ) ;
      func -> SetLineColor(4) ;
      c_sigsbratio -> Update() ; c_sigsbratio -> Draw() ;
      c_sigsbratio -> SaveAs( "outputfiles/h_nb_ttbar_sigsb_ratio_allcuts.pdf" ) ;




      h_metsig_sigsb_ratio_nobtag_nomindphi_fb -> Fit( "pol0", "", "", 0., 3.5  ) ;
      func = h_metsig_sigsb_ratio_nobtag_nomindphi_fb -> GetFunction( "pol0" ) ;
      func -> SetLineColor(2) ;
      c_sigsbratio -> Update() ; c_sigsbratio -> Draw() ;
      c_sigsbratio -> SaveAs( "outputfiles/h_metsig_sigsb_ratio_nobtag_nomindphi_fb.pdf" ) ;

      h_metsig_sigsb_ratio_nobtag_fb -> Fit( "pol0" ) ;
      func = h_metsig_sigsb_ratio_nobtag_fb -> GetFunction( "pol0" ) ;
      func -> SetLineColor(2) ;
      c_sigsbratio -> Update() ; c_sigsbratio -> Draw() ;
      c_sigsbratio -> SaveAs( "outputfiles/h_metsig_sigsb_ratio_nobtag_fb.pdf" ) ;

      h_nb_sigsb_ratio_nometsig_nomindphi -> Fit( "pol0" ) ;
      func = h_nb_sigsb_ratio_nometsig_nomindphi -> GetFunction( "pol0" ) ;
      func -> SetLineColor(2) ;
      c_sigsbratio -> Update() ; c_sigsbratio -> Draw() ;
      c_sigsbratio -> SaveAs( "outputfiles/h_nb_sigsb_ratio_nometsig_nomindphi.pdf" ) ;

      h_nb_sigsb_ratio_nometsig -> Fit( "pol0" ) ;
      func = h_nb_sigsb_ratio_nometsig -> GetFunction( "pol0" ) ;
      func -> SetLineColor(2) ;
      c_sigsbratio -> Update() ; c_sigsbratio -> Draw() ;
      c_sigsbratio -> SaveAs( "outputfiles/h_nb_sigsb_ratio_nometsig.pdf" ) ;

      h_nb_sigsb_ratio_metsig30 -> Fit( "pol0" ) ;
      func = h_nb_sigsb_ratio_metsig30 -> GetFunction( "pol0" ) ;
      func -> SetLineColor(2) ;
      c_sigsbratio -> Update() ; c_sigsbratio -> Draw() ;
      c_sigsbratio -> SaveAs( "outputfiles/h_nb_sigsb_ratio_metsig30.pdf" ) ;






      //====== QCD METsig PDF ----------------------------------------------------------------------------------------

      TCanvas* c_metsigpdf = new TCanvas( "c_metsigpdf", "METsig pdf", 700, 500 ) ;

      gPad -> SetGridy(1) ;

      gStyle -> SetMarkerSize(3.0) ;
      gStyle -> SetPaintTextFormat(".3f") ;


      h_metsig_sigsb_nobtag_fb -> Scale( 1.0 / (h_metsig_sigsb_nobtag_fb->Integral()) ) ;

      h_metsig_sigsb_nobtag_fb -> SetMaximum(1.1) ;
      h_metsig_sigsb_nobtag_fb -> SetMinimum(0.0) ;

      h_metsig_sigsb_nobtag_fb -> UseCurrentStyle() ;

      h_metsig_sigsb_nobtag_fb -> SetLineWidth(3) ;
      h_metsig_sigsb_nobtag_fb -> SetLineColor(2) ;

      h_metsig_sigsb_nobtag_fb -> Draw() ;
      h_metsig_sigsb_nobtag_fb -> Draw("hist same") ;
      h_metsig_sigsb_nobtag_fb -> Draw( "text0 same" ) ;

      c_metsigpdf -> Update() ; c_metsigpdf -> Draw() ;
      c_metsigpdf -> SaveAs( "outputfiles/qcd-metsig-pdf.pdf" ) ;

      printf("\n\n QCD METsig PDF:\n" ) ;
      h_metsig_sigsb_nobtag_fb -> Print("all") ;



      //====== QCD Nb PDF ----------------------------------------------------------------------------------------

      TCanvas* c_nbpdf = new TCanvas( "c_nbpdf", "Nb pdf", 700, 500 ) ;

      gPad -> SetGridy(1) ;

      gStyle -> SetMarkerSize(3.0) ;
      gStyle -> SetPaintTextFormat(".3f") ;


      h_nb_sigsb_nometsig_nomindphi -> Scale( 1.0 / (h_nb_sigsb_nometsig_nomindphi->Integral(3,5)) ) ;

      h_nb_sigsb_nometsig_nomindphi -> SetMaximum(1.1) ;
      h_nb_sigsb_nometsig_nomindphi -> SetMinimum(0.0) ;

      h_nb_sigsb_nometsig_nomindphi -> UseCurrentStyle() ;

      h_nb_sigsb_nometsig_nomindphi -> SetLineWidth(3) ;
      h_nb_sigsb_nometsig_nomindphi -> SetLineColor(2) ;

      h_nb_sigsb_nometsig_nomindphi -> Draw() ;
      h_nb_sigsb_nometsig_nomindphi -> Draw("hist same") ;
      h_nb_sigsb_nometsig_nomindphi -> Draw( "text0 same" ) ;

      c_nbpdf -> Update() ; c_metsigpdf -> Draw() ;
      c_nbpdf -> SaveAs( "outputfiles/qcd-nb-pdf.pdf" ) ;

      printf( "\n\n QCD Nb pdf:\n" ) ;
      h_nb_sigsb_nometsig_nomindphi -> Print("all") ;
      printf("\n\n") ;





      //====== QCD 2D Nb vs METsig PDF ----------------------------------------------------------------------------------------

      TCanvas* c_2dpdf = new TCanvas( "c_2dpdf", "2D Nb vs METsig pdf", 700, 500 ) ;

      TH2F* h_qcd_2d_nb_vs_metsig_pdf = new TH2F( "h_qcd_2d_nb_vs_metsig_pdf", "QCD 2D Nb vs METsig PDF",  4, 0.5, 4.5,  3, 0.5, 3.5 ) ;

      printf("\n\n QCD 2D Nb vs METsig PDF: \n" ) ;

      for ( int msbi=1; msbi<=4; msbi++ ) {

         double p_metsig_val = h_metsig_sigsb_nobtag_fb -> GetBinContent( msbi ) ;
         double p_metsig_err = h_metsig_sigsb_nobtag_fb -> GetBinError( msbi ) ;

         char blabel[10] ;
         sprintf( blabel, "S bin %d", msbi ) ;
         h_qcd_2d_nb_vs_metsig_pdf -> GetXaxis() -> SetBinLabel( msbi, blabel ) ;

         for ( int nbi=1; nbi<=3; nbi++ ) {

            double p_nb_val = h_nb_sigsb_nometsig_nomindphi -> GetBinContent( 6-nbi ) ;
            double p_nb_err = h_nb_sigsb_nometsig_nomindphi -> GetBinError( 6-nbi ) ;

            double p_2d_val = p_metsig_val * p_nb_val ;
            double p_2d_err = 0. ;
            if ( p_nb_val > 0 && p_metsig_val > 0 ) {
               p_2d_err = p_2d_val * sqrt( pow( p_metsig_err / p_metsig_val, 2 ) + pow( p_2d_err / p_2d_val, 2 ) ) ;
            }
            printf("   METsig %d, Nb %d :  (%.3f +/- %.3f) * (%.3f +/- %.3f)  =  (%.4f +/- %.4f)\n", msbi, 5-nbi,
                   p_metsig_val, p_metsig_err, p_nb_val, p_nb_err, p_2d_val, p_2d_err ) ;

            h_qcd_2d_nb_vs_metsig_pdf -> SetBinContent( msbi, nbi, p_2d_val ) ;
            h_qcd_2d_nb_vs_metsig_pdf -> SetBinError( msbi, nbi, p_2d_err ) ;

            sprintf( blabel, "Nb %d", 5-nbi ) ;
            h_qcd_2d_nb_vs_metsig_pdf -> GetYaxis() -> SetBinLabel( nbi, blabel ) ;

         } // nbi
      } // msbi

      h_qcd_2d_nb_vs_metsig_pdf -> SetFillColor( kRed-10 ) ;
      gStyle -> SetPaintTextFormat(".4f") ;
      h_qcd_2d_nb_vs_metsig_pdf -> SetLabelSize( 0.070, "x" ) ;
      h_qcd_2d_nb_vs_metsig_pdf -> SetLabelSize( 0.070, "y" ) ;

      h_qcd_2d_nb_vs_metsig_pdf -> Draw( "box" ) ;
      h_qcd_2d_nb_vs_metsig_pdf -> Draw( "texte same" ) ;

      c_2dpdf -> Update() ; c_2dpdf -> Draw() ;
      c_2dpdf -> SaveAs( "outputfiles/qcd-2d-pdf.pdf" ) ;



   } // draw_qcdstudy1





