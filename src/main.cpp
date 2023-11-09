#include "support.h"

// **************** FUNCTIONS AND ROUTINES ****************

// MQTT and Time setup

// Return Register Values from the ATM90E32, or ATM90E36, - and Display
void DisplayRegisters(boolean DisplayFull = true)
{

  // PWM DutyCycle Output Pending Power Value. Test Usage: PWM_Power(2000)
  if (EnablePWMLocal == true && EnablePWMRemote == false && EnablePWMTestOutput == false)
    PWM_Power(ActivePowerExportCT1);

  if (EnablePWMLocal == false && EnablePWMRemote == true && EnablePWMTestOutput == false)
    PWM_Power(PWMRemotePower);

  // DAC Voltage Output Pending Power Value. Test Usage: DAC_Power(2000)
  // if (EnableDACLocal == true && EnableDACRemote == false && EnableDACTestOutput == false)
  //   DAC_Power(ActivePowerExportCT1);

  // if (EnableDACLocal == false && EnableDACRemote == true && EnableDACTestOutput == false)
  //   DAC_Power(PWMRemotePower);

  // if (DisplayFull == false) // Display Expanded Information
  //   Serial.println("\nDisplay Output (DisplayRegisters false), Set to Minimised");

  // Display Board Configuration
  if (EnableDisplayBoardConfiguration == true && DisplayFull == true)
    DisplayBoardConfiguration();

  // **************** VOLTAGE ****************

  // Get Mains Voltages
  LineVoltage1 = NoiseFilterSquelch(eic.GetLineVoltage1(), 1);
  LineVoltage2 = NoiseFilterSquelch(eic.GetLineVoltage2(), 1);
  LineVoltage3 = NoiseFilterSquelch(eic.GetLineVoltage3(), 1);
  LineVoltageAverage = 0;
  LineVoltageTotal = 0;

// Calculate Voltage
#if ATM_SINGLEVOLTAGE == true && ATM_SPLITPHASE == true
  Serial.println("* SOFTWARE CONFIGURATION ERROR *\n* You cannot have ATM_SINGLEVOLTAGE and ATM_SPLITPHASE, both Enabled.\n");
#else
#if ATM_SPLITPHASE == true
  LineVoltageTotal = (LineVoltage1 + LineVoltage3) / 2; // Split Single Phase configured, so only 120V per leg
#else
  LineVoltageAverage = (LineVoltage1 + LineVoltage2 + LineVoltage3) / 3; // Voltage should be around 110V, or 220-240, at the AC transformer primary.
#endif
#endif

  if (DisplayFull == true) // Display Expanded Information
  {

    // Mains RMS Voltage
    PrintUnderline("Mains RMS Voltage");

#if ATM_SINGLEVOLTAGE == false

    Serial.println("Voltage 1: " + String(LineVoltage1) + " V");

#if ATM_SPLITPHASE == false
    Serial.println("Voltage 2: " + String(LineVoltage2) + " V");
#endif

    Serial.println("Voltage 3: " + String(LineVoltage3) + " V");

#if ATM_SPLITPHASE == true
    PrintSeparator("Total Split Voltage: " + String(LineVoltageTotal) + " V (V1~X~V3)");
#else
    PrintSeparator("Average Voltage: " + String(LineVoltageAverage) + " V (V1~V2~V3)");
#endif

#else
    PrintSeparator("Voltage 1: " + String(LineVoltage1) + " V (Single Line Voltage Selected)");
#endif
  }

  // **************** CURRENT ****************

  // Get Total Current.  Ignore CT2 if Split Phase
  LineCurrentCT1 = NoiseFilterSquelch(eic.GetLineCurrentCT1());
#if ATM_SPLITPHASE == false
  LineCurrentCT2 = NoiseFilterSquelch(eic.GetLineCurrentCT2());
#else
  LineCurrentCT2 = 0;
#endif
  LineCurrentCT3 = NoiseFilterSquelch(eic.GetLineCurrentCT3());

  // Using ESP32 ADC for CT4 Current Input

#if ATM90DEVICE == ATM90E32_DEVICE || CT4_CONFIG == CT4_ESP
  ReadCT4Current();
#if CT4_ENABLED == true
  LineCurrentTotal = NoiseFilterSquelch(LineCurrentCT1 + LineCurrentCT2 + LineCurrentCT3 + LineCurrentCT4);
#else
  LineCurrentTotal = NoiseFilterSquelch(LineCurrentCT1 + LineCurrentCT2 + LineCurrentCT3);
#endif
#endif

// E36 Using I4N Input for Current
#if ATM90DEVICE == ATM90E36_DEVICE && CT4_CONFIG == CT4_ATM
  LineCurrentCTN = NoiseFilterSquelch(eic.GetLineCurrentCTN());
  LineCurrentTotal = NoiseFilterSquelch(LineCurrentCT1 + LineCurrentCT2 + LineCurrentCT3);
#endif

  if (DisplayFull == true) // Display Expanded Information
  {
    Serial.println("");

    // Mains RMS Current
    PrintUnderline("Mains RMS Current");
    Serial.println("Current CT1: " + String(LineCurrentCT1) + " A");

#if ATM_SPLITPHASE == false
    Serial.println("Current CT2: " + String(LineCurrentCT2) + " A");
#endif

    Serial.println("Current CT3: " + String(LineCurrentCT3) + " A");

#if ATM90DEVICE == ATM90E32_DEVICE && CT4_ENABLED == true || CT4_CONFIG == CT4_ESP && CT4_ENABLED == true
    Serial.println("Current CT4: " + String(LineCurrentCT4) + " A (ESP ADC1 CH7)");
#endif

#if ATM90DEVICE == ATM90E36_DEVICE && CT4_CONFIG == CT4_ATM
    Serial.println("Current CTN: " + String(LineCurrentCTN) + " A");
#endif

#if ATM_SPLITPHASE == true
    Serial.println("Actual Total Current: " + String(LineCurrentTotal) + " A (CT1~X~CT3)");
#else
#if CT4_ENABLED == true
    PrintSeparator("Actual Total Current: " + String(LineCurrentTotal) + " A (CT1~CT2~CT3~CT4)");
#else
    PrintSeparator("Actual Total Current: " + String(LineCurrentTotal) + " A (CT1~CT2~CT3)");
#endif
#endif

    Serial.println("");
  }

  // **************** POWER ****************

  // Calculated Power CT2ased on V*I
#if ATM_SINGLEVOLTAGE == true // Single Mains Voltage for all Current Measurements
  CalculatedPowerCT1 = LineVoltage1 * LineCurrentCT1;
  CalculatedPowerCT2 = LineVoltage1 * LineCurrentCT2;
  CalculatedPowerCT3 = LineVoltage1 * LineCurrentCT3;

#if ATM90DEVICE == ATM90E36_DEVICE
  CalculatedPowerCT4 = LineVoltage1 * LineCurrentCT4;
#endif

  if (DisplayFull == true) // Display Expanded Information
  {
    PrintUnderline("Calculated RMS Power");
    Serial.println("Power V1*I1: " + String(CalculatedPowerCT1) + " W");
    Serial.println("Power V1*I2: " + String(CalculatedPowerCT2) + " W");
    Serial.println("Power V1*I3: " + String(CalculatedPowerCT3) + " W");

#if ATM90DEVICE == ATM90E36_DEVICE
    Serial.println("Power V1*I4: " + String(CalculatedPowerCT4) + " W");
#endif
  }
#else // Seperate Mains Voltages for Current Measurements
  CalculatedPowerCT1 = LineVoltage1 * LineCurrentCT1;
  CalculatedPowerCT2 = LineVoltage2 * LineCurrentCT2;
  CalculatedPowerCT3 = LineVoltage3 * LineCurrentCT3;

#if ATM90DEVICE == ATM90E36_DEVICE
  CalculatedPowerCT4 = LineVoltage1 * LineCurrentCT4; // ESP32 ADC1 CH7 using V1
#endif

  if (DisplayFull == true) // Display Expanded Information
  {
    PrintUnderline("Calculated RMS Power");
    Serial.println("Power V1*I1: " + String(CalculatedPowerCT1) + " W");
    Serial.println("Power V2*I2: " + String(CalculatedPowerCT2) + " W");
    Serial.println("Power V3*I3: " + String(CalculatedPowerCT3) + " W");
  }
#if CT4_ENABLED == true && ATM90DEVICE == ATM90E36_DEVICE
  if (DisplayFull == true) // Display Expanded Information
  {
    Serial.println("Power V1*I4: " + String(CalculatedPowerCT4) + " W");
  }
#endif
#endif

// Calculate Total Watts
#if ATM_SPLITPHASE == true // USA 120+120
  CalculatedTotalPower = (LineVoltage1 * LineCurrentCT1) + (LineVoltage3 * LineCurrentCT3);

  if (DisplayFull == true) // Display Expanded Information
    PrintSeparator("Calculated Total Power: " + String(CalculatedTotalPower) + " W (CT1~X~CT3)");
#else // World
#if CT4_CONFIG == CT4_ESP && CT4_ENABLED == true
  CalculatedTotalPower = (LineVoltage1 * LineCurrentCT1) + (LineVoltage2 * LineCurrentCT2) + (LineVoltage3 * LineCurrentCT3) + (LineVoltage1 * LineCurrentCT4);

  if (DisplayFull == true) // Display Expanded Information
    PrintSeparator("Calculated Total Power: " + String(CalculatedTotalPower) + " W (CT1~CT2~CT3~CT4)");
#else
  CalculatedTotalPower = (LineVoltage1 * LineCurrentCT1) + (LineVoltage2 * LineCurrentCT2) + (LineVoltage3 * LineCurrentCT3);

  if (DisplayFull == true) // Display Expanded Information
    PrintSeparator("Calculated Total Power: " + String(CalculatedTotalPower) + " W (CT1~CT2~CT3)");
#endif
#endif

  if (DisplayFull == true) // Display Expanded Information
    Serial.println("");

  // Active Power.  Extra Import/Export values included to provide added detail for Home Automation logging
  String ActiveFlag = "";

  if (DisplayFull == true) // Display Expanded Information
    PrintUnderline("Active Power (Absorbed or Used by the Load)");

  // Active Power CT1 - Always a Postive Number
  ActivePowerCT1 = NoiseFilterSquelch(eic.GetActivePowerCT1(), 0.2);
  ActivePowerImportCT1 = 0;
  ActivePowerExportCT1 = 0;
  ActiveFlag = "";

  if (ActivePowerCT1 > 0)
  {
    ActivePowerImportCT1 = ActivePowerCT1;
    ActiveFlag = "(Import)";
  }

  if (ActivePowerCT1 < 0)
  {
    ActivePowerExportCT1 = -ActivePowerCT1;
    ActiveFlag = "(Export)";
  }

  if (DisplayFull == true) // Display Expanded Information
    Serial.println("Active Power CT1: " + String(ActivePowerCT1) + " W \t" + ActiveFlag);

  // Active Power CT2 - Always a Postive Number
  ActivePowerCT2 = NoiseFilterSquelch(eic.GetActivePowerCT2(), 0.2);
  ActivePowerImportCT2 = 0;
  ActivePowerExportCT2 = 0;
  ActiveFlag = "";

  if (ActivePowerCT2 > 0)
  {
    ActivePowerImportCT2 = ActivePowerCT2;
    ActiveFlag = "(Import)";
  }

  if (ActivePowerCT2 < 0)
  {
    ActivePowerExportCT2 = -ActivePowerCT2;
    ActiveFlag = "(Export)";
  }
  if (DisplayFull == true) // Display Expanded Information
    Serial.println("Active Power CT2: " + String(ActivePowerCT2) + " W \t" + ActiveFlag);

  // Active Power CT3 - Always a Postive Number
  ActivePowerCT3 = NoiseFilterSquelch(eic.GetActivePowerCT3(), 0.2);
  ActivePowerImportCT3 = 0;
  ActivePowerExportCT3 = 0;
  ActiveFlag = "";

  if (ActivePowerCT3 > 0)
  {
    ActivePowerImportCT3 = ActivePowerCT3;
    ActiveFlag = "(Import)";
  }

  if (ActivePowerCT3 < 0)
  {
    ActivePowerExportCT3 = -ActivePowerCT3;
    ActiveFlag = "(Export)";
  }

  if (DisplayFull == true) // Display Expanded Information
    Serial.println("Active Power CT3: " + String(ActivePowerCT3) + " W \t" + ActiveFlag);

  // Total Active Power
  TotalActivePower = NoiseFilterSquelch(eic.GetTotalActivePower(), 0.2);
  ActiveFlag = "";

  if (TotalActivePower > 0)
  {
    TotalActivePowerImport = TotalActivePower;
    ActiveFlag = "(Import)";
  }

  if (TotalActivePower < 0)
  {
    TotalActivePowerExport = -TotalActivePower;
    ActiveFlag = "(Export)";
  }

  CalculatedTotalActivePower = (ActivePowerCT1 + ActivePowerCT2 + ActivePowerCT3);

  if (DisplayFull == true) // Display Expanded Information
  {
    PrintSeparator("Total Active Power: " + String(TotalActivePower) + " W \t" + ActiveFlag);
    PrintSeparator("Calculated Total Active Power: " + String(CalculatedTotalActivePower) + " W (CT1~CT2~CT3)");
    Serial.println("");
  }

  // Re-Active Power
  ReactivePowerCT1 = NoiseFilterSquelch(eic.GetReactivePowerCT1());
  ReactivePowerCT2 = NoiseFilterSquelch(eic.GetReactivePowerCT2());
  ReactivePowerCT3 = NoiseFilterSquelch(eic.GetReactivePowerCT3());
  TotalReactivePower = NoiseFilterSquelch(eic.GetTotalReactivePower());
  CalculatedTotalReactivePower = (ReactivePowerCT1 + ReactivePowerCT2 + ReactivePowerCT3);

  if (DisplayFull == true) // Display Expanded Information
  {
    PrintUnderline("Re-Active Power");
    Serial.println("ReActive Power CT1: " + String(ReactivePowerCT1) + " VAR");
    Serial.println("ReActive Power CT2: " + String(ReactivePowerCT2) + " VAR");
    Serial.println("ReActive Power CT3: " + String(ReactivePowerCT3) + " VAR");
    PrintSeparator("Total ReActive Power: " + String(TotalReactivePower) + " VAR (CT1~CT2~CT3)");

    PrintSeparator("Calculated Total Reactive Power: " + String(CalculatedTotalReactivePower) + " W (CT1~CT2~CT3)");
    Serial.println("");
  }

  // Apparent Power Flowing - Voltage and Current (V * I)
  ApparentPowerCT1 = NoiseFilterSquelch(eic.GetApparentPowerCT1());
  ApparentPowerCT2 = NoiseFilterSquelch(eic.GetApparentPowerCT2());
  ApparentPowerCT3 = NoiseFilterSquelch(eic.GetApparentPowerCT3());
  TotalApparentPower = NoiseFilterSquelch(eic.GetTotalApparentPower());
  CalculatedTotalApparentPower = (ApparentPowerCT1 + ApparentPowerCT2 + ApparentPowerCT3);

  if (DisplayFull == true) // Display Expanded Information
  {
    PrintUnderline("Apparent Power (Total Amount of Power Flowing from Source to Load)");
    Serial.println("Apparent Power CT1: " + String(ApparentPowerCT1) + " VA");
    Serial.println("Apparent Power CT2: " + String(ApparentPowerCT2) + " VA");
    Serial.println("Apparent Power CT3: " + String(ApparentPowerCT3) + " VA");
    PrintSeparator("Total Apparent Power: " + String(TotalApparentPower) + " VA (CT1~CT2~CT3)");

    PrintSeparator("Calculated Total Apparent Power: " + String(CalculatedTotalApparentPower) + " W (CT1~CT2~CT3)");
    Serial.println("\n");
  }

#if ATM90DEVICE == ATM90E32_DEVICE
  if (DisplayFull == true) // Display Expanded Information
    PrintUnderline("Other Power Information");

  // Total Fundamental Power
  TotalActiveFundPower = NoiseFilterSquelch(eic.GetTotalActiveFundPower());
  if (DisplayFull == true) // Display Expanded Information
    Serial.println("Total Fundamental Power: " + String(TotalActiveFundPower) + " pH(t)\n");

  // Total Harmonic Power
  TotalActiveHarPower = NoiseFilterSquelch(eic.GetTotalActiveHarPower());
  if (DisplayFull == true) // Display Expanded Information
    Serial.println("Total Harmonic Power: " + String(TotalActiveHarPower) + " ");

#endif

  if (DisplayFull == true)
    Serial.println("");

  // **************** OTHER ****************

  // Power Factor
  PowerFactorCT1 = NoiseFilterSquelch(eic.GetPowerFactorCT1(), 0.01, false);
  PowerFactorCT2 = NoiseFilterSquelch(eic.GetPowerFactorCT2(), 0.01, false);
  PowerFactorCT3 = NoiseFilterSquelch(eic.GetPowerFactorCT3(), 0.01, false);
  TotalPowerFactor = NoiseFilterSquelch(eic.GetTotalPowerFactor(), 0, false);

  if (DisplayFull == true) // Display Expanded Information
  {
    PrintUnderline("Power Factor");
    Serial.println("Power Factor CT1: " + String(PowerFactorCT1) + " PF");
    Serial.println("Power Factor CT2: " + String(PowerFactorCT2) + " PF");
    Serial.println("Power Factor CT3: " + String(PowerFactorCT3) + " PF");
    PrintSeparator("Total Power Factor: " + String(TotalPowerFactor) + " PF");
    Serial.println("");
  }

  // Phase Angle
  PhaseAngleCT1 = NoiseFilterSquelch(eic.GetPhaseCT1(), 0, true, 180);
  PhaseAngleCT2 = NoiseFilterSquelch(eic.GetPhaseCT2(), 0, true, 180);
  PhaseAngleCT3 = NoiseFilterSquelch(eic.GetPhaseCT3(), 0, true, 180);

  if (DisplayFull == true) // Display Expanded Information
  {
    PrintUnderline("Phase Angle");
    Serial.println("Phase Angle CT1: " + String(PhaseAngleCT1));
    Serial.println("Phase Angle CT2: " + String(PhaseAngleCT2));
    Serial.println("Phase Angle CT3: " + String(PhaseAngleCT3));
    Serial.println("");
  }

  if (DisplayFull == true) // Display Expanded Information
    PrintUnderline("Other Information");

  // Chip Temperature
  ChipTemperature = NoiseFilterSquelch(eic.GetTemperature());

  if (DisplayFull == true) // Display Expanded Information
    Serial.println("Chip Temperature: " + String(ChipTemperature) + " °C\n");

  // Line Frequency
  LineFrequency = NoiseFilterSquelch(eic.GetFrequency());

  if (DisplayFull == true) // Display Expanded Information
    Serial.println("Mains Frequency: " + String(LineFrequency) + " Hz\n");

  // Read PCB NTC Temperature
  if (DisplayFull == true)
    ReadPCBTemperature(); // Read PCB NTC Temperature

  if (DisplayFull == true)
    Serial.println("");

  // Read PCB DCV_IN Voltage
  if (DisplayFull == true)
    ReadADCVoltage(); // Read AC>DC Input Voltage
}

// **************** SETUP ****************
void setup()
{
  // Stabalise
  delay(250);

  // Initialise UART
  Serial.begin(115200); // 115200
  while (!Serial)
    ;
  Serial.println("");

  if (!runWiFiManager())
  {
    // couldn't connect
    Serial.println("[main] Couldn't connect to WiFi after multiple attempts");
    delay(30000);
    ESP.restart();
  }
  Serial.println("WIFI Connected");

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  // Initialize and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

  // IPEM Board Port Configuration
  ConfigureBoard();

  // Check DCV_IN
  CheckDCVINVoltage();

// ****************  Initialise the ATM90E3x & Pass related calibrations to its library ****************

// LineFreq = lineFreq, PGAGain = pgagain, VoltageGainX = ugain, CurrentGainCT1 = igainA, CurrentGainCT2 = igainB, CurrentGainCT3 = igainC, CurrentGainCTN = igainN
#if ATM90DEVICE == ATM90E32_DEVICE && ATM_SPLITPHASE == true // Not Fully Tested.
// the 2nd (B) current channel is not used with the split phase meter
#if ATM_SINGLEVOLTAGE == true
  eic.begin(LineFreq, PGAGain, VoltageGain1, 0, 0, CurrentGainCT1, 0, CurrentGainCT2);
#else
  eic.begin(LineFreq, PGAGain, VoltageGain1, VoltageGain2, VoltageGain3, CurrentGainCT1, 0, CurrentGainCT2);
#endif
#endif

#if ATM90DEVICE == ATM90E32_DEVICE && ATM_SPLITPHASE == false
#if ATM_SINGLEVOLTAGE == true
  // eic.begin(LineFreq, PGAGain, VoltageGain1, 0, 0, CurrentGainCT1, CurrentGainCT2, CurrentGainCT3);
  eic.begin(LineFreq, PGAGain, VoltageGain1, VoltageGain1, VoltageGain1, CurrentGainCT1, CurrentGainCT2, CurrentGainCT3);
#else
  eic.begin(LineFreq, PGAGain, VoltageGain1, VoltageGain2, VoltageGain3, CurrentGainCT1, CurrentGainCT2, CurrentGainCT3);
#endif
#endif

#if ATM90DEVICE == ATM90E36_DEVICE && ATM_SPLITPHASE == false
#if ATM_SINGLEVOLTAGE == true
  // eic.begin(LineFreq, PGAGain, VoltageGain1, 0, 0, CurrentGainCT1, CurrentGainCT2, CurrentGainCT3, CurrentGainCTN);
  eic.begin(LineFreq, PGAGain, VoltageGain1, VoltageGain1, VoltageGain1, CurrentGainCT1, CurrentGainCT2, CurrentGainCT3, CurrentGainCTN);
#else
  eic.begin(LineFreq, PGAGain, VoltageGain1, VoltageGain2, VoltageGain3, CurrentGainCT1, CurrentGainCT2, CurrentGainCT3, CurrentGainCTN);
#endif
#endif

  Serial.println("IPEM Hardware Setup and Power-Up Test - Board Initialized");

  delay(1000);

  Serial.println("");

  DisplayRegisters(); // Display once

} // Setup

// **************** LOOP ****************
void loop() // Future - ISRs To Be Added
{
  repeatedCall();

  if (!client.connected())
  {
    reconnect();
  }
  client.loop();

  printLocalTime();

  String sDIR = "";

  // Force Continuous Test PWM Cycle Loop. Force OFF EnablePWMLocal EnablePWMRemote
  if (EnablePWMTestOutput == true)
  {
    EnablePWMLocal = false;
    EnablePWMRemote = false;
    PWM_Test();
  }

  // Simply DisplayRegisters on Loop if Enabled
  if (EnableBasicLoop == true)
  {
    DisplayRegisters();
    Serial.println("- - - / / - - -\n");
  }

  DisplayRegisters();
  Serial.println("- - - / / - - -\n");

  DisplayRegisters(false); // Refresh Values and Display.  Default false = Mute Expanded Info to Serial

  if (LineVoltageAverage > 100 || LineVoltage1 > 100) // Arbitrary Value
  {
    float LineVoltage1 = 0.0;
    if (ActivePowerImportCT1 > 0)
    {
      Serial.print(ActivePowerImportCT1);
      Serial.println("%.0f W");
      sDIR = "Impt";
    }
    else if (ActivePowerExportCT1 > 0)
    {
      Serial.print(ActivePowerExportCT1);
      Serial.println("%.0f W");
      sDIR = "Expt";
    }
    else
    {
      Serial.println("0 W");
      sDIR = "Zero";
    }

    if (ActivePowerImportCT2 > 0)
    {
      Serial.print(ActivePowerImportCT2);
      Serial.println("%.0f W");
      sDIR = "Impt";
    }
    else if (ActivePowerExportCT2 > 0)
    {
      Serial.print(ActivePowerExportCT2);
      Serial.println("%.0f W");
      sDIR = "Expt";
    }
    else
    {
      Serial.println("0 W");
      sDIR = "Zero";
    }

    if (ActivePowerImportCT3 > 0)
    {
      Serial.print(ActivePowerImportCT3);
      Serial.println("%.0f W");
      sDIR = "Impt";
    }
    else if (ActivePowerExportCT3 > 0)
    {
      Serial.print(ActivePowerExportCT3);
      Serial.println("%.0f W");
      sDIR = "Expt";
    }
    else
    {
      Serial.println("0 W");
      sDIR = "Zero";
    }

    Serial.print(LineVoltage1);
    Serial.println(" V " + sDIR);

    StaticJsonDocument<384> esp_data;

    esp_data["Time"] = ntp_time;
    esp_data["VoltageA"] = String(eic.GetLineVoltage1()) + "V";
    esp_data["VoltageB"] = String(eic.GetLineVoltage2()) + "V";
    esp_data["VoltageC"] = String(eic.GetLineVoltage3()) + "V";
    esp_data["CurrentA"] = String(eic.GetLineCurrentCT1()) + "A";
    esp_data["CurrentB"] = String(eic.GetLineCurrentCT2()) + "A";
    esp_data["CurrentC"] = String(eic.GetLineCurrentCT3()) + "A";
    esp_data["ActivePowerA"] = String(eic.GetActivePowerCT1()) + "W";
    esp_data["ActivePowerB"] = String(eic.GetActivePowerCT2()) + "W";
    esp_data["ActivePowerC"] = String(eic.GetActivePowerCT3()) + "W";
    esp_data["TotalActivePower"] = String(eic.GetTotalActivePower()) + "W";
    esp_data["ReactivePowerA"] = String(eic.GetReactivePowerCT1()) + "W";
    esp_data["ReactivePowerB"] = String(eic.GetReactivePowerCT2()) + "W";
    esp_data["ReactivePowerC"] = String(eic.GetReactivePowerCT3()) + "W";
    esp_data["PowerFactorA"] = String(eic.GetPowerFactorCT1()) + "W";
    esp_data["PowerFactorB"] = String(eic.GetPowerFactorCT2()) + "W";
    esp_data["PowerFactorC"] = String(eic.GetPowerFactorCT3()) + "W";
    esp_data["TotalActiveFundPower"] = String(eic.GetTotalActiveFundPower()) + "W";

    char output[384];
    serializeJson(esp_data, output);

    client.publish("updates", output);
  }
  else
  {
    // Houston, We may have a probem
    Serial.println("Please Chk");
    Serial.println("Line Volts");

    delay(1500);
  }

  // Loop Delay
  delay(LoopDelay * 1000);
} // loop
