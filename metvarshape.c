

#include "TChain.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TSystem.h"
#include "histio.c"
#include "TMath.h"
#include "TString.h"
#include "TLegend.h"




 //----------------
   int  nbgcomps(4) ;
   char bgcompname[4][100] = { "tt", "znn", "qcd", "tthad" } ;
   TChain* bgcompchain[4] ;
 //----------------

   float dataIntLumiIPB(20000.) ;

   void addoverflow( TH1* hp, bool dounder = false ) ;
   TH1F* make_h_cbw( TH1* hin, float xshift=0. ) ;

   void metvarshape( float sigmass = 250 ) {


      gStyle -> SetOptStat(0) ;

      //gStyle -> SetOptLogy(1) ;


      double met_bin_edges_metsig[8] ;
      double met_bin_edges_metsig2012[8] ;
      double met_bin_edges_met[8] ;
      double met_bin_edges_metovsqrtht[8] ;

      int bins_of_met(7) ;

      met_bin_edges_metsig[0] =   0. ;
      met_bin_edges_metsig[1] =  10. ;
      met_bin_edges_metsig[2] =  20. ;
      met_bin_edges_metsig[3] =  30. ;
      met_bin_edges_metsig[4] =  50. ;
      met_bin_edges_metsig[5] = 100. ;
      met_bin_edges_metsig[6] = 150. ;
      met_bin_edges_metsig[7] = 250. ; // add overflows

      met_bin_edges_metsig2012[0] =   0. ;
      met_bin_edges_metsig2012[1] =   9. ;
      met_bin_edges_metsig2012[2] =  17. ;
      met_bin_edges_metsig2012[3] =  25. ;
      met_bin_edges_metsig2012[4] =  40. ;
      met_bin_edges_metsig2012[5] =  85. ;
      met_bin_edges_metsig2012[6] = 120. ;
      met_bin_edges_metsig2012[7] = 200. ; // add overflows

      met_bin_edges_met[0] =   0. ;
      met_bin_edges_met[1] =  60. ;
      met_bin_edges_met[2] =  85. ;
      met_bin_edges_met[3] = 106. ;
      met_bin_edges_met[4] = 133. ;
      met_bin_edges_met[5] = 190. ;
      met_bin_edges_met[6] = 250. ;
      met_bin_edges_met[7] = 350. ; // add overflows

      met_bin_edges_metovsqrtht[0] =  0.0 ;
      met_bin_edges_metovsqrtht[1] =  3.3 ;
      met_bin_edges_metovsqrtht[2] =  4.7 ;
      met_bin_edges_metovsqrtht[3] =  5.9 ;
      met_bin_edges_metovsqrtht[4] =  7.7 ;
      met_bin_edges_metovsqrtht[5] = 10.8 ;
      met_bin_edges_metovsqrtht[6] = 13.0 ;
      met_bin_edges_metovsqrtht[7] = 20.0 ; // add overflows

      printf("\n\n Setting up reduced tree chains.\n\n" ) ;

      for ( int si=0; si<nbgcomps; si++ ) { bgcompchain[si] = new TChain("reducedTree") ; }
      char rtdir[10000] = "/Users/owen/work/cms/hadronic-susy-bjets/hbb/reduced-trees-july11-2013-pt20" ;


      int compIndex(0) ;

      char pathandfile[10000] ;

     //--- ttbar, 1 and 2 lepton
      sprintf( pathandfile, "%s/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.TTJets_SemiLeptMGDecays_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7C-v1_AODSIM_UCSB1800_v69-slimskim.root", rtdir ) ;
      bgcompchain[compIndex] -> Add( pathandfile ) ;
      sprintf( pathandfile, "%s/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.TTJets_FullLeptMGDecays_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7C-v2_AODSIM_UCSB1799_v69-slimskim.root", rtdir ) ;
      bgcompchain[compIndex] -> Add( pathandfile ) ;
      compIndex++ ;

     //--- Znn
      sprintf( pathandfile, "%s/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.ZJetsToNuNu_100_HT_200_TuneZ2Star_8TeV_madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1_AODSIM_UCSB1832_v69-slimskim.root", rtdir ) ;
      bgcompchain[compIndex] -> Add( pathandfile ) ;
      sprintf( pathandfile, "%s/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.ZJetsToNuNu_200_HT_400_TuneZ2Star_8TeV_madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1_AODSIM_UCSB1833_v69-slimskim.root", rtdir ) ;
      bgcompchain[compIndex] -> Add( pathandfile ) ;
      sprintf( pathandfile, "%s/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.ZJetsToNuNu_200_HT_400_TuneZ2Star_8TeV_madgraph_ext_Summer12_DR53X-PU_S10_START53_V7A-v1_AODSIM_UCSB1834_v69-slimskim.root", rtdir ) ;
      bgcompchain[compIndex] -> Add( pathandfile ) ;
      sprintf( pathandfile, "%s/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.ZJetsToNuNu_400_HT_inf_TuneZ2Star_8TeV_madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1_AODSIM_UCSB1831_v69-slimskim.root", rtdir ) ;
      bgcompchain[compIndex] -> Add( pathandfile ) ;
      sprintf( pathandfile, "%s/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.ZJetsToNuNu_400_HT_inf_TuneZ2Star_8TeV_madgraph_ext_Summer12_DR53X-PU_S10_START53_V7A-v1_AODSIM_UCSB1835_v69-slimskim.root", rtdir ) ;
      bgcompchain[compIndex] -> Add( pathandfile ) ;
      compIndex++ ;

     //--- QCD
      sprintf( pathandfile, "%s/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.QCD_Pt-1000to1400_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1_AODSIM_UCSB1820_v69-slimskim.root", rtdir ) ;
      bgcompchain[compIndex] -> Add( pathandfile ) ;
      sprintf( pathandfile, "%s/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v3_AODSIM_UCSB1814_v69-slimskim.root", rtdir ) ;
      bgcompchain[compIndex] -> Add( pathandfile ) ;
      sprintf( pathandfile, "%s/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.QCD_Pt-1400to1800_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1_AODSIM_UCSB1821_v69-slimskim.root", rtdir ) ;
      bgcompchain[compIndex] -> Add( pathandfile ) ;
      sprintf( pathandfile, "%s/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.QCD_Pt-170to300_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2_AODSIM_UCSB1815_v69-slimskim.root", rtdir ) ;
      bgcompchain[compIndex] -> Add( pathandfile ) ;
      sprintf( pathandfile, "%s/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.QCD_Pt-1800_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1_AODSIM_UCSB1822_v69-slimskim.root", rtdir ) ;
      bgcompchain[compIndex] -> Add( pathandfile ) ;
      sprintf( pathandfile, "%s/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.QCD_Pt-300to470_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2_AODSIM_UCSB1816_v69-slimskim.root", rtdir ) ;
      bgcompchain[compIndex] -> Add( pathandfile ) ;
      sprintf( pathandfile, "%s/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.QCD_Pt-470to600_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2_AODSIM_UCSB1817_v69-slimskim.root", rtdir ) ;
      bgcompchain[compIndex] -> Add( pathandfile ) ;
      sprintf( pathandfile, "%s/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.QCD_Pt-600to800_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2_AODSIM_UCSB1818_v69-slimskim.root", rtdir ) ;
      bgcompchain[compIndex] -> Add( pathandfile ) ;
      sprintf( pathandfile, "%s/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.QCD_Pt-800to1000_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2_AODSIM_UCSB1819_v69-slimskim.root", rtdir ) ;
      bgcompchain[compIndex] -> Add( pathandfile ) ;
      compIndex++ ;

     //--- hadronic ttbar
      sprintf( pathandfile, "%s/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.TTJets_HadronicMGDecays_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A_ext-v1_AODSIM_UCSB1848_v69-slimskim.root", rtdir ) ;
      bgcompchain[compIndex] -> Add( pathandfile ) ;
      compIndex++ ;


      float signal_weight = 1. ;
      TChain* sigchain ;

      if ( sigmass == 200 ) {

         sprintf( pathandfile, "%s/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.SMS-HbbHbb_mHiggsino-200_mLSP-1_8TeV-Pythia6Z_jgsmith_UCSB1807_v69-slimskim.root", rtdir ) ;
         sigchain = new TChain("reducedTree") ;
         sigchain -> Add( pathandfile ) ;
         signal_weight = 1.91e-6 ;

      } else if ( sigmass == 250 ) {

         sprintf( pathandfile, "%s/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.SMS-HbbHbb_mHiggsino-250_mLSP-1_8TeV-Pythia6Z_jgsmith_UCSB1809_v69-slimskim.root", rtdir ) ;
         sigchain = new TChain("reducedTree") ;
         sigchain -> Add( pathandfile ) ;
         signal_weight = 7.68e-7 ;

      } else if ( sigmass == 300 ) {

         sprintf( pathandfile, "%s/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.SMS-HbbHbb_mHiggsino-300_mLSP-1_8TeV-Pythia6Z_jgsmith_UCSB1810_v69-slimskim.root", rtdir ) ;
         sigchain = new TChain("reducedTree") ;
         sigchain -> Add( pathandfile ) ;
         signal_weight = 3.49e-7 ;

      } else if ( sigmass == 350 ) {

         sprintf( pathandfile, "%s/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.SMS-HbbHbb_mHiggsino-350_mLSP-1_8TeV-Pythia6Z_jgsmith_UCSB1811_v69-slimskim.root", rtdir ) ;
         sigchain = new TChain("reducedTree") ;
         sigchain -> Add( pathandfile ) ;
         signal_weight = 1.74e-7 ;

      } else if ( sigmass == 400 ) {

         sprintf( pathandfile, "%s/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.SMS-HbbHbb_mHiggsino-400_mLSP-1_8TeV-Pythia6Z_jgsmith_UCSB1812_v69-slimskim.root", rtdir ) ;
         sigchain = new TChain("reducedTree") ;
         sigchain -> Add( pathandfile ) ;
         signal_weight = 9.25e-8 ;

      } else if ( sigmass == 450 ) {

         sprintf( pathandfile, "%s/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.SMS-HbbHbb_mHiggsino-450_mLSP-1_8TeV-Pythia6Z_jgsmith_UCSB1808_v69-slimskim.root", rtdir ) ;
         sigchain = new TChain("reducedTree") ;
         sigchain -> Add( pathandfile ) ;
         signal_weight = 5.13e-8 ;

      }












     //--- Define cuts.

      printf("\n\n Setting up cuts.\n\n") ;

     //--- These are included in the skim definition of doSlimSkim.c.  Doesn't hurt to apply them here.

      char basiccuts[10000] ;
      sprintf( basiccuts, "cutPV==1&&passCleaning==1&&buggyEvent==0" ) ;

      char triggercuts[10000] ;
      sprintf( triggercuts, "(passMC_DiCentralPFJet30_PFMET80_BTagCSV07==1||passMC_PFMET150==1)" ) ;

      char njetcuts[10000] ;
      sprintf( njetcuts, "njets20>=4&&njets20<=5" ) ;

      char skimcuts[10000] ;
      sprintf( skimcuts, "((%s)&&(%s)&&(%s))", basiccuts, triggercuts, njetcuts ) ;


     //--- These are beyond the skim selection.

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

      char leptonveto[10000] ;
      sprintf( leptonveto, "%s", "nMuons==0&&nElectrons==0&&nIsoTracks15_005_03==0&&nTausLoose==0" ) ;

      char drmaxcut[10000] ;
      sprintf( drmaxcut, "%s", "deltaRmax_hh<2.2" ) ;

      char mindphicut[10000] ;
      sprintf( mindphicut, "%s", "minDeltaPhi30>0.3" ) ;

      char jet2ptcut[10000] ;
      sprintf( jet2ptcut, "%s", "jetpt2>50" ) ;

      char allcommoncuts[10000] ;
      sprintf( allcommoncuts, "(%s)&&(%s)&&(%s)&&(%s)", skimcuts, leptonveto, drmaxcut, jet2ptcut ) ;









      gDirectory -> Delete( "h*" ) ;

     //--- fill histograms.


      TH1F* h_metsig_all_qcd      = new TH1F("h_metsig_all_qcd"     , "METsig, all, qcd"     , bins_of_met, met_bin_edges_metsig ) ;
      TH1F* h_metsig2012_all_qcd  = new TH1F("h_metsig2012_all_qcd" , "metsig2012, all, qcd" , bins_of_met, met_bin_edges_metsig2012 ) ;
      TH1F* h_met_all_qcd         = new TH1F("h_met_all_qcd"        , "met, all, qcd"        , bins_of_met, met_bin_edges_met ) ;
      TH1F* h_metovsqrtht_all_qcd = new TH1F("h_metovsqrtht_all_qcd", "metovsqrtht, all, qcd", bins_of_met, met_bin_edges_metovsqrtht ) ;

      h_metsig_all_qcd -> Sumw2() ;
      h_metsig2012_all_qcd -> Sumw2() ;
      h_met_all_qcd -> Sumw2() ;
      h_metovsqrtht_all_qcd -> Sumw2() ;



      TH1F* h_metsig_2b_qcd      = new TH1F("h_metsig_2b_qcd"     , "METsig, 2b, qcd"     , bins_of_met, met_bin_edges_metsig ) ;
      TH1F* h_metsig2012_2b_qcd  = new TH1F("h_metsig2012_2b_qcd" , "metsig2012, 2b, qcd" , bins_of_met, met_bin_edges_metsig2012 ) ;
      TH1F* h_met_2b_qcd         = new TH1F("h_met_2b_qcd"        , "met, 2b, qcd"        , bins_of_met, met_bin_edges_met ) ;
      TH1F* h_metovsqrtht_2b_qcd = new TH1F("h_metovsqrtht_2b_qcd", "metovsqrtht, 2b, qcd", bins_of_met, met_bin_edges_metovsqrtht ) ;

      h_metsig_2b_qcd -> Sumw2() ;
      h_metsig2012_2b_qcd -> Sumw2() ;
      h_met_2b_qcd -> Sumw2() ;
      h_metovsqrtht_2b_qcd -> Sumw2() ;



      TH1F* h_metsig_3b_qcd      = new TH1F("h_metsig_3b_qcd"     , "METsig, 3b, qcd"     , bins_of_met, met_bin_edges_metsig ) ;
      TH1F* h_metsig2012_3b_qcd  = new TH1F("h_metsig2012_3b_qcd" , "metsig2012, 3b, qcd" , bins_of_met, met_bin_edges_metsig2012 ) ;
      TH1F* h_met_3b_qcd         = new TH1F("h_met_3b_qcd"        , "met, 3b, qcd"        , bins_of_met, met_bin_edges_met ) ;
      TH1F* h_metovsqrtht_3b_qcd = new TH1F("h_metovsqrtht_3b_qcd", "metovsqrtht, 3b, qcd", bins_of_met, met_bin_edges_metovsqrtht ) ;

      h_metsig_3b_qcd -> Sumw2() ;
      h_metsig2012_3b_qcd -> Sumw2() ;
      h_met_3b_qcd -> Sumw2() ;
      h_metovsqrtht_3b_qcd -> Sumw2() ;



      TH1F* h_metsig_4b_qcd      = new TH1F("h_metsig_4b_qcd"     , "METsig, 4b, qcd"     , bins_of_met, met_bin_edges_metsig ) ;
      TH1F* h_metsig2012_4b_qcd  = new TH1F("h_metsig2012_4b_qcd" , "metsig2012, 4b, qcd" , bins_of_met, met_bin_edges_metsig2012 ) ;
      TH1F* h_met_4b_qcd         = new TH1F("h_met_4b_qcd"        , "met, 4b, qcd"        , bins_of_met, met_bin_edges_met ) ;
      TH1F* h_metovsqrtht_4b_qcd = new TH1F("h_metovsqrtht_4b_qcd", "metovsqrtht, 4b, qcd", bins_of_met, met_bin_edges_metovsqrtht ) ;

      h_metsig_4b_qcd -> Sumw2() ;
      h_metsig2012_4b_qcd -> Sumw2() ;
      h_met_4b_qcd -> Sumw2() ;
      h_metovsqrtht_4b_qcd -> Sumw2() ;



      TH1F* h_metsig_mindphicut_qcd      = new TH1F("h_metsig_mindphicut_qcd"     , "METsig, mindphicut, qcd"     , bins_of_met, met_bin_edges_metsig ) ;
      TH1F* h_metsig2012_mindphicut_qcd  = new TH1F("h_metsig2012_mindphicut_qcd" , "metsig2012, mindphicut, qcd" , bins_of_met, met_bin_edges_metsig2012 ) ;
      TH1F* h_met_mindphicut_qcd         = new TH1F("h_met_mindphicut_qcd"        , "met, mindphicut, qcd"        , bins_of_met, met_bin_edges_met ) ;
      TH1F* h_metovsqrtht_mindphicut_qcd = new TH1F("h_metovsqrtht_mindphicut_qcd", "metovsqrtht, mindphicut, qcd", bins_of_met, met_bin_edges_metovsqrtht ) ;

      h_metsig_mindphicut_qcd -> Sumw2() ;
      h_metsig2012_mindphicut_qcd -> Sumw2() ;
      h_met_mindphicut_qcd -> Sumw2() ;
      h_metovsqrtht_mindphicut_qcd -> Sumw2() ;




      TH1F* h_metsig_all_tt      = new TH1F("h_metsig_all_tt"     , "METsig, all, tt"     , bins_of_met, met_bin_edges_metsig ) ;
      TH1F* h_metsig2012_all_tt  = new TH1F("h_metsig2012_all_tt" , "metsig2012, all, tt" , bins_of_met, met_bin_edges_metsig2012 ) ;
      TH1F* h_met_all_tt         = new TH1F("h_met_all_tt"        , "met, all, tt"        , bins_of_met, met_bin_edges_met ) ;
      TH1F* h_metovsqrtht_all_tt = new TH1F("h_metovsqrtht_all_tt", "metovsqrtht, all, tt", bins_of_met, met_bin_edges_metovsqrtht ) ;

      h_metsig_all_tt -> Sumw2() ;
      h_metsig2012_all_tt -> Sumw2() ;
      h_met_all_tt -> Sumw2() ;
      h_metovsqrtht_all_tt -> Sumw2() ;



      TH1F* h_metsig_all_signal      = new TH1F("h_metsig_all_signal"     , "METsig, all, signal"     , bins_of_met, met_bin_edges_metsig ) ;
      TH1F* h_metsig2012_all_signal  = new TH1F("h_metsig2012_all_signal" , "metsig2012, all, signal" , bins_of_met, met_bin_edges_metsig2012 ) ;
      TH1F* h_met_all_signal         = new TH1F("h_met_all_signal"        , "met, all, signal"        , bins_of_met, met_bin_edges_met ) ;
      TH1F* h_metovsqrtht_all_signal = new TH1F("h_metovsqrtht_all_signal", "metovsqrtht, all, signal", bins_of_met, met_bin_edges_metovsqrtht ) ;

      h_metsig_all_signal -> Sumw2() ;
      h_metsig2012_all_signal -> Sumw2() ;
      h_met_all_signal -> Sumw2() ;
      h_metovsqrtht_all_signal -> Sumw2() ;



      TH1F* h_metsig_all_tthad      = new TH1F("h_metsig_all_tthad"     , "METsig, all, tthad"     , bins_of_met, met_bin_edges_metsig ) ;
      TH1F* h_metsig2012_all_tthad  = new TH1F("h_metsig2012_all_tthad" , "metsig2012, all, tthad" , bins_of_met, met_bin_edges_metsig2012 ) ;
      TH1F* h_met_all_tthad         = new TH1F("h_met_all_tthad"        , "met, all, tthad"        , bins_of_met, met_bin_edges_met ) ;
      TH1F* h_metovsqrtht_all_tthad = new TH1F("h_metovsqrtht_all_tthad", "metovsqrtht, all, tthad", bins_of_met, met_bin_edges_metovsqrtht ) ;

      h_metsig_all_tthad -> Sumw2() ;
      h_metsig2012_all_tthad -> Sumw2() ;
      h_met_all_tthad -> Sumw2() ;
      h_metovsqrtht_all_tthad -> Sumw2() ;


      TH1F* h_metsig_2b_tthad      = new TH1F("h_metsig_2b_tthad"     , "METsig, 2b, tthad"     , bins_of_met, met_bin_edges_metsig ) ;
      TH1F* h_metsig2012_2b_tthad  = new TH1F("h_metsig2012_2b_tthad" , "metsig2012, 2b, tthad" , bins_of_met, met_bin_edges_metsig2012 ) ;
      TH1F* h_met_2b_tthad         = new TH1F("h_met_2b_tthad"        , "met, 2b, tthad"        , bins_of_met, met_bin_edges_met ) ;
      TH1F* h_metovsqrtht_2b_tthad = new TH1F("h_metovsqrtht_2b_tthad", "metovsqrtht, 2b, tthad", bins_of_met, met_bin_edges_metovsqrtht ) ;

      h_metsig_2b_tthad -> Sumw2() ;
      h_metsig2012_2b_tthad -> Sumw2() ;
      h_met_2b_tthad -> Sumw2() ;
      h_metovsqrtht_2b_tthad -> Sumw2() ;



      TH1F* h_metsig_3b_tthad      = new TH1F("h_metsig_3b_tthad"     , "METsig, 3b, tthad"     , bins_of_met, met_bin_edges_metsig ) ;
      TH1F* h_metsig2012_3b_tthad  = new TH1F("h_metsig2012_3b_tthad" , "metsig2012, 3b, tthad" , bins_of_met, met_bin_edges_metsig2012 ) ;
      TH1F* h_met_3b_tthad         = new TH1F("h_met_3b_tthad"        , "met, 3b, tthad"        , bins_of_met, met_bin_edges_met ) ;
      TH1F* h_metovsqrtht_3b_tthad = new TH1F("h_metovsqrtht_3b_tthad", "metovsqrtht, 3b, tthad", bins_of_met, met_bin_edges_metovsqrtht ) ;

      h_metsig_3b_tthad -> Sumw2() ;
      h_metsig2012_3b_tthad -> Sumw2() ;
      h_met_3b_tthad -> Sumw2() ;
      h_metovsqrtht_3b_tthad -> Sumw2() ;



      TH1F* h_metsig_4b_tthad      = new TH1F("h_metsig_4b_tthad"     , "METsig, 4b, tthad"     , bins_of_met, met_bin_edges_metsig ) ;
      TH1F* h_metsig2012_4b_tthad  = new TH1F("h_metsig2012_4b_tthad" , "metsig2012, 4b, tthad" , bins_of_met, met_bin_edges_metsig2012 ) ;
      TH1F* h_met_4b_tthad         = new TH1F("h_met_4b_tthad"        , "met, 4b, tthad"        , bins_of_met, met_bin_edges_met ) ;
      TH1F* h_metovsqrtht_4b_tthad = new TH1F("h_metovsqrtht_4b_tthad", "metovsqrtht, 4b, tthad", bins_of_met, met_bin_edges_metovsqrtht ) ;

      h_metsig_4b_tthad -> Sumw2() ;
      h_metsig2012_4b_tthad -> Sumw2() ;
      h_met_4b_tthad -> Sumw2() ;
      h_metovsqrtht_4b_tthad -> Sumw2() ;



      TH1F* h_metsig_mindphicut_tthad      = new TH1F("h_metsig_mindphicut_tthad"     , "METsig, mindphicut, tthad"     , bins_of_met, met_bin_edges_metsig ) ;
      TH1F* h_metsig2012_mindphicut_tthad  = new TH1F("h_metsig2012_mindphicut_tthad" , "metsig2012, mindphicut, tthad" , bins_of_met, met_bin_edges_metsig2012 ) ;
      TH1F* h_met_mindphicut_tthad         = new TH1F("h_met_mindphicut_tthad"        , "met, mindphicut, tthad"        , bins_of_met, met_bin_edges_met ) ;
      TH1F* h_metovsqrtht_mindphicut_tthad = new TH1F("h_metovsqrtht_mindphicut_tthad", "metovsqrtht, mindphicut, tthad", bins_of_met, met_bin_edges_metovsqrtht ) ;

      h_metsig_mindphicut_tthad -> Sumw2() ;
      h_metsig2012_mindphicut_tthad -> Sumw2() ;
      h_met_mindphicut_tthad -> Sumw2() ;
      h_metovsqrtht_mindphicut_tthad -> Sumw2() ;




      float xshift(0.03) ;


      TCanvas* cdraw = new TCanvas("cdraw","MET var shapes", 600, 400 ) ;

      char arg1[1000] ;
      char allcuts[10000] ;



    //--- qcd, all

      sprintf( allcuts, "(%s)*weight3*%.0f", allcommoncuts, dataIntLumiIPB ) ;
      sprintf( arg1, "METsig>>h_metsig_all_qcd" ) ;
      bgcompchain[2] -> Draw( arg1, allcuts ) ;
      cdraw -> Update() ; cdraw -> Draw() ;

      sprintf( arg1, "METsig_2012>>h_metsig2012_all_qcd" ) ;
      bgcompchain[2] -> Draw( arg1, allcuts ) ;
      cdraw -> Update() ; cdraw -> Draw() ;

      sprintf( arg1, "MET>>h_met_all_qcd" ) ;
      bgcompchain[2] -> Draw( arg1, allcuts ) ;
      cdraw -> Update() ; cdraw -> Draw() ;

      sprintf( arg1, "MET/sqrt(HT30)>>h_metovsqrtht_all_qcd" ) ;
      bgcompchain[2] -> Draw( arg1, allcuts ) ;
      cdraw -> Update() ; cdraw -> Draw() ;

      addoverflow ( h_metsig_all_qcd ) ;
      addoverflow ( h_metsig2012_all_qcd ) ;
      addoverflow ( h_met_all_qcd ) ;
      addoverflow ( h_metovsqrtht_all_qcd ) ;

      TH1F* h_metsig_all_qcd_cbw = make_h_cbw( h_metsig_all_qcd, 3*xshift ) ;
      TH1F* h_metsig2012_all_qcd_cbw = make_h_cbw( h_metsig2012_all_qcd, 1*xshift ) ;
      TH1F* h_met_all_qcd_cbw = make_h_cbw( h_met_all_qcd, 2*xshift ) ;
      TH1F* h_metovsqrtht_all_qcd_cbw = make_h_cbw( h_metovsqrtht_all_qcd, 0*xshift ) ;



    //--- qcd, 2b

      sprintf( allcuts, "(%s&&(%s))*weight3*%.0f", allcommoncuts, btag2bcuts, dataIntLumiIPB ) ;
      sprintf( arg1, "METsig>>h_metsig_2b_qcd" ) ;
      bgcompchain[2] -> Draw( arg1, allcuts ) ;
      cdraw -> Update() ; cdraw -> Draw() ;

      sprintf( arg1, "METsig_2012>>h_metsig2012_2b_qcd" ) ;
      bgcompchain[2] -> Draw( arg1, allcuts ) ;
      cdraw -> Update() ; cdraw -> Draw() ;

      sprintf( arg1, "MET>>h_met_2b_qcd" ) ;
      bgcompchain[2] -> Draw( arg1, allcuts ) ;
      cdraw -> Update() ; cdraw -> Draw() ;

      sprintf( arg1, "MET/sqrt(HT30)>>h_metovsqrtht_2b_qcd" ) ;
      bgcompchain[2] -> Draw( arg1, allcuts ) ;
      cdraw -> Update() ; cdraw -> Draw() ;

      addoverflow ( h_metsig_2b_qcd ) ;
      addoverflow ( h_metsig2012_2b_qcd ) ;
      addoverflow ( h_met_2b_qcd ) ;
      addoverflow ( h_metovsqrtht_2b_qcd ) ;

      TH1F* h_metsig_2b_qcd_cbw = make_h_cbw( h_metsig_2b_qcd, 3*xshift ) ;
      TH1F* h_metsig2012_2b_qcd_cbw = make_h_cbw( h_metsig2012_2b_qcd, 1*xshift ) ;
      TH1F* h_met_2b_qcd_cbw = make_h_cbw( h_met_2b_qcd, 2*xshift ) ;
      TH1F* h_metovsqrtht_2b_qcd_cbw = make_h_cbw( h_metovsqrtht_2b_qcd, 0*xshift ) ;




    //--- qcd, 3b

      sprintf( allcuts, "(%s&&(%s))*weight3*%.0f", allcommoncuts, btag3bcuts, dataIntLumiIPB ) ;
      sprintf( arg1, "METsig>>h_metsig_3b_qcd" ) ;
      bgcompchain[2] -> Draw( arg1, allcuts ) ;
      cdraw -> Update() ; cdraw -> Draw() ;

      sprintf( arg1, "METsig_2012>>h_metsig2012_3b_qcd" ) ;
      bgcompchain[2] -> Draw( arg1, allcuts ) ;
      cdraw -> Update() ; cdraw -> Draw() ;

      sprintf( arg1, "MET>>h_met_3b_qcd" ) ;
      bgcompchain[2] -> Draw( arg1, allcuts ) ;
      cdraw -> Update() ; cdraw -> Draw() ;

      sprintf( arg1, "MET/sqrt(HT30)>>h_metovsqrtht_3b_qcd" ) ;
      bgcompchain[2] -> Draw( arg1, allcuts ) ;
      cdraw -> Update() ; cdraw -> Draw() ;

      addoverflow ( h_metsig_3b_qcd ) ;
      addoverflow ( h_metsig2012_3b_qcd ) ;
      addoverflow ( h_met_3b_qcd ) ;
      addoverflow ( h_metovsqrtht_3b_qcd ) ;

      TH1F* h_metsig_3b_qcd_cbw = make_h_cbw( h_metsig_3b_qcd, 3*xshift ) ;
      TH1F* h_metsig2012_3b_qcd_cbw = make_h_cbw( h_metsig2012_3b_qcd, 1*xshift ) ;
      TH1F* h_met_3b_qcd_cbw = make_h_cbw( h_met_3b_qcd, 2*xshift ) ;
      TH1F* h_metovsqrtht_3b_qcd_cbw = make_h_cbw( h_metovsqrtht_3b_qcd, 0*xshift ) ;




    //--- qcd, 4b

      sprintf( allcuts, "(%s&&(%s))*weight3*%.0f", allcommoncuts, btag4bcuts, dataIntLumiIPB ) ;
      sprintf( arg1, "METsig>>h_metsig_4b_qcd" ) ;
      bgcompchain[2] -> Draw( arg1, allcuts ) ;
      cdraw -> Update() ; cdraw -> Draw() ;

      sprintf( arg1, "METsig_2012>>h_metsig2012_4b_qcd" ) ;
      bgcompchain[2] -> Draw( arg1, allcuts ) ;
      cdraw -> Update() ; cdraw -> Draw() ;

      sprintf( arg1, "MET>>h_met_4b_qcd" ) ;
      bgcompchain[2] -> Draw( arg1, allcuts ) ;
      cdraw -> Update() ; cdraw -> Draw() ;

      sprintf( arg1, "MET/sqrt(HT30)>>h_metovsqrtht_4b_qcd" ) ;
      bgcompchain[2] -> Draw( arg1, allcuts ) ;
      cdraw -> Update() ; cdraw -> Draw() ;

      addoverflow ( h_metsig_4b_qcd ) ;
      addoverflow ( h_metsig2012_4b_qcd ) ;
      addoverflow ( h_met_4b_qcd ) ;
      addoverflow ( h_metovsqrtht_4b_qcd ) ;

      TH1F* h_metsig_4b_qcd_cbw = make_h_cbw( h_metsig_4b_qcd, 3*xshift ) ;
      TH1F* h_metsig2012_4b_qcd_cbw = make_h_cbw( h_metsig2012_4b_qcd, 1*xshift ) ;
      TH1F* h_met_4b_qcd_cbw = make_h_cbw( h_met_4b_qcd, 2*xshift ) ;
      TH1F* h_metovsqrtht_4b_qcd_cbw = make_h_cbw( h_metovsqrtht_4b_qcd, 0*xshift ) ;




    //--- qcd, mindphicut

      sprintf( allcuts, "(%s&&(%s))*weight3*%.0f", allcommoncuts, mindphicut, dataIntLumiIPB ) ;
      sprintf( arg1, "METsig>>h_metsig_mindphicut_qcd" ) ;
      bgcompchain[2] -> Draw( arg1, allcuts ) ;
      cdraw -> Update() ; cdraw -> Draw() ;

      sprintf( arg1, "METsig_2012>>h_metsig2012_mindphicut_qcd" ) ;
      bgcompchain[2] -> Draw( arg1, allcuts ) ;
      cdraw -> Update() ; cdraw -> Draw() ;

      sprintf( arg1, "MET>>h_met_mindphicut_qcd" ) ;
      bgcompchain[2] -> Draw( arg1, allcuts ) ;
      cdraw -> Update() ; cdraw -> Draw() ;

      sprintf( arg1, "MET/sqrt(HT30)>>h_metovsqrtht_mindphicut_qcd" ) ;
      bgcompchain[2] -> Draw( arg1, allcuts ) ;
      cdraw -> Update() ; cdraw -> Draw() ;

      addoverflow ( h_metsig_mindphicut_qcd ) ;
      addoverflow ( h_metsig2012_mindphicut_qcd ) ;
      addoverflow ( h_met_mindphicut_qcd ) ;
      addoverflow ( h_metovsqrtht_mindphicut_qcd ) ;

      TH1F* h_metsig_mindphicut_qcd_cbw = make_h_cbw( h_metsig_mindphicut_qcd, 3*xshift ) ;
      TH1F* h_metsig2012_mindphicut_qcd_cbw = make_h_cbw( h_metsig2012_mindphicut_qcd, 1*xshift ) ;
      TH1F* h_met_mindphicut_qcd_cbw = make_h_cbw( h_met_mindphicut_qcd, 2*xshift ) ;
      TH1F* h_metovsqrtht_mindphicut_qcd_cbw = make_h_cbw( h_metovsqrtht_mindphicut_qcd, 0*xshift ) ;




    //--- tt

      sprintf( allcuts, "(%s)*weight3*%.0f", allcommoncuts, dataIntLumiIPB ) ;
      sprintf( arg1, "METsig>>h_metsig_all_tt" ) ;
      bgcompchain[0] -> Draw( arg1, allcuts ) ;
      cdraw -> Update() ; cdraw -> Draw() ;

      sprintf( arg1, "METsig_2012>>h_metsig2012_all_tt" ) ;
      bgcompchain[0] -> Draw( arg1, allcuts ) ;
      cdraw -> Update() ; cdraw -> Draw() ;

      sprintf( arg1, "MET>>h_met_all_tt" ) ;
      bgcompchain[0] -> Draw( arg1, allcuts ) ;
      cdraw -> Update() ; cdraw -> Draw() ;

      sprintf( arg1, "MET/sqrt(HT30)>>h_metovsqrtht_all_tt" ) ;
      bgcompchain[0] -> Draw( arg1, allcuts ) ;
      cdraw -> Update() ; cdraw -> Draw() ;

      addoverflow ( h_metsig_all_tt ) ;
      addoverflow ( h_metsig2012_all_tt ) ;
      addoverflow ( h_met_all_tt ) ;
      addoverflow ( h_metovsqrtht_all_tt ) ;

      TH1F* h_metsig_all_tt_cbw = make_h_cbw( h_metsig_all_tt, 3*xshift ) ;
      TH1F* h_metsig2012_all_tt_cbw = make_h_cbw( h_metsig2012_all_tt, 1*xshift ) ;
      TH1F* h_met_all_tt_cbw = make_h_cbw( h_met_all_tt, 2*xshift ) ;
      TH1F* h_metovsqrtht_all_tt_cbw = make_h_cbw( h_metovsqrtht_all_tt, 0*xshift ) ;




    //--- signal

      sprintf( allcuts, "(%s)*%f*%.0f", allcommoncuts, signal_weight, dataIntLumiIPB ) ;
      sprintf( arg1, "METsig>>h_metsig_all_signal" ) ;
      sigchain -> Draw( arg1, allcuts ) ;
      cdraw -> Update() ; cdraw -> Draw() ;

      sprintf( arg1, "METsig_2012>>h_metsig2012_all_signal" ) ;
      sigchain -> Draw( arg1, allcuts ) ;
      cdraw -> Update() ; cdraw -> Draw() ;

      sprintf( arg1, "MET>>h_met_all_signal" ) ;
      sigchain -> Draw( arg1, allcuts ) ;
      cdraw -> Update() ; cdraw -> Draw() ;

      sprintf( arg1, "MET/sqrt(HT30)>>h_metovsqrtht_all_signal" ) ;
      sigchain -> Draw( arg1, allcuts ) ;
      cdraw -> Update() ; cdraw -> Draw() ;

      addoverflow ( h_metsig_all_signal ) ;
      addoverflow ( h_metsig2012_all_signal ) ;
      addoverflow ( h_met_all_signal ) ;
      addoverflow ( h_metovsqrtht_all_signal ) ;

      TH1F* h_metsig_all_signal_cbw = make_h_cbw( h_metsig_all_signal, 3*xshift ) ;
      TH1F* h_metsig2012_all_signal_cbw = make_h_cbw( h_metsig2012_all_signal, 1*xshift ) ;
      TH1F* h_met_all_signal_cbw = make_h_cbw( h_met_all_signal, 2*xshift ) ;
      TH1F* h_metovsqrtht_all_signal_cbw = make_h_cbw( h_metovsqrtht_all_signal, 0*xshift ) ;




    //--- tthad, all

      sprintf( allcuts, "(%s)*weight3*%.0f", allcommoncuts, dataIntLumiIPB ) ;
      sprintf( arg1, "METsig>>h_metsig_all_tthad" ) ;
      bgcompchain[3] -> Draw( arg1, allcuts ) ;
      cdraw -> Update() ; cdraw -> Draw() ;

      sprintf( arg1, "METsig_2012>>h_metsig2012_all_tthad" ) ;
      bgcompchain[3] -> Draw( arg1, allcuts ) ;
      cdraw -> Update() ; cdraw -> Draw() ;

      sprintf( arg1, "MET>>h_met_all_tthad" ) ;
      bgcompchain[3] -> Draw( arg1, allcuts ) ;
      cdraw -> Update() ; cdraw -> Draw() ;

      sprintf( arg1, "MET/sqrt(HT30)>>h_metovsqrtht_all_tthad" ) ;
      bgcompchain[3] -> Draw( arg1, allcuts ) ;
      cdraw -> Update() ; cdraw -> Draw() ;

      addoverflow ( h_metsig_all_tthad ) ;
      addoverflow ( h_metsig2012_all_tthad ) ;
      addoverflow ( h_met_all_tthad ) ;
      addoverflow ( h_metovsqrtht_all_tthad ) ;

      TH1F* h_metsig_all_tthad_cbw = make_h_cbw( h_metsig_all_tthad, 3*xshift ) ;
      TH1F* h_metsig2012_all_tthad_cbw = make_h_cbw( h_metsig2012_all_tthad, 1*xshift ) ;
      TH1F* h_met_all_tthad_cbw = make_h_cbw( h_met_all_tthad, 2*xshift ) ;
      TH1F* h_metovsqrtht_all_tthad_cbw = make_h_cbw( h_metovsqrtht_all_tthad, 0*xshift ) ;



    //--- tthad, 2b

      sprintf( allcuts, "(%s&&(%s))*weight3*%.0f", allcommoncuts, btag2bcuts, dataIntLumiIPB ) ;
      sprintf( arg1, "METsig>>h_metsig_2b_tthad" ) ;
      bgcompchain[3] -> Draw( arg1, allcuts ) ;
      cdraw -> Update() ; cdraw -> Draw() ;

      sprintf( arg1, "METsig_2012>>h_metsig2012_2b_tthad" ) ;
      bgcompchain[3] -> Draw( arg1, allcuts ) ;
      cdraw -> Update() ; cdraw -> Draw() ;

      sprintf( arg1, "MET>>h_met_2b_tthad" ) ;
      bgcompchain[3] -> Draw( arg1, allcuts ) ;
      cdraw -> Update() ; cdraw -> Draw() ;

      sprintf( arg1, "MET/sqrt(HT30)>>h_metovsqrtht_2b_tthad" ) ;
      bgcompchain[3] -> Draw( arg1, allcuts ) ;
      cdraw -> Update() ; cdraw -> Draw() ;

      addoverflow ( h_metsig_2b_tthad ) ;
      addoverflow ( h_metsig2012_2b_tthad ) ;
      addoverflow ( h_met_2b_tthad ) ;
      addoverflow ( h_metovsqrtht_2b_tthad ) ;

      TH1F* h_metsig_2b_tthad_cbw = make_h_cbw( h_metsig_2b_tthad, 3*xshift ) ;
      TH1F* h_metsig2012_2b_tthad_cbw = make_h_cbw( h_metsig2012_2b_tthad, 1*xshift ) ;
      TH1F* h_met_2b_tthad_cbw = make_h_cbw( h_met_2b_tthad, 2*xshift ) ;
      TH1F* h_metovsqrtht_2b_tthad_cbw = make_h_cbw( h_metovsqrtht_2b_tthad, 0*xshift ) ;




    //--- tthad, 3b

      sprintf( allcuts, "(%s&&(%s))*weight3*%.0f", allcommoncuts, btag3bcuts, dataIntLumiIPB ) ;
      sprintf( arg1, "METsig>>h_metsig_3b_tthad" ) ;
      bgcompchain[3] -> Draw( arg1, allcuts ) ;
      cdraw -> Update() ; cdraw -> Draw() ;

      sprintf( arg1, "METsig_2012>>h_metsig2012_3b_tthad" ) ;
      bgcompchain[3] -> Draw( arg1, allcuts ) ;
      cdraw -> Update() ; cdraw -> Draw() ;

      sprintf( arg1, "MET>>h_met_3b_tthad" ) ;
      bgcompchain[3] -> Draw( arg1, allcuts ) ;
      cdraw -> Update() ; cdraw -> Draw() ;

      sprintf( arg1, "MET/sqrt(HT30)>>h_metovsqrtht_3b_tthad" ) ;
      bgcompchain[3] -> Draw( arg1, allcuts ) ;
      cdraw -> Update() ; cdraw -> Draw() ;

      addoverflow ( h_metsig_3b_tthad ) ;
      addoverflow ( h_metsig2012_3b_tthad ) ;
      addoverflow ( h_met_3b_tthad ) ;
      addoverflow ( h_metovsqrtht_3b_tthad ) ;

      TH1F* h_metsig_3b_tthad_cbw = make_h_cbw( h_metsig_3b_tthad, 3*xshift ) ;
      TH1F* h_metsig2012_3b_tthad_cbw = make_h_cbw( h_metsig2012_3b_tthad, 1*xshift ) ;
      TH1F* h_met_3b_tthad_cbw = make_h_cbw( h_met_3b_tthad, 2*xshift ) ;
      TH1F* h_metovsqrtht_3b_tthad_cbw = make_h_cbw( h_metovsqrtht_3b_tthad, 0*xshift ) ;




    //--- tthad, 4b

      sprintf( allcuts, "(%s&&(%s))*weight3*%.0f", allcommoncuts, btag4bcuts, dataIntLumiIPB ) ;
      sprintf( arg1, "METsig>>h_metsig_4b_tthad" ) ;
      bgcompchain[3] -> Draw( arg1, allcuts ) ;
      cdraw -> Update() ; cdraw -> Draw() ;

      sprintf( arg1, "METsig_2012>>h_metsig2012_4b_tthad" ) ;
      bgcompchain[3] -> Draw( arg1, allcuts ) ;
      cdraw -> Update() ; cdraw -> Draw() ;

      sprintf( arg1, "MET>>h_met_4b_tthad" ) ;
      bgcompchain[3] -> Draw( arg1, allcuts ) ;
      cdraw -> Update() ; cdraw -> Draw() ;

      sprintf( arg1, "MET/sqrt(HT30)>>h_metovsqrtht_4b_tthad" ) ;
      bgcompchain[3] -> Draw( arg1, allcuts ) ;
      cdraw -> Update() ; cdraw -> Draw() ;

      addoverflow ( h_metsig_4b_tthad ) ;
      addoverflow ( h_metsig2012_4b_tthad ) ;
      addoverflow ( h_met_4b_tthad ) ;
      addoverflow ( h_metovsqrtht_4b_tthad ) ;

      TH1F* h_metsig_4b_tthad_cbw = make_h_cbw( h_metsig_4b_tthad, 3*xshift ) ;
      TH1F* h_metsig2012_4b_tthad_cbw = make_h_cbw( h_metsig2012_4b_tthad, 1*xshift ) ;
      TH1F* h_met_4b_tthad_cbw = make_h_cbw( h_met_4b_tthad, 2*xshift ) ;
      TH1F* h_metovsqrtht_4b_tthad_cbw = make_h_cbw( h_metovsqrtht_4b_tthad, 0*xshift ) ;




    //--- tthad, mindphicut

      sprintf( allcuts, "(%s&&(%s))*weight3*%.0f", allcommoncuts, mindphicut, dataIntLumiIPB ) ;
      sprintf( arg1, "METsig>>h_metsig_mindphicut_tthad" ) ;
      bgcompchain[3] -> Draw( arg1, allcuts ) ;
      cdraw -> Update() ; cdraw -> Draw() ;

      sprintf( arg1, "METsig_2012>>h_metsig2012_mindphicut_tthad" ) ;
      bgcompchain[3] -> Draw( arg1, allcuts ) ;
      cdraw -> Update() ; cdraw -> Draw() ;

      sprintf( arg1, "MET>>h_met_mindphicut_tthad" ) ;
      bgcompchain[3] -> Draw( arg1, allcuts ) ;
      cdraw -> Update() ; cdraw -> Draw() ;

      sprintf( arg1, "MET/sqrt(HT30)>>h_metovsqrtht_mindphicut_tthad" ) ;
      bgcompchain[3] -> Draw( arg1, allcuts ) ;
      cdraw -> Update() ; cdraw -> Draw() ;

      addoverflow ( h_metsig_mindphicut_tthad ) ;
      addoverflow ( h_metsig2012_mindphicut_tthad ) ;
      addoverflow ( h_met_mindphicut_tthad ) ;
      addoverflow ( h_metovsqrtht_mindphicut_tthad ) ;

      TH1F* h_metsig_mindphicut_tthad_cbw = make_h_cbw( h_metsig_mindphicut_tthad, 3*xshift ) ;
      TH1F* h_metsig2012_mindphicut_tthad_cbw = make_h_cbw( h_metsig2012_mindphicut_tthad, 1*xshift ) ;
      TH1F* h_met_mindphicut_tthad_cbw = make_h_cbw( h_met_mindphicut_tthad, 2*xshift ) ;
      TH1F* h_metovsqrtht_mindphicut_tthad_cbw = make_h_cbw( h_metovsqrtht_mindphicut_tthad, 0*xshift ) ;
















    //====== Drawing below here


      TLegend* legend = new TLegend( 0.75, 0.75, 0.98, 0.98 ) ;
      legend -> SetFillColor( kWhite ) ;
      legend -> AddEntry( h_metsig_all_qcd_cbw, "METsig" ) ;
      legend -> AddEntry( h_metsig2012_all_qcd_cbw, "METsig2012" ) ;
      legend -> AddEntry( h_met_all_qcd_cbw, "MET" ) ;
      legend -> AddEntry( h_metovsqrtht_all_qcd_cbw, "MET/sqrt(HT)" ) ;



    //---- qcd, all

      TCanvas* c_qcd_all = new TCanvas("c_qcd_all", "QCD, all", 600, 400 ) ;

      h_metsig_all_qcd_cbw -> SetLineColor(4) ;
      h_metsig2012_all_qcd_cbw -> SetLineColor(1) ;
      h_met_all_qcd_cbw -> SetLineColor(2) ;
      h_metovsqrtht_all_qcd_cbw -> SetLineColor(3) ;

      h_metsig_all_qcd_cbw -> SetLineWidth(2) ;
      h_metsig2012_all_qcd_cbw -> SetLineWidth(2) ;
      h_met_all_qcd_cbw -> SetLineWidth(2) ;
      h_metovsqrtht_all_qcd_cbw -> SetLineWidth(2) ;


  //  h_metsig_all_qcd_cbw -> Scale( 1./(h_metsig_all_qcd->Integral()) ) ;
  //  h_metsig2012_all_qcd_cbw -> Scale( 1./(h_metsig2012_all_qcd->Integral()) ) ;
  //  h_met_all_qcd_cbw -> Scale( 1./(h_met_all_qcd->Integral()) ) ;
  //  h_metovsqrtht_all_qcd_cbw -> Scale( 1./(h_metovsqrtht_all_qcd->Integral()) ) ;


  //  h_metsig_all_qcd_cbw -> SetMaximum(0.50) ;
      h_metsig_all_qcd_cbw -> Draw( "hist" ) ;
      h_metsig_all_qcd_cbw -> Draw( "same" ) ;

      h_metsig2012_all_qcd_cbw -> Draw( "hist same" ) ;
      h_metsig2012_all_qcd_cbw -> Draw( "same" ) ;

      h_met_all_qcd_cbw -> Draw( "hist same" ) ;
      h_met_all_qcd_cbw -> Draw( "same" ) ;

      h_metovsqrtht_all_qcd_cbw -> Draw( "hist same" ) ;
      h_metovsqrtht_all_qcd_cbw -> Draw( "same" ) ;

      legend -> Draw() ;

      c_qcd_all -> Update() ;

      c_qcd_all -> SaveAs( "outputfiles/metvars-qcd-all.pdf" ) ;


    //---- qcd, 2b

      TCanvas* c_qcd_2b = new TCanvas("c_qcd_2b", "QCD, 2b", 600, 400 ) ;

      h_metsig_2b_qcd_cbw -> SetLineColor(4) ;
      h_metsig2012_2b_qcd_cbw -> SetLineColor(1) ;
      h_met_2b_qcd_cbw -> SetLineColor(2) ;
      h_metovsqrtht_2b_qcd_cbw -> SetLineColor(3) ;

      h_metsig_2b_qcd_cbw -> SetLineWidth(2) ;
      h_metsig2012_2b_qcd_cbw -> SetLineWidth(2) ;
      h_met_2b_qcd_cbw -> SetLineWidth(2) ;
      h_metovsqrtht_2b_qcd_cbw -> SetLineWidth(2) ;


  //  h_metsig_2b_qcd_cbw -> Scale( 1./(h_metsig_2b_qcd->Integral()) ) ;
  //  h_metsig2012_2b_qcd_cbw -> Scale( 1./(h_metsig2012_2b_qcd->Integral()) ) ;
  //  h_met_2b_qcd_cbw -> Scale( 1./(h_met_2b_qcd->Integral()) ) ;
  //  h_metovsqrtht_2b_qcd_cbw -> Scale( 1./(h_metovsqrtht_2b_qcd->Integral()) ) ;


  //  h_metsig_2b_qcd_cbw -> SetMaximum(0.50) ;
      h_metsig_2b_qcd_cbw -> Draw( "hist" ) ;
      h_metsig_2b_qcd_cbw -> Draw( "same" ) ;

      h_metsig2012_2b_qcd_cbw -> Draw( "hist same" ) ;
      h_metsig2012_2b_qcd_cbw -> Draw( "same" ) ;

      h_met_2b_qcd_cbw -> Draw( "hist same" ) ;
      h_met_2b_qcd_cbw -> Draw( "same" ) ;

      h_metovsqrtht_2b_qcd_cbw -> Draw( "hist same" ) ;
      h_metovsqrtht_2b_qcd_cbw -> Draw( "same" ) ;

      legend -> Draw() ;

      c_qcd_2b -> Update() ;

      c_qcd_2b -> SaveAs( "outputfiles/metvars-qcd-2b.pdf" ) ;

    //---- qcd, 3b

      TCanvas* c_qcd_3b = new TCanvas("c_qcd_3b", "QCD, 3b", 600, 400 ) ;

      h_metsig_3b_qcd_cbw -> SetLineColor(4) ;
      h_metsig2012_3b_qcd_cbw -> SetLineColor(1) ;
      h_met_3b_qcd_cbw -> SetLineColor(2) ;
      h_metovsqrtht_3b_qcd_cbw -> SetLineColor(3) ;

      h_metsig_3b_qcd_cbw -> SetLineWidth(2) ;
      h_metsig2012_3b_qcd_cbw -> SetLineWidth(2) ;
      h_met_3b_qcd_cbw -> SetLineWidth(2) ;
      h_metovsqrtht_3b_qcd_cbw -> SetLineWidth(2) ;


  //  h_metsig_3b_qcd_cbw -> Scale( 1./(h_metsig_3b_qcd->Integral()) ) ;
  //  h_metsig2012_3b_qcd_cbw -> Scale( 1./(h_metsig2012_3b_qcd->Integral()) ) ;
  //  h_met_3b_qcd_cbw -> Scale( 1./(h_met_3b_qcd->Integral()) ) ;
  //  h_metovsqrtht_3b_qcd_cbw -> Scale( 1./(h_metovsqrtht_3b_qcd->Integral()) ) ;


  //  h_metsig_3b_qcd_cbw -> SetMaximum(0.50) ;
      h_metsig_3b_qcd_cbw -> Draw( "hist" ) ;
      h_metsig_3b_qcd_cbw -> Draw( "same" ) ;

      h_metsig2012_3b_qcd_cbw -> Draw( "hist same" ) ;
      h_metsig2012_3b_qcd_cbw -> Draw( "same" ) ;

      h_met_3b_qcd_cbw -> Draw( "hist same" ) ;
      h_met_3b_qcd_cbw -> Draw( "same" ) ;

      h_metovsqrtht_3b_qcd_cbw -> Draw( "hist same" ) ;
      h_metovsqrtht_3b_qcd_cbw -> Draw( "same" ) ;

      legend -> Draw() ;

      c_qcd_3b -> Update() ;

      c_qcd_3b -> SaveAs( "outputfiles/metvars-qcd-3b.pdf" ) ;




    //---- qcd, 4b

      TCanvas* c_qcd_4b = new TCanvas("c_qcd_4b", "QCD, 4b", 600, 400 ) ;

      h_metsig_4b_qcd_cbw -> SetLineColor(4) ;
      h_metsig2012_4b_qcd_cbw -> SetLineColor(1) ;
      h_met_4b_qcd_cbw -> SetLineColor(2) ;
      h_metovsqrtht_4b_qcd_cbw -> SetLineColor(3) ;

      h_metsig_4b_qcd_cbw -> SetLineWidth(2) ;
      h_metsig2012_4b_qcd_cbw -> SetLineWidth(2) ;
      h_met_4b_qcd_cbw -> SetLineWidth(2) ;
      h_metovsqrtht_4b_qcd_cbw -> SetLineWidth(2) ;


  //  h_metsig_4b_qcd_cbw -> Scale( 1./(h_metsig_4b_qcd->Integral()) ) ;
  //  h_metsig2012_4b_qcd_cbw -> Scale( 1./(h_metsig2012_4b_qcd->Integral()) ) ;
  //  h_met_4b_qcd_cbw -> Scale( 1./(h_met_4b_qcd->Integral()) ) ;
  //  h_metovsqrtht_4b_qcd_cbw -> Scale( 1./(h_metovsqrtht_4b_qcd->Integral()) ) ;


  //  h_metsig_4b_qcd_cbw -> SetMaximum(0.50) ;
      h_metsig_4b_qcd_cbw -> Draw( "hist" ) ;
      h_metsig_4b_qcd_cbw -> Draw( "same" ) ;

      h_metsig2012_4b_qcd_cbw -> Draw( "hist same" ) ;
      h_metsig2012_4b_qcd_cbw -> Draw( "same" ) ;

      h_met_4b_qcd_cbw -> Draw( "hist same" ) ;
      h_met_4b_qcd_cbw -> Draw( "same" ) ;

      h_metovsqrtht_4b_qcd_cbw -> Draw( "hist same" ) ;
      h_metovsqrtht_4b_qcd_cbw -> Draw( "same" ) ;

      legend -> Draw() ;

      c_qcd_4b -> Update() ;

      c_qcd_4b -> SaveAs( "outputfiles/metvars-qcd-4b.pdf" ) ;


    //---- qcd, mindphicut

      TCanvas* c_qcd_mindphicut = new TCanvas("c_qcd_mindphicut", "QCD, mindphicut", 600, 400 ) ;

      h_metsig_mindphicut_qcd_cbw -> SetLineColor(4) ;
      h_metsig2012_mindphicut_qcd_cbw -> SetLineColor(1) ;
      h_met_mindphicut_qcd_cbw -> SetLineColor(2) ;
      h_metovsqrtht_mindphicut_qcd_cbw -> SetLineColor(3) ;

      h_metsig_mindphicut_qcd_cbw -> SetLineWidth(2) ;
      h_metsig2012_mindphicut_qcd_cbw -> SetLineWidth(2) ;
      h_met_mindphicut_qcd_cbw -> SetLineWidth(2) ;
      h_metovsqrtht_mindphicut_qcd_cbw -> SetLineWidth(2) ;


  //  h_metsig_mindphicut_qcd_cbw -> Scale( 1./(h_metsig_mindphicut_qcd->Integral()) ) ;
  //  h_metsig2012_mindphicut_qcd_cbw -> Scale( 1./(h_metsig2012_mindphicut_qcd->Integral()) ) ;
  //  h_met_mindphicut_qcd_cbw -> Scale( 1./(h_met_mindphicut_qcd->Integral()) ) ;
  //  h_metovsqrtht_mindphicut_qcd_cbw -> Scale( 1./(h_metovsqrtht_mindphicut_qcd->Integral()) ) ;


  //  h_metsig_mindphicut_qcd_cbw -> SetMaximum(0.50) ;
      h_metsig_mindphicut_qcd_cbw -> Draw( "hist" ) ;
      h_metsig_mindphicut_qcd_cbw -> Draw( "same" ) ;

      h_metsig2012_mindphicut_qcd_cbw -> Draw( "hist same" ) ;
      h_metsig2012_mindphicut_qcd_cbw -> Draw( "same" ) ;

      h_met_mindphicut_qcd_cbw -> Draw( "hist same" ) ;
      h_met_mindphicut_qcd_cbw -> Draw( "same" ) ;

      h_metovsqrtht_mindphicut_qcd_cbw -> Draw( "hist same" ) ;
      h_metovsqrtht_mindphicut_qcd_cbw -> Draw( "same" ) ;

      legend -> Draw() ;

      c_qcd_mindphicut -> Update() ;

      c_qcd_mindphicut -> SaveAs( "outputfiles/metvars-qcd-mindphicut.pdf" ) ;





    //----

      TCanvas* c_tt_all = new TCanvas("c_tt_all", "tt", 600, 400 ) ;

      h_metsig_all_tt_cbw -> SetLineColor(4) ;
      h_metsig2012_all_tt_cbw -> SetLineColor(1) ;
      h_met_all_tt_cbw -> SetLineColor(2) ;
      h_metovsqrtht_all_tt_cbw -> SetLineColor(3) ;

      h_metsig_all_tt_cbw -> SetLineWidth(2) ;
      h_metsig2012_all_tt_cbw -> SetLineWidth(2) ;
      h_met_all_tt_cbw -> SetLineWidth(2) ;
      h_metovsqrtht_all_tt_cbw -> SetLineWidth(2) ;


  //  h_metsig_all_tt_cbw -> Scale( 1./(h_metsig_all_tt->Integral()) ) ;
  //  h_metsig2012_all_tt_cbw -> Scale( 1./(h_metsig2012_all_tt->Integral()) ) ;
  //  h_met_all_tt_cbw -> Scale( 1./(h_met_all_tt->Integral()) ) ;
  //  h_metovsqrtht_all_tt_cbw -> Scale( 1./(h_metovsqrtht_all_tt->Integral()) ) ;


  //  h_metsig_all_tt_cbw -> SetMaximum(0.50) ;
      h_metsig_all_tt_cbw -> Draw( "hist" ) ;
      h_metsig_all_tt_cbw -> Draw( "same" ) ;

      h_metsig2012_all_tt_cbw -> Draw( "hist same" ) ;
      h_metsig2012_all_tt_cbw -> Draw( "same" ) ;

      h_met_all_tt_cbw -> Draw( "hist same" ) ;
      h_met_all_tt_cbw -> Draw( "same" ) ;

      h_metovsqrtht_all_tt_cbw -> Draw( "hist same" ) ;
      h_metovsqrtht_all_tt_cbw -> Draw( "same" ) ;

      legend -> Draw() ;

      c_tt_all -> Update() ;

      c_tt_all -> SaveAs( "outputfiles/metvars-tt-all.pdf" ) ;


    //----

      TCanvas* c_signal_all = new TCanvas("c_signal_all", "signal", 600, 400 ) ;

      h_metsig_all_signal_cbw -> SetLineColor(4) ;
      h_metsig2012_all_signal_cbw -> SetLineColor(1) ;
      h_met_all_signal_cbw -> SetLineColor(2) ;
      h_metovsqrtht_all_signal_cbw -> SetLineColor(3) ;

      h_metsig_all_signal_cbw -> SetLineWidth(2) ;
      h_metsig2012_all_signal_cbw -> SetLineWidth(2) ;
      h_met_all_signal_cbw -> SetLineWidth(2) ;
      h_metovsqrtht_all_signal_cbw -> SetLineWidth(2) ;


   // h_metsig_all_signal_cbw -> Scale( 1./(h_metsig_all_signal->Integral()) ) ;
   // h_metsig2012_all_signal_cbw -> Scale( 1./(h_metsig2012_all_signal->Integral()) ) ;
   // h_met_all_signal_cbw -> Scale( 1./(h_met_all_signal->Integral()) ) ;
   // h_metovsqrtht_all_signal_cbw -> Scale( 1./(h_metovsqrtht_all_signal->Integral()) ) ;


   // h_metsig_all_signal_cbw -> SetMaximum(0.50) ;
      h_metsig_all_signal_cbw -> Draw( "hist" ) ;
      h_metsig_all_signal_cbw -> Draw( "same" ) ;

      h_metsig2012_all_signal_cbw -> Draw( "hist same" ) ;
      h_metsig2012_all_signal_cbw -> Draw( "same" ) ;

      h_met_all_signal_cbw -> Draw( "hist same" ) ;
      h_met_all_signal_cbw -> Draw( "same" ) ;

      h_metovsqrtht_all_signal_cbw -> Draw( "hist same" ) ;
      h_metovsqrtht_all_signal_cbw -> Draw( "same" ) ;

      legend -> Draw() ;

      c_signal_all -> Update() ;

      c_signal_all -> SaveAs( "outputfiles/metvars-signal-all.pdf" ) ;


    //---- tthad, all

      TCanvas* c_tthad_all = new TCanvas("c_tthad_all", "tthad, all", 600, 400 ) ;

      h_metsig_all_tthad_cbw -> SetLineColor(4) ;
      h_metsig2012_all_tthad_cbw -> SetLineColor(1) ;
      h_met_all_tthad_cbw -> SetLineColor(2) ;
      h_metovsqrtht_all_tthad_cbw -> SetLineColor(3) ;

      h_metsig_all_tthad_cbw -> SetLineWidth(2) ;
      h_metsig2012_all_tthad_cbw -> SetLineWidth(2) ;
      h_met_all_tthad_cbw -> SetLineWidth(2) ;
      h_metovsqrtht_all_tthad_cbw -> SetLineWidth(2) ;


  //  h_metsig_all_tthad_cbw -> Scale( 1./(h_metsig_all_tthad->Integral()) ) ;
  //  h_metsig2012_all_tthad_cbw -> Scale( 1./(h_metsig2012_all_tthad->Integral()) ) ;
  //  h_met_all_tthad_cbw -> Scale( 1./(h_met_all_tthad->Integral()) ) ;
  //  h_metovsqrtht_all_tthad_cbw -> Scale( 1./(h_metovsqrtht_all_tthad->Integral()) ) ;


  //  h_metsig_all_tthad_cbw -> SetMaximum(0.50) ;
      h_metsig_all_tthad_cbw -> Draw( "hist" ) ;
      h_metsig_all_tthad_cbw -> Draw( "same" ) ;

      h_metsig2012_all_tthad_cbw -> Draw( "hist same" ) ;
      h_metsig2012_all_tthad_cbw -> Draw( "same" ) ;

      h_met_all_tthad_cbw -> Draw( "hist same" ) ;
      h_met_all_tthad_cbw -> Draw( "same" ) ;

      h_metovsqrtht_all_tthad_cbw -> Draw( "hist same" ) ;
      h_metovsqrtht_all_tthad_cbw -> Draw( "same" ) ;

      legend -> Draw() ;

      c_tthad_all -> Update() ;

      c_tthad_all -> SaveAs( "outputfiles/metvars-tthad-all.pdf" ) ;


    //---- tthad, 2b

      TCanvas* c_tthad_2b = new TCanvas("c_tthad_2b", "tthad, 2b", 600, 400 ) ;

      h_metsig_2b_tthad_cbw -> SetLineColor(4) ;
      h_metsig2012_2b_tthad_cbw -> SetLineColor(1) ;
      h_met_2b_tthad_cbw -> SetLineColor(2) ;
      h_metovsqrtht_2b_tthad_cbw -> SetLineColor(3) ;

      h_metsig_2b_tthad_cbw -> SetLineWidth(2) ;
      h_metsig2012_2b_tthad_cbw -> SetLineWidth(2) ;
      h_met_2b_tthad_cbw -> SetLineWidth(2) ;
      h_metovsqrtht_2b_tthad_cbw -> SetLineWidth(2) ;


  //  h_metsig_2b_tthad_cbw -> Scale( 1./(h_metsig_2b_tthad->Integral()) ) ;
  //  h_metsig2012_2b_tthad_cbw -> Scale( 1./(h_metsig2012_2b_tthad->Integral()) ) ;
  //  h_met_2b_tthad_cbw -> Scale( 1./(h_met_2b_tthad->Integral()) ) ;
  //  h_metovsqrtht_2b_tthad_cbw -> Scale( 1./(h_metovsqrtht_2b_tthad->Integral()) ) ;


  //  h_metsig_2b_tthad_cbw -> SetMaximum(0.50) ;
      h_metsig_2b_tthad_cbw -> Draw( "hist" ) ;
      h_metsig_2b_tthad_cbw -> Draw( "same" ) ;

      h_metsig2012_2b_tthad_cbw -> Draw( "hist same" ) ;
      h_metsig2012_2b_tthad_cbw -> Draw( "same" ) ;

      h_met_2b_tthad_cbw -> Draw( "hist same" ) ;
      h_met_2b_tthad_cbw -> Draw( "same" ) ;

      h_metovsqrtht_2b_tthad_cbw -> Draw( "hist same" ) ;
      h_metovsqrtht_2b_tthad_cbw -> Draw( "same" ) ;

      legend -> Draw() ;

      c_tthad_2b -> Update() ;

      c_tthad_2b -> SaveAs( "outputfiles/metvars-tthad-2b.pdf" ) ;

    //---- tthad, 3b

      TCanvas* c_tthad_3b = new TCanvas("c_tthad_3b", "tthad, 3b", 600, 400 ) ;

      h_metsig_3b_tthad_cbw -> SetLineColor(4) ;
      h_metsig2012_3b_tthad_cbw -> SetLineColor(1) ;
      h_met_3b_tthad_cbw -> SetLineColor(2) ;
      h_metovsqrtht_3b_tthad_cbw -> SetLineColor(3) ;

      h_metsig_3b_tthad_cbw -> SetLineWidth(2) ;
      h_metsig2012_3b_tthad_cbw -> SetLineWidth(2) ;
      h_met_3b_tthad_cbw -> SetLineWidth(2) ;
      h_metovsqrtht_3b_tthad_cbw -> SetLineWidth(2) ;


  //  h_metsig_3b_tthad_cbw -> Scale( 1./(h_metsig_3b_tthad->Integral()) ) ;
  //  h_metsig2012_3b_tthad_cbw -> Scale( 1./(h_metsig2012_3b_tthad->Integral()) ) ;
  //  h_met_3b_tthad_cbw -> Scale( 1./(h_met_3b_tthad->Integral()) ) ;
  //  h_metovsqrtht_3b_tthad_cbw -> Scale( 1./(h_metovsqrtht_3b_tthad->Integral()) ) ;


  //  h_metsig_3b_tthad_cbw -> SetMaximum(0.50) ;
      h_metsig_3b_tthad_cbw -> Draw( "hist" ) ;
      h_metsig_3b_tthad_cbw -> Draw( "same" ) ;

      h_metsig2012_3b_tthad_cbw -> Draw( "hist same" ) ;
      h_metsig2012_3b_tthad_cbw -> Draw( "same" ) ;

      h_met_3b_tthad_cbw -> Draw( "hist same" ) ;
      h_met_3b_tthad_cbw -> Draw( "same" ) ;

      h_metovsqrtht_3b_tthad_cbw -> Draw( "hist same" ) ;
      h_metovsqrtht_3b_tthad_cbw -> Draw( "same" ) ;

      legend -> Draw() ;

      c_tthad_3b -> Update() ;

      c_tthad_3b -> SaveAs( "outputfiles/metvars-tthad-3b.pdf" ) ;




    //---- tthad, 4b

      TCanvas* c_tthad_4b = new TCanvas("c_tthad_4b", "tthad, 4b", 600, 400 ) ;

      h_metsig_4b_tthad_cbw -> SetLineColor(4) ;
      h_metsig2012_4b_tthad_cbw -> SetLineColor(1) ;
      h_met_4b_tthad_cbw -> SetLineColor(2) ;
      h_metovsqrtht_4b_tthad_cbw -> SetLineColor(3) ;

      h_metsig_4b_tthad_cbw -> SetLineWidth(2) ;
      h_metsig2012_4b_tthad_cbw -> SetLineWidth(2) ;
      h_met_4b_tthad_cbw -> SetLineWidth(2) ;
      h_metovsqrtht_4b_tthad_cbw -> SetLineWidth(2) ;


  //  h_metsig_4b_tthad_cbw -> Scale( 1./(h_metsig_4b_tthad->Integral()) ) ;
  //  h_metsig2012_4b_tthad_cbw -> Scale( 1./(h_metsig2012_4b_tthad->Integral()) ) ;
  //  h_met_4b_tthad_cbw -> Scale( 1./(h_met_4b_tthad->Integral()) ) ;
  //  h_metovsqrtht_4b_tthad_cbw -> Scale( 1./(h_metovsqrtht_4b_tthad->Integral()) ) ;


  //  h_metsig_4b_tthad_cbw -> SetMaximum(0.50) ;
      h_metsig_4b_tthad_cbw -> Draw( "hist" ) ;
      h_metsig_4b_tthad_cbw -> Draw( "same" ) ;

      h_metsig2012_4b_tthad_cbw -> Draw( "hist same" ) ;
      h_metsig2012_4b_tthad_cbw -> Draw( "same" ) ;

      h_met_4b_tthad_cbw -> Draw( "hist same" ) ;
      h_met_4b_tthad_cbw -> Draw( "same" ) ;

      h_metovsqrtht_4b_tthad_cbw -> Draw( "hist same" ) ;
      h_metovsqrtht_4b_tthad_cbw -> Draw( "same" ) ;

      legend -> Draw() ;

      c_tthad_4b -> Update() ;

      c_tthad_4b -> SaveAs( "outputfiles/metvars-tthad-4b.pdf" ) ;


    //---- tthad, mindphicut

      TCanvas* c_tthad_mindphicut = new TCanvas("c_tthad_mindphicut", "tthad, mindphicut", 600, 400 ) ;

      h_metsig_mindphicut_tthad_cbw -> SetLineColor(4) ;
      h_metsig2012_mindphicut_tthad_cbw -> SetLineColor(1) ;
      h_met_mindphicut_tthad_cbw -> SetLineColor(2) ;
      h_metovsqrtht_mindphicut_tthad_cbw -> SetLineColor(3) ;

      h_metsig_mindphicut_tthad_cbw -> SetLineWidth(2) ;
      h_metsig2012_mindphicut_tthad_cbw -> SetLineWidth(2) ;
      h_met_mindphicut_tthad_cbw -> SetLineWidth(2) ;
      h_metovsqrtht_mindphicut_tthad_cbw -> SetLineWidth(2) ;


  //  h_metsig_mindphicut_tthad_cbw -> Scale( 1./(h_metsig_mindphicut_tthad->Integral()) ) ;
  //  h_metsig2012_mindphicut_tthad_cbw -> Scale( 1./(h_metsig2012_mindphicut_tthad->Integral()) ) ;
  //  h_met_mindphicut_tthad_cbw -> Scale( 1./(h_met_mindphicut_tthad->Integral()) ) ;
  //  h_metovsqrtht_mindphicut_tthad_cbw -> Scale( 1./(h_metovsqrtht_mindphicut_tthad->Integral()) ) ;


  //  h_metsig_mindphicut_tthad_cbw -> SetMaximum(0.50) ;
      h_metsig_mindphicut_tthad_cbw -> Draw( "hist" ) ;
      h_metsig_mindphicut_tthad_cbw -> Draw( "same" ) ;

      h_metsig2012_mindphicut_tthad_cbw -> Draw( "hist same" ) ;
      h_metsig2012_mindphicut_tthad_cbw -> Draw( "same" ) ;

      h_met_mindphicut_tthad_cbw -> Draw( "hist same" ) ;
      h_met_mindphicut_tthad_cbw -> Draw( "same" ) ;

      h_metovsqrtht_mindphicut_tthad_cbw -> Draw( "hist same" ) ;
      h_metovsqrtht_mindphicut_tthad_cbw -> Draw( "same" ) ;

      legend -> Draw() ;

      c_tthad_mindphicut -> Update() ;

      c_tthad_mindphicut -> SaveAs( "outputfiles/metvars-tthad-mindphicut.pdf" ) ;





      saveHist( "outputfiles/metvarshape.root", "h*" ) ;


   } // metvarshape


//====================================================


   void addoverflow( TH1* hp, bool dounder ) {
      if ( hp==0x0 ) return ;
      int nb = hp -> GetNbinsX() ;
      float newval = hp -> GetBinContent( nb ) + hp -> GetBinContent( nb+1 ) ;
      float newerr = sqrt( pow( hp -> GetBinError( nb ), 2 ) + pow( hp -> GetBinError( nb+1 ), 2 ) ) ;
      hp -> SetBinContent( nb, newval ) ;
      hp -> SetBinError( nb, newerr ) ;
      if ( dounder ) {
         newval = hp -> GetBinContent( 1 ) + hp -> GetBinContent( 0 ) ;
         newerr = sqrt( pow( hp -> GetBinError( 1 ), 2 ) + pow( hp -> GetBinError( 0 ), 2 ) ) ;
         hp -> SetBinContent( 1, newval ) ;
         hp -> SetBinError( 1, newerr ) ;
      }
   } // addoverflow

//====================================================

   TH1F* make_h_cbw( TH1* hin, float xshift ) {

      if ( hin == 0x0 ) return 0x0 ;

      TString hname = hin -> GetName() ;
      hname += TString("_cbw") ;

      int nbins = hin -> GetNbinsX() ;

      TH1F* retval = new TH1F( hname, hin->GetTitle(), nbins+2, -0.5+xshift, 1.5+nbins+xshift ) ;

      for ( int bi=1; bi<=nbins; bi++ ) {
         retval -> SetBinContent( bi+1, hin -> GetBinContent(bi) ) ;
         retval -> SetBinError( bi+1, hin -> GetBinError(bi) ) ;
      } // bi.

      retval -> SetLineColor( hin -> GetLineColor() ) ;
      retval -> SetLineWidth( hin -> GetLineWidth() ) ;

      if ( gStyle -> GetOptLogy() ) { retval -> SetMinimum(0.1) ; }

      return retval ;

   } // make_h_cbw

//====================================================
