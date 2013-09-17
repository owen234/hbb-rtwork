//
//  dmc_drawplots2( infile, savePdf, recycleCanvas, histnamepat )
//
//    If you run it with the default arguments, it will produce pdf files
//    for all of the plots, recycling one canvas.
//
//    If you set recycleCanvas = false, a new canvas will open for each plot.
//    this is not recommended unles you specify a subset of plots with
//    the histnamepat argument.  The total is too big now.
//
//    If histnamepat is set, only plots that contain the histnamepat
//    substring will be drawn.
//
//    The kfactor array contains fudge factors for the samples.
//    Set them all to 1 if you want the raw MC normalization.
//

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

#include <iostream>


    bool recycleCanvas(false) ;

    int nComps(6) ;
    char compname[6][100] ;
    double kfactor[6] ;

    bool kfactorAlreadyApplied ;

    bool savePdf ;
    char inrootfile[10000] ;

  //----------
  // prototypes

   void drawSet( const char* hname_base, const char* xtitle ) ;
   void loadHist(const char* filename="in.root", const char* pfx=0, const char* pat="*", Bool_t doAdd=kFALSE, Double_t scaleFactor=-1.0) ;
   void saveHist(const char* filename, const char* pat) ;
   void drawMETsigBinBoundaries( float ymax ) ;
   void drawMETBinBoundaries( float ymax ) ;

  //----------

    void dmc_drawplots1( const char* infile = "outputfiles/dmc_plots1.root", bool arg_savePdf = true, bool arg_recycleCanvas=true, const char* histnamepat = "" ) {

       recycleCanvas = arg_recycleCanvas ;
       savePdf = arg_savePdf ;
       sprintf( inrootfile, "%s", infile ) ;

       gDirectory->Delete("h*") ;

       gStyle -> SetOptStat(0) ;
       gStyle -> SetTitleH(0.035 ) ;

       sprintf( compname[0], "data" ) ;      kfactor[0] = 1.00 ;
       sprintf( compname[1], "znn" ) ;       kfactor[1] = 1.00 ;
       sprintf( compname[2], "tt2l" ) ;      kfactor[2] = 1.00 ;
       sprintf( compname[3], "tt1l" ) ;      kfactor[3] = 1.00 ;
       sprintf( compname[4], "tt0l" ) ;      kfactor[4] = 1.00 ;
       sprintf( compname[5], "qcd_bb" ) ;    kfactor[5] = 1.30 ;
       //sprintf( compname[5], "qcd" ) ;    kfactor[5] = 1.00 ;


     //---------

       char histnamelist[500][100] ;
       char histxtitlelist[500][100] ;
       int hind(0) ;

       sprintf( histnamelist[hind], "h_metsig_2b_with_mindphi" ) ; sprintf( histxtitlelist[hind], "METsig" ) ; hind++ ;
       sprintf( histnamelist[hind], "h_metsig_2b_with_mindphi_wide1" ) ; sprintf( histxtitlelist[hind], "METsig" ) ; hind++ ;
       sprintf( histnamelist[hind], "h_metsig_2b_with_mindphi_wide2" ) ; sprintf( histxtitlelist[hind], "METsig" ) ; hind++ ;
       sprintf( histnamelist[hind], "h_met_2b_with_mindphi" ) ; sprintf( histxtitlelist[hind], "MET (GeV)" ) ; hind++ ;
       sprintf( histnamelist[hind], "h_metsig_2b_no_mindphi" ) ; sprintf( histxtitlelist[hind], "METsig" ) ; hind++ ;
       sprintf( histnamelist[hind], "h_metsig_2b_no_mindphi_wide1" ) ; sprintf( histxtitlelist[hind], "METsig" ) ; hind++ ;
       sprintf( histnamelist[hind], "h_metsig_2b_no_mindphi_wide2" ) ; sprintf( histxtitlelist[hind], "METsig" ) ; hind++ ;
       sprintf( histnamelist[hind], "h_met_2b_no_mindphi" ) ; sprintf( histxtitlelist[hind], "MET (GeV)" ) ; hind++ ;

 //    sprintf( histnamelist[hind], "h_mindphi_2b_no_metsig" ) ; sprintf( histxtitlelist[hind], "minDeltaPhi20" ) ; hind++ ;

 //    sprintf( histnamelist[hind], "h_mindphi_2b_metsig_030" ) ; sprintf( histxtitlelist[hind], "minDeltaPhi20" ) ; hind++ ;
 //    sprintf( histnamelist[hind], "h_mindphi_2b_metsig_050" ) ; sprintf( histxtitlelist[hind], "minDeltaPhi20" ) ; hind++ ;
 //    sprintf( histnamelist[hind], "h_mindphi_2b_metsig_100" ) ; sprintf( histxtitlelist[hind], "minDeltaPhi20" ) ; hind++ ;
 //    sprintf( histnamelist[hind], "h_mindphi_2b_metsig_150" ) ; sprintf( histxtitlelist[hind], "minDeltaPhi20" ) ; hind++ ;

 //    sprintf( histnamelist[hind], "h_mindphi_2b_no_met" ) ; sprintf( histxtitlelist[hind], "minDeltaPhi20" ) ; hind++ ;
 //    sprintf( histnamelist[hind], "h_mindphi_2b_met_100" ) ; sprintf( histxtitlelist[hind], "minDeltaPhi20" ) ; hind++ ;
 //    sprintf( histnamelist[hind], "h_mindphi_2b_met_135" ) ; sprintf( histxtitlelist[hind], "minDeltaPhi20" ) ; hind++ ;
 //    sprintf( histnamelist[hind], "h_mindphi_2b_met_190" ) ; sprintf( histxtitlelist[hind], "minDeltaPhi20" ) ; hind++ ;
 //    sprintf( histnamelist[hind], "h_mindphi_2b_met_250" ) ; sprintf( histxtitlelist[hind], "minDeltaPhi20" ) ; hind++ ;

 //    sprintf( histnamelist[hind], "h_mindphi_2b_metsig_bin0" ) ; sprintf( histxtitlelist[hind], "minDeltaPhi20" ) ; hind++ ;
 //    sprintf( histnamelist[hind], "h_mindphi_2b_metsig_bin1" ) ; sprintf( histxtitlelist[hind], "minDeltaPhi20" ) ; hind++ ;
 //    sprintf( histnamelist[hind], "h_mindphi_2b_metsig_bin2" ) ; sprintf( histxtitlelist[hind], "minDeltaPhi20" ) ; hind++ ;
 //    sprintf( histnamelist[hind], "h_mindphi_2b_metsig_bin3" ) ; sprintf( histxtitlelist[hind], "minDeltaPhi20" ) ; hind++ ;
 //    sprintf( histnamelist[hind], "h_mindphi_2b_metsig_bin4" ) ; sprintf( histxtitlelist[hind], "minDeltaPhi20" ) ; hind++ ;

 //    sprintf( histnamelist[hind], "h_mindphi_2b_met_bin0" ) ; sprintf( histxtitlelist[hind], "minDeltaPhi20" ) ; hind++ ;
 //    sprintf( histnamelist[hind], "h_mindphi_2b_met_bin1" ) ; sprintf( histxtitlelist[hind], "minDeltaPhi20" ) ; hind++ ;
 //    sprintf( histnamelist[hind], "h_mindphi_2b_met_bin2" ) ; sprintf( histxtitlelist[hind], "minDeltaPhi20" ) ; hind++ ;
 //    sprintf( histnamelist[hind], "h_mindphi_2b_met_bin3" ) ; sprintf( histxtitlelist[hind], "minDeltaPhi20" ) ; hind++ ;
 //    sprintf( histnamelist[hind], "h_mindphi_2b_met_bin4" ) ; sprintf( histxtitlelist[hind], "minDeltaPhi20" ) ; hind++ ;

 //    sprintf( histnamelist[hind], "h_mindphi_3bSB_no_metsig" ) ; sprintf( histxtitlelist[hind], "minDeltaPhi20" ) ; hind++ ;
 //    sprintf( histnamelist[hind], "h_mindphi_3bSB_metsig_030" ) ; sprintf( histxtitlelist[hind], "minDeltaPhi20" ) ; hind++ ;
 //    sprintf( histnamelist[hind], "h_mindphi_3bSB_metsig_050" ) ; sprintf( histxtitlelist[hind], "minDeltaPhi20" ) ; hind++ ;
 //    sprintf( histnamelist[hind], "h_mindphi_3bSB_metsig_100" ) ; sprintf( histxtitlelist[hind], "minDeltaPhi20" ) ; hind++ ;
 //    sprintf( histnamelist[hind], "h_mindphi_3bSB_metsig_150" ) ; sprintf( histxtitlelist[hind], "minDeltaPhi20" ) ; hind++ ;

 //    sprintf( histnamelist[hind], "h_mindphi_3bSIG_no_metsig" ) ; sprintf( histxtitlelist[hind], "minDeltaPhi20" ) ; hind++ ;
 //    sprintf( histnamelist[hind], "h_mindphi_3bSIG_metsig_030" ) ; sprintf( histxtitlelist[hind], "minDeltaPhi20" ) ; hind++ ;
 //    sprintf( histnamelist[hind], "h_mindphi_3bSIG_metsig_050" ) ; sprintf( histxtitlelist[hind], "minDeltaPhi20" ) ; hind++ ;
 //    sprintf( histnamelist[hind], "h_mindphi_3bSIG_metsig_100" ) ; sprintf( histxtitlelist[hind], "minDeltaPhi20" ) ; hind++ ;
 //    sprintf( histnamelist[hind], "h_mindphi_3bSIG_metsig_150" ) ; sprintf( histxtitlelist[hind], "minDeltaPhi20" ) ; hind++ ;

 //    sprintf( histnamelist[hind], "h_mindphi_4bSB_no_metsig" ) ; sprintf( histxtitlelist[hind], "minDeltaPhi20" ) ; hind++ ;
 //    sprintf( histnamelist[hind], "h_mindphi_4bSB_metsig_030" ) ; sprintf( histxtitlelist[hind], "minDeltaPhi20" ) ; hind++ ;
 //    sprintf( histnamelist[hind], "h_mindphi_4bSB_metsig_050" ) ; sprintf( histxtitlelist[hind], "minDeltaPhi20" ) ; hind++ ;
 //    sprintf( histnamelist[hind], "h_mindphi_4bSB_metsig_100" ) ; sprintf( histxtitlelist[hind], "minDeltaPhi20" ) ; hind++ ;
 //    sprintf( histnamelist[hind], "h_mindphi_4bSB_metsig_150" ) ; sprintf( histxtitlelist[hind], "minDeltaPhi20" ) ; hind++ ;

 //    sprintf( histnamelist[hind], "h_mindphi_4bSIG_no_metsig" ) ; sprintf( histxtitlelist[hind], "minDeltaPhi20" ) ; hind++ ;
 //    sprintf( histnamelist[hind], "h_mindphi_4bSIG_metsig_030" ) ; sprintf( histxtitlelist[hind], "minDeltaPhi20" ) ; hind++ ;
 //    sprintf( histnamelist[hind], "h_mindphi_4bSIG_metsig_050" ) ; sprintf( histxtitlelist[hind], "minDeltaPhi20" ) ; hind++ ;
 //    sprintf( histnamelist[hind], "h_mindphi_4bSIG_metsig_100" ) ; sprintf( histxtitlelist[hind], "minDeltaPhi20" ) ; hind++ ;
 //    sprintf( histnamelist[hind], "h_mindphi_4bSIG_metsig_150" ) ; sprintf( histxtitlelist[hind], "minDeltaPhi20" ) ; hind++ ;


       int nhistlist( hind ) ;




     //---------


       loadHist( infile ) ;

       kfactorAlreadyApplied = false ;

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




       kfactorAlreadyApplied = true ;

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



       printf("\n\n Done.\n\n") ;

       TString outputrootfile( infile ) ;
       outputrootfile.ReplaceAll(".root","-as-drawn.root") ;
       printf("\n\n Saving drawn histograms in %s\n\n", outputrootfile.Data() ) ;
       saveHist( outputrootfile, "h*" ) ;


    } // dmc_drawplots2b

  //--------------------------------------------------------



   void drawSet( const char* hname_base, const char* xtitle ) {

      printf("\n\n") ;

      TString hnstr( hname_base ) ;


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
      TCanvas* dmccan = (TCanvas*) gDirectory->FindObject( cname ) ;
      if ( dmccan == 0x0 ) {
         dmccan = new TCanvas( cname, hname_base, 600, 750 ) ;
      }
      dmccan->Clear() ;

      char hname[1000] ;
      sprintf( hname, "%s_%s", hname_base, "data" ) ;
      TH1F* hdata = (TH1F*) gDirectory->FindObject( hname ) ;
      if ( hdata == 0x0 ) {
         printf("\n\n *** drawSet: can't find data hist with name %s\n\n", hname ) ; return ;
      }

      double integral_val, integral_err ;
      int nbins = hdata->GetNbinsX() ;

      integral_val = hdata -> IntegralAndError( 1, nbins, integral_err ) ;
      printf(" %s : %8s : total %7.1f +/- %5.1f\n", hname_base, "data", integral_val, integral_err ) ;

      sprintf( hname, "%s_mcstack", hname_base ) ;
      THStack* hmcstack = new THStack() ;

      sprintf( hname, "%s_mcsum", hname_base ) ;
      TH1F* hmcsum = (TH1F*) hdata->Clone( hname ) ;
      hmcsum -> Reset() ;

      hdata -> SetLineWidth(2) ;
      hdata -> SetMarkerStyle(20) ;

      TLegend* legend = new TLegend( 0.80, 0.67, 0.95, 0.92 ) ;
      legend->SetFillColor(kWhite) ;

      for ( int ci=1; ci<nComps; ci++ ) {

         sprintf( hname, "%s_%s", hname_base, compname[ci] ) ;
         TH1F* hmc = (TH1F*) gDirectory->FindObject( hname ) ;
         if ( hmc == 0x0 ) { printf("\n\n *** drawSet: missing MC hist %s\n", hname ) ; return ; }
         integral_val = hmc -> IntegralAndError( 1, nbins, integral_err ) ;
         printf(" %s : %8s : total %7.1f +/- %5.1f\n", hname_base, compname[ci], integral_val, integral_err ) ;
         if ( !kfactorAlreadyApplied ) { hmc->Scale( kfactor[ci] ) ; }
         hmcsum -> Add( hmc ) ;
         hmcstack -> Add( hmc ) ;

      }

      integral_val = hmcsum -> IntegralAndError( 1, nbins, integral_err ) ;
      printf(" %s : %8s : total %7.1f +/- %5.1f\n", hname_base, "MC sum", integral_val, integral_err ) ;

      for ( int ci=nComps-1; ci>0; ci-- ) {

         sprintf( hname, "%s_%s", hname_base, compname[ci] ) ;
         TH1F* hmc = (TH1F*) gDirectory->FindObject( hname ) ;
         legend -> AddEntry( hmc, compname[ci] ) ;

      }

      sprintf( hname, "%s_diff", hname_base ) ;
      TH1F* hratio = (TH1F*) hdata->Clone( hname ) ;
      hratio->Reset() ;

      for ( int bi=1; bi<=hdata->GetNbinsX(); bi++ ) {
         double data = hdata->GetBinContent(bi) ;
         double data_err = hdata->GetBinError(bi) ;
         double mc = hmcsum->GetBinContent(bi) ;
         double mc_err = hmcsum->GetBinError(bi) ;
         double val = 0. ;
         double err = 0. ;
         if ( mc > 0 ) {
            val = data / mc ;
            double errsq(0.) ;
            if ( mc > 0 ) { errsq += pow(mc_err/mc,2) ; }
            if ( data > 0 ) { errsq += pow(data_err/data,2) ; }
            err = sqrt(errsq) ;
         }
         hratio->SetBinContent(bi,val) ;
         hratio->SetBinError(bi,err) ;
      } // bi.

      hratio->SetMinimum(0.0) ;
      hratio->SetMaximum(2.0) ;




      double hmax = hdata->GetBinContent( hdata->GetMaximumBin() ) ;
      if ( hmax > 0 ) {
         if ( hmcsum->GetBinContent( hmcsum->GetMaximumBin() ) > hmax ) { hmax = hmcsum->GetBinContent( hmcsum->GetMaximumBin() ) ; }
         if ( islogy ) {
            hmax = 3*hmax ;
         } else {
            hmax = 1.2*hmax ;
         }
         hdata->SetMaximum(hmax) ;
      }
      hdata->SetXTitle( xtitle ) ;

      char padname[1000] ;
      sprintf( padname, "tp_%s", hname_base ) ;
      TPad* toppad = new TPad( padname, padname, 0.02, 0.3, 0.98, 0.98 ) ;
      toppad->Draw() ;
      sprintf( padname, "bp_%s", hname_base ) ;
      TPad* bottompad = new TPad( padname, padname, 0.02, 0.02, 0.98, 0.28 ) ;
      bottompad->Draw() ;

      hmcsum->SetMarkerStyle(0) ;

      toppad->cd() ;
      gStyle->SetOptTitle(0) ;
      if ( hdata->GetMaximum() > 0 ) {
         hdata->DrawCopy() ;
         hmcstack->Draw("samehist") ;
      } else {
         hmcstack->Draw("e") ;
         hmcstack->Draw("samehist") ;
      }
      hmcsum->Draw("esame") ;
      hdata->DrawCopy("same") ;
      hdata->DrawCopy("axis same") ;
      legend->Draw() ;
      toppad->Update() ;
      toppad->Draw() ;
      TText* title = new TText() ;
      title->SetTextSize(0.040) ;
      title->DrawTextNDC( 0.05, 0.95, hdata->GetTitle() ) ;

      if ( hnstr.Contains("_metsig_") ) {
         drawMETsigBinBoundaries( hmax ) ;
      }
      if ( hnstr.Contains("_met_") ) {
         drawMETBinBoundaries( hmax ) ;
      }
      if ( hnstr.Contains("_mindphi_") ) {
         TLine* line = new TLine() ;
         line -> SetLineStyle(2) ;
         line -> DrawLine( 0.30, 0., 0.30, hmax ) ;
      }


      dmccan->Update() ;
      dmccan->Draw() ;


      bottompad->cd() ;
      hratio->UseCurrentStyle() ;
      gPad->SetLogy(0) ;
      hratio->SetNdivisions(404,"y") ;
      gStyle->SetOptTitle(0) ;
      hratio->SetLabelSize(0.10,"x") ;
      hratio->SetLabelSize(0.10,"y") ;
      hratio->SetTitleSize(0.11,"y") ;
      hratio->SetTitleOffset(0.4,"y") ;

      if ( hdata -> GetMaximum() > 0 ) {
         hratio->SetLineWidth(2) ;
         hratio->SetMarkerStyle(20) ;
         hratio->Draw() ;
         hratio->SetYTitle("Data/MC") ;
         TLine* line = new TLine() ;
         line->SetLineStyle(2) ;
         double xl = hdata->GetBinLowEdge(1) ;
         double xh = hdata->GetBinLowEdge( hdata->GetNbinsX() ) + hdata->GetBinWidth(1) ;
         line->DrawLine( xl, 1., xh, 1. ) ;
      }

      dmccan->Update() ;
      dmccan->Draw() ;


      if ( savePdf ) {
         char filename[10000] ;
         if ( islogy ) {
            sprintf( filename, "outputfiles/%s_logy.pdf", hname_base ) ;
         } else {
            sprintf( filename, "outputfiles/%s_liny.pdf", hname_base ) ;
         }
         dmccan->SaveAs( filename ) ;
      }

   } // drawSet

   //=======================================================================================

   void drawMETsigBinBoundaries( float ymax ) {

      printf("\n Drawing METsig bin boundaries.\n\n") ;

      TLine* line = new TLine() ;
      line -> SetLineStyle(2) ;

      line -> DrawLine(  30., 0.,  30., ymax ) ;
      line -> DrawLine(  50., 0.,  50., ymax ) ;
      line -> DrawLine( 100., 0., 100., ymax ) ;
      line -> DrawLine( 150., 0., 150., ymax ) ;

   }


   //=======================================================================================

   void drawMETBinBoundaries( float ymax ) {

      printf("\n Drawing MET bin boundaries.\n\n") ;

      TLine* line = new TLine() ;
      line -> SetLineStyle(2) ;

      line -> DrawLine( 106., 0., 106., ymax ) ;
      line -> DrawLine( 133., 0., 133., ymax ) ;
      line -> DrawLine( 190., 0., 190., ymax ) ;
      line -> DrawLine( 250., 0., 250., ymax ) ;

   }


   //=======================================================================================
void loadHist(const char* filename, const char* pfx, const char* pat, Bool_t doAdd, Double_t scaleFactor)
{
  cout << " Reading histograms from file: " << filename << endl << flush ;
  TFile inf(filename) ;
  //inf.ReadAll() ;
  TList* list = inf.GetListOfKeys() ;
  TIterator* iter = list->MakeIterator();

  TRegexp re(pat,kTRUE) ;
  std::cout << "pat = " << pat << std::endl ;

  gDirectory->cd("Rint:") ;

  TObject* obj ;
  TKey* key ;
  std::cout << "doAdd = " << (doAdd?"T":"F") << std::endl ;
  std::cout << "loadHist: reading." ;
  while((key=(TKey*)iter->Next())) {
   
    Int_t ridx = TString(key->GetName()).Index(re) ;    
    if (ridx==-1) {
      continue ;
    }

    obj = inf.Get(key->GetName()) ;
    TObject* clone ;
    if (pfx) {

      // Find existing TH1-derived objects
      TObject* oldObj = 0 ;
      if (doAdd){
	oldObj = gDirectory->Get(Form("%s_%s",pfx,obj->GetName())) ;
	if (oldObj && !oldObj->IsA()->InheritsFrom(TH1::Class())) {
	  oldObj = 0 ;
	}
      }
      if (oldObj) {
	clone = oldObj ;
        if ( scaleFactor > 0 ) {
           ((TH1*)clone)->Sumw2() ;
           ((TH1*)clone)->Add((TH1*)obj, scaleFactor) ;
        } else {
           ((TH1*)clone)->Add((TH1*)obj) ;
        }
      } else {
	clone = obj->Clone(Form("%s_%s",pfx,obj->GetName())) ;
      }


    } else {

      // Find existing TH1-derived objects
      TObject* oldObj = 0 ;
      if (doAdd){
	oldObj = gDirectory->Get(key->GetName()) ;
	if (oldObj && !oldObj->IsA()->InheritsFrom(TH1::Class())) {
	  oldObj = 0 ;
	}
      }

      if (oldObj) {
	clone = oldObj ;
        if ( scaleFactor > 0 ) {
           ((TH1*)clone)->Sumw2() ;
           ((TH1*)clone)->Add((TH1*)obj, scaleFactor) ;
        } else {
           ((TH1*)clone)->Add((TH1*)obj) ;
        }
      } else {
	clone = obj->Clone() ;
      }
    }
    if ( scaleFactor > 0 && !doAdd ) {
       ((TH1*) clone)->Sumw2() ;
       ((TH1*) clone)->Scale(scaleFactor) ;
    }
    if (!gDirectory->GetList()->FindObject(clone)) {
      gDirectory->Append(clone) ;
    }
    std::cout << "." ;
    std::cout.flush() ;
  }
  std::cout << std::endl;
  inf.Close() ;
  delete iter ;
}

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
