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

   void drawSet( const char* hname_base, const char* xtitle ) ;


  //==========================================================================================

   void drawplots3_clean( const char* histnamepat = "", bool arg_savePdf = true, const char* infile = "plots3.root", bool arg_recycleCanvas=false ) {

       recycleCanvas = arg_recycleCanvas ;
       savePdf = arg_savePdf ;


       gDirectory->Delete("h*") ;

       gStyle -> SetOptStat(0) ;
       gStyle -> SetTitleH(0.035 ) ;

       char histnamelist[500][100] ;
       char histxtitlelist[500][100] ;

       int hind(0) ;

       sprintf( histnamelist[hind], "h_metsig_sigmass_cb" ) ; sprintf( histxtitlelist[hind], "METsig" ) ; hind++ ;
       sprintf( histnamelist[hind], "h_metsig_sigmass_3b_cb" ) ; sprintf( histxtitlelist[hind], "METsig" ) ; hind++ ;
       sprintf( histnamelist[hind], "h_metsig_sigmass_2b_cb" ) ; sprintf( histxtitlelist[hind], "METsig" ) ; hind++ ;
       sprintf( histnamelist[hind], "h_metsig_sbmass_cb" ) ; sprintf( histxtitlelist[hind], "METsig" ) ; hind++ ;
       sprintf( histnamelist[hind], "h_metsig_sbmass_3b_cb" ) ; sprintf( histxtitlelist[hind], "METsig" ) ; hind++ ;
       sprintf( histnamelist[hind], "h_metsig_sbmass_2b_cb" ) ; sprintf( histxtitlelist[hind], "METsig" ) ; hind++ ;



       int nhistlist = hind ;

       loadHist( infile ) ;

   ////--- log y scale.
   //  printf("\n\n Log scale plots.\n\n") ;

   //  gStyle->SetOptLogy(1) ;

   //  for ( int hi=0; hi<nhistlist; hi++ ) {
   //     if ( strlen(histnamepat) > 0 ) {
   //        TString str( histnamelist[hi] ) ;
   //        if ( str.Contains( histnamepat ) ) {
   //           drawSet( histnamelist[hi], histxtitlelist[hi] ) ;
   //        }
   //     } else {
   //        drawSet( histnamelist[hi], histxtitlelist[hi] ) ;
   //     }
   //  }


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




   } // drawplots3.

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

      for ( int si=0; si<=nbgsamples; si++ ) {
         sprintf( hname, "%s_%s", hname_base, samplename[si] ) ;
         TH1F* hmc = (TH1F*) gDirectory->FindObject( hname ) ;
         hmcstack -> Add( hmc ) ;
      } // si.

      for ( int si=nbgsamples; si>=0; si-- ) {
         sprintf( hname, "%s_%s", hname_base, samplename[si] ) ;
         TH1F* hmc = (TH1F*) gDirectory->FindObject( hname ) ;
         legend -> AddEntry( hmc, samplename[si] ) ;
      } // si.

      TH1F* hmcsum(0x0) ;
      for ( int si=0; si<=nbgsamples; si++ ) {
         sprintf( hname, "%s_%s", hname_base, samplename[si] ) ;
         TH1F* hmc = (TH1F*) gDirectory->FindObject( hname ) ;
         if ( si==0 ) {
            sprintf( hname, "%s_mcsum", hname_base ) ;
            hmcsum = (TH1F*) hmc->Clone( hname ) ;
         } else {
            hmcsum->Add(hmc) ;
         }
      } // si.
  //  sprintf( hname, "%s_mcbgsum", hname_base ) ;
  //  TH1F* hmcbgsum = (TH1F*) hmcsum->Clone( hname ) ;
  //  hmcbgsum->SetXTitle( xtitle ) ;
      hmcsum->SetXTitle( xtitle ) ;


  //  sprintf( hname, "%s_%s", hname_base, samplename[nbgsamples] ) ;
  //  TH1F* hmcsig = (TH1F*) gDirectory->FindObject( hname ) ;
  //  hmcsum->Add(hmcsig) ;

      if ( islogy ) {
         hmcsum->SetMinimum(0.1) ;
      } else {
         hmcsum->SetMinimum(0.0) ;
      }

      hmcsum->SetFillStyle(0) ;
      hmcsum->Draw("hist") ;
      hmcstack->Draw( "samehist" ) ;
      hmcstack->Draw( "same" ) ;

   // int sls(1) ;
   // for ( int si=nbgsamples; si<nsamples; si++ ) {
   //    sprintf( hname, "%s_%s", hname_base, samplename[si] ) ;
   //    TH1F* hmc = (TH1F*) gDirectory->FindObject( hname ) ;
   //    hmc->SetLineColor( hmc->GetFillColor() ) ;
   //    hmc->SetLineWidth(2) ;
   //    hmc->SetLineStyle(sls++ ) ;
   //    hmc->SetFillStyle(0) ;
   //    hmc->Draw("same") ;
   //    hmc->Draw("samehist") ;
   //    hmc->Draw("same axis") ;
   //    legend->AddEntry( hmc, samplename[si] ) ;
   // } // si.

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




