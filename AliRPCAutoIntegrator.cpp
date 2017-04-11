//
// AliRPCAutoIntegrator.cpp
//
//   Created by Gabriele Gaetano Fronzé
//   Copyright © 2016 Gabriele Gaetano Fronzé. All rights reserved.
//

#include "AliRPCAutoIntegrator.h"

using namespace std;

ClassImp(AliRPCAutoIntegrator);

////////////////////////////////////////////////////////////////////////////////
// Filling of data members (const) needed for conversione notation.
// This method allows a direct filling of arrays even if defined as const void*
////////////////////////////////////////////////////////////////////////////////

static const Int_t RPCIndexes[] = {5,6,7,8,9,9,8,7,6,5,4,3,2,1,1,2,3,4};
const Int_t *AliRPCAutoIntegrator::kRPCIndexes = RPCIndexes;

static const Int_t RPCSides[] = {0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0};
const Int_t *AliRPCAutoIntegrator::kRPCSides = RPCSides;

/*{index from 1 to 234, RPC [1-9], side [0,1]}*/
static const Int_t LBToRPC[][3]={{1,1,0},{2,2,0},{3,2,0},{4,3,0},{5,3,0},{6,4,0},{7,4,0},{8,4,0},{9,6,0},{10,6,0},{11,6,0},{12,7,0},{13,7,0},{14,8,0},{15,8,0},{16,9,0},{17,1,0},{18,2,0},{19,2,0},{20,3,0},{21,3,0},{22,4,0},{23,4,0},{24,4,0},{25,4,0},{26,5,0},{27,5,0},{28,5,0},{29,5,0},{30,6,0},{31,6,0},{32,6,0},{33,6,0},{34,7,0},{35,7,0},{36,8,0},{37,8,0},{38,9,0},{39,1,0},{40,2,0},{41,2,0},{42,3,0},{43,3,0},{44,4,0},{45,4,0},{46,4,0},{47,4,0},{48,5,0},{49,5,0},{50,5,0},{51,5,0},{52,6,0},{53,6,0},{54,6,0},{55,6,0},{56,7,0},{57,7,0},{58,8,0},{59,8,0},{60,9,0},{61,1,0},{62,2,0},{63,2,0},{64,3,0},{65,3,0},{66,4,0},{67,4,0},{68,5,0},{69,5,0},{70,6,0},{71,6,0},{72,7,0},{73,7,0},{74,8,0},{75,8,0},{76,9,0},{77,1,0},{78,2,0},{79,2,0},{80,3,0},{81,3,0},{82,4,0},{83,4,0},{84,5,0},{85,5,0},{86,6,0},{87,6,0},{88,7,0},{89,7,0},{90,8,0},{91,8,0},{92,9,0},{93,1,0},{94,2,0},{95,2,0},{96,3,0},{97,3,0},{98,4,0},{99,4,0},{100,5,0},{101,5,0},{102,6,0},{103,6,0},{104,7,0},{105,7,0},{106,8,0},{107,8,0},{108,9,0},{109,1,0},{110,2,0},{111,3,0},{112,4,0},{113,5,0},{114,6,0},{115,7,0},{116,8,0},{117,9,0},{118,1,1},{119,2,1},{120,2,1},{121,3,1},{122,3,1},{123,4,1},{124,4,1},{125,4,1},{126,6,1},{127,6,1},{128,6,1},{129,7,1},{130,7,1},{131,8,1},{132,8,1},{133,9,1},{134,1,1},{135,2,1},{136,2,1},{137,3,1},{138,3,1},{139,4,1},{140,4,1},{141,4,1},{142,4,1},{143,5,1},{144,5,1},{145,5,1},{146,5,1},{147,6,1},{148,6,1},{149,6,1},{150,6,1},{151,7,1},{152,7,1},{153,8,1},{154,8,1},{155,9,1},{156,1,1},{157,2,1},{158,2,1},{159,3,1},{160,3,1},{161,4,1},{162,4,1},{163,4,1},{164,4,1},{165,5,1},{166,5,1},{167,5,1},{168,5,1},{169,6,1},{170,6,1},{171,6,1},{172,6,1},{173,7,1},{174,7,1},{175,8,1},{176,8,1},{177,9,1},{178,1,1},{179,2,1},{180,2,1},{181,3,1},{182,3,1},{183,4,1},{184,4,1},{185,5,1},{186,5,1},{187,6,1},{188,6,1},{189,7,1},{190,7,1},{191,8,1},{192,8,1},{193,9,1},{194,1,1},{195,2,1},{196,2,1},{197,3,1},{198,3,1},{199,4,1},{200,4,1},{201,5,1},{202,5,1},{203,6,1},{204,6,1},{205,7,1},{206,7,1},{207,8,1},{208,8,1},{209,9,1},{210,1,1},{211,2,1},{212,2,1},{213,3,1},{214,3,1},{215,4,1},{216,4,1},{217,5,1},{218,5,1},{219,6,1},{220,6,1},{221,7,1},{222,7,1},{223,8,1},{224,8,1},{225,9,1},{226,1,1},{227,2,1},{228,3,1},{229,4,1},{230,5,1},{231,6,1},{232,7,1},{233,8,1},{234,9,1}};
const Int_t *AliRPCAutoIntegrator::kLBToRPC = LBToRPC[0];


static const TString fSides_[] = {"INSIDE","OUTSIDE"};
const TString *AliRPCAutoIntegrator::fSides = fSides_;
static const Int_t fPlanes_[] = {11,12,21,22};
const Int_t *AliRPCAutoIntegrator::fPlanes = fPlanes_;
static const TString fCathodes_[] = {"BENDING","NOT BENDING"};
const TString *AliRPCAutoIntegrator::fCathodes = fCathodes_;

static const Int_t fColors_[] = {kBlack,kRed,kGreen,kBlue,kViolet+7,kMagenta,kCyan,kGray,kOrange};
const Int_t *AliRPCAutoIntegrator::fColors = fColors_;
static const Int_t fStyles_[]={20,24,21,25};
const Int_t *AliRPCAutoIntegrator::fStyles = fStyles_;

//call this in constructors
void AliRPCAutoIntegrator::InitDataMembers(){
    for(Int_t iRPC=0;iRPC<kNRPC;iRPC++){
        for(Int_t iPlane=0;iPlane<kNPlanes;iPlane++){
            if(iRPC==5){
                if(iPlane<2){
                    fRPCAreas[iRPC][iPlane]=16056.;
                } else {
                    fRPCAreas[iRPC][iPlane]=18176.;
                }
            }else if(iRPC==4 || iRPC==6){
                if(iPlane<2){
                    fRPCAreas[iRPC][iPlane]=19728./28.*27.;
                } else {
                    fRPCAreas[iRPC][iPlane]=22338./28.*27.;
                }
            }else {
                if(iPlane<2){
                    fRPCAreas[iRPC][iPlane]=19728.;
                } else {
                    fRPCAreas[iRPC][iPlane]=22338.;
                }
            }
        }
    }

    for(Int_t iPlane=0;iPlane<kNPlanes;iPlane++){
        fTinyArea[iPlane]=(fRPCAreas[9-1][iPlane]/7.*6.-fRPCAreas[5-1][iPlane])/4.;
        fLittleArea[iPlane]=fRPCAreas[9-1][iPlane]/28.;
        fNormalArea[iPlane]=fRPCAreas[9-1][iPlane]/14.;
        fBigArea[iPlane]=fRPCAreas[9-1][iPlane]/7.;
    }

    for(Int_t iLB=0;iLB<kNLocalBoards;iLB++){
        for(Int_t iPlane=0;iPlane<kNPlanes;iPlane++){
            if((iLB>=25 && iLB<=28) || (iLB>=142 && iLB<=145)){
                fLBAreas[iLB][iPlane]=fTinyArea[iPlane];
            } else if((iLB>=43 && iLB<=54) || (iLB>=21 && iLB<=24) || (iLB>=29 && iLB<=32) || (iLB>=5 && iLB<=10) || (iLB>=122 && iLB<=127) || (iLB>=138 && iLB<=141) || (iLB>=146 && iLB<=149) || (iLB>=160 && iLB<=171)){
                fLBAreas[iLB][iPlane]=fLittleArea[iPlane];
            } else if((iLB>=108 && iLB<=116) || (iLB>=225 && iLB<=233) || iLB==0 || iLB==16 || iLB==38 || iLB==60 || iLB==76 || iLB==92 || iLB==117 || iLB==133 || iLB==155 || iLB==177 || iLB==193 || iLB==209 || iLB==224 || iLB==208 || iLB==192 || iLB==176 || iLB==154 || iLB==132 || iLB==15 || iLB==37 || iLB==59 || iLB==75 || iLB==91 || iLB==107){
                fLBAreas[iLB][iPlane]=fBigArea[iPlane];
            } else {
                fLBAreas[iLB][iPlane]=fNormalArea[iPlane];
            }

            //cout<<iLB+1<<" "<<LBAreas[iLB][iPlane]<<endl;
        }
    }
}

// Default constructor
AliRPCAutoIntegrator::AliRPCAutoIntegrator(){
    InitDataMembers();
};

// Class constructor
AliRPCAutoIntegrator::AliRPCAutoIntegrator(TString RunListFileName, TString AMANDAInputFileName, TString OutputFileName, Bool_t updateOCDB, Bool_t updateAMANDA):
fRunListFileName(RunListFileName),
fAMANDAInputFileName(AMANDAInputFileName),
fOutputFileName(OutputFileName),
fUpdateOCDB(updateOCDB),
fUpdateAMANDA(updateAMANDA){

    // The update data variable allows the user to decide wether the data has to
    // be reloaded in the *DataContainer.root files or not (data already there)
    if(fUpdateOCDB){
        fOCDBDataContainer= new TFile("OCDBDataContainer.root","UPDATE");
        //fAMANDADataContainer= new TFile("AMANDADataContainer.root","RECREATE");
    } else {
        fOCDBDataContainer= new TFile("OCDBDataContainer.root","READ");
        //fAMANDADataContainer= new TFile("AMANDADataContainer.root","READ");
    }

    if(fUpdateAMANDA){
        //fOCDBDataContainer= new TFile("OCDBDataContainer.root","RECREATE");
        fAMANDADataContainer= new TFile("AMANDADataContainer.root","UPDATE");
    } else {
        //fOCDBDataContainer= new TFile("OCDBDataContainer.root","READ");
        //fAMANDADataContainer= new TFile("AMANDADataContainer.root","READ");
        fAMANDADataContainer= new TFile("AMANDADataContainer.root","UPDATE");
    }

    //fGlobalDataContainer= new TFile(Form("%s",OutputFileName.Data()),"RECREATE");
    fGlobalDataContainer= new TFile(Form("%s",OutputFileName.Data()),"UPDATE");

    fGlobalDataContainer->cd();
    fGlobalDataContainer->mkdir("TLists");
    fGlobalDataContainer->mkdir("iNet_Graphs");
    fGlobalDataContainer->mkdir("integrated_charge_Graphs");

    //check if AliRPCData already exists
    AliRPCData *AliRPCDataBuffer;
    fGlobalDataContainer->cd();
    fGlobalDataContainer->GetObject("AliRPCDataObj", AliRPCDataBuffer);

    if (!AliRPCDataBuffer) {
        AliRPCDataBuffer = new AliRPCData();
        fAliRPCDataObject=AliRPCDataBuffer;
        cout << "Creating new AliRPCData" << endl << flush;
    } else {
        fAliRPCDataObject = AliRPCDataBuffer;
        cout << "Reading old AliRPCData" << endl << flush;
    }

    // Calling this method to preload the runs of which the OCDB data has to be
    // downloaded
    OCDBRunListReader();

    InitDataMembers();
}

//  Destructor will dellaocate any data member allocated in the heap
AliRPCAutoIntegrator::~AliRPCAutoIntegrator(){
    fOCDBDataContainer->Close();
    fAMANDADataContainer->Close();
    fGlobalDataContainer->Close();

    // delete fOCDBDataContainer;
    // delete fAMANDADataContainer;
    // delete fGlobalDataContainer;
    // delete fSides;
    // delete fPlanes;
    // delete fCathodes;
    // delete kRPCIndexes;
    // delete kRPCSides;
}

// This method is the only public one and is a wrapper of the various methods
// which have to be called in sequence to
void AliRPCAutoIntegrator::RunAutoIntegrator(){

    // If user wants to update the data then the macro has to connect to OCDB.
    // Note that if data are already in the file there is nothing else to do.
    if (fUpdateOCDB){
        cout<<"Starting OCDB data retrieving...\n";
        OCDBDataToCParser();
        cout<<"DONE\n"<<endl;
    }

    if (fUpdateAMANDA){
        cout<<"Starting AMANDA data parsing...\n";
        AMANDATextToCParser();

        cout<<"Setting Amanda Parameters...\n";
        AMANDASetDataMembers();
        cout<<"DONE\n"<<endl;
    }


    cout<<"Starting data aggregation...\n";
    Aggregator();
    cout<<"DONE\n"<<endl;

    cout<<"Starting plot generation...\n";
    GeneratePlots();
    cout<<"DONE\n"<<endl;

    cout<<"Starting data elaboration...\n";
    Subtractor();
    cout<<"DONE\n"<<endl;

    cout<<"Starting filling AliRPCdata...\n";
    FillAliRPCData();
    cout<<"DONE\n"<<endl;

    cout<<"Starting integrated charge calculation...\n";
    Integrator();
    cout<<"DONE\n"<<endl;

    fOCDBDataContainer->Close();
    fAMANDADataContainer->Close();
    fGlobalDataContainer->Close();
}

// Method to parse a text file containing the run list for OCDB downloader
void AliRPCAutoIntegrator::OCDBRunListReader(){
    ifstream fin;
    AliOCDBRun runBuffer;
    runBuffer.fYear = 0000;
    fin.open(fRunListFileName.Data());
    while(kTRUE){
        if(fin.eof()) break;
        fin >> runBuffer.fRunNumber;
        fOCDBRunListToAdd.push_back(runBuffer);
        //cout<<runBuffer.fRunNumber<<endl<<flush;
    }
    fin.close();
}

// Method to merge the two files: AMANDA data and OCDB data.
// This procedure is needed to have chronologically ordered data with continuous
// current measurements (AMANDA) and "dark current" measurements from without
// beam runs (OCDB). This allows one to use subtract the dark current from
// AMANDA data in the most detailed way.
void AliRPCAutoIntegrator::Aggregator(){
    TList *listBufferAMANDA = 0x0;
    TList *listBufferOCDB = 0x0;
    TList *mergedData[kNSides][kNPlanes][kNRPC];

    for(Int_t iSide=0;iSide<kNSides;iSide++){
        for(Int_t iPlane=0;iPlane<kNPlanes;iPlane++){
            for(Int_t iRPC=0;iRPC<kNRPC;iRPC++){

                fAMANDADataContainer->GetObject(Form("AMANDA_Data_MTR_%s_MT%d_RPC%d",(fSides[iSide]).Data(),fPlanes[iPlane],iRPC+1), listBufferAMANDA);
                fOCDBDataContainer->GetObject(Form("OCDB_Data_MTR_%s_MT%d_RPC%d",(fSides[iSide]).Data(),fPlanes[iPlane],iRPC+1), listBufferOCDB);

                // if any data list is missing, then the channel
                // (aka {iSide,iPlane,iRPC}) is skipped from the whole following
                // analysis
                if (!listBufferAMANDA) {
                    printf("AMANDA_Data_MTR_%s_MT%d_RPC%d NOT FOUND\n",(fSides[iSide]).Data(),fPlanes[iPlane],iRPC+1);
                    continue;
                }
                if (!listBufferOCDB) {
                    printf("OCDB_Data_MTR_%s_MT%d_RPC%d NOT FOUND\n",(fSides[iSide]).Data(),fPlanes[iPlane],iRPC+1);
                    continue;
                }

                mergedData[iSide][iPlane][iRPC]=new TList();
                mergedData[iSide][iPlane][iRPC]->SetName(Form("OCDB_AMANDA_Data_MTR_%s_MT%d_RPC%d",(fSides[iSide]).Data(),fPlanes[iPlane],iRPC+1));

                TIter iterValueAMANDA(listBufferAMANDA);
                while(iterValueAMANDA()){
                    ((AliRPCValueCurrent*)*iterValueAMANDA)->SetIsAMANDA(kTRUE);
                    mergedData[iSide][iPlane][iRPC]->Add(*iterValueAMANDA);
                }


                TIter iterValueOCDB(listBufferOCDB);
                // UInt_t previousRun = 0;
                // Int_t measuresCounter = 0;
                // Double_t measuresCumulus = 0.;
                // while(iterValueOCDB()){
                //     //((AliRPCValueCurrent*)*iterValueAMANDA)->SetIsAMANDA(kFALSE);
                //     if (previousRun == 0) previousRun = ((AliRPCValueCurrent*)*iterValueOCDB)->GetRunNumber();
                //
                //     if (previousRun == ((AliRPCValueCurrent*)*iterValueOCDB)->GetRunNumber()) {
                //         measuresCounter++;
                //         measuresCumulus+=((AliRPCValueCurrent*)*iterValueOCDB)->GetITot();
                //     } else {
                //         mergedData[iSide][iPlane][iRPC]->Add(*iterValueOCDB);
                //         if ( ((AliRPCValueCurrent*)*iterValueOCDB)->IsCurrent() ){
                //         if (((AliRPCValueCurrent*)*iterValueOCDB)->GetTimeStamp()>8000 && ((AliRPCValueCurrent*)*iterValueOCDB)->GetITot()>0.)
                //             OCDBPlotsIDark[iSide][iPlane][iRPC]->SetPoint(counter++, ((AliRPCValueCurrent*)*iterValueOCDB)->GetTimeStamp(), measuresCumulus/(Double_t)measuresCounter);
                //         }
                //         measuresCounter = 0;
                //         measuresCumulus = 0.;
                //         previousRun = ((AliRPCValueCurrent*)*iterValueOCDB)->GetRunNumber();
                //     }
                // }

                while(iterValueOCDB()){
                    //((AliRPCValueCurrent*)*iterValueAMANDA)->SetIsAMANDA(kFALSE);
                    mergedData[iSide][iPlane][iRPC]->Add(*iterValueOCDB);
                }

                // the sorting will take place with respect to the timestamp of
                // each entry
                mergedData[iSide][iPlane][iRPC]->Sort();

                fGlobalDataContainer->cd("TLists");
                mergedData[iSide][iPlane][iRPC]->Write(Form("OCDB_AMANDA_Data_MTR_%s_MT%d_RPC%d",(fSides[iSide]).Data(),fPlanes[iPlane],iRPC+1),TObject::kSingleKey | TObject::kOverwrite);
                WhichRPC(iRPC, iSide, iPlane);

                listBufferAMANDA = 0x0;
                listBufferOCDB = 0x0;
            }
        }
    }
    fGlobalDataContainer->Flush();
}

void AliRPCAutoIntegrator::GeneratePlots() {
    TGraph *PlotsITot[kNSides][kNPlanes][kNRPC];
    TGraph *PlotsIDark[kNSides][kNPlanes][kNRPC];
    TGraph *PlotsVoltage[kNSides][kNPlanes][kNRPC];
    TList *listBuffer;

    fGlobalDataContainer->mkdir("iTot_Graphs");
    fGlobalDataContainer->mkdir("iDark_Graphs");
    fGlobalDataContainer->mkdir("Voltage_Graphs");


    for(Int_t iSide=0;iSide<kNSides;iSide++){
        for(Int_t iPlane=0;iPlane<kNPlanes;iPlane++){
            for(Int_t iRPC=0;iRPC<kNRPC;iRPC++){
                fGlobalDataContainer->GetObject(Form("TLists/OCDB_AMANDA_Data_MTR_%s_MT%d_RPC%d",(fSides[iSide]).Data(),fPlanes[iPlane],iRPC+1), listBuffer);

                if (!listBuffer) {
                    printf("TLists/OCDB_AMANDA_Data_MTR_%s_MT%d_RPC%d NOT FOUND\n",(fSides[iSide]).Data(),fPlanes[iPlane],iRPC+1);
                    continue;
                }

                PlotsITot[iSide][iPlane][iRPC] = new TGraph();
                PlotsITot[iSide][iPlane][iRPC]->SetLineColor(fColors[iRPC]);
                PlotsITot[iSide][iPlane][iRPC]->SetMarkerColor(fColors[iRPC]);
                PlotsITot[iSide][iPlane][iRPC]->SetMarkerStyle(fStyles[iPlane]);
                PlotsITot[iSide][iPlane][iRPC]->SetMarkerSize(0.15);

                PlotSomethingVersusTime(PlotsITot[iSide][iPlane][iRPC],&AliRPCValueDCS::IsOkForITot, listBuffer, AliRPCValueCurrent::kITot);

                fGlobalDataContainer->cd("iTot_Graphs");
                PlotsITot[iSide][iPlane][iRPC]->Write(Form("iTot_Graph_MTR_%s_MT%d_RPC%d",(fSides[iSide]).Data(),fPlanes[iPlane],iRPC+1),TObject::kSingleKey|TObject::kOverwrite);

                PlotsIDark[iSide][iPlane][iRPC]=new TGraph();
                PlotsIDark[iSide][iPlane][iRPC]->SetLineColor(fColors[iRPC]);
                PlotsIDark[iSide][iPlane][iRPC]->SetMarkerColor(fColors[iRPC]);
                PlotsIDark[iSide][iPlane][iRPC]->SetMarkerStyle(fStyles[iPlane]);
                PlotsIDark[iSide][iPlane][iRPC]->SetMarkerSize(0.15);

                PlotSomethingVersusTime(PlotsIDark[iSide][iPlane][iRPC],&AliRPCValueDCS::IsOkForIDark, listBuffer, AliRPCValueCurrent::kITot);

                fGlobalDataContainer->cd("iDark_Graphs");
                PlotsIDark[iSide][iPlane][iRPC]->Fit("pol1","Q");
                PlotsIDark[iSide][iPlane][iRPC]->Write(Form("iDark_Graph_MTR_%s_MT%d_RPC%d",(fSides[iSide]).Data(),fPlanes[iPlane],iRPC+1),TObject::kSingleKey|TObject::kOverwrite);

                PlotsVoltage[iSide][iPlane][iRPC]=new TGraph();
                PlotsVoltage[iSide][iPlane][iRPC]->SetLineColor(fColors[iRPC]);
                PlotsVoltage[iSide][iPlane][iRPC]->SetMarkerColor(fColors[iRPC]);
                PlotsVoltage[iSide][iPlane][iRPC]->SetMarkerStyle(fStyles[iPlane]);
                PlotsVoltage[iSide][iPlane][iRPC]->SetMarkerSize(0.15);

                PlotSomethingVersusTime(PlotsVoltage[iSide][iPlane][iRPC],&AliRPCValueDCS::IsVoltage,listBuffer);

                fGlobalDataContainer->cd("Voltage_Graphs");
                PlotsVoltage[iSide][iPlane][iRPC]->Write(Form("Voltage_Graph_MTR_%s_MT%d_RPC%d",(fSides[iSide]).Data(),fPlanes[iPlane],iRPC+1),TObject::kSingleKey|TObject::kOverwrite);

                WhichRPC(iRPC,iSide,iPlane);

                listBuffer=0x0;
            }
        }
    }
    fGlobalDataContainer->Flush();
}

// This method is one of the possible ones for the dark current subtraction. the
// basic idea is to subtract to AMANDA total currents the dark currents
// retrieved from OCDB. Since the OCDB has way less granularity than AMANDA, one
// should choose a method to interpolate the dark current readings:
//    * first possibility is to read the first dark current value and keep it
//      flat up to the following OCDB current value. In that case the dark
//      current plot will present a "stepping" trend;
//    * second possibility is to interpolate linearly two adjacent OCDB dark
//      current readings and compute, using a linear function evaluation, a
//      dark current value for each AMANDA value falling between the two
//      interpolated dark current values.
void AliRPCAutoIntegrator::Subtractor(){
    TList *buffer;
    TGraph *AMANDAPlotsINet[kNSides][kNPlanes][kNRPC];

    for(Int_t iSide=0;iSide<kNSides;iSide++){
        for(Int_t iPlane=0;iPlane<kNPlanes;iPlane++){
            for(Int_t iRPC=0;iRPC<kNRPC;iRPC++){
                fGlobalDataContainer->GetObject(Form("TLists/OCDB_AMANDA_Data_MTR_%s_MT%d_RPC%d",(fSides[iSide]).Data(),fPlanes[iPlane],iRPC+1),buffer);

                // if any data list is missing, then the channel
                // (aka {iSide,iPlane,iRPC}) is skipped from the whole following
                // analysis
                if (!buffer){
                    printf("TList/OCDB_AMANDA_Data_MTR_%s_MT%d_RPC%d NOT FOUND\n",(fSides[iSide]).Data(),fPlanes[iPlane],iRPC+1);
                    continue;
                }

                AMANDAPlotsINet[iSide][iPlane][iRPC]=new TGraph();
                AMANDAPlotsINet[iSide][iPlane][iRPC]->SetLineColor(fColors[iRPC]);
                AMANDAPlotsINet[iSide][iPlane][iRPC]->SetMarkerColor(fColors[iRPC]);
                AMANDAPlotsINet[iSide][iPlane][iRPC]->SetMarkerStyle(fStyles[iPlane]);
                AMANDAPlotsINet[iSide][iPlane][iRPC]->SetMarkerSize(0.15);

                TIter iterValueGlobal(buffer);
                Double_t darkCurrentValue = 0.;
                Double_t startTimeStamp = 0;
                Int_t counter=0;
                while(iterValueGlobal()){

                    //skip if is not current
                    if ( !((AliRPCValueDCS*)*iterValueGlobal)->IsCurrent() ) continue;

                    // if the read value is an AMANDA reading, then the dark
                    // current subtraction must take place. To do that via
                    // interpolation, having stored the previous dark current
                    // reading in darkCurrentValue, one should look for the
                    // following dark current value and the interpolate.
                    if ( ((AliRPCValueDCS*)*iterValueGlobal)->IsOkForITot() ){

                        // Looking for the following not AMANDA (aka OCDB)
                        // dark current reading.
                        TIter iterValueGlobalNext = iterValueGlobal;
                        while ( iterValueGlobalNext() ){
                            if (!((AliRPCValueDCS*)*iterValueGlobalNext)->IsOkForITot()) break;
                        }

                        // whenever a good OCDB reading is found then proceed
                        // with linear interpolation.
                        if (*iterValueGlobalNext) {
                            Double_t iDarkt0 = darkCurrentValue;
                            Double_t t0 = startTimeStamp;
                            Double_t iDarkt1 = ((AliRPCValueCurrent*)*iterValueGlobalNext)->GetIDark();
                            Double_t t1 = ((AliRPCValueCurrent*)*iterValueGlobalNext)->GetTimeStamp();
                            Double_t tnow = ((AliRPCValueCurrent*)*iterValueGlobal)->GetTimeStamp();

                            Double_t darkCurrent = tnow * (iDarkt1-iDarkt0)/(t1-t0) + iDarkt0;

                            // the dark current value if forced to be positive
                            if (darkCurrent<0.) darkCurrent=0.;

                            // the subtraction is not direct: the dark current
                            // value is set for each AMANDA reading.
                            // The subtraction will take place at the moment of
                            // asking the AMANDA reading the iNET value
                            // (since it returns iTOT-iDARK).
                            ((AliRPCValueCurrent*)*iterValueGlobal)->SetIDark(darkCurrent);
                            //cout<<((AliRPCValueCurrent*)*iterValueGlobal)->GetINet()<<endl;
                            if (((AliRPCValueCurrent*)*iterValueGlobal)->GetTimeStamp()>8000 && ((AliRPCValueCurrent*)*iterValueGlobal)->GetINet()>0.)
                                AMANDAPlotsINet[iSide][iPlane][iRPC]->SetPoint(counter++, ((AliRPCValueCurrent*)*iterValueGlobal)->GetTimeStamp(), ((AliRPCValueCurrent*)*iterValueGlobal)->GetINet()/fRPCAreas[iRPC][iPlane]);
                        }
                    }
                        // if a new dark current reding is found (non AMANDA = OCDB)
                        // then the dark current value is updated (as well as the
                        // timestamp)
                    else{
                        darkCurrentValue = ((AliRPCValueCurrent*)*iterValueGlobal)->GetITot();
                        startTimeStamp = ((AliRPCValueCurrent*)*iterValueGlobal)->GetTimeStamp();
                    }
                }
                fGlobalDataContainer->cd("iNet_Graphs");
                AMANDAPlotsINet[iSide][iPlane][iRPC]->Write(Form("iNet_Graph_MTR_%s_MT%d_RPC%d",(fSides[iSide]).Data(),fPlanes[iPlane],iRPC+1));

                WhichRPC(iRPC,iSide,iPlane);
            }
        }
    }
}


// This method integrates vs time the iNET valueDCS in order to get the
// integrated charge for each channel. And plots it.
void AliRPCAutoIntegrator::Integrator(){
    TGraph *buffer;
    TGraph *AMANDAPlotsIntegratedCharge[kNSides][kNPlanes][kNRPC];

   //arrays contains {iSide, IPlane, IRPC, integratedCharge}
    RPC RPCWhichIntegratedBest;
    RPC RPCWhichIntegratedWorst;
    Double_t MaxCharge=0.;
    Double_t MinCharge=1000000.;

    for(Int_t iSide=0;iSide<kNSides;iSide++){
        for(Int_t iPlane=0;iPlane<kNPlanes;iPlane++){
            for(Int_t iRPC=0;iRPC<kNRPC;iRPC++){
                fGlobalDataContainer->GetObject(Form("iNet_Graphs/iNet_Graph_MTR_%s_MT%d_RPC%d",(fSides[iSide]).Data(),fPlanes[iPlane],iRPC+1),buffer);

                // if any data list is missing, then the channel
                // (aka {iSide,iPlane,iRPC}) is skipped from the whole following
                // analysis
                if (!buffer){
                    printf("iNet_Graphs/iNet_Graph_MTR_%s_MT%d_RPC%d NOT FOUND\n",(fSides[iSide]).Data(),fPlanes[iPlane],iRPC+1);
                    continue;
                }

                AMANDAPlotsIntegratedCharge[iSide][iPlane][iRPC]=new TGraph();
                AMANDAPlotsIntegratedCharge[iSide][iPlane][iRPC]->SetLineColor(fColors[iRPC]);
                AMANDAPlotsIntegratedCharge[iSide][iPlane][iRPC]->SetMarkerColor(fColors[iRPC]);
                AMANDAPlotsIntegratedCharge[iSide][iPlane][iRPC]->SetMarkerStyle(fStyles[iPlane]);
                AMANDAPlotsIntegratedCharge[iSide][iPlane][iRPC]->SetMarkerSize(0.15);

                Double_t previousTimestamp = 0.;
                Double_t integratedCharge = 0.;
                Int_t counter = 0;

                // The integration takes place running on the TGraph points. The
                // adopted integration method is the trapezoidal rule.
                for(Int_t iPoint=0; iPoint<buffer->GetN()-1; iPoint++){
                    Double_t timestamp0,timestamp1;
                    Double_t iNet0,iNet1;
                    buffer->GetPoint(iPoint, timestamp0, iNet0);
                    buffer->GetPoint(iPoint+1, timestamp1, iNet1);

                    // the integrated charge is an incremental value
                    integratedCharge+=(timestamp1-timestamp0)*(iNet0+iNet1)/2.;

                    AMANDAPlotsIntegratedCharge[iSide][iPlane][iRPC]->SetPoint(counter++, (timestamp0+timestamp1)/2., integratedCharge);
                }

                if(integratedCharge<MinCharge){
                    RPCWhichIntegratedBest.Plane=iPlane;
                    RPCWhichIntegratedBest.Side=iSide;
                    RPCWhichIntegratedBest.RPC=iRPC+1;
                    MinCharge=integratedCharge;
                }else if(integratedCharge>=MaxCharge){
                    RPCWhichIntegratedWorst.Plane=iPlane;
                    RPCWhichIntegratedWorst.Side=iSide;
                    RPCWhichIntegratedWorst.RPC=iRPC+1;
                    MaxCharge=integratedCharge;
                }

                printf("MTR_%s_MT%d_RPC%d %f\n",(fSides[iSide]).Data(),fPlanes[iPlane],iRPC+1,integratedCharge);

                // for(Int_t iPoint=0; iPoint<buffer->GetN(); iPoint++){
                //     Double_t timestamp;
                //     Double_t iNet;
                //     buffer->GetPoint(iPoint, timestamp, iNet);
                //     if (previousTimestamp == 0.) previousTimestamp = timestamp;
                //     integratedCharge+=(timestamp-previousTimestamp)*iNet;
                //     AMANDAPlotsIntegratedCharge[iSide][iPlane][iRPC]->SetPoint(counter++, timestamp, integratedCharge);
                // }

                fGlobalDataContainer->cd("integrated_charge_Graphs");
                AMANDAPlotsIntegratedCharge[iSide][iPlane][iRPC]->Write(Form("integrated_charge_Graph_MTR_%s_MT%d_RPC%d",(fSides[iSide]).Data(),fPlanes[iPlane],iRPC+1),TObject::kOverwrite|TObject::kSingleKey);

                WhichRPC(iRPC, iSide, iPlane);

            }
        }
    }

    //Plot the best and the worst chamber
    TMultiGraph *BestAndWorstGraph=new TMultiGraph("BestAndWorstGraph","BestAndWorstGraph");
    //GetBest
    fGlobalDataContainer->GetObject(Form("integrated_charge_Graphs/integrated_charge_Graph_MTR_%s_MT%d_RPC%d",(fSides[RPCWhichIntegratedBest.Side]).Data(),fPlanes[RPCWhichIntegratedBest.Plane],RPCWhichIntegratedBest.RPC+1),buffer);
    BestAndWorstGraph->Add(buffer);
    //GetWorst
    fGlobalDataContainer->GetObject(Form("integrated_charge_Graphs/integrated_charge_Graph_MTR_%s_MT%d_RPC%d",(fSides[RPCWhichIntegratedWorst.Side]).Data(),fPlanes[RPCWhichIntegratedWorst.Plane],RPCWhichIntegratedWorst.RPC+1),buffer);
    BestAndWorstGraph->Add(buffer);
    fGlobalDataContainer->cd("integrated_charge_Graphs");
    BestAndWorstGraph->Write(Form("integrated_charge_Graph"),TObject::kOverwrite|TObject::kSingleKey);
    printf("Best RPC: MTR_%s_MT%d_RPC%d\t charge:%f \n",(fSides[RPCWhichIntegratedBest.Side]).Data(),fPlanes[RPCWhichIntegratedBest.Plane],RPCWhichIntegratedBest.RPC,MinCharge);
    printf("Worst RPC: MTR_%s_MT%d_RPC%d\t charge:%f \n",(fSides[RPCWhichIntegratedWorst.Side]).Data(),fPlanes[RPCWhichIntegratedWorst.Plane],RPCWhichIntegratedWorst.RPC,MaxCharge);

    fGlobalDataContainer->Flush();
}

void AliRPCAutoIntegrator::AMANDATextToCParser(){

    Int_t mts[23];
    mts[11]=0;
    mts[12]=1;
    mts[21]=2;
    mts[22]=3;

    TList *bufferOutputList;

	TList *data[kNSides][kNPlanes][kNRPC];
    for(Int_t iSide=0;iSide<kNSides;iSide++){
        for(Int_t iPlane=0;iPlane<kNPlanes;iPlane++){
            for(Int_t iRPC=0;iRPC<kNRPC;iRPC++){
                // The idea is to try to get the corresponding object from the
                // root file. If it is already there the new data will be
                // added to the list after the data already there. If not the
                //  object will be created.
                fAMANDADataContainer->cd();
                fAMANDADataContainer->GetObject(Form("AMANDA_Data_MTR_%s_MT%d_RPC%d",(fSides[iSide]).Data(),fPlanes[iPlane],iRPC+1),bufferOutputList);
                if (!bufferOutputList) {
                    data[iSide][iPlane][iRPC]=new TList();
                    data[iSide][iPlane][iRPC]->SetName(Form("AMANDA_Data_MTR_%s_MT%d_RPC%d",(fSides[iSide]).Data(),fPlanes[iPlane],iRPC+1));
                } else {
                    data[iSide][iPlane][iRPC] = bufferOutputList;
                }
                bufferOutputList = 0x0;
                //cout<<"created "<<data[iSide][iPlane][iRPC]->GetName()<<endl;
            }
        }
    }

    Bool_t isZero=kFALSE;

    ULong64_t dummyTimeStamp=0;
    ULong64_t timeStamp=0;
    Double_t current=0.;
    Int_t MT=0;
    Int_t RPC=0;
    char InsideOutside='I';

    string line;
    ifstream fin (fAMANDAInputFileName.Data());
    if (fin.is_open())
    {
        while (! fin.eof() )
        {
          getline (fin,line);
          if (fin.eof()) break;
          const char *charbuffer = (char*)line.c_str();
          if (!charbuffer) continue;
          sscanf(charbuffer,"%llu;MTR_%c",&dummyTimeStamp,&InsideOutside);
          char pattern[200];
          sprintf(pattern,"%%lf;MTR_%sSIDE_MT%%d_RPC%%d_HV.actual.iMon;%%lf",(InsideOutside=='I'?"IN":"OUT"));
          sscanf(charbuffer,pattern,&timeStamp,&MT,&RPC,&current);
        //   cout<<current<<endl;

          if((current!=0. || (current==0. && isZero)) && timeStamp>8000000.){
            //printf("%f %c=%d %d %d %.17f\n\n",timeStamp,InsideOutside,(InsideOutside=='I'?0:1),MT,RPC,current);
            //cout<<timeStamp<<endl;
            AliRPCValueCurrent *currentBuffer = new AliRPCValueCurrent(0, timeStamp, 0, current, 0., kFALSE,"",0.f,"", 0, kTRUE);
            currentBuffer->SetIsAMANDA(kTRUE);
            // //if (timeStamp<8000000) continue;
            //if (!(data[(InsideOutside=='I'?0:1)][mts[MT]][RPC-1])) continue;
            data[(InsideOutside=='I'?0:1)][mts[MT]][RPC-1]->Add(currentBuffer);
            currentBuffer = 0x0;
        } //else cout<<"#### skip ###"<<endl;
        }
        fin.close();
    }
    else cout << "Unable to open file";

    for(Int_t iSide=0;iSide<kNSides;iSide++){
        for(Int_t iPlane=0;iPlane<kNPlanes;iPlane++){
            for(Int_t iRPC=0;iRPC<kNRPC;iRPC++){
                fAMANDADataContainer->cd();
                if (data[iSide][iPlane][iRPC]->GetEntries()==0) continue;
                data[iSide][iPlane][iRPC]->Write(Form("AMANDA_Data_MTR_%s_MT%d_RPC%d",(fSides[iSide]).Data(),fPlanes[iPlane],iRPC+1),TObject::kSingleKey | TObject::kOverwrite);

            }
        }
    }
}

void AliRPCAutoIntegrator::OCDBDataToCParser(){

    //flag che è kTRUE se l'evento è di calibrazione
    Bool_t isCalib=kFALSE;
    Bool_t isBeamPresent=kFALSE;

    AliCDBManager *managerYearCheck = AliCDBManager::Instance();
    for (std::vector<AliOCDBRun>::iterator runIteratorYearChecker = fOCDBRunListToAdd.begin(); runIteratorYearChecker != fOCDBRunListToAdd.end(); ++runIteratorYearChecker) {
        for (Int_t year = 2016; year>2009; year--){
            managerYearCheck->SetDefaultStorage(Form("alien://folder=/alice/data/%d/OCDB",year));
            AliCDBStorage *defStorageYear = managerYearCheck->GetDefaultStorage();
            defStorageYear->QueryCDB((*runIteratorYearChecker).fRunNumber);
            TObjArray* arrCDBIDYear = defStorageYear->GetQueryCDBList();
            TIter nxt(arrCDBIDYear);
            AliCDBId* cdbIDYear = 0;
            Bool_t hasGRP = kFALSE;
            while ((cdbIDYear=(AliCDBId*)nxt())) {
                if (cdbIDYear->GetPath() == "GRP/GRP/Data") {hasGRP = kTRUE; break;}
            }
            if(!hasGRP){
                printf("\n\n### Can't find run %d\n\n",(*runIteratorYearChecker).fRunNumber);
                (*runIteratorYearChecker).fYear = 0000;
                continue;
            } else {
                printf("\n\n### Run %d belongs to year %d\n\n",(*runIteratorYearChecker).fRunNumber,year);
                (*runIteratorYearChecker).fYear = year;
                break;
            }
        }
    }

    //manager per interfacciarsi con gli OCDB
    AliCDBManager *managerCurrent = AliCDBManager::Instance();
    AliCDBManager *managerVoltage = AliCDBManager::Instance();
    AliCDBManager *managerRunType = AliCDBManager::Instance();
    AliCDBManager *managerScaler  = AliCDBManager::Instance();


    //array 3D di liste di dati. le TList sono già ordinate dopo ogni inserimento
    TList *dataList[kNSides][kNPlanes][kNRPC];
    TList *scalersDataList[2][kNSides][kNPlanes][kNRPC];
    TList *scalersLocalBoardList[kNCathodes][kNPlanes][kNLocalBoards];

    TList *bufferDataList;
    TList *bufferScalersDataList0;
    TList *bufferScalersDataList1;

    for (Int_t plane=0; plane<kNPlanes; plane++) {
        for (Int_t side=0; side<kNSides; side++) {
            for (Int_t RPC=1; RPC<=kNRPC; RPC++) {
                // The idea is to try to get the corresponding object from the
                // root file. If it is already there the new data will be
                // added to the list after the data already there. If not the
                //  object will be created.
                fOCDBDataContainer->cd();
                fOCDBDataContainer->GetObject(Form("OCDB_Data_MTR_%s_MT%d_RPC%d",(fSides[side]).Data(),fPlanes[plane],RPC),bufferDataList);
                fOCDBDataContainer->GetObject(Form("OCDB_Scalers_MTR_%s_%s_MT%d_RPC%d",(fSides[side]).Data(),(fCathodes[0]).Data(),fPlanes[plane],RPC),bufferScalersDataList0);
                fOCDBDataContainer->GetObject(Form("OCDB_Scalers_MTR_%s_%s_MT%d_RPC%d",(fSides[side]).Data(),(fCathodes[1]).Data(),fPlanes[plane],RPC),bufferScalersDataList1);

                if (!bufferDataList) {
                    dataList[side][plane][RPC-1]=new TList();
                    dataList[side][plane][RPC-1]->SetName(Form("OCDB_Data_MTR_%s_MT%d_RPC%d",(fSides[side]).Data(),fPlanes[plane],RPC));
                } else {
                    dataList[side][plane][RPC-1] = bufferDataList;
                }
                bufferDataList = 0x0;

                if (!bufferScalersDataList0) {
                    scalersDataList[0][side][plane][RPC-1]=new TList();
                    scalersDataList[0][side][plane][RPC-1]->SetName(Form("OCDB_Scalers_MTR_%s_%s_MT%d_RPC%d",(fSides[side]).Data(),(fCathodes[0]).Data(),fPlanes[plane],RPC));
                } else {
                    scalersDataList[0][side][plane][RPC-1] = bufferScalersDataList0;
                }
                bufferScalersDataList0 = 0x0;

                if (!bufferScalersDataList1) {
                    scalersDataList[1][side][plane][RPC-1]=new TList();
                    scalersDataList[1][side][plane][RPC-1]->SetName(Form("OCDB_Scalers_MTR_%s_%s_MT%d_RPC%d",(fSides[side]).Data(),(fCathodes[1]).Data(),fPlanes[plane],RPC));
                } else {
                    scalersDataList[1][side][plane][RPC-1] = bufferScalersDataList1;
                }
                bufferScalersDataList1 = 0x0;


            }
        }
    }

    bufferDataList = 0x0;
    bufferScalersDataList0 = 0x0;
    bufferScalersDataList1 = 0x0;

    TList *bufferScalersLocalBoardList1;

    for(Int_t cathode=0;cathode<kNCathodes;cathode++){
        for(Int_t plane=0;plane<kNPlanes;plane++){
            for(Int_t local=0;local<kNLocalBoards;local++){
                // The idea is to try to get the corresponding object from the
                // root file. If it is already there the new data will be
                // added to the list after the data already there. If not the
                //  object will be created.
                fOCDBDataContainer->cd();
                fOCDBDataContainer->GetObject(Form("OCDB_Scalers_MTR_%s_MT%d_LB%d",(fCathodes[cathode]).Data(),fPlanes[plane],local+1),bufferScalersLocalBoardList1);

                if (!bufferScalersLocalBoardList1) {
                    scalersLocalBoardList[cathode][plane][local]=new TList();
                    scalersLocalBoardList[cathode][plane][local]->SetName(Form("OCDB_Scalers_MTR_%s_MT%d_LB%d",(fCathodes[cathode]).Data(),fPlanes[plane],local+1));
                } else {
                    scalersLocalBoardList[cathode][plane][local] = bufferScalersLocalBoardList1;
                }
                bufferScalersLocalBoardList1 = 0x0;
            }
        }
    }

    bufferScalersLocalBoardList1 = 0x0;

    //loop sui run inseriti
    for (std::vector<AliOCDBRun>::iterator runIterator = fOCDBRunListToAdd.begin(); runIterator != fOCDBRunListToAdd.end(); ++runIterator) {
        if ((*runIterator).fYear == 0) continue;
        UInt_t RunYear=(*runIterator).fYear;

        //cout<<"YEar retrieved"<<endl;

        //inizializzazione dei manager
        managerCurrent->SetDefaultStorage(Form("alien://folder=/alice/data/%d/OCDB",(*runIterator).fYear));
        managerVoltage->SetDefaultStorage(Form("alien://folder=/alice/data/%d/OCDB",(*runIterator).fYear));
        managerRunType->SetDefaultStorage(Form("alien://folder=/alice/data/%d/OCDB",(*runIterator).fYear));
        managerScaler->SetDefaultStorage(Form("alien://folder=/alice/data/%d/OCDB",(*runIterator).fYear));

        //i manager puntano al run desiderato
        managerCurrent->SetRun((*runIterator).fRunNumber);
        managerVoltage->SetRun((*runIterator).fRunNumber);
        managerRunType->SetRun((*runIterator).fRunNumber);
        managerScaler->SetRun((*runIterator).fRunNumber);

        //cout<<"Managers retrieved"<<endl;

        if(CheckPointer((TNamed*)managerCurrent)) continue;
        if(CheckPointer((TNamed*)managerVoltage)) continue;
        if(CheckPointer((TNamed*)managerRunType)) continue;
        if(CheckPointer((TNamed*)managerScaler)) continue;

        AliCDBStorage *defStorage = managerCurrent->GetDefaultStorage();
        if(CheckPointer((TNamed*)defStorage)) continue;

        defStorage->QueryCDB((*runIterator).fRunNumber);
        TObjArray* arrCDBID = defStorage->GetQueryCDBList();
        if(CheckPointer((TNamed*)arrCDBID)) continue;
        TIter nxt(arrCDBID);
        AliCDBId* cdbID = 0;
        Bool_t hasGRP = kFALSE;
        while ((cdbID=(AliCDBId*)nxt())) {
            if (cdbID->GetPath() == "GRP/GRP/Data") {hasGRP = kTRUE; break;}
        }
        if(!hasGRP){
            printf("\n\nSkipping run %d\n\n",(*runIterator).fRunNumber);
            continue;
        }

        if(!AliMpCDB::LoadDDLStore()) continue;
        AliMpDDLStore *ddlStore=AliMpDDLStore::Instance();

        //inizializzazione dell'entry contente il runtype
        AliCDBEntry *entryRunType = managerRunType->Get("GRP/GRP/Data");
        if(CheckPointer((TNamed*)entryRunType)) continue;

        //retrievering delle informazioni sul run
        AliGRPObject *grpObj=(AliGRPObject*)entryRunType->GetObject();
        if(CheckPointer((TNamed*)grpObj)) continue;
        TString *runType=new TString(grpObj->GetRunType());
        TString *beamType=new TString(grpObj->GetBeamType());
        Float_t beamEnergy = grpObj->GetBeamEnergy();
        TString *LHCState = new TString(grpObj->GetLHCState());
        Long64_t SOR=(Long64_t)grpObj->GetTimeStart();
        Long64_t EOR=(Long64_t)grpObj->GetTimeEnd();

        //settaggio del flag isCalib
        if(runType->Contains("PHYSICS")){
            isCalib=kFALSE;
            //cout<<(*runIterator).runNumber<<" is phys"<<endl;
        } else if(runType->Contains("CALIBRATION")){
            isCalib=kTRUE;
            //cout<<(*runIterator).runNumber<<" is calib"<<endl;
        } else {
            continue;
        }

        //cout<<"Beam type retrieved"<<endl;

        //settaggio del flag beamPresence
        isBeamPresent = (beamEnergy > 1.) ? kTRUE : kFALSE ;

        //printf("-------------\n#####   Beam energy:%f Beam presence:%s Beam type:%s LHC State:%s \n-------------\n",beamEnergy,(isBeamPresent) ? "true" : "false",beamType->Data(), LHCState->Data());

        //cout<<isCalib<<endl;

        //inizializzazione dell'entry contente i valori di corrente
        AliCDBEntry *entryCurrent = managerCurrent->Get("MUON/Calib/TriggerDCS");
        if(CheckPointer((TNamed*)entryCurrent)) continue;

        //mappa delle correnti
        TMap *mapCurrent = (TMap*)entryCurrent->GetObject();
        if(CheckPointer((TNamed*)mapCurrent)) continue;

        //inizializzazione dell'entry contente i valori di tensione
        AliCDBEntry *entryVoltage = managerVoltage->Get("MUON/Calib/TriggerDCS");
        if(CheckPointer((TNamed*)entryVoltage)) continue;

        //mappa delle tensioni
        TMap *mapVoltage = (TMap*)entryVoltage->GetObject();
        if(CheckPointer((TNamed*)mapVoltage)) continue;

        //inizializzazone dell'entry contenente le letture degli scalers
        AliCDBEntry *entryScalers = managerScaler->Get("MUON/Calib/TriggerScalers");
        if(CheckPointer((TNamed*)entryScalers)) continue;

        //array delle letture
        TClonesArray *arrayScalers = (TClonesArray*)entryScalers->GetObject();
        if(CheckPointer((TNamed*)arrayScalers)) continue;

        //cout<<"ready to go"<<endl;

        //loop sui piani, i lati (inside e outside) e le RPC (9 per side)
        for (Int_t plane=0; plane<kNPlanes; plane++) {
            for (Int_t side=0; side<kNSides; side++) {
                for (Int_t RPC=1; RPC<=kNRPC; RPC++) {

                    Int_t dummyIndex = 0;
                    if(fAliRPCDataObject->IsThereThisRun(plane,side,RPC-1,runIterator->fRunNumber,dummyIndex)) {
                        printf("Run %d already there for ", runIterator->fRunNumber);
                        WhichRPC(RPC - 1, side, plane);
                        continue;
                    }

                    //creazione di un pointer all'elemento della mappa delle tensioni
                    TObjArray *dataArrayVoltage;
                    dataArrayVoltage=(TObjArray*)(mapCurrent->GetValue(Form("MTR_%s_MT%d_RPC%d_HV.vEff",fSides[side].Data(),fPlanes[plane],RPC)));

                    if(!dataArrayVoltage) {
                        printf(" Problems getting dataArrayVoltage\n");
                        break;
                    }

                    //cout<<"N voltage entries= "<<dataArrayVoltage->GetEntries()<<endl;

                    Bool_t isVoltageOk=kTRUE;

                    //loop sulle entry del vettore di misure di tensione
                    for (Int_t arrayIndex=0; arrayIndex<(dataArrayVoltage->GetEntries()); arrayIndex++) {
                        AliDCSValue *value = (AliDCSValue*)dataArrayVoltage->At(arrayIndex);

                        if(value->GetFloat()<8500.){
                            isVoltageOk=kFALSE;
                            //cout<<"\t"<<value->GetFloat()<<"\tBAD"<<endl;
                            break;
                        } else {
                            //cout<<"\t"<<value->GetFloat()<<endl;
                            dataList[side][plane][RPC-1]->Add(new AliRPCValueVoltage((*runIterator).fRunNumber,value->GetTimeStamp(),RunYear,value->GetFloat(),isCalib,*beamType,beamEnergy,*LHCState));
                        }
                        //cout<<"\t"<<value->GetFloat()<<endl;
                        dataList[side][plane][RPC-1]->Add(new AliRPCValueVoltage((*runIterator).fRunNumber,value->GetTimeStamp(),RunYear,value->GetFloat(),isCalib,*beamType,beamEnergy,*LHCState));
                        value = 0x0;
                    }

                    if (isVoltageOk==kFALSE) break;

                    //creazione di un pointer all'elemento della mappa delle correnti
                    TObjArray *dataArrayCurrents;
                    dataArrayCurrents=(TObjArray*)(mapCurrent->GetValue(Form("MTR_%s_MT%d_RPC%d_HV.actual.iMon",fSides[side].Data(),fPlanes[plane],RPC)));
                    if(!dataArrayCurrents) {
                        printf(" Problems getting dataArrayCurrents\n");
                        break;
                    }
                    //printf("%d-%d-%d\n",plane,side,RPC);
                    //loop sulle entry del vettore di misure di corrente
                    //cout<<"N current entries= "<<dataArrayCurrents->GetEntries()<<endl;
                    for (Int_t arrayIndex=0; arrayIndex<(dataArrayCurrents->GetEntries()); arrayIndex++) {
                        //puntatore all'elemento i-esimo
                        AliDCSValue *value = (AliDCSValue*)dataArrayCurrents->At(arrayIndex);
                        //se il run è di calibrazione corrente e corrente di buio coincidono
                        if (isCalib) {
                            dataList[side][plane][RPC-1]->Add(new AliRPCValueCurrent((*runIterator).fRunNumber,value->GetTimeStamp(),RunYear,value->GetFloat(),value->GetFloat(),isCalib,*beamType,beamEnergy,*LHCState ,0));
                            //((AliRPCValueDCS*)dataList[side][plane][RPC-1]->Last())->PrintBeamStatus();
                            //altrimenti imposto la corrente di buio a 0 (la cambio dopo)
                        } else {
                            dataList[side][plane][RPC-1]->Add(new AliRPCValueCurrent((*runIterator).fRunNumber,value->GetTimeStamp(),RunYear,value->GetFloat(),0.,isCalib,*beamType,beamEnergy,*LHCState,0));
                            //((AliRPCValueDCS*)dataList[side][plane][RPC-1]->Last())->PrintBeamStatus();
                        }
                        //cout<<"\t"<<value->GetFloat()<<"   "<<value->GetTimeStamp()<<endl;
                        value = 0x0;
                    }
                    //Form("OCDB_Data_MTR_%s_MT%d_RPC%d",(fSides[side]).Data(),fPlanes[plane],RPC)
                }
            }
        }

        //if(arrayScalers)printf("\n\n\n##### Scalers %d ######\n\n\n",arrayScalers->GetEntries());

        ULong64_t elapsedTime=0;
        UInt_t readLB[kNCathodes][kNSides][kNPlanes][kNRPC];
        UInt_t overflowLB[kNCathodes][kNSides][kNPlanes][kNRPC];
        for (Int_t plane=0; plane<kNPlanes; plane++) {
            for (Int_t side=0; side<kNSides; side++) {
                for (Int_t RPC=1; RPC<=kNRPC; RPC++) {
                    for (Int_t cathode=0; cathode<kNCathodes; cathode++) {
                        readLB[cathode][side][plane][RPC-1]=0;
                        overflowLB[cathode][side][plane][RPC-1]=0;
                    }
                }
            }
        }
        //loop sulle entries, sui piani, i catodi (bending e non bending) e le Local Boards (234 per piano)
        //cout<<"entries: "<<arrayScalers->GetEntries()<<endl;
        AliMUONTriggerScalers *scalersData;
        for (Int_t scalerEntry=0; scalerEntry<arrayScalers->GetEntries() && isCalib==kFALSE; scalerEntry++){
            scalersData=(AliMUONTriggerScalers*)arrayScalers->At(scalerEntry);
            //cout<<"deltat: "<<scalersData->GetDeltaT()<<endl;
            Int_t arrayScalersEntries=arrayScalers->GetEntries();
            //if(scalerEntry%100==0)cout<<scalerEntry<<"/"<<arrayScalersEntries<<endl;
            elapsedTime+=scalersData->GetDeltaT();
            for (Int_t plane=0; plane<kNPlanes; plane++) {
                for (Int_t cathode=0; cathode<kNCathodes; cathode++) {
                    //cout<<"{";
                    for (Int_t localBoard=0; localBoard<kNLocalBoards; localBoard++) {
                        Int_t iRPC017=(ddlStore->GetDEfromLocalBoard(localBoard+1, plane+10))-(plane+1+10)*100;
                        Int_t iRPC09=kRPCIndexes[iRPC017];
                        Int_t iSide=kRPCSides[iRPC017];

                        //cout<<"{"<<localBoard<<","<<iRPC09<<","<<iSide<<"},";

                        // se c'è overflow scarto il dato
                        readLB[cathode][iSide][plane][iRPC09-1]++;
                        Bool_t isOverflow=kFALSE;
                        if (scalersData->GetLocScalStripOver(cathode, plane, localBoard)!=0. ){//| scalersData->GetLocScalStrip(cathode, plane, localBoard)==0.) {
                            //printf(" MTR %d cathode %d LB %d RPC %d or %d_%s timestamp %lu data %d OVERFLOW\n",fPlanes[plane],cathode,localBoard,iRPC017,iRPC09,(fSides[iSide]).Data(),SOR+elapsedTime,scalersData->GetLocScalStrip(cathode, plane, localBoard));
                            overflowLB[cathode][iSide][plane][iRPC09-1]++;
                            readLB[cathode][iSide][plane][iRPC09-1]--;
                            isOverflow=kTRUE;
                        }
                        // se la lettura non è quella a fine run immagazzino il dato con timestamp pari a SOR+DeltaT
                        if(scalerEntry!=arrayScalersEntries-1){
                            AliRPCValueScaler *buffer=new AliRPCValueScaler((*runIterator).fRunNumber, SOR+elapsedTime,RunYear, scalersData->GetLocScalStrip(cathode, plane, localBoard), isCalib,*beamType,beamEnergy,*LHCState, scalersData->GetDeltaT(), isOverflow);
                            scalersDataList[cathode][iSide][plane][iRPC09-1]->Add(buffer);
                            scalersLocalBoardList[cathode][plane][localBoard]->Add(buffer);
                            //delete buffer;
                        }
                            // altrimenti il timestamp è pari all'EOR
                        else {
                            AliRPCValueScaler *buffer=new AliRPCValueScaler((*runIterator).fRunNumber, EOR, RunYear,scalersData->GetLocScalStrip(cathode, plane, localBoard), isCalib,*beamType,beamEnergy,*LHCState, scalersData->GetDeltaT(), isOverflow);
                            scalersDataList[cathode][iSide][plane][iRPC09-1]->Add(buffer);
                            scalersLocalBoardList[cathode][plane][localBoard]->Add(buffer);
                            //delete buffer;
                        }
                        //printf(" MTR %d cathode %d LB %d RPC %d or %d_%s timestamp %lu data %d\n",fPlanes[plane],cathode,localBoard,iRPC017,iRPC09,(fSides[iSide]).Data(),SOR+elapsedTime,scalersData->GetLocScalStrip(cathode, plane, localBoard));
                    }
                    //cout<<"}"<<endl;
                }
            }
            scalersData=0x0;
        }
        delete scalersData;

        //printf("scalers reading complete.\n");

        for (Int_t plane=0; plane<kNPlanes; plane++) {
            for (Int_t side=0; side<kNSides; side++) {
                for (Int_t RPC=1; RPC<=kNRPC; RPC++) {
                    for (Int_t cathode=0; cathode<kNCathodes; cathode++) {
                        scalersDataList[cathode][side][plane][RPC-1]->Add(new AliRPCOverflowStatistics((*runIterator).fRunNumber, EOR, overflowLB[cathode][side][plane][RPC-1], readLB[cathode][side][plane][RPC-1], isCalib,*beamType,beamEnergy,*LHCState ));
                        //cout<<"RUN"<<(*runIterator).runNumber<<" side:"<<side<<" plane "<<plane<<" RPC "<<RPC<<" cathode "<<cathode<<" READ="<<readLB[cathode][side][plane][RPC-1]<<" OVERFLOW="<<overflowLB[cathode][side][plane][RPC-1]<<endl<<endl;
                    }
                }
            }
        }
        //printf("data saved.\n");

    }

    printf("\n\n\nData retrieving complete\n\n\n");

    //loop sui piani, i lati (inside e outside) e le RPC (9 per side)
    for (Int_t plane=0; plane<kNPlanes; plane++) {
        for (Int_t side=0; side<kNSides; side++) {
            for (Int_t RPC=1; RPC<=kNRPC; RPC++) {
                //alias all'elemento dell'array 3D di TLists*
                TList *sortedList=dataList[side][plane][RPC-1];
                sortedList->Sort();

                //contenitore per il run number del run dal quale deriva la misura di dark current
                UInt_t calibRunNumber=0;

                //contenitore per il valore di corrente di buio misurata
                Double_t iDarkCalib=0.;

                //flag positivo se la precedente misura di tensione è >=8500.V
                Bool_t voltageOkFlag=kFALSE;

                //printf("MT%d_%s_%d\n",fPlanes[plane],fSides[side].Data(),RPC);

                //loop sulle entries della lisa di dati
                for(Int_t iList=0; iList<sortedList->GetEntries(); iList++){
                    //cout<<iList<<"/"<<sortedList->GetEntries()<<endl;
                    //L'elemento può essere una tensione o una corrente
                    AliRPCValueDCS *valueDCS=(AliRPCValueDCS*)(sortedList->At(iList));
                    //se è una tensione
                    if (valueDCS->IsVoltage()) {
                        //cast a tensione
                        AliRPCValueVoltage* valueVoltage=(AliRPCValueVoltage*)valueDCS;
                        //settaggio del flag
                        voltageOkFlag=(Bool_t)(valueVoltage->GetVSupp()>=8500.);
                        valueVoltage=0x0;
                        //se è una corrente
                    } else if (valueDCS->IsCurrent()) {
                        //cast a corrente
                        AliRPCValueCurrent* valueCurrent=(AliRPCValueCurrent*)valueDCS;
                        //se è un run di calibrazione fatto a tensione di lavoro
                        if (valueCurrent->IsCalib()==kTRUE && voltageOkFlag==kTRUE) {
                            //rimangono alcune letture a 0.0A, così si tolgono ###GIUSTO?###
                            if(valueCurrent->GetIDark()!=0.){
                                iDarkCalib=valueCurrent->GetIDark();
                                calibRunNumber=valueCurrent->GetCalibRunNumber();
                            }
                            //se è un run di fisica setto la dark current prendendola dal precedente run di calibrazione eseguito in condizioni di lavoro
                        } else {
                            valueCurrent->SetIDark(iDarkCalib);
                            valueCurrent->SetCalibRunNumber(calibRunNumber);
                            //cout<<valueCurrent<<"\t"<<calibRunNumber<<endl;
                        }
                        valueCurrent=0x0;
                    }
                    //cout<<valueDCS->IsCalib()<<endl;
                    valueDCS=0x0;
                }

                fOCDBDataContainer->cd();
                sortedList->Sort();
                scalersDataList[0][side][plane][RPC-1]->Sort();
                scalersDataList[1][side][plane][RPC-1]->Sort();
                sortedList->Write(Form("OCDB_Data_MTR_%s_MT%d_RPC%d",(fSides[side]).Data(),fPlanes[plane],RPC),TObject::kSingleKey | TObject::kOverwrite);
                scalersDataList[0][side][plane][RPC-1]->Write(Form("OCDB_Scalers_MTR_%s_%s_MT%d_RPC%d",(fSides[side]).Data(),(fCathodes[0]).Data(),fPlanes[plane],RPC),TObject::kSingleKey | TObject::kOverwrite);
                scalersDataList[1][side][plane][RPC-1]->Write(Form("OCDB_Scalers_MTR_%s_%s_MT%d_RPC%d",(fSides[side]).Data(),(fCathodes[1]).Data(),fPlanes[plane],RPC),TObject::kSingleKey | TObject::kOverwrite);
            }
        }
    }

    for(Int_t cathode=0;cathode<kNCathodes;cathode++){
        for(Int_t plane=0;plane<kNPlanes;plane++){
            for(Int_t local=0;local<kNLocalBoards;local++){
                fOCDBDataContainer->cd();
                scalersLocalBoardList[cathode][plane][local]->Sort();
                scalersLocalBoardList[cathode][plane][local]->Write(Form("OCDB_Scalers_MTR_%s_MT%d_LB%d",(fCathodes[cathode]).Data(),fPlanes[plane],local+1),TObject::kSingleKey | TObject::kOverwrite);
                //printf("OCDB_Scalers_MTR_%s_MT%d_LB%d\n",(fCathodes[cathode]).Data(),fPlanes[plane],local+1);
            }
        }
    }

    printf("\n\n\nDark currents setting complete\n\n\n");
}


void AliRPCAutoIntegrator::FillAliRPCData(){

    TList *sortedListData[kNSides][kNPlanes][kNRPC];
    TList *sortedListScalers[kNSides][kNPlanes][kNRPC][kNCathodes];
    TList *scalersLocalBoardList[kNCathodes][kNPlanes][kNLocalBoards];

    Int_t previousScalers[kNCathodes][kNPlanes][kNLocalBoards];

    for (Int_t plane=0; plane<kNPlanes; plane++) {
        for (Int_t cathode=0; cathode<kNCathodes; cathode++) {
            for (Int_t localBoard=1; localBoard<=kNLocalBoards; localBoard++) {
                previousScalers[cathode][plane][localBoard-1]=0;
            }
        }
    }

    TList *buffer=new TList();
    for (Int_t side=0; side<kNSides; side++) {
        cout<<fSides[side].Data()<<endl;
        for (Int_t plane=0; plane<kNPlanes; plane++) {
            cout<<"\t"<<fPlanes[plane]<<endl;
            for (Int_t RPC=1; RPC<=kNRPC; RPC++) {
                cout<<"\t\t"<<RPC<<endl;
                //sortedListData[side][plane][RPC-1]=new TList();
                fGlobalDataContainer->GetObject(Form("TLists/OCDB_AMANDA_Data_MTR_%s_MT%d_RPC%d",(fSides[side]).Data(),fPlanes[plane],RPC),buffer);
                if(!buffer){
                    cout<<"OCDB_AMANDA_Data NOT FOUND"<<endl;
                    continue;
                }
                 if(!(buffer->IsSorted())) buffer->Sort();
                sortedListData[side][plane][RPC-1]=buffer;
                buffer=0x0;

                for(Int_t cathode=0;cathode<kNCathodes;cathode++){
                    cout<<"\t\t\t"<<fCathodes[cathode].Data()<<endl;
                    //sortedListScalers[side][plane][RPC-1][cathode]=new TList();
                    fOCDBDataContainer->GetObject(Form("OCDB_Scalers_MTR_%s_%s_MT%d_RPC%d",(fSides[side]).Data(),(fCathodes[cathode]).Data(),fPlanes[plane],RPC),buffer);
                    if(!buffer){
                        cout<<"Scalers NOT FOUND"<<endl;
                        continue;
                    }
                    if(!(buffer->IsSorted())) buffer->Sort();
                    sortedListScalers[side][plane][RPC-1][cathode]=buffer;
                    buffer=0x0;
                }
            }
        }
    }

    for(Int_t cathode=0;cathode<kNCathodes;cathode++){
        cout<<fCathodes[cathode].Data()<<endl;
        for(Int_t plane=0;plane<kNPlanes;plane++){
            cout<<"\t"<<fPlanes[plane]<<endl;
            for(Int_t local=0;local<kNLocalBoards;local++){
                cout<<"\t\t"<<local+1<<endl;
                //scalersLocalBoardList[cathode][plane][local]=new TSortedList();
                //printf("Scalers_MTR_%s_MT%d_LB%d\n",(cathodes[cathode]).Data(),planes[plane],local+1);
                fOCDBDataContainer->GetObject(Form("OCDB_Scalers_MTR_%s_MT%d_LB%d",(fCathodes[cathode]).Data(),fPlanes[plane],local+1),buffer);
                if(!buffer){
                    cout<<"Scalers NOT FOUND"<<endl;
                    continue;
                }
                if(!(buffer->IsSorted())) buffer->Sort();
                scalersLocalBoardList[cathode][plane][local]=buffer;
                buffer=0x0;
            }
        }
    }


    for (Int_t iSide=0; iSide<kNSides; iSide++) {
        for (Int_t iPlane = 0; iPlane < kNPlanes; iPlane++) {
            for (Int_t iRPC = 1; iRPC <= kNRPC; iRPC++) {
                UInt_t actualRunNumber = 0;
                UInt_t actualYear=0;
                UInt_t previousRunNumber = 0;
                ULong64_t timeStampStart = 0;
                ULong64_t timeStampStop = 0;
                Bool_t isCalib = kFALSE;
                Bool_t isDark=kFALSE;
                Double_t meanDarkCurrent = 0.;
                UInt_t nDarkCurrent = 0;
                Double_t meanTotalCurrent = 0.;
                UInt_t nTotalCurrent = 0;
                Double_t meanHV = 0.;
                UInt_t nHV = 0;
                Double_t RPCTotalRatePerArea[2] = {0., 0.};
                ULong64_t totalScalerCounts[2] = {0, 0};

                TIter iterValueDCS(sortedListData[iSide][iPlane][iRPC - 1]);
                AliRPCValueDCS *valueDCS = (AliRPCValueDCS *) iterValueDCS();
                do {
                    //generica entry della sorted list
                    //AliRPCValueDCS *valueDCS = ((AliRPCValueDCS*)sortedListData[iSide][iPlane][iRPC-1]->At(iDataList));
                    if (previousRunNumber == 0) {
                        previousRunNumber = valueDCS->GetRunNumber();
                        timeStampStart = valueDCS->GetTimeStamp();
                        isCalib = valueDCS->IsCalib();
                        isDark = ((AliRPCValueDCS *) *iterValueDCS)->IsOkForIDark();
                    }

                    actualRunNumber = valueDCS->GetRunNumber();
                    actualYear = valueDCS->GetYear();

                    Int_t dummyIndex = 0;
                    if(fAliRPCDataObject->IsThereThisRun(iPlane,iSide,iRPC,actualRunNumber,dummyIndex)) {
                        printf("Run %d already there for ",actualRunNumber);
                        WhichRPC(iRPC,iSide,iPlane);
                        continue;
                    }

                    if (actualRunNumber == previousRunNumber) {
                        if (valueDCS->IsVoltage()){
                            //cast a tensione
                            AliRPCValueVoltage *voltageBuffer=(AliRPCValueVoltage*)valueDCS;
                            meanHV+=voltageBuffer->GetVSupp();
                            nHV++;
                            timeStampStop=valueDCS->GetTimeStamp();
                        } else if(valueDCS->IsCurrent()){
                            //cast a corrente
                            AliRPCValueCurrent *currentBuffer=(AliRPCValueCurrent*)valueDCS;
                            meanTotalCurrent+=currentBuffer->GetITot();
                            nTotalCurrent++;
                            meanDarkCurrent+=currentBuffer->GetIDark();
                            nDarkCurrent++;
                            timeStampStop=valueDCS->GetTimeStamp();
                        } else continue;
                    } else if (actualRunNumber < previousRunNumber) continue;
                    else {
                        Double_t ratesTimesLBArea[2] = {0., 0.};
                        Double_t LBRateSum[2] = {0., 0.};
                        Double_t notOverflowLBTotalArea[2] = {0., 0.};

                        printf("\n######################\nRun=%d MT=%d iRPC=%d SIDE=%s\n", previousRunNumber, fPlanes[iPlane], iRPC, fSides[iSide].Data());
                        for (Int_t cathode = 0; cathode < kNCathodes; cathode++) {
                            for (Int_t localBoard = 1; localBoard <= kNLocalBoards; localBoard++) {
                                Int_t acceptedCount = 0;
                                Int_t LBScalers = 0;
                                Double_t elapsedTime = 0.;
                                Double_t LBRate = 0.;
                                Int_t iRPC09 = (kLBToRPC+localBoard - 1)[1];
                                Int_t side = (kLBToRPC+localBoard - 1)[2];
                                Bool_t isAccepted = kFALSE;
                                Int_t readingCount = 0;
                                if (iSide == side && iRPC09 == iRPC) {

                                    //printf("\n\t%s LB=%d area=%f\n",cathodes[cathode].Data(),localBoard,LBAreas[localBoard-1][iPlane]);
                                    //printf("\t\tReading\tScaler\t\tIsOF\n");
                                    //cout<<"\t"<<localBoard<<endl;
                                    //cout<<previousScalers[cathode][iPlane][localBoard-1]<<endl;
                                    TIter iterValueScaler(scalersLocalBoardList[cathode][iPlane][localBoard - 1]);
                                    AliRPCValueScaler *valueScaler;
                                    while ((valueScaler = (AliRPCValueScaler *) iterValueScaler())) {
                                        if (valueScaler->GetScalerCounts() <= 0.) continue;
                                        //for(Int_t iScaler=previousScalers[cathode][iPlane][localBoard-1];iScaler<scalersLocalBoardList[cathode][iPlane][localBoard-1]->GetEntries();iScaler++){
                                        //AliRPCValueScaler *valueScaler=((AliRPCValueScaler*)scalersLocalBoardList[cathode][iPlane][localBoard-1]->At(iScaler));
                                        readingCount++;
                                        if (valueScaler->GetRunNumber() < previousRunNumber) {
                                            //cout<<"continue"<<iScaler<<" "<<valueScaler->GetRunNumber()<<"<"<<previousRunNumber<<endl;
                                            //cout<<"continue "<<iScaler<<" "<<valueScaler->GetRunNumber()<<"<"<<previousRunNumber<<endl;
                                            continue;
                                        } else if (valueScaler->GetRunNumber() > previousRunNumber) {
                                            //cout<<"breaking"<<iScaler<<" "<<valueScaler->GetRunNumber()<<">"<<previousRunNumber<<endl;
                                            previousScalers[cathode][iPlane][localBoard - 1] = 0;//iScaler;
                                            break;
                                        } else {
                                            //cout<<"filling"<<iScaler<<" "<<valueScaler->GetRunNumber()<<">"<<previousRunNumber<<endl;
                                            if (valueScaler->GetScalerCounts() == 0) continue;
                                            //(!valueScaler->GetHasOverflow())? printf("\t\t%d\t%d\t\t%s\n",readingCount,valueScaler->GetScalerCounts(),(valueScaler->GetHasOverflow())?"TRUE":"false") : printf("\t>>>\t%d\t%d\t\t%s\n",readingCount,valueScaler->GetScalerCounts(),(valueScaler->GetHasOverflow())?"TRUE":"false");
                                            if (valueScaler->GetHasOverflow() == kTRUE) {
                                                //cout<<"################ "<<localBoard<<" has overflow"<<endl;
                                                continue;
                                            } else {
                                                //cout<<"pippo"<<endl;
                                                acceptedCount++;
                                                isAccepted = kTRUE;
                                                LBScalers += valueScaler->GetScalerCounts();
                                                elapsedTime += valueScaler->GetDeltaT();
                                            }
                                        }
                                        //scalersLocalBoardList[cathode][iPlane][localBoard-1]->RemoveAt(iScaler);
                                    }

                                    if (isAccepted == kTRUE) {
                                        //cout<<localBoard<<" accepted"<<endl;
                                        LBRate = (Double_t) LBScalers / elapsedTime;
                                        LBRateSum[cathode] += LBRate;
                                        notOverflowLBTotalArea[cathode] += fLBAreas[localBoard - 1][iPlane];
                                        //printf("MT %d iRPC %d LB %d cath %d area %f totarea %f\n",iPlane,iRPC,localBoard,cathode,LBAreas[localBoard-1][iPlane],notOverflowLBTotalArea[cathode]);
                                        //cout<<notOverflowLBTotalArea[cathode]<<endl;
                                        //printf("%d %f %f %f %f\n",acceptedCount,LBRate,LBRate,LBRateSum[cathode],notOverflowLBTotalArea[cathode]);
                                    }
                                }
                            }

                            if (notOverflowLBTotalArea[cathode] != 0)
                                RPCTotalRatePerArea[cathode] = LBRateSum[cathode] / notOverflowLBTotalArea[cathode];
                            else RPCTotalRatePerArea[cathode] = -1.;
                            totalScalerCounts[cathode] = (ULong64_t) (RPCTotalRatePerArea[cathode] * (Double_t) (timeStampStop - timeStampStart) *fRPCAreas[iRPC - 1][iPlane]);
                            if (cathode == 1)
                                printf("-Rates:\n\t·Bending: %f Hz/cm^2\n\t·Not bending: %f Hz/cm^2\n\n-Total scaler counts:\n\t·Bending: %llu\n\t·Not bending: %llu\n####################\n",RPCTotalRatePerArea[0], RPCTotalRatePerArea[1], totalScalerCounts[0],totalScalerCounts[1]);
                            //cout<<cathode<<": "<<totalScalerCounts[cathode]<<endl<<endl;

                        }

                        if(nDarkCurrent!=0)meanDarkCurrent=meanDarkCurrent/(Double_t)nDarkCurrent;
                        if(nTotalCurrent!=0)meanTotalCurrent=meanTotalCurrent/(Double_t)nTotalCurrent;
                        if(nHV!=0)meanHV=meanHV/(Double_t)nHV;
                        //cout<<"setting "<<previousRunNumber<<" complete"<<endl;
                        //cout<<totalScalerCounts[0]<<"\t"<<totalScalerCounts[1]<<endl;
                        AliRPCRunStatistics *statsBuffer=new AliRPCRunStatistics(previousRunNumber, timeStampStart, timeStampStop, actualYear, isCalib, isDark, meanDarkCurrent, meanTotalCurrent, meanHV, totalScalerCounts[0], totalScalerCounts[1]);
                        fAliRPCDataObject->AddRunStatistics(iPlane, iSide, iRPC, statsBuffer);

                        actualRunNumber=0;
                        timeStampStart=0;
                        timeStampStop=0;
                        isCalib=kFALSE;
                        isDark=kFALSE;
                        meanDarkCurrent=0.;
                        nDarkCurrent=0;
                        meanTotalCurrent=0.;
                        nTotalCurrent=0;
                        meanHV=0.;
                        nHV=0;
                        totalScalerCounts[0]=0;
                        totalScalerCounts[1]=0;
                        //statsBuffer=0x0;
                        //force reset of previous and start timestamp
                        previousRunNumber=0;
                        previousRunNumber=valueDCS->GetRunNumber();
                        timeStampStart=valueDCS->GetTimeStamp();
                        isCalib=valueDCS->IsCalib();
                        ratesTimesLBArea[0]=0;
                        ratesTimesLBArea[1]=0;
                    }
                }while((valueDCS=(AliRPCValueDCS*)iterValueDCS()));

            }
        }
    }

    //save AliRPCData on File
    fGlobalDataContainer->cd();
    fAliRPCDataObject->Write("AliRPCDataObj", TObject::kSingleKey | TObject::kOverwrite);
    fGlobalDataContainer->Flush();

};

void AliRPCAutoIntegrator::AMANDASetDataMembers(){
    TList *listBufferAMANDA=0x0;
    TList *listBufferOCDB=0x0;
    TSortedList *DataWithRunNumber[kNSides][kNPlanes][kNRPC];

    for(Int_t iSide=0;iSide<kNSides;iSide++){
        for(Int_t iPlane=0;iPlane<kNPlanes;iPlane++){
            for(Int_t iRPC=0;iRPC<kNRPC;iRPC++){
                fOCDBDataContainer->GetObject(Form("OCDB_Data_MTR_%s_MT%d_RPC%d",(fSides[iSide]).Data(),fPlanes[iPlane],iRPC+1),listBufferOCDB);
                fAMANDADataContainer->GetObject(Form("AMANDA_Data_MTR_%s_MT%d_RPC%d",(fSides[iSide]).Data(),fPlanes[iPlane],iRPC+1),listBufferAMANDA);

                DataWithRunNumber[iSide][iPlane][iRPC]=new TSortedList();
                DataWithRunNumber[iSide][iPlane][iRPC]->SetName(Form("AMANDA_Data_MTR_%s_MT%d_RPC%d",(fSides[iSide]).Data(),fPlanes[iPlane],iRPC+1));

                // if any data list is missing, then the channel
                // (aka {iSide,iPlane,iRPC}) is skipped
                if (!listBufferAMANDA) {
                    printf("AMANDA_Data_MTR_%s_MT%d_RPC%d NOT FOUND\n",(fSides[iSide]).Data(),fPlanes[iPlane],iRPC+1);
                    continue;
                }

                if (!listBufferOCDB) {
                    printf("OCDB_Data_MTR_%s_MT%d_RPC%d NOT FOUND\n",(fSides[iSide]).Data(),fPlanes[iPlane],iRPC+1);
                    continue;
                }

                if(!listBufferOCDB->IsSorted()) listBufferOCDB->Sort();
                if(!listBufferAMANDA->IsSorted()) listBufferAMANDA->Sort();

                TIter iterValueOCDB(listBufferOCDB);
                TIter iterValueAMANDA(listBufferAMANDA);
                TIter iterValueAMANDANext(listBufferAMANDA);
                iterValueAMANDANext();

                UInt_t runNumberBuffer=((AliRPCValueDCS *) listBufferOCDB->At(0))->GetRunNumber();
                //it is intended as runnumber extends from runbegin to runend then
                //at newbegin begins another run
                ULong64_t runBeginBuffer=((AliRPCValueDCS *) listBufferOCDB->At(0))->GetTimeStamp();
                ULong64_t newRunBeginBuffer=0;
                ULong64_t runEndBuffer=0;

                //iter on OCDB until runnumber changes
                while(iterValueOCDB()){

                    TBeamType OCDBRunTypeBuffer= ((AliRPCValueDCS *) *iterValueOCDB)->GetBeamType();
                    float_t OCDBBeamEnergyBuffer= ((AliRPCValueDCS *) *iterValueOCDB)->GetBeamEnergy();
                    TLHCStatus OCDBLHCStatusBuffer= ((AliRPCValueDCS *) *iterValueOCDB)->GetLHCStatus();
                    UInt_t OCDBRunNumberBuffer=((AliRPCValueDCS *) *iterValueOCDB)->GetRunNumber();
                    ULong64_t OCDBTimeStampBuffer= ((AliRPCValueDCS *) *iterValueOCDB)->GetTimeStamp();
                    Bool_t OCDBIsCalibBuffer=((AliRPCValueDCS *) *iterValueOCDB)->IsCalib();
                    UInt_t OCDBRunYearBuffer=((AliRPCValueDCS *) *iterValueOCDB)->GetYear();

                    //check if OCDBTimestamp is updated
                    if(OCDBRunNumberBuffer>runNumberBuffer){
                        //if is updated iterator is in a new run and last endbuffer should not be updated
                        newRunBeginBuffer=OCDBTimeStampBuffer;

                        //((AliRPCValueDCS *) *iterValueOCDB)->PrintBeamStatus();
                        //printf("run: %d, start %llu, stop %llu \n",OCDBRunNumberBuffer,runBeginBuffer,runEndBuffer);


                        //iter over amanda to update the run from start to stop then look for next run
                        while(iterValueAMANDA()) {
                            ULong64_t AMANDATimeStamp = ((AliRPCValueDCS *) *iterValueAMANDA)->GetTimeStamp();
                            if ((AMANDATimeStamp >= runBeginBuffer) && (AMANDATimeStamp <= runEndBuffer)) {

                                ((AliRPCValueDCS *) *iterValueAMANDA)->SetRunNumber(runNumberBuffer);
                                ((AliRPCValueDCS *) *iterValueAMANDA)->SetBeamType(OCDBRunTypeBuffer);
                                ((AliRPCValueDCS *) *iterValueAMANDA)->SetBeamEnergy(OCDBBeamEnergyBuffer);
                                ((AliRPCValueDCS *) *iterValueAMANDA)->SetLHCStatus(OCDBLHCStatusBuffer);
                                ((AliRPCValueDCS *) *iterValueAMANDA)->SetIsCalib(OCDBIsCalibBuffer);
                                ((AliRPCValueDCS *) *iterValueAMANDA)->SetRunYear(OCDBRunYearBuffer);

                                //printf("###AMANDA###");
                                //((AliRPCValueDCS *) *iterValueAMANDA)->PrintBeamStatus();

                                DataWithRunNumber[iSide][iPlane][iRPC]->Add(*iterValueAMANDA);
                            } else if ((AMANDATimeStamp < newRunBeginBuffer) && (AMANDATimeStamp > runEndBuffer)) {
                                //now I add data with runnumber =0 (values get between two different runs)
                                DataWithRunNumber[iSide][iPlane][iRPC]->Add(*iterValueAMANDA);
                            }

                            //when the run is passed exit the cycle
                            if(iterValueAMANDANext()){
                                if(AMANDATimeStamp>=newRunBeginBuffer) break;
                            } else break;
                        }

                        //printf("end of run:%u, begin of run %u\n",runNumberBuffer,OCDBRunNumberBuffer);

                        runBeginBuffer=newRunBeginBuffer;
                        runNumberBuffer=OCDBRunNumberBuffer;

                    }else{
                        runEndBuffer=OCDBTimeStampBuffer;
                    }

                }

                DataWithRunNumber[iSide][iPlane][iRPC]->Sort();

                //Update File
                fAMANDADataContainer->cd();
                DataWithRunNumber[iSide][iPlane][iRPC]->Write(Form("AMANDA_Data_MTR_%s_MT%d_RPC%d",(fSides[iSide]).Data(),fPlanes[iPlane],iRPC+1),TObject::kSingleKey|TObject::kOverwrite);

                WhichRPC(iRPC, iSide, iPlane);

                listBufferAMANDA = 0x0;
                listBufferOCDB = 0x0;

            }
        }
    }

    fAMANDADataContainer->Flush();

}

void AliRPCAutoIntegrator::PlotSomethingVersusTime(TGraph *Graph, Bool_t (AliRPCValueDCS::*funky)() const, TList *list, std::vector<UInt_t> RunNumberList, Int_t whichValue) {
    Int_t counter=0;
    TIter iterValue(list);
    counter=0;
    while (iterValue()) {
        if(IsRunInList(RunNumberList,((AliRPCValueDCS *) *iterValue)->GetRunNumber())) {
            if ((((AliRPCValueDCS *) *iterValue)->*funky)() &&
                ((AliRPCValueDCS *) *iterValue)->GetTimeStamp() > 8000) {
                Graph->SetPoint(counter++, ((AliRPCValueDCS *) *iterValue)->GetTimeStamp(),(((AliRPCValueDCS *) *iterValue)->GetValue(whichValue)));
            }
        }
    }
    return;
}

void AliRPCAutoIntegrator::PlotSomethingVersusTime(TGraph *Graph, Bool_t (AliRPCValueDCS::*funky)() const, TList *list, UInt_t RunNumber, Int_t whichValue){
    std::vector<UInt_t> RunDummyList;
    RunDummyList.push_back(RunNumber);
    PlotSomethingVersusTime(Graph, funky, list, RunDummyList, whichValue);
    return;
}

void AliRPCAutoIntegrator::PlotSomethingVersusTime(TGraph *Graph, Bool_t (AliRPCValueDCS::*funky)() const, TList *list,std::vector<AliOCDBRun> RunNumberList, Int_t whichValue){
    std::vector<UInt_t> RunDummyList;
    for(AliOCDBRun iter :RunNumberList){
        UInt_t temp=((UInt_t)iter.fRunNumber);
        RunDummyList.push_back(temp);
    }
    PlotSomethingVersusTime(Graph, funky, list, RunDummyList, whichValue);
    return;
}

void AliRPCAutoIntegrator::PlotSomethingVersusTime(TGraph *Graph, Bool_t (AliRPCValueDCS::*funky)() const,TList *list, Int_t whichValue){
    Int_t counter=0;
    TIter iterValue(list);
    counter=0;
    while (iterValue()) {
        if ((((AliRPCValueDCS *) *iterValue)->*funky)() &&
            ((AliRPCValueDCS *) *iterValue)->GetTimeStamp() > 8000) {
            Graph->SetPoint(counter++, ((AliRPCValueDCS *) *iterValue)->GetTimeStamp(),(((AliRPCValueDCS *) *iterValue)->GetValue(whichValue)));
        }
    }
    return;
}


void AliRPCAutoIntegrator::PlotSomethingVersusRun(TGraph *Graph, Double_t (AliRPCData::*funky)(Int_t)const){
    Int_t counter=0;
    for(AliOCDBRun iter:fOCDBRunListToAdd){
        Graph->SetPoint(counter++,(fAliRPCDataObject->GetMeanTimeStampStart(iter.fRunNumber)),(fAliRPCDataObject->*funky)(iter.fRunNumber));
    }
}

void AliRPCAutoIntegrator::PlotSomethingVersusRPC(TGraph *Graph[kNSides][kNPlanes][kNRPC], Double_t (AliRPCData::*funkyX)(Int_t, Int_t, Int_t)const, Double_t (AliRPCData::*funkyY)(Int_t, Int_t, Int_t)const){
    Int_t counter=0;
    for(Int_t iSide=0;iSide<kNSides;iSide++) {
        for (Int_t iPlane = 0; iPlane < kNPlanes; iPlane++) {
            for (Int_t iRPC = 0; iRPC < kNRPC; iRPC++) {
                Graph[iSide][iPlane][iRPC]->SetPoint(counter++,(fAliRPCDataObject->*funkyX)(iSide,iPlane,iRPC),(fAliRPCDataObject->*funkyY)(iSide,iPlane,iRPC));
            }
        }
    }
}

void AliRPCAutoIntegrator::CreateDistributionSomething(TH1 *Graph, Bool_t (AliRPCValueDCS::*funky)() const, UInt_t RunNumber, Int_t whichValue, Bool_t normalizedToArea){
    TList *listBuffer;

    for (Int_t iSide = 0; iSide < kNSides; iSide++) {
        for (Int_t iPlane = 0; iPlane < kNPlanes; iPlane++) {
            for (Int_t iRPC = 0; iRPC < kNRPC; iRPC++) {

                //get Object from merged data
                fGlobalDataContainer->GetObject(
                        Form("TLists/OCDB_AMANDA_Data_MTR_%s_MT%d_RPC%d", (fSides[iSide]).Data(),
                             fPlanes[iPlane], iRPC + 1),
                        listBuffer);

                if (!listBuffer) {
                    printf("TLists/OCDB_AMANDA_Data_MTR_%s_MT%d_RPC%d NOT FOUND\n", (fSides[iSide]).Data(),
                           fPlanes[iPlane],
                           iRPC + 1);
                    continue;
                }


                TIter iterValue(listBuffer);
                while (iterValue()) {
                    if(((AliRPCValueDCS *) *iterValue)->GetRunNumber()==RunNumber){
                        if (((AliRPCValueDCS *) *iterValue)->GetTimeStamp() > 8000 &&
                            (((AliRPCValueDCS *) *iterValue)->*funky)()) {
                            Graph->Fill(
                                    (((AliRPCValueCurrent *) *iterValue)->GetValue(whichValue))/(normalizedToArea?fRPCAreas[iRPC][iPlane]:1.));
                        }
                    }
                    //when run is finished exit the cycle
                    if (((AliRPCValueDCS *) *iterValue)->GetRunNumber() > RunNumber) break;
                }

                listBuffer = 0x0;
                WhichRPC(iRPC, iSide, iPlane);
            }
        }
    }
}

void AliRPCAutoIntegrator::CreateDistributionSomething(TH1 *Graph, Bool_t (AliRPCValueDCS::*funky)() const, std::vector<AliOCDBRun> RunNumberList, Int_t whichValue, Bool_t normalizedToArea){
    for(AliOCDBRun iter: RunNumberList){
        AliRPCAutoIntegrator::CreateDistributionSomething(Graph, funky, iter.fRunNumber, whichValue, normalizedToArea);
    }
}

void AliRPCAutoIntegrator::CreateDarkCurrentDistribution(TH1 *Graph, UInt_t RunNumber) {
    AliRPCAutoIntegrator::CreateDistributionSomething(Graph, &AliRPCValueDCS::IsCurrent, RunNumber, AliRPCValueCurrent::kIDark, kTRUE);
    return;
}

void AliRPCAutoIntegrator::VoltagePlotter(TGraph *Graph, TList* list, UInt_t RunNumber){
    AliRPCAutoIntegrator::PlotSomethingVersusTime(Graph, &AliRPCValueDCS::IsVoltage, list, RunNumber, 0);
    return;
}

void AliRPCAutoIntegrator::VoltagePlotter(TGraph *Graph, TList* list, std::vector<UInt_t> RunNumberList){
    AliRPCAutoIntegrator::PlotSomethingVersusTime(Graph,&AliRPCValueDCS::IsVoltage,list,RunNumberList,0);
    return;
}

void AliRPCAutoIntegrator::VoltagePlotter(TGraph *Graph, TList* list){
    AliRPCAutoIntegrator::PlotSomethingVersusTime(Graph,&AliRPCValueDCS::IsVoltage,list);
    return;
}


/*
 * print which RPC corresponds to iSide, iPlane, iRPC
 */
void AliRPCAutoIntegrator::WhichRPC(Int_t iRPC, Int_t iSide, Int_t iPlane){
  Int_t NTot=kNRPC*kNPlanes*kNSides;
  printf("RPC:%3d out of %3d\n",kNRPC*kNPlanes*iSide+kNRPC*iPlane+iRPC+1,NTot);
  return;
}

Bool_t AliRPCAutoIntegrator::IsRunInList(std::vector<UInt_t> RunList, UInt_t RunNumber) {
    return std::find(RunList.begin(), RunList.end(), RunNumber) != RunList.end();
}
