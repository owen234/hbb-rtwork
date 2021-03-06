#include "TStyle.h"
#include "TChain.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "THStack.h"

#include "histio.c"

#include <iostream>


   bool bookset( const char* hname,
                 const char* htitle,
                 int nbins,
                 double xmin,
                 double xmax ) ;

   bool booksetCB( const char* hname,
                 const char* htitle ) ;

   bool fillset( const char* hname,
                 const char* var,
                 const char* cuts
                  ) ;

 //---------------------------
   int  nsamples(4) ;
   char samplename[4][100] = { "tt", "znn", "sig250", "sig400" } ;
   int  samplecolor[4] = { kBlue-9, kGreen-3, kMagenta+2, kMagenta+1 } ;
   TChain* samplechain[4] ;
 //---------------------------
 //int  nsamples(5) ;
 //char samplename[5][100] = { "ttsl", "tthad", "znn", "sig250", "sig400" } ;
 //int  samplecolor[5] = { kBlue-9, kBlue-3, kGreen-3, kMagenta+2, kMagenta+1 } ;
 //TChain* samplechain[5] ;
 //---------------------------

  //======================================================================

   void fillplots3() {

      gDirectory->Delete("h*") ;


      gStyle->SetOptStat(0) ;

      for ( int si=0; si<nsamples; si++ ) { samplechain[si] = new TChain("reducedTree") ; }

      char rtdir[10000] = "/Users/owen/work/cms/hadronic-susy-bjets/hbb/reduced-trees-may23-2013" ;
      //char rtdir[10000] = "/data/cms/hadronic-susy-bjets/hbb/reduced-trees-may23-2013" ;

      char pathandfile[10000] ;

      int sampleIndex(0) ;

     //--- ttbar, sl
      sprintf( pathandfile, "%s/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.TTJets_SemiLeptMGDecays_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A_ext-v1_AODSIM_UCSB1606_v66-slimskim.root", rtdir ) ;
      samplechain[sampleIndex] -> Add( pathandfile ) ;
      sprintf( pathandfile, "%s/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.TTJets_FullLeptMGDecays_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v2_AODSIM_UCSB1596_v66-slimskim.root", rtdir ) ;
      samplechain[sampleIndex] -> Add( pathandfile ) ;
      sampleIndex++ ;

   ////--- ttbar, had
   // sprintf( pathandfile, "%s/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.TTJets_HadronicMGDecays_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A_ext-v1_AODSIM_UCSB1613_v66-slimskim.root", rtdir ) ;
   // samplechain[sampleIndex] -> Add( pathandfile ) ;
   // sampleIndex++ ;

     //--- Znn
      sprintf( pathandfile, "%s/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.ZJetsToNuNu_100_HT_200_TuneZ2Star_8TeV_madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1_AODSIM_UCSB1525_v66-slimskim.root", rtdir ) ;
      samplechain[sampleIndex] -> Add( pathandfile ) ;
      sprintf( pathandfile, "%s/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.ZJetsToNuNu_100_HT_200_TuneZ2Star_8TeV_madgraph_ext_Summer12_DR53X-PU_S10_START53_V7C-v1_AODSIM_UCSB1607_v66-slimskim.root", rtdir ) ;
      samplechain[sampleIndex] -> Add( pathandfile ) ;
      sprintf( pathandfile, "%s/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.ZJetsToNuNu_200_HT_400_TuneZ2Star_8TeV_madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1_AODSIM_UCSB1524_v66-slimskim.root", rtdir ) ;
      samplechain[sampleIndex] -> Add( pathandfile ) ;
      sprintf( pathandfile, "%s/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.ZJetsToNuNu_200_HT_400_TuneZ2Star_8TeV_madgraph_ext_Summer12_DR53X-PU_S10_START53_V7A-v1_AODSIM_UCSB1594_v66-slimskim.root", rtdir ) ;
      samplechain[sampleIndex] -> Add( pathandfile ) ;
      sprintf( pathandfile, "%s/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.ZJetsToNuNu_400_HT_inf_TuneZ2Star_8TeV_madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1_AODSIM_UCSB1523_v66-slimskim.root", rtdir ) ;
      samplechain[sampleIndex] -> Add( pathandfile ) ;
      sprintf( pathandfile, "%s/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.ZJetsToNuNu_400_HT_inf_TuneZ2Star_8TeV_madgraph_ext_Summer12_DR53X-PU_S10_START53_V7A-v1_AODSIM_UCSB1602_v66-slimskim.root", rtdir ) ;
      samplechain[sampleIndex] -> Add( pathandfile ) ;
      sampleIndex++ ;


     //--- signal, 250
      sprintf( pathandfile, "%s/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.test_TChihh_250_v68-slimskim.root", rtdir ) ;
      samplechain[sampleIndex] -> Add( pathandfile ) ;
      sampleIndex++ ;

     //--- signal, 400
      sprintf( pathandfile, "%s/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.test_TChihh_400_v68-slimskim.root", rtdir ) ;
      samplechain[sampleIndex] -> Add( pathandfile ) ;
      sampleIndex++ ;


      char masscuts[10000] ;
      sprintf( masscuts, "%s", "abs(higgsMbb1MassDiff-higgsMbb2MassDiff)<20&&((0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff)>100)&&(0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff)<140))" ) ;

      char masssbcuts[10000] ;
      sprintf( masssbcuts, "%s", "!(abs(higgsMbb1MassDiff-higgsMbb2MassDiff)<30&&((0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff)>90)&&(0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff)<150)))" ) ;
      ////sprintf( masssbcuts, "%s", "!(abs(higgsMbb1MassDiff-higgsMbb2MassDiff)<30&&((0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff)>70)&&(0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff)<150)))" ) ;
      ////sprintf( masssbcuts, "%s", "!(abs(higgsMbb1MassDiff-higgsMbb2MassDiff)<30&&((0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff)>50)&&(0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff)<150)))" ) ;

      char btagcuts[10000] ;
      sprintf( btagcuts,  "%s", "CSVbest2>0.898&&CSVbest3>0.679&&CSVbest4>0.244" ) ;
      char btag3cuts[10000] ;
      sprintf( btag3cuts, "%s", "CSVbest2>0.898&&CSVbest3>0.679&&CSVbest4<0.244" ) ;
      char btag2cuts[10000] ;
      sprintf( btag2cuts, "%s", "CSVbest2>0.898&&CSVbest3<0.244" ) ;

      char leptonveto[10000] ;
      sprintf( leptonveto, "%s", "nMuons==0&&nElectrons==0&&nIsoTracks15_005_03==0&&nIsoTracks5_005_03<2&&nTausLoose==0" ) ;

      char dphicut[10000] ;
      sprintf( dphicut, "%s", "maxDeltaPhi_bb_bb<2.0" ) ;

      char drmaxcut[10000] ;
      sprintf( drmaxcut, "%s", "deltaRmax_hh<2.2" ) ;
      ///////sprintf( drmaxcut, "%s", "deltaRmax_hh<2.3" ) ;

      char cuts[100000] ;

      int bins(60) ;

      char varstring[1000] ;

      float xl, xh ;

   //--- METsig

      sprintf( varstring, "METsig" ) ;

     //--- 50 bins
      bins = 50. ;
      xl = 0. ;   xh = 500. ;

     //--- signal mass cuts
      sprintf( cuts, "(%s)&&(%s)&&(%s)&&(%s)", btagcuts, leptonveto, masscuts, drmaxcut ) ;
      bookset( "h_metsig_sigmass_b50", "METsig, signal mass cuts", bins, xl, xh ) ;
      fillset( "h_metsig_sigmass_b50", varstring, cuts ) ;

     //--- SB mass cuts
      sprintf( cuts, "(%s)&&(%s)&&(%s)&&(%s)", btagcuts, leptonveto, masssbcuts, drmaxcut ) ;
      bookset( "h_metsig_sbmass_b50", "METsig, SB mass cuts", bins, xl, xh ) ;
      fillset( "h_metsig_sbmass_b50", varstring, cuts ) ;


     //--- 20 bins
      bins = 20. ;
      xl = 0. ;   xh = 200. ;

     //--- signal mass cuts
      sprintf( cuts, "(%s)&&(%s)&&(%s)&&(%s)", btagcuts, leptonveto, masscuts, drmaxcut ) ;
      bookset( "h_metsig_sigmass_b20", "METsig, signal mass cuts", bins, xl, xh ) ;
      fillset( "h_metsig_sigmass_b20", varstring, cuts ) ;

     //--- SB mass cuts
      sprintf( cuts, "(%s)&&(%s)&&(%s)&&(%s)", btagcuts, leptonveto, masssbcuts, drmaxcut ) ;
      bookset( "h_metsig_sbmass_b20", "METsig, SB mass cuts", bins, xl, xh ) ;
      fillset( "h_metsig_sbmass_b20", varstring, cuts ) ;


     //--- custom bins

     //--- signal mass cuts
      sprintf( cuts, "(%s)&&(%s)&&(%s)&&(%s)", btagcuts, leptonveto, masscuts, drmaxcut ) ;
      booksetCB( "h_metsig_sigmass_cb", "METsig, signal mass cuts" ) ;
      fillset( "h_metsig_sigmass_cb", varstring, cuts ) ;

     //--- SB mass cuts
      sprintf( cuts, "(%s)&&(%s)&&(%s)&&(%s)", btagcuts, leptonveto, masssbcuts, drmaxcut ) ;
      booksetCB( "h_metsig_sbmass_cb", "METsig, SB mass cuts" ) ;
      fillset( "h_metsig_sbmass_cb", varstring, cuts ) ;






    //---- loosen btag cuts to 3.

     //--- 50 bins
      bins = 50. ;
      xl = 0. ;   xh = 500. ;

     //--- signal mass cuts
      sprintf( cuts, "(%s)&&(%s)&&(%s)&&(%s)", btag3cuts, leptonveto, masscuts, drmaxcut ) ;
      bookset( "h_metsig_sigmass_3b_b50", "METsig, signal mass cuts,  3btag", bins, xl, xh ) ;
      fillset( "h_metsig_sigmass_3b_b50", varstring, cuts ) ;

     //--- SB mass cuts
      sprintf( cuts, "(%s)&&(%s)&&(%s)&&(%s)", btag3cuts, leptonveto, masssbcuts, drmaxcut ) ;
      bookset( "h_metsig_sbmass_3b_b50", "METsig, SB mass cuts,  3btag", bins, xl, xh ) ;
      fillset( "h_metsig_sbmass_3b_b50", varstring, cuts ) ;


     //--- 20 bins
      bins = 20. ;
      xl = 0. ;   xh = 200. ;

     //--- signal mass cuts
      sprintf( cuts, "(%s)&&(%s)&&(%s)&&(%s)", btag3cuts, leptonveto, masscuts, drmaxcut ) ;
      bookset( "h_metsig_sigmass_3b_b20", "METsig, signal mass cuts,  3btag", bins, xl, xh ) ;
      fillset( "h_metsig_sigmass_3b_b20", varstring, cuts ) ;

     //--- SB mass cuts
      sprintf( cuts, "(%s)&&(%s)&&(%s)&&(%s)", btag3cuts, leptonveto, masssbcuts, drmaxcut ) ;
      bookset( "h_metsig_sbmass_3b_b20", "METsig, SB mass cuts,  3btag", bins, xl, xh ) ;
      fillset( "h_metsig_sbmass_3b_b20", varstring, cuts ) ;


     //--- custom bins

     //--- signal mass cuts
      sprintf( cuts, "(%s)&&(%s)&&(%s)&&(%s)", btag3cuts, leptonveto, masscuts, drmaxcut ) ;
      booksetCB( "h_metsig_sigmass_3b_cb", "METsig, signal mass cuts,  3btag" ) ;
      fillset( "h_metsig_sigmass_3b_cb", varstring, cuts ) ;

     //--- SB mass cuts
      sprintf( cuts, "(%s)&&(%s)&&(%s)&&(%s)", btag3cuts, leptonveto, masssbcuts, drmaxcut ) ;
      booksetCB( "h_metsig_sbmass_3b_cb", "METsig, SB mass cuts,  3btag" ) ;
      fillset( "h_metsig_sbmass_3b_cb", varstring, cuts ) ;




    //---- loosen btag cuts to 2.

     //--- 50 bins
      bins = 50. ;
      xl = 0. ;   xh = 500. ;

     //--- signal mass cuts
      sprintf( cuts, "(%s)&&(%s)&&(%s)&&(%s)", btag2cuts, leptonveto, masscuts, drmaxcut ) ;
      bookset( "h_metsig_sigmass_2b_b50", "METsig, signal mass cuts,  2btag", bins, xl, xh ) ;
      fillset( "h_metsig_sigmass_2b_b50", varstring, cuts ) ;

     //--- SB mass cuts
      sprintf( cuts, "(%s)&&(%s)&&(%s)&&(%s)", btag2cuts, leptonveto, masssbcuts, drmaxcut ) ;
      bookset( "h_metsig_sbmass_2b_b50", "METsig, SB mass cuts,  2btag", bins, xl, xh ) ;
      fillset( "h_metsig_sbmass_2b_b50", varstring, cuts ) ;


     //--- 20 bins
      bins = 20. ;
      xl = 0. ;   xh = 200. ;

     //--- signal mass cuts
      sprintf( cuts, "(%s)&&(%s)&&(%s)&&(%s)", btag2cuts, leptonveto, masscuts, drmaxcut ) ;
      bookset( "h_metsig_sigmass_2b_b20", "METsig, signal mass cuts,  2btag", bins, xl, xh ) ;
      fillset( "h_metsig_sigmass_2b_b20", varstring, cuts ) ;

     //--- SB mass cuts
      sprintf( cuts, "(%s)&&(%s)&&(%s)&&(%s)", btag2cuts, leptonveto, masssbcuts, drmaxcut ) ;
      bookset( "h_metsig_sbmass_2b_b20", "METsig, SB mass cuts,  2btag", bins, xl, xh ) ;
      fillset( "h_metsig_sbmass_2b_b20", varstring, cuts ) ;


     //--- custom bins

     //--- signal mass cuts
      sprintf( cuts, "(%s)&&(%s)&&(%s)&&(%s)", btag2cuts, leptonveto, masscuts, drmaxcut ) ;
      booksetCB( "h_metsig_sigmass_2b_cb", "METsig, signal mass cuts,  2btag" ) ;
      fillset( "h_metsig_sigmass_2b_cb", varstring, cuts ) ;

     //--- SB mass cuts
      sprintf( cuts, "(%s)&&(%s)&&(%s)&&(%s)", btag2cuts, leptonveto, masssbcuts, drmaxcut ) ;
      booksetCB( "h_metsig_sbmass_2b_cb", "METsig, SB mass cuts,  2btag" ) ;
      fillset( "h_metsig_sbmass_2b_cb", varstring, cuts ) ;



      saveHist( "plots3.root", "h*" ) ;


   } // fillplots3.

  //======================================================================

   bool bookset( const char* hname,
                 const char* htitle,
                 int nbins,
                 double xmin,
                 double xmax ) {

      char hfullname[1000] ;
      char hfulltitle[1000] ;


      for ( int si=0; si<nsamples; si++ ) {

         sprintf( hfullname, "%s_%s", hname, samplename[si] ) ;
         sprintf( hfulltitle, "%s, %s", htitle, samplename[si] ) ;
         TH1F* hist = new TH1F( hfullname, hfulltitle, nbins, xmin, xmax ) ;

         hist->SetFillColor( samplecolor[si] ) ;
         hist->Sumw2() ;

      }

      return true ;

   } // bookset

  //======================================================================

   bool booksetCB( const char* hname,
                 const char* htitle ) {

      char hfullname[1000] ;
      char hfulltitle[1000] ;

      int nbins(7) ;
      double xbins[8] = { 0., 10., 20., 30., 50., 100., 150., 200. } ;


      for ( int si=0; si<nsamples; si++ ) {

         sprintf( hfullname, "%s_%s", hname, samplename[si] ) ;
         sprintf( hfulltitle, "%s, %s", htitle, samplename[si] ) ;
         TH1F* hist = new TH1F( hfullname, hfulltitle, nbins, xbins ) ;

         hist->SetFillColor( samplecolor[si] ) ;
         hist->Sumw2() ;

      }

      return true ;

   } // bookset

  //======================================================================

   bool fillset( const char* hname,
                 const char* var,
                 const char* cuts
                 ) {

      float dataIntLumiIPB(20000.) ;

      TCanvas* cplots = (TCanvas*) gDirectory->FindObject("cplots") ;
      if ( cplots == 0x0 ) {
         cplots = new TCanvas("cplots","cplots", 800, 700 ) ;
         cplots->Clear() ;
         cplots->Divide(2,3) ;
      }



      for ( int si=0; si<nsamples; si++ ) {

         char hfullname[1000] ;
         sprintf( hfullname, "%s_%s", hname, samplename[si] ) ;

         printf(" Filling for sample %s : %s : ", samplename[si], hfullname ) ;

         cplots->cd( si+1 ) ;

         char arg1[10000] ;
         sprintf( arg1, "%s>>%s_%s", var, hname, samplename[si] ) ;
         printf("%s : ", arg1 ) ; cout << flush ;

         char allcuts[10000] ;
         if ( strcmp( samplename[si], "sig250" ) == 0 ) {
            sprintf( allcuts, "(%s)*9.0e-6*%.0f", cuts, dataIntLumiIPB ) ;
         } else if ( strcmp( samplename[si], "sig400" ) == 0 ) {
            sprintf( allcuts, "(%s)*1.0e-6*%.0f", cuts, dataIntLumiIPB ) ;
         } else {
            sprintf( allcuts, "(%s)*weight3*%.0f", cuts, dataIntLumiIPB ) ;
         }

         samplechain[si] -> Draw( arg1, allcuts ) ;
         printf("%s\n", cuts ) ;

         TH1F* hist = (TH1F*) gDirectory->FindObject( hfullname ) ;
         int nbins = hist->GetNbinsX() ;
         double newlastval = hist->GetBinContent( nbins ) ;
         newlastval += hist->GetBinContent( nbins+1 ) ;
         double newlasterr2 = pow( hist->GetBinError( nbins ), 2 ) ;
         newlasterr2 += pow( hist->GetBinError( nbins+1 ), 2 ) ;
         hist->SetBinContent( nbins, newlastval ) ;
         hist->SetBinError( nbins, sqrt(newlasterr2) ) ;
         hist->Draw("hist") ;
         hist->Draw("esame") ;
         cplots->Update() ;
         cplots->Draw() ;

      } // si.

      return true ;

   } // fillset

  //======================================================================




