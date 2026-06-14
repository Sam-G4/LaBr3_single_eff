#!/bin/bash

# Define the absolute path matching your new C++ file name
OUTPUT_FILE="PP_eff.txt"

# Write the updated clean Photopeak headers (2 Columns)
echo -e "Energy(MeV)\tAbsEff (%)\tPhotopeakEff(%)" > "$OUTPUT_FILE"

current_energy=0.662
max_energy=20.0
interval=0.500

echo "Starting automated Photopeak efficiency energy scan..."

while (( $(echo "$current_energy <= $max_energy" | bc -l) )); do
    echo "------------------------------------------------"
    echo "Simulating Energy Step: $current_energy MeV"
    echo "------------------------------------------------"

    # Inject initialization instruction followed by the template contents
    echo "/run/initialize" > run_active.mac
    sed "s/ENERGY_PLACEHOLDER/$current_energy/g" template.mac >> run_active.mac

    # Execute simulation frame
    ./LaBr3_cyl run_active.mac

    # Track writing status directly to terminal
    if [ -f "$OUTPUT_FILE" ]; then
        echo "--> Data written. Photopeak summary currently holds $(wc -l < $OUTPUT_FILE) rows."
    fi

    current_energy=$(echo "$current_energy + $interval" | bc -l)
done

# Clear out temporary files
rm -f run_active.mac

echo "================================================"
echo "Scan complete! Results compiled in PP_eff.txt"
echo "================================================"
