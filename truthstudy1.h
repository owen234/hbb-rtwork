//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Jun 14 16:17:47 2013 by ROOT version 5.34/08
// from TChain reducedTree/
//////////////////////////////////////////////////////////

#ifndef truthstudy1_h
#define truthstudy1_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class truthstudy1 {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Double_t        weight;
   Double_t        weight2;
   Double_t        weight3;
   Float_t         PUweight;
   Bool_t          cutPV;
   Bool_t          passCleaning;
   Bool_t          buggyEvent;
   Int_t           nGoodPV;
   Int_t           njets20;
   Int_t           njets30;
   Int_t           nGluonsSplitToLF;
   Int_t           nGluonsSplitToC;
   Int_t           nGluonsSplitToB;
   Int_t           nElectrons;
   Int_t           nMuons;
   Int_t           nTausLoose;
   Float_t         higgsMbb1MassDiff;
   Float_t         higgsMbb2MassDiff;
   Int_t           higgsMbb1MassDiff_correct;
   Float_t         deltaRmax_hh;
   Float_t         deltaRmin_hh;
   Float_t         higgs1jetpt1;
   Float_t         higgs1jetpt2;
   Float_t         higgs2jetpt1;
   Float_t         higgs2jetpt2;
   Float_t         higgs1CSV1;
   Float_t         higgs1CSV2;
   Float_t         higgs2CSV1;
   Float_t         higgs2CSV2;
   Float_t         higgs1partonId1;
   Float_t         higgs1partonId2;
   Float_t         higgs2partonId1;
   Float_t         higgs2partonId2;
   Float_t         higgs1partonMomId1;
   Float_t         higgs1partonMomId2;
   Float_t         higgs2partonMomId1;
   Float_t         higgs2partonMomId2;
   Bool_t          passMC_DiCentralPFJet30_PFMET80_BTagCSV07;
   Bool_t          passMC_DiPFJet80_DiPFJet30_BTagCSVd07d05;
   Bool_t          passMC_PFMET150;
   Float_t         MET;
   Float_t         METsig;
   Float_t         METsig_2012;
   Float_t         maxDeltaPhi_bb_bb;
   Float_t         minDeltaPhi30;
   Float_t         CSVbest1;
   Float_t         CSVbest2;
   Float_t         CSVbest3;
   Float_t         CSVbest4;
   Float_t         jetpt1;
   Float_t         jetpt2;
   Float_t         jetpt3;
   Float_t         jetpt4;
   Int_t           nIsoTracks15_005_03;
   Int_t           nIsoTracks5_005_03;

   // List of branches
   TBranch        *b_weight;   //!
   TBranch        *b_weight2;   //!
   TBranch        *b_weight3;   //!
   TBranch        *b_PUweight;   //!
   TBranch        *b_cutPV;   //!
   TBranch        *b_passCleaning;   //!
   TBranch        *b_buggyEvent;   //!
   TBranch        *b_nGoodPV;   //!
   TBranch        *b_njets20;   //!
   TBranch        *b_njets30;   //!
   TBranch        *b_nGluonsSplitToLF;   //!
   TBranch        *b_nGluonsSplitToC;   //!
   TBranch        *b_nGluonsSplitToB;   //!
   TBranch        *b_nElectrons;   //!
   TBranch        *b_nMuons;   //!
   TBranch        *b_nTausLoose;   //!
   TBranch        *b_higgsMbb1MassDiff;   //!
   TBranch        *b_higgsMbb2MassDiff;   //!
   TBranch        *b_higgsMbb1MassDiff_correct;   //!
   TBranch        *b_deltaRmax_hh;   //!
   TBranch        *b_deltaRmin_hh;   //!
   TBranch        *b_higgs1jetpt1;   //!
   TBranch        *b_higgs1jetpt2;   //!
   TBranch        *b_higgs2jetpt1;   //!
   TBranch        *b_higgs2jetpt2;   //!
   TBranch        *b_higgs1CSV1;   //!
   TBranch        *b_higgs1CSV2;   //!
   TBranch        *b_higgs2CSV1;   //!
   TBranch        *b_higgs2CSV2;   //!
   TBranch        *b_higgs1partonId1;   //!
   TBranch        *b_higgs1partonId2;   //!
   TBranch        *b_higgs2partonId1;   //!
   TBranch        *b_higgs2partonId2;   //!
   TBranch        *b_higgs1partonMomId1;   //!
   TBranch        *b_higgs1partonMomId2;   //!
   TBranch        *b_higgs2partonMomId1;   //!
   TBranch        *b_higgs2partonMomId2;   //!
   TBranch        *b_passMC_DiCentralPFJet30_PFMET80_BTagCSV07;   //!
   TBranch        *b_passMC_DiPFJet80_DiPFJet30_BTagCSVd07d05;   //!
   TBranch        *b_passMC_PFMET150;   //!
   TBranch        *b_MET;   //!
   TBranch        *b_METsig;   //!
   TBranch        *b_METsig_2012;   //!
   TBranch        *b_maxDeltaPhi_bb_bb;   //!
   TBranch        *b_minDeltaPhi30;   //!
   TBranch        *b_CSVbest1;   //!
   TBranch        *b_CSVbest2;   //!
   TBranch        *b_CSVbest3;   //!
   TBranch        *b_CSVbest4;   //!
   TBranch        *b_jetpt1;   //!
   TBranch        *b_jetpt2;   //!
   TBranch        *b_jetpt3;   //!
   TBranch        *b_jetpt4;   //!
   TBranch        *b_nIsoTracks15_005_03;   //!
   TBranch        *b_nIsoTracks5_005_03;   //!

   char samplename[1000] ;

   truthstudy1( const char* samplename_arg = "madgraph" );
   virtual ~truthstudy1();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

   void draw_mass_canvas( const char* cname, const char* ctitle, TH1* hm1a, TH1* hm1b, TH1* hm2a, TH1* hm2b, TH1* havema, TH1* havemb, TH1* hdma, TH1* hdmb, bool setmax=true ) ;

   void draw_pt_canvas( const char* cname, const char* ctitle, TH1* hptcsv1_2b, TH1* hptcsv1_4b,
                                                            TH1* hptcsv2_2b, TH1* hptcsv2_4b,
                                                            TH1* hptcsv3_2b, TH1* hptcsv3_4b,
                                                            TH1* hptcsv4_2b, TH1* hptcsv4_4b,
                                                            bool setmax=true ) ;

   void draw_pt_canvas_h( const char* cname, const char* ctitle, TH1* hptcsv1_2b, TH1* hptcsv1_4b,
                                                            TH1* hptcsv2_2b, TH1* hptcsv2_4b,
                                                            TH1* hptcsv3_2b, TH1* hptcsv3_4b,
                                                            TH1* hptcsv4_2b, TH1* hptcsv4_4b,
                                                            bool setmax=true ) ;

   void draw_pt_canvas3( const char* cname, const char* ctitle, TH1* hptcsv1_2b, TH1* hptcsv1_4b, TH1* hptcsv1_3b,
                                                            TH1* hptcsv2_2b, TH1* hptcsv2_4b, TH1* hptcsv2_3b,
                                                            TH1* hptcsv3_2b, TH1* hptcsv3_4b, TH1* hptcsv3_3b,
                                                            TH1* hptcsv4_2b, TH1* hptcsv4_4b, TH1* hptcsv4_3b,
                                                            bool setmax=true ) ;

   void draw_hspt_canvas( const char* cname, const char* ctitle, TH1* hhspth2b, TH1* hhspth4b, TH1* hhsptl2b, TH1* hhsptl4b, bool setmax=true ) ;

   void draw_code_ratio_canvas( const char* cname, const char* ctitle, TH1* hca, TH1* hcb, TH1* hra, TH1* hrb ) ;

};

#endif

#ifdef truthstudy1_cxx
truthstudy1::truthstudy1( const char* samplename_arg ) : fChain(0) 
{
   sprintf( samplename, "%s", samplename_arg ) ;
   TChain * chain(0x0) ;
   if ( strcmp( samplename, "madgraph" ) == 0 ) {
      chain = new TChain("reducedTree","");
      //chain->Add("/data/cms/hadronic-susy-bjets/hbb/reduced-trees-july03-2013/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.TTJets_SemiLeptMGDecays_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7C-v1_AODSIM_UCSB1800_v69-slimskim.root/reducedTree");
      //chain->Add("../reduced-trees-july03-2013/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.TTJets_SemiLeptMGDecays_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7C-v1_AODSIM_UCSB1800_v69-slimskim.root/reducedTree");
      chain->Add("../reduced-trees-july08-2013/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.TTJets_SemiLeptMGDecays_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7C-v1_AODSIM_UCSB1800_v69-slimskim.root/reducedTree");
   } else if ( strcmp( samplename, "powheg" ) == 0 ) {
      chain = new TChain("reducedTree","");
      chain->Add("../reduced-trees-july08-2013/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.TT_CT10_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v2_AODSIM_UCSB1838_v69-slimskim.root/reducedTree");
   } else if ( strcmp( samplename, "mcatnlo" ) == 0 ) {
      chain = new TChain("reducedTree","");
      chain->Add("../reduced-trees-july08-2013/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.TT_8TeV-mcatnlo_Summer12_DR53X-PU_S10_START53_V7A-v1_AODSIM_UCSB1837_v69-slimskim.root/reducedTree");
   } else if ( strcmp( samplename, "sherpa" ) == 0 ) {
      chain = new TChain("reducedTree","");
      //chain->Add("/data/cms/hadronic-susy-bjets/hbb/reduced-trees-july03-2013/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.TTJets_SemiLeptDecays_8TeV-sherpa_Summer12_DR53X-PU_S10_START53_V19-v1_AODSIM_UCSB1806_v69-slimskim.root/reducedTree");
      chain->Add("../reduced-trees-july03-2013/reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.TTJets_SemiLeptDecays_8TeV-sherpa_Summer12_DR53X-PU_S10_START53_V19-v1_AODSIM_UCSB1806_v69-slimskim.root/reducedTree");
   }
   if ( chain == 0x0 ) return ;

   Init(chain);
}

truthstudy1::~truthstudy1()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t truthstudy1::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t truthstudy1::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void truthstudy1::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("weight", &weight, &b_weight);
   fChain->SetBranchAddress("weight2", &weight2, &b_weight2);
   fChain->SetBranchAddress("weight3", &weight3, &b_weight3);
   fChain->SetBranchAddress("PUweight", &PUweight, &b_PUweight);
   fChain->SetBranchAddress("cutPV", &cutPV, &b_cutPV);
   fChain->SetBranchAddress("passCleaning", &passCleaning, &b_passCleaning);
   fChain->SetBranchAddress("buggyEvent", &buggyEvent, &b_buggyEvent);
   fChain->SetBranchAddress("nGoodPV", &nGoodPV, &b_nGoodPV);
   fChain->SetBranchAddress("njets20", &njets20, &b_njets20);
   fChain->SetBranchAddress("njets30", &njets30, &b_njets30);
   fChain->SetBranchAddress("nGluonsSplitToLF", &nGluonsSplitToLF, &b_nGluonsSplitToLF);
   fChain->SetBranchAddress("nGluonsSplitToC", &nGluonsSplitToC, &b_nGluonsSplitToC);
   fChain->SetBranchAddress("nGluonsSplitToB", &nGluonsSplitToB, &b_nGluonsSplitToB);
   fChain->SetBranchAddress("nElectrons", &nElectrons, &b_nElectrons);
   fChain->SetBranchAddress("nMuons", &nMuons, &b_nMuons);
   fChain->SetBranchAddress("nTausLoose", &nTausLoose, &b_nTausLoose);
   fChain->SetBranchAddress("higgsMbb1MassDiff", &higgsMbb1MassDiff, &b_higgsMbb1MassDiff);
   fChain->SetBranchAddress("higgsMbb2MassDiff", &higgsMbb2MassDiff, &b_higgsMbb2MassDiff);
   fChain->SetBranchAddress("higgsMbb1MassDiff_correct", &higgsMbb1MassDiff_correct, &b_higgsMbb1MassDiff_correct);
   fChain->SetBranchAddress("deltaRmax_hh", &deltaRmax_hh, &b_deltaRmax_hh);
   fChain->SetBranchAddress("deltaRmin_hh", &deltaRmin_hh, &b_deltaRmin_hh);
   fChain->SetBranchAddress("higgs1jetpt1", &higgs1jetpt1, &b_higgs1jetpt1);
   fChain->SetBranchAddress("higgs1jetpt2", &higgs1jetpt2, &b_higgs1jetpt2);
   fChain->SetBranchAddress("higgs2jetpt1", &higgs2jetpt1, &b_higgs2jetpt1);
   fChain->SetBranchAddress("higgs2jetpt2", &higgs2jetpt2, &b_higgs2jetpt2);
   fChain->SetBranchAddress("higgs1CSV1", &higgs1CSV1, &b_higgs1CSV1);
   fChain->SetBranchAddress("higgs1CSV2", &higgs1CSV2, &b_higgs1CSV2);
   fChain->SetBranchAddress("higgs2CSV1", &higgs2CSV1, &b_higgs2CSV1);
   fChain->SetBranchAddress("higgs2CSV2", &higgs2CSV2, &b_higgs2CSV2);
   fChain->SetBranchAddress("higgs1partonId1", &higgs1partonId1, &b_higgs1partonId1);
   fChain->SetBranchAddress("higgs1partonId2", &higgs1partonId2, &b_higgs1partonId2);
   fChain->SetBranchAddress("higgs2partonId1", &higgs2partonId1, &b_higgs2partonId1);
   fChain->SetBranchAddress("higgs2partonId2", &higgs2partonId2, &b_higgs2partonId2);
   fChain->SetBranchAddress("higgs1partonMomId1", &higgs1partonMomId1, &b_higgs1partonMomId1);
   fChain->SetBranchAddress("higgs1partonMomId2", &higgs1partonMomId2, &b_higgs1partonMomId2);
   fChain->SetBranchAddress("higgs2partonMomId1", &higgs2partonMomId1, &b_higgs2partonMomId1);
   fChain->SetBranchAddress("higgs2partonMomId2", &higgs2partonMomId2, &b_higgs2partonMomId2);
   fChain->SetBranchAddress("passMC_DiCentralPFJet30_PFMET80_BTagCSV07", &passMC_DiCentralPFJet30_PFMET80_BTagCSV07, &b_passMC_DiCentralPFJet30_PFMET80_BTagCSV07);
   fChain->SetBranchAddress("passMC_DiPFJet80_DiPFJet30_BTagCSVd07d05", &passMC_DiPFJet80_DiPFJet30_BTagCSVd07d05, &b_passMC_DiPFJet80_DiPFJet30_BTagCSVd07d05);
   fChain->SetBranchAddress("passMC_PFMET150", &passMC_PFMET150, &b_passMC_PFMET150);
   fChain->SetBranchAddress("MET", &MET, &b_MET);
   fChain->SetBranchAddress("METsig", &METsig, &b_METsig);
   fChain->SetBranchAddress("METsig_2012", &METsig_2012, &b_METsig_2012);
   fChain->SetBranchAddress("maxDeltaPhi_bb_bb", &maxDeltaPhi_bb_bb, &b_maxDeltaPhi_bb_bb);
   fChain->SetBranchAddress("minDeltaPhi30", &minDeltaPhi30, &b_minDeltaPhi30);
   fChain->SetBranchAddress("CSVbest1", &CSVbest1, &b_CSVbest1);
   fChain->SetBranchAddress("CSVbest2", &CSVbest2, &b_CSVbest2);
   fChain->SetBranchAddress("CSVbest3", &CSVbest3, &b_CSVbest3);
   fChain->SetBranchAddress("CSVbest4", &CSVbest4, &b_CSVbest4);
   fChain->SetBranchAddress("jetpt1", &jetpt1, &b_jetpt1);
   fChain->SetBranchAddress("jetpt2", &jetpt2, &b_jetpt2);
   fChain->SetBranchAddress("jetpt3", &jetpt3, &b_jetpt3);
   fChain->SetBranchAddress("jetpt4", &jetpt4, &b_jetpt4);
   fChain->SetBranchAddress("nIsoTracks15_005_03", &nIsoTracks15_005_03, &b_nIsoTracks15_005_03);
   fChain->SetBranchAddress("nIsoTracks5_005_03", &nIsoTracks5_005_03, &b_nIsoTracks5_005_03);
   Notify();
}

Bool_t truthstudy1::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void truthstudy1::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t truthstudy1::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   if (entry>0) return 1;
   return 1;
}
#endif // #ifdef truthstudy1_cxx
