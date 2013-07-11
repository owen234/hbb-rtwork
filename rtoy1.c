
#include "TRandom.h"
#include "TStyle.h"
#include "TH1.h"

   void rtoy1( float mean_numer = 1., float mean_denom = 25.  ) {

      TRandom ran(12345) ;

      TH1F* hratio = new TH1F("hratio", "ratio", 30, 0., 0.3 ) ;
      TH1F* hn = new TH1F("hn", "numer", 11, -0.5, 10.5 ) ;
      TH1F* hd = new TH1F("hd", "denom", 51, -0.5, 50.5 ) ;

      for ( int i=0; i<10000; i++ ) {
         int gn = ran.Poisson( mean_numer ) ;
         int gd = ran.Poisson( mean_denom ) ;
         float ratio(0.) ;
         if ( gd > 0 ) { ratio = (1.*gn)/(1.*gd) ; }
         hratio -> Fill( ratio ) ;
         hn -> Fill( gn ) ;
         hd -> Fill( gd ) ;
      }
      hratio -> SetFillColor(11) ;

      gStyle -> SetOptStat("emr") ;
      hratio -> Draw() ;


   }

