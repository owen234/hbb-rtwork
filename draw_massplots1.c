
#include "histio.c"

   void draw_massplots1( const char* infile = "outputfiles/truthstudy1.root" ) {

      loadHist( infile ) ;

      TH1F* h_amh_b1j_b2j__2b = (TH1F*) gDirectory -> FindObject( "h_amh_b1j_b2j__2b" ) ;
      TH1F* h_amh_b1b2_jj__2b = (TH1F*) gDirectory -> FindObject( "h_amh_b1b2_jj__2b" ) ;
      TH1F* h_amh_b1x_b2j__2b = (TH1F*) gDirectory -> FindObject( "h_amh_b1x_b2j__2b" ) ;
      TH1F* h_amh_b1j_b2x__2b = (TH1F*) gDirectory -> FindObject( "h_amh_b1j_b2x__2b" ) ;
      TH1F* h_amh_b1b2_jx__2b = (TH1F*) gDirectory -> FindObject( "h_amh_b1b2_jx__2b" ) ;

      TH1F* h_amh_b1j_b2j__4b = (TH1F*) gDirectory -> FindObject( "h_amh_b1j_b2j__4b" ) ;
      TH1F* h_amh_b1b2_jj__4b = (TH1F*) gDirectory -> FindObject( "h_amh_b1b2_jj__4b" ) ;
      TH1F* h_amh_b1x_b2j__4b = (TH1F*) gDirectory -> FindObject( "h_amh_b1x_b2j__4b" ) ;
      TH1F* h_amh_b1j_b2x__4b = (TH1F*) gDirectory -> FindObject( "h_amh_b1j_b2x__4b" ) ;
      TH1F* h_amh_b1b2_jx__4b = (TH1F*) gDirectory -> FindObject( "h_amh_b1b2_jx__4b" ) ;



      TH1F* h_amh_0x__2b = (TH1F*) h_amh_b1j_b2j__2b -> Clone( "h_amh_0x__2b" ) ;
      h_amh_0x__2b -> Add( h_amh_b1b2_jj__2b ) ;

      TH1F* h_amh_1x__2b = (TH1F*) h_amh_b1x_b2j__2b -> Clone( "h_amh_1x__2b" ) ;
      h_amh_1x__2b -> Add( h_amh_b1j_b2x__2b ) ;
      h_amh_1x__2b -> Add( h_amh_b1b2_jx__2b ) ;

      TH1F* h_amh_lt2x__2b = (TH1F*) h_amh_b1j_b2j__2b -> Clone( "h_amh_lt2x__2b" ) ;
      h_amh_lt2x__2b -> Add( h_amh_b1b2_jj__2b ) ;
      h_amh_lt2x__2b -> Add( h_amh_b1x_b2j__2b ) ;
      h_amh_lt2x__2b -> Add( h_amh_b1j_b2x__2b ) ;
      h_amh_lt2x__2b -> Add( h_amh_b1b2_jx__2b ) ;



      TH1F* h_amh_0x__4b = (TH1F*) h_amh_b1j_b2j__4b -> Clone( "h_amh_0x__4b" ) ;
      h_amh_0x__4b -> Add( h_amh_b1b2_jj__4b ) ;

      TH1F* h_amh_1x__4b = (TH1F*) h_amh_b1x_b2j__4b -> Clone( "h_amh_1x__4b" ) ;
      h_amh_1x__4b -> Add( h_amh_b1j_b2x__4b ) ;
      h_amh_1x__4b -> Add( h_amh_b1b2_jx__4b ) ;

      TH1F* h_amh_lt2x__4b = (TH1F*) h_amh_b1j_b2j__4b -> Clone( "h_amh_lt2x__4b" ) ;
      h_amh_lt2x__4b -> Add( h_amh_b1b2_jj__4b ) ;
      h_amh_lt2x__4b -> Add( h_amh_b1x_b2j__4b ) ;
      h_amh_lt2x__4b -> Add( h_amh_b1j_b2x__4b ) ;
      h_amh_lt2x__4b -> Add( h_amh_b1b2_jx__4b ) ;




   } // draw_massplots1.



