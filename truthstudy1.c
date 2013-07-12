#define truthstudy1_cxx
#include "truthstudy1.h"
#include "TStyle.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TH1F.h"
#include "TPaveStats.h"
#include "TString.h"
#include "TLegend.h"
#include "THStack.h"

#include "histio.c"

void labelCodeBins( TH1* hp ) ;

TH1F* shiftHist( TH1* hin, float xshift ) ;

void fillratio( TH1* hn, TH1* hd, TH1* hr ) ;

void fillratioReweight( TH1* hn4j, TH1* hd4j, TH1* hn5j, TH1* hd5j, float w4j, float w5j, TH1* hr ) ;

void filldistReweight( TH1* h4j, TH1* h5j, float w4j, float w5j, TH1* hr ) ;

void fillEffHist( TH1* hpass, TH1* hall, TH1* heff ) ;

void fillWeightHist( TH1* h2b, TH1* h4b, TH1* hw ) ;

void addoverflow( TH1* hp, bool dounder = false ) ;

int getptbin( float ptval ) ;

int getsumptbin( float sumptval ) ;

void write_btageff_file( TH1* heff, const char* outfile ) ;
void read_btageff_file( const char* infile, double* eff_array ) ;

void write_weight_sumpt( TH1* hweight, const char* outfile ) ;
void read_weight_sumpt( const char* infile ) ;

   int ncbinspt(9) ;
   double pt_bins[10] = { 0., 20., 30., 40., 60., 80., 100., 150., 200., 500. } ;

   double eff_nlcsv_med[9] ;
   double eff_lcsv_loose[9] ;

   int nbinssumpt(5) ;
   double sumpt_bins[6] = { 0., 200., 300., 400., 500., 5000. } ;
   double weight_sumpt[5] ;


void truthstudy1::Loop()
{

   {
      char eff_filename[10000] ;

      sprintf( eff_filename, "outputfiles/btag-eff-vs-pt--nextlowest-csv-passmed--%s.txt", samplename ) ;
      read_btageff_file( eff_filename, eff_nlcsv_med ) ;

      sprintf( eff_filename, "outputfiles/btag-eff-vs-pt--lowest-csv-passloose--%s.txt", samplename ) ;
      read_btageff_file( eff_filename, eff_lcsv_loose ) ;
   }
   {
      char weight_filename[10000] ;
      sprintf( weight_filename, "outputfiles/sumpt-weight--%s.txt", samplename ) ;
      read_weight_sumpt( weight_filename ) ;
   }


   gStyle -> SetPadBottomMargin(0.25) ;
   gStyle -> SetOptStat("eMR") ;
   gStyle -> SetPadGridY(1) ;

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntries();

   Long64_t nbytes = 0, nb = 0;

   int ncats(16) ;
   TH1F* h_evtcode_nocuts = new TH1F("h_evtcode_nocuts", "Event code, no cuts", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_baselinecuts = new TH1F("h_evtcode_baselinecuts", "Event code, baseline cuts", ncats+1, -0.5, ncats+0.5 ) ;

   TH1F* h_evtcode_2b = new TH1F("h_evtcode_2b", "Event code, 2b", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_4b = new TH1F("h_evtcode_4b", "Event code, 4b", ncats+1, -0.5, ncats+0.5 ) ;

   TH1F* h_evtcode_2b_4j = new TH1F("h_evtcode_2b_4j", "Event code, 2b, 4 jets", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_4b_4j = new TH1F("h_evtcode_4b_4j", "Event code, 4b, 4 jets", ncats+1, -0.5, ncats+0.5 ) ;

   TH1F* h_evtcode_2b_4j_ms40 = new TH1F("h_evtcode_2b_4j_ms40", "Event code, 2b, 4 jets, METsig>40", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_4b_4j_ms40 = new TH1F("h_evtcode_4b_4j_ms40", "Event code, 4b, 4 jets, METsig>40", ncats+1, -0.5, ncats+0.5 ) ;

   TH1F* h_evtcode_2b_4j_ms85 = new TH1F("h_evtcode_2b_4j_ms85", "Event code, 2b, 4 jets, METsig>85", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_4b_4j_ms85 = new TH1F("h_evtcode_4b_4j_ms85", "Event code, 4b, 4 jets, METsig>85", ncats+1, -0.5, ncats+0.5 ) ;

   TH1F* h_evtcode_2b_5j = new TH1F("h_evtcode_2b_5j", "Event code, 2b, 5 jets", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_4b_5j = new TH1F("h_evtcode_4b_5j", "Event code, 4b, 5 jets", ncats+1, -0.5, ncats+0.5 ) ;

   TH1F* h_evtcode_2b_5j_ms40 = new TH1F("h_evtcode_2b_5j_ms40", "Event code, 2b, 5 jets, METsig>40", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_4b_5j_ms40 = new TH1F("h_evtcode_4b_5j_ms40", "Event code, 4b, 5 jets, METsig>40", ncats+1, -0.5, ncats+0.5 ) ;

   TH1F* h_evtcode_2b_5j_ms85 = new TH1F("h_evtcode_2b_5j_ms85", "Event code, 2b, 5 jets, METsig>85", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_4b_5j_ms85 = new TH1F("h_evtcode_4b_5j_ms85", "Event code, 4b, 5 jets, METsig>85", ncats+1, -0.5, ncats+0.5 ) ;

   TH1F* h_evtcode_2b_NjetReweight = new TH1F("h_evtcode_2b_NjetReweight", "Event code, 2b, Njet reweighted", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_2b_ms40_NjetReweight = new TH1F("h_evtcode_2b_ms40_NjetReweight", "Event code, 2b, METsig>40, Njet reweighted", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_2b_ms85_NjetReweight = new TH1F("h_evtcode_2b_ms85_NjetReweight", "Event code, 2b, METsig>85, Njet reweighted", ncats+1, -0.5, ncats+0.5 ) ;

   TH1F* h_evtcode_2b_ms40 = new TH1F("h_evtcode_2b_ms40", "Event code, 2b, METsig>40", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_4b_ms40 = new TH1F("h_evtcode_4b_ms40", "Event code, 4b, METsig>40", ncats+1, -0.5, ncats+0.5 ) ;

   TH1F* h_evtcode_2b_ms85 = new TH1F("h_evtcode_2b_ms85", "Event code, 2b, METsig>85", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_4b_ms85 = new TH1F("h_evtcode_4b_ms85", "Event code, 4b, METsig>85", ncats+1, -0.5, ncats+0.5 ) ;


   TH1F* h_evtcode_msig_2b = new TH1F("h_evtcode_msig_2b", "Event code, mass sig box, 2b", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_msig_4b = new TH1F("h_evtcode_msig_4b", "Event code, mass sig box, 4b", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_msb_2b = new TH1F("h_evtcode_msb_2b", "Event code, mass SB, 2b", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_msb_4b = new TH1F("h_evtcode_msb_4b", "Event code, mass SB, 4b", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_rmsigsb_2b = new TH1F("h_evtcode_rmsigsb_2b", "Event code, mass SIG/SB ratio, 2b", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_rmsigsb_4b = new TH1F("h_evtcode_rmsigsb_4b", "Event code, mass SIG/SB ratio, 4b", ncats+1, -0.5, ncats+0.5 ) ;


   TH1F* h_evtcode_msig_2b_ms40 = new TH1F("h_evtcode_msig_2b_ms40", "Event code, mass sig box, 2b, METsig>40", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_msig_4b_ms40 = new TH1F("h_evtcode_msig_4b_ms40", "Event code, mass sig box, 4b, METsig>40", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_msb_2b_ms40 = new TH1F("h_evtcode_msb_2b_ms40", "Event code, mass SB, 2b, METsig>40", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_msb_4b_ms40 = new TH1F("h_evtcode_msb_4b_ms40", "Event code, mass SB, 4b, METsig>40", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_rmsigsb_2b_ms40 = new TH1F("h_evtcode_rmsigsb_2b_ms40", "Event code, mass SIG/SB ratio, 2b, METsig>40", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_rmsigsb_4b_ms40 = new TH1F("h_evtcode_rmsigsb_4b_ms40", "Event code, mass SIG/SB ratio, 4b, METsig>40", ncats+1, -0.5, ncats+0.5 ) ;


   TH1F* h_evtcode_msig_2b_ms85 = new TH1F("h_evtcode_msig_2b_ms85", "Event code, mass sig box, 2b, METsig>85", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_msig_4b_ms85 = new TH1F("h_evtcode_msig_4b_ms85", "Event code, mass sig box, 4b, METsig>85", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_msb_2b_ms85 = new TH1F("h_evtcode_msb_2b_ms85", "Event code, mass SB, 2b, METsig>85", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_msb_4b_ms85 = new TH1F("h_evtcode_msb_4b_ms85", "Event code, mass SB, 4b, METsig>85", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_rmsigsb_2b_ms85 = new TH1F("h_evtcode_rmsigsb_2b_ms85", "Event code, mass SIG/SB ratio, 2b, METsig>85", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_rmsigsb_4b_ms85 = new TH1F("h_evtcode_rmsigsb_4b_ms85", "Event code, mass SIG/SB ratio, 4b, METsig>85", ncats+1, -0.5, ncats+0.5 ) ;



   TH1F* h_evtcode_msig_2b_4j = new TH1F("h_evtcode_msig_2b_4j", "Event code, mass sig box, 2b, 4 jets", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_msig_4b_4j = new TH1F("h_evtcode_msig_4b_4j", "Event code, mass sig box, 4b, 4 jets", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_msb_2b_4j = new TH1F("h_evtcode_msb_2b_4j", "Event code, mass SB, 2b, 4 jets", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_msb_4b_4j = new TH1F("h_evtcode_msb_4b_4j", "Event code, mass SB, 4b, 4 jets", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_rmsigsb_2b_4j = new TH1F("h_evtcode_rmsigsb_2b_4j", "Event code, mass SIG/SB ratio, 2b, 4 jets", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_rmsigsb_4b_4j = new TH1F("h_evtcode_rmsigsb_4b_4j", "Event code, mass SIG/SB ratio, 4b, 4 jets", ncats+1, -0.5, ncats+0.5 ) ;

   TH1F* h_evtcode_msig_2b_4j_ms40 = new TH1F("h_evtcode_msig_2b_4j_ms40", "Event code, mass sig box, 2b, 4 jets, METsig>40", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_msig_4b_4j_ms40 = new TH1F("h_evtcode_msig_4b_4j_ms40", "Event code, mass sig box, 4b, 4 jets, METsig>40", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_msb_2b_4j_ms40 = new TH1F("h_evtcode_msb_2b_4j_ms40", "Event code, mass SB, 2b, 4 jets, METsig>40", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_msb_4b_4j_ms40 = new TH1F("h_evtcode_msb_4b_4j_ms40", "Event code, mass SB, 4b, 4 jets, METsig>40", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_rmsigsb_2b_4j_ms40 = new TH1F("h_evtcode_rmsigsb_2b_4j_ms40", "Event code, mass SIG/SB ratio, 2b, 4 jets, METsig>40", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_rmsigsb_4b_4j_ms40 = new TH1F("h_evtcode_rmsigsb_4b_4j_ms40", "Event code, mass SIG/SB ratio, 4b, 4 jets, METsig>40", ncats+1, -0.5, ncats+0.5 ) ;

   TH1F* h_evtcode_msig_2b_4j_ms85 = new TH1F("h_evtcode_msig_2b_4j_ms85", "Event code, mass sig box, 2b, 4 jets, METsig>85", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_msig_4b_4j_ms85 = new TH1F("h_evtcode_msig_4b_4j_ms85", "Event code, mass sig box, 4b, 4 jets, METsig>85", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_msb_2b_4j_ms85 = new TH1F("h_evtcode_msb_2b_4j_ms85", "Event code, mass SB, 2b, 4 jets, METsig>85", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_msb_4b_4j_ms85 = new TH1F("h_evtcode_msb_4b_4j_ms85", "Event code, mass SB, 4b, 4 jets, METsig>85", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_rmsigsb_2b_4j_ms85 = new TH1F("h_evtcode_rmsigsb_2b_4j_ms85", "Event code, mass SIG/SB ratio, 2b, 4 jets, METsig>85", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_rmsigsb_4b_4j_ms85 = new TH1F("h_evtcode_rmsigsb_4b_4j_ms85", "Event code, mass SIG/SB ratio, 4b, 4 jets, METsig>85", ncats+1, -0.5, ncats+0.5 ) ;




   TH1F* h_evtcode_msig_2b_5j = new TH1F("h_evtcode_msig_2b_5j", "Event code, mass sig box, 2b, 5 jets", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_msig_4b_5j = new TH1F("h_evtcode_msig_4b_5j", "Event code, mass sig box, 4b, 5 jets", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_msb_2b_5j = new TH1F("h_evtcode_msb_2b_5j", "Event code, mass SB, 2b, 5 jets", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_msb_4b_5j = new TH1F("h_evtcode_msb_4b_5j", "Event code, mass SB, 4b, 5 jets", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_rmsigsb_2b_5j = new TH1F("h_evtcode_rmsigsb_2b_5j", "Event code, mass SIG/SB ratio, 2b, 5 jets", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_rmsigsb_4b_5j = new TH1F("h_evtcode_rmsigsb_4b_5j", "Event code, mass SIG/SB ratio, 4b, 5 jets", ncats+1, -0.5, ncats+0.5 ) ;

   TH1F* h_evtcode_msig_2b_5j_ms40 = new TH1F("h_evtcode_msig_2b_5j_ms40", "Event code, mass sig box, 2b, 5 jets, METsig>40", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_msig_4b_5j_ms40 = new TH1F("h_evtcode_msig_4b_5j_ms40", "Event code, mass sig box, 4b, 5 jets, METsig>40", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_msb_2b_5j_ms40 = new TH1F("h_evtcode_msb_2b_5j_ms40", "Event code, mass SB, 2b, 5 jets, METsig>40", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_msb_4b_5j_ms40 = new TH1F("h_evtcode_msb_4b_5j_ms40", "Event code, mass SB, 4b, 5 jets, METsig>40", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_rmsigsb_2b_5j_ms40 = new TH1F("h_evtcode_rmsigsb_2b_5j_ms40", "Event code, mass SIG/SB ratio, 2b, 5 jets, METsig>40", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_rmsigsb_4b_5j_ms40 = new TH1F("h_evtcode_rmsigsb_4b_5j_ms40", "Event code, mass SIG/SB ratio, 4b, 5 jets, METsig>40", ncats+1, -0.5, ncats+0.5 ) ;

   TH1F* h_evtcode_msig_2b_5j_ms85 = new TH1F("h_evtcode_msig_2b_5j_ms85", "Event code, mass sig box, 2b, 5 jets, METsig>85", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_msig_4b_5j_ms85 = new TH1F("h_evtcode_msig_4b_5j_ms85", "Event code, mass sig box, 4b, 5 jets, METsig>85", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_msb_2b_5j_ms85 = new TH1F("h_evtcode_msb_2b_5j_ms85", "Event code, mass SB, 2b, 5 jets, METsig>85", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_msb_4b_5j_ms85 = new TH1F("h_evtcode_msb_4b_5j_ms85", "Event code, mass SB, 4b, 5 jets, METsig>85", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_rmsigsb_2b_5j_ms85 = new TH1F("h_evtcode_rmsigsb_2b_5j_ms85", "Event code, mass SIG/SB ratio, 2b, 5 jets, METsig>85", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_rmsigsb_4b_5j_ms85 = new TH1F("h_evtcode_rmsigsb_4b_5j_ms85", "Event code, mass SIG/SB ratio, 4b, 5 jets, METsig>85", ncats+1, -0.5, ncats+0.5 ) ;



   TH1F* h_evtcode_rmsigsb_2b_NjetReweight = new TH1F("h_evtcode_rmsigsb_2b_NjetReweight", "Event code, mass SIG/SB ratio, 2b, reweighted Njet dist", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_rmsigsb_2b_ms40_NjetReweight = new TH1F("h_evtcode_rmsigsb_2b_ms40_NjetReweight", "Event code, mass SIG/SB ratio, 2b, METsig>40, reweighted Njet dist", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_rmsigsb_2b_ms85_NjetReweight = new TH1F("h_evtcode_rmsigsb_2b_ms85_NjetReweight", "Event code, mass SIG/SB ratio, 2b, METsig>85, reweighted Njet dist", ncats+1, -0.5, ncats+0.5 ) ;


   TH1F* h_evtcode_2b_lcsvpt40 = new TH1F("h_evtcode_2b_lcsvpt40", "Event code, lowest CSV pt>40, 2b", ncats+1, -0.5, ncats+0.5 ) ;
   TH1F* h_evtcode_4b_lcsvpt40 = new TH1F("h_evtcode_4b_lcsvpt40", "Event code, lowest CSV pt>40, 4b", ncats+1, -0.5, ncats+0.5 ) ;

   labelCodeBins( h_evtcode_nocuts ) ;
   labelCodeBins( h_evtcode_baselinecuts ) ;
   labelCodeBins( h_evtcode_2b ) ;
   labelCodeBins( h_evtcode_4b ) ;

   labelCodeBins( h_evtcode_2b_4j ) ;
   labelCodeBins( h_evtcode_4b_4j ) ;
   labelCodeBins( h_evtcode_2b_5j ) ;
   labelCodeBins( h_evtcode_4b_5j ) ;

   labelCodeBins( h_evtcode_2b_4j_ms40 ) ;
   labelCodeBins( h_evtcode_4b_4j_ms40 ) ;
   labelCodeBins( h_evtcode_2b_5j_ms40 ) ;
   labelCodeBins( h_evtcode_4b_5j_ms40 ) ;

   labelCodeBins( h_evtcode_2b_4j_ms85 ) ;
   labelCodeBins( h_evtcode_4b_4j_ms85 ) ;
   labelCodeBins( h_evtcode_2b_5j_ms85 ) ;
   labelCodeBins( h_evtcode_4b_5j_ms85 ) ;

   labelCodeBins( h_evtcode_2b_NjetReweight ) ;
   labelCodeBins( h_evtcode_2b_ms40_NjetReweight ) ;
   labelCodeBins( h_evtcode_2b_ms85_NjetReweight ) ;

   labelCodeBins( h_evtcode_msig_2b ) ;
   labelCodeBins( h_evtcode_msig_4b ) ;
   labelCodeBins( h_evtcode_msb_2b ) ;
   labelCodeBins( h_evtcode_msb_4b ) ;
   labelCodeBins( h_evtcode_rmsigsb_2b ) ;
   labelCodeBins( h_evtcode_rmsigsb_4b ) ;

   labelCodeBins( h_evtcode_msig_2b_ms40 ) ;
   labelCodeBins( h_evtcode_msig_4b_ms40 ) ;
   labelCodeBins( h_evtcode_msb_2b_ms40 ) ;
   labelCodeBins( h_evtcode_msb_4b_ms40 ) ;
   labelCodeBins( h_evtcode_rmsigsb_2b_ms40 ) ;
   labelCodeBins( h_evtcode_rmsigsb_4b_ms40 ) ;

   labelCodeBins( h_evtcode_msig_2b_4j ) ;
   labelCodeBins( h_evtcode_msig_4b_4j ) ;
   labelCodeBins( h_evtcode_msb_2b_4j ) ;
   labelCodeBins( h_evtcode_msb_4b_4j ) ;
   labelCodeBins( h_evtcode_rmsigsb_2b_4j ) ;
   labelCodeBins( h_evtcode_rmsigsb_4b_4j ) ;

   labelCodeBins( h_evtcode_msig_2b_4j_ms40 ) ;
   labelCodeBins( h_evtcode_msig_4b_4j_ms40 ) ;
   labelCodeBins( h_evtcode_msb_2b_4j_ms40 ) ;
   labelCodeBins( h_evtcode_msb_4b_4j_ms40 ) ;
   labelCodeBins( h_evtcode_rmsigsb_2b_4j_ms40 ) ;
   labelCodeBins( h_evtcode_rmsigsb_4b_4j_ms40 ) ;

   labelCodeBins( h_evtcode_msig_2b_4j_ms85 ) ;
   labelCodeBins( h_evtcode_msig_4b_4j_ms85 ) ;
   labelCodeBins( h_evtcode_msb_2b_4j_ms85 ) ;
   labelCodeBins( h_evtcode_msb_4b_4j_ms85 ) ;
   labelCodeBins( h_evtcode_rmsigsb_2b_4j_ms85 ) ;
   labelCodeBins( h_evtcode_rmsigsb_4b_4j_ms85 ) ;

   labelCodeBins( h_evtcode_msig_2b_5j ) ;
   labelCodeBins( h_evtcode_msig_4b_5j ) ;
   labelCodeBins( h_evtcode_msb_2b_5j ) ;
   labelCodeBins( h_evtcode_msb_4b_5j ) ;
   labelCodeBins( h_evtcode_rmsigsb_2b_5j ) ;
   labelCodeBins( h_evtcode_rmsigsb_4b_5j ) ;

   labelCodeBins( h_evtcode_msig_2b_5j_ms40 ) ;
   labelCodeBins( h_evtcode_msig_4b_5j_ms40 ) ;
   labelCodeBins( h_evtcode_msb_2b_5j_ms40 ) ;
   labelCodeBins( h_evtcode_msb_4b_5j_ms40 ) ;
   labelCodeBins( h_evtcode_rmsigsb_2b_5j_ms40 ) ;
   labelCodeBins( h_evtcode_rmsigsb_4b_5j_ms40 ) ;

   labelCodeBins( h_evtcode_msig_2b_5j_ms85 ) ;
   labelCodeBins( h_evtcode_msig_4b_5j_ms85 ) ;
   labelCodeBins( h_evtcode_msb_2b_5j_ms85 ) ;
   labelCodeBins( h_evtcode_msb_4b_5j_ms85 ) ;
   labelCodeBins( h_evtcode_rmsigsb_2b_5j_ms85 ) ;
   labelCodeBins( h_evtcode_rmsigsb_4b_5j_ms85 ) ;

   labelCodeBins( h_evtcode_rmsigsb_2b_NjetReweight ) ;
   labelCodeBins( h_evtcode_rmsigsb_2b_ms40_NjetReweight ) ;
   labelCodeBins( h_evtcode_rmsigsb_2b_ms85_NjetReweight ) ;

   labelCodeBins( h_evtcode_msig_2b_ms85 ) ;
   labelCodeBins( h_evtcode_msig_4b_ms85 ) ;
   labelCodeBins( h_evtcode_msb_2b_ms85 ) ;
   labelCodeBins( h_evtcode_msb_4b_ms85 ) ;
   labelCodeBins( h_evtcode_rmsigsb_2b_ms85 ) ;
   labelCodeBins( h_evtcode_rmsigsb_4b_ms85 ) ;

   labelCodeBins( h_evtcode_2b_ms40 ) ;
   labelCodeBins( h_evtcode_4b_ms40 ) ;
   labelCodeBins( h_evtcode_2b_ms85 ) ;
   labelCodeBins( h_evtcode_4b_ms85 ) ;
   labelCodeBins( h_evtcode_2b_lcsvpt40 ) ;
   labelCodeBins( h_evtcode_4b_lcsvpt40 ) ;


   TH1F* h_njets_2b = new TH1F("h_njets_2b", "Njets, 2b", 7, 0.5, 7.5 ) ;
   TH1F* h_njets_3b = new TH1F("h_njets_3b", "Njets, 3b", 7, 0.5, 7.5 ) ;
   TH1F* h_njets_4b = new TH1F("h_njets_4b", "Njets, 4b", 7, 0.5, 7.5 ) ;
   TH1F* h_njets_2b_NjetReweight = new TH1F("h_njets_2b_NjetReweight", "Njets, 2b, Njet reweighted", 7, 0.5, 7.5 ) ;

   TH1F* h_njets_2b_ms40 = new TH1F("h_njets_2b_ms40", "Njets, 2b, METsig>40", 7, 0.5, 7.5 ) ;
   TH1F* h_njets_3b_ms40 = new TH1F("h_njets_3b_ms40", "Njets, 3b, METsig>40", 7, 0.5, 7.5 ) ;
   TH1F* h_njets_4b_ms40 = new TH1F("h_njets_4b_ms40", "Njets, 4b, METsig>40", 7, 0.5, 7.5 ) ;

   TH1F* h_njets_2b_ms85 = new TH1F("h_njets_2b_ms85", "Njets, 2b, METsig>85", 7, 0.5, 7.5 ) ;
   TH1F* h_njets_3b_ms85 = new TH1F("h_njets_3b_ms85", "Njets, 3b, METsig>85", 7, 0.5, 7.5 ) ;
   TH1F* h_njets_4b_ms85 = new TH1F("h_njets_4b_ms85", "Njets, 4b, METsig>85", 7, 0.5, 7.5 ) ;

   TH1F* h_jj_flavor = new TH1F("h_jj_flavor", "Flavor of jets from W", 7, -0.5, 6.5 ) ;
   TH1F* h_jj_flavor_2b = new TH1F("h_jj_flavor_2b", "Flavor of jets from W, 2b", 7, -0.5, 6.5 ) ;
   TH1F* h_jj_flavor_4b = new TH1F("h_jj_flavor_4b", "Flavor of jets from W, 4b", 7, -0.5, 6.5 ) ;
   TH1F* h_jx_wjet_flavor = new TH1F("h_jx_wjet_flavor", "Flavor of jets from W", 7, -0.5, 6.5 ) ;
   TH1F* h_jx_wjet_flavor_2b = new TH1F("h_jx_wjet_flavor_2b", "Flavor of jets from W, 2b", 7, -0.5, 6.5 ) ;
   TH1F* h_jx_wjet_flavor_4b = new TH1F("h_jx_wjet_flavor_4b", "Flavor of jets from W, 4b", 7, -0.5, 6.5 ) ;

   TH1F* h_xjet_flavor = new TH1F("h_xjet_flavor", "Flavor of non-top-daughter jet", 31, -0.5, 30.5 ) ;
   TH1F* h_xjet_flavor_2b = new TH1F("h_xjet_flavor_2b", "Flavor of non-top-daughter jet, 2b", 31, -0.5, 30.5 ) ;
   TH1F* h_xjet_flavor_4b = new TH1F("h_xjet_flavor_4b", "Flavor of non-top-daughter jet, 4b", 31, -0.5, 30.5 ) ;
   TH1F* h_xjet_parent_flavor = new TH1F("h_xjet_parent_flavor", "Flavor of parent of non-top-daughter jet", 31, -0.5, 30.5 ) ;
   TH2F* h_xjet_flav_vs_parent = new TH2F("h_xjet_flav_vs_parent", "Non-top-daughter jet, flav vs parent", 31, -0.5, 30.5,  31, -0.5, 30.5 ) ;

   TH1F* h_xjet_pt = new TH1F("h_xjet_pt", "Non-top-daughter jet pt", 40, 0., 200. ) ;
   TH1F* h_xjet_pt_2b = new TH1F("h_xjet_pt_2b", "Non-top-daughter jet pt, 2b", 40, 0., 200. ) ;
   TH1F* h_xjet_pt_4b = new TH1F("h_xjet_pt_4b", "Non-top-daughter jet pt, 4b", 40, 0., 200. ) ;
   TH1F* h_jj_wjet_pt = new TH1F("h_jj_wjet_pt", "W-daughter jet pt, both W jets used", 40, 0., 200. ) ;
   TH1F* h_jx_wjet_pt = new TH1F("h_jx_wjet_pt", "W-daughter jet pt, one W jet used", 40, 0., 200. ) ;
   TH1F* h_jj_lfj_csv = new TH1F("h_jj_lfj_csv", "W-daughter jet CSV, both W jets used, lighter flavor one", 40., 0., 1. ) ;
   TH1F* h_jj_lfj_pt = new TH1F("h_jj_lfj_pt", "W-daughter jet pt, both W jets used, lighter flavor one", 40., 0., 200. ) ;
   TH1F* h_jj_charm_csv = new TH1F("h_jj_charm_csv", "W-daughter jet CSV, both W jets used, charm jet", 40., 0., 1. ) ;
   TH1F* h_jj_charm_pt = new TH1F("h_jj_charm_pt", "W-daughter jet pt, both W jets used, charm jet", 40., 0., 200. ) ;
   TH1F* h_xjet_pt_gluon = new TH1F("h_xjet_pt_gluon", "Non-top-daughter jet pt, gluon", 40, 0., 200. ) ;
   TH1F* h_xjet_pt_quark = new TH1F("h_xjet_pt_quark", "Non-top-daughter jet pt, quark", 40, 0., 200. ) ;
   TH1F* h_xjet_pt_nomatch = new TH1F("h_xjet_pt_nomatch", "Non-top-daughter jet pt, nomatch", 40, 0., 200. ) ;
   TH1F* h_xjet_csv_gluon = new TH1F("h_xjet_csv_gluon", "Non-top-daughter jet, CSV output, gluon", 40, 0., 1. ) ;
   TH1F* h_xjet_csv_quark = new TH1F("h_xjet_csv_quark", "Non-top-daughter jet, CSV output, quark", 40, 0., 1. ) ;
   TH1F* h_xjet_csv_nomatch = new TH1F("h_xjet_csv_nomatch", "Non-top-daughter jet, CSV output, nomatch", 40, 0., 1. ) ;
   TH1F* h_bjet_csv = new TH1F("h_bjet_csv", "b jet CSV", 40., 0., 1. ) ;
   TH1F* h_bjet_pt  = new TH1F("h_bjet_pt" , "b jet, pt", 40., 0., 200. ) ;

   TH1F* h_lowestcsv_csv = new TH1F("h_lowestcsv_csv", "Lowest CSV jet, CVS output", 40, 0., 1. ) ;
   TH1F* h_lowestcsv_source = new TH1F("h_lowestcsv_source", "Lowest CSV jet, source (1=X,2=W,3=t)", 3, 0.5, 3.5 ) ;
   TH1F* h_lowestcsv_pt = new TH1F("h_lowestcsv_pt", "Lowest CSV jet, pt", 40, 0., 200. ) ;
   TH1F* h_lowestcsv_csv_4b = new TH1F("h_lowestcsv_csv_4b", "Lowest CSV jet, CVS output, 4b", 40, 0., 1. ) ;
   TH1F* h_lowestcsv_source_4b = new TH1F("h_lowestcsv_source_4b", "Lowest CSV jet, source (1=X,2=W,3=t), 4b", 3, 0.5, 3.5 ) ;
   TH1F* h_lowestcsv_pt_4b = new TH1F("h_lowestcsv_pt_4b", "Lowest CSV jet, pt, 4b", 40, 0., 200. ) ;





   int nmhbins(30) ;
   float mhmin(0.) ;
   float mhmax(300.) ;

   int ndmhbins(40) ;
   float dmhmin(-120.) ;
   float dmhmax(120.) ;



   TH1F* h_mh_b1j_b2j__b1j = new TH1F("h_mh_b1j_b2j__b1j", "mh, (b1 j) (b2 j),  (b1 j)", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_b1j_b2j__b2j = new TH1F("h_mh_b1j_b2j__b2j", "mh, (b1 j) (b2 j),  (b2 j)", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_b1j_b2j__b1j_2b = new TH1F("h_mh_b1j_b2j__b1j_2b", "mh, (b1 j) (b2 j),  (b1 j), 2b", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_b1j_b2j__b2j_2b = new TH1F("h_mh_b1j_b2j__b2j_2b", "mh, (b1 j) (b2 j),  (b2 j), 2b", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_b1j_b2j__b1j_4b = new TH1F("h_mh_b1j_b2j__b1j_4b", "mh, (b1 j) (b2 j),  (b1 j), 4b", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_b1j_b2j__b2j_4b = new TH1F("h_mh_b1j_b2j__b2j_4b", "mh, (b1 j) (b2 j),  (b2 j), 4b", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_b1j_b2j__b1j_2b_ptrw = new TH1F("h_mh_b1j_b2j__b1j_2b_ptrw", "mh, (b1 j) (b2 j),  (b1 j), 2b, pt reweighted", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_b1j_b2j__b2j_2b_ptrw = new TH1F("h_mh_b1j_b2j__b2j_2b_ptrw", "mh, (b1 j) (b2 j),  (b2 j), 2b, pt reweighted", nmhbins, mhmin, mhmax ) ;
   TH1F* h_amh_b1j_b2j = new TH1F("h_amh_b1j_b2j", "ave mh, (b1 j) (b2 j)", nmhbins, mhmin, mhmax ) ;
   TH1F* h_amh_b1j_b2j__2b = new TH1F("h_amh_b1j_b2j__2b", "ave mh, (b1 j) (b2 j), 2b", nmhbins, mhmin, mhmax ) ;
   TH1F* h_amh_b1j_b2j__4b = new TH1F("h_amh_b1j_b2j__4b", "ave mh, (b1 j) (b2 j), 4b", nmhbins, mhmin, mhmax ) ;
   TH1F* h_dmh_b1j_b2j = new TH1F("h_dmh_b1j_b2j", "delta mh, (b1 j) (b2 j)", ndmhbins, dmhmin, dmhmax ) ;
   TH1F* h_dmh_b1j_b2j__2b = new TH1F("h_dmh_b1j_b2j__2b", "delta mh, (b1 j) (b2 j), 2b", ndmhbins, dmhmin, dmhmax ) ;
   TH1F* h_dmh_b1j_b2j__4b = new TH1F("h_dmh_b1j_b2j__4b", "delta mh, (b1 j) (b2 j), 4b", ndmhbins, dmhmin, dmhmax ) ;

   TH1F* h_amh_b1j_b2j_ms40 = new TH1F("h_amh_b1j_b2j_ms40", "ave mh, (b1 j) (b2 j), METsig>40", nmhbins, mhmin, mhmax ) ;
   TH1F* h_amh_b1j_b2j__2b_ms40 = new TH1F("h_amh_b1j_b2j__2b_ms40", "ave mh, (b1 j) (b2 j), 2b, METsig>40", nmhbins, mhmin, mhmax ) ;
   TH1F* h_amh_b1j_b2j__4b_ms40 = new TH1F("h_amh_b1j_b2j__4b_ms40", "ave mh, (b1 j) (b2 j), 4b, METsig>40", nmhbins, mhmin, mhmax ) ;
   TH1F* h_amh_b1j_b2j_ms85 = new TH1F("h_amh_b1j_b2j_ms85", "ave mh, (b1 j) (b2 j), METsig>40", nmhbins, mhmin, mhmax ) ;
   TH1F* h_amh_b1j_b2j__2b_ms85 = new TH1F("h_amh_b1j_b2j__2b_ms85", "ave mh, (b1 j) (b2 j), 2b, METsig>40", nmhbins, mhmin, mhmax ) ;
   TH1F* h_amh_b1j_b2j__4b_ms85 = new TH1F("h_amh_b1j_b2j__4b_ms85", "ave mh, (b1 j) (b2 j), 4b, METsig>40", nmhbins, mhmin, mhmax ) ;

   TH1F* h_dmh_b1j_b2j_ms40 = new TH1F("h_dmh_b1j_b2j_ms40", "delta mh, (b1 j) (b2 j), METsig>40", ndmhbins, dmhmin, dmhmax ) ;
   TH1F* h_dmh_b1j_b2j__2b_ms40 = new TH1F("h_dmh_b1j_b2j__2b_ms40", "delta mh, (b1 j) (b2 j), 2b, METsig>40", ndmhbins, dmhmin, dmhmax ) ;
   TH1F* h_dmh_b1j_b2j__4b_ms40 = new TH1F("h_dmh_b1j_b2j__4b_ms40", "delta mh, (b1 j) (b2 j), 4b, METsig>40", ndmhbins, dmhmin, dmhmax ) ;
   TH1F* h_dmh_b1j_b2j_ms85 = new TH1F("h_dmh_b1j_b2j_ms85", "delta mh, (b1 j) (b2 j), METsig>40", ndmhbins, dmhmin, dmhmax ) ;
   TH1F* h_dmh_b1j_b2j__2b_ms85 = new TH1F("h_dmh_b1j_b2j__2b_ms85", "delta mh, (b1 j) (b2 j), 2b, METsig>40", ndmhbins, dmhmin, dmhmax ) ;
   TH1F* h_dmh_b1j_b2j__4b_ms85 = new TH1F("h_dmh_b1j_b2j__4b_ms85", "delta mh, (b1 j) (b2 j), 4b, METsig>40", ndmhbins, dmhmin, dmhmax ) ;




   TH1F* h_mh_b1x_b2j__b1x = new TH1F("h_mh_b1x_b2j__b1x", "mh, (b1 x) (b2 j),  (b1 x)", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_b1x_b2j__b2j = new TH1F("h_mh_b1x_b2j__b2j", "mh, (b1 x) (b2 j),  (b2 j)", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_b1x_b2j__b1x_2b = new TH1F("h_mh_b1x_b2j__b1x_2b", "mh, (b1 x) (b2 j),  (b1 x), 2b", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_b1x_b2j__b2j_2b = new TH1F("h_mh_b1x_b2j__b2j_2b", "mh, (b1 x) (b2 j),  (b2 j), 2b", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_b1x_b2j__b1x_4b = new TH1F("h_mh_b1x_b2j__b1x_4b", "mh, (b1 x) (b2 j),  (b1 x), 4b", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_b1x_b2j__b2j_4b = new TH1F("h_mh_b1x_b2j__b2j_4b", "mh, (b1 x) (b2 j),  (b2 j), 4b", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_b1x_b2j__b1x_2b_ptrw = new TH1F("h_mh_b1x_b2j__b1x_2b_ptrw", "mh, (b1 x) (b2 j),  (b1 x), 2b, pt reweighted", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_b1x_b2j__b2j_2b_ptrw = new TH1F("h_mh_b1x_b2j__b2j_2b_ptrw", "mh, (b1 x) (b2 j),  (b2 j), 2b, pt reweighted", nmhbins, mhmin, mhmax ) ;
   TH1F* h_amh_b1x_b2j = new TH1F("h_amh_b1x_b2j", "ave mh, (b1 x) (b2 j)", nmhbins, mhmin, mhmax ) ;
   TH1F* h_amh_b1x_b2j__2b = new TH1F("h_amh_b1x_b2j__2b", "ave mh, (b1 x) (b2 j), 2b", nmhbins, mhmin, mhmax ) ;
   TH1F* h_amh_b1x_b2j__4b = new TH1F("h_amh_b1x_b2j__4b", "ave mh, (b1 x) (b2 j), 4b", nmhbins, mhmin, mhmax ) ;
   TH1F* h_dmh_b1x_b2j = new TH1F("h_dmh_b1x_b2j", "delta mh, (b1 x) (b2 j)", ndmhbins, dmhmin, dmhmax ) ;
   TH1F* h_dmh_b1x_b2j__2b = new TH1F("h_dmh_b1x_b2j__2b", "delta mh, (b1 x) (b2 j), 2b", ndmhbins, dmhmin, dmhmax ) ;
   TH1F* h_dmh_b1x_b2j__4b = new TH1F("h_dmh_b1x_b2j__4b", "delta mh, (b1 x) (b2 j), 4b", ndmhbins, dmhmin, dmhmax ) ;







   TH1F* h_mh_b1j_b2x__b1j = new TH1F("h_mh_b1j_b2x__b1j", "mh, (b1 j) (b2 x),  (b1 j)", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_b1j_b2x__b2x = new TH1F("h_mh_b1j_b2x__b2x", "mh, (b1 j) (b2 x),  (b2 x)", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_b1j_b2x__b1j_2b = new TH1F("h_mh_b1j_b2x__b1j_2b", "mh, (b1 j) (b2 x),  (b1 j), 2b", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_b1j_b2x__b2x_2b = new TH1F("h_mh_b1j_b2x__b2x_2b", "mh, (b1 j) (b2 x),  (b2 x), 2b", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_b1j_b2x__b1j_4b = new TH1F("h_mh_b1j_b2x__b1j_4b", "mh, (b1 j) (b2 x),  (b1 j), 4b", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_b1j_b2x__b2x_4b = new TH1F("h_mh_b1j_b2x__b2x_4b", "mh, (b1 j) (b2 x),  (b2 x), 4b", nmhbins, mhmin, mhmax ) ;
   TH1F* h_amh_b1j_b2x = new TH1F("h_amh_b1j_b2x", "ave mh, (b1 j) (b2 x)", nmhbins, mhmin, mhmax ) ;
   TH1F* h_amh_b1j_b2x__2b = new TH1F("h_amh_b1j_b2x__2b", "ave mh, (b1 j) (b2 x), 2b", nmhbins, mhmin, mhmax ) ;
   TH1F* h_amh_b1j_b2x__4b = new TH1F("h_amh_b1j_b2x__4b", "ave mh, (b1 j) (b2 x), 4b", nmhbins, mhmin, mhmax ) ;
   TH1F* h_dmh_b1j_b2x = new TH1F("h_dmh_b1j_b2x", "delta mh, (b1 j) (b2 x)", ndmhbins, dmhmin, dmhmax ) ;
   TH1F* h_dmh_b1j_b2x__2b = new TH1F("h_dmh_b1j_b2x__2b", "delta mh, (b1 j) (b2 x), 2b", ndmhbins, dmhmin, dmhmax ) ;
   TH1F* h_dmh_b1j_b2x__4b = new TH1F("h_dmh_b1j_b2x__4b", "delta mh, (b1 j) (b2 x), 4b", ndmhbins, dmhmin, dmhmax ) ;





   TH1F* h_mh_b1x_b2x__b1x = new TH1F("h_mh_b1x_b2x__b1x", "mh, (b1 x) (b2 x),  (b1 x)", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_b1x_b2x__b2x = new TH1F("h_mh_b1x_b2x__b2x", "mh, (b1 x) (b2 x),  (b2 x)", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_b1x_b2x__b1x_2b = new TH1F("h_mh_b1x_b2x__b1x_2b", "mh, (b1 x) (b2 x),  (b1 x), 2b", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_b1x_b2x__b2x_2b = new TH1F("h_mh_b1x_b2x__b2x_2b", "mh, (b1 x) (b2 x),  (b2 x), 2b", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_b1x_b2x__b1x_4b = new TH1F("h_mh_b1x_b2x__b1x_4b", "mh, (b1 x) (b2 x),  (b1 x), 4b", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_b1x_b2x__b2x_4b = new TH1F("h_mh_b1x_b2x__b2x_4b", "mh, (b1 x) (b2 x),  (b2 x), 4b", nmhbins, mhmin, mhmax ) ;
   TH1F* h_amh_b1x_b2x = new TH1F("h_amh_b1x_b2x", "ave mh, (b1 x) (b2 x)", nmhbins, mhmin, mhmax ) ;
   TH1F* h_amh_b1x_b2x__2b = new TH1F("h_amh_b1x_b2x__2b", "ave mh, (b1 x) (b2 x), 2b", nmhbins, mhmin, mhmax ) ;
   TH1F* h_amh_b1x_b2x__4b = new TH1F("h_amh_b1x_b2x__4b", "ave mh, (b1 x) (b2 x), 4b", nmhbins, mhmin, mhmax ) ;
   TH1F* h_dmh_b1x_b2x = new TH1F("h_dmh_b1x_b2x", "delta mh, (b1 x) (b2 x)", ndmhbins, dmhmin, dmhmax ) ;
   TH1F* h_dmh_b1x_b2x__2b = new TH1F("h_dmh_b1x_b2x__2b", "delta mh, (b1 x) (b2 x), 2b", ndmhbins, dmhmin, dmhmax ) ;
   TH1F* h_dmh_b1x_b2x__4b = new TH1F("h_dmh_b1x_b2x__4b", "delta mh, (b1 x) (b2 x), 4b", ndmhbins, dmhmin, dmhmax ) ;




   TH1F* h_mh_b1b2_jj__b1b2 = new TH1F("h_mh_b1b2_jj__b1b2", "mh, (b1 b2) (j j),  (b1 b2)", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_b1b2_jj__jj = new TH1F("h_mh_b1b2_jj__jj", "mh, (b1 b2) (j j),  (jj)", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_b1b2_jj__b1b2_2b = new TH1F("h_mh_b1b2_jj__b1b2_2b", "mh, (b1 b2) (j j),  (b1 b2), 2b", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_b1b2_jj__jj_2b = new TH1F("h_mh_b1b2_jj__jj_2b", "mh, (b1 b2) (j j),  (jj), 2b", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_b1b2_jj__b1b2_4b = new TH1F("h_mh_b1b2_jj__b1b2_4b", "mh, (b1 b2) (j j),  (b1 b2), 4b", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_b1b2_jj__jj_4b = new TH1F("h_mh_b1b2_jj__jj_4b", "mh, (b1 b2) (j j),  (jj), 4b", nmhbins, mhmin, mhmax ) ;
   TH1F* h_amh_b1b2_jj = new TH1F("h_amh_b1b2_jj", "ave mh, (b1 b2) (j j)", nmhbins, mhmin, mhmax ) ;
   TH1F* h_amh_b1b2_jj__2b = new TH1F("h_amh_b1b2_jj__2b", "ave mh, (b1 b2) (j j), 2b", nmhbins, mhmin, mhmax ) ;
   TH1F* h_amh_b1b2_jj__4b = new TH1F("h_amh_b1b2_jj__4b", "ave mh, (b1 b2) (j j), 4b", nmhbins, mhmin, mhmax ) ;
   TH1F* h_dmh_b1b2_jj = new TH1F("h_dmh_b1b2_jj", "delta mh, (b1 b2) (j j)", ndmhbins, dmhmin, dmhmax ) ;
   TH1F* h_dmh_b1b2_jj__2b = new TH1F("h_dmh_b1b2_jj__2b", "delta mh, (b1 b2) (j j), 2b", ndmhbins, dmhmin, dmhmax ) ;
   TH1F* h_dmh_b1b2_jj__4b = new TH1F("h_dmh_b1b2_jj__4b", "delta mh, (b1 b2) (j j), 4b", ndmhbins, dmhmin, dmhmax ) ;






   TH1F* h_mh_b1b2_jx__b1b2 = new TH1F("h_mh_b1b2_jx__b1b2", "mh, (b1 b2) (j x),  (b1 b2)", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_b1b2_jx__jx = new TH1F("h_mh_b1b2_jx__jx", "mh, (b1 b2) (j x),  (jx)", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_b1b2_jx__b1b2_2b = new TH1F("h_mh_b1b2_jx__b1b2_2b", "mh, (b1 b2) (j x),  (b1 b2), 2b", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_b1b2_jx__jx_2b = new TH1F("h_mh_b1b2_jx__jx_2b", "mh, (b1 b2) (j x),  (jx), 2b", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_b1b2_jx__b1b2_4b = new TH1F("h_mh_b1b2_jx__b1b2_4b", "mh, (b1 b2) (j x),  (b1 b2), 4b", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_b1b2_jx__jx_4b = new TH1F("h_mh_b1b2_jx__jx_4b", "mh, (b1 b2) (j x),  (jx), 4b", nmhbins, mhmin, mhmax ) ;
   TH1F* h_amh_b1b2_jx = new TH1F("h_amh_b1b2_jx", "ave mh, (b1 b2) (j x)", nmhbins, mhmin, mhmax ) ;
   TH1F* h_amh_b1b2_jx__2b = new TH1F("h_amh_b1b2_jx__2b", "ave mh, (b1 b2) (j x), 2b", nmhbins, mhmin, mhmax ) ;
   TH1F* h_amh_b1b2_jx__4b = new TH1F("h_amh_b1b2_jx__4b", "ave mh, (b1 b2) (j x), 4b", nmhbins, mhmin, mhmax ) ;
   TH1F* h_dmh_b1b2_jx = new TH1F("h_dmh_b1b2_jx", "delta mh, (b1 b2) (j x)", ndmhbins, dmhmin, dmhmax ) ;
   TH1F* h_dmh_b1b2_jx__2b = new TH1F("h_dmh_b1b2_jx__2b", "delta mh, (b1 b2) (j x), 2b", ndmhbins, dmhmin, dmhmax ) ;
   TH1F* h_dmh_b1b2_jx__4b = new TH1F("h_dmh_b1b2_jx__4b", "delta mh, (b1 b2) (j x), 4b", ndmhbins, dmhmin, dmhmax ) ;





   TH1F* h_amh_other = new TH1F("h_amh_other", "ave mh, other", nmhbins, mhmin, mhmax ) ;
   TH1F* h_amh_other__2b = new TH1F("h_amh_other__2b", "ave mh, other, 2b", nmhbins, mhmin, mhmax ) ;
   TH1F* h_amh_other__4b = new TH1F("h_amh_other__4b", "ave mh, other, 4b", nmhbins, mhmin, mhmax ) ;
   TH1F* h_dmh_other = new TH1F("h_dmh_other", "delta mh, other", ndmhbins, dmhmin, dmhmax ) ;
   TH1F* h_dmh_other__2b = new TH1F("h_dmh_other__2b", "ave mh, other, 2b", ndmhbins, dmhmin, dmhmax ) ;
   TH1F* h_dmh_other__4b = new TH1F("h_dmh_other__4b", "ave mh, other, 4b", ndmhbins, dmhmin, dmhmax ) ;





   TH1F* h_mh_all__b1 = new TH1F("h_mh_all__b1", "mh, all, higgs with b1", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__b2 = new TH1F("h_mh_all__b2", "mh, all, higgs with b2", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__b1_2b = new TH1F("h_mh_all__b1_2b", "mh, all, higgs with b1, 2b", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__b2_2b = new TH1F("h_mh_all__b2_2b", "mh, all, higgs with b2, 2b", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__b1_4b = new TH1F("h_mh_all__b1_4b", "mh, all, higgs with b1, 4b", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__b2_4b = new TH1F("h_mh_all__b2_4b", "mh, all, higgs with b2, 4b", nmhbins, mhmin, mhmax ) ;

   TH1F* h_mh_all__spth = new TH1F("h_mh_all__spth", "mh, all, higgs with higher sum jet pt", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__sptl = new TH1F("h_mh_all__sptl", "mh, all, higgs with lower sum jet pt", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__spth_2b = new TH1F("h_mh_all__spth_2b", "mh, all, higgs with higher sum jet pt, 2b", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__sptl_2b = new TH1F("h_mh_all__sptl_2b", "mh, all, higgs with lower sum jet pt, 2b", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__spth_4b = new TH1F("h_mh_all__spth_4b", "mh, all, higgs with higher sum jet pt, 4b", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__sptl_4b = new TH1F("h_mh_all__sptl_4b", "mh, all, higgs with lower sum jet pt, 4b", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__spth_2b_njrw = new TH1F("h_mh_all__spth_2b_njrw", "mh, all, higgs with higher sum jet pt, 2b, Njets reweighted", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__sptl_2b_njrw = new TH1F("h_mh_all__sptl_2b_njrw", "mh, all, higgs with lower sum jet pt, 2b, Njets reweighted", nmhbins, mhmin, mhmax ) ;

   TH1F* h_amh_all = new TH1F("h_amh_all", "ave mh, all", nmhbins, mhmin, mhmax ) ;
   TH1F* h_amh_all__2b = new TH1F("h_amh_all__2b", "ave mh, all, 2b", nmhbins, mhmin, mhmax ) ;
   TH1F* h_amh_all__4b = new TH1F("h_amh_all__4b", "ave mh, all, 4b", nmhbins, mhmin, mhmax ) ;
   TH1F* h_dmh_all = new TH1F("h_dmh_all", "delta mh, all", ndmhbins, dmhmin, dmhmax ) ;
   TH1F* h_dmh_all__2b = new TH1F("h_dmh_all__2b", "delta mh, all, 2b", ndmhbins, dmhmin, dmhmax ) ;
   TH1F* h_dmh_all__4b = new TH1F("h_dmh_all__4b", "delta mh, all, 4b", ndmhbins, dmhmin, dmhmax ) ;




   TH1F* h_mh_all__b1_4j = new TH1F("h_mh_all__b1_4j", "mh, all, higgs with b1, 4j", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__b2_4j = new TH1F("h_mh_all__b2_4j", "mh, all, higgs with b2, 4j", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__b1_2b_4j = new TH1F("h_mh_all__b1_2b_4j", "mh, all, higgs with b1, 2b, 4j", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__b2_2b_4j = new TH1F("h_mh_all__b2_2b_4j", "mh, all, higgs with b2, 2b, 4j", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__b1_4b_4j = new TH1F("h_mh_all__b1_4b_4j", "mh, all, higgs with b1, 4b, 4j", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__b2_4b_4j = new TH1F("h_mh_all__b2_4b_4j", "mh, all, higgs with b2, 4b, 4j", nmhbins, mhmin, mhmax ) ;

   TH1F* h_mh_all__spth_4j = new TH1F("h_mh_all__spth_4j", "mh, all, higgs with higher sum jet pt, 4j", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__sptl_4j = new TH1F("h_mh_all__sptl_4j", "mh, all, higgs with lower sum jet pt, 4j", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__spth_2b_4j = new TH1F("h_mh_all__spth_2b_4j", "mh, all, higgs with higher sum jet pt, 2b, 4j", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__sptl_2b_4j = new TH1F("h_mh_all__sptl_2b_4j", "mh, all, higgs with lower sum jet pt, 2b, 4j", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__spth_4b_4j = new TH1F("h_mh_all__spth_4b_4j", "mh, all, higgs with higher sum jet pt, 4b, 4j", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__sptl_4b_4j = new TH1F("h_mh_all__sptl_4b_4j", "mh, all, higgs with lower sum jet pt, 4b, 4j", nmhbins, mhmin, mhmax ) ;

   TH1F* h_amh_all_4j = new TH1F("h_amh_all_4j", "ave mh, all, 4j", nmhbins, mhmin, mhmax ) ;
   TH1F* h_amh_all__2b_4j = new TH1F("h_amh_all__2b_4j", "ave mh, all, 2b, 4j", nmhbins, mhmin, mhmax ) ;
   TH1F* h_amh_all__4b_4j = new TH1F("h_amh_all__4b_4j", "ave mh, all, 4b, 4j", nmhbins, mhmin, mhmax ) ;
   TH1F* h_dmh_all_4j = new TH1F("h_dmh_all_4j", "delta mh, all, 4j", ndmhbins, dmhmin, dmhmax ) ;
   TH1F* h_dmh_all__2b_4j = new TH1F("h_dmh_all__2b_4j", "delta mh, all, 2b, 4j", ndmhbins, dmhmin, dmhmax ) ;
   TH1F* h_dmh_all__4b_4j = new TH1F("h_dmh_all__4b_4j", "delta mh, all, 4b, 4j", ndmhbins, dmhmin, dmhmax ) ;





   TH1F* h_mh_all__b1_5j = new TH1F("h_mh_all__b1_5j", "mh, all, higgs with b1, 5j", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__b2_5j = new TH1F("h_mh_all__b2_5j", "mh, all, higgs with b2, 5j", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__b1_2b_5j = new TH1F("h_mh_all__b1_2b_5j", "mh, all, higgs with b1, 2b, 5j", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__b2_2b_5j = new TH1F("h_mh_all__b2_2b_5j", "mh, all, higgs with b2, 2b, 5j", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__b1_4b_5j = new TH1F("h_mh_all__b1_4b_5j", "mh, all, higgs with b1, 4b, 5j", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__b2_4b_5j = new TH1F("h_mh_all__b2_4b_5j", "mh, all, higgs with b2, 4b, 5j", nmhbins, mhmin, mhmax ) ;

   TH1F* h_mh_all__spth_5j = new TH1F("h_mh_all__spth_5j", "mh, all, higgs with higher sum jet pt, 5j", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__sptl_5j = new TH1F("h_mh_all__sptl_5j", "mh, all, higgs with lower sum jet pt, 5j", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__spth_2b_5j = new TH1F("h_mh_all__spth_2b_5j", "mh, all, higgs with higher sum jet pt, 2b, 5j", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__sptl_2b_5j = new TH1F("h_mh_all__sptl_2b_5j", "mh, all, higgs with lower sum jet pt, 2b, 5j", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__spth_4b_5j = new TH1F("h_mh_all__spth_4b_5j", "mh, all, higgs with higher sum jet pt, 4b, 5j", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__sptl_4b_5j = new TH1F("h_mh_all__sptl_4b_5j", "mh, all, higgs with lower sum jet pt, 4b, 5j", nmhbins, mhmin, mhmax ) ;

   TH1F* h_amh_all_5j = new TH1F("h_amh_all_5j", "ave mh, all, 5j", nmhbins, mhmin, mhmax ) ;
   TH1F* h_amh_all__2b_5j = new TH1F("h_amh_all__2b_5j", "ave mh, all, 2b, 5j", nmhbins, mhmin, mhmax ) ;
   TH1F* h_amh_all__4b_5j = new TH1F("h_amh_all__4b_5j", "ave mh, all, 4b, 5j", nmhbins, mhmin, mhmax ) ;
   TH1F* h_dmh_all_5j = new TH1F("h_dmh_all_5j", "delta mh, all, 5j", ndmhbins, dmhmin, dmhmax ) ;
   TH1F* h_dmh_all__2b_5j = new TH1F("h_dmh_all__2b_5j", "delta mh, all, 2b, 5j", ndmhbins, dmhmin, dmhmax ) ;
   TH1F* h_dmh_all__4b_5j = new TH1F("h_dmh_all__4b_5j", "delta mh, all, 4b, 5j", ndmhbins, dmhmin, dmhmax ) ;





   TH1F* h_mh_all__b1_ms40 = new TH1F("h_mh_all__b1_ms40", "mh, all, higgs with b1, METsig>40", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__b2_ms40 = new TH1F("h_mh_all__b2_ms40", "mh, all, higgs with b2, METsig>40", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__b1_2b_ms40 = new TH1F("h_mh_all__b1_2b_ms40", "mh, all, higgs with b1, 2b, METsig>40", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__b2_2b_ms40 = new TH1F("h_mh_all__b2_2b_ms40", "mh, all, higgs with b2, 2b, METsig>40", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__b1_4b_ms40 = new TH1F("h_mh_all__b1_4b_ms40", "mh, all, higgs with b1, 4b, METsig>40", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__b2_4b_ms40 = new TH1F("h_mh_all__b2_4b_ms40", "mh, all, higgs with b2, 4b, METsig>40", nmhbins, mhmin, mhmax ) ;

   TH1F* h_mh_all__spth_ms40 = new TH1F("h_mh_all__spth_ms40", "mh, all, higgs with higher sum jet pt, METsig>40", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__sptl_ms40 = new TH1F("h_mh_all__sptl_ms40", "mh, all, higgs with lower sum jet pt, METsig>40", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__spth_2b_ms40 = new TH1F("h_mh_all__spth_2b_ms40", "mh, all, higgs with higher sum jet pt, 2b, METsig>40", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__sptl_2b_ms40 = new TH1F("h_mh_all__sptl_2b_ms40", "mh, all, higgs with lower sum jet pt, 2b, METsig>40", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__spth_4b_ms40 = new TH1F("h_mh_all__spth_4b_ms40", "mh, all, higgs with higher sum jet pt, 4b, METsig>40", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__sptl_4b_ms40 = new TH1F("h_mh_all__sptl_4b_ms40", "mh, all, higgs with lower sum jet pt, 4b, METsig>40", nmhbins, mhmin, mhmax ) ;

   TH1F* h_amh_all_ms40 = new TH1F("h_amh_all_ms40", "ave mh, all, METsig>40", nmhbins, mhmin, mhmax ) ;
   TH1F* h_amh_all__2b_ms40 = new TH1F("h_amh_all__2b_ms40", "ave mh, all, 2b, METsig>40", nmhbins, mhmin, mhmax ) ;
   TH1F* h_amh_all__4b_ms40 = new TH1F("h_amh_all__4b_ms40", "ave mh, all, 4b, METsig>40", nmhbins, mhmin, mhmax ) ;
   TH1F* h_dmh_all_ms40 = new TH1F("h_dmh_all_ms40", "delta mh, all, METsig>40", ndmhbins, dmhmin, dmhmax ) ;
   TH1F* h_dmh_all__2b_ms40 = new TH1F("h_dmh_all__2b_ms40", "delta mh, all, 2b, METsig>40", ndmhbins, dmhmin, dmhmax ) ;
   TH1F* h_dmh_all__4b_ms40 = new TH1F("h_dmh_all__4b_ms40", "delta mh, all, 4b, METsig>40", ndmhbins, dmhmin, dmhmax ) ;





   TH1F* h_mh_all__b1_ms85 = new TH1F("h_mh_all__b1_ms85", "mh, all, higgs with b1, METsig>85", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__b2_ms85 = new TH1F("h_mh_all__b2_ms85", "mh, all, higgs with b2, METsig>85", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__b1_2b_ms85 = new TH1F("h_mh_all__b1_2b_ms85", "mh, all, higgs with b1, 2b, METsig>85", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__b2_2b_ms85 = new TH1F("h_mh_all__b2_2b_ms85", "mh, all, higgs with b2, 2b, METsig>85", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__b1_4b_ms85 = new TH1F("h_mh_all__b1_4b_ms85", "mh, all, higgs with b1, 4b, METsig>85", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__b2_4b_ms85 = new TH1F("h_mh_all__b2_4b_ms85", "mh, all, higgs with b2, 4b, METsig>85", nmhbins, mhmin, mhmax ) ;

   TH1F* h_mh_all__spth_ms85 = new TH1F("h_mh_all__spth_ms85", "mh, all, higgs with higher sum jet pt, METsig>85", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__sptl_ms85 = new TH1F("h_mh_all__sptl_ms85", "mh, all, higgs with lower sum jet pt, METsig>85", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__spth_2b_ms85 = new TH1F("h_mh_all__spth_2b_ms85", "mh, all, higgs with higher sum jet pt, 2b, METsig>85", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__sptl_2b_ms85 = new TH1F("h_mh_all__sptl_2b_ms85", "mh, all, higgs with lower sum jet pt, 2b, METsig>85", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__spth_4b_ms85 = new TH1F("h_mh_all__spth_4b_ms85", "mh, all, higgs with higher sum jet pt, 4b, METsig>85", nmhbins, mhmin, mhmax ) ;
   TH1F* h_mh_all__sptl_4b_ms85 = new TH1F("h_mh_all__sptl_4b_ms85", "mh, all, higgs with lower sum jet pt, 4b, METsig>85", nmhbins, mhmin, mhmax ) ;

   TH1F* h_amh_all_ms85 = new TH1F("h_amh_all_ms85", "ave mh, all, METsig>85", nmhbins, mhmin, mhmax ) ;
   TH1F* h_amh_all__2b_ms85 = new TH1F("h_amh_all__2b_ms85", "ave mh, all, 2b, METsig>85", nmhbins, mhmin, mhmax ) ;
   TH1F* h_amh_all__4b_ms85 = new TH1F("h_amh_all__4b_ms85", "ave mh, all, 4b, METsig>85", nmhbins, mhmin, mhmax ) ;
   TH1F* h_dmh_all_ms85 = new TH1F("h_dmh_all_ms85", "delta mh, all, METsig>85", ndmhbins, dmhmin, dmhmax ) ;
   TH1F* h_dmh_all__2b_ms85 = new TH1F("h_dmh_all__2b_ms85", "delta mh, all, 2b, METsig>85", ndmhbins, dmhmin, dmhmax ) ;
   TH1F* h_dmh_all__4b_ms85 = new TH1F("h_dmh_all__4b_ms85", "delta mh, all, 4b, METsig>85", ndmhbins, dmhmin, dmhmax ) ;





   int n_metsig_bins(7) ;
   ///double metsig_bins[8] = { 0., 10., 20., 30., 50., 100., 150., 200. } ;  // scale for METsig
   double metsig_bins[8] = { 0., 9., 17., 25., 40., 85., 120., 170. } ;

   TH1F* h_metsig_msig_2b = new TH1F("h_metsig_msig_2b", "METsig, mass sig box, 2b", n_metsig_bins, metsig_bins ) ;
   TH1F* h_metsig_msig_3b = new TH1F("h_metsig_msig_3b", "METsig, mass sig box, 3b", n_metsig_bins, metsig_bins ) ;
   TH1F* h_metsig_msig_4b = new TH1F("h_metsig_msig_4b", "METsig, mass sig box, 4b", n_metsig_bins, metsig_bins ) ;
   TH1F* h_metsig_msb_2b = new TH1F("h_metsig_msb_2b", "METsig, mass SB, 2b", n_metsig_bins, metsig_bins ) ;
   TH1F* h_metsig_msb_3b = new TH1F("h_metsig_msb_3b", "METsig, mass SB, 3b", n_metsig_bins, metsig_bins ) ;
   TH1F* h_metsig_msb_4b = new TH1F("h_metsig_msb_4b", "METsig, mass SB, 4b", n_metsig_bins, metsig_bins ) ;
   TH1F* h_metsig_rmsigsb_2b = new TH1F("h_metsig_rmsigsb_2b", "METsig, mass SIG/SB ratio, 2b", n_metsig_bins, metsig_bins ) ;
   TH1F* h_metsig_rmsigsb_3b = new TH1F("h_metsig_rmsigsb_3b", "METsig, mass SIG/SB ratio, 3b", n_metsig_bins, metsig_bins ) ;
   TH1F* h_metsig_rmsigsb_4b = new TH1F("h_metsig_rmsigsb_4b", "METsig, mass SIG/SB ratio, 4b", n_metsig_bins, metsig_bins ) ;

   TH1F* h_metsig_msig_2b_4j = new TH1F("h_metsig_msig_2b_4j", "METsig, mass sig box, 2b, 4j", n_metsig_bins, metsig_bins ) ;
   TH1F* h_metsig_msig_3b_4j = new TH1F("h_metsig_msig_3b_4j", "METsig, mass sig box, 3b, 4j", n_metsig_bins, metsig_bins ) ;
   TH1F* h_metsig_msig_4b_4j = new TH1F("h_metsig_msig_4b_4j", "METsig, mass sig box, 4b, 4j", n_metsig_bins, metsig_bins ) ;
   TH1F* h_metsig_msb_2b_4j = new TH1F("h_metsig_msb_2b_4j", "METsig, mass SB, 2b, 4j", n_metsig_bins, metsig_bins ) ;
   TH1F* h_metsig_msb_3b_4j = new TH1F("h_metsig_msb_3b_4j", "METsig, mass SB, 3b, 4j", n_metsig_bins, metsig_bins ) ;
   TH1F* h_metsig_msb_4b_4j = new TH1F("h_metsig_msb_4b_4j", "METsig, mass SB, 4b, 4j", n_metsig_bins, metsig_bins ) ;
   TH1F* h_metsig_rmsigsb_2b_4j = new TH1F("h_metsig_rmsigsb_2b_4j", "METsig, mass SIG/SB ratio, 2b, 4j", n_metsig_bins, metsig_bins ) ;
   TH1F* h_metsig_rmsigsb_3b_4j = new TH1F("h_metsig_rmsigsb_3b_4j", "METsig, mass SIG/SB ratio, 3b, 4j", n_metsig_bins, metsig_bins ) ;
   TH1F* h_metsig_rmsigsb_4b_4j = new TH1F("h_metsig_rmsigsb_4b_4j", "METsig, mass SIG/SB ratio, 4b, 4j", n_metsig_bins, metsig_bins ) ;

   TH1F* h_metsig_msig_2b_5j = new TH1F("h_metsig_msig_2b_5j", "METsig, mass sig box, 2b, 5j", n_metsig_bins, metsig_bins ) ;
   TH1F* h_metsig_msig_3b_5j = new TH1F("h_metsig_msig_3b_5j", "METsig, mass sig box, 3b, 5j", n_metsig_bins, metsig_bins ) ;
   TH1F* h_metsig_msig_4b_5j = new TH1F("h_metsig_msig_4b_5j", "METsig, mass sig box, 4b, 5j", n_metsig_bins, metsig_bins ) ;
   TH1F* h_metsig_msb_2b_5j = new TH1F("h_metsig_msb_2b_5j", "METsig, mass SB, 2b, 5j", n_metsig_bins, metsig_bins ) ;
   TH1F* h_metsig_msb_3b_5j = new TH1F("h_metsig_msb_3b_5j", "METsig, mass SB, 3b, 5j", n_metsig_bins, metsig_bins ) ;
   TH1F* h_metsig_msb_4b_5j = new TH1F("h_metsig_msb_4b_5j", "METsig, mass SB, 4b, 5j", n_metsig_bins, metsig_bins ) ;
   TH1F* h_metsig_rmsigsb_2b_5j = new TH1F("h_metsig_rmsigsb_2b_5j", "METsig, mass SIG/SB ratio, 2b, 5j", n_metsig_bins, metsig_bins ) ;
   TH1F* h_metsig_rmsigsb_3b_5j = new TH1F("h_metsig_rmsigsb_3b_5j", "METsig, mass SIG/SB ratio, 3b, 5j", n_metsig_bins, metsig_bins ) ;
   TH1F* h_metsig_rmsigsb_4b_5j = new TH1F("h_metsig_rmsigsb_4b_5j", "METsig, mass SIG/SB ratio, 4b, 5j", n_metsig_bins, metsig_bins ) ;

   TH1F* h_metsig_msig_2b_mdpc = new TH1F("h_metsig_msig_2b_mdpc", "METsig, mass sig box, 2b, minDeltaPhi30>0.3", n_metsig_bins, metsig_bins ) ;
   TH1F* h_metsig_msig_3b_mdpc = new TH1F("h_metsig_msig_3b_mdpc", "METsig, mass sig box, 3b, minDeltaPhi30>0.3", n_metsig_bins, metsig_bins ) ;
   TH1F* h_metsig_msig_4b_mdpc = new TH1F("h_metsig_msig_4b_mdpc", "METsig, mass sig box, 4b, minDeltaPhi30>0.3", n_metsig_bins, metsig_bins ) ;
   TH1F* h_metsig_msb_2b_mdpc = new TH1F("h_metsig_msb_2b_mdpc", "METsig, mass SB, 2b, minDeltaPhi30>0.3", n_metsig_bins, metsig_bins ) ;
   TH1F* h_metsig_msb_3b_mdpc = new TH1F("h_metsig_msb_3b_mdpc", "METsig, mass SB, 3b, minDeltaPhi30>0.3", n_metsig_bins, metsig_bins ) ;
   TH1F* h_metsig_msb_4b_mdpc = new TH1F("h_metsig_msb_4b_mdpc", "METsig, mass SB, 4b, minDeltaPhi30>0.3", n_metsig_bins, metsig_bins ) ;
   TH1F* h_metsig_rmsigsb_2b_mdpc = new TH1F("h_metsig_rmsigsb_2b_mdpc", "METsig, mass SIG/SB ratio, 2b, minDeltaPhi30>0.3", n_metsig_bins, metsig_bins ) ;
   TH1F* h_metsig_rmsigsb_3b_mdpc = new TH1F("h_metsig_rmsigsb_3b_mdpc", "METsig, mass SIG/SB ratio, 3b, minDeltaPhi30>0.3", n_metsig_bins, metsig_bins ) ;
   TH1F* h_metsig_rmsigsb_4b_mdpc = new TH1F("h_metsig_rmsigsb_4b_mdpc", "METsig, mass SIG/SB ratio, 4b, minDeltaPhi30>0.3", n_metsig_bins, metsig_bins ) ;

   TH1F* h_metsig_rmsigsb_2b_NjetReweight = new TH1F("h_metsig_rmsigsb_2b_NjetReweight", "METsig, mass SIG/SB ratio, 2b, Njet reweighted", n_metsig_bins, metsig_bins ) ;

   TH1F* h_metsig_msig_2b_ptrw = new TH1F("h_metsig_msig_2b_ptrw", "METsig, mass sig box, 2b, pt reweighted", n_metsig_bins, metsig_bins ) ;
   TH1F* h_metsig_msb_2b_ptrw = new TH1F("h_metsig_msb_2b_ptrw", "METsig, mass SB, 2b, pt reweighted", n_metsig_bins, metsig_bins ) ;
   TH1F* h_metsig_rmsigsb_2b_ptrw = new TH1F("h_metsig_rmsigsb_2b_ptrw", "METsig, mass SIG/SB ratio, 2b, pt reweighted", n_metsig_bins, metsig_bins ) ;

   TH1F* h_metsig_msig_2b_4j_ptrw = new TH1F("h_metsig_msig_2b_4j_ptrw", "METsig, mass sig box, 2b, 4j, pt reweighted", n_metsig_bins, metsig_bins ) ;
   TH1F* h_metsig_msb_2b_4j_ptrw = new TH1F("h_metsig_msb_2b_4j_ptrw", "METsig, mass SB, 2b, 4j, pt reweighted", n_metsig_bins, metsig_bins ) ;
   TH1F* h_metsig_rmsigsb_2b_4j_ptrw = new TH1F("h_metsig_rmsigsb_2b_4j_ptrw", "METsig, mass SIG/SB ratio, 2b, 4j, pt reweighted", n_metsig_bins, metsig_bins ) ;

   TH1F* h_metsig_msig_2b_5j_ptrw = new TH1F("h_metsig_msig_2b_5j_ptrw", "METsig, mass sig box, 2b, 5j, pt reweighted", n_metsig_bins, metsig_bins ) ;
   TH1F* h_metsig_msb_2b_5j_ptrw = new TH1F("h_metsig_msb_2b_5j_ptrw", "METsig, mass SB, 2b, 5j, pt reweighted", n_metsig_bins, metsig_bins ) ;
   TH1F* h_metsig_rmsigsb_2b_5j_ptrw = new TH1F("h_metsig_rmsigsb_2b_5j_ptrw", "METsig, mass SIG/SB ratio, 2b, 5j, pt reweighted", n_metsig_bins, metsig_bins ) ;

   TH1F* h_metsig_rmsigsb_2b_NjetReweight_ptrw = new TH1F("h_metsig_rmsigsb_2b_NjetReweight_ptrw", "METsig, mass SIG/SB ratio, 2b, Njet reweighted, pt reweighted", n_metsig_bins, metsig_bins ) ;

   TH1F* h_metsig_msig_2b_sptrw = new TH1F("h_metsig_msig_2b_sptrw", "METsig, mass sig box, 2b, sum pt reweighted", n_metsig_bins, metsig_bins ) ;
   TH1F* h_metsig_msb_2b_sptrw = new TH1F("h_metsig_msb_2b_sptrw", "METsig, mass SB, 2b, sum pt reweighted", n_metsig_bins, metsig_bins ) ;
   TH1F* h_metsig_rmsigsb_2b_sptrw = new TH1F("h_metsig_rmsigsb_2b_sptrw", "METsig, mass SIG/SB ratio, 2b, sum pt reweighted", n_metsig_bins, metsig_bins ) ;

   h_metsig_msig_2b_ptrw -> Sumw2() ;
   h_metsig_msb_2b_ptrw -> Sumw2() ;
   h_metsig_msig_2b_4j_ptrw -> Sumw2() ;
   h_metsig_msb_2b_4j_ptrw -> Sumw2() ;
   h_metsig_msig_2b_5j_ptrw -> Sumw2() ;
   h_metsig_msb_2b_5j_ptrw -> Sumw2() ;

   h_metsig_msig_2b_sptrw -> Sumw2() ;
   h_metsig_msb_2b_sptrw -> Sumw2() ;



 //TH1F* h_sumpt = new TH1F("h_sumpt", "sum pt of 4 jets", 10, 0., 1000. ) ;
 //TH1F* h_sumpt__2b = new TH1F("h_sumpt__2b", "sum pt of 4 jets, 2b", 10, 0., 1000. ) ;
 //TH1F* h_sumpt__4b = new TH1F("h_sumpt__4b", "sum pt of 4 jets, 4b", 10, 0., 1000. ) ;
 //TH1F* h_sumpt__2b_ms40 = new TH1F("h_sumpt__2b_ms40", "sum pt of 4 jets, 2b, METsig>40", 10, 0., 1000. ) ;
 //TH1F* h_sumpt__4b_ms40 = new TH1F("h_sumpt__4b_ms40", "sum pt of 4 jets, 4b, METsig>40", 10, 0., 1000. ) ;
 //TH1F* h_sumpt__2b_ms85 = new TH1F("h_sumpt__2b_ms85", "sum pt of 4 jets, 2b, METsig>85", 10, 0., 1000. ) ;
 //TH1F* h_sumpt__4b_ms85 = new TH1F("h_sumpt__4b_ms85", "sum pt of 4 jets, 4b, METsig>85", 10, 0., 1000. ) ;
 //TH1F* h_sumpt__2b_4j = new TH1F("h_sumpt__2b_4j", "sum pt of 4 jets, 2b, 4j", 10, 0., 1000. ) ;
 //TH1F* h_sumpt__4b_4j = new TH1F("h_sumpt__4b_4j", "sum pt of 4 jets, 4b, 4j", 10, 0., 1000. ) ;
 //TH1F* h_sumpt__2b_5j = new TH1F("h_sumpt__2b_5j", "sum pt of 4 jets, 2b, 5j", 10, 0., 1000. ) ;
 //TH1F* h_sumpt__4b_5j = new TH1F("h_sumpt__4b_5j", "sum pt of 4 jets, 4b, 5j", 10, 0., 1000. ) ;
 //TH1F* h_sumpt__weight = new TH1F("h_sumpt__weight", "sum pt of 4 jets, weight", 10, 0., 1000. ) ;


   TH1F* h_sumpt = new TH1F("h_sumpt", "sum pt of 4 jets", nbinssumpt, sumpt_bins ) ;
   TH1F* h_sumpt__2b = new TH1F("h_sumpt__2b", "sum pt of 4 jets, 2b", nbinssumpt, sumpt_bins ) ;
   TH1F* h_sumpt__4b = new TH1F("h_sumpt__4b", "sum pt of 4 jets, 4b", nbinssumpt, sumpt_bins ) ;
   TH1F* h_sumpt__2b_ms40 = new TH1F("h_sumpt__2b_ms40", "sum pt of 4 jets, 2b, METsig>40", nbinssumpt, sumpt_bins ) ;
   TH1F* h_sumpt__4b_ms40 = new TH1F("h_sumpt__4b_ms40", "sum pt of 4 jets, 4b, METsig>40", nbinssumpt, sumpt_bins ) ;
   TH1F* h_sumpt__2b_ms85 = new TH1F("h_sumpt__2b_ms85", "sum pt of 4 jets, 2b, METsig>85", nbinssumpt, sumpt_bins ) ;
   TH1F* h_sumpt__4b_ms85 = new TH1F("h_sumpt__4b_ms85", "sum pt of 4 jets, 4b, METsig>85", nbinssumpt, sumpt_bins ) ;
   TH1F* h_sumpt__2b_4j = new TH1F("h_sumpt__2b_4j", "sum pt of 4 jets, 2b, 4j", nbinssumpt, sumpt_bins ) ;
   TH1F* h_sumpt__4b_4j = new TH1F("h_sumpt__4b_4j", "sum pt of 4 jets, 4b, 4j", nbinssumpt, sumpt_bins ) ;
   TH1F* h_sumpt__2b_5j = new TH1F("h_sumpt__2b_5j", "sum pt of 4 jets, 2b, 5j", nbinssumpt, sumpt_bins ) ;
   TH1F* h_sumpt__4b_5j = new TH1F("h_sumpt__4b_5j", "sum pt of 4 jets, 4b, 5j", nbinssumpt, sumpt_bins ) ;
   TH1F* h_sumpt__weight = new TH1F("h_sumpt__weight", "sum pt of 4 jets, weight", nbinssumpt, sumpt_bins ) ;



   int nbinspt(20) ;
   float ptlow(0.) ;
   float pthigh(400.) ;

   TH1F* h_pt_highest_csv = new TH1F("h_pt_highest_csv", "jet pt, highest CSV", nbinspt, ptlow, pthigh ) ;
   TH1F* h_pt_nexthighest_csv = new TH1F("h_pt_nexthighest_csv", "jet pt, nexthighest CSV", nbinspt, ptlow, pthigh ) ;
   TH1F* h_pt_nextlowest_csv = new TH1F("h_pt_nextlowest_csv", "jet pt, next lowest CSV", nbinspt, ptlow, pthigh ) ;
   TH1F* h_pt_lowest_csv = new TH1F("h_pt_lowest_csv", "jet pt, lowest CSV", nbinspt, ptlow, pthigh ) ;

   TH1F* h_pt_highest_csv_2b = new TH1F("h_pt_highest_csv_2b", "jet pt, highest CSV, 2b", nbinspt, ptlow, pthigh ) ;
   TH1F* h_pt_nexthighest_csv_2b = new TH1F("h_pt_nexthighest_csv_2b", "jet pt, nexthighest CSV, 2b", nbinspt, ptlow, pthigh ) ;
   TH1F* h_pt_nextlowest_csv_2b = new TH1F("h_pt_nextlowest_csv_2b", "jet pt, next lowest CSV, 2b", nbinspt, ptlow, pthigh ) ;
   TH1F* h_pt_lowest_csv_2b = new TH1F("h_pt_lowest_csv_2b", "jet pt, lowest CSV, 2b", nbinspt, ptlow, pthigh ) ;

   TH1F* h_pt_highest_csv_3b = new TH1F("h_pt_highest_csv_3b", "jet pt, highest CSV, 3b", nbinspt, ptlow, pthigh ) ;
   TH1F* h_pt_nexthighest_csv_3b = new TH1F("h_pt_nexthighest_csv_3b", "jet pt, nexthighest CSV, 3b", nbinspt, ptlow, pthigh ) ;
   TH1F* h_pt_nextlowest_csv_3b = new TH1F("h_pt_nextlowest_csv_3b", "jet pt, next lowest CSV, 3b", nbinspt, ptlow, pthigh ) ;
   TH1F* h_pt_lowest_csv_3b = new TH1F("h_pt_lowest_csv_3b", "jet pt, lowest CSV, 3b", nbinspt, ptlow, pthigh ) ;

   TH1F* h_pt_highest_csv_4b = new TH1F("h_pt_highest_csv_4b", "jet pt, highest CSV, 4b", nbinspt, ptlow, pthigh ) ;
   TH1F* h_pt_nexthighest_csv_4b = new TH1F("h_pt_nexthighest_csv_4b", "jet pt, nexthighest CSV, 4b", nbinspt, ptlow, pthigh ) ;
   TH1F* h_pt_nextlowest_csv_4b = new TH1F("h_pt_nextlowest_csv_4b", "jet pt, next lowest CSV, 4b", nbinspt, ptlow, pthigh ) ;
   TH1F* h_pt_lowest_csv_4b = new TH1F("h_pt_lowest_csv_4b", "jet pt, lowest CSV, 4b", nbinspt, ptlow, pthigh ) ;

   TH1F* h_pt_highest_csv_2b_ptrw = new TH1F("h_pt_highest_csv_2b_ptrw", "jet pt, highest CSV, 2b, pt reweighted", nbinspt, ptlow, pthigh ) ;
   TH1F* h_pt_nexthighest_csv_2b_ptrw = new TH1F("h_pt_nexthighest_csv_2b_ptrw", "jet pt, nexthighest CSV, 2b, pt reweighted", nbinspt, ptlow, pthigh ) ;
   TH1F* h_pt_nextlowest_csv_2b_ptrw = new TH1F("h_pt_nextlowest_csv_2b_ptrw", "jet pt, next lowest CSV, 2b, pt reweighted", nbinspt, ptlow, pthigh ) ;
   TH1F* h_pt_lowest_csv_2b_ptrw = new TH1F("h_pt_lowest_csv_2b_ptrw", "jet pt, lowest CSV, 2b, pt reweighted", nbinspt, ptlow, pthigh ) ;

   h_pt_highest_csv_2b_ptrw -> Sumw2() ;
   h_pt_nexthighest_csv_2b_ptrw -> Sumw2() ;
   h_pt_nextlowest_csv_2b_ptrw -> Sumw2() ;
   h_pt_lowest_csv_2b_ptrw -> Sumw2() ;


   TH1F* h_pt_lowest_csv__passloose = new TH1F("h_pt_lowest_csv__passloose", "jet pt, lowest CSV, pass loose", nbinspt, ptlow, pthigh ) ;
   TH1F* h_pt_lowest_csv__failmed   = new TH1F("h_pt_lowest_csv__failmed", "jet pt, lowest CSV, fail medium", nbinspt, ptlow, pthigh ) ;
   TH1F* h_pt_lowest_csv__passloose_eff = new TH1F("h_pt_lowest_csv__passloose_eff", "jet pt, lowest CSV, pass loose efficiency", nbinspt, ptlow, pthigh ) ;

   TH1F* h_pt_nextlowest_csv__passmed = new TH1F("h_pt_nextlowest_csv__passmed", "jet pt, next lowest CSV, pass medium", nbinspt, ptlow, pthigh ) ;
   TH1F* h_pt_nextlowest_csv__failmed   = new TH1F("h_pt_nextlowest_csv__failmed", "jet pt, next lowest CSV, fail medium", nbinspt, ptlow, pthigh ) ;
   TH1F* h_pt_nextlowest_csv__passmed_eff = new TH1F("h_pt_nextlowest_csv__passmed_eff", "jet pt, next lowest CSV, pass medium efficiency", nbinspt, ptlow, pthigh ) ;
   TH1F* h_pt_nextlowest_csv__failmed_eff   = new TH1F("h_pt_nextlowest_csv__failmed_eff", "jet pt, next lowest CSV, fail medium efficiency", nbinspt, ptlow, pthigh ) ;



   TH1F* h_pt_lowest_csv_cb = new TH1F("h_pt_lowest_csv_cb", "jet pt, lowest CSV", ncbinspt, pt_bins ) ;
   TH1F* h_pt_lowest_csv_cb__passloose = new TH1F("h_pt_lowest_csv_cb__passloose", "jet pt, lowest CSV, pass loose", ncbinspt, pt_bins ) ;
   TH1F* h_pt_lowest_csv_cb__failmed   = new TH1F("h_pt_lowest_csv_cb__failmed", "jet pt, lowest CSV, fail medium", ncbinspt, pt_bins ) ;
   TH1F* h_pt_lowest_csv_cb__passloose_eff = new TH1F("h_pt_lowest_csv_cb__passloose_eff", "jet pt, lowest CSV, pass loose efficiency", ncbinspt, pt_bins ) ;


   TH1F* h_pt_nextlowest_csv_cb = new TH1F("h_pt_nextlowest_csv_cb", "jet pt, next lowest CSV", ncbinspt, pt_bins ) ;
   TH1F* h_pt_nextlowest_csv_cb__passmed = new TH1F("h_pt_nextlowest_csv_cb__passmed", "jet pt, next lowest CSV, pass medium", ncbinspt, pt_bins ) ;
   TH1F* h_pt_nextlowest_csv_cb__failmed   = new TH1F("h_pt_nextlowest_csv_cb__failmed", "jet pt, next lowest CSV, fail medium", ncbinspt, pt_bins ) ;
   TH1F* h_pt_nextlowest_csv_cb__passmed_eff = new TH1F("h_pt_nextlowest_csv_cb__passmed_eff", "jet pt, next lowest CSV, pass medium efficiency", ncbinspt, pt_bins ) ;
   TH1F* h_pt_nextlowest_csv_cb__failmed_eff   = new TH1F("h_pt_nextlowest_csv_cb__failmed_eff", "jet pt, next lowest CSV, fail medium efficiency", ncbinspt, pt_bins ) ;


   int nhsptbins(50) ;
   float hsptlow(0.) ;
   float hspthigh(500.) ;

   TH1F* h_hspt_lower = new TH1F("h_hspt_lower", "sum pt of higgs daughters, lower sum pt higgs", nhsptbins, hsptlow, hspthigh ) ;
   TH1F* h_hspt_higher = new TH1F("h_hspt_higher", "sum pt of higgs daughters, higher sum pt higgs", nhsptbins, hsptlow, hspthigh ) ;

   TH1F* h_hspt_lower_2b = new TH1F("h_hspt_lower_2b", "sum pt of higgs daughters, lower sum pt higgs, 2b", nhsptbins, hsptlow, hspthigh ) ;
   TH1F* h_hspt_higher_2b = new TH1F("h_hspt_higher_2b", "sum pt of higgs daughters, higher sum pt higgs, 2b", nhsptbins, hsptlow, hspthigh ) ;

   TH1F* h_hspt_lower_4b = new TH1F("h_hspt_lower_4b", "sum pt of higgs daughters, lower sum pt higgs, 4b", nhsptbins, hsptlow, hspthigh ) ;
   TH1F* h_hspt_higher_4b = new TH1F("h_hspt_higher_4b", "sum pt of higgs daughters, higher sum pt higgs, 4b", nhsptbins, hsptlow, hspthigh ) ;

   TH1F* h_hspt_lower_2b_ptrw = new TH1F("h_hspt_lower_2b_ptrw", "sum pt of higgs daughters, lower sum pt higgs, 2b, pt reweighted", nhsptbins, hsptlow, hspthigh ) ;
   TH1F* h_hspt_higher_2b_ptrw = new TH1F("h_hspt_higher_2b_ptrw", "sum pt of higgs daughters, higher sum pt higgs, 2b, pt reweighted", nhsptbins, hsptlow, hspthigh ) ;

   h_hspt_lower_2b_ptrw -> Sumw2() ;
   h_hspt_higher_2b_ptrw -> Sumw2() ;






   TH1F* h_maxdr__2b = new TH1F("h_maxdr__2b", "max DR, 2b", 40, 0., 5. ) ;
   TH1F* h_maxdr__4b = new TH1F("h_maxdr__4b", "max DR, 4b", 40, 0., 5. ) ;

   TH1F* h_maxdr_pc__2b = new TH1F("h_maxdr_pc__2b", "max DR, post cut, 2b", 5, 0.2, 2.2 ) ;
   TH1F* h_maxdr_pc__4b = new TH1F("h_maxdr_pc__4b", "max DR, post cut, 4b", 5, 0.2, 2.2 ) ;

   TH1F* h_maxdr_pc__2b_4j = new TH1F("h_maxdr_pc__2b_4j", "max DR, post cut, 2b, 4j", 5, 0.2, 2.2 ) ;
   TH1F* h_maxdr_pc__4b_4j = new TH1F("h_maxdr_pc__4b_4j", "max DR, post cut, 4b, 4j", 5, 0.2, 2.2 ) ;

   TH1F* h_maxdr_pc__2b_5j = new TH1F("h_maxdr_pc__2b_5j", "max DR, post cut, 2b, 5j", 5, 0.2, 2.2 ) ;
   TH1F* h_maxdr_pc__4b_5j = new TH1F("h_maxdr_pc__4b_5j", "max DR, post cut, 4b, 5j", 5, 0.2, 2.2 ) ;

   TH1F* h_maxdr_pc__2b_ptrw = new TH1F("h_maxdr_pc__2b_ptrw", "max DR, post cut, 2b, pt reweighted", 5, 0.2, 2.2 ) ;

   h_maxdr_pc__2b_ptrw -> Sumw2() ;















   int prevpercent(0) ;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {

      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      //-- look for the W.

      int wtype(0) ;
      if ( ::abs(higgs1partonMomId1) == 24 ) { wtype = higgs1partonMomId1 ; }
      if ( ::abs(higgs1partonMomId2) == 24 ) { wtype = higgs1partonMomId2 ; }
      if ( ::abs(higgs2partonMomId1) == 24 ) { wtype = higgs2partonMomId1 ; }
      if ( ::abs(higgs2partonMomId2) == 24 ) { wtype = higgs2partonMomId2 ; }

      //-- assign higgs cand indices for b jets from top decays.
      //
      //     b1 is the b jet from the top that decays semileptonically ( t -> b1 (lnu) )
      //     b2 is the b jet from the top that decays hadronicallj     ( t -> b2 (ja jb) )
      //

      int b1hind(0), b2hind(0) ;

      if ( wtype > 0 ) {

         if ( higgs1partonMomId1 == -6 ) { b1hind = 1 ; }
         if ( higgs1partonMomId2 == -6 ) { b1hind = 1 ; }
         if ( higgs2partonMomId1 == -6 ) { b1hind = 2 ; }
         if ( higgs2partonMomId2 == -6 ) { b1hind = 2 ; }

         if ( higgs1partonMomId1 ==  6 ) { b2hind = 1 ; }
         if ( higgs1partonMomId2 ==  6 ) { b2hind = 1 ; }
         if ( higgs2partonMomId1 ==  6 ) { b2hind = 2 ; }
         if ( higgs2partonMomId2 ==  6 ) { b2hind = 2 ; }

      } else if ( wtype < 0 ) {

         if ( higgs1partonMomId1 ==  6 ) { b1hind = 1 ; }
         if ( higgs1partonMomId2 ==  6 ) { b1hind = 1 ; }
         if ( higgs2partonMomId1 ==  6 ) { b1hind = 2 ; }
         if ( higgs2partonMomId2 ==  6 ) { b1hind = 2 ; }

         if ( higgs1partonMomId1 == -6 ) { b2hind = 1 ; }
         if ( higgs1partonMomId2 == -6 ) { b2hind = 1 ; }
         if ( higgs2partonMomId1 == -6 ) { b2hind = 2 ; }
         if ( higgs2partonMomId2 == -6 ) { b2hind = 2 ; }

      } else {

         //-- don't have W, so b1 and b2 assignment is ambiguous.

         if ( ::abs(higgs1partonMomId1) ==  6 ) { b1hind = 1 ; }
         if ( ::abs(higgs1partonMomId2) ==  6 ) { b1hind = 1 ; }
         if ( ::abs(higgs2partonMomId1) ==  6 ) { b1hind = 2 ; }
         if ( ::abs(higgs2partonMomId2) ==  6 ) { b1hind = 2 ; }

         if ( b1hind > 0 ) {
            if ( ::abs(higgs1partonMomId1) ==  6 && b1hind == 2 ) { b2hind = 1 ; }
            if ( ::abs(higgs1partonMomId2) ==  6 && b1hind == 2 ) { b2hind = 1 ; }
            if ( ::abs(higgs2partonMomId1) ==  6 && b1hind == 1 ) { b2hind = 2 ; }
            if ( ::abs(higgs2partonMomId2) ==  6 && b1hind == 1 ) { b2hind = 2 ; }
         }


      }



      //-- assign hadronic W jet higgs cand indices.
      //
      //   ja is the down-type quark (1 or 3 or 5)
      //   jb is the up-type quark   (2 or 4)
      //

      int jahind(0), jbhind(0) ;
      int jaflav(-99), jbflav(-99) ;
      float japt(0.), jbpt(0.) ;
      float jacsv(-1.), jbcsv(-1.) ;

      if ( ::abs(higgs1partonMomId1) == 24 && ( ::abs(higgs1partonId1)==5 || ::abs(higgs1partonId1)==3 || ::abs(higgs1partonId1)==1 ) ) { jahind = 1 ; jaflav = ::abs(higgs1partonId1) ; japt = higgs1jetpt1 ; jacsv = higgs1CSV1 ; }
      if ( ::abs(higgs1partonMomId2) == 24 && ( ::abs(higgs1partonId2)==5 || ::abs(higgs1partonId2)==3 || ::abs(higgs1partonId2)==1 ) ) { jahind = 1 ; jaflav = ::abs(higgs1partonId2) ; japt = higgs1jetpt2 ; jacsv = higgs1CSV2 ; }
      if ( ::abs(higgs2partonMomId1) == 24 && ( ::abs(higgs2partonId1)==5 || ::abs(higgs2partonId1)==3 || ::abs(higgs2partonId1)==1 ) ) { jahind = 2 ; jaflav = ::abs(higgs2partonId1) ; japt = higgs2jetpt1 ; jacsv = higgs2CSV1 ; }
      if ( ::abs(higgs2partonMomId2) == 24 && ( ::abs(higgs2partonId2)==5 || ::abs(higgs2partonId2)==3 || ::abs(higgs2partonId2)==1 ) ) { jahind = 2 ; jaflav = ::abs(higgs2partonId2) ; japt = higgs2jetpt2 ; jacsv = higgs2CSV2 ; }

      if ( ::abs(higgs1partonMomId1) == 24 && ( ::abs(higgs1partonId1)==4 || ::abs(higgs1partonId1)==2 ) ) { jbhind = 1 ; jbflav = ::abs(higgs1partonId1) ; jbpt = higgs1jetpt1 ; jbcsv = higgs1CSV1 ; }
      if ( ::abs(higgs1partonMomId2) == 24 && ( ::abs(higgs1partonId2)==4 || ::abs(higgs1partonId2)==2 ) ) { jbhind = 1 ; jbflav = ::abs(higgs1partonId2) ; jbpt = higgs1jetpt2 ; jbcsv = higgs1CSV2 ; }
      if ( ::abs(higgs2partonMomId1) == 24 && ( ::abs(higgs2partonId1)==4 || ::abs(higgs2partonId1)==2 ) ) { jbhind = 2 ; jbflav = ::abs(higgs2partonId1) ; jbpt = higgs2jetpt1 ; jbcsv = higgs2CSV1 ; }
      if ( ::abs(higgs2partonMomId2) == 24 && ( ::abs(higgs2partonId2)==4 || ::abs(higgs2partonId2)==2 ) ) { jbhind = 2 ; jbflav = ::abs(higgs2partonId2) ; jbpt = higgs2jetpt2 ; jbcsv = higgs2CSV2 ; }

      float xjetpt(0.) ;
      int xjetflav(-99) ;
      int xjetparentflav(-99) ;
      float xjetcsv(-1.) ;

      if ( ::abs(higgs1partonMomId1) != 24 && ::abs(higgs1partonMomId1) != 6 ) { xjetflav = ::abs(higgs1partonId1) ; xjetparentflav = ::abs(higgs1partonMomId1) ; xjetpt = higgs1jetpt1 ; xjetcsv = higgs1CSV1 ; }
      if ( ::abs(higgs1partonMomId2) != 24 && ::abs(higgs1partonMomId2) != 6 ) { xjetflav = ::abs(higgs1partonId2) ; xjetparentflav = ::abs(higgs1partonMomId2) ; xjetpt = higgs1jetpt2 ; xjetcsv = higgs1CSV2 ; }
      if ( ::abs(higgs2partonMomId1) != 24 && ::abs(higgs2partonMomId1) != 6 ) { xjetflav = ::abs(higgs2partonId1) ; xjetparentflav = ::abs(higgs2partonMomId1) ; xjetpt = higgs2jetpt1 ; xjetcsv = higgs2CSV1 ; }
      if ( ::abs(higgs2partonMomId2) != 24 && ::abs(higgs2partonMomId2) != 6 ) { xjetflav = ::abs(higgs2partonId2) ; xjetparentflav = ::abs(higgs2partonMomId2) ; xjetpt = higgs2jetpt2 ; xjetcsv = higgs2CSV2 ; }





      //-- find the lowest and 2nd lowest CSV jets
      float lowestcsv(9.) ;
      int   lowestcsvsource(0) ;
      float lowestcsvpt(0.) ;

      if ( higgs1CSV1 < lowestcsv ) {
         lowestcsv = higgs1CSV1 ;
         lowestcsvpt = higgs1jetpt1 ;
         if ( ::abs(higgs1partonMomId1) == 6 ) {
            lowestcsvsource = 3 ;
         } else if ( ::abs(higgs1partonMomId1) == 24 ) {
            lowestcsvsource = 2 ;
         } else {
            lowestcsvsource = 1 ;
         }
      }
      if ( higgs1CSV2 < lowestcsv ) {
         lowestcsv = higgs1CSV2 ;
         lowestcsvpt = higgs1jetpt2 ;
         if ( ::abs(higgs1partonMomId2) == 6 ) {
            lowestcsvsource = 3 ;
         } else if ( ::abs(higgs1partonMomId2) == 24 ) {
            lowestcsvsource = 2 ;
         } else {
            lowestcsvsource = 1 ;
         }
      }
      if ( higgs2CSV1 < lowestcsv ) {
         lowestcsv = higgs2CSV1 ;
         lowestcsvpt = higgs2jetpt1 ;
         if ( ::abs(higgs2partonMomId1) == 6 ) {
            lowestcsvsource = 3 ;
         } else if ( ::abs(higgs2partonMomId1) == 24 ) {
            lowestcsvsource = 2 ;
         } else {
            lowestcsvsource = 1 ;
         }
      }
      if ( higgs2CSV2 < lowestcsv ) {
         lowestcsv = higgs2CSV2 ;
         lowestcsvpt = higgs2jetpt2 ;
         if ( ::abs(higgs2partonMomId2) == 6 ) {
            lowestcsvsource = 3 ;
         } else if ( ::abs(higgs2partonMomId2) == 24 ) {
            lowestcsvsource = 2 ;
         } else {
            lowestcsvsource = 1 ;
         }
      }

      float nextlowestcsv(9.) ;
      float nextlowestcsvpt(0.) ;

      if ( higgs1CSV1 <= nextlowestcsv && higgs1CSV1 > lowestcsv ) {
         nextlowestcsv = higgs1CSV1 ;
         nextlowestcsvpt = higgs1jetpt1 ;
      }
      if ( higgs1CSV2 <= nextlowestcsv && higgs1CSV2 > lowestcsv ) {
         nextlowestcsv = higgs1CSV2 ;
         nextlowestcsvpt = higgs1jetpt2 ;
      }
      if ( higgs2CSV1 <= nextlowestcsv && higgs2CSV1 > lowestcsv ) {
         nextlowestcsv = higgs2CSV1 ;
         nextlowestcsvpt = higgs2jetpt1 ;
      }
      if ( higgs2CSV2 <= nextlowestcsv && higgs2CSV2 > lowestcsv ) {
         nextlowestcsv = higgs2CSV2 ;
         nextlowestcsvpt = higgs2jetpt2 ;
      }


      float highestcsv(0.) ;
      float highestcsvpt(0.) ;
      if ( higgs1CSV1 > highestcsv ) {
         highestcsv = higgs1CSV1 ;
         highestcsvpt = higgs1jetpt1 ;
      }
      if ( higgs1CSV2 > highestcsv ) {
         highestcsv = higgs1CSV2 ;
         highestcsvpt = higgs1jetpt2 ;
      }
      if ( higgs2CSV1 > highestcsv ) {
         highestcsv = higgs2CSV1 ;
         highestcsvpt = higgs2jetpt1 ;
      }
      if ( higgs2CSV2 > highestcsv ) {
         highestcsv = higgs2CSV2 ;
         highestcsvpt = higgs2jetpt2 ;
      }

      float nexthighestcsv(0.) ;
      float nexthighestcsvpt(0.) ;
      if ( higgs1CSV1 <= highestcsv && higgs1CSV1 > nextlowestcsv ) {
         nexthighestcsv = higgs1CSV1 ;
         nexthighestcsvpt = higgs1jetpt1 ;
      }
      if ( higgs1CSV2 <= highestcsv && higgs1CSV2 > nextlowestcsv ) {
         nexthighestcsv = higgs1CSV2 ;
         nexthighestcsvpt = higgs1jetpt2 ;
      }
      if ( higgs2CSV1 <= highestcsv && higgs2CSV1 > nextlowestcsv ) {
         nexthighestcsv = higgs2CSV1 ;
         nexthighestcsvpt = higgs2jetpt1 ;
      }
      if ( higgs2CSV2 <= highestcsv && higgs2CSV2 > nextlowestcsv ) {
         nexthighestcsv = higgs2CSV2 ;
         nexthighestcsvpt = higgs2jetpt2 ;
      }


      //-- Assign an event configuration code.

      int evtcode(0) ;

      if ( b1hind==b2hind && b1hind>0 ) {
         if ( jahind==jbhind && jahind>0 ) {
            evtcode = 2 ; // (b1 b2) (ja jb)
         } else if ( jahind+jbhind > 0 ) {
            evtcode = 5 ; // (b1 b2) (j x)
         } else {
            evtcode = 7 ; // (b1 b2) (x x)
         }
      } // both top bs in same higgs cand.

      if ( evtcode==0 ) {
         if ( jahind==jbhind && jahind>0 ) {
            if ( b1hind>0 ) { evtcode = 12 ; } // (b1 x) (j j)
            if ( b2hind>0 ) { evtcode = 13 ; } // (b2 x) (j j)
         } // both W jets in same higgs cand.
      }

      if ( evtcode==0 ) {
         if ( b1hind==jahind && b1hind>0 ) {
            if ( b2hind==jbhind && b2hind>0 ) { evtcode = 1 ; } // (b1 j) (b2 j)
            if ( b2hind>0 && jbhind==0 ) { evtcode = 4 ; } // (b1 j) (b2 x)
            if ( b2hind==0 && jbhind>0 ) { evtcode = 16 ; } // (b1 j) (x j)
            if ( b2hind==0 && jbhind==0 ) { evtcode = 14 ; } // (b1 j) (x x)
         } // b1 and ja in same higgs cand.
         if ( b1hind==jbhind && b1hind>0 ) {
            if ( b2hind==jahind && b2hind>0 ) { evtcode = 1 ; } // (b1 j) (b2 j)
            if ( b2hind>0 && jahind==0 ) { evtcode = 4 ; } // (b1 j) (b2 x)
            if ( b2hind==0 && jahind>0 ) { evtcode = 16 ; } // (b1 j) (x j)
            if ( b2hind==0 && jahind==0 ) { evtcode = 14 ; } // (b1 j) (x x)
         } // b1 and jb in same higgs cand.
      }

      if ( evtcode==0 ) {
         if ( b2hind==jahind && b2hind>0 ) {
            if ( b1hind>0 && jbhind==0 ) { evtcode = 3 ; } // (b2 j) (b1 x)
            if ( b1hind==0 && jbhind>0 ) { evtcode = 9 ; } // (b2 j) (x j)
            if ( b1hind==0 && jbhind==0 ) { evtcode = 15 ; } // (b2 j) (x x)
         } // b2 and ja in same higgs cand.
         if ( b2hind==jbhind && b2hind>0 ) {
            if ( b1hind>0 && jahind==0 ) { evtcode = 3 ; } // (b2 j) (b1 x)
            if ( b1hind==0 && jahind>0 ) { evtcode = 9 ; } // (b2 j) (x j)
            if ( b1hind==0 && jahind==0 ) { evtcode = 15 ; } // (b2 j) (x x)
         } // b2 and jb in same higgs cand.
      }

      if ( evtcode==0 ) {
         if ( jahind==jbhind && jahind>0 && b1hind==0 && b2hind==0 ) { evtcode = 10 ; } // (x x) (j j)
      }

      if ( evtcode==0 ) {
         if ( b1hind>0 && b2hind==0 && jahind>0 && jbhind==0 && b1hind!=jahind ) { evtcode = 11 ; } // (b1 x) (j x)
         if ( b1hind>0 && b2hind==0 && jbhind>0 && jahind==0 && b1hind!=jbhind ) { evtcode = 11 ; } // (b1 x) (j x)
         if ( b2hind>0 && b1hind==0 && jahind>0 && jbhind==0 && b2hind!=jahind ) { evtcode = 8 ; } // (b2 x) (j x)
         if ( b2hind>0 && b1hind==0 && jbhind>0 && jahind==0 && b2hind!=jbhind ) { evtcode = 8 ; } // (b2 x) (j x)
      }

      if ( evtcode==0 ) {
         if ( b1hind>0 && b2hind>0 && jahind==0 && jbhind==0 && b1hind!=b2hind ) { evtcode = 6 ; } // (b1 x) (b2 x)
      }

      h_evtcode_nocuts -> Fill( evtcode ) ;

      bool pass2b(false) ;
      if ( CSVbest2>0.898&&CSVbest3<0.679 ) { pass2b = true ;  }

      bool pass3b(false) ;
      if ( CSVbest2>0.898&&CSVbest3>0.679&&CSVbest4<0.244  ) { pass3b = true ; }

      bool pass4b(false) ;
      if ( CSVbest2>0.898&&CSVbest3>0.679&&CSVbest4>0.244  ) { pass4b = true ; }

      bool ismsig(false) ;
      if ( ::abs(higgsMbb1MassDiff-higgsMbb2MassDiff) < 20 && ((0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff)>100)&&(0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff)<140)) ) { ismsig = true ; }

      bool ismsb(false) ;
      if ( !( ::abs(higgsMbb1MassDiff-higgsMbb2MassDiff) < 30 && ((0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff)>90)&&(0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff)<150)) ) ) { ismsb = true ; }

      int lcsvptbin = getptbin( lowestcsvpt ) ;
      int nlcsvptbin = getptbin( nextlowestcsvpt ) ;
      if ( lcsvptbin > ncbinspt ) { printf("\n\n\n *** error in finding pt bin for lcsv: pt=%f, bin=%d\n", lowestcsvpt, lcsvptbin ) ; return ; }
      if ( nlcsvptbin > ncbinspt ) { printf("\n\n\n *** error in finding pt bin for nlcsv: pt=%f, bin=%d\n", nextlowestcsvpt, nlcsvptbin ) ; return ; }
      float lcsvleff = eff_lcsv_loose[lcsvptbin-1] ;
      float nlcsvmeff = eff_nlcsv_med[nlcsvptbin-1] ;
      float ptw2b = lcsvleff * nlcsvmeff ;


      float sumpt = higgs1jetpt1 + higgs1jetpt2 + higgs2jetpt1 + higgs2jetpt2 ;
      int sumptbin = getsumptbin( sumpt ) ;
      if ( sumptbin > nbinssumpt ) { printf("\n\n *** error in finding sum pt bin : pt=%f, bin=%d\n\n", sumpt, sumptbin ) ; return ; }
      float sptw2b = weight_sumpt[sumptbin-1] ;


      float mh_sptl(0.), mh_spth(0.) ;
      float hspt_lower(0.), hspt_higher(0.) ;
      if ( (higgs1jetpt1+higgs1jetpt2) > (higgs2jetpt1+higgs2jetpt2) ) {
         mh_spth = higgsMbb1MassDiff ;
         mh_sptl = higgsMbb2MassDiff ;
         hspt_higher = higgs1jetpt1+higgs1jetpt2 ;
         hspt_lower  = higgs2jetpt1+higgs2jetpt2 ;
      } else {
         mh_spth = higgsMbb2MassDiff ;
         mh_sptl = higgsMbb1MassDiff ;
         hspt_higher = higgs2jetpt1+higgs2jetpt2 ;
         hspt_lower  = higgs1jetpt1+higgs1jetpt2 ;
      }




      if ( (100*jentry)/nentries != prevpercent ) {
         prevpercent = (100*jentry)/nentries ;
         printf("   %2d %% (%llu/%llu)\n", prevpercent, jentry, nentries ) ;
         printf("   b1hind=%d, b2hind=%d, jahind=%d, jbhind=%d ;  evtcode=%d\n\n", b1hind, b2hind, jahind, jbhind, evtcode ) ;
      }


      //--- njets requirement.
      if ( njets20<4 || njets20>5 ) continue ;

      //--- lepton veto
      if ( ! (nMuons==0&&nElectrons==0&&nIsoTracks15_005_03==0&&nIsoTracks5_005_03<2&&nTausLoose==0 ) ) continue ;

      //--- two tight b tags
      if ( ! (CSVbest2>0.898) ) continue ;

      if ( pass2b ) { h_maxdr__2b -> Fill( deltaRmax_hh ) ; }
      if ( pass4b ) { h_maxdr__4b -> Fill( deltaRmax_hh ) ; }

      //--- max Dr cut
      if ( ! (deltaRmax_hh<2.2) ) continue ;

      //--- minDeltaPhi30 cut
      if ( minDeltaPhi30 < 0.3 ) continue ;



      if ( pass2b ) { h_maxdr_pc__2b -> Fill( deltaRmax_hh ) ; }
      if ( pass4b ) { h_maxdr_pc__4b -> Fill( deltaRmax_hh ) ; }
      if ( njets20 == 4 && pass2b ) { h_maxdr_pc__2b_4j -> Fill( deltaRmax_hh ) ; }
      if ( njets20 == 4 && pass4b ) { h_maxdr_pc__4b_4j -> Fill( deltaRmax_hh ) ; }
      if ( njets20 == 5 && pass2b ) { h_maxdr_pc__2b_5j -> Fill( deltaRmax_hh ) ; }
      if ( njets20 == 5 && pass4b ) { h_maxdr_pc__4b_5j -> Fill( deltaRmax_hh ) ; }
      if ( pass2b ) { h_maxdr_pc__2b_ptrw -> Fill( deltaRmax_hh, ptw2b ) ; }


      float metsig_var = METsig_2012 ;
      ///float metsig_var = METsig ;

      h_hspt_lower  -> Fill( hspt_lower ) ;
      h_hspt_higher -> Fill( hspt_higher ) ;
      if ( pass2b ) {
         h_hspt_lower_2b  -> Fill( hspt_lower ) ;
         h_hspt_higher_2b -> Fill( hspt_higher ) ;
         h_hspt_lower_2b_ptrw  -> Fill( hspt_lower, ptw2b ) ;
         h_hspt_higher_2b_ptrw -> Fill( hspt_higher, ptw2b ) ;
      }
      if ( pass4b ) {
         h_hspt_lower_4b  -> Fill( hspt_lower ) ;
         h_hspt_higher_4b -> Fill( hspt_higher ) ;
      }


      if ( pass2b && ismsig ) { h_metsig_msig_2b -> Fill( metsig_var ) ; }
      if ( pass3b && ismsig ) { h_metsig_msig_3b -> Fill( metsig_var ) ; }
      if ( pass4b && ismsig ) { h_metsig_msig_4b -> Fill( metsig_var ) ; }
      if ( pass2b && ismsb  ) { h_metsig_msb_2b  -> Fill( metsig_var ) ; }
      if ( pass3b && ismsb  ) { h_metsig_msb_3b  -> Fill( metsig_var ) ; }
      if ( pass4b && ismsb  ) { h_metsig_msb_4b  -> Fill( metsig_var ) ; }

      if ( pass2b && ismsig ) { h_metsig_msig_2b_ptrw -> Fill( metsig_var, ptw2b ) ; }
      if ( pass2b && ismsb  ) { h_metsig_msb_2b_ptrw  -> Fill( metsig_var, ptw2b ) ; }

      if ( pass2b && ismsig ) { h_metsig_msig_2b_sptrw -> Fill( metsig_var, sptw2b ) ; }
      if ( pass2b && ismsb  ) { h_metsig_msb_2b_sptrw  -> Fill( metsig_var, sptw2b ) ; }


      if ( njets20 == 4 ) {
         if ( pass2b && ismsig ) { h_metsig_msig_2b_4j -> Fill( metsig_var ) ; }
         if ( pass3b && ismsig ) { h_metsig_msig_3b_4j -> Fill( metsig_var ) ; }
         if ( pass4b && ismsig ) { h_metsig_msig_4b_4j -> Fill( metsig_var ) ; }
         if ( pass2b && ismsb  ) { h_metsig_msb_2b_4j  -> Fill( metsig_var ) ; }
         if ( pass3b && ismsb  ) { h_metsig_msb_3b_4j  -> Fill( metsig_var ) ; }
         if ( pass4b && ismsb  ) { h_metsig_msb_4b_4j  -> Fill( metsig_var ) ; }
         if ( pass2b && ismsig ) { h_metsig_msig_2b_4j_ptrw -> Fill( metsig_var, ptw2b ) ; }
         if ( pass2b && ismsb  ) { h_metsig_msb_2b_4j_ptrw  -> Fill( metsig_var, ptw2b ) ; }
      }
      if ( njets20 == 5 ) {
         if ( pass2b && ismsig ) { h_metsig_msig_2b_5j -> Fill( metsig_var ) ; }
         if ( pass3b && ismsig ) { h_metsig_msig_3b_5j -> Fill( metsig_var ) ; }
         if ( pass4b && ismsig ) { h_metsig_msig_4b_5j -> Fill( metsig_var ) ; }
         if ( pass2b && ismsb  ) { h_metsig_msb_2b_5j  -> Fill( metsig_var ) ; }
         if ( pass3b && ismsb  ) { h_metsig_msb_3b_5j  -> Fill( metsig_var ) ; }
         if ( pass4b && ismsb  ) { h_metsig_msb_4b_5j  -> Fill( metsig_var ) ; }
         if ( pass2b && ismsig ) { h_metsig_msig_2b_5j_ptrw -> Fill( metsig_var, ptw2b ) ; }
         if ( pass2b && ismsb  ) { h_metsig_msb_2b_5j_ptrw  -> Fill( metsig_var, ptw2b ) ; }
      }

      if ( minDeltaPhi30>0.3 ) {
         if ( pass2b && ismsig ) { h_metsig_msig_2b_mdpc -> Fill( metsig_var ) ; }
         if ( pass3b && ismsig ) { h_metsig_msig_3b_mdpc -> Fill( metsig_var ) ; }
         if ( pass4b && ismsig ) { h_metsig_msig_4b_mdpc -> Fill( metsig_var ) ; }
         if ( pass2b && ismsb  ) { h_metsig_msb_2b_mdpc  -> Fill( metsig_var ) ; }
         if ( pass3b && ismsb  ) { h_metsig_msb_3b_mdpc  -> Fill( metsig_var ) ; }
         if ( pass4b && ismsb  ) { h_metsig_msb_4b_mdpc  -> Fill( metsig_var ) ; }
      }



      //--- metsig_var
      if ( ! (metsig_var>25) ) continue ;



      h_pt_highest_csv -> Fill( highestcsvpt ) ;
      h_pt_nexthighest_csv -> Fill( nexthighestcsvpt ) ;
      h_pt_nextlowest_csv -> Fill( nextlowestcsvpt ) ;
      h_pt_lowest_csv -> Fill( lowestcsvpt ) ;

      if ( pass2b ) {
         h_pt_highest_csv_2b -> Fill( highestcsvpt ) ;
         h_pt_nexthighest_csv_2b -> Fill( nexthighestcsvpt ) ;
         h_pt_nextlowest_csv_2b -> Fill( nextlowestcsvpt ) ;
         h_pt_lowest_csv_2b -> Fill( lowestcsvpt ) ;

         h_pt_highest_csv_2b_ptrw -> Fill( highestcsvpt, ptw2b ) ;
         h_pt_nexthighest_csv_2b_ptrw -> Fill( nexthighestcsvpt, ptw2b ) ;
         h_pt_nextlowest_csv_2b_ptrw -> Fill( nextlowestcsvpt, ptw2b ) ;
         h_pt_lowest_csv_2b_ptrw -> Fill( lowestcsvpt, ptw2b ) ;
      }

      if ( pass3b ) {
         h_pt_highest_csv_3b -> Fill( highestcsvpt ) ;
         h_pt_nexthighest_csv_3b -> Fill( nexthighestcsvpt ) ;
         h_pt_nextlowest_csv_3b -> Fill( nextlowestcsvpt ) ;
         h_pt_lowest_csv_3b -> Fill( lowestcsvpt ) ;
      }

      if ( pass4b ) {
         h_pt_highest_csv_4b -> Fill( highestcsvpt ) ;
         h_pt_nexthighest_csv_4b -> Fill( nexthighestcsvpt ) ;
         h_pt_nextlowest_csv_4b -> Fill( nextlowestcsvpt ) ;
         h_pt_lowest_csv_4b -> Fill( lowestcsvpt ) ;
      }

      if ( lowestcsv > 0.244 ) h_pt_lowest_csv__passloose -> Fill( lowestcsvpt ) ;
      if ( lowestcsv < 0.679  ) h_pt_lowest_csv__failmed   -> Fill( lowestcsvpt ) ;

      if ( nextlowestcsv > 0.679 ) h_pt_nextlowest_csv__passmed -> Fill( nextlowestcsvpt ) ;
      if ( nextlowestcsv < 0.679 ) h_pt_nextlowest_csv__failmed -> Fill( nextlowestcsvpt ) ;



      h_pt_lowest_csv_cb -> Fill( lowestcsvpt ) ;
      if ( lowestcsv > 0.244 ) h_pt_lowest_csv_cb__passloose -> Fill( lowestcsvpt ) ;
      if ( lowestcsv < 0.679  ) h_pt_lowest_csv_cb__failmed   -> Fill( lowestcsvpt ) ;

      h_pt_nextlowest_csv_cb -> Fill( nextlowestcsvpt ) ;
      if ( nextlowestcsv > 0.679 ) h_pt_nextlowest_csv_cb__passmed -> Fill( nextlowestcsvpt ) ;
      if ( nextlowestcsv < 0.679 ) h_pt_nextlowest_csv_cb__failmed -> Fill( nextlowestcsvpt ) ;







      h_sumpt -> Fill( sumpt ) ;
      if ( pass2b ) h_sumpt__2b -> Fill( sumpt ) ;
      if ( pass4b ) h_sumpt__4b -> Fill( sumpt ) ;
      if ( njets20 == 4 && pass2b ) h_sumpt__2b_4j -> Fill( sumpt ) ;
      if ( njets20 == 4 && pass4b ) h_sumpt__4b_4j -> Fill( sumpt ) ;
      if ( njets20 == 5 && pass2b ) h_sumpt__2b_5j -> Fill( sumpt ) ;
      if ( njets20 == 5 && pass4b ) h_sumpt__4b_5j -> Fill( sumpt ) ;
      if ( metsig_var > 40 ) {
         if ( pass2b ) h_sumpt__2b_ms40 -> Fill( sumpt ) ;
         if ( pass4b ) h_sumpt__4b_ms40 -> Fill( sumpt ) ;
      }
      if ( metsig_var > 85 ) {
         if ( pass2b ) h_sumpt__2b_ms85 -> Fill( sumpt ) ;
         if ( pass4b ) h_sumpt__4b_ms85 -> Fill( sumpt ) ;
      }



      if ( pass2b ) { h_njets_2b -> Fill( njets20 ) ; }
      if ( pass3b ) { h_njets_3b -> Fill( njets20 ) ; }
      if ( pass4b ) { h_njets_4b -> Fill( njets20 ) ; }
      if ( metsig_var > 40 ) {
         if ( pass2b ) { h_njets_2b_ms40 -> Fill( njets20 ) ; }
         if ( pass3b ) { h_njets_3b_ms40 -> Fill( njets20 ) ; }
         if ( pass4b ) { h_njets_4b_ms40 -> Fill( njets20 ) ; }
      }
      if ( metsig_var > 85 ) {
         if ( pass2b ) { h_njets_2b_ms85 -> Fill( njets20 ) ; }
         if ( pass3b ) { h_njets_3b_ms85 -> Fill( njets20 ) ; }
         if ( pass4b ) { h_njets_4b_ms85 -> Fill( njets20 ) ; }
      }


      if ( ::abs(higgs1partonMomId1)==6 && ::abs(higgs1partonId1)==5 ) { h_bjet_csv -> Fill( higgs1CSV1 ) ; h_bjet_pt -> Fill( higgs1jetpt1 ) ; }
      if ( ::abs(higgs1partonMomId2)==6 && ::abs(higgs1partonId2)==5 ) { h_bjet_csv -> Fill( higgs1CSV2 ) ; h_bjet_pt -> Fill( higgs1jetpt2 ) ; }
      if ( ::abs(higgs2partonMomId1)==6 && ::abs(higgs2partonId1)==5 ) { h_bjet_csv -> Fill( higgs2CSV1 ) ; h_bjet_pt -> Fill( higgs2jetpt1 ) ; }
      if ( ::abs(higgs2partonMomId2)==6 && ::abs(higgs2partonId2)==5 ) { h_bjet_csv -> Fill( higgs2CSV2 ) ; h_bjet_pt -> Fill( higgs2jetpt2 ) ; }


      h_evtcode_baselinecuts -> Fill( evtcode ) ;

      if ( jahind == jbhind && jahind > 0 ) {
         h_jj_flavor -> Fill( jaflav ) ;
         h_jj_flavor -> Fill( jbflav ) ;
         if ( pass2b ) {
            h_jj_flavor_2b -> Fill( jaflav ) ;
            h_jj_flavor_2b -> Fill( jbflav ) ;
         }
         if ( pass4b ) {
            h_jj_flavor_4b -> Fill( jaflav ) ;
            h_jj_flavor_4b -> Fill( jbflav ) ;
         }
      }

      if ( evtcode==3 || evtcode==4 || evtcode==5 ) {
         h_xjet_flavor -> Fill( xjetflav ) ;
         if ( pass2b ) { h_xjet_flavor_2b -> Fill( xjetflav ) ; }
         if ( pass4b ) { h_xjet_flavor_4b -> Fill( xjetflav ) ; }
         h_xjet_parent_flavor -> Fill( xjetparentflav ) ;
         h_xjet_flav_vs_parent -> Fill( xjetparentflav, xjetflav ) ;
         h_xjet_pt -> Fill( xjetpt ) ;
         if ( pass2b ) { h_xjet_pt_2b -> Fill( xjetpt ) ; }
         if ( pass4b ) { h_xjet_pt_4b -> Fill( xjetpt ) ; }
         if ( xjetflav == 21 ) { h_xjet_pt_gluon -> Fill( xjetpt ) ; h_xjet_csv_gluon -> Fill( xjetcsv ) ; }
         if ( xjetflav == 0  ) { h_xjet_pt_nomatch -> Fill( xjetpt ) ;  h_xjet_csv_nomatch -> Fill( xjetcsv ) ;}
         if ( xjetflav != 21 && xjetflav != 0 ) { h_xjet_pt_quark -> Fill( xjetpt ) ;  h_xjet_csv_quark -> Fill( xjetcsv ) ;}
         if ( japt>0 ) { h_jx_wjet_pt -> Fill( japt ) ; }
         if ( jbpt>0 ) { h_jx_wjet_pt -> Fill( jbpt ) ; }
         if ( jaflav > 0 ) { h_jx_wjet_flavor -> Fill( abs(jaflav) ) ; }
         if ( jbflav > 0 ) { h_jx_wjet_flavor -> Fill( abs(jbflav) ) ; }
         if ( jaflav > 0 && pass2b ) { h_jx_wjet_flavor_2b -> Fill( jaflav ) ; }
         if ( jbflav > 0 && pass2b ) { h_jx_wjet_flavor_2b -> Fill( jbflav ) ; }
         if ( jaflav > 0 && pass4b ) { h_jx_wjet_flavor_4b -> Fill( jaflav ) ; }
         if ( jbflav > 0 && pass4b ) { h_jx_wjet_flavor_4b -> Fill( jbflav ) ; }
      }
      if ( evtcode==1 || evtcode==2 ) {
         h_jj_wjet_pt -> Fill( japt ) ;
         h_jj_wjet_pt -> Fill( jbpt ) ;
         if ( jaflav < jbflav ) {
            h_jj_lfj_csv -> Fill( jacsv ) ;
            h_jj_lfj_pt  -> Fill( japt  ) ;
         } else {
            h_jj_lfj_csv -> Fill( jbcsv ) ;
            h_jj_lfj_pt  -> Fill( jbpt  ) ;
         }
         if ( jaflav == 4 ) {
            h_jj_charm_csv -> Fill( jacsv ) ;
            h_jj_charm_pt  -> Fill( japt  ) ;
         }
         if ( jbflav == 4 ) {
            h_jj_charm_csv -> Fill( jbcsv ) ;
            h_jj_charm_pt  -> Fill( jbpt  ) ;
         }
      }

      h_lowestcsv_csv -> Fill( lowestcsv ) ;
      h_lowestcsv_source -> Fill( lowestcsvsource ) ;
      h_lowestcsv_pt -> Fill( lowestcsvpt ) ;

      if ( pass4b ) {
         h_lowestcsv_csv_4b -> Fill( lowestcsv ) ;
         h_lowestcsv_source_4b -> Fill( lowestcsvsource ) ;
         h_lowestcsv_pt_4b -> Fill( lowestcsvpt ) ;
      }



      if ( pass2b ) h_evtcode_2b -> Fill( evtcode ) ;
      if ( pass4b ) h_evtcode_4b -> Fill( evtcode ) ;

      if ( njets20 == 4 ) {

         if ( pass2b ) h_evtcode_2b_4j -> Fill( evtcode ) ;
         if ( pass4b ) h_evtcode_4b_4j -> Fill( evtcode ) ;

         if ( pass2b && ismsig ) h_evtcode_msig_2b_4j -> Fill( evtcode ) ;
         if ( pass4b && ismsig ) h_evtcode_msig_4b_4j -> Fill( evtcode ) ;

         if ( pass2b && ismsb ) h_evtcode_msb_2b_4j -> Fill( evtcode ) ;
         if ( pass4b && ismsb ) h_evtcode_msb_4b_4j -> Fill( evtcode ) ;

         if ( metsig_var>40 ) {
            if ( pass2b ) h_evtcode_2b_4j_ms40 -> Fill( evtcode ) ;
            if ( pass4b ) h_evtcode_4b_4j_ms40 -> Fill( evtcode ) ;
            if ( pass2b && ismsig ) h_evtcode_msig_2b_4j_ms40 -> Fill( evtcode ) ;
            if ( pass4b && ismsig ) h_evtcode_msig_4b_4j_ms40 -> Fill( evtcode ) ;
            if ( pass2b && ismsb )  h_evtcode_msb_2b_4j_ms40 -> Fill( evtcode ) ;
            if ( pass4b && ismsb )  h_evtcode_msb_4b_4j_ms40 -> Fill( evtcode ) ;
         }
         if ( metsig_var>85 ) {
            if ( pass2b ) h_evtcode_2b_4j_ms85 -> Fill( evtcode ) ;
            if ( pass4b ) h_evtcode_4b_4j_ms85 -> Fill( evtcode ) ;
            if ( pass2b && ismsig ) h_evtcode_msig_2b_4j_ms85 -> Fill( evtcode ) ;
            if ( pass4b && ismsig ) h_evtcode_msig_4b_4j_ms85 -> Fill( evtcode ) ;
            if ( pass2b && ismsb )  h_evtcode_msb_2b_4j_ms85 -> Fill( evtcode ) ;
            if ( pass4b && ismsb )  h_evtcode_msb_4b_4j_ms85 -> Fill( evtcode ) ;
         }

      }
      if ( njets20 == 5 ) {

         if ( pass2b ) h_evtcode_2b_5j -> Fill( evtcode ) ;
         if ( pass4b ) h_evtcode_4b_5j -> Fill( evtcode ) ;

         if ( pass2b && ismsig ) h_evtcode_msig_2b_5j -> Fill( evtcode ) ;
         if ( pass4b && ismsig ) h_evtcode_msig_4b_5j -> Fill( evtcode ) ;

         if ( pass2b && ismsb ) h_evtcode_msb_2b_5j -> Fill( evtcode ) ;
         if ( pass4b && ismsb ) h_evtcode_msb_4b_5j -> Fill( evtcode ) ;

         if ( metsig_var>40 ) {
            if ( pass2b ) h_evtcode_2b_5j_ms40 -> Fill( evtcode ) ;
            if ( pass4b ) h_evtcode_4b_5j_ms40 -> Fill( evtcode ) ;
            if ( pass2b && ismsig ) h_evtcode_msig_2b_5j_ms40 -> Fill( evtcode ) ;
            if ( pass4b && ismsig ) h_evtcode_msig_4b_5j_ms40 -> Fill( evtcode ) ;
            if ( pass2b && ismsb )  h_evtcode_msb_2b_5j_ms40 -> Fill( evtcode ) ;
            if ( pass4b && ismsb )  h_evtcode_msb_4b_5j_ms40 -> Fill( evtcode ) ;
         }
         if ( metsig_var>85 ) {
            if ( pass2b ) h_evtcode_2b_5j_ms85 -> Fill( evtcode ) ;
            if ( pass4b ) h_evtcode_4b_5j_ms85 -> Fill( evtcode ) ;
            if ( pass2b && ismsig ) h_evtcode_msig_2b_5j_ms85 -> Fill( evtcode ) ;
            if ( pass4b && ismsig ) h_evtcode_msig_4b_5j_ms85 -> Fill( evtcode ) ;
            if ( pass2b && ismsb )  h_evtcode_msb_2b_5j_ms85 -> Fill( evtcode ) ;
            if ( pass4b && ismsb )  h_evtcode_msb_4b_5j_ms85 -> Fill( evtcode ) ;
         }
      }

      if ( pass2b && ismsig ) h_evtcode_msig_2b -> Fill( evtcode ) ;
      if ( pass4b && ismsig ) h_evtcode_msig_4b -> Fill( evtcode ) ;

      if ( pass2b && ismsb ) h_evtcode_msb_2b -> Fill( evtcode ) ;
      if ( pass4b && ismsb ) h_evtcode_msb_4b -> Fill( evtcode ) ;

      if ( pass2b && lowestcsvpt > 40. ) h_evtcode_2b_lcsvpt40 -> Fill( evtcode ) ;
      if ( pass4b && lowestcsvpt > 40. ) h_evtcode_4b_lcsvpt40 -> Fill( evtcode ) ;

      if ( metsig_var>40 ) {

         if ( pass2b ) h_evtcode_2b_ms40 -> Fill( evtcode ) ;
         if ( pass4b ) h_evtcode_4b_ms40 -> Fill( evtcode ) ;

         if ( pass2b && ismsig ) h_evtcode_msig_2b_ms40 -> Fill( evtcode ) ;
         if ( pass4b && ismsig ) h_evtcode_msig_4b_ms40 -> Fill( evtcode ) ;

         if ( pass2b && ismsb ) h_evtcode_msb_2b_ms40 -> Fill( evtcode ) ;
         if ( pass4b && ismsb ) h_evtcode_msb_4b_ms40 -> Fill( evtcode ) ;

      }

      if ( metsig_var>85 ) {

         if ( pass2b ) h_evtcode_2b_ms85 -> Fill( evtcode ) ;
         if ( pass4b ) h_evtcode_4b_ms85 -> Fill( evtcode ) ;

         if ( pass2b && ismsig ) h_evtcode_msig_2b_ms85 -> Fill( evtcode ) ;
         if ( pass4b && ismsig ) h_evtcode_msig_4b_ms85 -> Fill( evtcode ) ;

         if ( pass2b && ismsb ) h_evtcode_msb_2b_ms85 -> Fill( evtcode ) ;
         if ( pass4b && ismsb ) h_evtcode_msb_4b_ms85 -> Fill( evtcode ) ;

      }

      if ( evtcode == 1 ) {

         if ( b1hind == 1 ) { h_mh_b1j_b2j__b1j -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_b1j_b2j__b1j -> Fill( higgsMbb2MassDiff ) ; }
         if ( b2hind == 1 ) { h_mh_b1j_b2j__b2j -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_b1j_b2j__b2j -> Fill( higgsMbb2MassDiff ) ; }

         if ( pass2b ) {
            if ( b1hind == 1 ) { h_mh_b1j_b2j__b1j_2b -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_b1j_b2j__b1j_2b -> Fill( higgsMbb2MassDiff ) ; }
            if ( b2hind == 1 ) { h_mh_b1j_b2j__b2j_2b -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_b1j_b2j__b2j_2b -> Fill( higgsMbb2MassDiff ) ; }
            if ( b1hind == 1 ) { h_mh_b1j_b2j__b1j_2b_ptrw -> Fill( higgsMbb1MassDiff, ptw2b ) ; } else { h_mh_b1j_b2j__b1j_2b_ptrw -> Fill( higgsMbb2MassDiff, ptw2b ) ; }
            if ( b2hind == 1 ) { h_mh_b1j_b2j__b2j_2b_ptrw -> Fill( higgsMbb1MassDiff, ptw2b ) ; } else { h_mh_b1j_b2j__b2j_2b_ptrw -> Fill( higgsMbb2MassDiff, ptw2b ) ; }
         }
         if ( pass4b ) {
            if ( b1hind == 1 ) { h_mh_b1j_b2j__b1j_4b -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_b1j_b2j__b1j_4b -> Fill( higgsMbb2MassDiff ) ; }
            if ( b2hind == 1 ) { h_mh_b1j_b2j__b2j_4b -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_b1j_b2j__b2j_4b -> Fill( higgsMbb2MassDiff ) ; }
         }

         h_amh_b1j_b2j -> Fill( 0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff) ) ;
         if ( pass2b ) { h_amh_b1j_b2j__2b -> Fill( 0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff) ) ; }
         if ( pass4b ) { h_amh_b1j_b2j__4b -> Fill( 0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff) ) ; }
         if ( metsig_var>40 ) {
            h_amh_b1j_b2j_ms40 -> Fill( 0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff) ) ;
            if ( pass2b ) { h_amh_b1j_b2j__2b_ms40 -> Fill( 0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff) ) ; }
            if ( pass4b ) { h_amh_b1j_b2j__4b_ms40 -> Fill( 0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff) ) ; }
         }
         if ( metsig_var>85 ) {
            h_amh_b1j_b2j_ms85 -> Fill( 0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff) ) ;
            if ( pass2b ) { h_amh_b1j_b2j__2b_ms85 -> Fill( 0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff) ) ; }
            if ( pass4b ) { h_amh_b1j_b2j__4b_ms85 -> Fill( 0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff) ) ; }
         }

         h_dmh_b1j_b2j -> Fill( (higgsMbb1MassDiff-higgsMbb2MassDiff) ) ;
         if ( pass2b ) { h_dmh_b1j_b2j__2b -> Fill( (higgsMbb1MassDiff-higgsMbb2MassDiff) ) ; }
         if ( pass4b ) { h_dmh_b1j_b2j__4b -> Fill( (higgsMbb1MassDiff-higgsMbb2MassDiff) ) ; }
         if ( metsig_var>40 ) {
            h_dmh_b1j_b2j_ms40 -> Fill( (higgsMbb1MassDiff-higgsMbb2MassDiff) ) ;
            if ( pass2b ) { h_dmh_b1j_b2j__2b_ms40 -> Fill( (higgsMbb1MassDiff-higgsMbb2MassDiff) ) ; }
            if ( pass4b ) { h_dmh_b1j_b2j__4b_ms40 -> Fill( (higgsMbb1MassDiff-higgsMbb2MassDiff) ) ; }
         }
         if ( metsig_var>85 ) {
            h_dmh_b1j_b2j_ms85 -> Fill( (higgsMbb1MassDiff-higgsMbb2MassDiff) ) ;
            if ( pass2b ) { h_dmh_b1j_b2j__2b_ms85 -> Fill( (higgsMbb1MassDiff-higgsMbb2MassDiff) ) ; }
            if ( pass4b ) { h_dmh_b1j_b2j__4b_ms85 -> Fill( (higgsMbb1MassDiff-higgsMbb2MassDiff) ) ; }
         }
      }

      if ( evtcode == 3 ) {
         if ( b1hind == 1 ) { h_mh_b1x_b2j__b1x -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_b1x_b2j__b1x -> Fill( higgsMbb2MassDiff ) ; }
         if ( b2hind == 1 ) { h_mh_b1x_b2j__b2j -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_b1x_b2j__b2j -> Fill( higgsMbb2MassDiff ) ; }
         if ( pass2b ) {
            if ( b1hind == 1 ) { h_mh_b1x_b2j__b1x_2b -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_b1x_b2j__b1x_2b -> Fill( higgsMbb2MassDiff ) ; }
            if ( b2hind == 1 ) { h_mh_b1x_b2j__b2j_2b -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_b1x_b2j__b2j_2b -> Fill( higgsMbb2MassDiff ) ; }
            if ( b1hind == 1 ) { h_mh_b1x_b2j__b1x_2b_ptrw -> Fill( higgsMbb1MassDiff, ptw2b ) ; } else { h_mh_b1x_b2j__b1x_2b_ptrw -> Fill( higgsMbb2MassDiff, ptw2b ) ; }
            if ( b2hind == 1 ) { h_mh_b1x_b2j__b2j_2b_ptrw -> Fill( higgsMbb1MassDiff, ptw2b ) ; } else { h_mh_b1x_b2j__b2j_2b_ptrw -> Fill( higgsMbb2MassDiff, ptw2b ) ; }
         }
         if ( pass4b ) {
            if ( b1hind == 1 ) { h_mh_b1x_b2j__b1x_4b -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_b1x_b2j__b1x_4b -> Fill( higgsMbb2MassDiff ) ; }
            if ( b2hind == 1 ) { h_mh_b1x_b2j__b2j_4b -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_b1x_b2j__b2j_4b -> Fill( higgsMbb2MassDiff ) ; }
         }
         h_amh_b1x_b2j -> Fill( 0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff) ) ;
         if ( pass2b ) { h_amh_b1x_b2j__2b -> Fill( 0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff) ) ; }
         if ( pass4b ) { h_amh_b1x_b2j__4b -> Fill( 0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff) ) ; }
         h_dmh_b1x_b2j -> Fill( (higgsMbb1MassDiff-higgsMbb2MassDiff) ) ;
         if ( pass2b ) { h_dmh_b1x_b2j__2b -> Fill( (higgsMbb1MassDiff-higgsMbb2MassDiff) ) ; }
         if ( pass4b ) { h_dmh_b1x_b2j__4b -> Fill( (higgsMbb1MassDiff-higgsMbb2MassDiff) ) ; }
      }

      if ( evtcode == 4 ) {
         if ( b1hind == 1 ) { h_mh_b1j_b2x__b1j -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_b1j_b2x__b1j -> Fill( higgsMbb2MassDiff ) ; }
         if ( b2hind == 1 ) { h_mh_b1j_b2x__b2x -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_b1j_b2x__b2x -> Fill( higgsMbb2MassDiff ) ; }
         if ( pass2b ) {
            if ( b1hind == 1 ) { h_mh_b1j_b2x__b1j_2b -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_b1j_b2x__b1j_2b -> Fill( higgsMbb2MassDiff ) ; }
            if ( b2hind == 1 ) { h_mh_b1j_b2x__b2x_2b -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_b1j_b2x__b2x_2b -> Fill( higgsMbb2MassDiff ) ; }
         }
         if ( pass4b ) {
            if ( b1hind == 1 ) { h_mh_b1j_b2x__b1j_4b -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_b1j_b2x__b1j_4b -> Fill( higgsMbb2MassDiff ) ; }
            if ( b2hind == 1 ) { h_mh_b1j_b2x__b2x_4b -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_b1j_b2x__b2x_4b -> Fill( higgsMbb2MassDiff ) ; }
         }
         h_amh_b1j_b2x -> Fill( 0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff) ) ;
         if ( pass2b ) { h_amh_b1j_b2x__2b -> Fill( 0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff) ) ; }
         if ( pass4b ) { h_amh_b1j_b2x__4b -> Fill( 0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff) ) ; }
         h_dmh_b1j_b2x -> Fill( (higgsMbb1MassDiff-higgsMbb2MassDiff) ) ;
         if ( pass2b ) { h_dmh_b1j_b2x__2b -> Fill( (higgsMbb1MassDiff-higgsMbb2MassDiff) ) ; }
         if ( pass4b ) { h_dmh_b1j_b2x__4b -> Fill( (higgsMbb1MassDiff-higgsMbb2MassDiff) ) ; }
      }

      if ( evtcode == 6 ) {
         if ( b1hind == 1 ) { h_mh_b1x_b2x__b1x -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_b1x_b2x__b1x -> Fill( higgsMbb2MassDiff ) ; }
         if ( b2hind == 1 ) { h_mh_b1x_b2x__b2x -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_b1x_b2x__b2x -> Fill( higgsMbb2MassDiff ) ; }
         if ( pass2b ) {
            if ( b1hind == 1 ) { h_mh_b1x_b2x__b1x_2b -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_b1x_b2x__b1x_2b -> Fill( higgsMbb2MassDiff ) ; }
            if ( b2hind == 1 ) { h_mh_b1x_b2x__b2x_2b -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_b1x_b2x__b2x_2b -> Fill( higgsMbb2MassDiff ) ; }
         }
         if ( pass4b ) {
            if ( b1hind == 1 ) { h_mh_b1x_b2x__b1x_4b -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_b1x_b2x__b1x_4b -> Fill( higgsMbb2MassDiff ) ; }
            if ( b2hind == 1 ) { h_mh_b1x_b2x__b2x_4b -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_b1x_b2x__b2x_4b -> Fill( higgsMbb2MassDiff ) ; }
         }
         h_amh_b1x_b2x -> Fill( 0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff) ) ;
         if ( pass2b ) { h_amh_b1x_b2x__2b -> Fill( 0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff) ) ; }
         if ( pass4b ) { h_amh_b1x_b2x__4b -> Fill( 0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff) ) ; }
         h_dmh_b1x_b2x -> Fill( (higgsMbb1MassDiff-higgsMbb2MassDiff) ) ;
         if ( pass2b ) { h_dmh_b1x_b2x__2b -> Fill( (higgsMbb1MassDiff-higgsMbb2MassDiff) ) ; }
         if ( pass4b ) { h_dmh_b1x_b2x__4b -> Fill( (higgsMbb1MassDiff-higgsMbb2MassDiff) ) ; }
      }




      if ( evtcode == 2 ) {
         if ( b1hind == 1 ) { h_mh_b1b2_jj__b1b2 -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_b1b2_jj__b1b2 -> Fill( higgsMbb2MassDiff ) ; }
         if ( jahind == 1 ) { h_mh_b1b2_jj__jj -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_b1b2_jj__jj -> Fill( higgsMbb2MassDiff ) ; }
         if ( pass2b ) {
            if ( b1hind == 1 ) { h_mh_b1b2_jj__b1b2_2b -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_b1b2_jj__b1b2_2b -> Fill( higgsMbb2MassDiff ) ; }
            if ( jahind == 1 ) { h_mh_b1b2_jj__jj_2b -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_b1b2_jj__jj_2b -> Fill( higgsMbb2MassDiff ) ; }
         }
         if ( pass4b ) {
            if ( b1hind == 1 ) { h_mh_b1b2_jj__b1b2_4b -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_b1b2_jj__b1b2_4b -> Fill( higgsMbb2MassDiff ) ; }
            if ( jahind == 1 ) { h_mh_b1b2_jj__jj_4b -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_b1b2_jj__jj_4b -> Fill( higgsMbb2MassDiff ) ; }
         }
         h_amh_b1b2_jj -> Fill( 0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff) ) ;
         if ( pass2b ) { h_amh_b1b2_jj__2b -> Fill( 0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff) ) ; }
         if ( pass4b ) { h_amh_b1b2_jj__4b -> Fill( 0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff) ) ; }
         h_dmh_b1b2_jj -> Fill( (higgsMbb1MassDiff-higgsMbb2MassDiff) ) ;
         if ( pass2b ) { h_dmh_b1b2_jj__2b -> Fill( (higgsMbb1MassDiff-higgsMbb2MassDiff) ) ; }
         if ( pass4b ) { h_dmh_b1b2_jj__4b -> Fill( (higgsMbb1MassDiff-higgsMbb2MassDiff) ) ; }
      }





      if ( evtcode == 5 ) {
         if ( b1hind == 1 ) { h_mh_b1b2_jx__b1b2 -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_b1b2_jx__b1b2 -> Fill( higgsMbb2MassDiff ) ; }
         if ( b1hind == 2 ) { h_mh_b1b2_jx__jx -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_b1b2_jx__jx -> Fill( higgsMbb2MassDiff ) ; }
         if ( pass2b ) {
            if ( b1hind == 1 ) { h_mh_b1b2_jx__b1b2_2b -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_b1b2_jx__b1b2_2b -> Fill( higgsMbb2MassDiff ) ; }
            if ( b1hind == 2 ) { h_mh_b1b2_jx__jx_2b -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_b1b2_jx__jx_2b -> Fill( higgsMbb2MassDiff ) ; }
         }
         if ( pass4b ) {
            if ( b1hind == 1 ) { h_mh_b1b2_jx__b1b2_4b -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_b1b2_jx__b1b2_4b -> Fill( higgsMbb2MassDiff ) ; }
            if ( b1hind == 2 ) { h_mh_b1b2_jx__jx_4b -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_b1b2_jx__jx_4b -> Fill( higgsMbb2MassDiff ) ; }
         }
         h_amh_b1b2_jx -> Fill( 0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff) ) ;
         if ( pass2b ) { h_amh_b1b2_jx__2b -> Fill( 0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff) ) ; }
         if ( pass4b ) { h_amh_b1b2_jx__4b -> Fill( 0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff) ) ; }
         h_dmh_b1b2_jx -> Fill( (higgsMbb1MassDiff-higgsMbb2MassDiff) ) ;
         if ( pass2b ) { h_dmh_b1b2_jx__2b -> Fill( (higgsMbb1MassDiff-higgsMbb2MassDiff) ) ; }
         if ( pass4b ) { h_dmh_b1b2_jx__4b -> Fill( (higgsMbb1MassDiff-higgsMbb2MassDiff) ) ; }
      }





      if ( evtcode == 0 ) {
         h_amh_other -> Fill( 0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff) ) ;
         if ( pass2b ) h_amh_other__2b -> Fill( 0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff) ) ;
         if ( pass4b ) h_amh_other__4b -> Fill( 0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff) ) ;
         h_dmh_other -> Fill( (higgsMbb1MassDiff-higgsMbb2MassDiff) ) ;
         if ( pass2b ) h_dmh_other__2b -> Fill( (higgsMbb1MassDiff-higgsMbb2MassDiff) ) ;
         if ( pass4b ) h_dmh_other__4b -> Fill( (higgsMbb1MassDiff-higgsMbb2MassDiff) ) ;
      }






      if ( b1hind == 1 ) { h_mh_all__b1 -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_all__b1 -> Fill( higgsMbb2MassDiff ) ; }
      if ( b2hind == 1 ) { h_mh_all__b2 -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_all__b2 -> Fill( higgsMbb2MassDiff ) ; }
      h_mh_all__sptl -> Fill( mh_sptl ) ;
      h_mh_all__spth -> Fill( mh_spth ) ;
      if ( pass2b ) {
         if ( b1hind == 1 ) { h_mh_all__b1_2b -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_all__b1_2b -> Fill( higgsMbb2MassDiff ) ; }
         if ( b2hind == 1 ) { h_mh_all__b2_2b -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_all__b2_2b -> Fill( higgsMbb2MassDiff ) ; }
         h_mh_all__sptl_2b -> Fill( mh_sptl ) ;
         h_mh_all__spth_2b -> Fill( mh_spth ) ;
      }
      if ( pass4b ) {
         if ( b1hind == 1 ) { h_mh_all__b1_4b -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_all__b1_4b -> Fill( higgsMbb2MassDiff ) ; }
         if ( b2hind == 1 ) { h_mh_all__b2_4b -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_all__b2_4b -> Fill( higgsMbb2MassDiff ) ; }
         h_mh_all__sptl_4b -> Fill( mh_sptl ) ;
         h_mh_all__spth_4b -> Fill( mh_spth ) ;
      }
      h_amh_all -> Fill( 0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff) ) ;
      if ( pass2b ) h_amh_all__2b -> Fill( 0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff) ) ;
      if ( pass4b ) h_amh_all__4b -> Fill( 0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff) ) ;
      h_dmh_all -> Fill( (higgsMbb1MassDiff-higgsMbb2MassDiff) ) ;
      if ( pass2b ) h_dmh_all__2b -> Fill( (higgsMbb1MassDiff-higgsMbb2MassDiff) ) ;
      if ( pass4b ) h_dmh_all__4b -> Fill( (higgsMbb1MassDiff-higgsMbb2MassDiff) ) ;



      if ( njets20 == 4 ) {
         if ( b1hind == 1 ) { h_mh_all__b1_4j -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_all__b1_4j -> Fill( higgsMbb2MassDiff ) ; }
         if ( b2hind == 1 ) { h_mh_all__b2_4j -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_all__b2_4j -> Fill( higgsMbb2MassDiff ) ; }
         h_mh_all__sptl_4j -> Fill( mh_sptl ) ;
         h_mh_all__spth_4j -> Fill( mh_spth ) ;
         if ( pass2b ) {
            if ( b1hind == 1 ) { h_mh_all__b1_2b_4j -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_all__b1_2b_4j -> Fill( higgsMbb2MassDiff ) ; }
            if ( b2hind == 1 ) { h_mh_all__b2_2b_4j -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_all__b2_2b_4j -> Fill( higgsMbb2MassDiff ) ; }
            h_mh_all__sptl_2b_4j -> Fill( mh_sptl ) ;
            h_mh_all__spth_2b_4j -> Fill( mh_spth ) ;
         }
         if ( pass4b ) {
            if ( b1hind == 1 ) { h_mh_all__b1_4b_4j -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_all__b1_4b_4j -> Fill( higgsMbb2MassDiff ) ; }
            if ( b2hind == 1 ) { h_mh_all__b2_4b_4j -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_all__b2_4b_4j -> Fill( higgsMbb2MassDiff ) ; }
            h_mh_all__sptl_4b_4j -> Fill( mh_sptl ) ;
            h_mh_all__spth_4b_4j -> Fill( mh_spth ) ;
         }
         h_amh_all_4j -> Fill( 0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff) ) ;
         if ( pass2b ) h_amh_all__2b_4j -> Fill( 0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff) ) ;
         if ( pass4b ) h_amh_all__4b_4j -> Fill( 0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff) ) ;
         h_dmh_all_4j -> Fill( (higgsMbb1MassDiff-higgsMbb2MassDiff) ) ;
         if ( pass2b ) h_dmh_all__2b_4j -> Fill( (higgsMbb1MassDiff-higgsMbb2MassDiff) ) ;
         if ( pass4b ) h_dmh_all__4b_4j -> Fill( (higgsMbb1MassDiff-higgsMbb2MassDiff) ) ;
      }





      if ( njets20 == 5 ) {
         if ( b1hind == 1 ) { h_mh_all__b1_5j -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_all__b1_5j -> Fill( higgsMbb2MassDiff ) ; }
         if ( b2hind == 1 ) { h_mh_all__b2_5j -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_all__b2_5j -> Fill( higgsMbb2MassDiff ) ; }
         h_mh_all__sptl_5j -> Fill( mh_sptl ) ;
         h_mh_all__spth_5j -> Fill( mh_spth ) ;
         if ( pass2b ) {
            if ( b1hind == 1 ) { h_mh_all__b1_2b_5j -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_all__b1_2b_5j -> Fill( higgsMbb2MassDiff ) ; }
            if ( b2hind == 1 ) { h_mh_all__b2_2b_5j -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_all__b2_2b_5j -> Fill( higgsMbb2MassDiff ) ; }
            h_mh_all__sptl_2b_5j -> Fill( mh_sptl ) ;
            h_mh_all__spth_2b_5j -> Fill( mh_spth ) ;
         }
         if ( pass4b ) {
            if ( b1hind == 1 ) { h_mh_all__b1_4b_5j -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_all__b1_4b_5j -> Fill( higgsMbb2MassDiff ) ; }
            if ( b2hind == 1 ) { h_mh_all__b2_4b_5j -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_all__b2_4b_5j -> Fill( higgsMbb2MassDiff ) ; }
            h_mh_all__sptl_4b_5j -> Fill( mh_sptl ) ;
            h_mh_all__spth_4b_5j -> Fill( mh_spth ) ;
         }
         h_amh_all_5j -> Fill( 0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff) ) ;
         if ( pass2b ) h_amh_all__2b_5j -> Fill( 0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff) ) ;
         if ( pass4b ) h_amh_all__4b_5j -> Fill( 0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff) ) ;
         h_dmh_all_5j -> Fill( (higgsMbb1MassDiff-higgsMbb2MassDiff) ) ;
         if ( pass2b ) h_dmh_all__2b_5j -> Fill( (higgsMbb1MassDiff-higgsMbb2MassDiff) ) ;
         if ( pass4b ) h_dmh_all__4b_5j -> Fill( (higgsMbb1MassDiff-higgsMbb2MassDiff) ) ;
      }


      if ( metsig_var>40 ) {
         if ( b1hind == 1 ) { h_mh_all__b1_ms40 -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_all__b1_ms40 -> Fill( higgsMbb2MassDiff ) ; }
         if ( b2hind == 1 ) { h_mh_all__b2_ms40 -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_all__b2_ms40 -> Fill( higgsMbb2MassDiff ) ; }
         h_mh_all__sptl_ms40 -> Fill( mh_sptl ) ;
         h_mh_all__spth_ms40 -> Fill( mh_spth ) ;
         if ( pass2b ) {
            if ( b1hind == 1 ) { h_mh_all__b1_2b_ms40 -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_all__b1_2b_ms40 -> Fill( higgsMbb2MassDiff ) ; }
            if ( b2hind == 1 ) { h_mh_all__b2_2b_ms40 -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_all__b2_2b_ms40 -> Fill( higgsMbb2MassDiff ) ; }
            h_mh_all__sptl_2b_ms40 -> Fill( mh_sptl ) ;
            h_mh_all__spth_2b_ms40 -> Fill( mh_spth ) ;
         }
         if ( pass4b ) {
            if ( b1hind == 1 ) { h_mh_all__b1_4b_ms40 -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_all__b1_4b_ms40 -> Fill( higgsMbb2MassDiff ) ; }
            if ( b2hind == 1 ) { h_mh_all__b2_4b_ms40 -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_all__b2_4b_ms40 -> Fill( higgsMbb2MassDiff ) ; }
            h_mh_all__sptl_4b_ms40 -> Fill( mh_sptl ) ;
            h_mh_all__spth_4b_ms40 -> Fill( mh_spth ) ;
         }
         h_amh_all_ms40 -> Fill( 0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff) ) ;
         if ( pass2b ) h_amh_all__2b_ms40 -> Fill( 0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff) ) ;
         if ( pass4b ) h_amh_all__4b_ms40 -> Fill( 0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff) ) ;
         h_dmh_all_ms40 -> Fill( (higgsMbb1MassDiff-higgsMbb2MassDiff) ) ;
         if ( pass2b ) h_dmh_all__2b_ms40 -> Fill( (higgsMbb1MassDiff-higgsMbb2MassDiff) ) ;
         if ( pass4b ) h_dmh_all__4b_ms40 -> Fill( (higgsMbb1MassDiff-higgsMbb2MassDiff) ) ;
      }

      if ( metsig_var>85 ) {
         if ( b1hind == 1 ) { h_mh_all__b1_ms85 -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_all__b1_ms85 -> Fill( higgsMbb2MassDiff ) ; }
         if ( b2hind == 1 ) { h_mh_all__b2_ms85 -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_all__b2_ms85 -> Fill( higgsMbb2MassDiff ) ; }
         h_mh_all__sptl_ms85 -> Fill( mh_sptl ) ;
         h_mh_all__spth_ms85 -> Fill( mh_spth ) ;
         if ( pass2b ) {
            if ( b1hind == 1 ) { h_mh_all__b1_2b_ms85 -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_all__b1_2b_ms85 -> Fill( higgsMbb2MassDiff ) ; }
            if ( b2hind == 1 ) { h_mh_all__b2_2b_ms85 -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_all__b2_2b_ms85 -> Fill( higgsMbb2MassDiff ) ; }
            h_mh_all__sptl_2b_ms85 -> Fill( mh_sptl ) ;
            h_mh_all__spth_2b_ms85 -> Fill( mh_spth ) ;
         }
         if ( pass4b ) {
            if ( b1hind == 1 ) { h_mh_all__b1_4b_ms85 -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_all__b1_4b_ms85 -> Fill( higgsMbb2MassDiff ) ; }
            if ( b2hind == 1 ) { h_mh_all__b2_4b_ms85 -> Fill( higgsMbb1MassDiff ) ; } else { h_mh_all__b2_4b_ms85 -> Fill( higgsMbb2MassDiff ) ; }
            h_mh_all__sptl_4b_ms85 -> Fill( mh_sptl ) ;
            h_mh_all__spth_4b_ms85 -> Fill( mh_spth ) ;
         }
         h_amh_all_ms85 -> Fill( 0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff) ) ;
         if ( pass2b ) h_amh_all__2b_ms85 -> Fill( 0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff) ) ;
         if ( pass4b ) h_amh_all__4b_ms85 -> Fill( 0.5*(higgsMbb1MassDiff+higgsMbb2MassDiff) ) ;
         h_dmh_all_ms85 -> Fill( (higgsMbb1MassDiff-higgsMbb2MassDiff) ) ;
         if ( pass2b ) h_dmh_all__2b_ms85 -> Fill( (higgsMbb1MassDiff-higgsMbb2MassDiff) ) ;
         if ( pass4b ) h_dmh_all__4b_ms85 -> Fill( (higgsMbb1MassDiff-higgsMbb2MassDiff) ) ;
      }

   } // jentry.

   addoverflow( h_lowestcsv_pt_4b ) ;
   addoverflow( h_lowestcsv_pt ) ;

   addoverflow( h_metsig_msig_2b ) ;
   addoverflow( h_metsig_msig_3b ) ;
   addoverflow( h_metsig_msig_4b ) ;
   addoverflow( h_metsig_msb_2b ) ;
   addoverflow( h_metsig_msb_3b ) ;
   addoverflow( h_metsig_msb_4b ) ;

   addoverflow( h_metsig_msig_2b_ptrw ) ;
   addoverflow( h_metsig_msb_2b_ptrw ) ;

   addoverflow( h_metsig_msig_2b_sptrw ) ;
   addoverflow( h_metsig_msb_2b_sptrw ) ;

   addoverflow( h_metsig_msig_2b_4j ) ;
   addoverflow( h_metsig_msig_3b_4j ) ;
   addoverflow( h_metsig_msig_4b_4j ) ;
   addoverflow( h_metsig_msb_2b_4j ) ;
   addoverflow( h_metsig_msb_3b_4j ) ;
   addoverflow( h_metsig_msb_4b_4j ) ;

   addoverflow( h_metsig_msig_2b_4j_ptrw ) ;
   addoverflow( h_metsig_msb_2b_4j_ptrw ) ;

   addoverflow( h_metsig_msig_2b_5j ) ;
   addoverflow( h_metsig_msig_3b_5j ) ;
   addoverflow( h_metsig_msig_4b_5j ) ;
   addoverflow( h_metsig_msb_2b_5j ) ;
   addoverflow( h_metsig_msb_3b_5j ) ;
   addoverflow( h_metsig_msb_4b_5j ) ;

   addoverflow( h_metsig_msig_2b_5j_ptrw ) ;
   addoverflow( h_metsig_msb_2b_5j_ptrw ) ;

   addoverflow( h_metsig_msig_2b_mdpc ) ;
   addoverflow( h_metsig_msig_3b_mdpc ) ;
   addoverflow( h_metsig_msig_4b_mdpc ) ;
   addoverflow( h_metsig_msb_2b_mdpc ) ;
   addoverflow( h_metsig_msb_3b_mdpc ) ;
   addoverflow( h_metsig_msb_4b_mdpc ) ;


   addoverflow( h_dmh_b1j_b2j, 1 ) ;
   addoverflow( h_dmh_b1j_b2j__2b, 1 ) ;
   addoverflow( h_dmh_b1j_b2j__4b, 1 ) ;
   addoverflow( h_dmh_b1j_b2j_ms40, 1 ) ;
   addoverflow( h_dmh_b1j_b2j__2b_ms40, 1 ) ;
   addoverflow( h_dmh_b1j_b2j__4b_ms40, 1 ) ;
   addoverflow( h_dmh_b1j_b2j_ms85, 1 ) ;
   addoverflow( h_dmh_b1j_b2j__2b_ms85, 1 ) ;
   addoverflow( h_dmh_b1j_b2j__4b_ms85, 1 ) ;

   addoverflow( h_dmh_b1x_b2j, 1 ) ;
   addoverflow( h_dmh_b1x_b2j__2b, 1 ) ;
   addoverflow( h_dmh_b1x_b2j__4b, 1 ) ;

   addoverflow( h_dmh_b1j_b2x, 1 ) ;
   addoverflow( h_dmh_b1j_b2x__2b, 1 ) ;
   addoverflow( h_dmh_b1j_b2x__4b, 1 ) ;

   addoverflow( h_dmh_b1x_b2x, 1 ) ;
   addoverflow( h_dmh_b1x_b2x__2b, 1 ) ;
   addoverflow( h_dmh_b1x_b2x__4b, 1 ) ;

   addoverflow( h_dmh_b1b2_jj, 1 ) ;
   addoverflow( h_dmh_b1b2_jj__2b, 1 ) ;
   addoverflow( h_dmh_b1b2_jj__4b, 1 ) ;

   addoverflow( h_dmh_b1b2_jx, 1 ) ;
   addoverflow( h_dmh_b1b2_jx__2b, 1 ) ;
   addoverflow( h_dmh_b1b2_jx__4b, 1 ) ;

   addoverflow( h_dmh_other, 1 ) ;
   addoverflow( h_dmh_other__2b, 1 ) ;
   addoverflow( h_dmh_other__4b, 1 ) ;

   addoverflow( h_dmh_all, 1 ) ;
   addoverflow( h_dmh_all__2b, 1 ) ;
   addoverflow( h_dmh_all__4b, 1 ) ;

   addoverflow( h_pt_highest_csv_2b ) ;
   addoverflow( h_pt_nexthighest_csv_2b ) ;
   addoverflow( h_pt_nextlowest_csv_2b ) ;
   addoverflow( h_pt_lowest_csv_2b ) ;

   addoverflow( h_pt_highest_csv_3b ) ;
   addoverflow( h_pt_nexthighest_csv_3b ) ;
   addoverflow( h_pt_nextlowest_csv_3b ) ;
   addoverflow( h_pt_lowest_csv_3b ) ;

   addoverflow( h_pt_highest_csv_4b ) ;
   addoverflow( h_pt_nexthighest_csv_4b ) ;
   addoverflow( h_pt_nextlowest_csv_4b ) ;
   addoverflow( h_pt_lowest_csv_4b ) ;



   fillratio( h_metsig_msig_2b, h_metsig_msb_2b, h_metsig_rmsigsb_2b ) ;
   fillratio( h_metsig_msig_3b, h_metsig_msb_3b, h_metsig_rmsigsb_3b ) ;
   fillratio( h_metsig_msig_4b, h_metsig_msb_4b, h_metsig_rmsigsb_4b ) ;

   fillratio( h_metsig_msig_2b_ptrw, h_metsig_msb_2b_ptrw, h_metsig_rmsigsb_2b_ptrw ) ;
   fillratio( h_metsig_msig_2b_sptrw, h_metsig_msb_2b_sptrw, h_metsig_rmsigsb_2b_sptrw ) ;

   fillratio( h_metsig_msig_2b_4j, h_metsig_msb_2b_4j, h_metsig_rmsigsb_2b_4j ) ;
   fillratio( h_metsig_msig_3b_4j, h_metsig_msb_3b_4j, h_metsig_rmsigsb_3b_4j ) ;
   fillratio( h_metsig_msig_4b_4j, h_metsig_msb_4b_4j, h_metsig_rmsigsb_4b_4j ) ;

   fillratio( h_metsig_msig_2b_4j_ptrw, h_metsig_msb_2b_4j_ptrw, h_metsig_rmsigsb_2b_4j_ptrw ) ;

   fillratio( h_metsig_msig_2b_5j, h_metsig_msb_2b_5j, h_metsig_rmsigsb_2b_5j ) ;
   fillratio( h_metsig_msig_3b_5j, h_metsig_msb_3b_5j, h_metsig_rmsigsb_3b_5j ) ;
   fillratio( h_metsig_msig_4b_5j, h_metsig_msb_4b_5j, h_metsig_rmsigsb_4b_5j ) ;

   fillratio( h_metsig_msig_2b_5j_ptrw, h_metsig_msb_2b_5j_ptrw, h_metsig_rmsigsb_2b_5j_ptrw ) ;

   fillratio( h_metsig_msig_2b_mdpc, h_metsig_msb_2b_mdpc, h_metsig_rmsigsb_2b_mdpc ) ;
   fillratio( h_metsig_msig_3b_mdpc, h_metsig_msb_3b_mdpc, h_metsig_rmsigsb_3b_mdpc ) ;
   fillratio( h_metsig_msig_4b_mdpc, h_metsig_msb_4b_mdpc, h_metsig_rmsigsb_4b_mdpc ) ;



   fillratio( h_evtcode_msig_2b, h_evtcode_msb_2b, h_evtcode_rmsigsb_2b ) ;
   fillratio( h_evtcode_msig_4b, h_evtcode_msb_4b, h_evtcode_rmsigsb_4b ) ;

   fillratio( h_evtcode_msig_2b_ms40, h_evtcode_msb_2b_ms40, h_evtcode_rmsigsb_2b_ms40 ) ;
   fillratio( h_evtcode_msig_4b_ms40, h_evtcode_msb_4b_ms40, h_evtcode_rmsigsb_4b_ms40 ) ;

   fillratio( h_evtcode_msig_2b_ms85, h_evtcode_msb_2b_ms85, h_evtcode_rmsigsb_2b_ms85 ) ;
   fillratio( h_evtcode_msig_4b_ms85, h_evtcode_msb_4b_ms85, h_evtcode_rmsigsb_4b_ms85 ) ;

   fillratio( h_evtcode_msig_2b_4j, h_evtcode_msb_2b_4j, h_evtcode_rmsigsb_2b_4j ) ;
   fillratio( h_evtcode_msig_4b_4j, h_evtcode_msb_4b_4j, h_evtcode_rmsigsb_4b_4j ) ;

   fillratio( h_evtcode_msig_2b_5j, h_evtcode_msb_2b_5j, h_evtcode_rmsigsb_2b_5j ) ;
   fillratio( h_evtcode_msig_4b_5j, h_evtcode_msb_4b_5j, h_evtcode_rmsigsb_4b_5j ) ;

   fillratio( h_evtcode_msig_2b_4j_ms40, h_evtcode_msb_2b_4j_ms40, h_evtcode_rmsigsb_2b_4j_ms40 ) ;
   fillratio( h_evtcode_msig_4b_4j_ms40, h_evtcode_msb_4b_4j_ms40, h_evtcode_rmsigsb_4b_4j_ms40 ) ;

   fillratio( h_evtcode_msig_2b_5j_ms40, h_evtcode_msb_2b_5j_ms40, h_evtcode_rmsigsb_2b_5j_ms40 ) ;
   fillratio( h_evtcode_msig_4b_5j_ms40, h_evtcode_msb_4b_5j_ms40, h_evtcode_rmsigsb_4b_5j_ms40 ) ;

   fillratio( h_evtcode_msig_2b_4j_ms85, h_evtcode_msb_2b_4j_ms85, h_evtcode_rmsigsb_2b_4j_ms85 ) ;
   fillratio( h_evtcode_msig_4b_4j_ms85, h_evtcode_msb_4b_4j_ms85, h_evtcode_rmsigsb_4b_4j_ms85 ) ;

   fillratio( h_evtcode_msig_2b_5j_ms85, h_evtcode_msb_2b_5j_ms85, h_evtcode_rmsigsb_2b_5j_ms85 ) ;
   fillratio( h_evtcode_msig_4b_5j_ms85, h_evtcode_msb_4b_5j_ms85, h_evtcode_rmsigsb_4b_5j_ms85 ) ;

   fillWeightHist( h_sumpt__2b, h_sumpt__4b, h_sumpt__weight ) ;

  //--- Njet reweighting, METsig>30

   float f4j2b = h_njets_2b -> GetBinContent( 4 ) / h_njets_2b -> Integral() ;
   float f5j2b = h_njets_2b -> GetBinContent( 5 ) / h_njets_2b -> Integral() ;

   float f4j4b = h_njets_4b -> GetBinContent( 4 ) / h_njets_4b -> Integral() ;
   float f5j4b = h_njets_4b -> GetBinContent( 5 ) / h_njets_4b -> Integral() ;

   float w4j = f4j4b / f4j2b ;
   float w5j = f5j4b / f5j2b ;

   printf("\n\n") ;
   printf("  METsig>30 2b, f4j = %.3f, f5j = %.3f\n", f4j2b, f5j2b ) ;
   printf("  METsig>30 4b, f4j = %.3f, f5j = %.3f\n", f4j4b, f5j4b ) ;
   printf("  METsig>30     w4j = %.3f, w5j = %.3f\n", w4j, w5j ) ;
   printf("\n\n") ;

   fillratioReweight( h_evtcode_msig_2b_4j, h_evtcode_msb_2b_4j, h_evtcode_msig_2b_5j, h_evtcode_msb_2b_5j, w4j, w5j, h_evtcode_rmsigsb_2b_NjetReweight ) ;
   fillratioReweight( h_metsig_msig_2b_4j, h_metsig_msb_2b_4j, h_metsig_msig_2b_5j, h_metsig_msb_2b_5j, w4j, w5j, h_metsig_rmsigsb_2b_NjetReweight ) ;

   fillratioReweight( h_metsig_msig_2b_4j_ptrw, h_metsig_msb_2b_4j_ptrw, h_metsig_msig_2b_5j_ptrw, h_metsig_msb_2b_5j_ptrw, w4j, w5j, h_metsig_rmsigsb_2b_NjetReweight_ptrw ) ;

   h_evtcode_2b_NjetReweight -> Sumw2() ;
   h_evtcode_2b_NjetReweight -> Add( h_evtcode_2b_4j, w4j ) ;
   h_evtcode_2b_NjetReweight -> Add( h_evtcode_2b_5j, w5j ) ;

  //-- sanity check
   h_njets_2b_NjetReweight -> SetBinContent( 4, w4j*(h_njets_2b->GetBinContent(4)) ) ;
   h_njets_2b_NjetReweight -> SetBinContent( 5, w5j*(h_njets_2b->GetBinContent(5)) ) ;
   h_njets_2b_NjetReweight -> SetBinError( 4, w4j*(h_njets_2b->GetBinError(4)) ) ;
   h_njets_2b_NjetReweight -> SetBinError( 5, w5j*(h_njets_2b->GetBinError(5)) ) ;






  //--- Njet reweighting, METsig>40

   float f4j2b_ms40 = h_njets_2b_ms40 -> GetBinContent( 4 ) / h_njets_2b_ms40 -> Integral() ;
   float f5j2b_ms40 = h_njets_2b_ms40 -> GetBinContent( 5 ) / h_njets_2b_ms40 -> Integral() ;

   float f4j4b_ms40 = h_njets_4b_ms40 -> GetBinContent( 4 ) / h_njets_4b_ms40 -> Integral() ;
   float f5j4b_ms40 = h_njets_4b_ms40 -> GetBinContent( 5 ) / h_njets_4b_ms40 -> Integral() ;

   float w4j_ms40 = f4j4b_ms40 / f4j2b_ms40 ;
   float w5j_ms40 = f5j4b_ms40 / f5j2b_ms40 ;

   printf("\n\n") ;
   printf("  METsig>40 2b, f4j = %.3f, f5j = %.3f\n", f4j2b_ms40, f5j2b_ms40 ) ;
   printf("  METsig>40 4b, f4j = %.3f, f5j = %.3f\n", f4j4b_ms40, f5j4b_ms40 ) ;
   printf("  METsig>40     w4j = %.3f, w5j = %.3f\n", w4j_ms40, w5j_ms40 ) ;
   printf("\n\n") ;

   fillratioReweight( h_evtcode_msig_2b_4j_ms40, h_evtcode_msb_2b_4j_ms40, h_evtcode_msig_2b_5j_ms40, h_evtcode_msb_2b_5j_ms40, w4j_ms40, w5j_ms40, h_evtcode_rmsigsb_2b_ms40_NjetReweight ) ;

   h_evtcode_2b_ms40_NjetReweight -> Sumw2() ;
   h_evtcode_2b_ms40_NjetReweight -> Add( h_evtcode_2b_4j_ms40, w4j_ms40 ) ;
   h_evtcode_2b_ms40_NjetReweight -> Add( h_evtcode_2b_5j_ms40, w5j_ms40 ) ;



  //--- Njet reweighting, METsig>85

   float f4j2b_ms85 = h_njets_2b_ms85 -> GetBinContent( 4 ) / h_njets_2b_ms85 -> Integral() ;
   float f5j2b_ms85 = h_njets_2b_ms85 -> GetBinContent( 5 ) / h_njets_2b_ms85 -> Integral() ;

   float f4j4b_ms85 = h_njets_4b_ms85 -> GetBinContent( 4 ) / h_njets_4b_ms85 -> Integral() ;
   float f5j4b_ms85 = h_njets_4b_ms85 -> GetBinContent( 5 ) / h_njets_4b_ms85 -> Integral() ;

   float w4j_ms85 = f4j4b_ms85 / f4j2b_ms85 ;
   float w5j_ms85 = f5j4b_ms85 / f5j2b_ms85 ;

   printf("\n\n") ;
   printf("  METsig>85 2b, f4j = %.3f, f5j = %.3f\n", f4j2b_ms85, f5j2b_ms85 ) ;
   printf("  METsig>85 4b, f4j = %.3f, f5j = %.3f\n", f4j4b_ms85, f5j4b_ms85 ) ;
   printf("  METsig>85     w4j = %.3f, w5j = %.3f\n", w4j_ms85, w5j_ms85 ) ;
   printf("\n\n") ;

   fillratioReweight( h_evtcode_msig_2b_4j_ms85, h_evtcode_msb_2b_4j_ms85, h_evtcode_msig_2b_5j_ms85, h_evtcode_msb_2b_5j_ms85, w4j_ms85, w5j_ms85, h_evtcode_rmsigsb_2b_ms85_NjetReweight ) ;

   h_evtcode_2b_ms85_NjetReweight -> Sumw2() ;
   h_evtcode_2b_ms85_NjetReweight -> Add( h_evtcode_2b_4j_ms85, w4j_ms85 ) ;
   h_evtcode_2b_ms85_NjetReweight -> Add( h_evtcode_2b_5j_ms85, w5j_ms85 ) ;









   filldistReweight( h_mh_all__spth_2b_4j, h_mh_all__spth_2b_5j, w4j, w5j, h_mh_all__spth_2b_njrw ) ;
   filldistReweight( h_mh_all__sptl_2b_4j, h_mh_all__sptl_2b_5j, w4j, w5j, h_mh_all__sptl_2b_njrw ) ;



   fillEffHist( h_pt_lowest_csv__passloose, h_pt_lowest_csv, h_pt_lowest_csv__passloose_eff ) ;

   fillEffHist( h_pt_nextlowest_csv__passmed, h_pt_nextlowest_csv, h_pt_nextlowest_csv__passmed_eff ) ;

   fillEffHist( h_pt_nextlowest_csv__failmed, h_pt_nextlowest_csv, h_pt_nextlowest_csv__failmed_eff ) ;


   fillEffHist( h_pt_lowest_csv_cb__passloose, h_pt_lowest_csv_cb, h_pt_lowest_csv_cb__passloose_eff ) ;

   fillEffHist( h_pt_nextlowest_csv_cb__passmed, h_pt_nextlowest_csv_cb, h_pt_nextlowest_csv_cb__passmed_eff ) ;

   fillEffHist( h_pt_nextlowest_csv_cb__failmed, h_pt_nextlowest_csv_cb, h_pt_nextlowest_csv_cb__failmed_eff ) ;



   char outfile[10000] ;
   sprintf( outfile, "outputfiles/truthstudy1-%s.root", samplename ) ;
   saveHist( outfile, "h*" ) ;

 //=====================


   draw_code_ratio_canvas( "code_ratio_ms30", "Config and mass SIG/SB ratio, METsig>30",
                           h_evtcode_2b, h_evtcode_4b, h_evtcode_rmsigsb_2b, h_evtcode_rmsigsb_4b ) ;

   draw_code_ratio_canvas( "code_ratio_ms40", "Config and mass SIG/SB ratio, METsig>40",
                           h_evtcode_2b_ms40, h_evtcode_4b_ms40, h_evtcode_rmsigsb_2b_ms40, h_evtcode_rmsigsb_4b_ms40 ) ;

   draw_code_ratio_canvas( "code_ratio_ms85", "Config and mass SIG/SB ratio, METsig>85",
                           h_evtcode_2b_ms85, h_evtcode_4b_ms85, h_evtcode_rmsigsb_2b_ms85, h_evtcode_rmsigsb_4b_ms85 ) ;

   draw_code_ratio_canvas( "code_ratio_4j", "Config and mass SIG/SB ratio, Njets = 4",
                           h_evtcode_2b_4j, h_evtcode_4b_4j, h_evtcode_rmsigsb_2b_4j, h_evtcode_rmsigsb_4b_4j ) ;

   draw_code_ratio_canvas( "code_ratio_5j", "Config and mass SIG/SB ratio, Njets = 5",
                           h_evtcode_2b_5j, h_evtcode_4b_5j, h_evtcode_rmsigsb_2b_5j, h_evtcode_rmsigsb_4b_5j ) ;

   draw_code_ratio_canvas( "code_ratio_NjetReweight", "Config and mass SIG/SB ratio, METsig>30, 2b Njet Reweighted",
                           h_evtcode_2b_NjetReweight, h_evtcode_4b, h_evtcode_rmsigsb_2b_NjetReweight, h_evtcode_rmsigsb_4b ) ;

   draw_code_ratio_canvas( "code_ratio_ms40_NjetReweight", "Config and mass SIG/SB ratio, METsig>40, 2b Njet Reweighted",
                           h_evtcode_2b_ms40_NjetReweight, h_evtcode_4b_ms40, h_evtcode_rmsigsb_2b_ms40_NjetReweight, h_evtcode_rmsigsb_4b_ms40 ) ;

   draw_code_ratio_canvas( "code_ratio_ms85_NjetReweight", "Config and mass SIG/SB ratio, METsig>85, 2b Njet Reweighted",
                           h_evtcode_2b_ms85_NjetReweight, h_evtcode_4b_ms85, h_evtcode_rmsigsb_2b_ms85_NjetReweight, h_evtcode_rmsigsb_4b_ms85 ) ;



 //=====================

   draw_mass_canvas( "mh_b1jb2j", "Mass (b1j)(b2j)", h_mh_b1j_b2j__b1j_2b, h_mh_b1j_b2j__b1j_4b,
                                                     h_mh_b1j_b2j__b2j_2b, h_mh_b1j_b2j__b2j_4b,
                                                     h_amh_b1j_b2j__2b, h_amh_b1j_b2j__4b,
                                                     h_dmh_b1j_b2j__2b, h_dmh_b1j_b2j__4b ) ;

   draw_mass_canvas( "mh_b1b2jj", "Mass (b1b2)(jj)", h_mh_b1b2_jj__b1b2_2b, h_mh_b1b2_jj__b1b2_4b,
                                                     h_mh_b1b2_jj__jj_2b, h_mh_b1b2_jj__jj_4b,
                                                     h_amh_b1b2_jj__2b, h_amh_b1b2_jj__4b,
                                                     h_dmh_b1b2_jj__2b, h_dmh_b1b2_jj__4b, 0 ) ;

   draw_mass_canvas( "mh_b1xb2j", "Mass (b1x)(b2j)", h_mh_b1x_b2j__b1x_2b, h_mh_b1x_b2j__b1x_4b,
                                                     h_mh_b1x_b2j__b2j_2b, h_mh_b1x_b2j__b2j_4b,
                                                     h_amh_b1x_b2j__2b, h_amh_b1x_b2j__4b,
                                                     h_dmh_b1x_b2j__2b, h_dmh_b1x_b2j__4b ) ;

   draw_mass_canvas( "mh_b1jb2x", "Mass (b1j)(b2x)", h_mh_b1j_b2x__b1j_2b, h_mh_b1j_b2x__b1j_4b,
                                                     h_mh_b1j_b2x__b2x_2b, h_mh_b1j_b2x__b2x_4b,
                                                     h_amh_b1j_b2x__2b, h_amh_b1j_b2x__4b,
                                                     h_dmh_b1j_b2x__2b, h_dmh_b1j_b2x__4b ) ;

   draw_mass_canvas( "mh_b1b2jx", "Mass (b1b2)(jx)", h_mh_b1b2_jx__b1b2_2b, h_mh_b1b2_jx__b1b2_4b,
                                                     h_mh_b1b2_jx__jx_2b, h_mh_b1b2_jx__jx_4b,
                                                     h_amh_b1b2_jx__2b, h_amh_b1b2_jx__4b,
                                                     h_dmh_b1b2_jx__2b, h_dmh_b1b2_jx__4b ) ;

   draw_mass_canvas( "mh_b1xb2x", "Mass (b1x)(b2x)", h_mh_b1x_b2x__b1x_2b, h_mh_b1x_b2x__b1x_4b,
                                                     h_mh_b1x_b2x__b2x_2b, h_mh_b1x_b2x__b2x_4b,
                                                     h_amh_b1x_b2x__2b, h_amh_b1x_b2x__4b,
                                                     h_dmh_b1x_b2x__2b, h_dmh_b1x_b2x__4b ) ;

   draw_mass_canvas( "mh_all_spt", "Mass, sum pt rank",  h_mh_all__spth_2b, h_mh_all__spth_4b,
                                                     h_mh_all__sptl_2b, h_mh_all__sptl_4b,
                                                     h_amh_all__2b, h_amh_all__4b,
                                                     h_dmh_all__2b, h_dmh_all__4b ) ;

   draw_mass_canvas( "mh_all_spt_ms40", "Mass, sum pt rank, METsig>40",  h_mh_all__spth_2b_ms40, h_mh_all__spth_4b_ms40,
                                                     h_mh_all__sptl_2b_ms40, h_mh_all__sptl_4b_ms40,
                                                     h_amh_all__2b_ms40, h_amh_all__4b_ms40,
                                                     h_dmh_all__2b_ms40, h_dmh_all__4b_ms40 ) ;

   draw_mass_canvas( "mh_all_spt_ms85", "Mass, sum pt rank, METsig>85",  h_mh_all__spth_2b_ms85, h_mh_all__spth_4b_ms85,
                                                     h_mh_all__sptl_2b_ms85, h_mh_all__sptl_4b_ms85,
                                                     h_amh_all__2b_ms85, h_amh_all__4b_ms85,
                                                     h_dmh_all__2b_ms85, h_dmh_all__4b_ms85 ) ;

   draw_mass_canvas( "mh_all_spt_4j", "Mass sum pt rank, Njets=4", h_mh_all__spth_2b_4j, h_mh_all__spth_4b_4j,
                                                     h_mh_all__sptl_2b_4j, h_mh_all__sptl_4b_4j,
                                                     h_amh_all__2b_4j, h_amh_all__4b_4j,
                                                     h_dmh_all__2b_4j, h_dmh_all__4b_4j ) ;

   draw_mass_canvas( "mh_all_spt_5j", "Mass sum pt rank, Njets=5", h_mh_all__spth_2b_5j, h_mh_all__spth_4b_5j,
                                                     h_mh_all__sptl_2b_5j, h_mh_all__sptl_4b_5j,
                                                     h_amh_all__2b_5j, h_amh_all__4b_5j,
                                                     h_dmh_all__2b_5j, h_dmh_all__4b_5j ) ;

 //=====================

   draw_pt_canvas( "pt_all", "jet pt, all",
                    h_pt_highest_csv_2b, h_pt_highest_csv_4b,
                    h_pt_nexthighest_csv_2b, h_pt_nexthighest_csv_4b,
                    h_pt_nextlowest_csv_2b, h_pt_nextlowest_csv_4b,
                    h_pt_lowest_csv_2b, h_pt_lowest_csv_4b ) ;

   draw_pt_canvas_h( "pt_all_h", "jet pt, all",
                    h_pt_highest_csv_2b, h_pt_highest_csv_4b,
                    h_pt_nexthighest_csv_2b, h_pt_nexthighest_csv_4b,
                    h_pt_nextlowest_csv_2b, h_pt_nextlowest_csv_4b,
                    h_pt_lowest_csv_2b, h_pt_lowest_csv_4b ) ;

   draw_pt_canvas3( "pt_all_w3b", "jet pt, all",
                    h_pt_highest_csv_2b, h_pt_highest_csv_4b, h_pt_highest_csv_3b,
                    h_pt_nexthighest_csv_2b, h_pt_nexthighest_csv_4b, h_pt_nexthighest_csv_3b,
                    h_pt_nextlowest_csv_2b, h_pt_nextlowest_csv_4b, h_pt_nextlowest_csv_3b,
                    h_pt_lowest_csv_2b, h_pt_lowest_csv_4b, h_pt_lowest_csv_3b ) ;

   draw_pt_canvas( "pt_all_ptrw", "jet pt, all, 2b pt reweighted",
                    h_pt_highest_csv_2b_ptrw, h_pt_highest_csv_4b,
                    h_pt_nexthighest_csv_2b_ptrw, h_pt_nexthighest_csv_4b,
                    h_pt_nextlowest_csv_2b_ptrw, h_pt_nextlowest_csv_4b,
                    h_pt_lowest_csv_2b_ptrw, h_pt_lowest_csv_4b ) ;

   draw_pt_canvas_h( "pt_all_h_ptrw", "jet pt, all, 2b pt reweighted",
                    h_pt_highest_csv_2b_ptrw, h_pt_highest_csv_4b,
                    h_pt_nexthighest_csv_2b_ptrw, h_pt_nexthighest_csv_4b,
                    h_pt_nextlowest_csv_2b_ptrw, h_pt_nextlowest_csv_4b,
                    h_pt_lowest_csv_2b_ptrw, h_pt_lowest_csv_4b ) ;


   draw_hspt_canvas( "higgs_sumpt_all", "higgs sum pt of daughters, all",
                       h_hspt_higher_2b, h_hspt_higher_4b,
                       h_hspt_lower_2b, h_hspt_lower_4b ) ;

   draw_hspt_canvas( "higgs_sumpt_all_ptrw", "higgs sum pt of daughters, all, 2b pt reweighted",
                       h_hspt_higher_2b_ptrw, h_hspt_higher_4b,
                       h_hspt_lower_2b_ptrw, h_hspt_lower_4b ) ;



 //=====================

   float maxRatio(0.50) ;

   gStyle -> SetOptStat(0) ;
   gStyle -> SetPadGridY(1) ;
   gStyle -> SetTitleW(0.50) ;
   gStyle -> SetTitleH(0.07) ;


   TString title ;



 //----

   {
      TCanvas* c_ratio_vs_met_4j = new TCanvas("c_ratio_vs_met_4j", "Higgs mass SIG/SB ratio vs METsig, Njets=4", 600, 400 ) ;

      TH1F* hra = h_metsig_rmsigsb_2b_4j ;
      TH1F* hrb = h_metsig_rmsigsb_4b_4j ;
      TH1F* hrc = h_metsig_rmsigsb_3b_4j ;

      TH1F* hrbs = shiftHist( hrb, 1.0 ) ;
      TH1F* hrcs = shiftHist( hrc, 2.0 ) ;

      TLegend* legend = new TLegend( 0.40, 0.70, 0.60, 0.87 ) ;
      legend -> SetFillColor( kWhite ) ;
      legend -> AddEntry( hra, "2b") ;
      legend -> AddEntry( hrbs, "4b") ;
      legend -> AddEntry( hrcs, "3b") ;

      TString ts_sn = TString(", ") + TString( samplename ) ;

      title = hra -> GetTitle() + ts_sn ;
      title.ReplaceAll(", 2b"," ") ;
      hra -> SetTitle( title ) ;
      hra -> SetLineWidth(2) ;
      hrbs-> SetLineWidth(2) ;
      hrcs-> SetLineWidth(2) ;
      hra -> SetLineColor(4) ;
      hrbs-> SetLineColor(2) ;
      hrcs-> SetLineColor(1) ;

      hra -> SetMaximum(maxRatio) ;
      hra -> SetXTitle("METsig") ;
      hra -> SetYTitle("Higgs mass SIG/SB ratio") ;
      hra -> SetTitleOffset(1.1,"y") ;
      hra -> SetTitleSize(0.05,"y") ;

      hra -> Draw() ;
      hrbs-> Draw("same") ;
      hrcs-> Draw("same") ;

      legend -> Draw() ;

      char fname[10000] ;
      sprintf( fname, "outputfiles/ratio-vs-met-4j-%s.pdf", samplename ) ;
      c_ratio_vs_met_4j -> SaveAs( fname ) ;
   }

 //----

   {
      TCanvas* c_ratio_vs_met_5j = new TCanvas("c_ratio_vs_met_5j", "Higgs mass SIG/SB ratio vs METsig, Njets=5", 600, 400 ) ;

      TH1F* hra = h_metsig_rmsigsb_2b_5j ;
      TH1F* hrb = h_metsig_rmsigsb_4b_5j ;
      TH1F* hrc = h_metsig_rmsigsb_3b_5j ;

      TH1F* hrbs = shiftHist( hrb, 1.0 ) ;
      TH1F* hrcs = shiftHist( hrc, 2.0 ) ;

      TLegend* legend = new TLegend( 0.40, 0.70, 0.60, 0.87 ) ;
      legend -> SetFillColor( kWhite ) ;
      legend -> AddEntry( hra, "2b") ;
      legend -> AddEntry( hrbs, "4b") ;
      legend -> AddEntry( hrcs, "3b") ;

      TString ts_sn = TString(", ") + TString( samplename ) ;

      title = hra -> GetTitle() + ts_sn ;
      title.ReplaceAll(", 2b"," ") ;
      hra -> SetTitle( title ) ;
      hra -> SetLineWidth(2) ;
      hrbs-> SetLineWidth(2) ;
      hrcs-> SetLineWidth(2) ;
      hra -> SetLineColor(4) ;
      hrbs-> SetLineColor(2) ;
      hrcs-> SetLineColor(1) ;

      hra -> SetMaximum(maxRatio) ;
      hra -> SetXTitle("METsig") ;
      hra -> SetYTitle("Higgs mass SIG/SB ratio") ;
      hra -> SetTitleOffset(1.1,"y") ;
      hra -> SetTitleSize(0.05,"y") ;

      hra -> Draw() ;
      hrbs-> Draw("same") ;
      hrcs-> Draw("same") ;

      legend -> Draw() ;

      char fname[10000] ;
      sprintf( fname, "outputfiles/ratio-vs-met-5j-%s.pdf", samplename ) ;
      c_ratio_vs_met_5j -> SaveAs( fname ) ;
   }

 //----

   {
      TCanvas* c_ratio_vs_met_ave = new TCanvas("c_ratio_vs_met_ave", "Higgs mass SIG/SB ratio vs METsig", 600, 400 ) ;

      TH1F* hra = h_metsig_rmsigsb_2b ;
      TH1F* hrb = h_metsig_rmsigsb_4b ;

      TH1F* hra2 = shiftHist( h_metsig_rmsigsb_2b_NjetReweight, 1.0 ) ;
      TH1F* hra3 = shiftHist( h_metsig_rmsigsb_2b_NjetReweight_ptrw, 2.0 ) ;
      TH1F* hrbs = shiftHist( hrb, 3.0 ) ;

      TLegend* legend = new TLegend( 0.40, 0.70, 0.85, 0.87 ) ;
      legend -> SetFillColor( kWhite ) ;
      legend -> AddEntry( hra, "2b") ;
      legend -> AddEntry( hra2, "2b, Njet reweighted") ;
      legend -> AddEntry( hra3, "2b, Njet and jetpt reweighted") ;
      legend -> AddEntry( hrbs, "4b") ;

      TString ts_sn = TString(", ") + TString( samplename ) ;

      title = hra -> GetTitle() + ts_sn ;
      title.ReplaceAll(", 2b"," ") ;
      hra -> SetTitle( title ) ;
      hra -> SetLineWidth(2) ;
      hra2-> SetLineWidth(2) ;
      hra3-> SetLineWidth(2) ;
      hrbs-> SetLineWidth(2) ;
      hra -> SetLineStyle(2) ;
      hra2-> SetLineStyle(3) ;
      hra3-> SetLineStyle(1) ;
      hra -> SetLineColor(4) ;
      hra2-> SetLineColor(4) ;
      hra3-> SetLineColor(4) ;
      hrbs-> SetLineColor(2) ;

      hra -> SetMaximum(maxRatio) ;
      hra -> SetXTitle("METsig") ;
      hra -> SetYTitle("Higgs mass SIG/SB ratio") ;
      hra -> SetTitleOffset(1.1,"y") ;
      hra -> SetTitleSize(0.05,"y") ;

      hra -> Draw() ;
      hra2-> Draw("same") ;
      hra3-> Draw("same") ;
      hrbs-> Draw("same") ;

      legend -> Draw() ;

      char fname[10000] ;
      sprintf( fname, "outputfiles/ratio-vs-met-ave-%s.pdf", samplename ) ;
      c_ratio_vs_met_ave -> SaveAs( fname ) ;
   }

 //----

   {
      TCanvas* c_ratio_vs_met = new TCanvas("c_ratio_vs_met", "Higgs mass SIG/SB ratio vs METsig", 600, 400 ) ;

      TH1F* hra = h_metsig_rmsigsb_2b ;
      TH1F* hrb = h_metsig_rmsigsb_4b ;
      TH1F* hrc = h_metsig_rmsigsb_3b ;

      TH1F* hrbs = shiftHist( hrb, 3.0 ) ;
      TH1F* hrcs = shiftHist( hrc, 2.0 ) ;

      TLegend* legend = new TLegend( 0.40, 0.70, 0.85, 0.87 ) ;
      legend -> SetFillColor( kWhite ) ;
      legend -> AddEntry( hra, "2b") ;
      legend -> AddEntry( hrbs, "4b") ;
      legend -> AddEntry( hrcs, "3b") ;

      TString ts_sn = TString(", ") + TString( samplename ) ;

      ///// title = hra -> GetTitle() + ts_sn ;
      ///// title.ReplaceAll(", 2b"," ") ;
      hra -> SetTitle( title ) ;
      hra -> SetLineWidth(2) ;
      hrbs-> SetLineWidth(2) ;
      hrcs-> SetLineWidth(2) ;
      hra -> SetLineStyle(2) ;
      hra -> SetLineColor(4) ;
      hrbs-> SetLineColor(2) ;
      hrcs-> SetLineColor(1) ;

      hra -> SetMaximum(maxRatio) ;
      hra -> SetXTitle("METsig") ;
      hra -> SetYTitle("Higgs mass SIG/SB ratio") ;
      hra -> SetTitleOffset(1.1,"y") ;
      hra -> SetTitleSize(0.05,"y") ;

      hra -> Draw() ;
      hrbs-> Draw("same") ;
      hrcs-> Draw("same") ;

      legend -> Draw() ;

      char fname[10000] ;
      sprintf( fname, "outputfiles/ratio-vs-met-w3b-%s.pdf", samplename ) ;
      c_ratio_vs_met -> SaveAs( fname ) ;
   }

 //----

   {
      gStyle -> SetOptStat(0) ;
      gStyle -> SetPadGridX(1) ;
      gStyle -> SetPadGridY(1) ;
      gStyle -> SetTitleW(0.7) ;

      TCanvas* c_btag_eff = new TCanvas("c_btag_eff", "btag efficiency, 3rd and 4th tags", 1100, 500 ) ;

      c_btag_eff -> Divide(2,1) ;

      TH1F* ha = h_pt_nextlowest_csv_cb__passmed_eff ;
      TH1F* hb = h_pt_lowest_csv_cb__passloose_eff ;

      ha -> SetTitle( ha->GetTitle() + TString(", ") + TString( samplename ) ) ;
      hb -> SetTitle( hb->GetTitle() + TString(", ") + TString( samplename ) ) ;

      ha -> SetLineWidth(2) ;
      hb -> SetLineWidth(2) ;

      ha -> SetMinimum(0.00) ;
      ha -> SetMaximum(0.40) ;
      ha -> SetXTitle("jet pt (GeV)") ;
      ha -> SetYTitle("CSV medium tag efficiency") ;
      ha -> SetTitleOffset(1.1,"y") ;
      ha -> SetTitleSize(0.05,"y") ;
      ha -> SetMarkerStyle(20) ;

      hb -> SetMinimum(0.00) ;
      hb -> SetMaximum(0.40) ;
      hb -> SetXTitle("jet pt (GeV)") ;
      hb -> SetYTitle("CSV loose tag efficiency") ;
      hb -> SetTitleOffset(1.1,"y") ;
      hb -> SetTitleSize(0.05,"y") ;
      hb -> SetMarkerStyle(20) ;

      c_btag_eff -> cd(1) ;
      ha -> Draw() ;

      c_btag_eff -> cd(2) ;
      hb -> Draw() ;


      char fname[10000] ;
      sprintf( fname, "outputfiles/btag_eff-%s.pdf", samplename ) ;
      c_btag_eff -> SaveAs( fname ) ;
   }

 //----

   {
      gStyle -> SetOptStat("eM") ;
      gStyle -> SetPadGridX(1) ;
      gStyle -> SetPadGridY(1) ;
      gStyle -> SetTitleW(0.7) ;

      TCanvas* c_njet_eff = new TCanvas("c_njet_eff_3", "Njets", 1100, 500 ) ;

      c_njet_eff -> Divide(3,1) ;

      TH1F* ha = h_njets_2b ;
      TH1F* hb = h_njets_4b ;
      TH1F* hc = h_njets_3b ;

      ha -> SetTitle( ha->GetTitle() + TString(", ") + TString( samplename ) ) ;
      hb -> SetTitle( hb->GetTitle() + TString(", ") + TString( samplename ) ) ;
      hc -> SetTitle( hc->GetTitle() + TString(", ") + TString( samplename ) ) ;

      ha -> SetLineWidth(2) ;
      hb -> SetLineWidth(2) ;
      hc -> SetLineWidth(2) ;
      ha -> SetLineColor(4) ;
      hb -> SetLineColor(2) ;
      hc -> SetLineColor(1) ;

      ha -> SetXTitle("Njets, pt>30") ;
      hb -> SetXTitle("Njets, pt>30") ;
      hc -> SetXTitle("Njets, pt>30") ;

      c_njet_eff -> cd(1) ;
      ha -> Draw() ;

      c_njet_eff -> cd(2) ;
      hb -> Draw() ;

      c_njet_eff -> cd(3) ;
      hc -> Draw() ;

      c_njet_eff -> Update() ; c_njet_eff -> Draw() ;

      char fname[10000] ;
      sprintf( fname, "outputfiles/njets-3-%s.pdf", samplename ) ;
      c_njet_eff -> SaveAs( fname ) ;
   }

 //----

   {
      gStyle -> SetOptStat("eM") ;
      gStyle -> SetPadGridX(1) ;
      gStyle -> SetPadGridY(1) ;
      gStyle -> SetTitleW(0.5) ;
      TPaveStats *st1(0x0), *st2(0x0) ;
      float sx1(0.70), sy1(0.80), sx2(0.99), sy2(0.95) ;

      TCanvas* c_njet_eff = new TCanvas("c_njet_eff", "Njets", 1100, 500 ) ;

      c_njet_eff -> Divide(2,1) ;

      TH1F* ha = h_njets_2b ;
      TH1F* hb = h_njets_4b ;

      st1 = (TPaveStats*) ha -> FindObject("stats") ;
      st2 = (TPaveStats*) hb -> FindObject("stats") ;
      st1 -> SetX1NDC( sx1 ) ; st1 -> SetY1NDC( sy1 ) ; st1 -> SetX2NDC( sx2 ) ; st1 -> SetY2NDC( sy2 ) ; st1 -> SetTextColor( 4 ) ;
      st2 -> SetX1NDC( sx1 ) ; st2 -> SetY1NDC( sy1 ) ; st2 -> SetX2NDC( sx2 ) ; st2 -> SetY2NDC( sy2 ) ; st2 -> SetTextColor( 2 ) ;

      ha -> SetTitle( ha->GetTitle() + TString(", ") + TString( samplename ) ) ;
      hb -> SetTitle( hb->GetTitle() + TString(", ") + TString( samplename ) ) ;

      ha -> SetLineWidth(2) ;
      hb -> SetLineWidth(2) ;
      ha -> SetLineColor(4) ;
      hb -> SetLineColor(2) ;

      ha -> SetXTitle("Njets, pt>30") ;
      hb -> SetXTitle("Njets, pt>30") ;

      c_njet_eff -> cd(1) ;
      ha -> Draw() ;

      c_njet_eff -> cd(2) ;
      hb -> Draw() ;

      char fname[10000] ;
      sprintf( fname, "outputfiles/njets-%s.pdf", samplename ) ;
      c_njet_eff -> SaveAs( fname ) ;
   }

 //----

   {

      gStyle -> SetOptStat(0) ;
      gStyle -> SetPadGridX(0) ;
      gStyle -> SetPadGridY(0) ;

      THStack* h_ptstack = new THStack("h_ptstack", "Non-top-daughter jet" ) ;

      h_xjet_pt_nomatch -> SetFillColor( 42 ) ;
      h_xjet_pt_gluon   -> SetFillColor( 46 ) ;
      h_xjet_pt_quark   -> SetFillColor( 48 ) ;

      h_bjet_pt -> SetFillColor(11) ;
      h_jx_wjet_pt -> SetFillColor(11) ;

      h_bjet_pt -> SetTitle("b jet from top decay") ;
      h_jx_wjet_pt -> SetTitle("W daugher jet") ;

      h_ptstack -> Add( h_xjet_pt_quark ) ;
      h_ptstack -> Add( h_xjet_pt_gluon ) ;
      h_ptstack -> Add( h_xjet_pt_nomatch ) ;

      TLegend* xlegend = new TLegend( 0.50, 0.65, 0.85, 0.85 ) ;
      xlegend->AddEntry( h_xjet_pt_nomatch, "no match" ) ;
      xlegend->AddEntry( h_xjet_pt_gluon, "gluon" ) ;
      xlegend->AddEntry( h_xjet_pt_quark, "quark" ) ;

      h_bjet_pt -> SetXTitle("jet pt (GeV)") ;
      h_jx_wjet_pt -> SetXTitle("jet pt (GeV)") ;
      h_xjet_pt_quark -> SetXTitle("jet pt (GeV)") ;
      h_xjet_pt_gluon -> SetXTitle("jet pt (GeV)") ;
      h_xjet_pt_nomatch -> SetXTitle("jet pt (GeV)") ;


      TCanvas* c_jet_pt = new TCanvas("c_jet_pt", "Njets", 1100, 350 ) ;

      c_jet_pt -> Divide(3,1) ;

      c_jet_pt -> cd(1) ;
      h_bjet_pt -> Draw() ;

      c_jet_pt -> cd(2) ;
      h_jx_wjet_pt -> Draw() ;

      c_jet_pt -> cd(3) ;
      h_ptstack -> Draw() ;
      xlegend -> Draw() ;
      TText* text = new TText() ;
      text->SetTextSize(0.035) ;
      text->DrawTextNDC( 0.75,0.03,"jet pt (GeV)" ) ;

      char fname[10000] ;
      sprintf( fname, "outputfiles/truth-match-jetpt-%s.pdf", samplename ) ;
      c_jet_pt -> SaveAs( fname ) ;

   }

 //----

   {
      char eff_filename[10000] ;

      sprintf( eff_filename, "outputfiles/btag-eff-vs-pt--nextlowest-csv-passmed--%s.txt", samplename ) ;
      write_btageff_file( h_pt_nextlowest_csv_cb__passmed_eff, eff_filename ) ;

      sprintf( eff_filename, "outputfiles/btag-eff-vs-pt--lowest-csv-passloose--%s.txt", samplename ) ;
      write_btageff_file( h_pt_lowest_csv_cb__passloose_eff, eff_filename ) ;
   }

   {
      char weight_filename[10000] ;
      sprintf( weight_filename, "outputfiles/sumpt-weight--%s.txt", samplename ) ;
      write_weight_sumpt( h_sumpt__weight, weight_filename ) ;
   }

   gStyle -> SetOptStat("eMR") ;

} // truthstudy1::Loop()

//====================================================

void labelCodeBins( TH1* hp ) {
   if ( hp == 0x0 ) return ;
   TAxis* axis = hp->GetXaxis() ;
   if ( axis == 0x0 ) return ;

   axis->SetBinLabel(  0+1, "Other" ) ;
   axis->SetBinLabel(  1+1, "(b1 j) (b2 j)" ) ;
   axis->SetBinLabel(  2+1, "(b1 b2) (j j)" ) ;
   axis->SetBinLabel(  3+1, "(b1 x) (b2 j)" ) ;
   axis->SetBinLabel(  4+1, "(b1 j) (b2 x)" ) ;
   axis->SetBinLabel(  5+1, "(b1 b2) (j x)" ) ;
   axis->SetBinLabel(  6+1, "(b1 x) (b2 x)" ) ;
   axis->SetBinLabel(  7+1, "(b1 b2) (x x)" ) ;
   axis->SetBinLabel(  8+1, "(b2 x) (j x)" ) ;
   axis->SetBinLabel(  9+1, "(x j) (b2 j)" ) ;
   axis->SetBinLabel( 10+1, "(x x) (j j)" ) ;
   axis->SetBinLabel( 11+1, "(b1 x) (j x)" ) ;
   axis->SetBinLabel( 12+1, "(b1 x) (j j)" ) ;
   axis->SetBinLabel( 13+1, "(b2 x) (j j)" ) ;
   axis->SetBinLabel( 14+1, "(b1 j) (x x)" ) ;
   axis->SetBinLabel( 15+1, "(x x) (b2 j)" ) ;
   axis->SetBinLabel( 16+1, "(b1 j) (x j)" ) ;

   hp->SetLabelSize(0.06,"x") ;
   axis->LabelsOption("v") ;
}

//====================================================

void fillratio( TH1* hn, TH1* hd, TH1* hr ) {

   if ( hn==0x0 || hd==0x0 || hr==0x0 ) return ;

   int nb = hn->GetNbinsX() ;

   for ( int bi=1; bi<=nb; bi++ ) {

      float nv = hn -> GetBinContent( bi ) ;
      float ne = hn -> GetBinError( bi ) ;

      float dv = hd -> GetBinContent( bi ) ;
      float de = hd -> GetBinError( bi ) ;

      float rv(0.) ;
      float re(0.) ;
      if ( dv > 0 ) {
         rv = nv / dv ;
         if ( nv > 0 && ne > 0 && dv > 0 && de > 0 ) {
            re = rv * sqrt( pow(ne/nv,2) + pow(de/dv,2) ) ;
         }
      }
      hr -> SetBinContent( bi, rv ) ;
      hr -> SetBinError( bi, re ) ;

   } // bi

   float inval = hn -> Integral() ;
   float idval = hd -> Integral() ;

   float aveRval(0.), aveRerr(0.) ;
   if ( idval > 0 ) { aveRval = inval / idval ; }
   if ( idval > 0 && inval > 0 ) { aveRerr = aveRval * sqrt( 1./ inval + 1./idval ) ; }

   printf("\n\n Ave ratio: %s : Rsigsb = %.3f +/- %.3f\n\n",
      hr->GetTitle(), aveRval, aveRerr ) ;

} // fillratio


//====================================================

void fillratioReweight( TH1* hn4j, TH1* hd4j, TH1* hn5j, TH1* hd5j, float w4j, float w5j, TH1* hr ) {

   if ( hn4j==0x0 || hd4j==0x0 || hn5j==0x0 || hd5j==0x0 || hr==0x0 ) return ;

   int nb = hn4j->GetNbinsX() ;

   for ( int bi=1; bi<=nb; bi++ ) {

      float nv4j = hn4j -> GetBinContent( bi ) ;
      float ne4j = hn4j -> GetBinError( bi ) ;

      float dv4j = hd4j -> GetBinContent( bi ) ;
      float de4j = hd4j -> GetBinError( bi ) ;

      float nv5j = hn5j -> GetBinContent( bi ) ;
      float ne5j = hn5j -> GetBinError( bi ) ;

      float dv5j = hd5j -> GetBinContent( bi ) ;
      float de5j = hd5j -> GetBinError( bi ) ;

      float wrv(0.) ;
      float wre(0.) ;

      float wnv = w4j * nv4j + w5j * nv5j ;
      float wdv = w4j * dv4j + w5j * dv5j ;

      if ( wdv > 0 ) {
         wrv = wnv / wdv ;
         wre = sqrt( pow( (w4j/wdv) * ne4j ,2 )  +  pow( (w5j/wdv) * ne5j ,2 )  +  pow( (wrv/wdv) * w4j * de4j ,2 )  +  pow( (wrv/wdv) * w5j * de5j ,2 )  ) ;
      }
      hr -> SetBinContent( bi, wrv ) ;
      hr -> SetBinError( bi, wre ) ;

   } // bi

   float inval4j = hn4j -> Integral() ;
   float idval4j = hd4j -> Integral() ;

   float inval5j = hn5j -> Integral() ;
   float idval5j = hd5j -> Integral() ;

   float aveRval(0.), aveRerr(0.) ;

   float aveNval = w4j * inval4j + w5j * inval5j ;
   float aveDval = w4j * idval4j + w5j * idval5j ;
   if ( aveDval > 0 ) {
      aveRval = aveNval / aveDval ;
      aveRerr = sqrt( pow( (w4j/aveDval) * sqrt(inval4j) ,2 )  +  pow( (w5j/aveDval) * sqrt(inval5j) ,2 )  +  pow( (aveRval/aveDval) * w4j * sqrt(idval4j) ,2 )  +  pow( (aveRval/aveDval) * w5j * sqrt(idval5j) ,2 )  ) ;
   }

   printf("\n\n Ave ratio: %s : Rsigsb = %.3f +/- %.3f\n\n",
      hr->GetTitle(), aveRval, aveRerr ) ;

} // fillratioReweight


//====================================================

void filldistReweight( TH1* h4j, TH1* h5j, float w4j, float w5j, TH1* hr ) {

   if ( h4j==0x0 || h5j==0x0 || hr==0x0 ) return ;

   h4j -> Sumw2() ;
   h5j -> Sumw2() ;

   hr -> Add( h4j, w4j ) ;
   hr -> Add( h5j, w5j ) ;


} // filldistReweight



//====================================================

void truthstudy1::draw_mass_canvas( const char* cname, const char* ctitle, TH1* hm1a, TH1* hm1b, TH1* hm2a, TH1* hm2b, TH1* havema, TH1* havemb, TH1* hdma, TH1* hdmb, bool setmax ) {

   float s1x1(0.70), s1y1(0.70), s1x2(0.99), s1y2(0.95) ;
   float s2x1(0.70), s2y1(0.40), s2x2(0.99), s2y2(0.65) ;
   TPaveStats *st1(0x0), *st2(0x0) ;

   TLine line ;


   if ( hm1a == 0x0 || hm1b == 0x0 || hm2a == 0x0 || hm2b == 0x0 || havema == 0x0 || havemb == 0x0 || hdma == 0x0 || hdmb == 0x0 ) return ;

   hm1a -> Sumw2() ;
   hm1b -> Sumw2() ;
   hm2a -> Sumw2() ;
   hm2b -> Sumw2() ;
   havema -> Sumw2() ;
   havemb -> Sumw2() ;
   hdma -> Sumw2() ;
   hdmb -> Sumw2() ;

   if ( hm1a->Integral() > 0 ) hm1a -> Scale( 1./(hm1a->Integral()) ) ;
   if ( hm1b->Integral() > 0 ) hm1b -> Scale( 1./(hm1b->Integral()) ) ;
   if ( hm2a->Integral() > 0 ) hm2a -> Scale( 1./(hm2a->Integral()) ) ;
   if ( hm2b->Integral() > 0 ) hm2b -> Scale( 1./(hm2b->Integral()) ) ;
   if ( havema->Integral() > 0 ) havema -> Scale( 1./(havema->Integral()) ) ;
   if ( havemb->Integral() > 0 ) havemb -> Scale( 1./(havemb->Integral()) ) ;
   if ( hdma->Integral() > 0 ) hdma -> Scale( 1./(hdma->Integral()) ) ;
   if ( hdmb->Integral() > 0 ) hdmb -> Scale( 1./(hdmb->Integral()) ) ;

   float maxsf(1.4) ;

   if ( setmax ) {
      hm1a -> SetMaximum( 0.20 ) ;
      hm1b -> SetMaximum( 0.20 ) ;
      hm2a -> SetMaximum( 0.20 ) ;
      hm2b -> SetMaximum( 0.20 ) ;
      havema -> SetMaximum( 0.20 ) ;
      havemb -> SetMaximum( 0.20 ) ;
      hdma -> SetMaximum( 0.16 ) ;
      hdmb -> SetMaximum( 0.16 ) ;
   } else {
      hm1a -> SetMaximum( maxsf * hm1a->GetMaximum() ) ;
      hm1b -> SetMaximum( maxsf * hm1b->GetMaximum() ) ;
      hm2a -> SetMaximum( maxsf * hm2a->GetMaximum() ) ;
      hm2b -> SetMaximum( maxsf * hm2b->GetMaximum() ) ;
      havema -> SetMaximum( maxsf * havema->GetMaximum() ) ;
      havemb -> SetMaximum( maxsf * havemb->GetMaximum() ) ;
      hdma -> SetMaximum( maxsf * hdma->GetMaximum() ) ;
      hdmb -> SetMaximum( maxsf * hdmb->GetMaximum() ) ;
   }

   hm1a -> SetLineColor(4) ;
   hm1b -> SetLineColor(2) ;
   hm2a -> SetLineColor(4) ;
   hm2b -> SetLineColor(2) ;
   havema -> SetLineColor(4) ;
   havemb -> SetLineColor(2) ;
   hdma -> SetLineColor(4) ;
   hdmb -> SetLineColor(2) ;

   hm1a -> SetLineWidth(2) ;
   hm1b -> SetLineWidth(2) ;
   hm2a -> SetLineWidth(2) ;
   hm2b -> SetLineWidth(2) ;
   havema -> SetLineWidth(2) ;
   havemb -> SetLineWidth(2) ;
   hdma -> SetLineWidth(2) ;
   hdmb -> SetLineWidth(2) ;

   hm1a -> SetXTitle("mh (GeV)") ;
   hm2a -> SetXTitle("mh (GeV)") ;
   havema -> SetXTitle("ave mh (GeV)") ;
   hdma -> SetXTitle("delta mh (GeV)") ;

   hm1a -> SetTitleSize( 0.05 ) ;
   hm2a -> SetTitleSize( 0.05 ) ;
   havema -> SetTitleSize( 0.05 ) ;
   hdma -> SetTitleSize( 0.05 ) ;

   hm1a -> SetLabelSize( 0.05, "x" ) ;
   hm2a -> SetLabelSize( 0.05, "x" ) ;
   havema -> SetLabelSize( 0.05, "x" ) ;
   hdma -> SetLabelSize( 0.05, "x" ) ;

   hm1a -> SetLabelSize( 0.05, "y" ) ;
   hm2a -> SetLabelSize( 0.05, "y" ) ;
   havema -> SetLabelSize( 0.05, "y" ) ;
   hdma -> SetLabelSize( 0.05, "y" ) ;

   TString newtitle ;
   TString ts_sn = TString(", ") + TString( samplename ) ;

   newtitle = hm1a -> GetTitle() + ts_sn;
   newtitle.ReplaceAll(", 2b","") ;
   hm1a -> SetTitle( newtitle ) ;

   newtitle = hm2a -> GetTitle() + ts_sn;
   newtitle.ReplaceAll(", 2b","") ;
   hm2a -> SetTitle( newtitle ) ;

   newtitle = havema -> GetTitle() + ts_sn;
   newtitle.ReplaceAll(", 2b","") ;
   havema -> SetTitle( newtitle ) ;

   newtitle = hdma -> GetTitle() + ts_sn;
   newtitle.ReplaceAll(", 2b","") ;
   hdma -> SetTitle( newtitle ) ;

 //---

   gStyle -> SetOptStat("neMR") ;
   gStyle -> SetPadGridY(0) ;
   gStyle -> SetTitleW(0.60) ;
   gStyle -> SetTitleH(0.09) ;
   gStyle -> SetPadBottomMargin(0.10) ;
   gStyle -> SetTitleY(1.00) ;
   gStyle -> SetPadTopMargin(0.11) ;

   TCanvas* c_mass = new TCanvas( cname, ctitle, 500, 1000 ) ;

   c_mass -> Divide(1,4) ;

  //-- draw to create stats boxes.
   c_mass -> cd(1) ;
   hm1a -> Draw() ; c_mass -> Update() ; c_mass -> Draw() ;
   hm1b -> Draw() ; c_mass -> Update() ; c_mass -> Draw() ;
   hm2a -> Draw() ; c_mass -> Update() ; c_mass -> Draw() ;
   hm2b -> Draw() ; c_mass -> Update() ; c_mass -> Draw() ;
   havema -> Draw() ; c_mass -> Update() ; c_mass -> Draw() ;
   havemb -> Draw() ; c_mass -> Update() ; c_mass -> Draw() ;
   hdma -> Draw() ; c_mass -> Update() ; c_mass -> Draw() ;
   hdmb -> Draw() ; c_mass -> Update() ; c_mass -> Draw() ;


   c_mass -> cd(1) ;
   hm1a -> Draw("hist") ;
   hm1a -> Draw("e same") ;
   hm1b -> Draw("e same") ;
   st1 = (TPaveStats*) hm1a -> FindObject("stats") ;
   st2 = (TPaveStats*) hm1b -> FindObject("stats") ;
   st1 -> SetX1NDC( s1x1 ) ; st1 -> SetY1NDC( s1y1 ) ; st1 -> SetX2NDC( s1x2 ) ; st1 -> SetY2NDC( s1y2 ) ; st1 -> SetTextColor( 4 ) ;
   st2 -> SetX1NDC( s2x1 ) ; st2 -> SetY1NDC( s2y1 ) ; st2 -> SetX2NDC( s2x2 ) ; st2 -> SetY2NDC( s2y2 ) ; st2 -> SetTextColor( 2 ) ;
   line.SetLineStyle(1) ;
   line.DrawLine( 100., 0.,   100., hm1a->GetMaximum() ) ;
   line.DrawLine( 140., 0.,   140., hm1a->GetMaximum() ) ;
   line.SetLineStyle(2) ;
   line.DrawLine(  90., 0.,    90., hm1a->GetMaximum() ) ;
   line.DrawLine( 150., 0.,   150., hm1a->GetMaximum() ) ;

   c_mass -> cd(2) ;
   hm2a -> Draw("hist") ;
   hm2a -> Draw("e same") ;
   hm2b -> Draw("e same") ;
   st1 = (TPaveStats*) hm2a -> FindObject("stats") ;
   st2 = (TPaveStats*) hm2b -> FindObject("stats") ;
   st1 -> SetX1NDC( s1x1 ) ; st1 -> SetY1NDC( s1y1 ) ; st1 -> SetX2NDC( s1x2 ) ; st1 -> SetY2NDC( s1y2 ) ; st1 -> SetTextColor( 4 ) ;
   st2 -> SetX1NDC( s2x1 ) ; st2 -> SetY1NDC( s2y1 ) ; st2 -> SetX2NDC( s2x2 ) ; st2 -> SetY2NDC( s2y2 ) ; st2 -> SetTextColor( 2 ) ;
   line.SetLineStyle(1) ;
   line.DrawLine( 100., 0.,   100., hm2a->GetMaximum() ) ;
   line.DrawLine( 140., 0.,   140., hm2a->GetMaximum() ) ;
   line.SetLineStyle(2) ;
   line.DrawLine(  90., 0.,    90., hm2a->GetMaximum() ) ;
   line.DrawLine( 150., 0.,   150., hm2a->GetMaximum() ) ;

   c_mass -> cd(3) ;
   havema -> Draw("hist") ;
   havema -> Draw("e same") ;
   havemb -> Draw("e same") ;
   st1 = (TPaveStats*) havema -> FindObject("stats") ;
   st2 = (TPaveStats*) havemb -> FindObject("stats") ;
   st1 -> SetX1NDC( s1x1 ) ; st1 -> SetY1NDC( s1y1 ) ; st1 -> SetX2NDC( s1x2 ) ; st1 -> SetY2NDC( s1y2 ) ; st1 -> SetTextColor( 4 ) ;
   st2 -> SetX1NDC( s2x1 ) ; st2 -> SetY1NDC( s2y1 ) ; st2 -> SetX2NDC( s2x2 ) ; st2 -> SetY2NDC( s2y2 ) ; st2 -> SetTextColor( 2 ) ;
   line.SetLineStyle(1) ;
   line.DrawLine( 100., 0.,   100., havema->GetMaximum() ) ;
   line.DrawLine( 140., 0.,   140., havema->GetMaximum() ) ;
   line.SetLineStyle(2) ;
   line.DrawLine(  90., 0.,    90., havema->GetMaximum() ) ;
   line.DrawLine( 150., 0.,   150., havema->GetMaximum() ) ;

   c_mass -> cd(4) ;
   hdma -> Draw("hist") ;
   hdma -> Draw("e same") ;
   hdmb -> Draw("e same") ;
   st1 = (TPaveStats*) hdma -> FindObject("stats") ;
   st2 = (TPaveStats*) hdmb -> FindObject("stats") ;
   st1 -> SetX1NDC( s1x1 ) ; st1 -> SetY1NDC( s1y1 ) ; st1 -> SetX2NDC( s1x2 ) ; st1 -> SetY2NDC( s1y2 ) ; st1 -> SetTextColor( 4 ) ;
   st2 -> SetX1NDC( s2x1 ) ; st2 -> SetY1NDC( s2y1 ) ; st2 -> SetX2NDC( s2x2 ) ; st2 -> SetY2NDC( s2y2 ) ; st2 -> SetTextColor( 2 ) ;
   line.SetLineStyle(1) ;
   line.DrawLine( -20., 0.,   -20., hdma->GetMaximum() ) ;
   line.DrawLine(  20., 0.,    20., hdma->GetMaximum() ) ;
   line.SetLineStyle(2) ;
   line.DrawLine(  -30., 0.,    -30., hdma->GetMaximum() ) ;
   line.DrawLine(   30., 0.,     30., hdma->GetMaximum() ) ;

   c_mass -> Update() ;
   c_mass -> Draw() ;


   char fname[1000] ;
   sprintf( fname, "outputfiles/%s-%s.pdf", cname, samplename ) ;
   c_mass -> SaveAs( fname ) ;


} // draw_mass_canvas.

//====================================================

void truthstudy1::draw_pt_canvas( const char* cname, const char* ctitle, TH1* hptcsv1_2b, TH1* hptcsv1_4b,
                                                            TH1* hptcsv2_2b, TH1* hptcsv2_4b,
                                                            TH1* hptcsv3_2b, TH1* hptcsv3_4b,
                                                            TH1* hptcsv4_2b, TH1* hptcsv4_4b,
                                                            bool setmax ) {

   float s1x1(0.70), s1y1(0.70), s1x2(0.99), s1y2(0.95) ;
   float s2x1(0.70), s2y1(0.40), s2x2(0.99), s2y2(0.65) ;
   TPaveStats *st1(0x0), *st2(0x0) ;

    if ( hptcsv1_2b==0x0 || hptcsv1_4b==0x0 ) return ;
    if ( hptcsv2_2b==0x0 || hptcsv2_4b==0x0 ) return ;
    if ( hptcsv3_2b==0x0 || hptcsv3_4b==0x0 ) return ;
    if ( hptcsv4_2b==0x0 || hptcsv4_4b==0x0 ) return ;

    hptcsv1_2b -> Sumw2() ;  hptcsv1_4b -> Sumw2() ;
    hptcsv2_2b -> Sumw2() ;  hptcsv2_4b -> Sumw2() ;
    hptcsv3_2b -> Sumw2() ;  hptcsv3_4b -> Sumw2() ;
    hptcsv4_2b -> Sumw2() ;  hptcsv4_4b -> Sumw2() ;

    if ( hptcsv1_2b -> Integral() > 0 ) hptcsv1_2b -> Scale( 1./(hptcsv1_2b->Integral()) ) ;
    if ( hptcsv2_2b -> Integral() > 0 ) hptcsv2_2b -> Scale( 1./(hptcsv2_2b->Integral()) ) ;
    if ( hptcsv3_2b -> Integral() > 0 ) hptcsv3_2b -> Scale( 1./(hptcsv3_2b->Integral()) ) ;
    if ( hptcsv4_2b -> Integral() > 0 ) hptcsv4_2b -> Scale( 1./(hptcsv4_2b->Integral()) ) ;
    if ( hptcsv1_4b -> Integral() > 0 ) hptcsv1_4b -> Scale( 1./(hptcsv1_4b->Integral()) ) ;
    if ( hptcsv2_4b -> Integral() > 0 ) hptcsv2_4b -> Scale( 1./(hptcsv2_4b->Integral()) ) ;
    if ( hptcsv3_4b -> Integral() > 0 ) hptcsv3_4b -> Scale( 1./(hptcsv3_4b->Integral()) ) ;
    if ( hptcsv4_4b -> Integral() > 0 ) hptcsv4_4b -> Scale( 1./(hptcsv4_4b->Integral()) ) ;

    hptcsv1_2b -> SetLineWidth(2) ;
    hptcsv2_2b -> SetLineWidth(2) ;
    hptcsv3_2b -> SetLineWidth(2) ;
    hptcsv4_2b -> SetLineWidth(2) ;

    hptcsv1_4b -> SetLineWidth(2) ;
    hptcsv2_4b -> SetLineWidth(2) ;
    hptcsv3_4b -> SetLineWidth(2) ;
    hptcsv4_4b -> SetLineWidth(2) ;

    hptcsv1_2b -> SetLineColor(4) ;
    hptcsv2_2b -> SetLineColor(4) ;
    hptcsv3_2b -> SetLineColor(4) ;
    hptcsv4_2b -> SetLineColor(4) ;

    hptcsv1_4b -> SetLineColor(2) ;
    hptcsv2_4b -> SetLineColor(2) ;
    hptcsv3_4b -> SetLineColor(2) ;
    hptcsv4_4b -> SetLineColor(2) ;


    if ( setmax ) {
       hptcsv1_2b -> SetMaximum( 0.60 ) ;
       hptcsv2_2b -> SetMaximum( 0.60 ) ;
       hptcsv3_2b -> SetMaximum( 0.60 ) ;
       hptcsv4_2b -> SetMaximum( 0.60 ) ;
       hptcsv1_4b -> SetMaximum( 0.60 ) ;
       hptcsv2_4b -> SetMaximum( 0.60 ) ;
       hptcsv3_4b -> SetMaximum( 0.60 ) ;
       hptcsv4_4b -> SetMaximum( 0.60 ) ;
    }

   hptcsv1_2b -> SetXTitle("jet pt (GeV)") ;
   hptcsv2_2b -> SetXTitle("jet pt (GeV)") ;
   hptcsv3_2b -> SetXTitle("jet pt (GeV)") ;
   hptcsv4_2b -> SetXTitle("jet pt (GeV)") ;

   hptcsv1_2b -> SetTitleSize( 0.05 ) ;
   hptcsv2_2b -> SetTitleSize( 0.05 ) ;
   hptcsv3_2b -> SetTitleSize( 0.05 ) ;
   hptcsv4_2b -> SetTitleSize( 0.05 ) ;

   hptcsv1_2b -> SetLabelSize( 0.05, "x" ) ;
   hptcsv2_2b -> SetLabelSize( 0.05, "x" ) ;
   hptcsv3_2b -> SetLabelSize( 0.05, "x" ) ;
   hptcsv4_2b -> SetLabelSize( 0.05, "x" ) ;

   hptcsv1_2b -> SetLabelSize( 0.05, "y" ) ;
   hptcsv2_2b -> SetLabelSize( 0.05, "y" ) ;
   hptcsv3_2b -> SetLabelSize( 0.05, "y" ) ;
   hptcsv4_2b -> SetLabelSize( 0.05, "y" ) ;


   TString newtitle ;
   TString ts_sn = TString(", ") + TString( samplename ) ;

   newtitle = hptcsv1_2b -> GetTitle() + ts_sn ;
   newtitle.ReplaceAll(", 2b","") ;
   hptcsv1_2b -> SetTitle( newtitle ) ;

   newtitle = hptcsv2_2b -> GetTitle() + ts_sn ;
   newtitle.ReplaceAll(", 2b","") ;
   hptcsv2_2b -> SetTitle( newtitle ) ;

   newtitle = hptcsv3_2b -> GetTitle() + ts_sn ;
   newtitle.ReplaceAll(", 2b","") ;
   hptcsv3_2b -> SetTitle( newtitle ) ;

   newtitle = hptcsv4_2b -> GetTitle() + ts_sn ;
   newtitle.ReplaceAll(", 2b","") ;
   hptcsv4_2b -> SetTitle( newtitle ) ;


   gStyle -> SetOptStat("neMR") ;
   gStyle -> SetPadGridY(0) ;
   gStyle -> SetTitleW(0.60) ;
   gStyle -> SetTitleH(0.09) ;
   gStyle -> SetPadBottomMargin(0.10) ;
   gStyle -> SetTitleY(1.00) ;
   gStyle -> SetPadTopMargin(0.11) ;

   TCanvas* c_pt = new TCanvas( cname, ctitle, 500, 1000 ) ;

   c_pt -> Divide(1,4) ;

  //-- draw to create stats boxes.
   c_pt -> cd(1) ;
   hptcsv1_2b -> Draw() ; c_pt -> Update() ; c_pt -> Draw() ;
   hptcsv2_2b -> Draw() ; c_pt -> Update() ; c_pt -> Draw() ;
   hptcsv3_2b -> Draw() ; c_pt -> Update() ; c_pt -> Draw() ;
   hptcsv4_2b -> Draw() ; c_pt -> Update() ; c_pt -> Draw() ;
   hptcsv1_4b -> Draw() ; c_pt -> Update() ; c_pt -> Draw() ;
   hptcsv2_4b -> Draw() ; c_pt -> Update() ; c_pt -> Draw() ;
   hptcsv3_4b -> Draw() ; c_pt -> Update() ; c_pt -> Draw() ;
   hptcsv4_4b -> Draw() ; c_pt -> Update() ; c_pt -> Draw() ;


   c_pt -> cd(1) ;
   hptcsv1_2b -> Draw("hist") ;
   hptcsv1_2b -> Draw("same e") ;
   hptcsv1_4b -> Draw("same e") ;
   st1 = (TPaveStats*) hptcsv1_2b -> FindObject("stats") ;
   st2 = (TPaveStats*) hptcsv1_4b -> FindObject("stats") ;
   st1 -> SetX1NDC( s1x1 ) ; st1 -> SetY1NDC( s1y1 ) ; st1 -> SetX2NDC( s1x2 ) ; st1 -> SetY2NDC( s1y2 ) ; st1 -> SetTextColor( 4 ) ;
   st2 -> SetX1NDC( s2x1 ) ; st2 -> SetY1NDC( s2y1 ) ; st2 -> SetX2NDC( s2x2 ) ; st2 -> SetY2NDC( s2y2 ) ; st2 -> SetTextColor( 2 ) ;

   c_pt -> cd(2) ;
   hptcsv2_2b -> Draw("hist") ;
   hptcsv2_2b -> Draw("same e") ;
   hptcsv2_4b -> Draw("same e") ;
   st1 = (TPaveStats*) hptcsv2_2b -> FindObject("stats") ;
   st2 = (TPaveStats*) hptcsv2_4b -> FindObject("stats") ;
   st1 -> SetX1NDC( s1x1 ) ; st1 -> SetY1NDC( s1y1 ) ; st1 -> SetX2NDC( s1x2 ) ; st1 -> SetY2NDC( s1y2 ) ; st1 -> SetTextColor( 4 ) ;
   st2 -> SetX1NDC( s2x1 ) ; st2 -> SetY1NDC( s2y1 ) ; st2 -> SetX2NDC( s2x2 ) ; st2 -> SetY2NDC( s2y2 ) ; st2 -> SetTextColor( 2 ) ;

   c_pt -> cd(3) ;
   hptcsv3_2b -> Draw("hist") ;
   hptcsv3_2b -> Draw("same e") ;
   hptcsv3_4b -> Draw("same e") ;
   st1 = (TPaveStats*) hptcsv3_2b -> FindObject("stats") ;
   st2 = (TPaveStats*) hptcsv3_4b -> FindObject("stats") ;
   st1 -> SetX1NDC( s1x1 ) ; st1 -> SetY1NDC( s1y1 ) ; st1 -> SetX2NDC( s1x2 ) ; st1 -> SetY2NDC( s1y2 ) ; st1 -> SetTextColor( 4 ) ;
   st2 -> SetX1NDC( s2x1 ) ; st2 -> SetY1NDC( s2y1 ) ; st2 -> SetX2NDC( s2x2 ) ; st2 -> SetY2NDC( s2y2 ) ; st2 -> SetTextColor( 2 ) ;

   c_pt -> cd(4) ;
   hptcsv4_2b -> Draw("hist") ;
   hptcsv4_2b -> Draw("same e") ;
   hptcsv4_4b -> Draw("same e") ;
   st1 = (TPaveStats*) hptcsv4_2b -> FindObject("stats") ;
   st2 = (TPaveStats*) hptcsv4_4b -> FindObject("stats") ;
   st1 -> SetX1NDC( s1x1 ) ; st1 -> SetY1NDC( s1y1 ) ; st1 -> SetX2NDC( s1x2 ) ; st1 -> SetY2NDC( s1y2 ) ; st1 -> SetTextColor( 4 ) ;
   st2 -> SetX1NDC( s2x1 ) ; st2 -> SetY1NDC( s2y1 ) ; st2 -> SetX2NDC( s2x2 ) ; st2 -> SetY2NDC( s2y2 ) ; st2 -> SetTextColor( 2 ) ;


   char fname[1000] ;
   sprintf( fname, "outputfiles/%s-%s.pdf", cname, samplename ) ;
   c_pt -> SaveAs( fname ) ;


} // draw_pt_canvas

//====================================================

void truthstudy1::draw_pt_canvas_h( const char* cname, const char* ctitle, TH1* hptcsv1_2b, TH1* hptcsv1_4b,
                                                            TH1* hptcsv2_2b, TH1* hptcsv2_4b,
                                                            TH1* hptcsv3_2b, TH1* hptcsv3_4b,
                                                            TH1* hptcsv4_2b, TH1* hptcsv4_4b,
                                                            bool setmax ) {

   //float s1x1(0.40), s1y1(0.60), s1x2(0.99), s1y2(0.85) ;
   //float s2x1(0.40), s2y1(0.30), s2x2(0.99), s2y2(0.55) ;

   float s1x1(0.45), s1y1(0.65), s1x2(0.99), s1y2(0.85) ;
   float s2x1(0.45), s2y1(0.40), s2x2(0.99), s2y2(0.60) ;

   TPaveStats *st1(0x0), *st2(0x0) ;

    if ( hptcsv1_2b==0x0 || hptcsv1_4b==0x0 ) return ;
    if ( hptcsv2_2b==0x0 || hptcsv2_4b==0x0 ) return ;
    if ( hptcsv3_2b==0x0 || hptcsv3_4b==0x0 ) return ;
    if ( hptcsv4_2b==0x0 || hptcsv4_4b==0x0 ) return ;

    hptcsv1_2b -> Sumw2() ;  hptcsv1_4b -> Sumw2() ;
    hptcsv2_2b -> Sumw2() ;  hptcsv2_4b -> Sumw2() ;
    hptcsv3_2b -> Sumw2() ;  hptcsv3_4b -> Sumw2() ;
    hptcsv4_2b -> Sumw2() ;  hptcsv4_4b -> Sumw2() ;

    if ( hptcsv1_2b -> Integral() > 0 ) hptcsv1_2b -> Scale( 1./(hptcsv1_2b->Integral()) ) ;
    if ( hptcsv2_2b -> Integral() > 0 ) hptcsv2_2b -> Scale( 1./(hptcsv2_2b->Integral()) ) ;
    if ( hptcsv3_2b -> Integral() > 0 ) hptcsv3_2b -> Scale( 1./(hptcsv3_2b->Integral()) ) ;
    if ( hptcsv4_2b -> Integral() > 0 ) hptcsv4_2b -> Scale( 1./(hptcsv4_2b->Integral()) ) ;
    if ( hptcsv1_4b -> Integral() > 0 ) hptcsv1_4b -> Scale( 1./(hptcsv1_4b->Integral()) ) ;
    if ( hptcsv2_4b -> Integral() > 0 ) hptcsv2_4b -> Scale( 1./(hptcsv2_4b->Integral()) ) ;
    if ( hptcsv3_4b -> Integral() > 0 ) hptcsv3_4b -> Scale( 1./(hptcsv3_4b->Integral()) ) ;
    if ( hptcsv4_4b -> Integral() > 0 ) hptcsv4_4b -> Scale( 1./(hptcsv4_4b->Integral()) ) ;

    hptcsv1_2b -> SetLineWidth(2) ;
    hptcsv2_2b -> SetLineWidth(2) ;
    hptcsv3_2b -> SetLineWidth(2) ;
    hptcsv4_2b -> SetLineWidth(2) ;

    hptcsv1_4b -> SetLineWidth(2) ;
    hptcsv2_4b -> SetLineWidth(2) ;
    hptcsv3_4b -> SetLineWidth(2) ;
    hptcsv4_4b -> SetLineWidth(2) ;

    hptcsv1_2b -> SetLineColor(4) ;
    hptcsv2_2b -> SetLineColor(4) ;
    hptcsv3_2b -> SetLineColor(4) ;
    hptcsv4_2b -> SetLineColor(4) ;

    hptcsv1_4b -> SetLineColor(2) ;
    hptcsv2_4b -> SetLineColor(2) ;
    hptcsv3_4b -> SetLineColor(2) ;
    hptcsv4_4b -> SetLineColor(2) ;


    if ( setmax ) {
       hptcsv1_2b -> SetMaximum( 0.60 ) ;
       hptcsv2_2b -> SetMaximum( 0.60 ) ;
       hptcsv3_2b -> SetMaximum( 0.60 ) ;
       hptcsv4_2b -> SetMaximum( 0.60 ) ;
       hptcsv1_4b -> SetMaximum( 0.60 ) ;
       hptcsv2_4b -> SetMaximum( 0.60 ) ;
       hptcsv3_4b -> SetMaximum( 0.60 ) ;
       hptcsv4_4b -> SetMaximum( 0.60 ) ;
    }

   hptcsv1_2b -> SetXTitle("jet pt (GeV)") ;
   hptcsv2_2b -> SetXTitle("jet pt (GeV)") ;
   hptcsv3_2b -> SetXTitle("jet pt (GeV)") ;
   hptcsv4_2b -> SetXTitle("jet pt (GeV)") ;

   hptcsv1_2b -> SetTitleSize( 0.05 ) ;
   hptcsv2_2b -> SetTitleSize( 0.05 ) ;
   hptcsv3_2b -> SetTitleSize( 0.05 ) ;
   hptcsv4_2b -> SetTitleSize( 0.05 ) ;

   hptcsv1_2b -> SetLabelSize( 0.05, "x" ) ;
   hptcsv2_2b -> SetLabelSize( 0.05, "x" ) ;
   hptcsv3_2b -> SetLabelSize( 0.05, "x" ) ;
   hptcsv4_2b -> SetLabelSize( 0.05, "x" ) ;

   hptcsv1_2b -> SetLabelSize( 0.05, "y" ) ;
   hptcsv2_2b -> SetLabelSize( 0.05, "y" ) ;
   hptcsv3_2b -> SetLabelSize( 0.05, "y" ) ;
   hptcsv4_2b -> SetLabelSize( 0.05, "y" ) ;


   TString newtitle ;
   TString ts_sn = TString(", ") + TString( samplename ) ;

   newtitle = hptcsv1_2b -> GetTitle() + ts_sn ;
   newtitle.ReplaceAll(", 2b","") ;
   hptcsv1_2b -> SetTitle( newtitle ) ;

   newtitle = hptcsv2_2b -> GetTitle() + ts_sn ;
   newtitle.ReplaceAll(", 2b","") ;
   hptcsv2_2b -> SetTitle( newtitle ) ;

   newtitle = hptcsv3_2b -> GetTitle() + ts_sn ;
   newtitle.ReplaceAll(", 2b","") ;
   hptcsv3_2b -> SetTitle( newtitle ) ;

   newtitle = hptcsv4_2b -> GetTitle() + ts_sn ;
   newtitle.ReplaceAll(", 2b","") ;
   hptcsv4_2b -> SetTitle( newtitle ) ;


   gStyle -> SetOptStat("neMR") ;
   gStyle -> SetPadGridY(0) ;
   gStyle -> SetTitleW(0.90) ;
   gStyle -> SetTitleH(0.09) ;
   gStyle -> SetPadBottomMargin(0.10) ;
   gStyle -> SetTitleY(1.00) ;
   gStyle -> SetPadTopMargin(0.11) ;

   TCanvas* c_pt = new TCanvas( cname, ctitle, 1000, 400 ) ;

   c_pt -> Divide(4,1) ;

  //-- draw to create stats boxes.
   c_pt -> cd(1) ;
   hptcsv1_2b -> Draw() ; c_pt -> Update() ; c_pt -> Draw() ;
   hptcsv2_2b -> Draw() ; c_pt -> Update() ; c_pt -> Draw() ;
   hptcsv3_2b -> Draw() ; c_pt -> Update() ; c_pt -> Draw() ;
   hptcsv4_2b -> Draw() ; c_pt -> Update() ; c_pt -> Draw() ;
   hptcsv1_4b -> Draw() ; c_pt -> Update() ; c_pt -> Draw() ;
   hptcsv2_4b -> Draw() ; c_pt -> Update() ; c_pt -> Draw() ;
   hptcsv3_4b -> Draw() ; c_pt -> Update() ; c_pt -> Draw() ;
   hptcsv4_4b -> Draw() ; c_pt -> Update() ; c_pt -> Draw() ;


   c_pt -> cd(1) ;
   hptcsv1_2b -> Draw("hist") ;
   hptcsv1_2b -> Draw("same e") ;
   hptcsv1_4b -> Draw("same e") ;
   st1 = (TPaveStats*) hptcsv1_2b -> FindObject("stats") ;
   st2 = (TPaveStats*) hptcsv1_4b -> FindObject("stats") ;
   st1 -> SetX1NDC( s1x1 ) ; st1 -> SetY1NDC( s1y1 ) ; st1 -> SetX2NDC( s1x2 ) ; st1 -> SetY2NDC( s1y2 ) ; st1 -> SetTextColor( 4 ) ;
   st2 -> SetX1NDC( s2x1 ) ; st2 -> SetY1NDC( s2y1 ) ; st2 -> SetX2NDC( s2x2 ) ; st2 -> SetY2NDC( s2y2 ) ; st2 -> SetTextColor( 2 ) ;

   c_pt -> cd(2) ;
   hptcsv2_2b -> Draw("hist") ;
   hptcsv2_2b -> Draw("same e") ;
   hptcsv2_4b -> Draw("same e") ;
   st1 = (TPaveStats*) hptcsv2_2b -> FindObject("stats") ;
   st2 = (TPaveStats*) hptcsv2_4b -> FindObject("stats") ;
   st1 -> SetX1NDC( s1x1 ) ; st1 -> SetY1NDC( s1y1 ) ; st1 -> SetX2NDC( s1x2 ) ; st1 -> SetY2NDC( s1y2 ) ; st1 -> SetTextColor( 4 ) ;
   st2 -> SetX1NDC( s2x1 ) ; st2 -> SetY1NDC( s2y1 ) ; st2 -> SetX2NDC( s2x2 ) ; st2 -> SetY2NDC( s2y2 ) ; st2 -> SetTextColor( 2 ) ;

   c_pt -> cd(3) ;
   hptcsv3_2b -> Draw("hist") ;
   hptcsv3_2b -> Draw("same e") ;
   hptcsv3_4b -> Draw("same e") ;
   st1 = (TPaveStats*) hptcsv3_2b -> FindObject("stats") ;
   st2 = (TPaveStats*) hptcsv3_4b -> FindObject("stats") ;
   st1 -> SetX1NDC( s1x1 ) ; st1 -> SetY1NDC( s1y1 ) ; st1 -> SetX2NDC( s1x2 ) ; st1 -> SetY2NDC( s1y2 ) ; st1 -> SetTextColor( 4 ) ;
   st2 -> SetX1NDC( s2x1 ) ; st2 -> SetY1NDC( s2y1 ) ; st2 -> SetX2NDC( s2x2 ) ; st2 -> SetY2NDC( s2y2 ) ; st2 -> SetTextColor( 2 ) ;

   c_pt -> cd(4) ;
   hptcsv4_2b -> Draw("hist") ;
   hptcsv4_2b -> Draw("same e") ;
   hptcsv4_4b -> Draw("same e") ;
   st1 = (TPaveStats*) hptcsv4_2b -> FindObject("stats") ;
   st2 = (TPaveStats*) hptcsv4_4b -> FindObject("stats") ;
   st1 -> SetX1NDC( s1x1 ) ; st1 -> SetY1NDC( s1y1 ) ; st1 -> SetX2NDC( s1x2 ) ; st1 -> SetY2NDC( s1y2 ) ; st1 -> SetTextColor( 4 ) ;
   st2 -> SetX1NDC( s2x1 ) ; st2 -> SetY1NDC( s2y1 ) ; st2 -> SetX2NDC( s2x2 ) ; st2 -> SetY2NDC( s2y2 ) ; st2 -> SetTextColor( 2 ) ;


   char fname[1000] ;
   sprintf( fname, "outputfiles/%s-%s.pdf", cname, samplename ) ;
   c_pt -> SaveAs( fname ) ;


} // draw_pt_canvas

//====================================================

void truthstudy1::draw_pt_canvas3( const char* cname, const char* ctitle, TH1* hptcsv1_2b, TH1* hptcsv1_4b, TH1* hptcsv1_3b,
                                                            TH1* hptcsv2_2b, TH1* hptcsv2_4b, TH1* hptcsv2_3b,
                                                            TH1* hptcsv3_2b, TH1* hptcsv3_4b, TH1* hptcsv3_3b,
                                                            TH1* hptcsv4_2b, TH1* hptcsv4_4b, TH1* hptcsv4_3b,
                                                            bool setmax ) {

   float s1x1(0.70), s1y1(0.73), s1x2(0.99), s1y2(0.98) ;
   float s2x1(0.70), s2y1(0.43), s2x2(0.99), s2y2(0.68) ;
   float s3x1(0.70), s3y1(0.13), s3x2(0.99), s3y2(0.38) ;
   TPaveStats *st1(0x0), *st2(0x0), *st3(0x0) ;

    if ( hptcsv1_2b==0x0 || hptcsv1_4b==0x0 || hptcsv1_3b==0x0 ) return ;
    if ( hptcsv2_2b==0x0 || hptcsv2_4b==0x0 || hptcsv2_3b==0x0 ) return ;
    if ( hptcsv3_2b==0x0 || hptcsv3_4b==0x0 || hptcsv3_3b==0x0 ) return ;
    if ( hptcsv4_2b==0x0 || hptcsv4_4b==0x0 || hptcsv4_3b==0x0 ) return ;

    hptcsv1_2b -> Sumw2() ;  hptcsv1_4b -> Sumw2() ;   hptcsv1_3b -> Sumw2() ;
    hptcsv2_2b -> Sumw2() ;  hptcsv2_4b -> Sumw2() ;   hptcsv2_3b -> Sumw2() ;
    hptcsv3_2b -> Sumw2() ;  hptcsv3_4b -> Sumw2() ;   hptcsv3_3b -> Sumw2() ;
    hptcsv4_2b -> Sumw2() ;  hptcsv4_4b -> Sumw2() ;   hptcsv4_3b -> Sumw2() ;

    if ( hptcsv1_2b -> Integral() > 0 ) hptcsv1_2b -> Scale( 1./(hptcsv1_2b->Integral()) ) ;
    if ( hptcsv2_2b -> Integral() > 0 ) hptcsv2_2b -> Scale( 1./(hptcsv2_2b->Integral()) ) ;
    if ( hptcsv3_2b -> Integral() > 0 ) hptcsv3_2b -> Scale( 1./(hptcsv3_2b->Integral()) ) ;
    if ( hptcsv4_2b -> Integral() > 0 ) hptcsv4_2b -> Scale( 1./(hptcsv4_2b->Integral()) ) ;

    if ( hptcsv1_4b -> Integral() > 0 ) hptcsv1_4b -> Scale( 1./(hptcsv1_4b->Integral()) ) ;
    if ( hptcsv2_4b -> Integral() > 0 ) hptcsv2_4b -> Scale( 1./(hptcsv2_4b->Integral()) ) ;
    if ( hptcsv3_4b -> Integral() > 0 ) hptcsv3_4b -> Scale( 1./(hptcsv3_4b->Integral()) ) ;
    if ( hptcsv4_4b -> Integral() > 0 ) hptcsv4_4b -> Scale( 1./(hptcsv4_4b->Integral()) ) ;

    if ( hptcsv1_3b -> Integral() > 0 ) hptcsv1_3b -> Scale( 1./(hptcsv1_3b->Integral()) ) ;
    if ( hptcsv2_3b -> Integral() > 0 ) hptcsv2_3b -> Scale( 1./(hptcsv2_3b->Integral()) ) ;
    if ( hptcsv3_3b -> Integral() > 0 ) hptcsv3_3b -> Scale( 1./(hptcsv3_3b->Integral()) ) ;
    if ( hptcsv4_3b -> Integral() > 0 ) hptcsv4_3b -> Scale( 1./(hptcsv4_3b->Integral()) ) ;

    hptcsv1_2b -> SetLineWidth(2) ;
    hptcsv2_2b -> SetLineWidth(2) ;
    hptcsv3_2b -> SetLineWidth(2) ;
    hptcsv4_2b -> SetLineWidth(2) ;

    hptcsv1_3b -> SetLineWidth(2) ;
    hptcsv2_3b -> SetLineWidth(2) ;
    hptcsv3_3b -> SetLineWidth(2) ;
    hptcsv4_3b -> SetLineWidth(2) ;

    hptcsv1_4b -> SetLineWidth(2) ;
    hptcsv2_4b -> SetLineWidth(2) ;
    hptcsv3_4b -> SetLineWidth(2) ;
    hptcsv4_4b -> SetLineWidth(2) ;

    hptcsv1_2b -> SetLineColor(4) ;
    hptcsv2_2b -> SetLineColor(4) ;
    hptcsv3_2b -> SetLineColor(4) ;
    hptcsv4_2b -> SetLineColor(4) ;

    hptcsv1_3b -> SetLineColor(1) ;
    hptcsv2_3b -> SetLineColor(1) ;
    hptcsv3_3b -> SetLineColor(1) ;
    hptcsv4_3b -> SetLineColor(1) ;

    hptcsv1_4b -> SetLineColor(2) ;
    hptcsv2_4b -> SetLineColor(2) ;
    hptcsv3_4b -> SetLineColor(2) ;
    hptcsv4_4b -> SetLineColor(2) ;


    if ( setmax ) {
       hptcsv1_2b -> SetMaximum( 0.60 ) ;
       hptcsv2_2b -> SetMaximum( 0.60 ) ;
       hptcsv3_2b -> SetMaximum( 0.60 ) ;
       hptcsv4_2b -> SetMaximum( 0.60 ) ;
       hptcsv1_4b -> SetMaximum( 0.60 ) ;
       hptcsv2_4b -> SetMaximum( 0.60 ) ;
       hptcsv3_4b -> SetMaximum( 0.60 ) ;
       hptcsv4_4b -> SetMaximum( 0.60 ) ;
    }

   hptcsv1_2b -> SetXTitle("jet pt (GeV)") ;
   hptcsv2_2b -> SetXTitle("jet pt (GeV)") ;
   hptcsv3_2b -> SetXTitle("jet pt (GeV)") ;
   hptcsv4_2b -> SetXTitle("jet pt (GeV)") ;

   hptcsv1_2b -> SetTitleSize( 0.05 ) ;
   hptcsv2_2b -> SetTitleSize( 0.05 ) ;
   hptcsv3_2b -> SetTitleSize( 0.05 ) ;
   hptcsv4_2b -> SetTitleSize( 0.05 ) ;

   hptcsv1_2b -> SetLabelSize( 0.05, "x" ) ;
   hptcsv2_2b -> SetLabelSize( 0.05, "x" ) ;
   hptcsv3_2b -> SetLabelSize( 0.05, "x" ) ;
   hptcsv4_2b -> SetLabelSize( 0.05, "x" ) ;

   hptcsv1_2b -> SetLabelSize( 0.05, "y" ) ;
   hptcsv2_2b -> SetLabelSize( 0.05, "y" ) ;
   hptcsv3_2b -> SetLabelSize( 0.05, "y" ) ;
   hptcsv4_2b -> SetLabelSize( 0.05, "y" ) ;


   TString newtitle ;
   TString ts_sn = TString(", ") + TString( samplename ) ;

   newtitle = hptcsv1_2b -> GetTitle() + ts_sn ;
   newtitle.ReplaceAll(", 2b","") ;
   hptcsv1_2b -> SetTitle( newtitle ) ;

   newtitle = hptcsv2_2b -> GetTitle() + ts_sn ;
   newtitle.ReplaceAll(", 2b","") ;
   hptcsv2_2b -> SetTitle( newtitle ) ;

   newtitle = hptcsv3_2b -> GetTitle() + ts_sn ;
   newtitle.ReplaceAll(", 2b","") ;
   hptcsv3_2b -> SetTitle( newtitle ) ;

   newtitle = hptcsv4_2b -> GetTitle() + ts_sn ;
   newtitle.ReplaceAll(", 2b","") ;
   hptcsv4_2b -> SetTitle( newtitle ) ;


   gStyle -> SetOptStat("neMR") ;
   gStyle -> SetPadGridY(0) ;
   gStyle -> SetTitleW(0.60) ;
   gStyle -> SetTitleH(0.09) ;
   gStyle -> SetPadBottomMargin(0.10) ;
   gStyle -> SetTitleY(1.00) ;
   gStyle -> SetPadTopMargin(0.11) ;

   TCanvas* c_pt = new TCanvas( cname, ctitle, 500, 1000 ) ;

   c_pt -> Divide(1,4) ;

  //-- draw to create stats boxes.
   c_pt -> cd(1) ;
   hptcsv1_2b -> Draw() ; c_pt -> Update() ; c_pt -> Draw() ;
   hptcsv2_2b -> Draw() ; c_pt -> Update() ; c_pt -> Draw() ;
   hptcsv3_2b -> Draw() ; c_pt -> Update() ; c_pt -> Draw() ;
   hptcsv4_2b -> Draw() ; c_pt -> Update() ; c_pt -> Draw() ;

   hptcsv1_3b -> Draw() ; c_pt -> Update() ; c_pt -> Draw() ;
   hptcsv2_3b -> Draw() ; c_pt -> Update() ; c_pt -> Draw() ;
   hptcsv3_3b -> Draw() ; c_pt -> Update() ; c_pt -> Draw() ;
   hptcsv4_3b -> Draw() ; c_pt -> Update() ; c_pt -> Draw() ;

   hptcsv1_4b -> Draw() ; c_pt -> Update() ; c_pt -> Draw() ;
   hptcsv2_4b -> Draw() ; c_pt -> Update() ; c_pt -> Draw() ;
   hptcsv3_4b -> Draw() ; c_pt -> Update() ; c_pt -> Draw() ;
   hptcsv4_4b -> Draw() ; c_pt -> Update() ; c_pt -> Draw() ;


   c_pt -> cd(1) ;
   hptcsv1_2b -> Draw("hist") ;
   hptcsv1_2b -> Draw("same e") ;
   hptcsv1_4b -> Draw("same e") ;
   hptcsv1_3b -> Draw("same e") ;
   st1 = (TPaveStats*) hptcsv1_2b -> FindObject("stats") ;
   st2 = (TPaveStats*) hptcsv1_4b -> FindObject("stats") ;
   st3 = (TPaveStats*) hptcsv1_3b -> FindObject("stats") ;
   st1 -> SetX1NDC( s1x1 ) ; st1 -> SetY1NDC( s1y1 ) ; st1 -> SetX2NDC( s1x2 ) ; st1 -> SetY2NDC( s1y2 ) ; st1 -> SetTextColor( 4 ) ;
   st2 -> SetX1NDC( s2x1 ) ; st2 -> SetY1NDC( s2y1 ) ; st2 -> SetX2NDC( s2x2 ) ; st2 -> SetY2NDC( s2y2 ) ; st2 -> SetTextColor( 2 ) ;
   st3 -> SetX1NDC( s3x1 ) ; st3 -> SetY1NDC( s3y1 ) ; st3 -> SetX2NDC( s3x2 ) ; st3 -> SetY2NDC( s3y2 ) ; st3 -> SetTextColor( 1 ) ;

   c_pt -> cd(2) ;
   hptcsv2_2b -> Draw("hist") ;
   hptcsv2_2b -> Draw("same e") ;
   hptcsv2_4b -> Draw("same e") ;
   hptcsv2_3b -> Draw("same e") ;
   st1 = (TPaveStats*) hptcsv2_2b -> FindObject("stats") ;
   st2 = (TPaveStats*) hptcsv2_4b -> FindObject("stats") ;
   st3 = (TPaveStats*) hptcsv2_3b -> FindObject("stats") ;
   st1 -> SetX1NDC( s1x1 ) ; st1 -> SetY1NDC( s1y1 ) ; st1 -> SetX2NDC( s1x2 ) ; st1 -> SetY2NDC( s1y2 ) ; st1 -> SetTextColor( 4 ) ;
   st2 -> SetX1NDC( s2x1 ) ; st2 -> SetY1NDC( s2y1 ) ; st2 -> SetX2NDC( s2x2 ) ; st2 -> SetY2NDC( s2y2 ) ; st2 -> SetTextColor( 2 ) ;
   st3 -> SetX1NDC( s3x1 ) ; st3 -> SetY1NDC( s3y1 ) ; st3 -> SetX2NDC( s3x2 ) ; st3 -> SetY2NDC( s3y2 ) ; st3 -> SetTextColor( 1 ) ;

   c_pt -> cd(3) ;
   hptcsv3_2b -> Draw("hist") ;
   hptcsv3_2b -> Draw("same e") ;
   hptcsv3_4b -> Draw("same e") ;
   hptcsv3_3b -> Draw("same e") ;
   st1 = (TPaveStats*) hptcsv3_2b -> FindObject("stats") ;
   st2 = (TPaveStats*) hptcsv3_4b -> FindObject("stats") ;
   st3 = (TPaveStats*) hptcsv3_3b -> FindObject("stats") ;
   st1 -> SetX1NDC( s1x1 ) ; st1 -> SetY1NDC( s1y1 ) ; st1 -> SetX2NDC( s1x2 ) ; st1 -> SetY2NDC( s1y2 ) ; st1 -> SetTextColor( 4 ) ;
   st2 -> SetX1NDC( s2x1 ) ; st2 -> SetY1NDC( s2y1 ) ; st2 -> SetX2NDC( s2x2 ) ; st2 -> SetY2NDC( s2y2 ) ; st2 -> SetTextColor( 2 ) ;
   st3 -> SetX1NDC( s3x1 ) ; st3 -> SetY1NDC( s3y1 ) ; st3 -> SetX2NDC( s3x2 ) ; st3 -> SetY2NDC( s3y2 ) ; st3 -> SetTextColor( 1 ) ;

   c_pt -> cd(4) ;
   hptcsv4_2b -> Draw("hist") ;
   hptcsv4_2b -> Draw("same e") ;
   hptcsv4_4b -> Draw("same e") ;
   hptcsv4_3b -> Draw("same e") ;
   st1 = (TPaveStats*) hptcsv4_2b -> FindObject("stats") ;
   st2 = (TPaveStats*) hptcsv4_4b -> FindObject("stats") ;
   st3 = (TPaveStats*) hptcsv4_3b -> FindObject("stats") ;
   st1 -> SetX1NDC( s1x1 ) ; st1 -> SetY1NDC( s1y1 ) ; st1 -> SetX2NDC( s1x2 ) ; st1 -> SetY2NDC( s1y2 ) ; st1 -> SetTextColor( 4 ) ;
   st2 -> SetX1NDC( s2x1 ) ; st2 -> SetY1NDC( s2y1 ) ; st2 -> SetX2NDC( s2x2 ) ; st2 -> SetY2NDC( s2y2 ) ; st2 -> SetTextColor( 2 ) ;
   st3 -> SetX1NDC( s3x1 ) ; st3 -> SetY1NDC( s3y1 ) ; st3 -> SetX2NDC( s3x2 ) ; st3 -> SetY2NDC( s3y2 ) ; st3 -> SetTextColor( 1 ) ;


   char fname[1000] ;
   sprintf( fname, "outputfiles/%s-%s.pdf", cname, samplename ) ;
   c_pt -> SaveAs( fname ) ;


} // draw_pt_canvas3

//====================================================

void truthstudy1::draw_hspt_canvas( const char* cname, const char* ctitle, TH1* hhspth2b, TH1* hhspth4b, TH1* hhsptl2b, TH1* hhsptl4b, bool setmax ) {

   if ( hhspth2b==0x0 || hhspth4b==0x0 || hhsptl2b==0x0 || hhsptl4b==0x0 ) return ;

   float s1x1(0.70), s1y1(0.70), s1x2(0.99), s1y2(0.95) ;
   float s2x1(0.70), s2y1(0.40), s2x2(0.99), s2y2(0.65) ;
   TPaveStats *st1(0x0), *st2(0x0) ;

   hhspth2b -> Sumw2() ;
   hhspth4b -> Sumw2() ;
   hhsptl2b -> Sumw2() ;
   hhsptl4b -> Sumw2() ;

   if ( hhspth2b -> Integral() > 0 ) hhspth2b -> Scale( 1./(hhspth2b->Integral()) ) ;
   if ( hhspth4b -> Integral() > 0 ) hhspth4b -> Scale( 1./(hhspth4b->Integral()) ) ;
   if ( hhsptl2b -> Integral() > 0 ) hhsptl2b -> Scale( 1./(hhsptl2b->Integral()) ) ;
   if ( hhsptl4b -> Integral() > 0 ) hhsptl4b -> Scale( 1./(hhsptl4b->Integral()) ) ;

   hhspth2b -> SetLineWidth(2) ;
   hhspth4b -> SetLineWidth(2) ;
   hhsptl2b -> SetLineWidth(2) ;
   hhsptl4b -> SetLineWidth(2) ;

   hhspth2b -> SetLineColor(4) ;
   hhspth4b -> SetLineColor(2) ;
   hhsptl2b -> SetLineColor(4) ;
   hhsptl4b -> SetLineColor(2) ;

    if ( setmax ) {
       hhspth2b -> SetMaximum( 0.14 ) ;
       hhspth4b -> SetMaximum( 0.14 ) ;
       hhsptl2b -> SetMaximum( 0.14 ) ;
       hhsptl4b -> SetMaximum( 0.14 ) ;
    }

   hhspth2b -> SetXTitle("higgs cand sum jet pt (GeV)") ;
   hhspth4b -> SetXTitle("higgs cand sum jet pt (GeV)") ;
   hhsptl2b -> SetXTitle("higgs cand sum jet pt (GeV)") ;
   hhsptl4b -> SetXTitle("higgs cand sum jet pt (GeV)") ;

   hhspth2b -> SetTitleSize( 0.05 ) ;
   hhspth4b -> SetTitleSize( 0.05 ) ;
   hhsptl2b -> SetTitleSize( 0.05 ) ;
   hhsptl4b -> SetTitleSize( 0.05 ) ;

   hhspth2b -> SetLabelSize( 0.05, "x" ) ;
   hhspth4b -> SetLabelSize( 0.05, "x" ) ;
   hhsptl2b -> SetLabelSize( 0.05, "x" ) ;
   hhsptl4b -> SetLabelSize( 0.05, "x" ) ;

   hhspth2b -> SetLabelSize( 0.05, "y" ) ;
   hhspth4b -> SetLabelSize( 0.05, "y" ) ;
   hhsptl2b -> SetLabelSize( 0.05, "y" ) ;
   hhsptl4b -> SetLabelSize( 0.05, "y" ) ;


   TString newtitle ;
   TString ts_sn = TString(", ") + TString( samplename ) ;

   newtitle = hhspth2b -> GetTitle() + ts_sn ;
   newtitle.ReplaceAll(", 2b","") ;
   hhspth2b -> SetTitle( newtitle ) ;

   newtitle = hhspth4b -> GetTitle() + ts_sn ;
   newtitle.ReplaceAll(", 2b","") ;
   hhspth4b -> SetTitle( newtitle ) ;

   newtitle = hhsptl2b -> GetTitle() + ts_sn ;
   newtitle.ReplaceAll(", 2b","") ;
   hhsptl2b -> SetTitle( newtitle ) ;

   newtitle = hhsptl4b -> GetTitle() + ts_sn ;
   newtitle.ReplaceAll(", 2b","") ;
   hhsptl4b -> SetTitle( newtitle ) ;



   gStyle -> SetOptStat("neMR") ;
   gStyle -> SetPadGridY(0) ;
   gStyle -> SetTitleW(0.60) ;
   gStyle -> SetTitleH(0.09) ;
   gStyle -> SetPadBottomMargin(0.10) ;
   gStyle -> SetTitleY(1.00) ;
   gStyle -> SetPadTopMargin(0.11) ;

   TCanvas* c_hspt = new TCanvas( cname, ctitle, 500, 600 ) ;

   c_hspt -> Divide(1,2) ;

  //-- draw to create stats boxes.
   c_hspt -> cd(1) ;
   hhspth2b -> Draw() ; c_hspt -> Update() ; c_hspt -> Draw() ;
   hhspth4b -> Draw() ; c_hspt -> Update() ; c_hspt -> Draw() ;
   hhsptl2b -> Draw() ; c_hspt -> Update() ; c_hspt -> Draw() ;
   hhsptl4b -> Draw() ; c_hspt -> Update() ; c_hspt -> Draw() ;

   c_hspt -> cd(1) ;
   hhspth2b -> Draw("hist") ;
   hhspth2b -> Draw("same e") ;
   hhspth4b -> Draw("same e") ;
   st1 = (TPaveStats*) hhspth2b -> FindObject("stats") ;
   st2 = (TPaveStats*) hhspth4b -> FindObject("stats") ;
   st1 -> SetX1NDC( s1x1 ) ; st1 -> SetY1NDC( s1y1 ) ; st1 -> SetX2NDC( s1x2 ) ; st1 -> SetY2NDC( s1y2 ) ; st1 -> SetTextColor( 4 ) ;
   st2 -> SetX1NDC( s2x1 ) ; st2 -> SetY1NDC( s2y1 ) ; st2 -> SetX2NDC( s2x2 ) ; st2 -> SetY2NDC( s2y2 ) ; st2 -> SetTextColor( 2 ) ;

   c_hspt -> cd(2) ;
   hhsptl2b -> Draw("hist") ;
   hhsptl2b -> Draw("same e") ;
   hhsptl4b -> Draw("same e") ;
   st1 = (TPaveStats*) hhsptl2b -> FindObject("stats") ;
   st2 = (TPaveStats*) hhsptl4b -> FindObject("stats") ;
   st1 -> SetX1NDC( s1x1 ) ; st1 -> SetY1NDC( s1y1 ) ; st1 -> SetX2NDC( s1x2 ) ; st1 -> SetY2NDC( s1y2 ) ; st1 -> SetTextColor( 4 ) ;
   st2 -> SetX1NDC( s2x1 ) ; st2 -> SetY1NDC( s2y1 ) ; st2 -> SetX2NDC( s2x2 ) ; st2 -> SetY2NDC( s2y2 ) ; st2 -> SetTextColor( 2 ) ;

   char fname[1000] ;
   sprintf( fname, "outputfiles/%s-%s.pdf", cname, samplename ) ;
   c_hspt -> SaveAs( fname ) ;



} // draw_hspt_canvas

//====================================================


void truthstudy1::draw_code_ratio_canvas( const char* cname, const char* ctitle, TH1* hca, TH1* hcb, TH1* hra, TH1* hrb ) {

   if ( hca==0x0 || hcb==0x0 || hra==0x0 || hrb==0x0 ) return ;

   TH1F* hrbs = shiftHist( hrb, 0.05 ) ;
   TH1F* hcbs = shiftHist( hcb, 0.05 ) ;

   TString ts_sn = TString(", ") + TString( samplename ) ;
   TString title ;
   title = hca -> GetTitle() + ts_sn ;
   title.ReplaceAll(", 2b","  ") ;
   hca -> SetTitle( title ) ;
   title = hra -> GetTitle() + ts_sn ;
   title.ReplaceAll(", 2b","  ") ;
   hra -> SetTitle( title ) ;

   hca -> SetTitleOffset(1.1,"y") ;
   hra -> SetTitleOffset(1.1,"y") ;
   hca -> SetTitleSize(0.05,"y") ;
   hra -> SetTitleSize(0.05,"y") ;


   gStyle -> SetOptStat(0) ;
   gStyle -> SetPadLeftMargin(0.13) ;

   hca -> SetLineWidth(2) ;
   hcbs-> SetLineWidth(2) ;
   hra -> SetLineWidth(2) ;
   hrbs-> SetLineWidth(2) ;

   hca -> SetLineColor(4) ;
   hcbs-> SetLineColor(2) ;
   hra -> SetLineColor(4) ;
   hrbs-> SetLineColor(2) ;

   hca -> Sumw2() ;
   hcbs-> Sumw2() ;
   hra -> Sumw2() ;
   hrbs-> Sumw2() ;

   hca -> SetYTitle("Fraction") ;
   hra -> SetYTitle("Mass SIG/SB ratio") ;

   if ( hca -> Integral() > 0 ) hca -> Scale( 1./(hca->Integral()) ) ;
   if ( hcbs-> Integral() > 0 ) hcbs-> Scale( 1./(hcbs->Integral()) ) ;

   hra -> SetMinimum(0.00) ;
   hra -> SetMaximum(0.50) ;

   float hcmax = hca -> GetMaximum() ;
   if ( hcbs -> GetMaximum() > hcmax ) hcmax = hcbs -> GetMaximum() ;

   ////hca -> SetMaximum( 1.5 * hcmax ) ;
   hca -> SetMaximum( 0.45 ) ;

   TLegend* legend = new TLegend(0.80, 0.75,  0.90, 0.95) ;
   legend -> SetFillColor( kWhite ) ;
   legend -> AddEntry( hca, "2b") ;
   legend -> AddEntry( hcbs, "4b") ;


   TCanvas* c_code_ratio = new TCanvas( cname, ctitle, 600, 800 ) ;

   c_code_ratio->Divide(1,2) ;

   c_code_ratio->cd(1) ;

   hca -> Draw("e") ;
   hcbs-> Draw("esame") ;
   hca -> Draw("histsame") ;
   hcbs-> Draw("histsame") ;
   legend -> Draw() ;


   c_code_ratio->cd(2) ;

   hra -> Draw() ;
   hrbs-> Draw("same") ;

   c_code_ratio -> Update() ;
   c_code_ratio -> Draw() ;

   char fname[1000] ;
   sprintf( fname, "outputfiles/%s-%s.pdf", cname, samplename ) ;
   c_code_ratio -> SaveAs( fname ) ;



} // draw_code_ratio_canvas

//====================================================

   TH1F* shiftHist( TH1* hin, float xshift ) {

      if ( hin == 0x0 ) return 0x0 ;

      int nbins = hin->GetNbinsX() ;
      float xlow = hin -> GetXaxis() -> GetBinLowEdge(1) ;
      float xhigh = hin -> GetXaxis() -> GetBinUpEdge(nbins) ;

      const TArrayD* xbins = hin -> GetXaxis() -> GetXbins() ;

      int size = xbins->GetSize() ;
      printf("\n\n Size of xbins array: %d\n", size ) ;

      double shiftedxbins[500] ;
      if ( size > 0 ) {
         for ( int bi=0; bi<=nbins; bi++ ) {
            shiftedxbins[bi] = xbins->At(bi) + xshift ;
            printf("  %s: bin %2d, edge = %.1f\n", hin->GetName(), bi, xbins->At(bi) ) ;
         } // bi.
      } else {
         float binwid = ( xhigh - xlow ) / ( nbins ) ;
         for ( int bi=0; bi<=nbins; bi++ ) {
            shiftedxbins[bi] = xlow + bi*binwid + xshift ;
         }
      }

      TH1F* retval = new TH1F( hin->GetName() + TString("_shift"), hin->GetTitle(), nbins, shiftedxbins ) ;
      for ( int bi=1; bi<=nbins; bi++ ) {
         retval->SetBinContent( bi, hin->GetBinContent(bi) ) ;
         retval->SetBinError( bi, hin->GetBinError(bi) ) ;
      }

      return retval ;

   }

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
}

//====================================================

void fillEffHist( TH1* hpass, TH1* hall, TH1* heff ) {

   if ( hpass == 0x0 || hall == 0x0 || heff == 0x0 ) return ;

   int nb = hpass -> GetNbinsX() ;
   for ( int bi=1; bi<=nb; bi++ ) {
      float pv = hpass -> GetBinContent( bi ) ;
      float pe = hpass -> GetBinError( bi ) ;
      float av = hall -> GetBinContent( bi ) ;
      float ae = hall -> GetBinError( bi ) ;
      float effval(0.) ;
      float efferr(0.) ;
      if ( av > 0 ) {
         effval = pv / av ;
         float fv = av - pv ;
         float fe = ae ;
         if ( ae > pe ) fe = sqrt( pow(ae,2) - pow(pe,2) ) ;
         efferr = sqrt( pow( fv * pe / (av*av), 2 ) + pow( pv * fe / (av*av), 2 ) ) ;
      }
      heff -> SetBinContent( bi, effval ) ;
      heff -> SetBinError( bi, efferr ) ;
   } // bi

} // fillEffHist

//====================================================


int getptbin( float ptval ) {
   for ( int bi=1; bi<=ncbinspt; bi++ ) {
      if ( ptval >= pt_bins[bi-1]  &&  ptval < pt_bins[bi] ) return bi ;
   } // bi.
   return ncbinspt ;
} // getptbin


//====================================================


int getsumptbin( float sumptval ) {
   for ( int bi=1; bi<=nbinssumpt; bi++ ) {
      if ( sumptval >= sumpt_bins[bi-1]  &&  sumptval < sumpt_bins[bi] ) return bi ;
   } // bi.
   return nbinssumpt ;
} // getsumptbin


//====================================================

void fillWeightHist( TH1* h2b, TH1* h4b, TH1* hw ) {

   if ( h2b==0x0 || h4b==0x0 || hw==0x0 ) return ;

   h2b -> Sumw2() ;
   h4b -> Sumw2() ;

   if ( h2b -> Integral() > 0 ) h2b -> Scale( 1./( h2b -> Integral() ) ) ;
   if ( h4b -> Integral() > 0 ) h4b -> Scale( 1./( h4b -> Integral() ) ) ;

   int nb = h2b->GetNbinsX() ;
   for ( int bi=1; bi<=nb; bi++ ) {
      float wval(0.) ;
      float werr(0.) ;
      float f2bval = h2b -> GetBinContent( bi ) ;
      float f2berr = h2b -> GetBinError( bi ) ;
      float f4bval = h4b -> GetBinContent( bi ) ;
      float f4berr = h4b -> GetBinError( bi ) ;
      if ( f2bval > 0 ) {
         wval = f4bval / f2bval ;
         if ( f2bval > 0 && f4bval > 0 ) werr = wval * sqrt( pow( f2berr/f2bval, 2 ) + pow( f4berr/f4bval, 2 ) ) ;
      }
      hw -> SetBinContent( bi, wval ) ;
      hw -> SetBinError( bi, werr ) ;
   } // bi

}

//====================================================

void write_btageff_file( TH1* heff, const char* outfile ) {

   if ( heff == 0x0 ) return ;

   FILE* ofp = fopen( outfile, "w" ) ;

   for ( int bi=1; bi<=heff->GetNbinsX(); bi++ ) {
      fprintf( ofp, "%6.4f\n", heff->GetBinContent(bi) ) ;
   } // bi.

   fclose( ofp ) ;

}

//====================================================

void read_btageff_file( const char* infile, double* eff_array ) {

   FILE* infp ;
   if ( (infp=fopen( infile,"r"))==NULL ) {
      printf("\n\n\n *** problem opening file %s\n\n\n", infile ) ;
      return ;
   }

   printf("\n") ;
   for ( int bi=0; bi<ncbinspt; bi++ ) {
      fscanf( infp, "%lf", &eff_array[bi] ) ;
      printf( "%50s : %2d : %f\n", infile, bi, eff_array[bi] ) ;
   }
   printf("\n") ;


   fclose( infp ) ;

}

//====================================================

void write_weight_sumpt( TH1* hweight, const char* outfile ) {

   if ( hweight == 0x0 ) return ;

   FILE* ofp = fopen( outfile, "w" ) ;

   for ( int bi=1; bi<=hweight->GetNbinsX(); bi++ ) {
      fprintf( ofp, "%6.4f\n", hweight->GetBinContent(bi) ) ;
   } // bi.

   fclose( ofp ) ;

}

//====================================================

void read_weight_sumpt( const char* infile ) {

   FILE* infp ;
   if ( (infp=fopen( infile,"r"))==NULL ) {
      printf("\n\n\n *** problem opening file %s\n\n\n", infile ) ;
      return ;
   }

   printf("\n") ;
   for ( int bi=0; bi<nbinssumpt; bi++ ) {
      fscanf( infp, "%lf", &weight_sumpt[bi] ) ;
      printf( "%50s : %2d : %f\n", infile, bi, weight_sumpt[bi] ) ;
   }
   printf("\n") ;


   fclose( infp ) ;

}

//====================================================

