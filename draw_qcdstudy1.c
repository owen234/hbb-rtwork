
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
      TH1F* h_metsig_sigsb_nobtag_nomindphi_fb = (TH1F*) gDirectory -> FindObject( "h_metsig_sigsb_nobtag_nomindphi_fb" ) ;
      TH1F* h_metsig_sigsb_nobtag_fb = (TH1F*) gDirectory -> FindObject( "h_metsig_sigsb_nobtag_fb" ) ;
      TH1F* h_metsig_sigsb_2b_fb = (TH1F*) gDirectory -> FindObject( "h_metsig_sigsb_2b_fb" ) ;
      TH1F* h_metsig_sigsb_3b_fb = (TH1F*) gDirectory -> FindObject( "h_metsig_sigsb_3b_fb" ) ;
      TH1F* h_metsig_sigsb_4b_fb = (TH1F*) gDirectory -> FindObject( "h_metsig_sigsb_4b_fb" ) ;
      TH1F* h_metsig_ttbar_allcuts_ub = (TH1F*) gDirectory -> FindObject( "h_metsig_ttbar_allcuts_ub" ) ;
      TH1F* h_metsig_ttbar_sigsb_allcuts_fb = (TH1F*) gDirectory -> FindObject( "h_metsig_ttbar_sigsb_allcuts_fb" ) ;

      h_metsig_sigsb_nobtag_nomindphi_ub -> SetLineWidth(2) ;
      h_metsig_sigsb_nobtag_nomindphi_ub -> SetLineColor(2) ;
      h_metsig_sigsb_nobtag_nomindphi_ub -> SetXTitle( "METsig" ) ;
      h_metsig_sigsb_nobtag_nomindphi_fb -> SetLineWidth(2) ;
      h_metsig_sigsb_nobtag_nomindphi_fb -> SetLineColor(2) ;
      h_metsig_sigsb_nobtag_nomindphi_fb -> SetXTitle( "METsig" ) ;
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

      hmax = 1.2 * ( h_metsig_sigsb_nobtag_nomindphi_fb -> GetMaximum() ) ;
      h_metsig_sigsb_nobtag_nomindphi_fb -> SetMaximum( hmax ) ;

      h_metsig_sigsb_nobtag_nomindphi_fb -> Draw( "hist" ) ;
      h_metsig_sigsb_nobtag_nomindphi_fb -> Draw( "same" ) ;

      c_metsig -> Update() ; c_metsig -> Draw() ;
      c_metsig -> SaveAs( "outputfiles/h_metsig_sigsb_nobtag_nomindphi_fb-liny.pdf" ) ;


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

      hmax = 2.0 * ( h_metsig_sigsb_nobtag_nomindphi_fb -> GetMaximum() ) ;
      h_metsig_sigsb_nobtag_nomindphi_fb -> SetMaximum( hmax ) ;
      h_metsig_sigsb_nobtag_nomindphi_fb -> SetMinimum( hmin ) ;

      h_metsig_sigsb_nobtag_nomindphi_fb -> Draw( "hist" ) ;
      h_metsig_sigsb_nobtag_nomindphi_fb -> Draw( "same" ) ;

      c_metsig -> Update() ; c_metsig -> Draw() ;
      c_metsig -> SaveAs( "outputfiles/h_metsig_sigsb_nobtag_nomindphi_fb-logy.pdf" ) ;


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

      if ( h_metsig_sigsb_2b_fb->Integral() > 0 ) {
         h_metsig_sigsb_nobtag_fb -> Scale( (h_metsig_sigsb_2b_fb->Integral())/(h_metsig_sigsb_nobtag_fb->Integral()) ) ;
      }

      hmax = 1.2 * ( h_metsig_sigsb_2b_fb->GetMaximum() ) ;
      h_metsig_sigsb_2b_fb -> SetMaximum( hmax ) ;
      h_metsig_sigsb_2b_fb -> Draw( ) ;
      h_metsig_sigsb_nobtag_fb -> Draw( "hist same" ) ;
      h_metsig_sigsb_nobtag_fb -> Draw( "same" ) ;
      h_metsig_sigsb_2b_fb -> Draw( "same" ) ;

      c_metsig -> Update() ; c_metsig -> Draw() ;
      c_metsig -> SaveAs( "outputfiles/h_metsig_sigsb_2b_fb.pdf" ) ;


      //------

      if ( h_metsig_sigsb_3b_fb->Integral() > 0 ) {
         h_metsig_sigsb_nobtag_fb -> Scale( (h_metsig_sigsb_3b_fb->Integral())/(h_metsig_sigsb_nobtag_fb->Integral()) ) ;
      }

      hmax = 1.2 * ( h_metsig_sigsb_3b_fb->GetMaximum() ) ;
      h_metsig_sigsb_3b_fb -> SetMaximum( hmax ) ;
      h_metsig_sigsb_3b_fb -> Draw( ) ;
      h_metsig_sigsb_nobtag_fb -> Draw( "hist same" ) ;
      h_metsig_sigsb_nobtag_fb -> Draw( "same" ) ;
      h_metsig_sigsb_3b_fb -> Draw( "same" ) ;

      c_metsig -> Update() ; c_metsig -> Draw() ;
      c_metsig -> SaveAs( "outputfiles/h_metsig_sigsb_3b_fb.pdf" ) ;


      //------

      if ( h_metsig_sigsb_4b_fb->Integral() > 0 ) {
         h_metsig_sigsb_nobtag_fb -> Scale( (h_metsig_sigsb_4b_fb->Integral())/(h_metsig_sigsb_nobtag_fb->Integral()) ) ;
      }

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

      printf("\n\n working on METsig pdf.\n\n") ;
      printf(" integral of h_metsig_sigsb_nobtag_fb : %.2f\n", h_metsig_sigsb_nobtag_fb->Integral() ) ;
      h_metsig_sigsb_nobtag_fb->Print("all") ;
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





      //====== QCD METsig, nomindphi PDF ----------------------------------------------------------------------------------------

      gPad -> SetGridy(1) ;

      gStyle -> SetMarkerSize(3.0) ;
      gStyle -> SetPaintTextFormat(".3f") ;

      printf("\n\n working on METsig pdf.\n\n") ;
      printf(" integral of h_metsig_sigsb_nobtag_nomindphi_fb : %.2f\n", h_metsig_sigsb_nobtag_nomindphi_fb->Integral() ) ;
      h_metsig_sigsb_nobtag_nomindphi_fb->Print("all") ;
      h_metsig_sigsb_nobtag_nomindphi_fb -> Scale( 1.0 / (h_metsig_sigsb_nobtag_nomindphi_fb->Integral()) ) ;

      h_metsig_sigsb_nobtag_nomindphi_fb -> SetMaximum(1.1) ;
      h_metsig_sigsb_nobtag_nomindphi_fb -> SetMinimum(0.0) ;

      h_metsig_sigsb_nobtag_nomindphi_fb -> UseCurrentStyle() ;

      h_metsig_sigsb_nobtag_nomindphi_fb -> SetLineWidth(3) ;
      h_metsig_sigsb_nobtag_nomindphi_fb -> SetLineColor(2) ;

      h_metsig_sigsb_nobtag_nomindphi_fb -> Draw() ;
      h_metsig_sigsb_nobtag_nomindphi_fb -> Draw("hist same") ;
      h_metsig_sigsb_nobtag_nomindphi_fb -> Draw( "text0 same" ) ;

      c_metsigpdf -> Update() ; c_metsigpdf -> Draw() ;
      c_metsigpdf -> SaveAs( "outputfiles/qcd-metsig-pdf-nomindphi.pdf" ) ;

      printf("\n\n QCD METsig PDF, nomindphi:\n" ) ;
      h_metsig_sigsb_nobtag_nomindphi_fb -> Print("all") ;





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



      //====== QCD 2D Nb vs METsig PDF, nomindphi ----------------------------------------------------------------------------------------

      TCanvas* c_2dpdf_nomindphi = new TCanvas( "c_2dpdf_nomindphi", "2D Nb vs METsig pdf, no minDeltaPhi", 700, 500 ) ;

      TH2F* h_qcd_2d_nb_vs_metsig_nomindphi_pdf = new TH2F( "h_qcd_2d_nb_vs_metsig_nomindphi_pdf", "QCD 2D Nb vs METsig PDF, no minDeltaPhi",  4, 0.5, 4.5,  3, 0.5, 3.5 ) ;

      printf("\n\n QCD 2D Nb vs METsig PDF, no minDeltaPhi: \n" ) ;

      for ( int msbi=1; msbi<=4; msbi++ ) {

         double p_metsig_val = h_metsig_sigsb_nobtag_nomindphi_fb -> GetBinContent( msbi ) ;
         double p_metsig_err = h_metsig_sigsb_nobtag_nomindphi_fb -> GetBinError( msbi ) ;

         char blabel[10] ;
         sprintf( blabel, "S bin %d", msbi ) ;
         h_qcd_2d_nb_vs_metsig_nomindphi_pdf -> GetXaxis() -> SetBinLabel( msbi, blabel ) ;

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

            h_qcd_2d_nb_vs_metsig_nomindphi_pdf -> SetBinContent( msbi, nbi, p_2d_val ) ;
            h_qcd_2d_nb_vs_metsig_nomindphi_pdf -> SetBinError( msbi, nbi, p_2d_err ) ;

            sprintf( blabel, "Nb %d", 5-nbi ) ;
            h_qcd_2d_nb_vs_metsig_nomindphi_pdf -> GetYaxis() -> SetBinLabel( nbi, blabel ) ;

         } // nbi
      } // msbi

      h_qcd_2d_nb_vs_metsig_nomindphi_pdf -> SetFillColor( kRed-10 ) ;
      gStyle -> SetPaintTextFormat(".4f") ;
      h_qcd_2d_nb_vs_metsig_nomindphi_pdf -> SetLabelSize( 0.070, "x" ) ;
      h_qcd_2d_nb_vs_metsig_nomindphi_pdf -> SetLabelSize( 0.070, "y" ) ;

      h_qcd_2d_nb_vs_metsig_nomindphi_pdf -> Draw( "box" ) ;
      h_qcd_2d_nb_vs_metsig_nomindphi_pdf -> Draw( "texte same" ) ;

      c_2dpdf_nomindphi -> Update() ; c_2dpdf_nomindphi -> Draw() ;
      c_2dpdf_nomindphi -> SaveAs( "outputfiles/qcd-2d-pdf-nomindphi.pdf" ) ;





      //====== ttbar 2D Nb vs METsig events ----------------------------------------------------------------------------------------

      TCanvas* c_tt2devents = new TCanvas( "c_tt2devents", "ttbar, 2D Nb vs METsig events", 700, 500 ) ;

      gStyle -> SetPaintTextFormat(".1f") ;

      TH2F* h_nb_vs_metsig_ttbar = (TH2F*) gDirectory -> FindObject( "h_nb_vs_metsig_ttbar" ) ;
      h_nb_vs_metsig_ttbar -> UseCurrentStyle() ;
      h_nb_vs_metsig_ttbar -> SetFillColor( kBlue - 10 ) ;
      h_nb_vs_metsig_ttbar -> SetLabelSize( 0.070, "x" ) ;
      h_nb_vs_metsig_ttbar -> SetLabelSize( 0.070, "y" ) ;

      h_nb_vs_metsig_ttbar -> Draw( "box" ) ;
      h_nb_vs_metsig_ttbar -> Draw( "texte same" ) ;

      c_tt2devents -> Update() ; c_tt2devents -> Draw() ;
      c_tt2devents -> SaveAs( "outputfiles/ttbar-2d-events.pdf" ) ;


      //====== ttbar 2D Nb vs METsig, nomindphi, events ----------------------------------------------------------------------------------------

      gStyle -> SetPaintTextFormat(".1f") ;

      TH2F* h_nb_vs_metsig_ttbar_nomindphi = (TH2F*) gDirectory -> FindObject( "h_nb_vs_metsig_ttbar_nomindphi" ) ;
      h_nb_vs_metsig_ttbar_nomindphi -> UseCurrentStyle() ;
      h_nb_vs_metsig_ttbar_nomindphi -> SetFillColor( kBlue - 10 ) ;
      h_nb_vs_metsig_ttbar_nomindphi -> SetLabelSize( 0.070, "x" ) ;
      h_nb_vs_metsig_ttbar_nomindphi -> SetLabelSize( 0.070, "y" ) ;

      h_nb_vs_metsig_ttbar_nomindphi -> Draw( "box" ) ;
      h_nb_vs_metsig_ttbar_nomindphi -> Draw( "texte same" ) ;

      c_tt2devents -> Update() ; c_tt2devents -> Draw() ;
      c_tt2devents -> SaveAs( "outputfiles/ttbar-2d-events-nomindphi.pdf" ) ;


      //====== ttbar 2D Nb vs METsig PDF ----------------------------------------------------------------------------------------

      TCanvas* c_tt2dpdf = new TCanvas( "c_tt2dpdf", "ttbar, 2D Nb vs METsig pdf", 700, 500 ) ;

      TH2F* h_nb_vs_metsig_ttbar_pdf = (TH2F*) h_nb_vs_metsig_ttbar -> Clone( "h_nb_vs_metsig_ttbar_pdf" ) ;

      gStyle -> SetPaintTextFormat(".4f") ;

      h_nb_vs_metsig_ttbar_pdf -> Scale( 1./(h_nb_vs_metsig_ttbar_pdf->Integral()) ) ;

      h_nb_vs_metsig_ttbar_pdf -> Draw( "box" ) ;
      h_nb_vs_metsig_ttbar_pdf -> Draw( "texte same" ) ;

      c_tt2dpdf -> Update() ; c_tt2dpdf -> Draw() ;
      c_tt2dpdf -> SaveAs( "outputfiles/ttbar-2d-pdf.pdf" ) ;


      //====== ttbar 2D Nb vs METsig, nomindphi PDF ----------------------------------------------------------------------------------------

      TH2F* h_nb_vs_metsig_ttbar_nomindphi_pdf = (TH2F*) h_nb_vs_metsig_ttbar_nomindphi -> Clone( "h_nb_vs_metsig_ttbar_nomindphi_pdf" ) ;

      gStyle -> SetPaintTextFormat(".4f") ;

      h_nb_vs_metsig_ttbar_nomindphi_pdf -> Scale( 1./(h_nb_vs_metsig_ttbar_nomindphi_pdf->Integral()) ) ;

      h_nb_vs_metsig_ttbar_nomindphi_pdf -> Draw( "box" ) ;
      h_nb_vs_metsig_ttbar_nomindphi_pdf -> Draw( "texte same" ) ;

      c_tt2dpdf -> Update() ; c_tt2dpdf -> Draw() ;
      c_tt2dpdf -> SaveAs( "outputfiles/ttbar-2d-pdf-nomindphi.pdf" ) ;


      //====== QCD 2D Nb vs METsig events ----------------------------------------------------------------------------------------

      TCanvas* c_qcd2devts = new TCanvas( "c_qcd2devts", "QCD, 2D Nb vs METsig events", 700, 500 ) ;

      gStyle -> SetPaintTextFormat(".1f") ;

      TH2F* h_nb_vs_metsig_qcd = (TH2F*) gDirectory -> FindObject( "h_nb_vs_metsig_qcd" ) ;
      h_nb_vs_metsig_qcd -> UseCurrentStyle() ;
      h_nb_vs_metsig_qcd -> SetFillColor( kRed - 10 ) ;
      h_nb_vs_metsig_qcd -> SetLabelSize( 0.070, "x" ) ;
      h_nb_vs_metsig_qcd -> SetLabelSize( 0.070, "y" ) ;

      h_nb_vs_metsig_qcd -> Draw( "box" ) ;
      h_nb_vs_metsig_qcd -> Draw( "texte same" ) ;

      c_qcd2devts -> Update() ; c_qcd2devts -> Draw() ;
      c_qcd2devts -> SaveAs( "outputfiles/qcd-2d-events.pdf" ) ;


      //====== QCD 2D Nb vs METsig, nomindphi, events ----------------------------------------------------------------------------------------

      gStyle -> SetPaintTextFormat(".1f") ;

      TH2F* h_nb_vs_metsig_qcd_nomindphi = (TH2F*) gDirectory -> FindObject( "h_nb_vs_metsig_qcd_nomindphi" ) ;
      h_nb_vs_metsig_qcd_nomindphi -> UseCurrentStyle() ;
      h_nb_vs_metsig_qcd_nomindphi -> SetFillColor( kRed - 10 ) ;
      h_nb_vs_metsig_qcd_nomindphi -> SetLabelSize( 0.070, "x" ) ;
      h_nb_vs_metsig_qcd_nomindphi -> SetLabelSize( 0.070, "y" ) ;

      h_nb_vs_metsig_qcd_nomindphi -> Draw( "box" ) ;
      h_nb_vs_metsig_qcd_nomindphi -> Draw( "texte same" ) ;

      c_qcd2devts -> Update() ; c_qcd2devts -> Draw() ;
      c_qcd2devts -> SaveAs( "outputfiles/qcd-2d-events-nomindphi.pdf" ) ;


      //====== QCD 2D Nb vs METsig, nomindphi, x1.3, events ----------------------------------------------------------------------------------------

      TH2F* h_nb_vs_metsig_qcd_nomindphi_x13 = (TH2F*) h_nb_vs_metsig_qcd_nomindphi -> Clone( "h_nb_vs_metsig_qcd_nomindphi_x13" ) ;
      h_nb_vs_metsig_qcd_nomindphi_x13 -> SetTitle( "QCD Nb vs METsig bin, no minDeltaPhi, x1.3, events" ) ;
      h_nb_vs_metsig_qcd_nomindphi_x13 -> Scale( 1.3 ) ;

      h_nb_vs_metsig_qcd_nomindphi_x13 -> Draw( "box" ) ;
      h_nb_vs_metsig_qcd_nomindphi_x13 -> Draw( "texte same" ) ;

      c_qcd2devts -> Update() ; c_qcd2devts -> Draw() ;
      c_qcd2devts -> SaveAs( "outputfiles/qcd-2d-events-x13-nomindphi.pdf" ) ;



      //====== QCD 2D Nb vs METsig events, model prediction ----------------------------------------------------------------------------------------

      TCanvas* c_qcd2devts_mp = new TCanvas( "c_qcd2devts_mp", "QCD, 2D Nb vs METsig events, model", 700, 500 ) ;

      TH2F* h_qcd_2d_nb_vs_metsig_events_model = (TH2F*) h_qcd_2d_nb_vs_metsig_pdf -> Clone( "h_qcd_2d_nb_vs_metsig_events_model" ) ;

      h_qcd_2d_nb_vs_metsig_events_model -> Scale( (h_nb_vs_metsig_qcd->GetBinContent(1,3))/(h_qcd_2d_nb_vs_metsig_pdf->GetBinContent(1,3)) ) ;

      h_qcd_2d_nb_vs_metsig_events_model -> Draw( "box" ) ;
      h_qcd_2d_nb_vs_metsig_events_model -> Draw( "texte same" ) ;

      c_qcd2devts_mp -> Update() ; c_qcd2devts_mp -> Draw() ;
      c_qcd2devts_mp -> SaveAs( "outputfiles/qcd-2d-events-model.pdf" ) ;



      //====== QCD 2D Nb vs METsig events, nomindphi, model prediction ----------------------------------------------------------------------------------------

      TCanvas* c_qcd2devts_mp_nomindphi = new TCanvas( "c_qcd2devts_mp_nomindphi", "QCD, 2D Nb vs METsig events, no minDeltaPhi, model", 700, 500 ) ;

      TH2F* h_qcd_2d_nb_vs_metsig_nomindphi_events_model = (TH2F*) h_qcd_2d_nb_vs_metsig_nomindphi_pdf -> Clone( "h_qcd_2d_nb_vs_metsig_nomindphi_events_model" ) ;

      h_qcd_2d_nb_vs_metsig_nomindphi_events_model -> Scale( (h_nb_vs_metsig_qcd_nomindphi->GetBinContent(1,3))/(h_qcd_2d_nb_vs_metsig_nomindphi_pdf->GetBinContent(1,3)) ) ;

      h_qcd_2d_nb_vs_metsig_nomindphi_events_model -> Draw( "box" ) ;
      h_qcd_2d_nb_vs_metsig_nomindphi_events_model -> Draw( "texte same" ) ;

      c_qcd2devts_mp_nomindphi -> Update() ; c_qcd2devts_mp_nomindphi -> Draw() ;
      c_qcd2devts_mp_nomindphi -> SaveAs( "outputfiles/qcd-2d-events-model-nomindphi.pdf" ) ;


      //====== QCD 2D Nb vs METsig events, nomindphi, x1.3, model prediction ----------------------------------------------------------------------------------------

      TCanvas* c_qcd2devts_mp_nomindphi_x13 = new TCanvas( "c_qcd2devts_mp_nomindphi_x13", "QCD, 2D Nb vs METsig events, no minDeltaPhi, x1.3, model", 700, 500 ) ;

      TH2F* h_qcd_2d_nb_vs_metsig_nomindphi_x13_events_model = (TH2F*) h_qcd_2d_nb_vs_metsig_nomindphi_pdf -> Clone( "h_qcd_2d_nb_vs_metsig_nomindphi_events_model" ) ;

      h_qcd_2d_nb_vs_metsig_nomindphi_x13_events_model -> Scale( 1.3 * (h_nb_vs_metsig_qcd_nomindphi->GetBinContent(1,3))/(h_qcd_2d_nb_vs_metsig_nomindphi_pdf->GetBinContent(1,3)) ) ;

      h_qcd_2d_nb_vs_metsig_nomindphi_x13_events_model -> Draw( "box" ) ;
      h_qcd_2d_nb_vs_metsig_nomindphi_x13_events_model -> Draw( "texte same" ) ;

      c_qcd2devts_mp_nomindphi_x13 -> Update() ; c_qcd2devts_mp_nomindphi_x13 -> Draw() ;
      c_qcd2devts_mp_nomindphi_x13 -> SaveAs( "outputfiles/qcd-2d-events-model-nomindphi-x13.pdf" ) ;




      //====== QCD fraction, model prediction ----------------------------------------------------------------------------------------

      TCanvas* c_qcdfrac = new TCanvas( "c_qcdfrac", "QCD fraction", 700, 500 ) ;

      gStyle -> SetPaintTextFormat(".3f") ;

      TH2F* h_qcd_2d_nb_vs_metsig_fraction_mc = (TH2F*) h_qcd_2d_nb_vs_metsig_events_model -> Clone( "h_qcd_2d_nb_vs_metsig_fraction_mc" ) ;
      h_qcd_2d_nb_vs_metsig_fraction_mc -> SetTitle( "QCD fraction" ) ;

      for ( int msbi=1; msbi<=4; msbi++ ) {
         for ( int nbi=1; nbi<=3; nbi++ ) {
            double qcd_val = h_qcd_2d_nb_vs_metsig_events_model -> GetBinContent( msbi, nbi ) ;
            double qcd_err = h_qcd_2d_nb_vs_metsig_events_model -> GetBinError( msbi, nbi ) ;
            double ttbar_val =  h_nb_vs_metsig_ttbar -> GetBinContent( msbi, nbi ) ;
            double ttbar_err =  h_nb_vs_metsig_ttbar -> GetBinError( msbi, nbi ) ;
            double sum = qcd_val + ttbar_val ;
            double frac_val(0.)  ;
            double frac_err(0.) ;
            if ( sum > 0 ) {
               frac_val = qcd_val / sum ;
               frac_err = pow( 1./sum, 2 ) * sqrt( pow( qcd_val * ttbar_err, 2 ) + pow( ttbar_val * qcd_err, 2 ) ) ;
            }
            h_qcd_2d_nb_vs_metsig_fraction_mc -> SetBinContent( msbi, nbi, frac_val ) ;
            h_qcd_2d_nb_vs_metsig_fraction_mc -> SetBinError( msbi, nbi, frac_err ) ;
         } // nbi.
      } // msbi

      h_qcd_2d_nb_vs_metsig_fraction_mc -> Draw( "box" ) ;
      h_qcd_2d_nb_vs_metsig_fraction_mc -> Draw( "texte same" ) ;

      c_qcdfrac -> Update() ; c_qcdfrac -> Draw() ;
      c_qcdfrac -> SaveAs( "outputfiles/h_qcd_2d_nb_vs_metsig_fraction_mc.pdf" ) ;


      //====== QCD fraction, model prediction ----------------------------------------------------------------------------------------

      TCanvas* c_qcdfrac_qcdx2 = new TCanvas( "c_qcdfrac_qcdx2", "QCD fraction, QCD x 2", 700, 500 ) ;

      gStyle -> SetPaintTextFormat(".3f") ;

      TH2F* h_qcd_2d_nb_vs_metsig_fraction_mc_qcdx2 = (TH2F*) h_qcd_2d_nb_vs_metsig_events_model -> Clone( "h_qcd_2d_nb_vs_metsig_fraction_mc_qcdx2" ) ;
      h_qcd_2d_nb_vs_metsig_fraction_mc_qcdx2 -> SetTitle( "QCD fraction, QCD x 2" ) ;

      for ( int msbi=1; msbi<=4; msbi++ ) {
         for ( int nbi=1; nbi<=3; nbi++ ) {
            double qcd_val = 2. * ( h_qcd_2d_nb_vs_metsig_events_model -> GetBinContent( msbi, nbi ) ) ;
            double qcd_err = 2. * ( h_qcd_2d_nb_vs_metsig_events_model -> GetBinError( msbi, nbi ) ) ;
            double ttbar_val =  h_nb_vs_metsig_ttbar -> GetBinContent( msbi, nbi ) ;
            double ttbar_err =  h_nb_vs_metsig_ttbar -> GetBinError( msbi, nbi ) ;
            double sum = qcd_val + ttbar_val ;
            double frac_val(0.)  ;
            double frac_err(0.) ;
            if ( sum > 0 ) {
               frac_val = qcd_val / sum ;
               frac_err = pow( 1./sum, 2 ) * sqrt( pow( qcd_val * ttbar_err, 2 ) + pow( ttbar_val * qcd_err, 2 ) ) ;
            }
            h_qcd_2d_nb_vs_metsig_fraction_mc_qcdx2 -> SetBinContent( msbi, nbi, frac_val ) ;
            h_qcd_2d_nb_vs_metsig_fraction_mc_qcdx2 -> SetBinError( msbi, nbi, frac_err ) ;
         } // nbi.
      } // msbi

      h_qcd_2d_nb_vs_metsig_fraction_mc_qcdx2 -> Draw( "box" ) ;
      h_qcd_2d_nb_vs_metsig_fraction_mc_qcdx2 -> Draw( "texte same" ) ;

      c_qcdfrac_qcdx2 -> Update() ; c_qcdfrac_qcdx2 -> Draw() ;
      c_qcdfrac_qcdx2 -> SaveAs( "outputfiles/h_qcd_2d_nb_vs_metsig_fraction_mc_qcdx2.pdf" ) ;



      //====== compute sample SIG and SB fractions ----------------------------------------------------------------------------------------

      double qcd_total     = h_deltam_vs_avem_nometsig_nobtag_nomindphi -> Integral() ;
      double qcd_sig       = h_deltam_vs_avem_nometsig_nobtag_nomindphi -> Integral( 11,14, 1,2 ) ;
      double qcd_sig_buf   = h_deltam_vs_avem_nometsig_nobtag_nomindphi -> Integral( 10,15, 1,3 ) ;

      double f_qcd_sig = qcd_sig / qcd_total ;
      double f_qcd_sb  = (qcd_total - qcd_sig_buf) / qcd_total ;

      double ttbar_total     = h_deltam_vs_avem_ttbar_allcuts -> Integral() ;
      double ttbar_sig       = h_deltam_vs_avem_ttbar_allcuts -> Integral( 11,14, 1,2 ) ;
      double ttbar_sig_buf   = h_deltam_vs_avem_ttbar_allcuts -> Integral( 10,15, 1,3 ) ;

      double f_ttbar_sig = ttbar_sig / ttbar_total ;
      double f_ttbar_sb  = (ttbar_total - ttbar_sig_buf) / ttbar_total ;

      printf(" \n\n QCD   fractions:  f_sig = %.3f ,  f_sb = %.3f ,  SIG/SB = %.3f \n", f_qcd_sig, f_qcd_sb, f_qcd_sig / f_qcd_sb ) ;
      printf(" \n\n ttbar fractions:  f_sig = %.3f ,  f_sb = %.3f ,  SIG/SB = %.3f \n", f_ttbar_sig, f_ttbar_sb, f_ttbar_sig / f_ttbar_sb ) ;
      printf("\n\n") ;


      //====== Fill SIG and SB histograms for QCD and ttbar ----------------------------------------------------------------------------------------

      TH2F* h_qcd = (TH2F*) h_qcd_2d_nb_vs_metsig_events_model -> Clone( "h_qcd" ) ;
      h_qcd -> SetTitle( "QCD, all" ) ;

      TH2F* h_qcd_sb = (TH2F*) h_qcd -> Clone( "h_qcd_sb" ) ;
      h_qcd_sb -> SetTitle( "QCD, SB" ) ;
      h_qcd_sb -> Scale( f_qcd_sb ) ;

      TH2F* h_qcd_sig = (TH2F*) h_qcd -> Clone( "h_qcd_sig" ) ;
      h_qcd_sig -> SetTitle( "QCD, SIG" ) ;
      h_qcd_sig -> Scale( f_qcd_sig ) ;


      TH2F* h_ttbar = (TH2F*) h_nb_vs_metsig_ttbar -> Clone( "h_ttbar" ) ;
      h_ttbar -> SetTitle( "ttbar, all" ) ;

      TH2F* h_ttbar_sb = (TH2F*) h_ttbar -> Clone( "h_ttbar_sb" ) ;
      h_ttbar_sb -> SetTitle( "ttbar, SB" ) ;
      h_ttbar_sb -> Scale( f_ttbar_sb ) ;

      TH2F* h_ttbar_sig = (TH2F*) h_ttbar -> Clone( "h_ttbar_sig" ) ;
      h_ttbar_sig -> SetTitle( "ttbar, SIG" ) ;
      h_ttbar_sig -> Scale( f_ttbar_sig ) ;


      //====== Fill SIG and SB histograms for sum of QCD and ttbar, nominal ----------------------------------------------------------------------------------------

      TH2F* h_sb = (TH2F*) h_qcd_sb -> Clone( "h_sb" ) ;
      h_sb -> SetTitle("Sum (QCD+ttbar), SB") ;
      h_sb -> Reset() ;
      h_sb -> Sumw2() ;
      h_sb -> Add( h_qcd_sb ) ;
      h_sb -> Add( h_ttbar_sb ) ;

      TH2F* h_sig = (TH2F*) h_qcd_sig -> Clone( "h_sig" ) ;
      h_sig -> SetTitle("Sum (QCD+ttbar), SIG") ;
      h_sig -> Reset() ;
      h_sig -> Sumw2() ;
      h_sig -> Add( h_qcd_sig ) ;
      h_sig -> Add( h_ttbar_sig ) ;

      //====== Fill SIG/SB ratio histogram, nominal ----------------------------------------------------------------------------------------

      gStyle -> SetPaintTextFormat(".4f") ;

      TH2F* h_sigsb_ratio = (TH2F*) h_sig -> Clone( "h_sigsb_ratio" ) ;
      h_sigsb_ratio -> SetTitle( "SIG/SB ratio" ) ;
      h_sigsb_ratio -> Divide( h_sb ) ;

      TCanvas* c_ratio = new TCanvas("c_ratio", "SIG/SB ratio", 700, 500 ) ;

      h_sigsb_ratio -> Draw("text" ) ;

      c_ratio -> Update() ; c_ratio -> Draw() ;
      c_ratio -> SaveAs( "outputfiles/h_sigsb_ratio.pdf" ) ;



      //====== Scale up QCD by x 2: Fill SIG and SB histograms for sum of QCD and ttbar ----------------------------------------------------------------------------------------

      TH2F* h_sb_qcdx2 = (TH2F*) h_qcd_sb -> Clone( "h_sb_qcdx2" ) ;
      h_sb_qcdx2 -> SetTitle("Sum (QCDx2+ttbar), SB") ;
      h_sb_qcdx2 -> Reset() ;
      h_sb_qcdx2 -> Sumw2() ;
      h_sb_qcdx2 -> Add( h_qcd_sb ) ;
      h_sb_qcdx2 -> Scale( 2.0 ) ;
      h_sb_qcdx2 -> Add( h_ttbar_sb ) ;

      TH2F* h_sig_qcdx2 = (TH2F*) h_qcd_sig -> Clone( "h_sig_qcdx2" ) ;
      h_sig_qcdx2 -> SetTitle("Sum (QCDx2+ttbar), SIG") ;
      h_sig_qcdx2 -> Reset() ;
      h_sig_qcdx2 -> Sumw2() ;
      h_sig_qcdx2 -> Add( h_qcd_sig ) ;
      h_sig_qcdx2 -> Scale( 2.0 ) ;
      h_sig_qcdx2 -> Add( h_ttbar_sig ) ;

      //====== Scale up QCD by x 2 : Fill SIG/SB ratio histogram ----------------------------------------------------------------------------------------

      gStyle -> SetPaintTextFormat(".4f") ;

      TH2F* h_sigsb_ratio_qcdx2 = (TH2F*) h_sig_qcdx2 -> Clone( "h_sigsb_ratio_qcdx2" ) ;
      h_sigsb_ratio_qcdx2 -> SetTitle( "SIG/SB ratio, QCD x 2" ) ;
      h_sigsb_ratio_qcdx2 -> Divide( h_sb_qcdx2 ) ;

      TCanvas* c_ratio_qcdx2 = new TCanvas("c_ratio_qcdx2", "SIG/SB ratio, QCDx2", 700, 500 ) ;

      h_sigsb_ratio_qcdx2 -> Draw("text" ) ;

      c_ratio_qcdx2 -> Update() ; c_ratio_qcdx2 -> Draw() ;
      c_ratio_qcdx2 -> SaveAs( "outputfiles/h_sigsb_ratio_qcdx2.pdf" ) ;



      //====== Ratio of ratios: R(4b)/R(2b) and R(3b)/R(2b), nominal ----------------------------------------------------------------------------------------

      TH2F* h_ratio_of_ratios = (TH2F*) h_sigsb_ratio -> Clone( "h_ratio_of_ratios" ) ;
      h_ratio_of_ratios -> SetTitle( "Ratio of ratios:  (SIG/SB nb) / (SIG/SB 2b)" ) ;

      for ( int msbi=1; msbi<=4; msbi++ ) {
         double ratio_2b = h_sigsb_ratio -> GetBinContent( msbi, 3 ) ;
         for ( int nbi=1; nbi<=3; nbi++ ) {
            double ratio_nb = h_sigsb_ratio -> GetBinContent( msbi, nbi ) ;
            double ratio_of_ratios(0.) ;
            if ( ratio_2b > 0. ) { ratio_of_ratios = ratio_nb / ratio_2b ; }
            h_ratio_of_ratios -> SetBinContent( msbi, nbi, ratio_of_ratios ) ;
            h_ratio_of_ratios -> SetBinError( msbi, nbi, 0. ) ;
         } // nbi
      } // msbi

      TCanvas* c_rofr = new TCanvas("c_rofr", "Ratio of SIG/SB ratios", 700, 500 ) ;

      gStyle -> SetPaintTextFormat(".3f") ;
      h_ratio_of_ratios -> Draw( "text" ) ;

      c_rofr -> Update() ; c_rofr -> Draw() ;
      c_rofr -> SaveAs( "outputfiles/h_ratio_of_ratios.pdf" ) ;



      //====== Ratio of ratios: R(4b)/R(2b) and R(3b)/R(2b), QCD x 2 ----------------------------------------------------------------------------------------

      TH2F* h_ratio_of_ratios_qcdx2 = (TH2F*) h_sigsb_ratio_qcdx2 -> Clone( "h_ratio_of_ratios_qcdx2" ) ;
      h_ratio_of_ratios_qcdx2 -> SetTitle( "Ratio of ratios:  (SIG/SB nb) / (SIG/SB 2b),  QCD x 2" ) ;

      for ( int msbi=1; msbi<=4; msbi++ ) {
         double ratio_2b = h_sigsb_ratio_qcdx2 -> GetBinContent( msbi, 3 ) ;
         for ( int nbi=1; nbi<=3; nbi++ ) {
            double ratio_nb = h_sigsb_ratio_qcdx2 -> GetBinContent( msbi, nbi ) ;
            double ratio_of_ratios(0.) ;
            if ( ratio_2b > 0. ) { ratio_of_ratios = ratio_nb / ratio_2b ; }
            h_ratio_of_ratios_qcdx2 -> SetBinContent( msbi, nbi, ratio_of_ratios ) ;
            h_ratio_of_ratios_qcdx2 -> SetBinError( msbi, nbi, 0. ) ;
         } // nbi
      } // msbi

      TCanvas* c_rofr_qcdx2 = new TCanvas("c_rofr_qcdx2", "Ratio of SIG/SB ratios, QCD x 2", 700, 500 ) ;

      gStyle -> SetPaintTextFormat(".3f") ;
      h_ratio_of_ratios_qcdx2 -> Draw( "text" ) ;

      c_rofr_qcdx2 -> Update() ; c_rofr_qcdx2 -> Draw() ;
      c_rofr_qcdx2 -> SaveAs( "outputfiles/h_ratio_of_ratios_qcdx2.pdf" ) ;


   } // draw_qcdstudy1





