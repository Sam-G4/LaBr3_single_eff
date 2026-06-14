#include <TCanvas.h>
#include <TGraph.h>
#include <TAxis.h>
#include <TStyle.h>

void plot() {
    // 1. Set a clean canvas style
    gStyle->SetOptStat(0);
    gStyle->SetGridColor(kGray);
    
    // Create a canvas window (Width: 800, Height: 600)
    TCanvas *c1 = new TCanvas("c1", "LaBr3 Detector Efficiency", 800, 600);
    c1->SetGrid(); // Turn on grid lines
    c1->SetLeftMargin(0.12);
    c1->SetBottomMargin(0.12);

    // 2. Read data from the text file
    // "%lg %*lg %*lg %lg" tells ROOT to:
    // Read 1st column (%lg -> Energy)
    // Skip 2nd column (%*lg -> GeoEff)
    // Skip 3rd column (%*lg -> IntEff)
    // Read 4th column (%lg -> AbsEff)
  //  TGraph *graph = new TGraph("efficiency_results.txt", "%lg %*lg %*lg %lg");
    //    TGraph *graph = new TGraph("Abs_eff_results.txt", "%lg %lg" );
           TGraph *graph = new TGraph("PP_eff.txt", "%lg %*lg %lg" );

    if (graph->GetN() == 0) {
        printf("Error: No data points read from efficiency_results.txt! Check file name or formatting.\n");
        return;
    }

    // 3. Customize the plot appearance
//    graph->SetTitle("Absolute Efficiency vs. Incident Gamma Energy;Energy (MeV);Absolute Efficiency (%)");
        graph->SetTitle("Photopeak Efficiency vs. Incident Gamma Energy;Energy (MeV);Photopeak Efficiency (%)");
    graph->SetMarkerStyle(21);       // Filled square markers
    graph->SetMarkerSize(1.2);       // Size of markers
    graph->SetMarkerColor(kBlue+1);  // Professional blue color
    graph->SetLineColor(kBlue-2);    // Line connecting points
    graph->SetLineWidth(2);

    // Fine-tune Axis Labels and Offsets
    graph->GetXaxis()->CenterTitle(true);
    graph->GetYaxis()->CenterTitle(true);
    graph->GetXaxis()->SetTitleSize(0.045);
    graph->GetYaxis()->SetTitleSize(0.045);
    graph->GetXaxis()->SetLabelSize(0.04);
    graph->GetYaxis()->SetLabelSize(0.04);

    // 4. Draw the graph
    // "APL" means: Draw Axis (A), Draw Points (P), Draw Line connecting them (L)
    graph->Draw("APL");

    // Update the canvas to display changes
    c1->Update();
    
    // Optional: Save the plot as an image automatically
   // c1->SaveAs("LaBr3_Absolute_Efficiency_Curve.png");
}
