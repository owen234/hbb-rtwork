
#include "TChain.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TH1.h"
#include "TH2.h"
#include "TSystem.h"
#include "histio.c"
#include "TMath.h"
#include "TString.h"



   float dataIntLumiIPB(19399.) ;

   void addoverflow( TH1* hp ) {
      if ( hp==0x0 ) return ;
      int nb = hp -> GetNbinsX() ;
      float newval = hp -> GetBinContent( nb ) + hp -> GetBinContent( nb+1 ) ;
      float newerr = sqrt( pow( hp -> GetBinError( nb ), 2 ) + pow( hp -> GetBinError( nb+1 ), 2 ) ) ;
      hp -> SetBinContent( nb, newval ) ;
      hp -> SetBinError( nb, newerr ) ;
   }

  //================================================================================================

   void fill_qcdstudy1( ) {


      int bins_of_met = 4 ;
      double met_bin_edges[5] = { 30., 50., 100., 150., 10000. } ;



      gDirectory -> Delete( "h*" ) ;

      gStyle -> SetOptStat( "MRi" ) ;
      gStyle -> SetStatW( 0.35 ) ;


    //--- setup chains of reduced trees for the comps.

      printf("\n\n Setting up reduced tree chains.\n\n" ) ;


      char rtdir[10000] = "/Users/owen/work/cms/hadronic-susy-bjets/hbb/reduced-trees-qcd-study-sept30-2013" ;

      printf("\n\n\n   Reduced tree directory: %s\n\n\n", rtdir ) ;



      char pathandfile[10000] ;

      TChain* qcd_chain = new TChain("reducedTree") ;
      TChain* tt_chain  = new TChain("reducedTree") ;

      TChain* qcd1_chain = new TChain("reducedTree") ;
      TChain* qcd2_chain = new TChain("reducedTree") ;
      TChain* qcd3_chain = new TChain("reducedTree") ;

      sprintf( pathandfile, "%s/*BJets*-slimskim.root", rtdir ) ;
      qcd_chain -> Add( pathandfile ) ;

      sprintf( pathandfile, "%s/*BJets_HT-250To500*-slimskim.root", rtdir ) ;
      qcd1_chain -> Add( pathandfile ) ;
      sprintf( pathandfile, "%s/*BJets_HT-500To1000*-slimskim.root", rtdir ) ;
      qcd2_chain -> Add( pathandfile ) ;
      sprintf( pathandfile, "%s/*BJets_HT-1000ToInf*-slimskim.root", rtdir ) ;
      qcd3_chain -> Add( pathandfile ) ;



      sprintf( pathandfile, "%s/*TTJets*-slimskim.root", rtdir ) ;
      tt_chain  -> Add( pathandfile ) ;






     //--- Define cuts.

      printf("\n\n Setting up cuts.\n\n") ;

     //--- These are included in the skim definition of doSlimSkim.c.  Doesn't hurt to apply them here.

      char basiccuts[10000] ;
      sprintf( basiccuts, "cutPV==1&&passCleaning==1&&buggyEvent==0&& MET/caloMET<2 && maxTOBTECjetDeltaMult<40" ) ;

      char triggercuts[10000] ;
      sprintf( triggercuts, "(passMC_DiCentralPFJet30_PFMET80_BTagCSV07==1||passMC_PFMET150==1)" ) ;
      char triggercuts_data[10000] ;
      sprintf( triggercuts_data, "(pass_DiCentralPFJet30_PFMET80_BTagCSV07==1||pass_PFMET150==1||pass_DiCentralPFJet30_PFMHT80==1)" ) ;

      char njetcuts[10000] ;
      sprintf( njetcuts, "njets20>=4&&njets20<=5" ) ;

      char skimcuts[10000] ;
      //--- It's safe both in data and MC to require both triggercuts and triggercuts_data.
      //    In data, passMC_* = pass_*.  In MC, pass_* is always true.
      sprintf( skimcuts, "((%s)&&(%s)&&(%s)&&(%s))", basiccuts, triggercuts, triggercuts_data, njetcuts ) ;


     //--- These are beyond the skim selection.

      char leptonveto[10000] ;
      sprintf( leptonveto, "%s", "nMuons==0&&nElectrons==0&&nIsoPFcands10_010==0&&nTausLoose==0" ) ;

      char maxdrcut[10000] ;
      sprintf( maxdrcut, "%s", "deltaRmax_hh<2.2" ) ;

      char mindphicut[10000] ;
      sprintf( mindphicut, "%s", "((METsig>50&&minDeltaPhi20>0.3)||(METsig<50&&minDeltaPhi20>0.5))" ) ;

      char jet2ptcut[10000] ;
      sprintf( jet2ptcut, "%s", "jetpt2>50" ) ;


      char masssigcuts[10000] ;
      sprintf( masssigcuts, "%s", "deltam<20&&avem>100&&avem<140" ) ;

      char masssbcuts[10000] ;
      sprintf( masssbcuts, "%s", "!(deltam<30&&avem>90&&avem<150)" ) ;

      char btag4bcuts[10000] ;
      sprintf( btag4bcuts, "%s", "CSVbest2>0.898&&CSVbest3>0.679&&CSVbest4>0.244" ) ;

      char btag3bcuts[10000] ;
      sprintf( btag3bcuts, "%s", "CSVbest2>0.898&&CSVbest3>0.679&&CSVbest4<0.244" ) ;

      char btag2bcuts[10000] ;
      sprintf( btag2bcuts, "%s", "CSVbest2>0.898&&CSVbest3<0.679" ) ;

      char allcommoncuts[10000] ;
      sprintf( allcommoncuts, "(%s)&&(%s)&&(%s)&&(%s)&&(%s)", skimcuts, leptonveto, maxdrcut, jet2ptcut, mindphicut ) ;


    //--- METsig

      int nhist_metsig(0) ;
      char metsig_hist_cuts[20][10000] ;
      char metsig_hist_name[20][100] ;

      sprintf( metsig_hist_name[nhist_metsig], "nobtag_nomindphi_nomaxdr" ) ;
      sprintf( metsig_hist_cuts[nhist_metsig], "(%s)&&(%s)&&(%s)", skimcuts, jet2ptcut, leptonveto ) ;
      nhist_metsig++ ;

      sprintf( metsig_hist_name[nhist_metsig], "nobtag_nomindphi" ) ;
      sprintf( metsig_hist_cuts[nhist_metsig], "(%s)&&(%s)&&(%s)&&(%s)", skimcuts, jet2ptcut, leptonveto, maxdrcut ) ;
      nhist_metsig++ ;

      sprintf( metsig_hist_name[nhist_metsig], "nobtag" ) ;
      sprintf( metsig_hist_cuts[nhist_metsig], "(%s)&&(%s)&&(%s)&&(%s)&&(%s)", skimcuts, jet2ptcut, leptonveto, mindphicut, maxdrcut ) ;
      nhist_metsig++ ;

      sprintf( metsig_hist_name[nhist_metsig], "2b" ) ;
      sprintf( metsig_hist_cuts[nhist_metsig], "(%s)&&(%s)&&(%s)&&(%s)&&(%s)&&nbtag_cat==2", skimcuts, jet2ptcut, leptonveto, mindphicut, maxdrcut ) ;
      nhist_metsig++ ;

      sprintf( metsig_hist_name[nhist_metsig], "3b" ) ;
      sprintf( metsig_hist_cuts[nhist_metsig], "(%s)&&(%s)&&(%s)&&(%s)&&(%s)&&nbtag_cat==3", skimcuts, jet2ptcut, leptonveto, mindphicut, maxdrcut ) ;
      nhist_metsig++ ;

      sprintf( metsig_hist_name[nhist_metsig], "4b" ) ;
      sprintf( metsig_hist_cuts[nhist_metsig], "(%s)&&(%s)&&(%s)&&(%s)&&(%s)&&nbtag_cat==4", skimcuts, jet2ptcut, leptonveto, mindphicut, maxdrcut ) ;
      nhist_metsig++ ;























      TH1F* hist_metsig_sigsb[20] ;
      TH1F* hist_metsig_sigsb_fb[20] ;
      TH1F* hist_metsig_sigsb_ub[20] ;

      TH1F* hist_metsig_sig[20] ;
      TH1F* hist_metsig_sig_fb[20] ;

      TH1F* hist_metsig_sb[20] ;
      TH1F* hist_metsig_sb_fb[20] ;

      TH1F* hist_metsig_sigsb_ratio_fb[20] ;





     //--- Nb

      int nhist_nb(0) ;

      char nb_hist_cuts[20][10000] ;
      char nb_hist_name[20][100] ;

      sprintf( nb_hist_name[nhist_nb], "nometsig_nomindphi_nomaxdr" ) ;
      sprintf( nb_hist_cuts[nhist_nb], "(%s)&&(%s)&&(%s)", skimcuts, jet2ptcut, leptonveto ) ;
      nhist_nb++ ;

      sprintf( nb_hist_name[nhist_nb], "nometsig_nomindphi" ) ;
      sprintf( nb_hist_cuts[nhist_nb], "(%s)&&(%s)&&(%s)&&(%s)", skimcuts, jet2ptcut, leptonveto, maxdrcut ) ;
      nhist_nb++ ;

      sprintf( nb_hist_name[nhist_nb], "nometsig" ) ;
      sprintf( nb_hist_cuts[nhist_nb], "(%s)&&(%s)&&(%s)&&(%s)&&(%s)", skimcuts, jet2ptcut, leptonveto, mindphicut, maxdrcut ) ;
      nhist_nb++ ;

      sprintf( nb_hist_name[nhist_nb], "metsig30" ) ;
      sprintf( nb_hist_cuts[nhist_nb], "(%s)&&(%s)&&(%s)&&(%s)&&(%s)&&(METsig>30)", skimcuts, jet2ptcut, leptonveto, mindphicut, maxdrcut ) ;
      nhist_nb++ ;

      sprintf( nb_hist_name[nhist_nb], "metsig1" ) ;
      sprintf( nb_hist_cuts[nhist_nb], "(%s)&&(%s)&&(%s)&&(%s)&&(%s)&&(METsig>30&&METsig<50)", skimcuts, jet2ptcut, leptonveto, mindphicut, maxdrcut ) ;
      nhist_nb++ ;

      sprintf( nb_hist_name[nhist_nb], "metsig2" ) ;
      sprintf( nb_hist_cuts[nhist_nb], "(%s)&&(%s)&&(%s)&&(%s)&&(%s)&&(METsig>50&&METsig<100)", skimcuts, jet2ptcut, leptonveto, mindphicut, maxdrcut ) ;
      nhist_nb++ ;

      sprintf( nb_hist_name[nhist_nb], "metsig3" ) ;
      sprintf( nb_hist_cuts[nhist_nb], "(%s)&&(%s)&&(%s)&&(%s)&&(%s)&&(METsig>100&&METsig<150)", skimcuts, jet2ptcut, leptonveto, mindphicut, maxdrcut ) ;
      nhist_nb++ ;

      sprintf( nb_hist_name[nhist_nb], "metsig4" ) ;
      sprintf( nb_hist_cuts[nhist_nb], "(%s)&&(%s)&&(%s)&&(%s)&&(%s)&&(METsig>150)", skimcuts, jet2ptcut, leptonveto, mindphicut, maxdrcut ) ;
      nhist_nb++ ;

      TH1F* hist_nb_sigsb[20] ;
      TH1F* hist_nb_sig[20] ;
      TH1F* hist_nb_sb[20] ;
      TH1F* hist_nb_sigsb_ratio[20] ;





     //--- SIG,SB

      int nhist_hmasscat(0) ;

      char hmasscat_hist_cuts[20][10000] ;
      char hmasscat_hist_name[20][100] ;

      sprintf( hmasscat_hist_name[nhist_hmasscat], "nometsig_nobtag_nomindphi_nomaxdr" ) ;
      sprintf( hmasscat_hist_cuts[nhist_hmasscat], "(%s)&&(%s)&&(%s)", skimcuts, jet2ptcut, leptonveto ) ;
      nhist_hmasscat++ ;

      sprintf( hmasscat_hist_name[nhist_hmasscat], "nometsig_nobtag_nomindphi" ) ;
      sprintf( hmasscat_hist_cuts[nhist_hmasscat], "(%s)&&(%s)&&(%s)&&(%s)", skimcuts, jet2ptcut, leptonveto, maxdrcut ) ;
      nhist_hmasscat++ ;

      sprintf( hmasscat_hist_name[nhist_hmasscat], "nometsig_nobtag" ) ;
      sprintf( hmasscat_hist_cuts[nhist_hmasscat], "(%s)&&(%s)&&(%s)&&(%s)&&(%s)", skimcuts, jet2ptcut, leptonveto, mindphicut, maxdrcut ) ;
      nhist_hmasscat++ ;

      sprintf( hmasscat_hist_name[nhist_hmasscat], "nometsig" ) ;
      sprintf( hmasscat_hist_cuts[nhist_hmasscat], "(%s)&&(%s)&&(%s)&&(%s)&&(%s)&&(nbtag_cat>=2)", skimcuts, jet2ptcut, leptonveto, mindphicut, maxdrcut ) ;
      nhist_hmasscat++ ;

      sprintf( hmasscat_hist_name[nhist_hmasscat], "nobtag" ) ;
      sprintf( hmasscat_hist_cuts[nhist_hmasscat], "(%s)&&(%s)&&(%s)&&(%s)&&(%s)&&(METsig>30)", skimcuts, jet2ptcut, leptonveto, mindphicut, maxdrcut ) ;
      nhist_hmasscat++ ;

      sprintf( hmasscat_hist_name[nhist_hmasscat], "allcuts" ) ;
      sprintf( hmasscat_hist_cuts[nhist_hmasscat], "(%s)&&(%s)&&(%s)&&(%s)&&(%s)&&(METsig>30)&&(nbtag_cat>=2)", skimcuts, jet2ptcut, leptonveto, mindphicut, maxdrcut ) ;
      nhist_hmasscat++ ;

      TH1F* hist_hmasscat[20] ;







     //--- Higgs mass distributions, ave mass

      int nhist_avem(0) ;

      char avem_hist_cuts[20][10000] ;
      char avem_hist_name[20][100] ;

      sprintf( avem_hist_name[nhist_avem], "nometsig_nobtag_nomindphi_nomaxdr" ) ;
      sprintf( avem_hist_cuts[nhist_avem], "(%s)&&(%s)&&(%s)", skimcuts, jet2ptcut, leptonveto ) ;
      nhist_avem++ ;

      sprintf( avem_hist_name[nhist_avem], "nometsig_nobtag_nomindphi" ) ;
      sprintf( avem_hist_cuts[nhist_avem], "(%s)&&(%s)&&(%s)&&(%s)", skimcuts, jet2ptcut, leptonveto, maxdrcut ) ;
      nhist_avem++ ;

      sprintf( avem_hist_name[nhist_avem], "nometsig_nobtag" ) ;
      sprintf( avem_hist_cuts[nhist_avem], "(%s)&&(%s)&&(%s)&&(%s)&&(%s)", skimcuts, jet2ptcut, leptonveto, mindphicut, maxdrcut ) ;
      nhist_avem++ ;

      sprintf( avem_hist_name[nhist_avem], "nometsig" ) ;
      sprintf( avem_hist_cuts[nhist_avem], "(%s)&&(%s)&&(%s)&&(%s)&&(%s)&&(nbtag_cat>=2)", skimcuts, jet2ptcut, leptonveto, mindphicut, maxdrcut ) ;
      nhist_avem++ ;

      sprintf( avem_hist_name[nhist_avem], "nobtag" ) ;
      sprintf( avem_hist_cuts[nhist_avem], "(%s)&&(%s)&&(%s)&&(%s)&&(%s)&&(METsig>30)", skimcuts, jet2ptcut, leptonveto, mindphicut, maxdrcut ) ;
      nhist_avem++ ;

      sprintf( avem_hist_name[nhist_avem], "allcuts" ) ;
      sprintf( avem_hist_cuts[nhist_avem], "(%s)&&(%s)&&(%s)&&(%s)&&(%s)&&(METsig>30)&&(nbtag_cat>=2)", skimcuts, jet2ptcut, leptonveto, mindphicut, maxdrcut ) ;
      nhist_avem++ ;

      TH1F* hist_avem[20] ;



     //--- Higgs mass distributions, delta mass

      int nhist_deltam(0) ;

      char deltam_hist_cuts[20][10000] ;
      char deltam_hist_name[20][100] ;

      sprintf( deltam_hist_name[nhist_deltam], "nometsig_nobtag_nomindphi_nomaxdr" ) ;
      sprintf( deltam_hist_cuts[nhist_deltam], "(%s)&&(%s)&&(%s)", skimcuts, jet2ptcut, leptonveto ) ;
      nhist_deltam++ ;

      sprintf( deltam_hist_name[nhist_deltam], "nometsig_nobtag_nomindphi" ) ;
      sprintf( deltam_hist_cuts[nhist_deltam], "(%s)&&(%s)&&(%s)&&(%s)", skimcuts, jet2ptcut, leptonveto, maxdrcut ) ;
      nhist_deltam++ ;

      sprintf( deltam_hist_name[nhist_deltam], "nometsig_nobtag" ) ;
      sprintf( deltam_hist_cuts[nhist_deltam], "(%s)&&(%s)&&(%s)&&(%s)&&(%s)", skimcuts, jet2ptcut, leptonveto, mindphicut, maxdrcut ) ;
      nhist_deltam++ ;

      sprintf( deltam_hist_name[nhist_deltam], "nometsig" ) ;
      sprintf( deltam_hist_cuts[nhist_deltam], "(%s)&&(%s)&&(%s)&&(%s)&&(%s)&&(nbtag_cat>=2)", skimcuts, jet2ptcut, leptonveto, mindphicut, maxdrcut ) ;
      nhist_deltam++ ;

      sprintf( deltam_hist_name[nhist_deltam], "nobtag" ) ;
      sprintf( deltam_hist_cuts[nhist_deltam], "(%s)&&(%s)&&(%s)&&(%s)&&(%s)&&(METsig>30)", skimcuts, jet2ptcut, leptonveto, mindphicut, maxdrcut ) ;
      nhist_deltam++ ;

      sprintf( deltam_hist_name[nhist_deltam], "allcuts" ) ;
      sprintf( deltam_hist_cuts[nhist_deltam], "(%s)&&(%s)&&(%s)&&(%s)&&(%s)&&(METsig>30)&&(nbtag_cat>=2)", skimcuts, jet2ptcut, leptonveto, mindphicut, maxdrcut ) ;
      nhist_deltam++ ;

      TH1F* hist_deltam[20] ;

      TH2F* hist_deltam_vs_avem[20] ;






     //--- prepare histograms.

      printf("\n\n Booking histograms.\n\n") ;

      char hname[1000] ;
      char htitle[1000] ;

      for ( int hi=0; hi<nhist_metsig; hi++ ) {

         sprintf( htitle, "METsig, %s", metsig_hist_name[hi] ) ;
         sprintf( hname, "h_metsig_sigsb_%s", metsig_hist_name[hi] ) ;
         hist_metsig_sigsb[hi] = new TH1F( hname, htitle, bins_of_met, met_bin_edges ) ;
         hist_metsig_sigsb[hi] -> Sumw2() ;
         sprintf( hname, "h_metsig_sigsb_%s_fb", metsig_hist_name[hi] ) ;
         hist_metsig_sigsb_fb[hi] = new TH1F( hname, htitle, bins_of_met, 0.5, bins_of_met+0.5 ) ;
         hist_metsig_sigsb_fb[hi] -> Sumw2() ;
         sprintf( hname, "h_metsig_sigsb_%s_ub", metsig_hist_name[hi] ) ;
         hist_metsig_sigsb_ub[hi] = new TH1F( hname, htitle, 50, 0., 250. ) ;
         hist_metsig_sigsb_ub[hi] -> Sumw2() ;

         sprintf( htitle, "METsig, SIG, %s", metsig_hist_name[hi] ) ;
         sprintf( hname, "h_metsig_sig_%s", metsig_hist_name[hi] ) ;
         hist_metsig_sig[hi] = new TH1F( hname, htitle, bins_of_met, met_bin_edges ) ;
         hist_metsig_sig[hi] -> Sumw2() ;
         sprintf( hname, "h_metsig_sig_%s_fb", metsig_hist_name[hi] ) ;
         hist_metsig_sig_fb[hi] = new TH1F( hname, htitle, bins_of_met, 0.5, bins_of_met+0.5 ) ;
         hist_metsig_sig_fb[hi] -> Sumw2() ;

         sprintf( htitle, "METsig, SB, %s", metsig_hist_name[hi] ) ;
         sprintf( hname, "h_metsig_sb_%s", metsig_hist_name[hi] ) ;
         hist_metsig_sb[hi] = new TH1F( hname, htitle, bins_of_met, met_bin_edges ) ;
         hist_metsig_sb[hi] -> Sumw2() ;
         sprintf( hname, "h_metsig_sb_%s_fb", metsig_hist_name[hi] ) ;
         hist_metsig_sb_fb[hi] = new TH1F( hname, htitle, bins_of_met, 0.5, bins_of_met+0.5 ) ;
         hist_metsig_sb_fb[hi] -> Sumw2() ;

         sprintf( htitle, "METsig, SIG/SB ratio, %s", metsig_hist_name[hi] ) ;
         sprintf( hname, "h_metsig_sigsb_ratio_%s_fb", metsig_hist_name[hi] ) ;
         hist_metsig_sigsb_ratio_fb[hi] = new TH1F( hname, htitle, bins_of_met, 0.5, bins_of_met+0.5 ) ;
         hist_metsig_sigsb_ratio_fb[hi] -> Sumw2() ;

      } // hi.

      TH1F* h_metsig_ttbar_allcuts_ub = new TH1F( "h_metsig_ttbar_allcuts_ub", "METsig, ttbar, allcuts", 50, 0., 250. ) ;
      h_metsig_ttbar_allcuts_ub -> Sumw2() ;

      TH1F* h_metsig_ttbar_sigsb_allcuts = new TH1F( "h_metsig_ttbar_sigsb_allcuts", "METsig, ttbar, allcuts", bins_of_met, met_bin_edges ) ;
      h_metsig_ttbar_sigsb_allcuts -> Sumw2() ;
      TH1F* h_metsig_ttbar_sigsb_allcuts_fb = new TH1F( "h_metsig_ttbar_sigsb_allcuts_fb", "METsig, ttbar, allcuts", bins_of_met, 0.5, bins_of_met+0.5 ) ;
      h_metsig_ttbar_sigsb_allcuts_fb -> Sumw2() ;
      TH1F* h_metsig_ttbar_sig_allcuts = new TH1F( "h_metsig_ttbar_sig_allcuts", "METsig, SIG, ttbar, allcuts", bins_of_met, met_bin_edges ) ;
      h_metsig_ttbar_sig_allcuts -> Sumw2() ;
      TH1F* h_metsig_ttbar_sig_allcuts_fb = new TH1F( "h_metsig_ttbar_sig_allcuts_fb", "METsig, SIG, ttbar, allcuts", bins_of_met, 0.5, bins_of_met+0.5 ) ;
      h_metsig_ttbar_sig_allcuts_fb -> Sumw2() ;
      TH1F* h_metsig_ttbar_sb_allcuts = new TH1F( "h_metsig_ttbar_sb_allcuts", "METsig, SB, ttbar, allcuts", bins_of_met, met_bin_edges ) ;
      h_metsig_ttbar_sb_allcuts -> Sumw2() ;
      TH1F* h_metsig_ttbar_sb_allcuts_fb = new TH1F( "h_metsig_ttbar_sb_allcuts_fb", "METsig, SB, ttbar, allcuts", bins_of_met, 0.5, bins_of_met+0.5 ) ;
      h_metsig_ttbar_sb_allcuts_fb -> Sumw2() ;
      TH1F* h_metsig_ttbar_sigsb_ratio_allcuts = new TH1F( "h_metsig_ttbar_sigsb_ratio_allcuts", "METsig, SIG/SB ratio, ttbar, allcuts", bins_of_met, met_bin_edges ) ;
      h_metsig_ttbar_sigsb_ratio_allcuts -> Sumw2() ;
      TH1F* h_metsig_ttbar_sigsb_ratio_allcuts_fb = new TH1F( "h_metsig_ttbar_sigsb_ratio_allcuts_fb", "METsig, SIG/SB ratio, ttbar, allcuts", bins_of_met, 0.5, bins_of_met+0.5 ) ;
      h_metsig_ttbar_sigsb_ratio_allcuts_fb -> Sumw2() ;






      for ( int hi=0; hi<nhist_nb; hi++ ) {

         sprintf( htitle, "nb, %s", nb_hist_name[hi] ) ;
         sprintf( hname, "h_nb_sigsb_%s", nb_hist_name[hi] ) ;
         hist_nb_sigsb[hi] = new TH1F( hname, htitle, 5, -0.5, 4.5 ) ;
         hist_nb_sigsb[hi] -> Sumw2() ;

         sprintf( htitle, "nb, SIG, %s", nb_hist_name[hi] ) ;
         sprintf( hname, "h_nb_sig_%s", nb_hist_name[hi] ) ;
         hist_nb_sig[hi] = new TH1F( hname, htitle, 5, -0.5, 4.5 ) ;
         hist_nb_sig[hi] -> Sumw2() ;

         sprintf( htitle, "nb, SB, %s", nb_hist_name[hi] ) ;
         sprintf( hname, "h_nb_sb_%s", nb_hist_name[hi] ) ;
         hist_nb_sb[hi] = new TH1F( hname, htitle, 5, -0.5, 4.5 ) ;
         hist_nb_sb[hi] -> Sumw2() ;

         sprintf( htitle, "nb, SIG/SB ratio, %s", nb_hist_name[hi] ) ;
         sprintf( hname, "h_nb_sigsb_ratio_%s", nb_hist_name[hi] ) ;
         hist_nb_sigsb_ratio[hi] = new TH1F( hname, htitle, 5, -0.5, 4.5 ) ;
         hist_nb_sigsb_ratio[hi] -> Sumw2() ;


      } // hi.

      TH1F* h_nb_ttbar_sigsb_allcuts = new TH1F( "h_nb_ttbar_sigsb_allcuts", "Nb, ttbar, allcuts", 5, -0.5, 4.5 ) ;
      h_nb_ttbar_sigsb_allcuts -> Sumw2() ;
      TH1F* h_nb_ttbar_sig_allcuts = new TH1F( "h_nb_ttbar_sig_allcuts", "Nb, ttbar, allcuts", 5, -0.5, 4.5 ) ;
      h_nb_ttbar_sig_allcuts -> Sumw2() ;
      TH1F* h_nb_ttbar_sb_allcuts = new TH1F( "h_nb_ttbar_sb_allcuts", "Nb, ttbar, allcuts", 5, -0.5, 4.5 ) ;
      h_nb_ttbar_sb_allcuts -> Sumw2() ;
      TH1F* h_nb_ttbar_sigsb_ratio_allcuts = new TH1F( "h_nb_ttbar_sigsb_ratio_allcuts", "Nb, ttbar, allcuts", 5, -0.5, 4.5 ) ;
      h_nb_ttbar_sigsb_ratio_allcuts -> Sumw2() ;



      for ( int hi=0; hi<nhist_hmasscat; hi++ ) {

         sprintf( htitle, "hmasscat, %s", hmasscat_hist_name[hi] ) ;
         sprintf( hname, "h_hmasscat_%s", hmasscat_hist_name[hi] ) ;
         hist_hmasscat[hi] = new TH1F( hname, htitle, 2, -0.5, 1.5 ) ;
         hist_hmasscat[hi] -> Sumw2() ;

      } // hi.


      for ( int hi=0; hi<nhist_avem; hi++ ) {

         sprintf( htitle, "avem, %s", avem_hist_name[hi] ) ;
         sprintf( hname, "h_avem_%s", avem_hist_name[hi] ) ;
         hist_avem[hi] = new TH1F( hname, htitle, 40, 0., 400. ) ;
         hist_avem[hi] -> Sumw2() ;

      } // hi.

      TH1F* h_avem_ttbar_allcuts = new TH1F( "h_avem_ttbar_allcuts", "Ave mass, ttbar, all cuts", 40, 0., 400. ) ;
      h_avem_ttbar_allcuts -> Sumw2() ;


      for ( int hi=0; hi<nhist_deltam; hi++ ) {

         sprintf( htitle, "deltam, %s", deltam_hist_name[hi] ) ;
         sprintf( hname, "h_deltam_%s", deltam_hist_name[hi] ) ;
         hist_deltam[hi] = new TH1F( hname, htitle, 30, 0., 300. ) ;
         hist_deltam[hi] -> Sumw2() ;

         sprintf( htitle, "deltam vs avem, %s", deltam_hist_name[hi] ) ;
         sprintf( hname, "h_deltam_vs_avem_%s", deltam_hist_name[hi] ) ;
         hist_deltam_vs_avem[hi] = new TH2F( hname, htitle, 40, 0., 400., 30, 0., 300. ) ;
         hist_deltam_vs_avem[hi] -> Sumw2() ;

      } // hi.

      TH1F* h_deltam_ttbar_allcuts = new TH1F( "h_deltam_ttbar_allcuts", "Delta mass, ttbar, all cuts", 30, 0., 300. ) ;
      h_deltam_ttbar_allcuts -> Sumw2() ;

      TH2F* h_deltam_vs_avem_ttbar_allcuts = new TH2F( "h_deltam_vs_avem_ttbar_allcuts", "Delta m vs Ave mass, ttbar, all cuts", 40, 0., 400., 30, 0., 300. ) ;
      h_deltam_vs_avem_ttbar_allcuts -> Sumw2() ;


















     //--- fill the histograms.

      TCanvas* can = new TCanvas("can","plots") ;

      printf("\n\n Filling the histograms.\n\n" ) ; fflush(stdout) ;

      char arg1[1000] ;
      char allcuts[10000] ;







      //--- 4b, no METsig, no minDeltaPhi

      TH1F* h_avem_4b_nometsig_nomindphi_nodmcut = new TH1F( "h_avem_4b_nometsig_nomindphi_nodmcut", "Ave m, QCD, 4b, no METsig, no minDphi, no Dm cut", 40, 0., 400. ) ;
      h_avem_4b_nometsig_nomindphi_nodmcut -> Sumw2() ;

      sprintf( arg1, "avem>>h_avem_4b_nometsig_nomindphi_nodmcut" ) ;
      sprintf( allcuts, "(%s&&%s&&%s&&%s&&nbtag_cat==4)*weight3*%.0f", skimcuts, jet2ptcut, leptonveto, maxdrcut, dataIntLumiIPB ) ;
      printf("\n %s : %s\n", arg1, allcuts ) ; fflush(stdout) ;
      qcd_chain -> Draw( arg1, allcuts ) ;
      addoverflow( h_avem_4b_nometsig_nomindphi_nodmcut ) ;
      h_avem_4b_nometsig_nomindphi_nodmcut -> Draw() ;
      can->Update() ; can->Draw() ;




      TH1F* h_avem_4b_nometsig_nomindphi = new TH1F( "h_avem_4b_nometsig_nomindphi", "Ave m, QCD, 4b, no METsig, no minDphi", 40, 0., 400. ) ;
      h_avem_4b_nometsig_nomindphi -> Sumw2() ;

      sprintf( arg1, "avem>>h_avem_4b_nometsig_nomindphi" ) ;
      sprintf( allcuts, "(%s&&%s&&%s&&%s&&nbtag_cat==4&&abs(deltam)<20)*weight3*%.0f", skimcuts, jet2ptcut, leptonveto, maxdrcut, dataIntLumiIPB ) ;
      printf("\n %s : %s\n", arg1, allcuts ) ; fflush(stdout) ;
      qcd_chain -> Draw( arg1, allcuts ) ;
      addoverflow( h_avem_4b_nometsig_nomindphi ) ;
      h_avem_4b_nometsig_nomindphi -> Draw() ;
      can->Update() ; can->Draw() ;



      TH1F* h_deltam_4b_nometsig_nomindphi_noavemcut = new TH1F( "h_deltam_4b_nometsig_nomindphi_noavemcut", "Delta m, QCD, 4b, no METsig, no minDphi, no avem cut", 30, 0., 300. ) ;
      h_deltam_4b_nometsig_nomindphi_noavemcut -> Sumw2() ;

      sprintf( arg1, "deltam>>h_deltam_4b_nometsig_nomindphi_noavemcut" ) ;
      sprintf( allcuts, "(%s&&%s&&%s&&%s&&nbtag_cat==4)*weight3*%.0f", skimcuts, jet2ptcut, leptonveto, maxdrcut, dataIntLumiIPB ) ;
      printf("\n %s : %s\n", arg1, allcuts ) ; fflush(stdout) ;
      qcd_chain -> Draw( arg1, allcuts ) ;
      addoverflow( h_deltam_4b_nometsig_nomindphi_noavemcut ) ;
      h_deltam_4b_nometsig_nomindphi_noavemcut -> Draw() ;
      can->Update() ; can->Draw() ;



      TH1F* h_deltam_4b_nometsig_nomindphi = new TH1F( "h_deltam_4b_nometsig_nomindphi", "Delta m, QCD, 4b, no METsig, no minDphi", 30, 0., 300. ) ;
      h_deltam_4b_nometsig_nomindphi -> Sumw2() ;

      sprintf( arg1, "deltam>>h_deltam_4b_nometsig_nomindphi" ) ;
      sprintf( allcuts, "(%s&&%s&&%s&&%s&&nbtag_cat==4&&avem>100&&avem<140)*weight3*%.0f", skimcuts, jet2ptcut, leptonveto, maxdrcut, dataIntLumiIPB ) ;
      printf("\n %s : %s\n", arg1, allcuts ) ; fflush(stdout) ;
      qcd_chain -> Draw( arg1, allcuts ) ;
      addoverflow( h_deltam_4b_nometsig_nomindphi ) ;
      h_deltam_4b_nometsig_nomindphi -> Draw() ;
      can->Update() ; can->Draw() ;




    //======= QCD, HT plots
      TH1F* h_ht_qcd1 = new TH1F( "h_ht_qcd1", "HT, QCD, 250 to 500 sample", 60, 0., 1200. ) ;
      h_ht_qcd1 -> Sumw2() ;
      TH1F* h_ht_qcd2 = new TH1F( "h_ht_qcd2", "HT, QCD, 500 to 1000 sample", 60, 0., 1200. ) ;
      h_ht_qcd2 -> Sumw2() ;
      TH1F* h_ht_qcd3 = new TH1F( "h_ht_qcd3", "HT, QCD, >1000 sample", 60, 0., 1200. ) ;
      h_ht_qcd3 -> Sumw2() ;
      TH1F* h_ht_qcd  = new TH1F( "h_ht_qcd", "HT, QCD, all samples", 60, 0., 1200. ) ;
      h_ht_qcd -> Sumw2() ;

      sprintf( arg1, "HT>>h_ht_qcd1" ) ;
      sprintf( allcuts, "(%s&&%s&&%s&&%s)*weight3*%.0f", skimcuts, jet2ptcut, leptonveto, maxdrcut, dataIntLumiIPB ) ;
      printf("\n %s : %s\n", arg1, allcuts ) ; fflush(stdout) ;
      qcd1_chain -> Draw( arg1, allcuts ) ;
      addoverflow( h_ht_qcd1 ) ;
      h_ht_qcd1 -> Draw() ;
      can->Update() ; can->Draw() ;

      sprintf( arg1, "HT>>h_ht_qcd2" ) ;
      sprintf( allcuts, "(%s&&%s&&%s&&%s)*weight3*%.0f", skimcuts, jet2ptcut, leptonveto, maxdrcut, dataIntLumiIPB ) ;
      printf("\n %s : %s\n", arg1, allcuts ) ; fflush(stdout) ;
      qcd2_chain -> Draw( arg1, allcuts ) ;
      addoverflow( h_ht_qcd2 ) ;
      h_ht_qcd2 -> Draw() ;
      can->Update() ; can->Draw() ;

      sprintf( arg1, "HT>>h_ht_qcd3" ) ;
      sprintf( allcuts, "(%s&&%s&&%s&&%s)*weight3*%.0f", skimcuts, jet2ptcut, leptonveto, maxdrcut, dataIntLumiIPB ) ;
      printf("\n %s : %s\n", arg1, allcuts ) ; fflush(stdout) ;
      qcd3_chain -> Draw( arg1, allcuts ) ;
      addoverflow( h_ht_qcd3 ) ;
      h_ht_qcd3 -> Draw() ;
      can->Update() ; can->Draw() ;

      sprintf( arg1, "HT>>h_ht_qcd" ) ;
      sprintf( allcuts, "(%s&&%s&&%s&&%s)*weight3*%.0f", skimcuts, jet2ptcut, leptonveto, maxdrcut, dataIntLumiIPB ) ;
      printf("\n %s : %s\n", arg1, allcuts ) ; fflush(stdout) ;
      qcd_chain -> Draw( arg1, allcuts ) ;
      addoverflow( h_ht_qcd ) ;
      h_ht_qcd -> Draw() ;
      can->Update() ; can->Draw() ;


    //======= ttbar, HT plot

      TH1F* h_ht_ttbar  = new TH1F( "h_ht_ttbar", "HT, ttbar", 60, 0., 1200. ) ;
      h_ht_ttbar -> Sumw2() ;
      sprintf( arg1, "HT>>h_ht_ttbar" ) ;
      sprintf( allcuts, "(%s&&nbtag_cat>=2)*weight3*%.0f", allcommoncuts, dataIntLumiIPB ) ;
      printf("\n %s : %s\n", arg1, allcuts ) ; fflush(stdout) ;
      tt_chain -> Draw( arg1, allcuts ) ;
      addoverflow( h_ht_ttbar ) ;
      h_ht_ttbar -> Draw() ;
      can->Update() ; can->Draw() ;






    //====== QCD, METsig ------------------------------------------------------------------------

      for ( int hi=0; hi<nhist_metsig; hi++ ) {

         printf("\n\n ++++++++ %s \n\n", metsig_hist_name[hi] ) ;

         sprintf( arg1, "METsig>>h_metsig_sigsb_%s", metsig_hist_name[hi] ) ;
         sprintf( allcuts, "(%s)*weight3*%.0f", metsig_hist_cuts[hi], dataIntLumiIPB ) ;
         printf("\n %s : %s\n", arg1, allcuts ) ; fflush(stdout) ;
         qcd_chain -> Draw( arg1, allcuts ) ;
         can->Update() ; can->Draw() ;
         hist_metsig_sigsb[hi] -> Print("all") ;

         for ( int bi=1; bi<=bins_of_met; bi++ ) {
            hist_metsig_sigsb_fb[hi] -> SetBinContent( bi, hist_metsig_sigsb[hi] -> GetBinContent(bi) ) ;
            hist_metsig_sigsb_fb[hi] -> SetBinError( bi, hist_metsig_sigsb[hi] -> GetBinError(bi) ) ;
            char bin_label[100] ;
            sprintf( bin_label, "S bin %d", bi ) ;
            hist_metsig_sigsb_fb[hi] -> GetXaxis() -> SetBinLabel( bi, bin_label ) ;
         } // bi.

         hist_metsig_sigsb_fb[hi] -> Draw() ;
         can->Update() ; can->Draw() ;

         sprintf( arg1, "METsig>>h_metsig_sigsb_%s_ub", metsig_hist_name[hi] ) ;
         printf("\n %s : %s\n", arg1, allcuts ) ; fflush(stdout) ;
         qcd_chain -> Draw( arg1, allcuts ) ;
         can->Update() ; can->Draw() ;


         printf("\n\n ++++++++ %s, SIG \n\n", metsig_hist_name[hi] ) ;

         sprintf( arg1, "METsig>>h_metsig_sig_%s", metsig_hist_name[hi] ) ;
         sprintf( allcuts, "(%s&&%s)*weight3*%.0f", metsig_hist_cuts[hi], masssigcuts, dataIntLumiIPB ) ;
         printf("\n %s : %s\n", arg1, allcuts ) ; fflush(stdout) ;
         qcd_chain -> Draw( arg1, allcuts ) ;
         can->Update() ; can->Draw() ;
         hist_metsig_sig[hi] -> Print("all") ;

         for ( int bi=1; bi<=bins_of_met; bi++ ) {
            hist_metsig_sig_fb[hi] -> SetBinContent( bi, hist_metsig_sig[hi] -> GetBinContent(bi) ) ;
            hist_metsig_sig_fb[hi] -> SetBinError( bi, hist_metsig_sig[hi] -> GetBinError(bi) ) ;
            char bin_label[100] ;
            sprintf( bin_label, "S bin %d", bi ) ;
            hist_metsig_sig_fb[hi] -> GetXaxis() -> SetBinLabel( bi, bin_label ) ;
         } // bi.

         hist_metsig_sig_fb[hi] -> Draw() ;
         can->Update() ; can->Draw() ;



         printf("\n\n ++++++++ %s, SB \n\n", metsig_hist_name[hi] ) ;

         sprintf( arg1, "METsig>>h_metsig_sb_%s", metsig_hist_name[hi] ) ;
         sprintf( allcuts, "(%s&&%s)*weight3*%.0f", metsig_hist_cuts[hi], masssbcuts, dataIntLumiIPB ) ;
         printf("\n %s : %s\n", arg1, allcuts ) ; fflush(stdout) ;
         qcd_chain -> Draw( arg1, allcuts ) ;
         can->Update() ; can->Draw() ;
         hist_metsig_sb[hi] -> Print("all") ;

         for ( int bi=1; bi<=bins_of_met; bi++ ) {
            hist_metsig_sb_fb[hi] -> SetBinContent( bi, hist_metsig_sb[hi] -> GetBinContent(bi) ) ;
            hist_metsig_sb_fb[hi] -> SetBinError( bi, hist_metsig_sb[hi] -> GetBinError(bi) ) ;
            char bin_label[100] ;
            sprintf( bin_label, "S bin %d", bi ) ;
            hist_metsig_sb_fb[hi] -> GetXaxis() -> SetBinLabel( bi, bin_label ) ;
         } // bi.

         hist_metsig_sb_fb[hi] -> Draw() ;
         can->Update() ; can->Draw() ;



         printf("\n\n ++++++++ %s, SIG/SB ratio \n\n", metsig_hist_name[hi] ) ;

         for ( int bi=1; bi<=bins_of_met; bi++ ) {

            float sig_val = hist_metsig_sig[hi] -> GetBinContent(bi) ;
            float sig_err = hist_metsig_sig[hi] -> GetBinError(bi) ;
            float sb_val  = hist_metsig_sb[hi]  -> GetBinContent(bi) ;
            float sb_err  = hist_metsig_sb[hi]  -> GetBinError(bi) ;

            float ratio_val(0.), ratio_err(0.) ;
            if ( sb_val > 0 ) {
               ratio_val = sig_val / sb_val ;
               if ( sig_val > 0 && sig_err > 0 ) {
                  ratio_err = ratio_val * sqrt( pow( sig_err/sig_val, 2 ) + pow( sb_err/sb_val, 2 ) ) ;
               }
            }

            hist_metsig_sigsb_ratio_fb[hi] -> SetBinContent( bi, ratio_val ) ;
            hist_metsig_sigsb_ratio_fb[hi] -> SetBinError( bi, ratio_err ) ;

            char bin_label[100] ;
            sprintf( bin_label, "S bin %d", bi ) ;
            hist_metsig_sigsb_ratio_fb[hi] -> GetXaxis() -> SetBinLabel( bi, bin_label ) ;

            printf(" %s  SIG/SB ratio, S bin %d : %.3f +/- %.3f\n", metsig_hist_name[hi], bi, ratio_val, ratio_err ) ;

         } // bi.


      } // hi.

    //====== End QCD, METsig ------------------------------------------------------------------------

    //====== ttbar, METsig ------------------------------------------------------------------------

      printf("\n\n ++++++++ h_metsig_ttbar_allcuts_ub \n\n" ) ;

      sprintf( arg1, "METsig>>h_metsig_ttbar_allcuts_ub" ) ;
      sprintf( allcuts, "(%s&&nbtag_cat>=2)*weight3*%.0f", allcommoncuts, dataIntLumiIPB ) ;
      printf("\n %s : %s\n", arg1, allcuts ) ; fflush(stdout) ;
      tt_chain -> Draw( arg1, allcuts ) ;
      addoverflow( h_metsig_ttbar_allcuts_ub ) ;
      h_metsig_ttbar_allcuts_ub -> Draw() ;
      can->Update() ; can->Draw() ;

      printf("\n\n ++++++++  \n\n" ) ;

      sprintf( arg1, "METsig>>h_metsig_ttbar_sigsb_allcuts" ) ;
      sprintf( allcuts, "(%s&&nbtag_cat>=2)*weight3*%.0f", allcommoncuts, dataIntLumiIPB ) ;
      printf("\n %s : %s\n", arg1, allcuts ) ; fflush(stdout) ;
      tt_chain -> Draw( arg1, allcuts ) ;
      can->Update() ; can->Draw() ;
      h_metsig_ttbar_sigsb_allcuts -> Print("all") ;

      for ( int bi=1; bi<=bins_of_met; bi++ ) {
         h_metsig_ttbar_sigsb_allcuts_fb -> SetBinContent( bi, h_metsig_ttbar_sigsb_allcuts -> GetBinContent(bi) ) ;
         h_metsig_ttbar_sigsb_allcuts_fb -> SetBinError( bi, h_metsig_ttbar_sigsb_allcuts -> GetBinError(bi) ) ;
         char bin_label[100] ;
         sprintf( bin_label, "S bin %d", bi ) ;
         h_metsig_ttbar_sigsb_allcuts_fb -> GetXaxis() -> SetBinLabel( bi, bin_label ) ;
      } // bi.

      h_metsig_ttbar_sigsb_allcuts_fb -> Draw() ;
      can->Update() ; can->Draw() ;



      printf("\n\n ++++++++ SIG \n\n" ) ;

      sprintf( arg1, "METsig>>h_metsig_ttbar_sig_allcuts" ) ;
      sprintf( allcuts, "(%s&&%s&&nbtag_cat>=2)*weight3*%.0f", allcommoncuts, masssigcuts, dataIntLumiIPB ) ;
      printf("\n %s : %s\n", arg1, allcuts ) ; fflush(stdout) ;
      tt_chain -> Draw( arg1, allcuts ) ;
      can->Update() ; can->Draw() ;
      h_metsig_ttbar_sig_allcuts -> Print("all") ;

      for ( int bi=1; bi<=bins_of_met; bi++ ) {
         h_metsig_ttbar_sig_allcuts_fb -> SetBinContent( bi, h_metsig_ttbar_sig_allcuts -> GetBinContent(bi) ) ;
         h_metsig_ttbar_sig_allcuts_fb -> SetBinError( bi, h_metsig_ttbar_sig_allcuts -> GetBinError(bi) ) ;
         char bin_label[100] ;
         sprintf( bin_label, "S bin %d", bi ) ;
         h_metsig_ttbar_sig_allcuts_fb -> GetXaxis() -> SetBinLabel( bi, bin_label ) ;
      } // bi.

      h_metsig_ttbar_sig_allcuts_fb -> Draw() ;
      can->Update() ; can->Draw() ;





      printf("\n\n ++++++++ SB \n\n" ) ;

      sprintf( arg1, "METsig>>h_metsig_ttbar_sb_allcuts" ) ;
      sprintf( allcuts, "(%s&&%s&&nbtag_cat>=2)*weight3*%.0f", allcommoncuts, masssbcuts, dataIntLumiIPB ) ;
      printf("\n %s : %s\n", arg1, allcuts ) ; fflush(stdout) ;
      tt_chain -> Draw( arg1, allcuts ) ;
      can->Update() ; can->Draw() ;
      h_metsig_ttbar_sb_allcuts -> Print("all") ;

      for ( int bi=1; bi<=bins_of_met; bi++ ) {
         h_metsig_ttbar_sb_allcuts_fb -> SetBinContent( bi, h_metsig_ttbar_sb_allcuts -> GetBinContent(bi) ) ;
         h_metsig_ttbar_sb_allcuts_fb -> SetBinError( bi, h_metsig_ttbar_sb_allcuts -> GetBinError(bi) ) ;
         char bin_label[100] ;
         sprintf( bin_label, "S bin %d", bi ) ;
         h_metsig_ttbar_sb_allcuts_fb -> GetXaxis() -> SetBinLabel( bi, bin_label ) ;
      } // bi.

      h_metsig_ttbar_sb_allcuts_fb -> Draw() ;
      can->Update() ; can->Draw() ;







      printf("\n\n ++++++++ SIG/SB ratio \n\n" ) ;

      for ( int bi=1; bi<=bins_of_met; bi++ ) {

         float sig_val = h_metsig_ttbar_sig_allcuts -> GetBinContent(bi) ;
         float sig_err = h_metsig_ttbar_sig_allcuts -> GetBinError(bi) ;
         float sb_val  = h_metsig_ttbar_sb_allcuts  -> GetBinContent(bi) ;
         float sb_err  = h_metsig_ttbar_sb_allcuts  -> GetBinError(bi) ;

         float ratio_val(0.), ratio_err(0.) ;
         if ( sb_val > 0 ) {
            ratio_val = sig_val / sb_val ;
            if ( sig_val > 0 && sig_err > 0 ) {
               ratio_err = ratio_val * sqrt( pow( sig_err/sig_val, 2 ) + pow( sb_err/sb_val, 2 ) ) ;
            }
         }

         h_metsig_ttbar_sigsb_ratio_allcuts_fb -> SetBinContent( bi, ratio_val ) ;
         h_metsig_ttbar_sigsb_ratio_allcuts_fb -> SetBinError( bi, ratio_err ) ;

         char bin_label[100] ;
         sprintf( bin_label, "S bin %d", bi ) ;
         h_metsig_ttbar_sigsb_ratio_allcuts_fb -> GetXaxis() -> SetBinLabel( bi, bin_label ) ;

         printf(" h_metsig_ttbar_sigsb_ratio_allcuts_fb  SIG/SB ratio, S bin %d : %.3f +/- %.3f\n", bi, ratio_val, ratio_err ) ;

      } // bi.



    //====== End ttbar, METsig ------------------------------------------------------------------------














    //====== QCD, Nbtag ------------------------------------------------------------------------

      for ( int hi=0; hi<nhist_nb; hi++ ) {

         printf("\n\n ++++++++ %s \n\n", nb_hist_name[hi] ) ;

         sprintf( arg1, "nbtag_cat>>h_nb_sigsb_%s", nb_hist_name[hi] ) ;
         sprintf( allcuts, "(%s)*weight3*%.0f", nb_hist_cuts[hi], dataIntLumiIPB ) ;
         printf("\n %s : %s\n", arg1, allcuts ) ; fflush(stdout) ;
         qcd_chain -> Draw( arg1, allcuts ) ;
         can->Update() ; can->Draw() ;
         hist_nb_sigsb[hi] -> Print("all") ;


         printf("\n\n ++++++++ %s, SIG \n\n", nb_hist_name[hi] ) ;

         sprintf( arg1, "nbtag_cat>>h_nb_sig_%s", nb_hist_name[hi] ) ;
         sprintf( allcuts, "(%s&&(%s))*weight3*%.0f", nb_hist_cuts[hi], masssigcuts, dataIntLumiIPB ) ;
         printf("\n %s : %s\n", arg1, allcuts ) ; fflush(stdout) ;
         qcd_chain -> Draw( arg1, allcuts ) ;
         can->Update() ; can->Draw() ;
         hist_nb_sig[hi] -> Print("all") ;


         printf("\n\n ++++++++ %s, SB \n\n", nb_hist_name[hi] ) ;

         sprintf( arg1, "nbtag_cat>>h_nb_sb_%s", nb_hist_name[hi] ) ;
         sprintf( allcuts, "(%s&&(%s))*weight3*%.0f", nb_hist_cuts[hi], masssbcuts, dataIntLumiIPB ) ;
         printf("\n %s : %s\n", arg1, allcuts ) ; fflush(stdout) ;
         qcd_chain -> Draw( arg1, allcuts ) ;
         can->Update() ; can->Draw() ;
         hist_nb_sb[hi] -> Print("all") ;


         printf("\n\n ++++++++ %s, SIG/SB ratio \n\n", nb_hist_name[hi] ) ;

         for ( int bi=1; bi<=5; bi++ ) {

            float sig_val = hist_nb_sig[hi] -> GetBinContent(bi) ;
            float sig_err = hist_nb_sig[hi] -> GetBinError(bi) ;
            float sb_val  = hist_nb_sb[hi]  -> GetBinContent(bi) ;
            float sb_err  = hist_nb_sb[hi]  -> GetBinError(bi) ;

            float ratio_val(0.), ratio_err(0.) ;
            if ( sb_val > 0 ) {
               ratio_val = sig_val / sb_val ;
               if ( sig_val > 0 && sig_err > 0 ) {
                  ratio_err = ratio_val * sqrt( pow( sig_err/sig_val, 2 ) + pow( sb_err/sb_val, 2 ) ) ;
               }
            }

            hist_nb_sigsb_ratio[hi] -> SetBinContent( bi, ratio_val ) ;
            hist_nb_sigsb_ratio[hi] -> SetBinError( bi, ratio_err ) ;

            printf(" %s  SIG/SB ratio, S bin %d : %.3f +/- %.3f\n", nb_hist_name[hi], bi, ratio_val, ratio_err ) ;

         } // bi.

      } // hi.

    //====== End QCD, Nbtag ------------------------------------------------------------------------

    //====== ttbar, Nbtag ------------------------------------------------------------------------


      printf("\n\n ++++++++ \n\n" ) ;

      sprintf( arg1, "nbtag_cat>>h_nb_ttbar_sigsb_allcuts" ) ;
      sprintf( allcuts, "(%s&&METsig>30)*weight3*%.0f", allcommoncuts, dataIntLumiIPB ) ;
      printf("\n %s : %s\n", arg1, allcuts ) ; fflush(stdout) ;
      tt_chain -> Draw( arg1, allcuts ) ;
      can->Update() ; can->Draw() ;
      h_nb_ttbar_sigsb_allcuts -> Print("all") ;


      printf("\n\n ++++++++ SIG \n\n" ) ;

      sprintf( arg1, "nbtag_cat>>h_nb_ttbar_sig_allcuts" ) ;
      sprintf( allcuts, "(%s&&%s&&METsig>30)*weight3*%.0f", allcommoncuts, masssigcuts, dataIntLumiIPB ) ;
      printf("\n %s : %s\n", arg1, allcuts ) ; fflush(stdout) ;
      tt_chain -> Draw( arg1, allcuts ) ;
      can->Update() ; can->Draw() ;
      h_nb_ttbar_sig_allcuts -> Print("all") ;


      printf("\n\n ++++++++ SB \n\n" ) ;

      sprintf( arg1, "nbtag_cat>>h_nb_ttbar_sb_allcuts" ) ;
      sprintf( allcuts, "(%s&&%s&&METsig>30)*weight3*%.0f", allcommoncuts, masssbcuts, dataIntLumiIPB ) ;
      printf("\n %s : %s\n", arg1, allcuts ) ; fflush(stdout) ;
      tt_chain -> Draw( arg1, allcuts ) ;
      can->Update() ; can->Draw() ;
      h_nb_ttbar_sb_allcuts -> Print("all") ;




      printf("\n\n ++++++++ SIG/SB ratio \n\n" ) ;

      for ( int bi=1; bi<=5; bi++ ) {

         float sig_val = h_nb_ttbar_sig_allcuts -> GetBinContent(bi) ;
         float sig_err = h_nb_ttbar_sig_allcuts -> GetBinError(bi) ;
         float sb_val  = h_nb_ttbar_sb_allcuts -> GetBinContent(bi) ;
         float sb_err  = h_nb_ttbar_sb_allcuts -> GetBinError(bi) ;

         float ratio_val(0.), ratio_err(0.) ;
         if ( sb_val > 0 ) {
            ratio_val = sig_val / sb_val ;
            if ( sig_val > 0 && sig_err > 0 ) {
               ratio_err = ratio_val * sqrt( pow( sig_err/sig_val, 2 ) + pow( sb_err/sb_val, 2 ) ) ;
            }
         }

         h_nb_ttbar_sigsb_ratio_allcuts -> SetBinContent( bi, ratio_val ) ;
         h_nb_ttbar_sigsb_ratio_allcuts -> SetBinError( bi, ratio_err ) ;

         printf(" h_nb_ttbar_sigsb_ratio_allcuts  SIG/SB ratio, S bin %d : %.3f +/- %.3f\n", bi, ratio_val, ratio_err ) ;

      } // bi.


    //====== End ttbar, Nbtag ------------------------------------------------------------------------









      for ( int hi=0; hi<nhist_hmasscat; hi++ ) {

         printf("\n\n ++++++++ %s \n\n", hmasscat_hist_name[hi] ) ;

         sprintf( arg1, "0>>h_hmasscat_%s", hmasscat_hist_name[hi] ) ;
         sprintf( allcuts, "(%s&&%s)*weight3*%.0f", hmasscat_hist_cuts[hi], masssbcuts, dataIntLumiIPB ) ;
         printf("\n %s : %s\n", arg1, allcuts ) ; fflush(stdout) ;
         qcd_chain -> Draw( arg1, allcuts ) ;
         sprintf( arg1, "1>>+h_hmasscat_%s", hmasscat_hist_name[hi] ) ;
         sprintf( allcuts, "(%s&&%s)*weight3*%.0f", hmasscat_hist_cuts[hi], masssigcuts, dataIntLumiIPB ) ;
         printf("\n %s : %s\n", arg1, allcuts ) ; fflush(stdout) ;
         qcd_chain -> Draw( arg1, allcuts ) ;
         can->Update() ; can->Draw() ;
         hist_hmasscat[hi] -> Print("all") ;

      } // hi.



      for ( int hi=0; hi<nhist_avem; hi++ ) {

         printf("\n\n ++++++++ %s \n\n", avem_hist_name[hi] ) ;

         sprintf( arg1, "avem>>h_avem_%s", avem_hist_name[hi] ) ;
         sprintf( allcuts, "(%s)*weight3*%.0f", avem_hist_cuts[hi], dataIntLumiIPB ) ;
         printf("\n %s : %s\n", arg1, allcuts ) ; fflush(stdout) ;
         qcd_chain -> Draw( arg1, allcuts ) ;
         addoverflow( hist_avem[hi] ) ;
         hist_avem[hi] -> Draw() ;
         can->Update() ; can->Draw() ;

      } // hi.

      printf("\n\n ++++++++ h_avem_ttbar_allcuts \n\n" ) ;

      sprintf( arg1, "avem>>h_avem_ttbar_allcuts" ) ;
      sprintf( allcuts, "(%s&&nbtag_cat>=2&&METsig>30)*weight3*%.0f", allcommoncuts, dataIntLumiIPB ) ;
      printf("\n %s : %s\n", arg1, allcuts ) ; fflush(stdout) ;
      tt_chain -> Draw( arg1, allcuts ) ;
      addoverflow( h_avem_ttbar_allcuts ) ;
      h_avem_ttbar_allcuts -> Draw() ;
      can->Update() ; can->Draw() ;


      for ( int hi=0; hi<nhist_deltam; hi++ ) {

         printf("\n\n ++++++++ %s \n\n", deltam_hist_name[hi] ) ;

         sprintf( arg1, "deltam>>h_deltam_%s", deltam_hist_name[hi] ) ;
         sprintf( allcuts, "(%s)*weight3*%.0f", deltam_hist_cuts[hi], dataIntLumiIPB ) ;
         printf("\n %s : %s\n", arg1, allcuts ) ; fflush(stdout) ;
         qcd_chain -> Draw( arg1, allcuts ) ;
         addoverflow( hist_deltam[hi] ) ;
         hist_deltam[hi] -> Draw() ;
         can->Update() ; can->Draw() ;

         sprintf( arg1, "deltam:avem>>h_deltam_vs_avem_%s", deltam_hist_name[hi] ) ;
         sprintf( allcuts, "(%s)*weight3*%.0f", deltam_hist_cuts[hi], dataIntLumiIPB ) ;
         printf("\n %s : %s\n", arg1, allcuts ) ; fflush(stdout) ;
         qcd_chain -> Draw( arg1, allcuts ) ;
         hist_deltam_vs_avem[hi] -> Draw("box") ;
         can->Update() ; can->Draw() ;

      } // hi.

      printf("\n\n ++++++++ h_deltam_ttbar_allcuts \n\n" ) ;

      sprintf( arg1, "deltam>>h_deltam_ttbar_allcuts" ) ;
      sprintf( allcuts, "(%s&&nbtag_cat>=2&&METsig>30)*weight3*%.0f", allcommoncuts, dataIntLumiIPB ) ;
      printf("\n %s : %s\n", arg1, allcuts ) ; fflush(stdout) ;
      tt_chain -> Draw( arg1, allcuts ) ;
      addoverflow( h_deltam_ttbar_allcuts ) ;
      h_deltam_ttbar_allcuts -> Draw() ;
      can->Update() ; can->Draw() ;

      sprintf( arg1, "deltam:avem>>h_deltam_vs_avem_ttbar_allcuts" ) ;
      sprintf( allcuts, "(%s&&nbtag_cat>=2&&METsig>30)*weight3*%.0f", allcommoncuts, dataIntLumiIPB ) ;
      printf("\n %s : %s\n", arg1, allcuts ) ; fflush(stdout) ;
      tt_chain -> Draw( arg1, allcuts ) ;
      h_deltam_vs_avem_ttbar_allcuts -> Draw("box") ;
      can->Update() ; can->Draw() ;











     //--- save histograms.

      printf("\n\n Saving histograms to outputfiles/qcd_study1.root\n\n") ;

      saveHist( "outputfiles/qcd_study1.root", "h*" ) ;


   } // fill_qcdstudy1







