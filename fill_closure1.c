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
   int  nsamples(3) ;
   char samplename[3][100] = { "ttsl", "znn", "qcd" } ;
   int  samplecolor[3] = { kBlue-9, kGreen-3, kRed } ;
   TChain* samplechain[3] ;
 //---------------------------

  //======================================================================

   void fill_closure1() {

      gDirectory->Delete("h*") ;


      gStyle->SetOptStat(0) ;

      for ( int si=0; si<nsamples; si++ ) { samplechain[si] = new TChain("reducedTree") ; }

      char rtdir[10000] = "/data/cms/hadronic-susy-bjets/hbb/reduced-trees-july03-2013" ;

      char pathandfile[10000] ;

      int sampleIndex(0) ;

     //--- ttbar, sl
      sprintf( pathandfile, "%s/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.TTJets_SemiLeptMGDecays_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7C-v1_AODSIM_UCSB1800_v69-slimskim.root", rtdir ) ;
      samplechain[sampleIndex] -> Add( pathandfile ) ;
      sprintf( pathandfile, "%s/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.TTJets_FullLeptMGDecays_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7C-v2_AODSIM_UCSB1799_v69-slimskim.root", rtdir ) ;
      samplechain[sampleIndex] -> Add( pathandfile ) ;
      sampleIndex++ ;

     //--- Znn
      sprintf( pathandfile, "%s/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.ZJetsToNuNu_100_HT_200_TuneZ2Star_8TeV_madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1_AODSIM_UCSB1832_v69-slimskim.root", rtdir ) ;
      samplechain[sampleIndex] -> Add( pathandfile ) ;
      sprintf( pathandfile, "%s/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.ZJetsToNuNu_200_HT_400_TuneZ2Star_8TeV_madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1_AODSIM_UCSB1833_v69-slimskim.root", rtdir ) ;
      samplechain[sampleIndex] -> Add( pathandfile ) ;
      sprintf( pathandfile, "%s/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.ZJetsToNuNu_200_HT_400_TuneZ2Star_8TeV_madgraph_ext_Summer12_DR53X-PU_S10_START53_V7A-v1_AODSIM_UCSB1834_v69-slimskim.root", rtdir ) ;
      samplechain[sampleIndex] -> Add( pathandfile ) ;
      sprintf( pathandfile, "%s/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.ZJetsToNuNu_400_HT_inf_TuneZ2Star_8TeV_madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1_AODSIM_UCSB1831_v69-slimskim.root", rtdir ) ;
      samplechain[sampleIndex] -> Add( pathandfile ) ;
      sprintf( pathandfile, "%s/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.ZJetsToNuNu_400_HT_inf_TuneZ2Star_8TeV_madgraph_ext_Summer12_DR53X-PU_S10_START53_V7A-v1_AODSIM_UCSB1835_v69-slimskim.root", rtdir ) ;
      samplechain[sampleIndex] -> Add( pathandfile ) ;
      sampleIndex++ ;

     //--- QCD
      sprintf( pathandfile, "%s/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.QCD_Pt-1000to1400_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1_AODSIM_UCSB1820_v69-slimskim.root", rtdir ) ;
      samplechain[sampleIndex] -> Add( pathandfile ) ;
      sprintf( pathandfile, "%s/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v3_AODSIM_UCSB1814_v69-slimskim.root", rtdir ) ;
      samplechain[sampleIndex] -> Add( pathandfile ) ;
      sprintf( pathandfile, "%s/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.QCD_Pt-1400to1800_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1_AODSIM_UCSB1821_v69-slimskim.root", rtdir ) ;
      samplechain[sampleIndex] -> Add( pathandfile ) ;
      sprintf( pathandfile, "%s/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.QCD_Pt-170to300_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2_AODSIM_UCSB1815_v69-slimskim.root", rtdir ) ;
      samplechain[sampleIndex] -> Add( pathandfile ) ;
      sprintf( pathandfile, "%s/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.QCD_Pt-1800_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1_AODSIM_UCSB1822_v69-slimskim.root", rtdir ) ;
      samplechain[sampleIndex] -> Add( pathandfile ) ;
      sprintf( pathandfile, "%s/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.QCD_Pt-300to470_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2_AODSIM_UCSB1816_v69-slimskim.root", rtdir ) ;
      samplechain[sampleIndex] -> Add( pathandfile ) ;
      sprintf( pathandfile, "%s/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.QCD_Pt-470to600_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2_AODSIM_UCSB1817_v69-slimskim.root", rtdir ) ;
      samplechain[sampleIndex] -> Add( pathandfile ) ;
      sprintf( pathandfile, "%s/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.QCD_Pt-600to800_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2_AODSIM_UCSB1818_v69-slimskim.root", rtdir ) ;
      samplechain[sampleIndex] -> Add( pathandfile ) ;
      sprintf( pathandfile, "%s/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.QCD_Pt-800to1000_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2_AODSIM_UCSB1819_v69-slimskim.root", rtdir ) ;
      samplechain[sampleIndex] -> Add( pathandfile ) ;
      sampleIndex++ ;


      char basiccuts[10000] ;
      sprintf( basiccuts, "cutPV==1&&passCleaning==1&&buggyEvent==0" ) ;

      char triggercuts[10000] ;
      sprintf( triggercuts, "(passMC_DiCentralPFJet30_PFMET80_BTagCSV07==1||passMC_DiPFJet80_DiPFJet30_BTagCSVd07d05==1||passMC_PFMET150==1)" ) ;

      char njetcuts[10000] ;
      sprintf( njetcuts, "njets30>=4&&njets30<=5" ) ;

      char skimcuts[10000] ;
      sprintf( skimcuts, "((%s)&&(%s)&&(%s))", basiccuts, triggercuts, njetcuts ) ;

      char leptonveto[10000] ;
      sprintf( leptonveto, "%s", "nMuons==0&&nElectrons==0&&nIsoTracks15_005_03==0&&nTausLoose==0" ) ;

      char drmaxcut[10000] ;
      sprintf( drmaxcut, "%s", "deltaRmax_hh<2.2" ) ;

      char basecuts[10000] ;
      sprintf( basecuts, "(%s)&&(%s)&&(%s)", skimcuts, leptonveto, drmaxcut ) ;



      char masssigcuts[10000] ;
      sprintf( masssigcuts, "%s", "abs(higgsMbb1MassDiff-higgsMbb2MassDiff)<20&&((0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff)>100)&&(0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff)<140))" ) ;

      char masssbcuts[10000] ;
      sprintf( masssbcuts, "%s", "!(abs(higgsMbb1MassDiff-higgsMbb2MassDiff)<30&&((0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff)>90)&&(0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff)<150)))" ) ;

      char btag4bcuts[10000] ;
      sprintf( btag4bcuts, "%s", "CSVbest2>0.898&&CSVbest3>0.679&&CSVbest4>0.244" ) ;
      char btag3bcuts[10000] ;
      sprintf( btag3bcuts, "%s", "CSVbest2>0.898&&CSVbest3>0.679&&CSVbest4<0.244" ) ;
      char btag2bcuts[10000] ;
      sprintf( btag2bcuts, "%s", "CSVbest2>0.898&&CSVbest3<0.679" ) ;




      char cuts[100000] ;

      int bins ;

      char varstring[1000] ;

      float xl, xh ;

   //--- METsig

      sprintf( varstring, "METsig_2012" ) ;
      xl = 0. ;   xh = 200. ;   bins = 40 ;

     //--- base cuts, 2b
      sprintf( cuts, "(%s)&&(%s)", basecuts, btag2bcuts ) ;
      bookset( "h_metsig_2b", "METsig, 2b", bins, xl, xh ) ;
      fillset( "h_metsig_2b", varstring, cuts ) ;

     //--- base cuts, 3b
      sprintf( cuts, "(%s)&&(%s)", basecuts, btag3bcuts ) ;
      bookset( "h_metsig_3b", "METsig, 3b", bins, xl, xh ) ;
      fillset( "h_metsig_3b", varstring, cuts ) ;

     //--- base cuts, 4b
      sprintf( cuts, "(%s)&&(%s)", basecuts, btag4bcuts ) ;
      bookset( "h_metsig_4b", "METsig, 4b", bins, xl, xh ) ;
      fillset( "h_metsig_4b", varstring, cuts ) ;


   //--- minDeltaPhi30

      sprintf( varstring, "minDeltaPhi30" ) ;
      xl = 0. ;   xh = 3.2 ;   bins = 64 ;

     //--- base cuts, METsig_2012>25, 2b
      sprintf( cuts, "(%s)&&(%s)&&METsig_2012>25", basecuts, btag2bcuts ) ;
      bookset( "h_mindphi30_ms25_2b", "minDeltaPhi30, METsig_2012>25, 2b", bins, xl, xh ) ;
      fillset( "h_mindphi30_ms25_2b", varstring, cuts ) ;

     //--- base cuts, METsig_2012>25, 3b
      sprintf( cuts, "(%s)&&(%s)&&METsig_2012>25", basecuts, btag3bcuts ) ;
      bookset( "h_mindphi30_ms25_3b", "minDeltaPhi30, METsig_2012>25, 3b", bins, xl, xh ) ;
      fillset( "h_mindphi30_ms25_3b", varstring, cuts ) ;

     //--- base cuts, METsig_2012>25, 4b
      sprintf( cuts, "(%s)&&(%s)&&METsig_2012>25", basecuts, btag4bcuts ) ;
      bookset( "h_mindphi30_ms25_4b", "minDeltaPhi30, METsig_2012>25, 4b", bins, xl, xh ) ;
      fillset( "h_mindphi30_ms25_4b", varstring, cuts ) ;




     //--- base cuts, METsig_2012>15, 2b
      sprintf( cuts, "(%s)&&(%s)&&METsig_2012>15", basecuts, btag2bcuts ) ;
      bookset( "h_mindphi30_ms15_2b", "minDeltaPhi30, METsig_2012>15, 2b", bins, xl, xh ) ;
      fillset( "h_mindphi30_ms15_2b", varstring, cuts ) ;

     //--- base cuts, METsig_2012>15, 3b
      sprintf( cuts, "(%s)&&(%s)&&METsig_2012>15", basecuts, btag3bcuts ) ;
      bookset( "h_mindphi30_ms15_3b", "minDeltaPhi30, METsig_2012>15, 3b", bins, xl, xh ) ;
      fillset( "h_mindphi30_ms15_3b", varstring, cuts ) ;

     //--- base cuts, METsig_2012>15, 4b
      sprintf( cuts, "(%s)&&(%s)&&METsig_2012>15", basecuts, btag4bcuts ) ;
      bookset( "h_mindphi30_ms15_4b", "minDeltaPhi30, METsig_2012>15, 4b", bins, xl, xh ) ;
      fillset( "h_mindphi30_ms15_4b", varstring, cuts ) ;




     //--- base cuts, METsig_2012>5, 2b
      sprintf( cuts, "(%s)&&(%s)&&METsig_2012>5", basecuts, btag2bcuts ) ;
      bookset( "h_mindphi30_ms05_2b", "minDeltaPhi30, METsig_2012>5, 2b", bins, xl, xh ) ;
      fillset( "h_mindphi30_ms05_2b", varstring, cuts ) ;

     //--- base cuts, METsig_2012>5, 3b
      sprintf( cuts, "(%s)&&(%s)&&METsig_2012>5", basecuts, btag3bcuts ) ;
      bookset( "h_mindphi30_ms05_3b", "minDeltaPhi30, METsig_2012>5, 3b", bins, xl, xh ) ;
      fillset( "h_mindphi30_ms05_3b", varstring, cuts ) ;

     //--- base cuts, METsig_2012>5, 4b
      sprintf( cuts, "(%s)&&(%s)&&METsig_2012>5", basecuts, btag4bcuts ) ;
      bookset( "h_mindphi30_ms05_4b", "minDeltaPhi30, METsig_2012>5, 4b", bins, xl, xh ) ;
      fillset( "h_mindphi30_ms05_4b", varstring, cuts ) ;




      saveHist( "outputfiles/plots_closure1.root", "h*" ) ;


   } // fill_closure1.

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




