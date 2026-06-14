#include <TCanvas.h>
#include <TGraph.h>
#include <TAxis.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TMultiGraph.h>

void Abs_vs_PPk() {
    // 1. Set clean, professional canvas styles
    gStyle->SetOptStat(0);
    gStyle->SetGridColor(kGray);
    
    TCanvas *c1 = new TCanvas("c1", "Efficiency Comparison", 900, 650);
    c1->SetGrid(); 
    c1->SetLeftMargin(0.12);
    c1->SetBottomMargin(0.12);
    c1->SetRightMargin(0.05);

    // 2. Read Absolute Efficiency (Columns 1 and 2)
    // "%lg %lg %*lg" -> Read 1st, Read 2nd, Skip 3rd
    TGraph *grAbs = new TGraph("PP_eff.txt", "%lg %lg %*lg");
    grAbs->SetMarkerStyle(21);        // Filled square
    grAbs->SetMarkerSize(1.2);
    grAbs->SetMarkerColor(kBlue+1);   // Solid Blue
    grAbs->SetLineColor(kBlue-2);
    grAbs->SetLineWidth(2);

    // 3. Read Photopeak Efficiency (Columns 1 and 3)
    // "%lg %*lg %lg" -> Read 1st, Skip 2nd, Read 3rd
    TGraph *grPhoto = new TGraph("PP_eff.txt", "%lg %*lg %lg");
    grPhoto->SetMarkerStyle(20);      // Filled circle
    grPhoto->SetMarkerSize(1.2);
    grPhoto->SetMarkerColor(kRed+1);  // Solid Red
    grPhoto->SetLineColor(kRed-2);
    grPhoto->SetLineWidth(2);

    // 4. Use TMultiGraph to bundle them together under a shared axis system
    TMultiGraph *mg = new TMultiGraph();
    mg->Add(grAbs, "PL");   // P = Points, L = Line
    mg->Add(grPhoto, "PL");
    
    // Set global titles and labels
    mg->SetTitle("LaBr_{3} Detector Efficiency Profiles;Incident Gamma Energy (MeV);Efficiency (%)");

    // 5. Draw the multigraph frame
    // "A" tells ROOT to generate the container frame bounding box automatically
    mg->Draw("A");

    // Fine-tune Axis Limits & Fonts (Must happen AFTER mg->Draw("A"))
    mg->GetXaxis()->CenterTitle(true);
    mg->GetYaxis()->CenterTitle(true);
    mg->GetXaxis()->SetTitleSize(0.045);
    mg->GetYaxis()->SetTitleSize(0.045);
    mg->GetYaxis()->SetRangeUser(0.0, 1.2); // Force Y-axis from 0% to 1.2% for visibility

    // 6. Construct a Legend box to differentiate curves cleanly
    TLegend *legend = new TLegend(0.65, 0.75, 0.92, 0.88);
    legend->SetBorderSize(1);
    legend->SetFillColor(kWhite);
    legend->SetTextSize(0.035);
    legend->AddEntry(grAbs, "Absolute Interaction Efficiency (>100 keV)", "pl");
    legend->AddEntry(grPhoto, "Photopeak (Full Absorption) Efficiency", "pl");
    legend->Draw();

    // Force canvas layout update
    c1->Update();
    
    // Export high-quality image artifact
    c1->SaveAs("LaBr3_Efficiency_Comparison.png");
}
