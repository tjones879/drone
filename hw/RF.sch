EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A 11000 8500
encoding utf-8
Sheet 2 4
Title ""
Date "2019-10-03"
Rev "A"
Comp "Tyler Jones"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L dk_RF-Transceiver-ICs:CC1101RGPR U1
U 1 1 5D96A68A
P 7300 4000
F 0 "U1" H 7800 4350 60  0000 C CNN
F 1 "CC1101RGPR" H 8000 4450 60  0000 C CNN
F 2 "Package_DFN_QFN:QFN-20-1EP_4x4mm_P0.5mm_EP2.7x2.7mm_ThermalVias" H 7500 4200 60  0001 L CNN
F 3 "http://www.ti.com/general/docs/suppproductinfo.tsp?distId=10&gotoUrl=http%3A%2F%2Fwww.ti.com%2Flit%2Fgpn%2Fcc1101" H 7500 4300 60  0001 L CNN
F 4 "296-35718-1-ND" H 7500 4400 60  0001 L CNN "Digi-Key_PN"
F 5 "CC1101RGPR" H 7500 4500 60  0001 L CNN "MPN"
F 6 "RF/IF and RFID" H 7500 4600 60  0001 L CNN "Category"
F 7 "RF Transceiver ICs" H 7500 4700 60  0001 L CNN "Family"
F 8 "http://www.ti.com/general/docs/suppproductinfo.tsp?distId=10&gotoUrl=http%3A%2F%2Fwww.ti.com%2Flit%2Fgpn%2Fcc1101" H 7500 4800 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/texas-instruments/CC1101RGPR/296-35718-1-ND/3947329" H 7500 4900 60  0001 L CNN "DK_Detail_Page"
F 10 "IC RF TXRX ISM<1GHZ 20VFQFN" H 7500 5000 60  0001 L CNN "Description"
F 11 "Texas Instruments" H 7500 5100 60  0001 L CNN "Manufacturer"
F 12 "Active" H 7500 5200 60  0001 L CNN "Status"
	1    7300 4000
	0    1    1    0   
$EndComp
$Comp
L SparkFun-PowerSymbols:GND #GND0101
U 1 1 5D96E54E
P 6300 4250
F 0 "#GND0101" H 6350 4200 45  0001 L BNN
F 1 "GND" H 6300 4080 45  0000 C CNN
F 2 "" H 6300 4150 60  0001 C CNN
F 3 "" H 6300 4150 60  0001 C CNN
	1    6300 4250
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-PowerSymbols:GND #GND0102
U 1 1 5D96EA50
P 6100 4250
F 0 "#GND0102" H 6150 4200 45  0001 L BNN
F 1 "GND" H 6100 4080 45  0000 C CNN
F 2 "" H 6100 4150 60  0001 C CNN
F 3 "" H 6100 4150 60  0001 C CNN
	1    6100 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 4100 6300 4250
$Comp
L SparkFun-Clocks:CRYSTALPTH-2X6 Y1
U 1 1 5D9752D5
P 7050 3000
F 0 "Y1" H 7000 3150 45  0000 L CNN
F 1 "CRYSTALPTH-2X6" V 7050 2200 45  0001 L CNN
F 2 "Crystal:Crystal_AT310_D3.0mm_L10.0mm_Horizontal" H 7050 3200 20  0001 C CNN
F 3 "" H 7050 3000 50  0001 C CNN
F 4 "XXX-00000" V 7150 2250 60  0001 L CNN "Field4"
	1    7050 3000
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-Capacitors:0.1UF-KIT-EZ-50V-20% C7
U 1 1 5D981962
P 6950 2800
F 0 "C7" H 6750 2850 45  0000 L CNN
F 1 "0.1UF-KIT-EZ-50V-20%" H 7058 2861 45  0001 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 6950 3050 20  0001 C CNN
F 3 "" H 6950 2800 50  0001 C CNN
F 4 "CAP-08370" H 7058 2766 60  0001 L CNN "Field4"
	1    6950 2800
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-PowerSymbols:GND #GND0103
U 1 1 5D9935AD
P 6950 2600
F 0 "#GND0103" H 7000 2550 45  0001 L BNN
F 1 "GND" H 6950 2430 45  0000 C CNN
F 2 "" H 6950 2500 60  0001 C CNN
F 3 "" H 6950 2500 60  0001 C CNN
	1    6950 2600
	-1   0    0    1   
$EndComp
Wire Wire Line
	7000 3400 7000 3150
Wire Wire Line
	7000 3150 6950 3150
Wire Wire Line
	6950 3150 6950 3000
Wire Wire Line
	6950 2900 6950 3000
Connection ~ 6950 3000
$Comp
L SparkFun-Capacitors:0.1UF-KIT-EZ-50V-20% C8
U 1 1 5D9AA820
P 7150 2800
F 0 "C8" H 7258 2850 45  0000 L CNN
F 1 "0.1UF-KIT-EZ-50V-20%" H 7258 2861 45  0001 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 7150 3050 20  0001 C CNN
F 3 "" H 7150 2800 50  0001 C CNN
F 4 "CAP-08370" H 7258 2766 60  0001 L CNN "Field4"
	1    7150 2800
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-PowerSymbols:GND #GND0104
U 1 1 5D9AA826
P 7150 2600
F 0 "#GND0104" H 7200 2550 45  0001 L BNN
F 1 "GND" H 7150 2430 45  0000 C CNN
F 2 "" H 7150 2500 60  0001 C CNN
F 3 "" H 7150 2500 60  0001 C CNN
	1    7150 2600
	-1   0    0    1   
$EndComp
Wire Wire Line
	7100 3400 7100 3150
Wire Wire Line
	7100 3150 7150 3150
Wire Wire Line
	7150 3150 7150 3000
Wire Wire Line
	7150 3000 7150 2900
Connection ~ 7150 3000
Wire Wire Line
	8000 3900 8000 4000
Wire Wire Line
	8000 4000 8000 4100
Connection ~ 8000 4000
Wire Wire Line
	8000 4100 8000 4200
Connection ~ 8000 4100
$Comp
L SparkFun-PowerSymbols:3.3V #SUPPLY0101
U 1 1 5D9B151B
P 8350 3700
F 0 "#SUPPLY0101" H 8400 3700 45  0001 L BNN
F 1 "3.3V" H 8350 3870 45  0000 C CNN
F 2 "XXX-00000" H 8350 3881 60  0001 C CNN
F 3 "" H 8350 3700 60  0001 C CNN
	1    8350 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	8000 3900 8350 3900
Wire Wire Line
	8350 3900 8350 3700
Connection ~ 8000 3900
Wire Wire Line
	8000 3700 8350 3700
Connection ~ 8350 3700
Text HLabel 8050 3300 2    50   Input ~ 0
RF_SCK
$Comp
L SparkFun-PowerSymbols:GND #GND0105
U 1 1 5D9B86E3
P 6150 2800
F 0 "#GND0105" H 6200 2750 45  0001 L BNN
F 1 "GND" H 6150 2630 45  0000 C CNN
F 2 "" H 6150 2700 60  0001 C CNN
F 3 "" H 6150 2700 60  0001 C CNN
	1    6150 2800
	-1   0    0    1   
$EndComp
$Comp
L SparkFun-Resistors:RESISTOR0402 R1
U 1 1 5D9B8F7F
P 6150 3000
F 0 "R1" V 6150 3068 45  0000 L CNN
F 1 "RESISTOR0402" V 6139 3068 45  0001 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 6150 3150 20  0001 C CNN
F 3 "" H 6150 3000 60  0001 C CNN
F 4 " " V 6234 3068 60  0001 L CNN "Field4"
	1    6150 3000
	0    1    1    0   
$EndComp
Text HLabel 8050 3000 2    50   Input ~ 0
RF_CS
Text HLabel 7200 5200 0    50   Input ~ 0
RF_MISO
Text HLabel 6200 3400 0    50   Input ~ 0
RF_MOSI
Wire Wire Line
	7400 3400 7400 3300
Wire Wire Line
	7400 3300 8050 3300
Wire Wire Line
	7200 3400 7200 3000
Wire Wire Line
	7200 3000 8050 3000
NoConn ~ 7300 3400
NoConn ~ 7100 4600
Wire Wire Line
	7200 4600 7200 5200
$Comp
L SparkFun-PowerSymbols:GND #GND0106
U 1 1 5D9F85B8
P 6900 4600
F 0 "#GND0106" H 6950 4550 45  0001 L BNN
F 1 "GND" H 6900 4430 45  0000 C CNN
F 2 "" H 6900 4500 60  0001 C CNN
F 3 "" H 6900 4500 60  0001 C CNN
	1    6900 4600
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-Capacitors:0.1UF-KIT-EZ-50V-20% C9
U 1 1 5DA0075A
P 8650 3800
F 0 "C9" V 8500 3850 45  0000 C CNN
F 1 "0.1UF-KIT-EZ-50V-20%" H 8758 3861 45  0001 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 8650 4050 20  0001 C CNN
F 3 "" H 8650 3800 50  0001 C CNN
F 4 "CAP-08370" H 8758 3766 60  0001 L CNN "Field4"
	1    8650 3800
	0    1    1    0   
$EndComp
Wire Wire Line
	8000 3800 8550 3800
$Comp
L SparkFun-PowerSymbols:GND #GND0107
U 1 1 5DA01234
P 8850 3800
F 0 "#GND0107" H 8900 3750 45  0001 L BNN
F 1 "GND" H 8920 3650 45  0000 R CNN
F 2 "" H 8850 3700 60  0001 C CNN
F 3 "" H 8850 3700 60  0001 C CNN
	1    8850 3800
	1    0    0    -1  
$EndComp
Text Label 6800 3400 1    50   ~ 0
RF_N
Text Label 6900 3400 1    50   ~ 0
RF_P
Wire Wire Line
	6600 3400 6200 3400
Wire Wire Line
	6700 3400 6700 3200
Wire Wire Line
	6700 3200 6150 3200
Text Label 4650 4250 0    50   ~ 0
RF_N
Text Label 4650 3850 0    50   ~ 0
RF_P
$Comp
L SparkFun-Coils:INDUCTOR-0402-3.9NH L5
U 1 1 5DA164EE
P 4300 4250
F 0 "L5" V 4214 4250 45  0000 C CNN
F 1 "INDUCTOR-0402-3.9NH" V 4108 4250 45  0001 C CNN
F 2 "Inductor_SMD:L_0805_2012Metric" H 4300 4500 20  0001 C CNN
F 3 "" H 4300 4250 50  0001 C CNN
F 4 "NDUC-13457" V 4203 4250 60  0001 C CNN "Field4"
	1    4300 4250
	0    1    1    0   
$EndComp
$Comp
L SparkFun-Coils:INDUCTOR-0402-3.9NH L4
U 1 1 5DA177FA
P 4300 3850
F 0 "L4" V 4214 3850 45  0000 C CNN
F 1 "INDUCTOR-0402-3.9NH" V 4108 3850 45  0001 C CNN
F 2 "Inductor_SMD:L_0805_2012Metric" H 4300 4100 20  0001 C CNN
F 3 "" H 4300 3850 50  0001 C CNN
F 4 "NDUC-13457" V 4203 3850 60  0001 C CNN "Field4"
	1    4300 3850
	0    1    1    0   
$EndComp
$Comp
L SparkFun-Coils:INDUCTOR-0402-3.9NH L3
U 1 1 5DA17EF8
P 3600 4250
F 0 "L3" V 3514 4250 45  0000 C CNN
F 1 "INDUCTOR-0402-3.9NH" V 3408 4250 45  0001 C CNN
F 2 "Inductor_SMD:L_0805_2012Metric" H 3600 4500 20  0001 C CNN
F 3 "" H 3600 4250 50  0001 C CNN
F 4 "NDUC-13457" V 3503 4250 60  0001 C CNN "Field4"
	1    3600 4250
	0    1    1    0   
$EndComp
$Comp
L SparkFun-Capacitors:0.1UF-KIT-EZ-50V-20% C6
U 1 1 5DA1B017
P 4100 4100
F 0 "C6" H 4208 4150 45  0000 L CNN
F 1 "0.1UF-KIT-EZ-50V-20%" H 4208 4161 45  0001 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4100 4350 20  0001 C CNN
F 3 "" H 4100 4100 50  0001 C CNN
F 4 "CAP-08370" H 4208 4066 60  0001 L CNN "Field4"
	1    4100 4100
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-Capacitors:0.1UF-KIT-EZ-50V-20% C3
U 1 1 5DA1BF75
P 3600 3850
F 0 "C3" H 3708 3900 45  0000 L CNN
F 1 "0.1UF-KIT-EZ-50V-20%" H 3708 3911 45  0001 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3600 4100 20  0001 C CNN
F 3 "" H 3600 3850 50  0001 C CNN
F 4 "CAP-08370" H 3708 3816 60  0001 L CNN "Field4"
	1    3600 3850
	0    1    1    0   
$EndComp
$Comp
L SparkFun-Capacitors:0.1UF-KIT-EZ-50V-20% C4
U 1 1 5DA21E27
P 3950 3650
F 0 "C4" H 4058 3700 45  0000 L CNN
F 1 "0.1UF-KIT-EZ-50V-20%" H 4058 3711 45  0001 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3950 3900 20  0001 C CNN
F 3 "" H 3950 3650 50  0001 C CNN
F 4 "CAP-08370" H 4058 3616 60  0001 L CNN "Field4"
	1    3950 3650
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-Capacitors:0.1UF-KIT-EZ-50V-20% C5
U 1 1 5DA225FB
P 3950 4550
F 0 "C5" H 4058 4600 45  0000 L CNN
F 1 "0.1UF-KIT-EZ-50V-20%" H 4058 4611 45  0001 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3950 4800 20  0001 C CNN
F 3 "" H 3950 4550 50  0001 C CNN
F 4 "CAP-08370" H 4058 4516 60  0001 L CNN "Field4"
	1    3950 4550
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-PowerSymbols:GND #GND0108
U 1 1 5DA26B2C
P 3950 3450
F 0 "#GND0108" H 4000 3400 45  0001 L BNN
F 1 "GND" H 3950 3280 45  0000 C CNN
F 2 "" H 3950 3350 60  0001 C CNN
F 3 "" H 3950 3350 60  0001 C CNN
	1    3950 3450
	-1   0    0    1   
$EndComp
$Comp
L SparkFun-PowerSymbols:GND #GND0109
U 1 1 5DA2723A
P 3950 4650
F 0 "#GND0109" H 4000 4600 45  0001 L BNN
F 1 "GND" H 3950 4480 45  0000 C CNN
F 2 "" H 3950 4550 60  0001 C CNN
F 3 "" H 3950 4550 60  0001 C CNN
	1    3950 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 3850 4650 3850
Wire Wire Line
	4500 4250 4650 4250
Wire Wire Line
	4100 3850 4100 3900
Wire Wire Line
	4100 4250 4100 4200
Wire Wire Line
	3800 4250 3950 4250
Connection ~ 4100 4250
Wire Wire Line
	3950 4350 3950 4250
Connection ~ 3950 4250
Wire Wire Line
	3950 4250 4100 4250
Wire Wire Line
	3800 3850 3950 3850
Connection ~ 4100 3850
Wire Wire Line
	3950 3750 3950 3850
Connection ~ 3950 3850
Wire Wire Line
	3950 3850 4100 3850
$Comp
L SparkFun-Capacitors:0.1UF-KIT-EZ-50V-20% C2
U 1 1 5DA59F11
P 2850 3900
F 0 "C2" H 2958 3950 45  0000 L CNN
F 1 "0.1UF-KIT-EZ-50V-20%" H 2958 3961 45  0001 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2850 4150 20  0001 C CNN
F 3 "" H 2850 3900 50  0001 C CNN
F 4 "CAP-08370" H 2958 3866 60  0001 L CNN "Field4"
	1    2850 3900
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-PowerSymbols:GND #GND0110
U 1 1 5DA59F17
P 2850 3700
F 0 "#GND0110" H 2900 3650 45  0001 L BNN
F 1 "GND" H 2850 3530 45  0000 C CNN
F 2 "" H 2850 3600 60  0001 C CNN
F 3 "" H 2850 3600 60  0001 C CNN
	1    2850 3700
	-1   0    0    1   
$EndComp
$Comp
L SparkFun-Coils:INDUCTOR-0402-3.9NH L2
U 1 1 5DA5E843
P 3150 4050
F 0 "L2" V 3064 4050 45  0000 C CNN
F 1 "INDUCTOR-0402-3.9NH" V 2958 4050 45  0001 C CNN
F 2 "Inductor_SMD:L_0805_2012Metric" H 3150 4300 20  0001 C CNN
F 3 "" H 3150 4050 50  0001 C CNN
F 4 "NDUC-13457" V 3053 4050 60  0001 C CNN "Field4"
	1    3150 4050
	0    1    1    0   
$EndComp
Wire Wire Line
	3500 3850 3350 3850
Wire Wire Line
	3350 3850 3350 4050
Wire Wire Line
	3350 4050 3350 4250
Wire Wire Line
	3350 4250 3400 4250
Connection ~ 3350 4050
Wire Wire Line
	2950 4050 2850 4050
Wire Wire Line
	2850 4050 2850 4000
$Comp
L SparkFun-Coils:INDUCTOR-0402-3.9NH L1
U 1 1 5DA62FAF
P 2550 4050
F 0 "L1" V 2464 4050 45  0000 C CNN
F 1 "INDUCTOR-0402-3.9NH" V 2358 4050 45  0001 C CNN
F 2 "Inductor_SMD:L_0805_2012Metric" H 2550 4300 20  0001 C CNN
F 3 "" H 2550 4050 50  0001 C CNN
F 4 "NDUC-13457" V 2453 4050 60  0001 C CNN "Field4"
	1    2550 4050
	0    1    1    0   
$EndComp
Wire Wire Line
	2750 4050 2850 4050
Connection ~ 2850 4050
$Comp
L SparkFun-Capacitors:0.1UF-KIT-EZ-50V-20% C1
U 1 1 5DA65A2E
P 2150 4050
F 0 "C1" H 2258 4100 45  0000 L CNN
F 1 "0.1UF-KIT-EZ-50V-20%" H 2258 4111 45  0001 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2150 4300 20  0001 C CNN
F 3 "" H 2150 4050 50  0001 C CNN
F 4 "CAP-08370" H 2258 4016 60  0001 L CNN "Field4"
	1    2150 4050
	0    1    1    0   
$EndComp
$Comp
L SparkFun-GPS:ANTENNAGPS-2X7MM M1
U 1 1 5DA673F3
P 1750 3850
F 0 "M1" H 1878 3842 45  0000 L CNN
F 1 "ANTENNAGPS-2X7MM" H 1878 3853 45  0001 L CNN
F 2 "TestPoint:TestPoint_2Pads_Pitch2.54mm_Drill0.8mm" H 1750 4100 20  0001 C CNN
F 3 "" H 1750 3850 50  0001 C CNN
F 4 "ANT-09087" H 1878 3758 60  0001 L CNN "Field4"
	1    1750 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2050 4050 1750 4050
Wire Wire Line
	6300 4000 6100 4000
Wire Wire Line
	6100 4000 6100 4250
$EndSCHEMATC
