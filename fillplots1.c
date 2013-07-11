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

   void fillplots1() {

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

      char btagcuts[10000] ;
      sprintf( btagcuts, "%s", "CSVbest2>0.898&&CSVbest3>0.679&&CSVbest4>0.244" ) ;

      char leptonveto[10000] ;
      sprintf( leptonveto, "%s", "nMuons==0&&nElectrons==0&&nIsoTracks15_005_03==0&&nIsoTracks5_005_03<2&&nTausLoose==0" ) ;

      char dphicut[10000] ;
      sprintf( dphicut, "%s", "maxDeltaPhi_bb_bb<2.0" ) ;

      char cuts[100000] ;

      int bins(60) ;

      char varstring[1000] ;

      float xl, xh ;

   //--- METsig

      sprintf( varstring, "METsig" ) ;
      xl = 0. ;   xh = 500. ;

     //--- skim cuts only
      sprintf( cuts, "njets20>0" ) ; // does nothing.
      bookset( "h_metsig_skimcuts", "METsig, skim cuts", bins, xl, xh ) ;
      fillset( "h_metsig_skimcuts", varstring, cuts ) ;

     //--- skim + mass cuts
      sprintf( cuts, "(%s)", masscuts ) ;
      bookset( "h_metsig_masscuts", "METsig, skim + mass cuts", bins, xl, xh ) ;
      fillset( "h_metsig_masscuts", varstring, cuts ) ;

     //--- skim + btag
      sprintf( cuts, "(%s)", btagcuts ) ;
      bookset( "h_metsig_btagcuts", "METsig, skim + btag cuts", bins, xl, xh ) ;
      fillset( "h_metsig_btagcuts", varstring, cuts ) ;

     //--- skim + btag + lepton veto
      sprintf( cuts, "(%s)&&(%s)", btagcuts, leptonveto ) ;
      bookset( "h_metsig_btaglvcuts", "METsig, skim + btag + lepton veto cuts", bins, xl, xh ) ;
      fillset( "h_metsig_btaglvcuts", varstring, cuts ) ;

     //--- skim + btag + lepton veto + mass
      sprintf( cuts, "(%s)&&(%s)&&(%s)", btagcuts, leptonveto, masscuts ) ;
      bookset( "h_metsig_btaglvmasscuts", "METsig, skim + btag + lepton veto + mass cuts", bins, xl, xh ) ;
      fillset( "h_metsig_btaglvmasscuts", varstring, cuts ) ;

     //--- skim + btag + lepton veto + mass + deltaphi
      sprintf( cuts, "(%s)&&(%s)&&(%s)&&(%s)", btagcuts, leptonveto, masscuts, dphicut ) ;
      bookset( "h_metsig_btaglvmassdpcuts", "METsig, skim + btag + lepton veto + mass cuts + dphi cut", bins, xl, xh ) ;
      fillset( "h_metsig_btaglvmassdpcuts", varstring, cuts ) ;



   //--- METsig

      sprintf( varstring, "0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff)" ) ;
      xl = 0. ;   xh = 350. ;

     //--- skim cuts only
      sprintf( cuts, "njets20>0" ) ; // does nothing.
      bookset( "h_avemass_skimcuts", "ave mass, skim cuts", bins, xl, xh ) ;
      fillset( "h_avemass_skimcuts", varstring, cuts ) ;

     //--- skim + btag
      sprintf( cuts, "(%s)", btagcuts ) ;
      bookset( "h_avemass_btagcuts", "ave mass, skim + btag cuts", bins, xl, xh ) ;
      fillset( "h_avemass_btagcuts", varstring, cuts ) ;

     //--- skim + btag + lepton veto
      sprintf( cuts, "(%s)&&(%s)", btagcuts, leptonveto ) ;
      bookset( "h_avemass_btaglvcuts", "ave mass, skim + btag + lepton veto cuts", bins, xl, xh ) ;
      fillset( "h_avemass_btaglvcuts", varstring, cuts ) ;

     //--- skim + btag + lepton veto + deltaphi
      sprintf( cuts, "(%s)&&(%s)&&(%s)", btagcuts, leptonveto, dphicut ) ;
      bookset( "h_avemass_btaglvdpcuts", "ave mass, skim + btag + lepton veto + dphi cut", bins, xl, xh ) ;
      fillset( "h_avemass_btaglvdpcuts", varstring, cuts ) ;

     //--- skim + btag + lepton veto + deltaphi + METsig>20
      sprintf( cuts, "(%s)&&(%s)&&(%s)&&(METsig>20)", btagcuts, leptonveto, dphicut ) ;
      bookset( "h_avemass_btaglvdpcuts_metsig020", "ave mass, skim + btag + lepton veto + dphi cut + METsig>20", bins, xl, xh ) ;
      fillset( "h_avemass_btaglvdpcuts_metsig020", varstring, cuts ) ;

     //--- skim + btag + lepton veto + deltaphi + METsig>30
      sprintf( cuts, "(%s)&&(%s)&&(%s)&&(METsig>30)", btagcuts, leptonveto, dphicut ) ;
      bookset( "h_avemass_btaglvdpcuts_metsig030", "ave mass, skim + btag + lepton veto + dphi cut + METsig>30", bins, xl, xh ) ;
      fillset( "h_avemass_btaglvdpcuts_metsig030", varstring, cuts ) ;

     //--- skim + btag + lepton veto + deltaphi + METsig>50
      sprintf( cuts, "(%s)&&(%s)&&(%s)&&(METsig>50)", btagcuts, leptonveto, dphicut ) ;
      bookset( "h_avemass_btaglvdpcuts_metsig050", "ave mass, skim + btag + lepton veto + dphi cut + METsig>50", bins, xl, xh ) ;
      fillset( "h_avemass_btaglvdpcuts_metsig050", varstring, cuts ) ;

     //--- skim + btag + lepton veto + deltaphi + METsig>100
      sprintf( cuts, "(%s)&&(%s)&&(%s)&&(METsig>100)", btagcuts, leptonveto, dphicut ) ;
      bookset( "h_avemass_btaglvdpcuts_metsig100", "ave mass, skim + btag + lepton veto + dphi cut + METsig>100", bins, xl, xh ) ;
      fillset( "h_avemass_btaglvdpcuts_metsig100", varstring, cuts ) ;

     //--- skim + btag + lepton veto + deltaphi + METsig>150
      sprintf( cuts, "(%s)&&(%s)&&(%s)&&(METsig>150)", btagcuts, leptonveto, dphicut ) ;
      bookset( "h_avemass_btaglvdpcuts_metsig150", "ave mass, skim + btag + lepton veto + dphi cut + METsig>150", bins, xl, xh ) ;
      fillset( "h_avemass_btaglvdpcuts_metsig150", varstring, cuts ) ;

      saveHist( "plots1.root", "h*" ) ;


   } // fillplots1.

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




