

#include "doSkimSlim.C"

   void slimall() {

       char rtdir[10000] ;
       //sprintf( rtdir, "/data/cms/hadronic-susy-bjets/hbb/reduced-trees-july03-2013/" ) ;
       //sprintf( rtdir, "/Users/owen/work/cms/hadronic-susy-bjets/hbb/reduced-trees-july08-2013/" ) ;
       sprintf( rtdir, "/Users/owen/work/cms/hadronic-susy-bjets/hbb/reduced-trees-july11-2013-pt20/" ) ;
       //sprintf( rtdir, "/Users/owen/work/cms/hadronic-susy-bjets/hbb/reduced-trees-july22-2013-nobeta/" ) ;

       char filenames[500][10000] ;
       int nfiles(0) ;

       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.QCD_Pt-1000to1400_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1_AODSIM_UCSB1820_v69-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v3_AODSIM_UCSB1814_v69-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.QCD_Pt-1400to1800_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1_AODSIM_UCSB1821_v69-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.QCD_Pt-170to300_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2_AODSIM_UCSB1815_v69-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.QCD_Pt-1800_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1_AODSIM_UCSB1822_v69-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.QCD_Pt-300to470_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2_AODSIM_UCSB1816_v69-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.QCD_Pt-470to600_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2_AODSIM_UCSB1817_v69-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.QCD_Pt-600to800_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2_AODSIM_UCSB1818_v69-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.QCD_Pt-800to1000_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2_AODSIM_UCSB1819_v69-skim.root") ;

       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.TTJets_SemiLeptMGDecays_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7C-v1_AODSIM_UCSB1800_v69-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.TTJets_FullLeptMGDecays_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7C-v2_AODSIM_UCSB1799_v69-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.TTJets_SemiLeptDecays_8TeV-sherpa_Summer12_DR53X-PU_S10_START53_V19-v1_AODSIM_UCSB1806_v69-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.TTJets_DileptDecays_8TeV-sherpa_Summer12_DR53X-PU_S10_START53_V19-v1_AODSIM_UCSB1804_v69-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1_AODSIM_UCSB1798_v69-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.TT_8TeV-mcatnlo_Summer12_DR53X-PU_S10_START53_V7A-v1_AODSIM_UCSB1837_v69-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.TT_CT10_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v2_AODSIM_UCSB1838_v69-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.TTJets_HadronicMGDecays_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A_ext-v1_AODSIM_UCSB1848_v69-skim.root") ;

       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.TChihh-HbbHbb_mHiggsino-200_mLSP-1_8TeV-Pythia6Z_jgsmith-SMS-HbbHbb_mHiggsino-200_mLSP-1_1_UCSB1807_v69.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.TChihh-HbbHbb_mHiggsino-350_mLSP-1_8TeV-Pythia6Z_jgsmith-SMS-HbbHbb_mHiggsino-350_mLSP-1_1_UCSB1811_v69.root") ;

       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.SMS-HbbHbb_mHiggsino-200_mLSP-1_8TeV-Pythia6Z_jgsmith_UCSB1807_v69.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.SMS-HbbHbb_mHiggsino-250_mLSP-1_8TeV-Pythia6Z_jgsmith_UCSB1809_v69.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.SMS-HbbHbb_mHiggsino-300_mLSP-1_8TeV-Pythia6Z_jgsmith_UCSB1810_v69.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.SMS-HbbHbb_mHiggsino-350_mLSP-1_8TeV-Pythia6Z_jgsmith_UCSB1811_v69.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.SMS-HbbHbb_mHiggsino-400_mLSP-1_8TeV-Pythia6Z_jgsmith_UCSB1812_v69.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.SMS-HbbHbb_mHiggsino-450_mLSP-1_8TeV-Pythia6Z_jgsmith_UCSB1808_v69.root") ;

       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.HiggsinoNLSP_chargino130_to_500_bino1_TChihh_v69.root" ) ;

       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.ZJetsToNuNu_100_HT_200_TuneZ2Star_8TeV_madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1_AODSIM_UCSB1832_v69-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.ZJetsToNuNu_200_HT_400_TuneZ2Star_8TeV_madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1_AODSIM_UCSB1833_v69-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.ZJetsToNuNu_200_HT_400_TuneZ2Star_8TeV_madgraph_ext_Summer12_DR53X-PU_S10_START53_V7A-v1_AODSIM_UCSB1834_v69-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.ZJetsToNuNu_400_HT_inf_TuneZ2Star_8TeV_madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1_AODSIM_UCSB1831_v69-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.ZJetsToNuNu_400_HT_inf_TuneZ2Star_8TeV_madgraph_ext_Summer12_DR53X-PU_S10_START53_V7A-v1_AODSIM_UCSB1835_v69-skim.root") ;


       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012A-13Jul2012-v1_AOD_UCSB1825_v69.1-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012A-13Jul2012-v1_AOD_UCSB1825_v69.2-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012A-13Jul2012-v1_AOD_UCSB1825_v69.3-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012A-13Jul2012-v1_AOD_UCSB1825_v69.4-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012A-13Jul2012-v1_AOD_UCSB1825_v69.5-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012A-13Jul2012-v1_AOD_UCSB1825_v69.6-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012A-13Jul2012-v1_AOD_UCSB1825_v69.7-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012A-13Jul2012-v1_AOD_UCSB1825_v69.8-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012A-13Jul2012-v1_AOD_UCSB1825_v69.9-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012B-13Jul2012-v1_AOD_UCSB1826_v69.1-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012B-13Jul2012-v1_AOD_UCSB1826_v69.10-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012B-13Jul2012-v1_AOD_UCSB1826_v69.11-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012B-13Jul2012-v1_AOD_UCSB1826_v69.12-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012B-13Jul2012-v1_AOD_UCSB1826_v69.13-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012B-13Jul2012-v1_AOD_UCSB1826_v69.14-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012B-13Jul2012-v1_AOD_UCSB1826_v69.15-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012B-13Jul2012-v1_AOD_UCSB1826_v69.16-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012B-13Jul2012-v1_AOD_UCSB1826_v69.17-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012B-13Jul2012-v1_AOD_UCSB1826_v69.18-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012B-13Jul2012-v1_AOD_UCSB1826_v69.19-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012B-13Jul2012-v1_AOD_UCSB1826_v69.2-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012B-13Jul2012-v1_AOD_UCSB1826_v69.3-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012B-13Jul2012-v1_AOD_UCSB1826_v69.4-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012B-13Jul2012-v1_AOD_UCSB1826_v69.5-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012B-13Jul2012-v1_AOD_UCSB1826_v69.6-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012B-13Jul2012-v1_AOD_UCSB1826_v69.7-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012B-13Jul2012-v1_AOD_UCSB1826_v69.8-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012B-13Jul2012-v1_AOD_UCSB1826_v69.9-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012C-24Aug2012-v1_AOD_UCSB1827_v69.1-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012C-24Aug2012-v1_AOD_UCSB1827_v69.2-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012C-24Aug2012-v1_AOD_UCSB1827_v69.3-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012C-24Aug2012-v1_AOD_UCSB1827_v69.4-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012C-24Aug2012-v1_AOD_UCSB1827_v69.5-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012C-24Aug2012-v1_AOD_UCSB1827_v69.6-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012C-24Aug2012-v1_AOD_UCSB1827_v69.7-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012C-24Aug2012-v1_AOD_UCSB1827_v69.8-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012C-24Aug2012-v1_AOD_UCSB1827_v69.9-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012C-PromptReco-v2_AOD_UCSB1828_v69.1-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012C-PromptReco-v2_AOD_UCSB1828_v69.10-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012C-PromptReco-v2_AOD_UCSB1828_v69.11-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012C-PromptReco-v2_AOD_UCSB1828_v69.12-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012C-PromptReco-v2_AOD_UCSB1828_v69.13-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012C-PromptReco-v2_AOD_UCSB1828_v69.14-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012C-PromptReco-v2_AOD_UCSB1828_v69.15-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012C-PromptReco-v2_AOD_UCSB1828_v69.16-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012C-PromptReco-v2_AOD_UCSB1828_v69.17-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012C-PromptReco-v2_AOD_UCSB1828_v69.18-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012C-PromptReco-v2_AOD_UCSB1828_v69.19-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012C-PromptReco-v2_AOD_UCSB1828_v69.2-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012C-PromptReco-v2_AOD_UCSB1828_v69.3-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012C-PromptReco-v2_AOD_UCSB1828_v69.4-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012C-PromptReco-v2_AOD_UCSB1828_v69.5-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012C-PromptReco-v2_AOD_UCSB1828_v69.6-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012C-PromptReco-v2_AOD_UCSB1828_v69.7-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012C-PromptReco-v2_AOD_UCSB1828_v69.8-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012C-PromptReco-v2_AOD_UCSB1828_v69.9-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012D-PromptReco-v1_AOD_UCSB1829_v69.1-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012D-PromptReco-v1_AOD_UCSB1829_v69.10-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012D-PromptReco-v1_AOD_UCSB1829_v69.11-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012D-PromptReco-v1_AOD_UCSB1829_v69.12-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012D-PromptReco-v1_AOD_UCSB1829_v69.13-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012D-PromptReco-v1_AOD_UCSB1829_v69.14-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012D-PromptReco-v1_AOD_UCSB1829_v69.15-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012D-PromptReco-v1_AOD_UCSB1829_v69.16-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012D-PromptReco-v1_AOD_UCSB1829_v69.17-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012D-PromptReco-v1_AOD_UCSB1829_v69.18-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012D-PromptReco-v1_AOD_UCSB1829_v69.19-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012D-PromptReco-v1_AOD_UCSB1829_v69.2-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012D-PromptReco-v1_AOD_UCSB1829_v69.3-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012D-PromptReco-v1_AOD_UCSB1829_v69.4-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012D-PromptReco-v1_AOD_UCSB1829_v69.5-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012D-PromptReco-v1_AOD_UCSB1829_v69.6-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012D-PromptReco-v1_AOD_UCSB1829_v69.7-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012D-PromptReco-v1_AOD_UCSB1829_v69.8-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012D-PromptReco-v1_AOD_UCSB1829_v69.9-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012D-PromptReco-v1_AOD_UCSB1830_v69.1-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012D-PromptReco-v1_AOD_UCSB1830_v69.2-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012D-PromptReco-v1_AOD_UCSB1830_v69.3-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012D-PromptReco-v1_AOD_UCSB1830_v69.4-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012D-PromptReco-v1_AOD_UCSB1830_v69.5-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012D-PromptReco-v1_AOD_UCSB1830_v69.6-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012D-PromptReco-v1_AOD_UCSB1830_v69.7-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012D-PromptReco-v1_AOD_UCSB1830_v69.8-skim.root") ;
       sprintf( filenames[nfiles++], "reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.MET_Run2012D-PromptReco-v1_AOD_UCSB1830_v69.9-skim.root") ;


       for ( int fi=0; fi<nfiles; fi++ ) {
          char dirfile[10000] ;
          sprintf( dirfile, "%s/%s", rtdir, filenames[fi] ) ;
          printf("  %2d : %s\n", fi, dirfile ) ;
          doSkimSlim( dirfile, 1 ) ;
       }

   }

