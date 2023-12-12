#include "ntuples_macro.h"

void ntuples_macro(){
   //WRITE HERE YOUR OWN CODE

   TFile *file_ttbar = TFile::Open("ntup/410470.PhPy8EG_A14_ttbar_hdamp258p75_nonallhad_ntup.root");
   TTree *tree_ttbar = (TTree*) file_ttbar->Get("analysis");

   int nentries_ttbar = tree_ttbar->GetEntries();
   cout << "ttbar MC sample nentries: " << nentries_ttbar << endl;


   for(int i = 0; i < tree_ttbar->GetListOfBranches()->GetEntries(); ++i){
    
     cout << tree_ttbar->GetListOfBranches()->At(i)->GetName() << '\n'; 
    }

    TCanvas *canvas = new TCanvas("can","", 800, 600);
    
    TFile *file_ttbar_hist = TFile::Open("hist/410470.PhPy8EG_A14_ttbar_hdamp258p75_nonallhad_hist.root");
    TH1F *hist_ttbar_weights = (TH1F*) file_ttbar_hist->Get("CutBookkeeper_410470_284500_NOSYS");
    hist_ttbar_weights->Draw();
    canvas->Draw();

    initial_events_ttbar = hist_ttbar_weights->GetBinContent(1);
    std::cout << "initial_events_ttbar:" << "\t" << initial_events_ttbar << endl;
    initial_sum_of_weights_ttbar = hist_ttbar_weights->GetBinContent(2);
    std::cout << "initial_sum_of_weights_ttbar:" << "\t" << initial_sum_of_weights_ttbar << endl;
    initial_sum_of_weights_squared_ttbar = hist_ttbar_weights->GetBinContent(3);
    std::cout << "initial_sum_of_weights_squared_ttbar:" << "\t" << initial_sum_of_weights_squared_ttbar << endl;

    //file_ttbar->Close();

    TFile *output_ttbar = new TFile("ttbar.root", "recreate");
    TTree *tree_ttbar_2 = new TTree();
    //TTree *tree_ttbar_2 = new TTree("analysis", "analysis");

    tree_ttbar_2 = set_branch_address("ttbar");

    Float_t initial_events_ttbar = 0;
    Float_t initial_sum_of_weights_ttbar = 0;
    Float_t initial_sum_of_weights_squared_ttbar = 0;

    tree_ttbar_2->Branch("initial_events_ttbar", &initial_events_ttbar, "initial_events_ttbar/F");
    tree_ttbar_2->Branch("initial_sum_of_weights_ttbar", &initial_sum_of_weights_ttbar, "initial_sum_of_weights_ttbar/F");
    tree_ttbar_2->Branch("initial_sum_of_weights_squared_ttbar", &initial_sum_of_weights_squared_ttbar, "initial_sum_of_weights_squared_ttbar/F");

    int nbytes = 0;

    int nentries_ttbar_2 = tree_ttbar_2->GetEntries();

    for(int ii=0; ii<nentries_ttbar_2*0.0000001; ii++){

    	nbytes = tree_ttbar_2->GetEntry(ii);
    
	initial_events_ttbar = hist_ttbar_weights->GetBinContent(1);
    	initial_sum_of_weights_ttbar = hist_ttbar_weights->GetBinContent(2);
    	initial_sum_of_weights_squared_ttbar = hist_ttbar_weights->GetBinContent(3);

    	tree_ttbar_2->Fill();
    }

    output_ttbar->Write();
    
    output_ttbar->Close();
}
