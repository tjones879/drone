EESchema Schematic File Version 4
LIBS:drone-cache
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 3
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L dk_Motion-Sensors-IMUs-Inertial-Measurement-Units:LSM9DS1TR U2
U 1 1 5DAFB04F
P 6000 4000
F 0 "U2" H 5400 4700 60  0000 C CNN
F 1 "LSM9DS1TR" H 5200 4600 60  0000 C CNN
F 2 "digikey-footprints:LGA-24_3x3.5mm_LSM9DS1" H 6200 4200 60  0001 L CNN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/1e/3f/2a/d6/25/eb/48/46/DM00103319.pdf/files/DM00103319.pdf/jcr:content/translations/en.DM00103319.pdf" H 6200 4300 60  0001 L CNN
F 4 "497-14946-1-ND" H 6200 4400 60  0001 L CNN "Digi-Key_PN"
F 5 "LSM9DS1TR" H 6200 4500 60  0001 L CNN "MPN"
F 6 "Sensors, Transducers" H 6200 4600 60  0001 L CNN "Category"
F 7 "Motion Sensors - IMUs (Inertial Measurement Units)" H 6200 4700 60  0001 L CNN "Family"
F 8 "http://www.st.com/content/ccc/resource/technical/document/datasheet/1e/3f/2a/d6/25/eb/48/46/DM00103319.pdf/files/DM00103319.pdf/jcr:content/translations/en.DM00103319.pdf" H 6200 4800 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/stmicroelectronics/LSM9DS1TR/497-14946-1-ND/4988079" H 6200 4900 60  0001 L CNN "DK_Detail_Page"
F 10 "IMU ACCEL/GYRO/MAG I2C/SPI 24LGA" H 6200 5000 60  0001 L CNN "Description"
F 11 "STMicroelectronics" H 6200 5100 60  0001 L CNN "Manufacturer"
F 12 "Active" H 6200 5200 60  0001 L CNN "Status"
	1    6000 4000
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-PowerSymbols:GND #GND0111
U 1 1 5DB010FB
P 6400 4600
F 0 "#GND0111" H 6450 4550 45  0001 L BNN
F 1 "GND" H 6400 4430 45  0000 C CNN
F 2 "" H 6400 4500 60  0001 C CNN
F 3 "" H 6400 4500 60  0001 C CNN
	1    6400 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 4500 5600 4600
Wire Wire Line
	5600 4600 5700 4600
Wire Wire Line
	5700 4500 5700 4600
Connection ~ 5700 4600
Wire Wire Line
	5700 4600 5800 4600
Wire Wire Line
	5800 4500 5800 4600
Connection ~ 5800 4600
Wire Wire Line
	5800 4600 5900 4600
Wire Wire Line
	5900 4500 5900 4600
Connection ~ 5900 4600
Wire Wire Line
	5900 4600 6000 4600
Wire Wire Line
	6000 4500 6000 4600
Connection ~ 6000 4600
Wire Wire Line
	6000 4600 6100 4600
Wire Wire Line
	6100 4500 6100 4600
Connection ~ 6100 4600
Wire Wire Line
	6100 4600 6200 4600
Wire Wire Line
	6200 4500 6200 4600
Connection ~ 6200 4600
Wire Wire Line
	6200 4600 6400 4600
$Comp
L SparkFun-PowerSymbols:GND #GND0112
U 1 1 5DB01A80
P 6750 4600
F 0 "#GND0112" H 6800 4550 45  0001 L BNN
F 1 "GND" H 6750 4430 45  0000 C CNN
F 2 "" H 6750 4500 60  0001 C CNN
F 3 "" H 6750 4500 60  0001 C CNN
	1    6750 4600
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-Capacitors:0.1UF-0603-25V-_+80_-20%_ C12
U 1 1 5DB2F784
P 6750 4500
F 0 "C12" H 6500 4550 45  0000 L CNN
F 1 "10nF" H 6858 4508 45  0001 L CNN
F 2 "0603" H 6750 4750 20  0001 C CNN
F 3 "" H 6750 4500 50  0001 C CNN
F 4 "" H 6858 4466 60  0001 L CNN "Field4"
	1    6750 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 4300 6750 4300
$Comp
L SparkFun-PowerSymbols:GND #GND0113
U 1 1 5DB3622C
P 7050 4600
F 0 "#GND0113" H 7100 4550 45  0001 L BNN
F 1 "GND" H 7050 4430 45  0000 C CNN
F 2 "" H 7050 4500 60  0001 C CNN
F 3 "" H 7050 4500 60  0001 C CNN
	1    7050 4600
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-Capacitors:0.1UF-0603-25V-_+80_-20%_ C13
U 1 1 5DB36233
P 7050 4500
F 0 "C13" H 7158 4550 45  0000 L CNN
F 1 "100nF" H 7158 4508 45  0001 L CNN
F 2 "0603" H 7050 4750 20  0001 C CNN
F 3 "" H 7050 4500 50  0001 C CNN
F 4 "" H 7158 4466 60  0001 L CNN "Field4"
	1    7050 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 4200 7050 4200
Wire Wire Line
	7050 4200 7050 4300
Text HLabel 5050 3600 0    50   Input ~ 0
IMU_MOSI
Text HLabel 5050 3700 0    50   Input ~ 0
IMU_SCK
Text HLabel 5050 3800 0    50   Input ~ 0
IMU_CS
Text HLabel 5050 3900 0    50   Input ~ 0
MAG_CS
Wire Wire Line
	5050 3600 5400 3600
Wire Wire Line
	5050 3700 5400 3700
Wire Wire Line
	5050 3800 5400 3800
Wire Wire Line
	5050 3900 5400 3900
Text HLabel 6950 3600 2    50   Input ~ 0
IMU_MISO
Wire Wire Line
	6600 3600 6850 3600
$Comp
L SparkFun-PowerSymbols:VDD #SUPPLY0102
U 1 1 5DB46A11
P 5800 2800
F 0 "#SUPPLY0102" H 5850 2800 45  0001 L BNN
F 1 "VDD" H 5800 2970 45  0000 C CNN
F 2 "XXX-00000" H 5800 2981 60  0001 C CNN
F 3 "" H 5800 2800 60  0001 C CNN
	1    5800 2800
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-PowerSymbols:VDD #SUPPLY0103
U 1 1 5DB4803D
P 6200 2800
F 0 "#SUPPLY0103" H 6250 2800 45  0001 L BNN
F 1 "VDD" H 6200 2970 45  0000 C CNN
F 2 "XXX-00000" H 6200 2981 60  0001 C CNN
F 3 "" H 6200 2800 60  0001 C CNN
	1    6200 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 2800 5800 3000
$Comp
L SparkFun-PowerSymbols:GND #GND0114
U 1 1 5DB49354
P 5250 3000
F 0 "#GND0114" H 5300 2950 45  0001 L BNN
F 1 "GND" H 5250 2830 45  0000 C CNN
F 2 "" H 5250 2900 60  0001 C CNN
F 3 "" H 5250 2900 60  0001 C CNN
	1    5250 3000
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-Capacitors:0.1UF-0603-25V-_+80_-20%_ C10
U 1 1 5DB4B5CC
P 5650 3000
F 0 "C10" V 5900 3000 45  0000 L CNN
F 1 "100nF" V 5800 2950 45  0000 L CNN
F 2 "0603" H 5650 3250 20  0001 C CNN
F 3 "" H 5650 3000 50  0001 C CNN
F 4 "" H 5758 2966 60  0001 L CNN "Field4"
	1    5650 3000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5450 3000 5250 3000
Wire Wire Line
	5750 3000 5800 3000
Connection ~ 5800 3000
Wire Wire Line
	5800 3000 5800 3200
$Comp
L SparkFun-PowerSymbols:GND #GND0115
U 1 1 5DB5194E
P 6750 3000
F 0 "#GND0115" H 6800 2950 45  0001 L BNN
F 1 "GND" H 6750 2830 45  0000 C CNN
F 2 "" H 6750 2900 60  0001 C CNN
F 3 "" H 6750 2900 60  0001 C CNN
	1    6750 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 3000 6750 3000
Wire Wire Line
	5900 3200 5900 3000
Wire Wire Line
	5900 3000 5800 3000
Wire Wire Line
	6200 2800 6200 3000
Wire Wire Line
	6200 3000 6100 3000
Wire Wire Line
	6100 3000 6100 3200
Wire Wire Line
	6200 3200 6200 3000
Connection ~ 6200 3000
Wire Wire Line
	6200 3000 6250 3000
$Comp
L SparkFun-PowerSymbols:GND #GND0116
U 1 1 5DB5F2FD
P 7250 4100
F 0 "#GND0116" H 7300 4050 45  0001 L BNN
F 1 "GND" H 7250 3930 45  0000 C CNN
F 2 "" H 7250 4000 60  0001 C CNN
F 3 "" H 7250 4000 60  0001 C CNN
	1    7250 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 4100 7250 4100
Wire Wire Line
	6600 4000 7250 4000
Wire Wire Line
	7250 4000 7250 4100
Connection ~ 7250 4100
Wire Wire Line
	6600 3900 7250 3900
Wire Wire Line
	7250 3900 7250 4000
Connection ~ 7250 4000
Wire Wire Line
	6600 3800 7250 3800
Wire Wire Line
	7250 3800 7250 3900
Connection ~ 7250 3900
Wire Wire Line
	6600 3700 6850 3700
Wire Wire Line
	6850 3700 6850 3600
Connection ~ 6850 3600
Wire Wire Line
	6850 3600 6950 3600
NoConn ~ 5400 4000
$Comp
L SparkFun-Capacitors:0.1UF-0603-25V-_+80_-20%_ C11
U 1 1 5DB7C0F9
P 6450 3000
F 0 "C11" V 6700 3000 45  0000 L CNN
F 1 "100nF" V 6600 2950 45  0000 L CNN
F 2 "0603" H 6450 3250 20  0001 C CNN
F 3 "" H 6450 3000 50  0001 C CNN
F 4 "" H 6558 2966 60  0001 L CNN "Field4"
	1    6450 3000
	0    -1   -1   0   
$EndComp
$EndSCHEMATC
