#include "TH1F.h"
#include "TH2F.h"
#include "THStack.h"
#include "TRegexp.h"
#include "TKey.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TLine.h"
#include "TText.h"
#include "TString.h"
#include "TRegexp.h"
#include "TBox.h"

#include "histio.c"

#include <iostream>

   bool recycleCanvas(false) ;

 //--------------------
   int  nsamples(4) ;
   int  nbgsamples(2) ;
   char samplename[4][100] = { "znn", "tt", "sig250", "sig400" } ;
 //--------------------
 //int  nsamples(5) ;
 //int  nbgsamples(3) ;
 //char samplename[5][100] = { "znn", "ttsl", "tthad", "sig250", "sig400" } ;
 //--------------------

   bool savePdf ;
   char inrootfile[10000] ;

   void drawcanvas( const char* hnamebase, const char* canname, const char* cantitle, const char* pdffile ) ;
   void drawplot( TString hname ) ;

  //==========================================================================================

   void drawplots3b2d( bool arg_savePdf = true, const char* infile = "plots3b.root", bool arg_recycleCanvas=false ) {

       recycleCanvas = arg_recycleCanvas ;
       savePdf = arg_savePdf ;

       gDirectory->Delete("h*") ;

       loadHist( infile ) ;



       gStyle -> SetOptStat("i") ;
       gStyle -> SetStatY(0.90) ;
       gStyle -> SetStatH(0.25) ;
       gStyle -> SetStatW(0.25) ;
       gStyle -> SetPadLeftMargin(0.14) ;
       gStyle -> SetPadBottomMargin(0.14) ;
       gStyle -> SetPadGridX(1) ;
       gStyle -> SetPadGridY(1) ;
       gStyle -> SetTitleY(1.000 ) ;
       gStyle -> SetTitleX(0.100 ) ;
       gStyle -> SetTitleH(0.090 ) ;
       gStyle -> SetLabelSize( 0.060, "x" ) ;
       gStyle -> SetLabelSize( 0.060, "y" ) ;
       gStyle -> SetTitleSize( 0.060, "x" ) ;
       gStyle -> SetTitleSize( 0.060, "y" ) ;

       drawcanvas( "h_dmvsam_4b_metsig30", "cmetsig30", "delta m vs ave m, METsig>30", "outputfiles/dmvsam_metsig30.pdf" ) ;

       drawcanvas( "h_dmvsam_4b_metsig30_50", "cmetsig30_50", "delta m vs ave m, METsig [30,50]", "outputfiles/dmvsam_metsig030-50.pdf" ) ;
       drawcanvas( "h_dmvsam_4b_metsig50_100", "cmetsig50_100", "delta m vs ave m, METsig [50,100]", "outputfiles/dmvsam_metsig050-100.pdf" ) ;
       drawcanvas( "h_dmvsam_4b_metsig100_150", "cmetsig100_150", "delta m vs ave m, METsig [100,150]", "outputfiles/dmvsam_metsig100-150.pdf" ) ;
       drawcanvas( "h_dmvsam_4b_metsig150", "cmetsig150", "delta m vs ave m, METsig>150", "outputfiles/dmvsam_metsig150.pdf" ) ;

   } // drawplots3b2d.

  //==========================================================================================

   void drawcanvas( const char* hnamebase, const char* canname, const char* cantitle, const char* pdffile ) {

       TCanvas* can = new TCanvas( canname, cantitle, 900, 1000 ) ;

       can->Divide(3,4) ;

       TString hnamebasets( hnamebase ) ;
       TString hnamebase4b = hnamebasets ;
       TString hnamebase3b = hnamebasets ;
       TString hnamebase2b = hnamebasets ;

       hnamebase3b.ReplaceAll("4b","3b") ;
       hnamebase2b.ReplaceAll("4b","2b") ;


       can->cd(1) ;
       drawplot( hnamebase4b + TString("_tt") ) ;
       can->Update() ; can->Draw() ;

       can->cd(2) ;
       drawplot( hnamebase3b + TString("_tt") ) ;
       can->Update() ; can->Draw() ;

       can->cd(3) ;
       drawplot( hnamebase2b + TString("_tt") ) ;
       can->Update() ; can->Draw() ;


       can->cd(4) ;
       drawplot( hnamebase4b + TString("_znn") ) ;
       can->Update() ; can->Draw() ;

       can->cd(5) ;
       drawplot( hnamebase3b + TString("_znn") ) ;
       can->Update() ; can->Draw() ;

       can->cd(6) ;
       drawplot( hnamebase2b + TString("_znn") ) ;
       can->Update() ; can->Draw() ;


       can->cd(7) ;
       drawplot( hnamebase4b + TString("_sig250") ) ;
       can->Update() ; can->Draw() ;

       can->cd(8) ;
       drawplot( hnamebase3b + TString("_sig250") ) ;
       can->Update() ; can->Draw() ;

       can->cd(9) ;
       drawplot( hnamebase2b + TString("_sig250") ) ;
       can->Update() ; can->Draw() ;


       can->cd(10) ;
       drawplot( hnamebase4b + TString("_sig400") ) ;
       can->Update() ; can->Draw() ;

       can->cd(11) ;
       drawplot( hnamebase3b + TString("_sig400") ) ;
       can->Update() ; can->Draw() ;

       can->cd(12) ;
       drawplot( hnamebase2b + TString("_sig400") ) ;
       can->Update() ; can->Draw() ;

       if ( savePdf ) { can->SaveAs( pdffile ) ; }

   } // drawcanvas.

  //==========================================================================================

   void drawplot( TString hname ) {

      TH2F* hp = (TH2F*) gDirectory->FindObject( hname ) ;
      if ( hp == 0x0 ) { printf("\n\n\n *** missing hist: %s\n\n\n", hname.Data() ) ; return ; }

      int color = hp->GetFillColor() ;

      hp->UseCurrentStyle() ;
      hp->SetFillColor(color) ;
      hp->SetXTitle("Ave mass") ;
      hp->SetYTitle("Delta mass") ;

      hp->Draw("box") ;



      TBox* box = new TBox() ;
      box->SetFillStyle(0) ;
      box->DrawBox( 100., -20., 140., 20. ) ;
      box->DrawBox(  90., -30., 150., 30. ) ;

   } // drawplot.

  //==========================================================================================


  //==========================================================================================










