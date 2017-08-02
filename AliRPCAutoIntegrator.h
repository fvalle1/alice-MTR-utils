/* Copyright(c) 1998-2017, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice                               */

/* $Id$ */

//-------------------------------------------------------------------------
//     Offline MTR/MID detector performance analysis class
//     Authors: Gabriele Gaetano Fronze' (INFN),
//              Filippo Valle (UniTo)
//-------------------------------------------------------------------------

#ifndef AliRPCAutoIntegrator_h
#define AliRPCAutoIntegrator_h

#include "TObject.h"
#include "TNamed.h"
#include "TString.h"
#include "TFile.h"
#include "AliRPCData.h"
#include "AliOCDBRun.h"
#include "AliCDBManager.h"
#include "AliGRPObject.h"
#include "AliCDBStorage.h"
#include "AliMpCDB.h"
#include "AliCDBEntry.h"
#include "AliMpDDLStore.h"
#include "AliMUONTriggerScalers.h"
#include "AliDCSValue.h"
#include "AliRPCValueDCS.h"
#include "AliRPCRunStatistics.h"
#include "AliRPCValueCurrent.h"
#include "AliRPCValueVoltage.h"
#include "AliRPCValueScaler.h"
#include "AliRPCOverflowStatistics.h"


// #include "TClass.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <stdio.h>

#include "TROOT.h"
#include "TSmartTree.h"
#include "TObjArray.h"
#include "TClonesArray.h"
#include "TObjString.h"
#include "TH1F.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TCanvas.h"
#include "TText.h"

typedef struct {
    Int_t Side;
    Int_t Plane;
    Int_t RPC;
} RPC;

class AliRPCAutoIntegrator : public TObject{
public:
    AliRPCAutoIntegrator();
    AliRPCAutoIntegrator(TString RunListFileName, TString AMANDAInputFileName, TString OutputFileName, Bool_t updateOCDB=kTRUE, Bool_t updateAMANDA=kTRUE);
    AliRPCAutoIntegrator(const AliRPCAutoIntegrator &obj)  : TObject(obj){};
    ~AliRPCAutoIntegrator();

private:
    std::vector<AliOCDBRun> fOCDBRunListToAdd;
    TObjArray *fOCDBRunListDownloaded;

    TString fRunListFileName;
    TString fAMANDAInputFileName;
    TString fOutputFileName;

public:
    TFile *fOCDBDataContainer;
    TFile *fAMANDADataContainer;
    TFile *fGlobalDataContainer;
    TFile *fPlotContainer;

private:
    Bool_t fUpdateOCDB;
    Bool_t fUpdateAMANDA;
    Bool_t fExistsRPCDataObject;

    AliRPCData *fAliRPCDataObject;

    static const Int_t kNSides=2;
    static const Int_t kNPlanes=4;
    static const Int_t kNRPC=9;
    static const Int_t kNLocalBoards=234;
    static const ULong64_t kFullScale=65535;
    static const Int_t kNCathodes=2;
    static const TString *fSides;
    static const Int_t *fPlanes;
    static const TString *fCathodes;
    //array per la conversione di iRPC={0,17} in iRPC={1,9}x{inside,outside}
    static const Int_t *kRPCIndexes;
    static const Int_t *kRPCSides;
    static const Int_t *kLBToRPC;
    Double_t fRPCAreas[kNRPC][kNPlanes];
    Double_t fLBAreas[kNLocalBoards][kNPlanes];
    Double_t fTinyArea[kNPlanes];
    Double_t fLittleArea[kNPlanes];
    Double_t fNormalArea[kNPlanes];
    Double_t fBigArea[kNPlanes];
    static const Int_t *fColors;//[kNRPC] = {kBlack,kRed,kGreen,kBlue,kYellow,kMagenta,kCyan,kGray,kOrange};
    static const Int_t *fStyles;//[kNPlanes]={20,24,21,25};
    

    TString checkTokenBashCommand = "if [[ \"`alien-token-info | grep \"still valid\" `\" != \"\" ]]; then echo \"1\"; else echo \"0\"; fi";
    Bool_t checkAlienToken() {
        Bool_t returnValue = kFALSE;
        FILE * f = popen(checkTokenBashCommand.Data(), "r");
        char buf[1];
        size_t read = fread((void *)&buf[0], 1, 1, f);
        returnValue = (buf[0] == '1');
        pclose(f);
        return returnValue;
    }
    void initAlienToken(TString userName){
        gROOT->ProcessLine(Form(".!alien-token-init %s",userName.Data()));
    }

public:
//    TTree *fOCDBTree;
    TSmartTree *fOCDBDataTree[kNSides][kNPlanes][kNRPC];
    TSmartTree *fOCDBRPCScalersTree[kNCathodes][kNSides][kNPlanes][kNRPC];
    TSmartTree *fOCDBLBScalersTree[kNCathodes][kNPlanes][kNLocalBoards];
    TBranch *fOCDBDataTreeBranch[kNSides][kNPlanes][kNRPC];
    TBranch *fOCDBRPCScalersTreeBranch[kNCathodes][kNSides][kNPlanes][kNRPC];
    TBranch *fOCDBLBScalersTreeBranch[kNCathodes][kNPlanes][kNLocalBoards];
    AliRPCValueDCS *fOCDBDataTreeBufferW[kNSides][kNPlanes][kNRPC];
    AliRPCValueScaler *fOCDBRPCScalersTreeBufferW[kNCathodes][kNSides][kNPlanes][kNRPC];
    AliRPCValueScaler *fOCDBLBScalersTreeBufferW[kNCathodes][kNPlanes][kNLocalBoards];
//    AliRPCValueDCS *fOCDBDataTreeBufferR[kNSides][kNPlanes][kNRPC];
//    AliRPCValueScaler *fOCDBRPCScalersTreeBufferR[2][kNSides][kNPlanes][kNRPC];
//    AliRPCValueScaler *fOCDBLBScalersTreeBufferR[kNCathodes][kNPlanes][kNLocalBoards];


//    TTree *fAMANDATree;
    TSmartTree *fAMANDADataTree[kNSides][kNPlanes][kNRPC];
    TBranch *fAMANDADataTreeBranch[kNSides][kNPlanes][kNRPC];
    AliRPCValueDCS *fAMANDADataTreeBufferW[kNSides][kNPlanes][kNRPC];
//    AliRPCValueDCS *fAMANDADataTreeBufferR[kNSides][kNPlanes][kNRPC];
    
//    TTree *fGlobalTree;
    TSmartTree *fGlobalDataTree[kNSides][kNPlanes][kNRPC];
    TBranch *fGlobalDataTreeBranch[kNSides][kNPlanes][kNRPC];
    AliRPCValueDCS *fGlobalDataTreeBufferW[kNSides][kNPlanes][kNRPC];
//    AliRPCValueDCS *fGlobalDataTreeBufferR[kNSides][kNPlanes][kNRPC];

private:
    Bool_t CheckPointer(TNamed *pointer){
        Bool_t output=!pointer;
        if(output) {
            printf("\nproblem with %s\n",pointer->GetName());
        }
        return output;
    }

    void SetupSmartTree(TString ObjectName, TFile *file, TSmartTree *smartTree, AliRPCValueDCS* smartTreeBuffer) {
        file->cd();
        if (!(file->GetListOfKeys()->Contains(ObjectName))) {
            smartTree = new TSmartTree(ObjectName, ObjectName);
            smartTree->Branch(ObjectName, smartTreeBuffer);
            smartTree->Write(ObjectName);
            cout << "Created ";
        } else {
            file->GetObject(ObjectName, smartTree);
            smartTree->SetBranchAddress(ObjectName, &smartTreeBuffer);
            cout << "Loading ";
        }
        cout << ObjectName << " #Entries: " << smartTree->GetEntries() << "\r";
    }

public:

    void InitDataMembers();

    void RunAutoIntegrator();

    void OCDBRunListReader();
    void OCDBDataToCParser(bool blockMode = true, UInt_t blockSize = 10);
    bool OCDBDataToCParserBlocks(Int_t blockNumber = -1, UInt_t blockSize = 10);
    void OCDBDarkCurrentSetter();
    void AMANDATextToCParser();
    void FillAliRPCData();
    void FillAliRPCData(UInt_t year);
    void Aggregator();
    void Subtractor();
    void Integrator();
    void AMANDASetDataMembers();

    
private:
    inline Bool_t checkFileExistance(TString fileName) {
        ifstream f(fileName.Data());
        return f.good();
    }
    
    Bool_t IsFEERIC(Int_t iRPC, Int_t iSide, Int_t iPlane){
        if(iPlane==3&&iSide==0&&iRPC==3) return kTRUE;
        else return kFALSE;
    }
    static void PrintWhichRPC(Int_t iRPC, Int_t iSide, Int_t iPlane);
    static void PrintWhichRPC(RPC RPC);
    Bool_t IsRunInList(std::vector<UInt_t> vector, UInt_t number);


ClassDef(AliRPCAutoIntegrator,9);
};

#endif
