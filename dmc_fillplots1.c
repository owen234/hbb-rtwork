
#include "TStyle.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TDirectory.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TRegexp.h"
#include "TKey.h"
#include "TFile.h"
#include <iostream>

    int nComps(6) ;
    char compname[6][100] ;
    int compcolor[6] ;
    double complumi[6] ;
    TChain* compchain[6] ;
    double compscale[6] ;

    TCanvas* dcan ;

   //----------------------------
   // prototypes

    void bookSet( const char* hname_base, const char* htitle_base, int nbins, double xmin, double xmax ) ;
    void fillSet( const char* hname_base, const char* varname, const char* cuts, bool blind_data = false ) ;
    void saveHist(const char* filename, const char* pat) ;

   //----------------------------

    void dmc_fillplots1( ) {

       gDirectory -> Delete("h*") ;

       gStyle -> SetOptStat(0) ;
       gStyle -> SetTitleH(0.035 ) ;

       for ( int ci=0; ci<nComps; ci++ ) { compchain[ci] = new TChain("reducedTree") ; }

       int compind ;

       char rtdir[10000] ;
       //// sprintf( rtdir, "/Users/owen/work/cms/hadronic-susy-bjets/hbb/reduced-trees-sept17-2013-v71-1s/" ) ;
       sprintf( rtdir, "/Users/owen/work/cms/hadronic-susy-bjets/hbb/reduced-trees-skim-sept17-2013-v71-1s/" ) ;
       char files_string[10000] ;
       int n_files_added ;

    //-- Data
       compind = 0 ;
       sprintf( compname[compind], "data" ) ;
       sprintf( files_string, "%s/*MET_Run2012*-skim.root", rtdir ) ;
       n_files_added = compchain[compind] -> Add( files_string ) ;
       printf(" Added %d files for comp %s\n", n_files_added, compname[compind] ) ;
       compcolor[compind] = 0 ;

    //-- Zinvisible
       compind = 1 ;
       sprintf( compname[compind], "znn" ) ;
       sprintf( files_string, "%s/*ZJetsToNuNu*-skim.root", rtdir ) ;
       n_files_added = compchain[compind] -> Add( files_string ) ;
       printf(" Added %d files for comp %s\n", n_files_added, compname[compind] ) ;
       ///compcolor[compind] = 416-3 ; // kGreen = 416
       compcolor[compind] = kOrange-2 ;

    //-- ttbar, 0 lepton
       compind = 2 ;
       sprintf( compname[compind], "tt0l" ) ;
       sprintf( files_string, "%s/*TTJets_HadronicMGDecays_8TeV*-skim.root", rtdir ) ;
       n_files_added = compchain[compind] -> Add( files_string ) ;
       printf(" Added %d files for comp %s\n", n_files_added, compname[compind] ) ;
       ///compcolor[compind] = 600-7 ; // kBlue = 600
       compcolor[compind] = kGreen-9 ;

    //-- ttbar, 2 lepton
       compind = 3 ;
       sprintf( compname[compind], "tt2l" ) ;
       sprintf( files_string, "%s/*TTJets_FullLeptMGDecays_8TeV*-skim.root", rtdir ) ;
       n_files_added = compchain[compind] -> Add( files_string ) ;
       printf(" Added %d files for comp %s\n", n_files_added, compname[compind] ) ;
       /////compcolor[compind] = 600-9 ; // kBlue = 600
       compcolor[compind] = kBlue-10 ;

    //-- ttbar, 1 lepton
       compind = 4 ;
       sprintf( compname[compind], "tt1l" ) ;
       sprintf( files_string, "%s/*TTJets_SemiLeptMGDecays_8TeV*-skim.root", rtdir ) ;
       n_files_added = compchain[compind] -> Add( files_string ) ;
       printf(" Added %d files for comp %s\n", n_files_added, compname[compind] ) ;
       /////compcolor[compind] = 600-9 ; // kBlue = 600
       compcolor[compind] = kBlue-7 ;

    //-- QCD with b bbar.
       compind = 5 ;
       sprintf( compname[compind], "qcd_bb" ) ;
       sprintf( files_string, "%s/*BJets_HT*-skim.root", rtdir ) ;
       n_files_added = compchain[compind] -> Add( files_string ) ;
       printf(" Added %d files for comp %s\n", n_files_added, compname[compind] ) ;
       //// compcolor[compind] = 2 ;
       compcolor[compind] = kGreen ;

 // //-- QCD nominal.
 //    compind = 4 ;
 //    sprintf( compname[compind], "qcd" ) ;
 //    sprintf( files_string, "%s/*QCD*-skim.root", rtdir ) ;
 //    n_files_added = compchain[compind] -> Add( files_string ) ;
 //    printf(" Added %d files for comp %s\n", n_files_added, compname[compind] ) ;
 //    compcolor[compind] = 2 ;




      printf("\n\n Setting up cuts.\n\n") ;

     //--- These are included in the skim definition of doSlimSkim.c.  Doesn't hurt to apply them here.

      char basiccuts[10000] ;
      sprintf( basiccuts, "cutPV==1&&passCleaning==1&&buggyEvent==0" ) ;

      char triggercuts[10000] ;
      ///sprintf( triggercuts, "(passMC_DiCentralPFJet30_PFMET80_BTagCSV07==1||passMC_PFMET150==1)" ) ;
      sprintf( triggercuts, "(passMC_DiCentralPFJet30_PFMET80_BTagCSV07==1||passMC_PFMET150==1)&&(pass_DiCentralPFJet30_PFMET80_BTagCSV07==1||pass_PFMET150==1)" ) ;

      char njetcuts[10000] ;
      sprintf( njetcuts, "njets20>=4&&njets20<=5" ) ;

      char skimcuts[10000] ;
      sprintf( skimcuts, "((%s)&&(%s)&&(%s))", basiccuts, triggercuts, njetcuts ) ;


     //--- These are beyond the skim selection.

      char masssigcuts[10000] ;
      sprintf( masssigcuts, "%s", "abs(higgsMbb1MassDiff-higgsMbb2MassDiff)<20&&((0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff)>100)&&(0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff)<140))" ) ;

      char masssbcuts[10000] ;
      sprintf( masssbcuts, "%s", "!(abs(higgsMbb1MassDiff-higgsMbb2MassDiff)<30&&((0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff)>90)&&(0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff)<150)))" ) ;

      char btag4cuts[10000] ;
      sprintf( btag4cuts, "%s", "CSVbest2>0.898&&CSVbest3>0.679&&CSVbest4>0.244" ) ;

      char btag3cuts[10000] ;
      sprintf( btag3cuts, "%s", "CSVbest2>0.898&&CSVbest3>0.679&&CSVbest4<0.244" ) ;

      char btag2cuts[10000] ;
      sprintf( btag2cuts, "%s", "CSVbest2>0.898&&CSVbest3<0.679" ) ;

      char leptonveto[10000] ;
      sprintf( leptonveto, "%s", "nMuons==0&&nElectrons==0&&nIsoTracks15_005_03==0&&nTausLoose==0" ) ;

      char drmaxcut[10000] ;
      sprintf( drmaxcut, "%s", "deltaRmax_hh<2.2" ) ;

      char mindphicut[10000] ;
      sprintf( mindphicut, "%s", "minDeltaPhi20>0.3" ) ;

      char jet2ptcut[10000] ;
      sprintf( jet2ptcut, "%s", "jetpt2>50" ) ;

      char minmetsig[10000] ;
      sprintf( minmetsig, "%s", "METsig>30" ) ;

      char allcommoncuts[10000] ;
      sprintf( allcommoncuts, "(%s)&&(%s)&&(%s)&&(%s)&&(%s)&&(%s)", skimcuts, leptonveto, drmaxcut, jet2ptcut, mindphicut, minmetsig ) ;

      char nm1_mindphi[10000] ;
      sprintf( nm1_mindphi, "(%s)&&(%s)&&(%s)&&(%s)&&(%s)", skimcuts, leptonveto, drmaxcut, jet2ptcut, minmetsig ) ;

      char nm1_metsig[10000] ;
      sprintf( nm1_metsig, "(%s)&&(%s)&&(%s)&&(%s)&&(%s)", skimcuts, leptonveto, drmaxcut, jet2ptcut, mindphicut ) ;

      char nm2_metsig_mindphi[10000] ;
      sprintf( nm2_metsig_mindphi, "(%s)&&(%s)&&(%s)&&(%s)", skimcuts, leptonveto, drmaxcut, jet2ptcut ) ;







       dcan = (TCanvas*) gDirectory->FindObject("dcan") ;
       if ( dcan == 0x0 ) {
          dcan = new TCanvas("dcan","",700, 1000) ;
       }

       char htitle[1000] ;
       char cuts[10000] ;


       sprintf( htitle, "METsig, 2b, with minDeltaPhi cut" ) ;
       bookSet( "h_metsig_2b_with_mindphi", htitle, 40, 0., 200. ) ;
       sprintf( cuts, "(%s&&%s)", nm1_metsig, btag2cuts  ) ;
       fillSet( "h_metsig_2b_with_mindphi", "METsig", cuts ) ;

       sprintf( htitle, "METsig, 2b, with minDeltaPhi cut" ) ;
       bookSet( "h_metsig_2b_with_mindphi_wide1", htitle, 80, 0., 400. ) ;
       sprintf( cuts, "(%s&&%s)", nm1_metsig, btag2cuts  ) ;
       fillSet( "h_metsig_2b_with_mindphi_wide1", "METsig", cuts ) ;

       sprintf( htitle, "METsig, 2b, with minDeltaPhi cut" ) ;
       bookSet( "h_metsig_2b_with_mindphi_wide2", htitle, 20, 0., 400. ) ;
       sprintf( cuts, "(%s&&%s)", nm1_metsig, btag2cuts  ) ;
       fillSet( "h_metsig_2b_with_mindphi_wide2", "METsig", cuts ) ;

       sprintf( htitle, "MET, 2b, with minDeltaPhi cut" ) ;
       bookSet( "h_met_2b_with_mindphi", htitle, 35, 0., 350. ) ;
       sprintf( cuts, "(%s&&%s)", nm1_metsig, btag2cuts ) ;
       fillSet( "h_met_2b_with_mindphi", "MET", cuts ) ;



       sprintf( htitle, "METsig, 2b, no minDeltaPhi cut" ) ;
       bookSet( "h_metsig_2b_no_mindphi", htitle, 40, 0., 200. ) ;
       sprintf( cuts, "(%s&&%s)", nm2_metsig_mindphi, btag2cuts ) ;
       fillSet( "h_metsig_2b_no_mindphi", "METsig", cuts ) ;

       sprintf( htitle, "METsig, 2b, no minDeltaPhi cut" ) ;
       bookSet( "h_metsig_2b_no_mindphi_wide1", htitle, 80, 0., 400. ) ;
       sprintf( cuts, "(%s&&%s)", nm2_metsig_mindphi, btag2cuts ) ;
       fillSet( "h_metsig_2b_no_mindphi_wide1", "METsig", cuts ) ;

       sprintf( htitle, "METsig, 2b, no minDeltaPhi cut" ) ;
       bookSet( "h_metsig_2b_no_mindphi_wide2", htitle, 20, 0., 400. ) ;
       sprintf( cuts, "(%s&&%s)", nm2_metsig_mindphi, btag2cuts ) ;
       fillSet( "h_metsig_2b_no_mindphi_wide2", "METsig", cuts ) ;

       sprintf( htitle, "MET, 2b, no minDeltaPhi cut" ) ;
       bookSet( "h_met_2b_no_mindphi", htitle, 35, 0., 350. ) ;
       sprintf( cuts, "(%s&&%s)", nm2_metsig_mindphi, btag2cuts ) ;
       fillSet( "h_met_2b_no_mindphi", "MET", cuts ) ;




 //    sprintf( htitle, "minDeltaPhi20, 2b, no METsig cut" ) ;
 //    bookSet( "h_mindphi_2b_no_metsig", htitle, 32, 0., 3.2 ) ;
 //    sprintf( cuts, "(%s&&%s)", nm2_metsig_mindphi, btag2cuts ) ;
 //    fillSet( "h_mindphi_2b_no_metsig", "minDeltaPhi20", cuts ) ;

 //    sprintf( htitle, "minDeltaPhi20, 2b, METsig>30" ) ;
 //    bookSet( "h_mindphi_2b_metsig_030", htitle, 32, 0., 3.2 ) ;
 //    sprintf( cuts, "(%s&&%s&&METsig>30)", nm2_metsig_mindphi, btag2cuts ) ;
 //    fillSet( "h_mindphi_2b_metsig_030", "minDeltaPhi20", cuts ) ;

 //    sprintf( htitle, "minDeltaPhi20, 2b, METsig>50" ) ;
 //    bookSet( "h_mindphi_2b_metsig_050", htitle, 32, 0., 3.2 ) ;
 //    sprintf( cuts, "(%s&&%s&&METsig>50)", nm2_metsig_mindphi, btag2cuts ) ;
 //    fillSet( "h_mindphi_2b_metsig_050", "minDeltaPhi20", cuts ) ;

 //    sprintf( htitle, "minDeltaPhi20, 2b, METsig>100" ) ;
 //    bookSet( "h_mindphi_2b_metsig_100", htitle, 32, 0., 3.2 ) ;
 //    sprintf( cuts, "(%s&&%s&&METsig>100)", nm2_metsig_mindphi, btag2cuts ) ;
 //    fillSet( "h_mindphi_2b_metsig_100", "minDeltaPhi20", cuts ) ;

 //    sprintf( htitle, "minDeltaPhi20, 2b, METsig>150" ) ;
 //    bookSet( "h_mindphi_2b_metsig_150", htitle, 32, 0., 3.2 ) ;
 //    sprintf( cuts, "(%s&&%s&&METsig>150)", nm2_metsig_mindphi, btag2cuts ) ;
 //    fillSet( "h_mindphi_2b_metsig_150", "minDeltaPhi20", cuts ) ;



 //    sprintf( htitle, "minDeltaPhi20, 2b, no MET cut" ) ;
 //    bookSet( "h_mindphi_2b_no_met", htitle, 32, 0., 3.2 ) ;
 //    sprintf( cuts, "(%s&&%s)", nm2_metsig_mindphi, btag2cuts ) ;
 //    fillSet( "h_mindphi_2b_no_met", "minDeltaPhi20", cuts ) ;

 //    sprintf( htitle, "minDeltaPhi20, 2b, MET>100" ) ;
 //    bookSet( "h_mindphi_2b_met_100", htitle, 32, 0., 3.2 ) ;
 //    sprintf( cuts, "(%s&&%s&&MET>100)", nm2_metsig_mindphi, btag2cuts ) ;
 //    fillSet( "h_mindphi_2b_met_100", "minDeltaPhi20", cuts ) ;

 //    sprintf( htitle, "minDeltaPhi20, 2b, MET>135" ) ;
 //    bookSet( "h_mindphi_2b_met_135", htitle, 32, 0., 3.2 ) ;
 //    sprintf( cuts, "(%s&&%s&&MET>135)", nm2_metsig_mindphi, btag2cuts ) ;
 //    fillSet( "h_mindphi_2b_met_135", "minDeltaPhi20", cuts ) ;

 //    sprintf( htitle, "minDeltaPhi20, 2b, MET>190" ) ;
 //    bookSet( "h_mindphi_2b_met_190", htitle, 32, 0., 3.2 ) ;
 //    sprintf( cuts, "(%s&&%s&&MET>190)", nm2_metsig_mindphi, btag2cuts ) ;
 //    fillSet( "h_mindphi_2b_met_190", "minDeltaPhi20", cuts ) ;

 //    sprintf( htitle, "minDeltaPhi20, 2b, MET>250" ) ;
 //    bookSet( "h_mindphi_2b_met_250", htitle, 32, 0., 3.2 ) ;
 //    sprintf( cuts, "(%s&&%s&&MET>250)", nm2_metsig_mindphi, btag2cuts ) ;
 //    fillSet( "h_mindphi_2b_met_250", "minDeltaPhi20", cuts ) ;





 //    sprintf( htitle, "minDeltaPhi20, 2b, METsig bin0 (<30)" ) ;
 //    bookSet( "h_mindphi_2b_metsig_bin0", htitle, 32, 0., 3.2 ) ;
 //    sprintf( cuts, "(%s&&%s&&METsig<30)", nm2_metsig_mindphi, btag2cuts ) ;
 //    fillSet( "h_mindphi_2b_metsig_bin0", "minDeltaPhi20", cuts ) ;

 //    sprintf( htitle, "minDeltaPhi20, 2b, METsig bin1 (30,50)" ) ;
 //    bookSet( "h_mindphi_2b_metsig_bin1", htitle, 32, 0., 3.2 ) ;
 //    sprintf( cuts, "(%s&&%s&&METsig>30&&METsig<50)", nm2_metsig_mindphi, btag2cuts ) ;
 //    fillSet( "h_mindphi_2b_metsig_bin1", "minDeltaPhi20", cuts ) ;

 //    sprintf( htitle, "minDeltaPhi20, 2b, METsig bin2 (50,100)" ) ;
 //    bookSet( "h_mindphi_2b_metsig_bin2", htitle, 32, 0., 3.2 ) ;
 //    sprintf( cuts, "(%s&&%s&&METsig>50&&METsig<100)", nm2_metsig_mindphi, btag2cuts ) ;
 //    fillSet( "h_mindphi_2b_metsig_bin2", "minDeltaPhi20", cuts ) ;

 //    sprintf( htitle, "minDeltaPhi20, 2b, METsig bin3 (100,150)" ) ;
 //    bookSet( "h_mindphi_2b_metsig_bin3", htitle, 32, 0., 3.2 ) ;
 //    sprintf( cuts, "(%s&&%s&&METsig>100&&METsig<150)", nm2_metsig_mindphi, btag2cuts ) ;
 //    fillSet( "h_mindphi_2b_metsig_bin3", "minDeltaPhi20", cuts ) ;

 //    sprintf( htitle, "minDeltaPhi20, 2b, METsig bin4 (>150)" ) ;
 //    bookSet( "h_mindphi_2b_metsig_bin4", htitle, 32, 0., 3.2 ) ;
 //    sprintf( cuts, "(%s&&%s&&METsig>150)", nm2_metsig_mindphi, btag2cuts ) ;
 //    fillSet( "h_mindphi_2b_metsig_bin4", "minDeltaPhi20", cuts ) ;




 //    sprintf( htitle, "minDeltaPhi20, 2b, MET bin0 (<106)" ) ;
 //    bookSet( "h_mindphi_2b_met_bin0", htitle, 32, 0., 3.2 ) ;
 //    sprintf( cuts, "(%s&&%s&&MET<106)", nm2_metsig_mindphi, btag2cuts ) ;
 //    fillSet( "h_mindphi_2b_met_bin0", "minDeltaPhi20", cuts ) ;

 //    sprintf( htitle, "minDeltaPhi20, 2b, MET bin1 (106,133)" ) ;
 //    bookSet( "h_mindphi_2b_met_bin1", htitle, 32, 0., 3.2 ) ;
 //    sprintf( cuts, "(%s&&%s&&MET>106&&MET<133)", nm2_metsig_mindphi, btag2cuts ) ;
 //    fillSet( "h_mindphi_2b_met_bin1", "minDeltaPhi20", cuts ) ;

 //    sprintf( htitle, "minDeltaPhi20, 2b, MET bin2 (133,190)" ) ;
 //    bookSet( "h_mindphi_2b_met_bin2", htitle, 32, 0., 3.2 ) ;
 //    sprintf( cuts, "(%s&&%s&&MET>133&&MET<190)", nm2_metsig_mindphi, btag2cuts ) ;
 //    fillSet( "h_mindphi_2b_met_bin2", "minDeltaPhi20", cuts ) ;

 //    sprintf( htitle, "minDeltaPhi20, 2b, MET bin3 (190,250)" ) ;
 //    bookSet( "h_mindphi_2b_met_bin3", htitle, 32, 0., 3.2 ) ;
 //    sprintf( cuts, "(%s&&%s&&MET>190&&MET<250)", nm2_metsig_mindphi, btag2cuts ) ;
 //    fillSet( "h_mindphi_2b_met_bin3", "minDeltaPhi20", cuts ) ;

 //    sprintf( htitle, "minDeltaPhi20, 2b, MET bin4 (>250)" ) ;
 //    bookSet( "h_mindphi_2b_met_bin4", htitle, 32, 0., 3.2 ) ;
 //    sprintf( cuts, "(%s&&%s&&MET>250)", nm2_metsig_mindphi, btag2cuts ) ;
 //    fillSet( "h_mindphi_2b_met_bin4", "minDeltaPhi20", cuts ) ;




 //    sprintf( htitle, "minDeltaPhi20, 3b SB, no METsig cut" ) ;
 //    bookSet( "h_mindphi_3bSB_no_metsig", htitle, 32, 0., 3.2 ) ;
 //    sprintf( cuts, "(%s&&%s&&%s)", nm2_metsig_mindphi, btag3cuts, masssbcuts ) ;
 //    fillSet( "h_mindphi_3bSB_no_metsig", "minDeltaPhi20", cuts ) ;

 //    sprintf( htitle, "minDeltaPhi20, 3b SB, METsig>30" ) ;
 //    bookSet( "h_mindphi_3bSB_metsig_030", htitle, 32, 0., 3.2 ) ;
 //    sprintf( cuts, "(%s&&%s&&%s&&METsig>30)", nm2_metsig_mindphi, btag3cuts, masssbcuts ) ;
 //    fillSet( "h_mindphi_3bSB_metsig_030", "minDeltaPhi20", cuts ) ;

 //    sprintf( htitle, "minDeltaPhi20, 3b SB, METsig>50" ) ;
 //    bookSet( "h_mindphi_3bSB_metsig_050", htitle, 32, 0., 3.2 ) ;
 //    sprintf( cuts, "(%s&&%s&&%s&&METsig>50)", nm2_metsig_mindphi, btag3cuts, masssbcuts ) ;
 //    fillSet( "h_mindphi_3bSB_metsig_050", "minDeltaPhi20", cuts ) ;

 //    sprintf( htitle, "minDeltaPhi20, 3b SB, METsig>100" ) ;
 //    bookSet( "h_mindphi_3bSB_metsig_100", htitle, 32, 0., 3.2 ) ;
 //    sprintf( cuts, "(%s&&%s&&%s&&METsig>100)", nm2_metsig_mindphi, btag3cuts, masssbcuts ) ;
 //    fillSet( "h_mindphi_3bSB_metsig_100", "minDeltaPhi20", cuts ) ;

 //    sprintf( htitle, "minDeltaPhi20, 3b SB, METsig>150" ) ;
 //    bookSet( "h_mindphi_3bSB_metsig_150", htitle, 32, 0., 3.2 ) ;
 //    sprintf( cuts, "(%s&&%s&&%s&&METsig>150)", nm2_metsig_mindphi, btag3cuts, masssbcuts ) ;
 //    fillSet( "h_mindphi_3bSB_metsig_150", "minDeltaPhi20", cuts ) ;



 //    bool keep_data_blind(true) ;

 //    sprintf( htitle, "minDeltaPhi20, 3b SIG, no METsig cut" ) ;
 //    bookSet( "h_mindphi_3bSIG_no_metsig", htitle, 32, 0., 3.2 ) ;
 //    sprintf( cuts, "(%s&&%s&&%s)", nm2_metsig_mindphi, btag3cuts, masssigcuts ) ;
 //    fillSet( "h_mindphi_3bSIG_no_metsig", "minDeltaPhi20", cuts, keep_data_blind ) ;

 //    sprintf( htitle, "minDeltaPhi20, 3b SIG, METsig>30" ) ;
 //    bookSet( "h_mindphi_3bSIG_metsig_030", htitle, 32, 0., 3.2 ) ;
 //    sprintf( cuts, "(%s&&%s&&%s&&METsig>30)", nm2_metsig_mindphi, btag3cuts, masssigcuts ) ;
 //    fillSet( "h_mindphi_3bSIG_metsig_030", "minDeltaPhi20", cuts, keep_data_blind ) ;

 //    sprintf( htitle, "minDeltaPhi20, 3b SIG, METsig>50" ) ;
 //    bookSet( "h_mindphi_3bSIG_metsig_050", htitle, 32, 0., 3.2 ) ;
 //    sprintf( cuts, "(%s&&%s&&%s&&METsig>50)", nm2_metsig_mindphi, btag3cuts, masssigcuts ) ;
 //    fillSet( "h_mindphi_3bSIG_metsig_050", "minDeltaPhi20", cuts, keep_data_blind ) ;

 //    sprintf( htitle, "minDeltaPhi20, 3b SIG, METsig>100" ) ;
 //    bookSet( "h_mindphi_3bSIG_metsig_100", htitle, 32, 0., 3.2 ) ;
 //    sprintf( cuts, "(%s&&%s&&%s&&METsig>100)", nm2_metsig_mindphi, btag3cuts, masssigcuts ) ;
 //    fillSet( "h_mindphi_3bSIG_metsig_100", "minDeltaPhi20", cuts, keep_data_blind ) ;

 //    sprintf( htitle, "minDeltaPhi20, 3b SIG, METsig>150" ) ;
 //    bookSet( "h_mindphi_3bSIG_metsig_150", htitle, 32, 0., 3.2 ) ;
 //    sprintf( cuts, "(%s&&%s&&%s&&METsig>150)", nm2_metsig_mindphi, btag3cuts, masssigcuts ) ;
 //    fillSet( "h_mindphi_3bSIG_metsig_150", "minDeltaPhi20", cuts, keep_data_blind ) ;




 //    sprintf( htitle, "minDeltaPhi20, 4b SB, no METsig cut" ) ;
 //    bookSet( "h_mindphi_4bSB_no_metsig", htitle, 32, 0., 3.2 ) ;
 //    sprintf( cuts, "(%s&&%s&&%s)", nm2_metsig_mindphi, btag4cuts, masssbcuts ) ;
 //    fillSet( "h_mindphi_4bSB_no_metsig", "minDeltaPhi20", cuts, keep_data_blind ) ;

 //    sprintf( htitle, "minDeltaPhi20, 4b SB, METsig>30" ) ;
 //    bookSet( "h_mindphi_4bSB_metsig_030", htitle, 32, 0., 3.2 ) ;
 //    sprintf( cuts, "(%s&&%s&&%s&&METsig>30)", nm2_metsig_mindphi, btag4cuts, masssbcuts ) ;
 //    fillSet( "h_mindphi_4bSB_metsig_030", "minDeltaPhi20", cuts, keep_data_blind ) ;

 //    sprintf( htitle, "minDeltaPhi20, 4b SB, METsig>50" ) ;
 //    bookSet( "h_mindphi_4bSB_metsig_050", htitle, 32, 0., 3.2 ) ;
 //    sprintf( cuts, "(%s&&%s&&%s&&METsig>50)", nm2_metsig_mindphi, btag4cuts, masssbcuts ) ;
 //    fillSet( "h_mindphi_4bSB_metsig_050", "minDeltaPhi20", cuts, keep_data_blind ) ;

 //    sprintf( htitle, "minDeltaPhi20, 4b SB, METsig>100" ) ;
 //    bookSet( "h_mindphi_4bSB_metsig_100", htitle, 32, 0., 3.2 ) ;
 //    sprintf( cuts, "(%s&&%s&&%s&&METsig>100)", nm2_metsig_mindphi, btag4cuts, masssbcuts ) ;
 //    fillSet( "h_mindphi_4bSB_metsig_100", "minDeltaPhi20", cuts, keep_data_blind ) ;

 //    sprintf( htitle, "minDeltaPhi20, 4b SB, METsig>150" ) ;
 //    bookSet( "h_mindphi_4bSB_metsig_150", htitle, 32, 0., 3.2 ) ;
 //    sprintf( cuts, "(%s&&%s&&%s&&METsig>150)", nm2_metsig_mindphi, btag4cuts, masssbcuts ) ;
 //    fillSet( "h_mindphi_4bSB_metsig_150", "minDeltaPhi20", cuts, keep_data_blind ) ;



 //    sprintf( htitle, "minDeltaPhi20, 4b SIG, no METsig cut" ) ;
 //    bookSet( "h_mindphi_4bSIG_no_metsig", htitle, 32, 0., 3.2 ) ;
 //    sprintf( cuts, "(%s&&%s&&%s)", nm2_metsig_mindphi, btag4cuts, masssigcuts ) ;
 //    fillSet( "h_mindphi_4bSIG_no_metsig", "minDeltaPhi20", cuts, keep_data_blind ) ;

 //    sprintf( htitle, "minDeltaPhi20, 4b SIG, METsig>30" ) ;
 //    bookSet( "h_mindphi_4bSIG_metsig_030", htitle, 32, 0., 3.2 ) ;
 //    sprintf( cuts, "(%s&&%s&&%s&&METsig>30)", nm2_metsig_mindphi, btag4cuts, masssigcuts ) ;
 //    fillSet( "h_mindphi_4bSIG_metsig_030", "minDeltaPhi20", cuts, keep_data_blind ) ;

 //    sprintf( htitle, "minDeltaPhi20, 4b SIG, METsig>50" ) ;
 //    bookSet( "h_mindphi_4bSIG_metsig_050", htitle, 32, 0., 3.2 ) ;
 //    sprintf( cuts, "(%s&&%s&&%s&&METsig>50)", nm2_metsig_mindphi, btag4cuts, masssigcuts ) ;
 //    fillSet( "h_mindphi_4bSIG_metsig_050", "minDeltaPhi20", cuts, keep_data_blind ) ;

 //    sprintf( htitle, "minDeltaPhi20, 4b SIG, METsig>100" ) ;
 //    bookSet( "h_mindphi_4bSIG_metsig_100", htitle, 32, 0., 3.2 ) ;
 //    sprintf( cuts, "(%s&&%s&&%s&&METsig>100)", nm2_metsig_mindphi, btag4cuts, masssigcuts ) ;
 //    fillSet( "h_mindphi_4bSIG_metsig_100", "minDeltaPhi20", cuts, keep_data_blind ) ;

 //    sprintf( htitle, "minDeltaPhi20, 4b SIG, METsig>150" ) ;
 //    bookSet( "h_mindphi_4bSIG_metsig_150", htitle, 32, 0., 3.2 ) ;
 //    sprintf( cuts, "(%s&&%s&&%s&&METsig>150)", nm2_metsig_mindphi, btag4cuts, masssigcuts ) ;
 //    fillSet( "h_mindphi_4bSIG_metsig_150", "minDeltaPhi20", cuts, keep_data_blind ) ;




       char outfile[10000] ;
       sprintf( outfile, "outputfiles/dmc_plots1.root" ) ;
       saveHist( outfile, "h*" ) ;

    } // dmc_fillplots2b.

   //----------------------------


    void bookSet( const char* hname_base, const char* htitle_base, int nbins, double xmin, double xmax ) {

       printf("\n\n") ;
       for ( int ci=0; ci<nComps; ci++ ) {

          char hname[1000] ;
          char htitle[1000] ;

          sprintf( hname, "%s_%s", hname_base, compname[ci] ) ;
          sprintf( htitle, "%s, %s", htitle_base, compname[ci] ) ;

          printf(" bookSet: %s : %s\n", hname, htitle ) ;
          TH1F* hp = new TH1F( hname, htitle, nbins, xmin, xmax ) ;
          if ( compcolor[ci] > 0 ) { hp -> SetFillColor( compcolor[ci] ) ; }
          hp -> Sumw2() ;

       } // ci
       printf("\n\n") ;


    } // bookSet

   //----------------------------

    void fillSet( const char* hname_base, const char* varname, const char* cuts, bool blind_data ) {

       dcan -> Clear() ;
       dcan -> Divide( 2, 3 ) ;
       int cind(1) ;

       printf("\n\n") ;
       for ( int ci=0; ci<nComps; ci++ ) {

          if ( blind_data && ( ci == 0 || strcmp( compname[ci], "data" ) == 0 ) ) continue ;

          dcan -> cd(cind++) ;

          char hname[1000] ;
          char arg1[10000] ;
          char arg2[10000] ;

          sprintf( hname, "%s_%s", hname_base, compname[ci] ) ;
          sprintf( arg1, "%s>>%s", varname, hname ) ;
          if ( ci>0 ) {
             sprintf( arg2, "weight3*19400*(%s)", cuts ) ;
          } else {
             sprintf( arg2, "(%s)", cuts ) ;
          }
          printf(" %s : %s\n", arg1, arg2 ) ;
          compchain[ci] -> Draw( arg1, arg2 ) ;

          TH1F* hp = (TH1F*) gDirectory->FindObject( hname ) ;
          if ( hp == 0x0 ) { printf("\n *** missing hist! %s \n\n", hname ) ; return ; }

          int nbinsx = hp->GetNbinsX() ;
          double last_val     = hp->GetBinContent( nbinsx  ) ;
          double last_err     = hp->GetBinError( nbinsx  ) ;
          double overflow_val = hp->GetBinContent( nbinsx + 1 ) ;
          double overflow_err = hp->GetBinError( nbinsx + 1 ) ;

          hp -> SetBinContent( nbinsx, last_val + overflow_val ) ;
          hp -> SetBinError( nbinsx, sqrt( pow(last_err,2) + pow(overflow_err,2) ) ) ;


          hp -> Draw("hist") ;
          hp -> Draw("esame") ;

          dcan->Update() ;

       } // ci
       printf("\n\n") ;


    } // fillSet

   //----------------------------

  //==========================================================================================


void saveHist(const char* filename, const char* pat)
{

  cout << "\n\n Saving histograms matching " << pat << " in file " << filename << "\n\n" << flush ;

  TList* list = gDirectory->GetList() ;
  TIterator* iter = list->MakeIterator();

  TRegexp re(pat,kTRUE) ;

  TFile outf(filename,"RECREATE") ;
  TObject* obj ;
  while((obj=iter->Next())) {
    if (TString(obj->GetName()).Index(re)>=0) {
      obj->Write() ;
      std::cout << "." ;
    }
  }
  std::cout << std::endl ;
  outf.Close() ;

  delete iter ;
}

//==========================================================================================

