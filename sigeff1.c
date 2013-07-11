#define sigeff1_cxx
#include "sigeff1.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void addoverflow( TH1* hp ) {
   if ( hp==0x0 ) return ;
   int nb = hp -> GetNbinsX() ;
   float newval = hp -> GetBinContent( nb ) + hp -> GetBinContent( nb+1 ) ;
   float newerr = sqrt( pow( hp -> GetBinError( nb ), 2 ) + pow( hp -> GetBinError( nb+1 ), 2 ) ) ;
   hp -> SetBinContent( nb, newval ) ;
   hp -> SetBinError( nb, newerr ) ;
}

void sigeff1::Loop()
{

   if (fChain == 0) return;

   TH1F* h_lowestcsv_csv = new TH1F("h_lowestcsv_csv", "Lowest CSV jet, CVS output", 40, 0., 1. ) ;
   TH1F* h_lowestcsv_pt = new TH1F("h_lowestcsv_pt", "Lowest CSV jet, pt", 40, 0., 200. ) ;
   TH1F* h_lowestcsv_csv_4b = new TH1F("h_lowestcsv_csv_4b", "Lowest CSV jet, CVS output, 4b", 40, 0., 1. ) ;
   TH1F* h_lowestcsv_pt_4b = new TH1F("h_lowestcsv_pt_4b", "Lowest CSV jet, pt, 4b", 40, 0., 200. ) ;


   Long64_t nentries = fChain->GetEntries();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      //-- find the lowest CSV jet
      float lowestcsv(9.) ;
      float lowestcsvpt(0.) ;

      if ( higgs1CSV1 < lowestcsv ) {
         lowestcsv = higgs1CSV1 ;
         lowestcsvpt = higgs1jetpt1 ;
      }
      if ( higgs1CSV2 < lowestcsv ) {
         lowestcsv = higgs1CSV2 ;
         lowestcsvpt = higgs1jetpt2 ;
      }
      if ( higgs2CSV1 < lowestcsv ) {
         lowestcsv = higgs2CSV1 ;
         lowestcsvpt = higgs2jetpt1 ;
      }
      if ( higgs2CSV2 < lowestcsv ) {
         lowestcsv = higgs2CSV2 ;
         lowestcsvpt = higgs2jetpt2 ;
      }


      //--- lepton veto
      if ( ! (nMuons==0&&nElectrons==0&&nIsoTracks15_005_03==0&&nIsoTracks5_005_03<2&&nTausLoose==0 ) ) continue ;

      //--- two tight b tags
      if ( ! (CSVbest2>0.898) ) continue ;

      //--- max Dr cut
      if ( ! (deltaRmax_hh<2.2) ) continue ;

      //--- METsig>30
      if ( ! (METsig>30) ) continue ;
      ///////////////////if ( ! (METsig>100) ) continue ;

      bool pass2b(false) ;
      if ( CSVbest2>0.898&&CSVbest3<0.244 ) { pass2b = true ;  }

      bool pass4b(false) ;
      if ( CSVbest2>0.898&&CSVbest3>0.679&&CSVbest4>0.244  ) { pass4b = true ; }

      h_lowestcsv_csv -> Fill( lowestcsv ) ;
      h_lowestcsv_pt -> Fill( lowestcsvpt ) ;

      if ( pass4b ) {
         h_lowestcsv_csv_4b -> Fill( lowestcsv ) ;
         h_lowestcsv_pt_4b -> Fill( lowestcsvpt ) ;
      }


   } // jentry.

   addoverflow( h_lowestcsv_pt_4b ) ;
   addoverflow( h_lowestcsv_csv_4b ) ;

   addoverflow( h_lowestcsv_pt ) ;
   addoverflow( h_lowestcsv_csv ) ;


}
