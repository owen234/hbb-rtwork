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

#include "histio.c"

#include <iostream>

   bool recycleCanvas(false) ;

 //--------------------
   int  nsamples(3) ;
   int  nbgsamples(3) ;
   char samplename[3][100] = { "znn", "ttsl", "qcd" } ;
 //--------------------

   bool savePdf ;
   char inrootfile[10000] ;

   void drawSet( const char* hname_base, const char* xtitle ) ;


  //==========================================================================================

   void draw_closure1( const char* histnamepat = "", bool arg_savePdf = true, const char* infile = "outputfiles/plots_closure1.root", bool arg_recycleCanvas=false ) {

       recycleCanvas = arg_recycleCanvas ;
       savePdf = arg_savePdf ;


       gDirectory->Delete("h*") ;

       gStyle -> SetOptStat(0) ;
       gStyle -> SetTitleH(0.035 ) ;

       char histnamelist[500][100] ;
       char histxtitlelist[500][100] ;

       int hind(0) ;

       sprintf( histnamelist[hind], "h_metsig_2b" ) ; sprintf( histxtitlelist[hind], "METsig" ) ; hind++ ;
       sprintf( histnamelist[hind], "h_metsig_3b" ) ; sprintf( histxtitlelist[hind], "METsig" ) ; hind++ ;
       sprintf( histnamelist[hind], "h_metsig_4b" ) ; sprintf( histxtitlelist[hind], "METsig" ) ; hind++ ;

       sprintf( histnamelist[hind], "h_mindphi30_ms05_2b" ) ; sprintf( histxtitlelist[hind], "minDeltaPhi30" ) ; hind++ ;
       sprintf( histnamelist[hind], "h_mindphi30_ms05_3b" ) ; sprintf( histxtitlelist[hind], "minDeltaPhi30" ) ; hind++ ;
       sprintf( histnamelist[hind], "h_mindphi30_ms05_4b" ) ; sprintf( histxtitlelist[hind], "minDeltaPhi30" ) ; hind++ ;

       sprintf( histnamelist[hind], "h_mindphi30_ms15_2b" ) ; sprintf( histxtitlelist[hind], "minDeltaPhi30" ) ; hind++ ;
       sprintf( histnamelist[hind], "h_mindphi30_ms15_3b" ) ; sprintf( histxtitlelist[hind], "minDeltaPhi30" ) ; hind++ ;
       sprintf( histnamelist[hind], "h_mindphi30_ms15_4b" ) ; sprintf( histxtitlelist[hind], "minDeltaPhi30" ) ; hind++ ;

       sprintf( histnamelist[hind], "h_mindphi30_ms25_2b" ) ; sprintf( histxtitlelist[hind], "minDeltaPhi30" ) ; hind++ ;
       sprintf( histnamelist[hind], "h_mindphi30_ms25_3b" ) ; sprintf( histxtitlelist[hind], "minDeltaPhi30" ) ; hind++ ;
       sprintf( histnamelist[hind], "h_mindphi30_ms25_4b" ) ; sprintf( histxtitlelist[hind], "minDeltaPhi30" ) ; hind++ ;


       int nhistlist = hind ;

       loadHist( infile ) ;

     //--- log y scale.
       printf("\n\n Log scale plots.\n\n") ;

       gStyle->SetOptLogy(1) ;

       for ( int hi=0; hi<nhistlist; hi++ ) {
          if ( strlen(histnamepat) > 0 ) {
             TString str( histnamelist[hi] ) ;
             if ( str.Contains( histnamepat ) ) {
                drawSet( histnamelist[hi], histxtitlelist[hi] ) ;
             }
          } else {
             drawSet( histnamelist[hi], histxtitlelist[hi] ) ;
          }
       }


     //--- linear y scale.
       printf("\n\n Linear scale plots.\n\n") ;

       gStyle->SetOptLogy(0) ;

       for ( int hi=0; hi<nhistlist; hi++ ) {
          if ( strlen(histnamepat) > 0 ) {
             TString str( histnamelist[hi] ) ;
             if ( str.Contains( histnamepat ) ) {
                drawSet( histnamelist[hi], histxtitlelist[hi] ) ;
             }
          } else {
             drawSet( histnamelist[hi], histxtitlelist[hi] ) ;
          }
       }




   } // draw_closure1

  //==========================================================================================

   void drawSet( const char* hname_base, const char* xtitle ) {

      printf(" drawSet : %s\n", hname_base ) ;

      bool islogy = gStyle->GetOptLogy() ;

       char cname[1000] ;
      if ( islogy ) {
         if ( recycleCanvas ) {
            sprintf( cname, "can_logy" ) ;
         } else {
            sprintf( cname, "can_logy_%s", hname_base ) ;
         }
      } else {
         if ( recycleCanvas ) {
            sprintf( cname, "can" ) ;
         } else {
            sprintf( cname, "can_%s", hname_base ) ;
         }
      }
      TCanvas* dmccan = (TCanvas*) gDirectory->FindObject( cname ) ;
      if ( dmccan == 0x0 ) {
         dmccan = new TCanvas( cname, hname_base, 600, 400 ) ;
      }
      dmccan->Clear() ;

      char hname[1000] ;
      sprintf( hname, "%s_mcstack", hname_base ) ;
      THStack* hmcstack = new THStack() ;

      TLegend* legend = new TLegend( 0.80, 0.67, 0.95, 0.92 ) ;
      legend->SetFillColor(kWhite) ;

      for ( int si=0; si<nbgsamples; si++ ) {
         sprintf( hname, "%s_%s", hname_base, samplename[si] ) ;
         TH1F* hmc = (TH1F*) gDirectory->FindObject( hname ) ;
         hmcstack -> Add( hmc ) ;
      } // si.

      for ( int si=nbgsamples-1; si>=0; si-- ) {
         sprintf( hname, "%s_%s", hname_base, samplename[si] ) ;
         TH1F* hmc = (TH1F*) gDirectory->FindObject( hname ) ;
         legend -> AddEntry( hmc, samplename[si] ) ;
      } // si.

      TH1F* hmcsum(0x0) ;
      for ( int si=0; si<nbgsamples; si++ ) {
         sprintf( hname, "%s_%s", hname_base, samplename[si] ) ;
         TH1F* hmc = (TH1F*) gDirectory->FindObject( hname ) ;
         if ( si==0 ) {
            sprintf( hname, "%s_mcsum", hname_base ) ;
            hmcsum = (TH1F*) hmc->Clone( hname ) ;
         } else {
            hmcsum->Add(hmc) ;
         }
      } // si.
      hmcsum->SetXTitle( xtitle ) ;

      sprintf( hname, "%s_%s", hname_base, samplename[nbgsamples] ) ;
      TH1F* hmcsig = (TH1F*) gDirectory->FindObject( hname ) ;
      hmcsum->Add(hmcsig) ;

      hmcsum->SetFillStyle(0) ;
      hmcsum->Draw("hist") ;
      hmcstack->Draw( "samehist" ) ;
      hmcstack->Draw( "same" ) ;

      int sls(1) ;
      for ( int si=nbgsamples; si<nsamples; si++ ) {
         sprintf( hname, "%s_%s", hname_base, samplename[si] ) ;
         TH1F* hmc = (TH1F*) gDirectory->FindObject( hname ) ;
         hmc->SetLineColor( hmc->GetFillColor() ) ;
         hmc->SetLineWidth(2) ;
         hmc->SetLineStyle(sls++ ) ;
         hmc->SetFillStyle(0) ;
         hmc->Draw("same") ;
         hmc->Draw("samehist") ;
         hmc->Draw("same axis") ;
         legend->AddEntry( hmc, samplename[si] ) ;
      } // si.

      legend->Draw() ;

      if ( savePdf ) {
         char filename[10000] ;
         if ( islogy ) {
            sprintf( filename, "outputfiles/%s_logy.pdf", hname_base ) ;
         } else {
            sprintf( filename, "outputfiles/%s_liny.pdf", hname_base ) ;
         }
         dmccan->SaveAs( filename ) ;
      }


   } // drawset.


  //==========================================================================================
  //==========================================================================================
  //==========================================================================================

