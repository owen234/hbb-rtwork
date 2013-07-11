
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


TH1F* shiftHist( TH1F* hin, float xshift ) ;

#include "histio.c"

   int  nsamples(4) ;
   int  nbgsamples(2) ;
   char samplename[4][100] = { "tt", "znn", "sig250", "sig400" } ;

   void bgratios3( const char* infile = "plots3.root" ) {

       gDirectory->Delete("h*") ;

       gStyle -> SetOptStat(0) ;
       gStyle -> SetPadGridY(1) ;
       gStyle -> SetOptTitle(0) ;
       gStyle -> SetTitleOffset(1.2,"y") ;
       gStyle -> SetTitleOffset(1.2,"x") ;
       gStyle -> SetPadLeftMargin(0.12) ;
       gStyle -> SetPadBottomMargin(0.12) ;

       TH1F* h_msig_4b[4] ;
       TH1F* h_msig_3b[4] ;
       TH1F* h_msig_2b[4] ;

       TH1F* h_msb_4b[4] ;
       TH1F* h_msb_3b[4] ;
       TH1F* h_msb_2b[4] ;

       loadHist( infile ) ;

     //--- load histogram arrays.

       for ( int si=0; si<nsamples; si++ ) {

          char hname[10000] ;

          sprintf( hname, "h_metsig_sigmass_cb_%s", samplename[si] ) ;
          h_msig_4b[si] = (TH1F*) gDirectory->FindObject( hname ) ;
          if ( h_msig_4b[si] == 0x0 ) { printf("\n\n\n *** missing 4b hist: %s\n\n", hname ) ; return ; }

          sprintf( hname, "h_metsig_sigmass_3b_cb_%s", samplename[si] ) ;
          h_msig_3b[si] = (TH1F*) gDirectory->FindObject( hname ) ;
          if ( h_msig_3b[si] == 0x0 ) { printf("\n\n\n *** missing 3b hist: %s\n\n", hname ) ; return ; }

          sprintf( hname, "h_metsig_sigmass_2b_cb_%s", samplename[si] ) ;
          h_msig_2b[si] = (TH1F*) gDirectory->FindObject( hname ) ;
          if ( h_msig_2b[si] == 0x0 ) { printf("\n\n\n *** missing 2b hist: %s\n\n", hname ) ; return ; }


          sprintf( hname, "h_metsig_sbmass_cb_%s", samplename[si] ) ;
          h_msb_4b[si] = (TH1F*) gDirectory->FindObject( hname ) ;
          if ( h_msb_4b[si] == 0x0 ) { printf("\n\n\n *** missing 4b hist: %s\n\n", hname ) ; return ; }

          sprintf( hname, "h_metsig_sbmass_3b_cb_%s", samplename[si] ) ;
          h_msb_3b[si] = (TH1F*) gDirectory->FindObject( hname ) ;
          if ( h_msb_3b[si] == 0x0 ) { printf("\n\n\n *** missing 3b hist: %s\n\n", hname ) ; return ; }

          sprintf( hname, "h_metsig_sbmass_2b_cb_%s", samplename[si] ) ;
          h_msb_2b[si] = (TH1F*) gDirectory->FindObject( hname ) ;
          if ( h_msb_2b[si] == 0x0 ) { printf("\n\n\n *** missing 2b hist: %s\n\n", hname ) ; return ; }


       } // si

       TH1F* h_msig_4b_bgsum(0x0) ;
       TH1F* h_msig_3b_bgsum(0x0) ;
       TH1F* h_msig_2b_bgsum(0x0) ;

       TH1F* h_msb_4b_bgsum(0x0) ;
       TH1F* h_msb_3b_bgsum(0x0) ;
       TH1F* h_msb_2b_bgsum(0x0) ;

       for ( int si=0; si<nbgsamples; si++ ) {

          if ( si==0 ) {
             h_msig_4b_bgsum = (TH1F*) h_msig_4b[si]->Clone( "h_metsig_sigmass_cb_bgsum" ) ;
             h_msig_3b_bgsum = (TH1F*) h_msig_3b[si]->Clone( "h_metsig_sigmass_3b_cb_bgsum" ) ;
             h_msig_2b_bgsum = (TH1F*) h_msig_2b[si]->Clone( "h_metsig_sigmass_2b_cb_bgsum" ) ;
             h_msb_4b_bgsum = (TH1F*) h_msb_4b[si]->Clone( "h_metsig_sbmass_cb_bgsum" ) ;
             h_msb_3b_bgsum = (TH1F*) h_msb_3b[si]->Clone( "h_metsig_sbmass_3b_cb_bgsum" ) ;
             h_msb_2b_bgsum = (TH1F*) h_msb_2b[si]->Clone( "h_metsig_sbmass_2b_cb_bgsum" ) ;
          } else {
             h_msig_4b_bgsum->Add( h_msig_4b[si] ) ;
             h_msig_3b_bgsum->Add( h_msig_3b[si] ) ;
             h_msig_2b_bgsum->Add( h_msig_2b[si] ) ;
             h_msb_4b_bgsum->Add( h_msb_4b[si] ) ;
             h_msb_3b_bgsum->Add( h_msb_3b[si] ) ;
             h_msb_2b_bgsum->Add( h_msb_2b[si] ) ;
          }

       }


       TH1F* h_sigsb_ratio_4b = (TH1F*) h_msig_4b_bgsum->Clone( "h_sigsb_ratio_4b" ) ;
       TH1F* h_sigsb_ratio_3b = (TH1F*) h_msig_3b_bgsum->Clone( "h_sigsb_ratio_3b" ) ;
       TH1F* h_sigsb_ratio_2b = (TH1F*) h_msig_2b_bgsum->Clone( "h_sigsb_ratio_2b" ) ;

       h_sigsb_ratio_4b -> Divide( h_msb_4b_bgsum ) ;
       h_sigsb_ratio_3b -> Divide( h_msb_3b_bgsum ) ;
       h_sigsb_ratio_2b -> Divide( h_msb_2b_bgsum ) ;

       TH1F* h_sigsb_ratio_4bs = shiftHist( h_sigsb_ratio_4b, 0.0 ) ;
       TH1F* h_sigsb_ratio_3bs = shiftHist( h_sigsb_ratio_3b, 0.5 ) ;
       TH1F* h_sigsb_ratio_2bs = shiftHist( h_sigsb_ratio_2b, 1.0 ) ;

       h_sigsb_ratio_4bs -> SetMarkerStyle( 20 ) ;
       h_sigsb_ratio_3bs -> SetMarkerStyle( 21 ) ;
       h_sigsb_ratio_2bs -> SetMarkerStyle( 22 ) ;

       h_sigsb_ratio_4bs -> SetLineColor(1) ;
       h_sigsb_ratio_3bs -> SetLineColor(2) ;
       h_sigsb_ratio_2bs -> SetLineColor(4) ;

       h_sigsb_ratio_4bs -> SetMarkerColor(1) ;
       h_sigsb_ratio_3bs -> SetMarkerColor(2) ;
       h_sigsb_ratio_2bs -> SetMarkerColor(4) ;

       h_sigsb_ratio_4bs -> SetLineWidth(2) ;
       h_sigsb_ratio_3bs -> SetLineWidth(2) ;
       h_sigsb_ratio_2bs -> SetLineWidth(2) ;

       TLegend* legend = new TLegend( 0.85, 0.70, 0.95, 0.95 ) ;
       legend->SetFillColor(kWhite) ;
       legend->AddEntry( h_sigsb_ratio_4bs, "4b" ) ;
       legend->AddEntry( h_sigsb_ratio_3bs, "3b" ) ;
       legend->AddEntry( h_sigsb_ratio_2bs, "2b" ) ;

       h_sigsb_ratio_4bs->SetXTitle("METsig") ;
       h_sigsb_ratio_4bs->SetYTitle("Mass SIG/SB ratio") ;

       TCanvas* cratio = new TCanvas( "cratio", " mass SIG/SB ratio", 800, 600 ) ;

       h_sigsb_ratio_4bs -> Draw() ;
       h_sigsb_ratio_3bs -> Draw("same") ;
       h_sigsb_ratio_2bs -> Draw("same") ;
       legend->Draw() ;

       cratio->SaveAs("outputfiles/mass-sigsb-ratios.pdf") ;

       printf("\n\n---------------------------------------------------------------\n") ;
       h_sigsb_ratio_4b->Print("all") ;
       printf("\n\n---------------------------------------------------------------\n") ;
       h_sigsb_ratio_3b->Print("all") ;
       printf("\n\n---------------------------------------------------------------\n") ;
       h_sigsb_ratio_2b->Print("all") ;
       printf("---------------------------------------------------------------\n\n\n") ;


   } // bgratios3

  //========================================================================================


   TH1F* shiftHist( TH1F* hin, float xshift ) {

      const TArrayD* xbins = hin -> GetXaxis() -> GetXbins() ;

      double shiftedxbins[500] ;
      for ( int bi=0; bi<=hin->GetNbinsX(); bi++ ) {
         shiftedxbins[bi] = xbins->At(bi) + xshift ;
      } // bi.

      TH1F* retval = new TH1F( hin->GetName() + TString("_shift"), hin->GetTitle(), hin->GetNbinsX(), shiftedxbins ) ;
      for ( int bi=1; bi<=hin->GetNbinsX(); bi++ ) {
         retval->SetBinContent( bi, hin->GetBinContent(bi) ) ;
         retval->SetBinError( bi, hin->GetBinError(bi) ) ;
      }

      return retval ;

   }

  //========================================================================================




