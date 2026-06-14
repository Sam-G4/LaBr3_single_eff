void plot_eff()
{
    std::vector<double> E;
    std::vector<double> Eff;

    //std::ifstream infile("Abs_eff_results.txt");
       std::ifstream infile("PP_eff.txt");

    // Skip header line
    std::string line;
    std::getline(infile, line);

//    double energy, geoeff, inteff, abseff;
        double energy, AbsEff, PhotopkEff;

 //   while (infile >> energy >> geoeff >> inteff >> abseff)
        while (infile >> energy >> AbsEff, PhotopkEff)
    {
        E.push_back(energy);
        Eff.push_back(AbsEff);   // Change to geoeff or inteff if desired
    }

    infile.close();

    TGraph *gr = new TGraph(E.size(), &E[0], &Eff[0]);

    gr->SetTitle("Absolute Efficiency;Energy (MeV);Efficiency (%)");
    gr->SetMarkerStyle(20);
    gr->SetMarkerSize(1.0);
    gr->SetLineWidth(2);

    TCanvas *c1 = new TCanvas("c1","Efficiency Plot",900,700);
    gr->Draw("ALP");

    c1->Update();
}
