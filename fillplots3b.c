#include "TStyle.h"
#include "TChain.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "THStack.h"
#include "TBox.h"

#include "histio.c"

#include <iostream>


   bool bookset2Dm( const char* hname,
                 const char* htitle ) ;


   bool fillset2Dm( const char* hname,
                 const char* cuts) ;

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

   void fillplots3b() {

      gDirectory->Delete("h*") ;


      gStyle->SetOptStat(0) ;

      for ( int si=0; si<nsamples; si++ ) { samplechain[si] = new TChain("reducedTree") ; }

      //char rtdir[10000] = "/Users/owen/work/cms/hadronic-susy-bjets/hbb/reduced-trees-may23-2013" ;
      char rtdir[10000] = "/data/cms/hadronic-susy-bjets/hbb/reduced-trees-may23-2013" ;

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

      char cuts[100000] ;






     //--- 4b, METsig>30
      sprintf( cuts, "(%s)&&(%s)&&(%s)&&METsig>30", btagcuts, leptonveto, drmaxcut ) ;
      bookset2Dm( "h_dmvsam_4b_metsig30", "delta m vs ave m, METsig>30, 4b" ) ;
      fillset2Dm( "h_dmvsam_4b_metsig30", cuts ) ;

     //--- 3b, METsig>30
      sprintf( cuts, "(%s)&&(%s)&&(%s)&&METsig>30", btag3cuts, leptonveto, drmaxcut ) ;
      bookset2Dm( "h_dmvsam_3b_metsig30", "delta m vs ave m, METsig>30, 3b" ) ;
      fillset2Dm( "h_dmvsam_3b_metsig30", cuts ) ;

     //--- 2b, METsig>30
      sprintf( cuts, "(%s)&&(%s)&&(%s)&&METsig>30", btag2cuts, leptonveto, drmaxcut ) ;
      bookset2Dm( "h_dmvsam_2b_metsig30", "delta m vs ave m, METsig>30, 2b" ) ;
      fillset2Dm( "h_dmvsam_2b_metsig30", cuts ) ;



     //--- 4b, METsig [30,50]
      sprintf( cuts, "(%s)&&(%s)&&(%s)&&METsig>30&&METsig<50", btagcuts, leptonveto, drmaxcut ) ;
      bookset2Dm( "h_dmvsam_4b_metsig30_50", "delta m vs ave m, METsig [30,50], 4b" ) ;
      fillset2Dm( "h_dmvsam_4b_metsig30_50", cuts ) ;

     //--- 3b, METsig [30,50]
      sprintf( cuts, "(%s)&&(%s)&&(%s)&&METsig>30&&METsig<50", btag3cuts, leptonveto, drmaxcut ) ;
      bookset2Dm( "h_dmvsam_3b_metsig30_50", "delta m vs ave m, METsig [30,50], 3b" ) ;
      fillset2Dm( "h_dmvsam_3b_metsig30_50", cuts ) ;

     //--- 2b, METsig [30,50]
      sprintf( cuts, "(%s)&&(%s)&&(%s)&&METsig>30&&METsig<50", btag2cuts, leptonveto, drmaxcut ) ;
      bookset2Dm( "h_dmvsam_2b_metsig30_50", "delta m vs ave m, METsig [30,50], 2b" ) ;
      fillset2Dm( "h_dmvsam_2b_metsig30_50", cuts ) ;



     //--- 4b, METsig [50,100]
      sprintf( cuts, "(%s)&&(%s)&&(%s)&&METsig>50&&METsig<100", btagcuts, leptonveto, drmaxcut ) ;
      bookset2Dm( "h_dmvsam_4b_metsig50_100", "delta m vs ave m, METsig [50,100], 4b" ) ;
      fillset2Dm( "h_dmvsam_4b_metsig50_100", cuts ) ;

     //--- 3b, METsig [50,100]
      sprintf( cuts, "(%s)&&(%s)&&(%s)&&METsig>50&&METsig<100", btag3cuts, leptonveto, drmaxcut ) ;
      bookset2Dm( "h_dmvsam_3b_metsig50_100", "delta m vs ave m, METsig [50,100], 3b" ) ;
      fillset2Dm( "h_dmvsam_3b_metsig50_100", cuts ) ;

     //--- 2b, METsig [50,100]
      sprintf( cuts, "(%s)&&(%s)&&(%s)&&METsig>50&&METsig<100", btag2cuts, leptonveto, drmaxcut ) ;
      bookset2Dm( "h_dmvsam_2b_metsig50_100", "delta m vs ave m, METsig [50,100], 2b" ) ;
      fillset2Dm( "h_dmvsam_2b_metsig50_100", cuts ) ;



     //--- 4b, METsig [100,150]
      sprintf( cuts, "(%s)&&(%s)&&(%s)&&METsig>100&&METsig<150", btagcuts, leptonveto, drmaxcut ) ;
      bookset2Dm( "h_dmvsam_4b_metsig100_150", "delta m vs ave m, METsig [100,150], 4b" ) ;
      fillset2Dm( "h_dmvsam_4b_metsig100_150", cuts ) ;

     //--- 3b, METsig [100,150]
      sprintf( cuts, "(%s)&&(%s)&&(%s)&&METsig>100&&METsig<150", btag3cuts, leptonveto, drmaxcut ) ;
      bookset2Dm( "h_dmvsam_3b_metsig100_150", "delta m vs ave m, METsig [100,150], 3b" ) ;
      fillset2Dm( "h_dmvsam_3b_metsig100_150", cuts ) ;

     //--- 2b, METsig [100,150]
      sprintf( cuts, "(%s)&&(%s)&&(%s)&&METsig>100&&METsig<150", btag2cuts, leptonveto, drmaxcut ) ;
      bookset2Dm( "h_dmvsam_2b_metsig100_150", "delta m vs ave m, METsig [100,150], 2b" ) ;
      fillset2Dm( "h_dmvsam_2b_metsig100_150", cuts ) ;



     //--- 4b, METsig>150
      sprintf( cuts, "(%s)&&(%s)&&(%s)&&METsig>150", btagcuts, leptonveto, drmaxcut ) ;
      bookset2Dm( "h_dmvsam_4b_metsig150", "delta m vs ave m, METsig>150, 4b" ) ;
      fillset2Dm( "h_dmvsam_4b_metsig150", cuts ) ;

     //--- 3b, METsig>150
      sprintf( cuts, "(%s)&&(%s)&&(%s)&&METsig>150", btag3cuts, leptonveto, drmaxcut ) ;
      bookset2Dm( "h_dmvsam_3b_metsig150", "delta m vs ave m, METsig>150, 3b" ) ;
      fillset2Dm( "h_dmvsam_3b_metsig150", cuts ) ;

     //--- 2b, METsig>150
      sprintf( cuts, "(%s)&&(%s)&&(%s)&&METsig>150", btag2cuts, leptonveto, drmaxcut ) ;
      bookset2Dm( "h_dmvsam_2b_metsig150", "delta m vs ave m, METsig>150, 2b" ) ;
      fillset2Dm( "h_dmvsam_2b_metsig150", cuts ) ;








      saveHist( "plots3b.root", "h*" ) ;


   } // fillplots3b.

  //======================================================================

   bool bookset2Dm( const char* hname,
                 const char* htitle ) {

      char hfullname[1000] ;
      char hfulltitle[1000] ;


      for ( int si=0; si<nsamples; si++ ) {

         sprintf( hfullname, "%s_%s", hname, samplename[si] ) ;
         sprintf( hfulltitle, "%s, %s", htitle, samplename[si] ) ;
         //TH2F* hist = new TH2F( hfullname, hfulltitle,   25, 0., 250.,  24, -120., 120. ) ;
         TH2F* hist = new TH2F( hfullname, hfulltitle,   50, 0., 500.,  48, -240., 240. ) ;

         hist->SetFillColor( samplecolor[si] ) ;
         hist->Sumw2() ;

      }

      return true ;

   } // bookset2Dm


  //======================================================================

   bool fillset2Dm( const char* hname,
                 const char* cuts ) {

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
         sprintf( arg1, "(higgsMbb1MassDiff-higgsMbb2MassDiff):(0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff))>>%s_%s", hname, samplename[si] ) ;
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

         TH2F* hist = (TH2F*) gDirectory->FindObject( hfullname ) ;

      // int nbins = hist->GetNbinsX() ;
      // double newlastval = hist->GetBinContent( nbins ) ;
      // newlastval += hist->GetBinContent( nbins+1 ) ;
      // double newlasterr2 = pow( hist->GetBinError( nbins ), 2 ) ;
      // newlasterr2 += pow( hist->GetBinError( nbins+1 ), 2 ) ;
      // hist->SetBinContent( nbins, newlastval ) ;
      // hist->SetBinError( nbins, sqrt(newlasterr2) ) ;

         hist->Draw("box") ;
         cplots->Update() ;
         cplots->Draw() ;

         TBox* box = new TBox() ;
         box->SetFillStyle(0) ;
         box->DrawBox( 100., -20., 140., 20. ) ;
         box->DrawBox(  90., -30., 150., 30. ) ;

      } // si.

      return true ;

   } // fillset

  //======================================================================




