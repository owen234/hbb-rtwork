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
#include "TLine.h"

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

   void drawcanvas( const char* hnamebase, const char* canname, const char* cantitle, bool proj_am, int comp_ind=-1 ) ;
   void drawplot4b( TString hname, bool proj_am, const char* subtitle="", int comp_ind=-1 ) ;
   void drawplotnb( TString hnamenb, TString hname4b, bool proj_am, const char* subtitle="", int comp_ind=-1 ) ;

  //==========================================================================================

   void drawplots3bam( bool arg_savePdf = true, const char* infile = "plots3b.root", bool arg_recycleCanvas=false ) {


       gStyle->SetStatW(0.30) ;
       gStyle->SetStatH(0.25) ;
       gStyle->SetOptStat("mri") ;

       recycleCanvas = arg_recycleCanvas ;
       savePdf = arg_savePdf ;

       gDirectory->Delete("h*") ;

       loadHist( infile ) ;

       gStyle -> SetTitleH(0.070 ) ;

       drawcanvas( "h_dmvsam_4b_metsig", "c_avem_allbg", "Average mass, all BG", true, -1 ) ;
       drawcanvas( "h_dmvsam_4b_metsig", "c_deltam_allbg", "Delta mass, all BG", false, -1 ) ;

       drawcanvas( "h_dmvsam_4b_metsig", "c_avem_tt", "Average mass, tt", true, 0 ) ;
       drawcanvas( "h_dmvsam_4b_metsig", "c_deltam_tt", "Delta mass, tt", false, 0 ) ;

       drawcanvas( "h_dmvsam_4b_metsig", "c_avem_znn", "Average mass, znn", true, 1 ) ;
       drawcanvas( "h_dmvsam_4b_metsig", "c_deltam_znn", "Delta mass, znn", false, 1 ) ;

       drawcanvas( "h_dmvsam_4b_metsig", "c_avem_sig250", "Average mass, sig250", true, 2 ) ;
       drawcanvas( "h_dmvsam_4b_metsig", "c_deltam_sig250", "Delta mass, sig250", false, 2 ) ;

       drawcanvas( "h_dmvsam_4b_metsig", "c_avem_sig400", "Average mass, sig400", true, 3 ) ;
       drawcanvas( "h_dmvsam_4b_metsig", "c_deltam_sig400", "Delta mass, sig400", false, 3 ) ;

   } // drawplots3bam.

  //==========================================================================================

   void drawcanvas( const char* hnamebase, const char* canname, const char* cantitle, bool proj_am, int comp_ind ) {

       TCanvas* can = new TCanvas( canname, cantitle, 900, 1000 ) ;

       can->Divide(3,5) ;

       TString hnamebasets( hnamebase ) ;
       TString hnamebase4b = hnamebasets ;
       TString hnamebase3b = hnamebasets ;
       TString hnamebase2b = hnamebasets ;

       hnamebase3b.ReplaceAll("4b","3b") ;
       hnamebase2b.ReplaceAll("4b","2b") ;


       TString metsigstr("30") ;

       can->cd(1) ;
       drawplot4b( hnamebase4b + metsigstr, proj_am, "4b, METsig>30", comp_ind ) ;
       can->Update() ; can->Draw() ;

       can->cd(2) ;
       drawplotnb( hnamebase3b + metsigstr, hnamebase4b + metsigstr, proj_am, "3b, METsig>30", comp_ind ) ;
       can->Update() ; can->Draw() ;

       can->cd(3) ;
       drawplotnb( hnamebase2b + metsigstr, hnamebase4b + metsigstr, proj_am, "2b, METsig>30", comp_ind ) ;
       can->Update() ; can->Draw() ;


       metsigstr = TString("30_50") ;
       can->cd(4) ;
       drawplot4b( hnamebase4b + metsigstr, proj_am, "4b, METsig [30,50]", comp_ind ) ;
       can->Update() ; can->Draw() ;

       can->cd(5) ;
       drawplotnb( hnamebase3b + metsigstr, hnamebase4b + metsigstr, proj_am, "3b, METsig [30,50]", comp_ind ) ;
       can->Update() ; can->Draw() ;

       can->cd(6) ;
       drawplotnb( hnamebase2b + metsigstr, hnamebase4b + metsigstr, proj_am, "2b, METsig [30,50]", comp_ind ) ;
       can->Update() ; can->Draw() ;


       metsigstr = TString("50_100") ;
       can->cd(7) ;
       drawplot4b( hnamebase4b + metsigstr, proj_am, "4b, METsig [50,100]", comp_ind ) ;
       can->Update() ; can->Draw() ;

       can->cd(8) ;
       drawplotnb( hnamebase3b + metsigstr, hnamebase4b + metsigstr, proj_am, "3b, METsig [50,100]", comp_ind ) ;
       can->Update() ; can->Draw() ;

       can->cd(9) ;
       drawplotnb( hnamebase2b + metsigstr, hnamebase4b + metsigstr, proj_am, "2b, METsig [50,100]", comp_ind ) ;
       can->Update() ; can->Draw() ;


       metsigstr = TString("100_150") ;
       can->cd(10) ;
       drawplot4b( hnamebase4b + metsigstr, proj_am, "4b, METsig [100,150]", comp_ind ) ;
       can->Update() ; can->Draw() ;

       can->cd(11) ;
       drawplotnb( hnamebase3b + metsigstr, hnamebase4b + metsigstr, proj_am, "3b, METsig [100,150]", comp_ind ) ;
       can->Update() ; can->Draw() ;

       can->cd(12) ;
       drawplotnb( hnamebase2b + metsigstr, hnamebase4b + metsigstr, proj_am, "2b, METsig [100,150]", comp_ind ) ;
       can->Update() ; can->Draw() ;


       metsigstr = TString("150") ;
       can->cd(13) ;
       drawplot4b( hnamebase4b + metsigstr, proj_am, "4b, METsig>150", comp_ind ) ;
       can->Update() ; can->Draw() ;

       can->cd(14) ;
       drawplotnb( hnamebase3b + metsigstr, hnamebase4b + metsigstr, proj_am, "3b, METsig>150", comp_ind ) ;
       can->Update() ; can->Draw() ;

       can->cd(15) ;
       drawplotnb( hnamebase2b + metsigstr, hnamebase4b + metsigstr, proj_am, "2b, METsig>150", comp_ind ) ;
       can->Update() ; can->Draw() ;

       if ( savePdf ) {
          if ( proj_am ) {
             if ( comp_ind  < 0 ) can->SaveAs( "outputfiles/background-avem-projections_allbg.pdf" ) ;
             if ( comp_ind == 0 ) can->SaveAs( "outputfiles/background-avem-projections_tt.pdf" ) ;
             if ( comp_ind == 1 ) can->SaveAs( "outputfiles/background-avem-projections_znn.pdf" ) ;
             if ( comp_ind == 2 ) can->SaveAs( "outputfiles/signal-avem-projections_sig250.pdf" ) ;
             if ( comp_ind == 3 ) can->SaveAs( "outputfiles/signal-avem-projections_sig400.pdf" ) ;
          } else {
             if ( comp_ind  < 0 ) can->SaveAs( "outputfiles/background-deltam-projections_allbg.pdf" ) ;
             if ( comp_ind == 0 ) can->SaveAs( "outputfiles/background-deltam-projections_tt.pdf" ) ;
             if ( comp_ind == 1 ) can->SaveAs( "outputfiles/background-deltam-projections_znn.pdf" ) ;
             if ( comp_ind == 2 ) can->SaveAs( "outputfiles/signal-deltam-projections_sig250.pdf" ) ;
             if ( comp_ind == 3 ) can->SaveAs( "outputfiles/signal-deltam-projections_sig400.pdf" ) ;
          }
       }


   } // drawcanvas.

  //==========================================================================================

   void drawplot4b( TString hname, bool proj_am, const char* subtitle, int comp_ind ) {

      TH2F* hptt = (TH2F*) gDirectory->FindObject( hname + TString("_tt") ) ;
      if ( hptt == 0x0 ) { printf("\n\n\n *** missing tt hist: %s\n\n\n", hname.Data()  ) ; return ; }

      TH2F* hpznn = (TH2F*) gDirectory->FindObject( hname + TString("_znn") ) ;
      if ( hpznn == 0x0 ) { printf("\n\n\n *** missing znn hist: %s\n\n\n", hname.Data() ) ; return ; }

      TH2F* hpsig250 = (TH2F*) gDirectory->FindObject( hname + TString("_sig250") ) ;
      if ( hpsig250 == 0x0 ) { printf("\n\n\n *** missing sig250 hist: %s\n\n\n", hname.Data() ) ; return ; }

      TH2F* hpsig400 = (TH2F*) gDirectory->FindObject( hname + TString("_sig400") ) ;
      if ( hpsig400 == 0x0 ) { printf("\n\n\n *** missing sig400 hist: %s\n\n\n", hname.Data() ) ; return ; }

      TH2F* hpallbg = (TH2F*) hptt->Clone( hname + TString("_allbg") ) ;
      hpallbg->Add( hpznn ) ;

      TH1D* hp(0x0) ;
      THStack* hstackp(0x0) ;

      char title[1000] ;

      if ( proj_am ) {
         if ( comp_ind < 0 ) {
            TH1D* hpptt  = hptt->ProjectionX( hname + TString("_tt_proj_am") ) ;
            TH1D* hppznn = hpznn->ProjectionX( hname + TString("_znn_proj_am") ) ;
            hstackp = new THStack() ;
            hstackp->Add( hppznn ) ;
            hstackp->Add( hpptt ) ;
            hp = hpallbg->ProjectionX( hname + TString("_allbg_proj_am") ) ;
         } else if ( comp_ind == 0 ) {
            hp = hptt->ProjectionX( hname + TString("_tt_proj_am") ) ;
         } else if ( comp_ind == 1 ) {
            hp = hpznn->ProjectionX( hname + TString("_znn_proj_am") ) ;
         } else if ( comp_ind == 2 ) {
            hp = hpsig250->ProjectionX( hname + TString("_sig250_proj_am") ) ;
         } else if ( comp_ind == 3 ) {
            hp = hpsig400->ProjectionX( hname + TString("_sig400_proj_am") ) ;
         }
         sprintf( title, "Ave. mass, %s", subtitle ) ;
         hp->SetTitle( title ) ;
      } else {
         if ( comp_ind < 0 ) {
            TH1D* hpptt  = hptt->ProjectionY( hname + TString("_tt_proj_dm") ) ;
            TH1D* hppznn = hpznn->ProjectionY( hname + TString("_znn_proj_dm") ) ;
            hstackp = new THStack() ;
            hstackp->Add( hppznn ) ;
            hstackp->Add( hpptt ) ;
            hp = hpallbg->ProjectionY( hname + TString("_allbg_proj_dm") ) ;
         } else if ( comp_ind == 0 ) {
            hp = hptt->ProjectionY( hname + TString("_tt_proj_dm") ) ;
         } else if ( comp_ind == 1 ) {
            hp = hpznn->ProjectionY( hname + TString("_znn_proj_dm") ) ;
         } else if ( comp_ind == 2 ) {
            hp = hpsig250->ProjectionY( hname + TString("_sig250_proj_dm") ) ;
         } else if ( comp_ind == 3 ) {
            hp = hpsig400->ProjectionY( hname + TString("_sig400_proj_dm") ) ;
         }
         sprintf( title, "Delta mass, %s", subtitle ) ;
         hp->SetTitle( title ) ;
      }

      gStyle->SetOptStat("mri") ;


      hp->Draw("hist") ;
      if ( comp_ind < 0 ) { hstackp->Draw("hist same") ; }
      hp->Draw("e same") ;

      TLine* line = new TLine() ;

      hp->SetMaximum( 1.15*(hp->GetMaximum()) ) ;

      if ( proj_am ) {
         line->SetLineStyle(1) ;
         line->DrawLine( 100., 0., 100., 1.00*(hp->GetMaximum()) ) ;
         line->DrawLine( 140., 0., 140., 1.00*(hp->GetMaximum()) ) ;
         line->SetLineStyle(2) ;
         line->DrawLine(  90., 0.,  90., 1.00*(hp->GetMaximum()) ) ;
         line->DrawLine( 150., 0., 150., 1.00*(hp->GetMaximum()) ) ;
      } else {
         line->SetLineStyle(1) ;
         line->DrawLine( -20., 0., -20., 1.00*(hp->GetMaximum()) ) ;
         line->DrawLine(  20., 0.,  20., 1.00*(hp->GetMaximum()) ) ;
         line->SetLineStyle(2) ;
         line->DrawLine( -30., 0., -30., 1.00*(hp->GetMaximum()) ) ;
         line->DrawLine(  30., 0.,  30., 1.00*(hp->GetMaximum()) ) ;
      }


   } // drawplot.

  //==========================================================================================

   void drawplotnb( TString hnamenb, TString hname4b, bool proj_am, const char* subtitle, int comp_ind ) {

      TH2F* hptt = (TH2F*) gDirectory->FindObject( hnamenb + TString("_tt") ) ;
      if ( hptt == 0x0 ) { printf("\n\n\n *** missing tt hist: %s\n\n\n", hnamenb.Data()  ) ; return ; }

      TH2F* hpznn = (TH2F*) gDirectory->FindObject( hnamenb + TString("_znn") ) ;
      if ( hpznn == 0x0 ) { printf("\n\n\n *** missing znn hist: %s\n\n\n", hnamenb.Data() ) ; return ; }

      TH2F* hpsig250 = (TH2F*) gDirectory->FindObject( hnamenb + TString("_sig250") ) ;
      if ( hpsig250 == 0x0 ) { printf("\n\n\n *** missing sig250 hist: %s\n\n\n", hnamenb.Data() ) ; return ; }

      TH2F* hpsig400 = (TH2F*) gDirectory->FindObject( hnamenb + TString("_sig400") ) ;
      if ( hpsig400 == 0x0 ) { printf("\n\n\n *** missing sig400 hist: %s\n\n\n", hnamenb.Data() ) ; return ; }

      TH2F* hpallbg = (TH2F*) hptt->Clone( hnamenb + TString("_allbg") ) ;
      hpallbg->Add( hpznn ) ;

      TH1D* hp(0x0) ;
      TH1D* hp4b(0x0) ;
      THStack* hstackp(0x0) ;

      char title[1000] ;

      if ( proj_am ) {
         if ( comp_ind < 0 ) {
            TH1D* hpptt  = hptt->ProjectionX( hnamenb + TString("_tt_proj_am") ) ;
            TH1D* hppznn = hpznn->ProjectionX( hnamenb + TString("_znn_proj_am") ) ;
            hstackp = new THStack() ;
            hstackp->Add( hppznn ) ;
            hstackp->Add( hpptt ) ;
            hp = hpallbg->ProjectionX( hnamenb + TString("_allbg_proj_am") ) ;
            hp4b = (TH1D*) gDirectory->FindObject( hname4b + TString("_allbg_proj_am") ) ;
         } else if ( comp_ind == 0 ) {
            hp = hptt->ProjectionX( hnamenb + TString("_tt_proj_am") ) ;
            hp4b = (TH1D*) gDirectory->FindObject( hname4b + TString("_tt_proj_am") ) ;
         } else if ( comp_ind == 1 ) {
            hp = hpznn->ProjectionX( hnamenb + TString("_znn_proj_am") ) ;
            hp4b = (TH1D*) gDirectory->FindObject( hname4b + TString("_znn_proj_am") ) ;
         } else if ( comp_ind == 2 ) {
            hp = hpsig250->ProjectionX( hnamenb + TString("_sig250_proj_am") ) ;
            hp4b = (TH1D*) gDirectory->FindObject( hname4b + TString("_sig250_proj_am") ) ;
         } else if ( comp_ind == 3 ) {
            hp = hpsig400->ProjectionX( hnamenb + TString("_sig400_proj_am") ) ;
            hp4b = (TH1D*) gDirectory->FindObject( hname4b + TString("_sig400_proj_am") ) ;
         }
         sprintf( title, "Ave. mass, %s", subtitle ) ;
         hp -> SetTitle( title ) ;
      } else {
         if ( comp_ind < 0 ) {
            TH1D* hpptt  = hptt->ProjectionY( hnamenb + TString("_tt_proj_dm") ) ;
            TH1D* hppznn = hpznn->ProjectionY( hnamenb + TString("_znn_proj_dm") ) ;
            hstackp = new THStack() ;
            hstackp->Add( hppznn ) ;
            hstackp->Add( hpptt ) ;
            hp = hpallbg->ProjectionY( hnamenb + TString("_allbg_proj_dm") ) ;
            hp4b = (TH1D*) gDirectory->FindObject( hname4b + TString("_allbg_proj_dm") ) ;
         } else if ( comp_ind == 0 ) {
            hp = hptt->ProjectionY( hnamenb + TString("_tt_proj_dm") ) ;
            hp4b = (TH1D*) gDirectory->FindObject( hname4b + TString("_tt_proj_dm") ) ;
         } else if ( comp_ind == 1 ) {
            hp = hpznn->ProjectionY( hnamenb + TString("_znn_proj_dm") ) ;
            hp4b = (TH1D*) gDirectory->FindObject( hname4b + TString("_znn_proj_dm") ) ;
         } else if ( comp_ind == 2 ) {
            hp = hpsig250->ProjectionY( hnamenb + TString("_sig250_proj_dm") ) ;
            hp4b = (TH1D*) gDirectory->FindObject( hname4b + TString("_sig250_proj_dm") ) ;
         } else if ( comp_ind == 3 ) {
            hp = hpsig400->ProjectionY( hnamenb + TString("_sig400_proj_dm") ) ;
            hp4b = (TH1D*) gDirectory->FindObject( hname4b + TString("_sig400_proj_dm") ) ;
         }
         sprintf( title, "Delta mass, %s", subtitle ) ;
         hp -> SetTitle( title ) ;
      }
      if ( hp4b == 0x0 ) { printf("\n\n\n *** missing 4b hist.\n\n") ; return ; }

      gStyle->SetOptStat("mri") ;

      hp->Draw("hist") ;
      if ( comp_ind < 0 ) { hstackp->Draw("hist same") ; }
      hp->Draw("e same") ;

      TLine* line = new TLine() ;

      hp->SetMaximum( 1.15*(hp->GetMaximum()) ) ;

      if ( proj_am ) {
         line->SetLineStyle(1) ;
         line->DrawLine( 100., 0., 100., 1.00*(hp->GetMaximum()) ) ;
         line->DrawLine( 140., 0., 140., 1.00*(hp->GetMaximum()) ) ;
         line->SetLineStyle(2) ;
         line->DrawLine(  90., 0.,  90., 1.00*(hp->GetMaximum()) ) ;
         line->DrawLine( 150., 0., 150., 1.00*(hp->GetMaximum()) ) ;
      } else {
         line->SetLineStyle(1) ;
         line->DrawLine( -20., 0., -20., 1.00*(hp->GetMaximum()) ) ;
         line->DrawLine(  20., 0.,  20., 1.00*(hp->GetMaximum()) ) ;
         line->SetLineStyle(2) ;
         line->DrawLine( -30., 0., -30., 1.00*(hp->GetMaximum()) ) ;
         line->DrawLine(  30., 0.,  30., 1.00*(hp->GetMaximum()) ) ;
      }

      TH1D* hp4bcopy = (TH1D*) hp4b->Clone( hp4b->GetName() + TString("_copy") ) ;
      hp4bcopy->SetNormFactor( hp->Integral() ) ;
      hp4bcopy->SetFillStyle(0) ;
      hp4bcopy->SetLineWidth(2) ;
      hp4bcopy->Draw("hist same") ;


   } // drawplot.

  //==========================================================================================










