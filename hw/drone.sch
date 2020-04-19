EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 4
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Sheet
S 6500 700  1400 1650
U 5D969FF0
F0 "RF" 50
F1 "RF.sch" 50
F2 "RF_SCK" I L 6500 900 50 
F3 "RF_CS" I L 6500 1050 50 
F4 "RF_MISO" I L 6500 1200 50 
F5 "RF_MOSI" I L 6500 1350 50 
$EndSheet
$Sheet
S 6500 2650 1450 1600
U 5DAFA187
F0 "IMU" 50
F1 "IMU.sch" 50
F2 "IMU_MOSI" I L 6500 2900 50 
F3 "IMU_SCK" I L 6500 3100 50 
F4 "IMU_CS" I L 6500 3300 50 
F5 "MAG_CS" I L 6500 3450 50 
F6 "IMU_MISO" I L 6500 3600 50 
$EndSheet
$Comp
L SparkFun-Connectors:CONN_20 J1
U 1 1 5DBE5143
P 4050 2850
F 0 "J1" H 4008 4954 45  0000 C CNN
F 1 "CONN_20" H 4008 4870 45  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x20_P2.54mm_Vertical" H 4050 4950 20  0001 C CNN
F 3 "" H 4050 2850 50  0001 C CNN
F 4 "XXX-00000" H 4008 4881 60  0001 C CNN "Field4"
	1    4050 2850
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-Connectors:CONN_20 J2
U 1 1 5DBE932A
P 4050 5150
F 0 "J2" H 4008 7254 45  0000 C CNN
F 1 "CONN_20" H 4008 7170 45  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x20_P2.54mm_Vertical" H 4050 7250 20  0001 C CNN
F 3 "" H 4050 5150 50  0001 C CNN
F 4 "XXX-00000" H 4008 7181 60  0001 C CNN "Field4"
	1    4050 5150
	1    0    0    -1  
$EndComp
Text Label 4150 2850 0    50   ~ 0
G
Text Label 4150 2750 0    50   ~ 0
G
Text Label 4150 2650 0    50   ~ 0
3.3
Text Label 4150 2550 0    50   ~ 0
R
Text Label 4150 2450 0    50   ~ 0
B11
Text Label 4150 2350 0    50   ~ 0
B10
Text Label 4150 2250 0    50   ~ 0
B1
Text Label 4150 2150 0    50   ~ 0
B0
Text Label 4150 2050 0    50   ~ 0
A7
Text Label 4150 1950 0    50   ~ 0
A6
Text Label 4150 1850 0    50   ~ 0
A5
Text Label 4150 1750 0    50   ~ 0
A4
Text Label 4150 1650 0    50   ~ 0
A3
Text Label 4150 1550 0    50   ~ 0
A2
Text Label 4150 1450 0    50   ~ 0
A1
Text Label 4150 1350 0    50   ~ 0
A0
Text Label 4150 1250 0    50   ~ 0
C15
Text Label 4150 1150 0    50   ~ 0
C14
Text Label 4150 1050 0    50   ~ 0
C13
Text Label 4150 950  0    50   ~ 0
VB
Text Label 4150 3250 0    50   ~ 0
3.3
Text Label 4150 3350 0    50   ~ 0
G
Text Label 4150 3450 0    50   ~ 0
5V
Text Label 4150 3550 0    50   ~ 0
B9
Text Label 4150 3650 0    50   ~ 0
B8
Text Label 4150 3750 0    50   ~ 0
B7
Text Label 4150 3850 0    50   ~ 0
B6
Text Label 4150 3950 0    50   ~ 0
B5
Text Label 4150 4050 0    50   ~ 0
B4
Text Label 4150 4150 0    50   ~ 0
B3
Text Label 4150 4250 0    50   ~ 0
A15
Text Label 4150 4350 0    50   ~ 0
A12
Text Label 4150 4450 0    50   ~ 0
A11
Text Label 4150 4550 0    50   ~ 0
A10
Text Label 4150 4650 0    50   ~ 0
A9
Text Label 4150 4750 0    50   ~ 0
A8
Text Label 4150 4850 0    50   ~ 0
B15
Text Label 4150 4950 0    50   ~ 0
B14
Text Label 4150 5050 0    50   ~ 0
B13
Text Label 4150 5150 0    50   ~ 0
B12
Text Label 6350 2900 2    50   ~ 0
A7
Wire Wire Line
	6500 2900 6350 2900
Text Label 6350 3600 2    50   ~ 0
A6
Text Label 6350 3100 2    50   ~ 0
A5
Wire Wire Line
	6350 3100 6500 3100
Wire Wire Line
	6350 3600 6500 3600
Text Label 6350 3300 2    50   ~ 0
A3
Text Label 6350 3450 2    50   ~ 0
A2
Wire Wire Line
	6350 3300 6500 3300
Wire Wire Line
	6350 3450 6500 3450
$Sheet
S 6500 4600 1350 1100
U 5E9C3A8B
F0 "uSD" 50
F1 "uSD.sch" 50
F2 "uSD_SCK" I L 6500 4950 50 
F3 "uSD_CS" I L 6500 5100 50 
F4 "uSD_MOSI" I L 6500 4800 50 
F5 "uSD_MISO" I L 6500 5250 50 
$EndSheet
$EndSCHEMATC
