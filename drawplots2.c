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
 //int  nsamples(4) ;
 //int  nbgsamples(2) ;
 //char samplename[4][100] = { "znn", "tt", "sig250", "sig400" } ;
 //--------------------
   int  nsamples(5) ;
   int  nbgsamples(3) ;
   char samplename[5][100] = { "znn", "ttsl", "tthad", "sig250", "sig400" } ;
 //--------------------

   bool savePdf ;
   char inrootfile[10000] ;

   void drawSet( const char* hname_base, const char* xtitle ) ;


  //==========================================================================================

   void drawplots2( const char* infile = "plots2.root", bool arg_recycleCanvas=false, const char* histnamepat = "" ) {

       recycleCanvas = arg_recycleCanvas ;

       gDirectory->Delete("h*") ;

       gStyle -> SetOptStat(0) ;
       gStyle -> SetTitleH(0.035 ) ;

       char histnamelist[500][100] ;
       char histxtitlelist[500][100] ;

       int hind(0) ;

       sprintf( histnamelist[hind], "h_metsig_allcuts" ) ; sprintf( histxtitlelist[hind], "METsig" ) ; hind++ ;
       sprintf( histnamelist[hind], "h_metsig_1lep" ) ; sprintf( histxtitlelist[hind], "METsig" ) ; hind++ ;
       sprintf( histnamelist[hind], "h_metsig_3btag" ) ; sprintf( histxtitlelist[hind], "METsig" ) ; hind++ ;
       sprintf( histnamelist[hind], "h_metsig_2btag" ) ; sprintf( histxtitlelist[hind], "METsig" ) ; hind++ ;
       sprintf( histnamelist[hind], "h_metsig_1lep3btag" ) ; sprintf( histxtitlelist[hind], "METsig" ) ; hind++ ;
       sprintf( histnamelist[hind], "h_metsig_1lep2btag" ) ; sprintf( histxtitlelist[hind], "METsig" ) ; hind++ ;



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




   } // drawplots1.

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
      TCanvas* pcanvas = (TCanvas*) gDirectory->FindObject( cname ) ;
      if ( pcanvas == 0x0 ) {
         pcanvas = new TCanvas( cname, hname_base, 600, 700 ) ;
      }
      pcanvas->Clear() ;

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


      TH1F* h_allcuts(0x0) ;
      h_allcuts = (TH1F*) gDirectory->FindObject("h_metsig_allcuts_mcsum") ;
      if ( h_allcuts==0x0 ) { printf("\n\n\n *** Missing h_metsig_allcuts.\n\n\n") ; return ; }



      sprintf( hname, "%s_ratio", hname_base ) ;
      TH1F* h_ratio = (TH1F*) h_allcuts->Clone( hname ) ;
      h_ratio->Reset() ;

      for ( int bi=1; bi<=h_allcuts->GetNbinsX(); bi++ ) {
         double allcuts = h_allcuts->GetBinContent( bi ) ;
         double allcuts_err = h_allcuts->GetBinError( bi ) ;
         double sbval = hmcsum->GetBinContent( bi ) ;
         double sberr = hmcsum->GetBinError( bi ) ;
         double ratio(0.) ;
         double ratio_err(0.) ;
         if ( allcuts > 0 ) {
            ratio = allcuts / sbval  ;
            double errsq(0.) ;
            if ( allcuts > 0 ) { errsq += pow(allcuts_err/allcuts,2.) ; }
            if ( sbval   > 0 ) { errsq += pow(sberr/sbval,2.) ; }
            ratio_err = sqrt(errsq)*ratio ;
         }
         h_ratio->SetBinContent( bi, ratio ) ;
         h_ratio->SetBinError( bi, ratio_err ) ;
      } // bi.




      char padname[1000] ;
      sprintf( padname, "tp_%s", hname_base ) ;
      TPad* toppad = new TPad( padname, padname, 0.02, 0.3, 0.98, 0.98 ) ;
      toppad->Draw() ;
      sprintf( padname, "bp_%s", hname_base ) ;
      if ( islogy ) { gStyle->SetOptLogy(0) ; }
      TPad* bottompad = new TPad( padname, padname, 0.02, 0.02, 0.98, 0.28 ) ;
      bottompad->Draw() ;
      if ( islogy ) { gStyle->SetOptLogy(1) ; }




     //---

      toppad->cd() ;

      h_allcuts->SetLineWidth(2) ;
      h_allcuts->SetLineColor(1) ;

      hmcsum->SetFillStyle(0) ;
      hmcsum->Draw("hist") ;
      hmcstack->Draw( "samehist" ) ;
      hmcstack->Draw( "same" ) ;
      h_allcuts->Draw( "histsame" ) ;
      h_allcuts->Draw( "histesame" ) ;
      legend->Draw() ;

      toppad->Update() ;
      toppad->Draw() ;

     //---


      bottompad->cd() ;
      h_ratio->Draw() ;
      bottompad->Update() ;
      bottompad->Draw() ;


     //---


   } // drawset.


  //==========================================================================================
  //==========================================================================================
  //==========================================================================================

