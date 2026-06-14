## To run Single energy
1. set energy of gammma in **PrimaryGeneratorAction**
2. If u wanna see the plots set the corresponding E- intervals (x-axis)
3. Run with **./LaBr3_cyl gamma.mac**


##To run a set of energies from 0.662 to 20 MeV with 500keV bin width
1. **./scan_energies.sh**

## The shell script 
1. Utilizes tempelate.mac for getting energies and running the program
2. Saved as scan_energies.sh
3. Then  Provide script initialization permissions
   using **chmod +x scan_energies.sh**
4. Once done need not do again, but if u copy paste this program might need to run again.


##tempelate.mac

