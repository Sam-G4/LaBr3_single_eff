void compare_Eff()
{
    std::vector<double> E1, Eff1;
    std::vector<double> E2, Eff2;

    // -------- Read first file --------
    std::ifstream f1("Abs_eff_results_Al_housing.txt");
    double e, eff;

    while (f1 >> e >> eff) {
        E1.push_back(e);
        Eff1.push_back(eff);
    }
    f1.close();

    // -------- Read second file --------
    std::ifstream f2("Abs_eff_results_1.txt");

    while (f2 >> e >> eff) {
        E2.push_back(e);
        Eff2.push_back(eff);
    }
    f2.close();

    // -------- Create graphs --------
    TGraph *g1 = new TGraph(E1.size(), &E1[0], &Eff1[0]);
    TGraph *g2 = new TGraph(E2.size(), &E2[0], &Eff2[0]);

    g1->SetLineColor(kBlue);
    g1->SetMarkerColor(kBlue);
    g1->SetMarkerStyle(20);
    g1->SetLineWidth(2);

    g2->SetLineColor(kRed);
    g2->SetMarkerColor(kRed);
    g2->SetMarkerStyle(21);
    g2->SetLineWidth(2);

    // -------- Draw --------
    TCanvas *c1 = new TCanvas("c1","Efficiency Comparison",900,700);

    g1->SetTitle("Efficiency Comparison;Energy (MeV);Efficiency (%)");
    g1->Draw("ALP");
    g2->Draw("LP SAME");

    // -------- Legend --------
    TLegend *leg = new TLegend(0.65,0.75,0.88,0.88);
    leg->AddEntry(g1,"Al_casing","lp");
    leg->AddEntry(g2,"SS_casing","lp");
    leg->Draw();

    c1->Update();
}
