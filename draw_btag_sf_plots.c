
#include "TDirectory.h"
#include "TH3D.h"
#include "TH2F.h"
#include "TStyle.h"
#include "TCanvas.h"

#include "histio.c"

   char btag_catname[5][10] = { "NT", "", "2b", "3b", "4b" } ;

   void draw_btag_sf_plots( const char* infile = "outputfiles/btag-sf-plots-higgsino-mass-300.root", int higgsino_mass = 300 ) {

      gDirectory -> Delete("h*") ;
      gStyle -> SetOptStat(0) ;
      gStyle -> SetMarkerSize(2.0);

      loadHist( infile ) ;

      TH3D* h_msig_p1s = (TH3D*) gDirectory -> FindObject( "h_msig_p1s" ) ;
      TH3D* h_msb_p1s = (TH3D*) gDirectory -> FindObject( "h_msb_p1s" ) ;
      TH3D* h_msig_m1s = (TH3D*) gDirectory -> FindObject( "h_msig_m1s" ) ;
      TH3D* h_msb_m1s = (TH3D*) gDirectory -> FindObject( "h_msb_m1s" ) ;

      if ( h_msig_p1s == 0x0 ) { printf("\n\n\n *** Can't find h_msig_p1s in %s\n\n", infile ) ; return ; }

      TCanvas* can_tm_evts_msig_p1s = new TCanvas( "can_tm_evts_msig_p1s", "Transfer matrix, events, SIG, SF+1sigma", 1100, 300 ) ;
      can_tm_evts_msig_p1s -> Clear() ;
      can_tm_evts_msig_p1s -> Divide(4,1) ;

      TCanvas* can_tm_evts_msb_p1s = new TCanvas( "can_tm_evts_msb_p1s", "Transfer matrix, events, SB, SF+1sigma", 1100, 300 ) ;
      can_tm_evts_msb_p1s -> Clear() ;
      can_tm_evts_msb_p1s -> Divide(4,1) ;

      TCanvas* can_tm_evts_msig_m1s = new TCanvas( "can_tm_evts_msig_m1s", "Transfer matrix, events, SIG, SF-1sigma", 1100, 300 ) ;
      can_tm_evts_msig_m1s -> Clear() ;
      can_tm_evts_msig_m1s -> Divide(4,1) ;

      TCanvas* can_tm_evts_msb_m1s = new TCanvas( "can_tm_evts_msb_m1s", "Transfer matrix, events, SB, SF-1sigma", 1100, 300 ) ;
      can_tm_evts_msb_m1s -> Clear() ;
      can_tm_evts_msb_m1s -> Divide(4,1) ;

     //---

      TCanvas* can_tm_frac_msig_p1s = new TCanvas( "can_tm_frac_msig_p1s", "Transfer matrix, fractions, SIG, SF+1sigma", 1100, 300 ) ;
      can_tm_frac_msig_p1s -> Clear() ;
      can_tm_frac_msig_p1s -> Divide(4,1) ;

      TCanvas* can_tm_frac_msb_p1s = new TCanvas( "can_tm_frac_msb_p1s", "Transfer matrix, fractions, SB, SF+1sigma", 1100, 300 ) ;
      can_tm_frac_msb_p1s -> Clear() ;
      can_tm_frac_msb_p1s -> Divide(4,1) ;

      TCanvas* can_tm_frac_msig_m1s = new TCanvas( "can_tm_frac_msig_m1s", "Transfer matrix, fractions, SIG, SF-1sigma", 1100, 300 ) ;
      can_tm_frac_msig_m1s -> Clear() ;
      can_tm_frac_msig_m1s -> Divide(4,1) ;

      TCanvas* can_tm_frac_msb_m1s = new TCanvas( "can_tm_frac_msb_m1s", "Transfer matrix, fractions, SB, SF-1sigma", 1100, 300 ) ;
      can_tm_frac_msb_m1s -> Clear() ;
      can_tm_frac_msb_m1s -> Divide(4,1) ;



      for ( int mbi=1; mbi<=4; mbi++ ) {

         char hname[1000] ;
         char htitle[1000] ;

         float col_sum[5] ;

        //--- SIG, +1sigma

         sprintf( hname, "h_tm_evts_msig_p1s_met%d", mbi ) ;
         sprintf( htitle, "Transfer matrix, events, for +1 sigma, SIG, METsig bin %d", mbi ) ;

         TH2F* h_tm_evts_msig_p1s = new TH2F( hname, htitle,  5, -0.4, 4.5,  5, -0.5, 4.5 ) ;
         h_tm_evts_msig_p1s -> SetMinimum(0.000001) ;
         h_tm_evts_msig_p1s -> SetXTitle( "Nominal SF, tag category" ) ;
         h_tm_evts_msig_p1s -> SetYTitle( "SF+1 sigma, tag category" ) ;

         for ( int fbi=0; fbi<5; fbi++ ) {
            h_tm_evts_msig_p1s -> GetXaxis() -> SetBinLabel( fbi+1, btag_catname[fbi] ) ;
            for ( int tbi=0; tbi<5; tbi++ ) {
               h_tm_evts_msig_p1s -> GetYaxis() -> SetBinLabel( tbi+1, btag_catname[tbi] ) ;
               h_tm_evts_msig_p1s -> SetBinContent( fbi+1, tbi+1, h_msig_p1s -> GetBinContent( fbi+1, tbi+1, mbi ) ) ;
            } // tbi.
         } // fbi.

         can_tm_evts_msig_p1s -> cd( mbi ) ;
         gStyle -> SetPaintTextFormat(".0f") ;
         h_tm_evts_msig_p1s -> SetFillColor( kBlue-9 ) ;
         h_tm_evts_msig_p1s -> Draw("box") ;
         h_tm_evts_msig_p1s -> Draw("text same") ;
         can_tm_evts_msig_p1s -> ForceUpdate() ; can_tm_evts_msig_p1s -> Draw() ;
         gPad -> Update() ; gPad -> Draw() ; gPad -> Paint() ;

        //---

         sprintf( hname, "h_tm_frac_msig_p1s_met%d", mbi ) ;
         sprintf( htitle, "Transfer matrix, fractions, for +1 sigma, SIG, METsig bin %d", mbi ) ;

         TH2F* h_tm_frac_msig_p1s = new TH2F( hname, htitle,  5, -0.4, 4.5,  5, -0.5, 4.5 ) ;
         h_tm_frac_msig_p1s -> SetMinimum(0.000001) ;
         h_tm_frac_msig_p1s -> SetXTitle( "Nominal SF, tag category" ) ;
         h_tm_frac_msig_p1s -> SetYTitle( "SF+1 sigma, tag category" ) ;

         for ( int fbi=0; fbi<5; fbi++ ) {
            col_sum[fbi] = 0. ;
            for ( int tbi=0; tbi<5; tbi++ ) { col_sum[fbi] += h_tm_evts_msig_p1s -> GetBinContent( fbi+1, tbi+1 ) ; }
         }

         for ( int fbi=0; fbi<5; fbi++ ) {
            h_tm_frac_msig_p1s -> GetXaxis() -> SetBinLabel( fbi+1, btag_catname[fbi] ) ;
            for ( int tbi=0; tbi<5; tbi++ ) {
               h_tm_frac_msig_p1s -> GetYaxis() -> SetBinLabel( tbi+1, btag_catname[tbi] ) ;
               double val(0) ;
               if ( col_sum[fbi] > 0 ) { val = ( h_tm_evts_msig_p1s -> GetBinContent( fbi+1, tbi+1 ) ) / col_sum[fbi] ; }
               h_tm_frac_msig_p1s -> SetBinContent( fbi+1, tbi+1, val ) ;
            } // tbi.
         } // fbi.

         can_tm_frac_msig_p1s -> cd( mbi ) ;
         //gStyle -> SetPaintTextFormat(".3f") ;
         h_tm_frac_msig_p1s -> SetFillColor( kBlue-9 ) ;
         h_tm_frac_msig_p1s -> Draw("box") ;
         h_tm_frac_msig_p1s -> Draw("text same") ;
         can_tm_frac_msig_p1s -> ForceUpdate() ; can_tm_frac_msig_p1s -> Draw() ;
         gPad -> Update() ; gPad -> Draw() ; gPad -> Paint() ;





        //--- SB, +1sigma

         sprintf( hname, "h_tm_evts_msb_p1s_met%d", mbi ) ;
         sprintf( htitle, "Transfer matrix, events, for +1 sigma, SIG, METsig bin %d", mbi ) ;

         TH2F* h_tm_evts_msb_p1s = new TH2F( hname, htitle,  5, -0.4, 4.5,  5, -0.5, 4.5 ) ;
         h_tm_evts_msb_p1s -> SetMinimum(0.000001) ;
         h_tm_evts_msb_p1s -> SetXTitle( "Nominal SF, tag category" ) ;
         h_tm_evts_msb_p1s -> SetYTitle( "SF+1 sigma, tag category" ) ;

         for ( int fbi=0; fbi<5; fbi++ ) {
            h_tm_evts_msb_p1s -> GetXaxis() -> SetBinLabel( fbi+1, btag_catname[fbi] ) ;
            for ( int tbi=0; tbi<5; tbi++ ) {
               h_tm_evts_msb_p1s -> GetYaxis() -> SetBinLabel( tbi+1, btag_catname[tbi] ) ;
               h_tm_evts_msb_p1s -> SetBinContent( fbi+1, tbi+1, h_msb_p1s -> GetBinContent( fbi+1, tbi+1, mbi ) ) ;
            } // tbi.
         } // fbi.

         can_tm_evts_msb_p1s -> cd( mbi ) ;
         gStyle -> SetPaintTextFormat(".0f") ;
         h_tm_evts_msb_p1s -> SetFillColor( kBlue-9 ) ;
         h_tm_evts_msb_p1s -> Draw("box") ;
         h_tm_evts_msb_p1s -> Draw("text same") ;
         can_tm_evts_msb_p1s -> ForceUpdate() ; can_tm_evts_msig_p1s -> Draw() ;
         gPad -> Update() ; gPad -> Draw() ; gPad -> Paint() ;



        //---

         sprintf( hname, "h_tm_frac_msb_p1s_met%d", mbi ) ;
         sprintf( htitle, "Transfer matrix, fractions, for +1 sigma, SIG, METsig bin %d", mbi ) ;

         TH2F* h_tm_frac_msb_p1s = new TH2F( hname, htitle,  5, -0.4, 4.5,  5, -0.5, 4.5 ) ;
         h_tm_frac_msb_p1s -> SetMinimum(0.000001) ;
         h_tm_frac_msb_p1s -> SetXTitle( "Nominal SF, tag category" ) ;
         h_tm_frac_msb_p1s -> SetYTitle( "SF+1 sigma, tag category" ) ;

         for ( int fbi=0; fbi<5; fbi++ ) {
            col_sum[fbi] = 0. ;
            for ( int tbi=0; tbi<5; tbi++ ) { col_sum[fbi] += h_tm_evts_msb_p1s -> GetBinContent( fbi+1, tbi+1 ) ; }
         }

         for ( int fbi=0; fbi<5; fbi++ ) {
            h_tm_frac_msb_p1s -> GetXaxis() -> SetBinLabel( fbi+1, btag_catname[fbi] ) ;
            for ( int tbi=0; tbi<5; tbi++ ) {
               h_tm_frac_msb_p1s -> GetYaxis() -> SetBinLabel( tbi+1, btag_catname[tbi] ) ;
               double val(0) ;
               if ( col_sum[fbi] > 0 ) { val = ( h_tm_evts_msb_p1s -> GetBinContent( fbi+1, tbi+1 ) ) / col_sum[fbi] ; }
               h_tm_frac_msb_p1s -> SetBinContent( fbi+1, tbi+1, val ) ;
            } // tbi.
         } // fbi.

         can_tm_frac_msb_p1s -> cd( mbi ) ;
         gStyle -> SetPaintTextFormat(".3f") ;
         h_tm_frac_msb_p1s -> SetFillColor( kBlue-9 ) ;
         h_tm_frac_msb_p1s -> Draw("box") ;
         h_tm_frac_msb_p1s -> Draw("text same") ;
         can_tm_frac_msb_p1s -> ForceUpdate() ; can_tm_frac_msig_p1s -> Draw() ;
         gPad -> Update() ; gPad -> Draw() ; gPad -> Paint() ;






        //--- SIG, -1sigma

         sprintf( hname, "h_tm_evts_msig_m1s_met%d", mbi ) ;
         sprintf( htitle, "Transfer matrix, events, for -1 sigma, SIG, METsig bin %d", mbi ) ;

         TH2F* h_tm_evts_msig_m1s = new TH2F( hname, htitle,  5, -0.4, 4.5,  5, -0.5, 4.5 ) ;
         h_tm_evts_msig_m1s -> SetMinimum(0.000001) ;
         h_tm_evts_msig_m1s -> SetXTitle( "Nominal SF, tag category" ) ;
         h_tm_evts_msig_m1s -> SetYTitle( "SF-1 sigma, tag category" ) ;

         for ( int fbi=0; fbi<5; fbi++ ) {
            h_tm_evts_msig_m1s -> GetXaxis() -> SetBinLabel( fbi+1, btag_catname[fbi] ) ;
            for ( int tbi=0; tbi<5; tbi++ ) {
               h_tm_evts_msig_m1s -> GetYaxis() -> SetBinLabel( tbi+1, btag_catname[tbi] ) ;
               h_tm_evts_msig_m1s -> SetBinContent( fbi+1, tbi+1, h_msig_m1s -> GetBinContent( fbi+1, tbi+1, mbi ) ) ;
            } // tbi.
         } // fbi.

         can_tm_evts_msig_m1s -> cd( mbi ) ;
         gStyle -> SetPaintTextFormat(".0f") ;
         h_tm_evts_msig_m1s -> SetFillColor( kRed-9 ) ;
         h_tm_evts_msig_m1s -> Draw("box") ;
         h_tm_evts_msig_m1s -> Draw("text same") ;
         can_tm_evts_msig_m1s -> ForceUpdate() ; can_tm_evts_msig_m1s -> Draw() ;
         gPad -> Update() ; gPad -> Draw() ; gPad -> Paint() ;

        //---

         sprintf( hname, "h_tm_frac_msig_m1s_met%d", mbi ) ;
         sprintf( htitle, "Transfer matrix, fractions, for -1 sigma, SIG, METsig bin %d", mbi ) ;

         TH2F* h_tm_frac_msig_m1s = new TH2F( hname, htitle,  5, -0.4, 4.5,  5, -0.5, 4.5 ) ;
         h_tm_frac_msig_m1s -> SetMinimum(0.000001) ;
         h_tm_frac_msig_m1s -> SetXTitle( "Nominal SF, tag category" ) ;
         h_tm_frac_msig_m1s -> SetYTitle( "SF-1 sigma, tag category" ) ;

         for ( int fbi=0; fbi<5; fbi++ ) {
            col_sum[fbi] = 0. ;
            for ( int tbi=0; tbi<5; tbi++ ) { col_sum[fbi] += h_tm_evts_msig_m1s -> GetBinContent( fbi+1, tbi+1 ) ; }
         }

         for ( int fbi=0; fbi<5; fbi++ ) {
            h_tm_frac_msig_m1s -> GetXaxis() -> SetBinLabel( fbi+1, btag_catname[fbi] ) ;
            for ( int tbi=0; tbi<5; tbi++ ) {
               h_tm_frac_msig_m1s -> GetYaxis() -> SetBinLabel( tbi+1, btag_catname[tbi] ) ;
               double val(0) ;
               if ( col_sum[fbi] > 0 ) { val = ( h_tm_evts_msig_m1s -> GetBinContent( fbi+1, tbi+1 ) ) / col_sum[fbi] ; }
               h_tm_frac_msig_m1s -> SetBinContent( fbi+1, tbi+1, val ) ;
            } // tbi.
         } // fbi.

         can_tm_frac_msig_m1s -> cd( mbi ) ;
         gStyle -> SetPaintTextFormat(".3f") ;
         h_tm_frac_msig_m1s -> SetFillColor( kRed-9 ) ;
         h_tm_frac_msig_m1s -> Draw("box") ;
         h_tm_frac_msig_m1s -> Draw("text same") ;
         can_tm_frac_msig_m1s -> ForceUpdate() ; can_tm_frac_msig_m1s -> Draw() ;
         gPad -> Update() ; gPad -> Draw() ; gPad -> Paint() ;




        //--- SB, -1sigma

         sprintf( hname, "h_tm_evts_msb_m1s_met%d", mbi ) ;
         sprintf( htitle, "Transfer matrix, events, for -1 sigma, SIG, METsig bin %d", mbi ) ;

         TH2F* h_tm_evts_msb_m1s = new TH2F( hname, htitle,  5, -0.4, 4.5,  5, -0.5, 4.5 ) ;
         h_tm_evts_msb_m1s -> SetMinimum(0.000001) ;
         h_tm_evts_msb_m1s -> SetXTitle( "Nominal SF, tag category" ) ;
         h_tm_evts_msb_m1s -> SetYTitle( "SF-1 sigma, tag category" ) ;

         for ( int fbi=0; fbi<5; fbi++ ) {
            h_tm_evts_msb_m1s -> GetXaxis() -> SetBinLabel( fbi+1, btag_catname[fbi] ) ;
            for ( int tbi=0; tbi<5; tbi++ ) {
               h_tm_evts_msb_m1s -> GetYaxis() -> SetBinLabel( tbi+1, btag_catname[tbi] ) ;
               h_tm_evts_msb_m1s -> SetBinContent( fbi+1, tbi+1, h_msb_m1s -> GetBinContent( fbi+1, tbi+1, mbi ) ) ;
            } // tbi.
         } // fbi.

         can_tm_evts_msb_m1s -> cd( mbi ) ;
         gStyle -> SetPaintTextFormat(".0f") ;
         h_tm_evts_msb_m1s -> SetFillColor( kRed-9 ) ;
         h_tm_evts_msb_m1s -> Draw("box") ;
         h_tm_evts_msb_m1s -> Draw("text same") ;
         can_tm_evts_msb_m1s -> ForceUpdate() ; can_tm_evts_msig_m1s -> Draw() ;
         gPad -> Update() ; gPad -> Draw() ; gPad -> Paint() ;


        //---

         sprintf( hname, "h_tm_frac_msb_m1s_met%d", mbi ) ;
         sprintf( htitle, "Transfer matrix, fractions, for -1 sigma, SIG, METsig bin %d", mbi ) ;

         TH2F* h_tm_frac_msb_m1s = new TH2F( hname, htitle,  5, -0.4, 4.5,  5, -0.5, 4.5 ) ;
         h_tm_frac_msb_m1s -> SetMinimum(0.000001) ;
         h_tm_frac_msb_m1s -> SetXTitle( "Nominal SF, tag category" ) ;
         h_tm_frac_msb_m1s -> SetYTitle( "SF-1 sigma, tag category" ) ;

         for ( int fbi=0; fbi<5; fbi++ ) {
            col_sum[fbi] = 0. ;
            for ( int tbi=0; tbi<5; tbi++ ) { col_sum[fbi] += h_tm_evts_msb_m1s -> GetBinContent( fbi+1, tbi+1 ) ; }
         }

         for ( int fbi=0; fbi<5; fbi++ ) {
            h_tm_frac_msb_m1s -> GetXaxis() -> SetBinLabel( fbi+1, btag_catname[fbi] ) ;
            for ( int tbi=0; tbi<5; tbi++ ) {
               h_tm_frac_msb_m1s -> GetYaxis() -> SetBinLabel( tbi+1, btag_catname[tbi] ) ;
               double val(0) ;
               if ( col_sum[fbi] > 0 ) { val = ( h_tm_evts_msb_m1s -> GetBinContent( fbi+1, tbi+1 ) ) / col_sum[fbi] ; }
               h_tm_frac_msb_m1s -> SetBinContent( fbi+1, tbi+1, val ) ;
            } // tbi.
         } // fbi.

         can_tm_frac_msb_m1s -> cd( mbi ) ;
         gStyle -> SetPaintTextFormat(".3f") ;
         h_tm_frac_msb_m1s -> SetFillColor( kRed-9 ) ;
         h_tm_frac_msb_m1s -> Draw("box") ;
         h_tm_frac_msb_m1s -> Draw("text same") ;
         can_tm_frac_msb_m1s -> ForceUpdate() ; can_tm_frac_msig_m1s -> Draw() ;
         gPad -> Update() ; gPad -> Draw() ; gPad -> Paint() ;



      } // mbi

      char outpdf[10000] ;

      gStyle -> SetPaintTextFormat(".0f") ;

      sprintf( outpdf, "outputfiles/btag-sf-transfer-matrix-evts-SIG-p1s-higgsino-mass-%d.pdf", higgsino_mass ) ;
      can_tm_evts_msig_p1s -> SaveAs( outpdf ) ;

      sprintf( outpdf, "outputfiles/btag-sf-transfer-matrix-evts-SB-p1s-higgsino-mass-%d.pdf", higgsino_mass ) ;
      can_tm_evts_msb_p1s -> SaveAs( outpdf ) ;


      sprintf( outpdf, "outputfiles/btag-sf-transfer-matrix-evts-SIG-m1s-higgsino-mass-%d.pdf", higgsino_mass ) ;
      can_tm_evts_msig_m1s -> SaveAs( outpdf ) ;

      sprintf( outpdf, "outputfiles/btag-sf-transfer-matrix-evts-SB-m1s-higgsino-mass-%d.pdf", higgsino_mass ) ;
      can_tm_evts_msb_m1s -> SaveAs( outpdf ) ;

     //---

      gStyle -> SetPaintTextFormat(".3f") ;

      sprintf( outpdf, "outputfiles/btag-sf-transfer-matrix-frac-SIG-p1s-higgsino-mass-%d.pdf", higgsino_mass ) ;
      can_tm_frac_msig_p1s -> SaveAs( outpdf ) ;

      sprintf( outpdf, "outputfiles/btag-sf-transfer-matrix-frac-SB-p1s-higgsino-mass-%d.pdf", higgsino_mass ) ;
      can_tm_frac_msb_p1s -> SaveAs( outpdf ) ;


      sprintf( outpdf, "outputfiles/btag-sf-transfer-matrix-frac-SIG-m1s-higgsino-mass-%d.pdf", higgsino_mass ) ;
      can_tm_frac_msig_m1s -> SaveAs( outpdf ) ;

      sprintf( outpdf, "outputfiles/btag-sf-transfer-matrix-frac-SB-m1s-higgsino-mass-%d.pdf", higgsino_mass ) ;
      can_tm_frac_msb_m1s -> SaveAs( outpdf ) ;



   } // draw_btag_sf_plots

