EESchema Schematic File Version 2
LIBS:or-clock_display
EELAYER 25 0
EELAYER END
$Descr A4 8268 11693 portrait
encoding utf-8
Sheet 1 1
Title "or-clock_display.sch"
Date "12 OCT 2015"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MOUNT-PAD-ROUND3.3 H1
U 1 1 561C2247
P 1200 7050
F 0 "H1" H 1310 7072 70  0000 L BNN
F 1 "MOUNT-PAD-ROUND3.3" H 1310 6953 70  0000 L BNN
F 2 "nixkit_display:3_3-PAD" H 1190 6840 70  0001 L TNN
F 3 "" H 1200 7050 60  0001 C CNN
	1    1200 7050
	1    0    0    -1  
$EndComp
$Comp
L MOUNT-PAD-ROUND3.3 H2
U 1 1 561C230F
P 2800 7050
F 0 "H2" H 2910 7072 70  0000 L BNN
F 1 "MOUNT-PAD-ROUND3.3" H 2910 6953 70  0000 L BNN
F 2 "nixkit_display:3_3-PAD" H 2790 6840 70  0001 L TNN
F 3 "" H 2800 7050 60  0001 C CNN
	1    2800 7050
	1    0    0    -1  
$EndComp
$Comp
L MOUNT-PAD-ROUND3.3 H3
U 1 1 561C23D7
P 1200 7650
F 0 "H3" H 1310 7672 70  0000 L BNN
F 1 "MOUNT-PAD-ROUND3.3" H 1310 7553 70  0000 L BNN
F 2 "nixkit_display:3_3-PAD" H 1190 7440 70  0001 L TNN
F 3 "" H 1200 7650 60  0001 C CNN
	1    1200 7650
	1    0    0    -1  
$EndComp
$Comp
L MOUNT-PAD-ROUND3.3 H4
U 1 1 561C249F
P 2800 7650
F 0 "H4" H 2910 7672 70  0000 L BNN
F 1 "MOUNT-PAD-ROUND3.3" H 2910 7553 70  0000 L BNN
F 2 "nixkit_display:3_3-PAD" H 2790 7440 70  0001 L TNN
F 3 "" H 2800 7650 60  0001 C CNN
	1    2800 7650
	1    0    0    -1  
$EndComp
$Comp
L PINHD-2X10 JP1
U 1 1 561C2567
P 2575 2250
F 0 "JP1" H 2326 2775 70  0000 L BNN
F 1 "~" H 2565 2140 70  0001 L TNN
F 2 "nixkit_display:2X10" H 2565 2040 70  0001 L TNN
F 3 "" H 2575 2250 60  0001 C CNN
	1    2575 2250
	1    0    0    -1  
$EndComp
$Comp
L IN-12B N1
U 1 1 561C262F
P 5775 2450
F 0 "N1" H 5601 3275 70  0000 L BNN
F 1 "IN-12B" H 5765 2340 70  0001 L TNN
F 2 "Nixies:in-12" H 5765 2240 70  0001 L TNN
F 3 "" H 5775 2450 60  0001 C CNN
	1    5775 2450
	1    0    0    -1  
$EndComp
$Comp
L IN-12B N2
U 1 1 561C26F7
P 5775 4150
F 0 "N2" H 5601 4975 70  0000 L BNN
F 1 "IN-12B" H 5765 4040 70  0001 L TNN
F 2 "Nixies:in-12" H 5765 3940 70  0001 L TNN
F 3 "" H 5775 4150 60  0001 C CNN
	1    5775 4150
	1    0    0    -1  
$EndComp
$Comp
L IN-12B N3
U 1 1 561C27BF
P 5775 5850
F 0 "N3" H 5601 6675 70  0000 L BNN
F 1 "IN-12B" H 5765 5740 70  0001 L TNN
F 2 "Nixies:in-12" H 5765 5640 70  0001 L TNN
F 3 "" H 5775 5850 60  0001 C CNN
	1    5775 5850
	1    0    0    -1  
$EndComp
$Comp
L IN-12B N4
U 1 1 561C2887
P 5775 7650
F 0 "N4" H 5601 8475 70  0000 L BNN
F 1 "IN-12B" H 5765 7540 70  0001 L TNN
F 2 "Nixies:in-12" H 5765 7440 70  0001 L TNN
F 3 "" H 5775 7650 60  0001 C CNN
	1    5775 7650
	1    0    0    -1  
$EndComp
$Comp
L INS-1 N5
U 1 1 561C294F
P 2375 3950
F 0 "N5" H 2424 4075 70  0000 L BNN
F 1 "INS-1" H 2365 3840 70  0001 L TNN
F 2 "nixkit_display:INS-1" H 2365 3740 70  0001 L TNN
F 3 "" H 2375 3950 60  0001 C CNN
	1    2375 3950
	-1   0    0    1   
$EndComp
$Comp
L INS-1 N6
U 1 1 561C2A17
P 2375 4750
F 0 "N6" H 2424 4875 70  0000 L BNN
F 1 "INS-1" H 2365 4640 70  0001 L TNN
F 2 "nixkit_display:INS-1" H 2365 4540 70  0001 L TNN
F 3 "" H 2375 4750 60  0001 C CNN
	1    2375 4750
	-1   0    0    1   
$EndComp
$Comp
L R-EU_0207_7 R1
U 1 1 561C2ADF
P 6575 2450
F 0 "R1" H 6425 2509 70  0000 L BNN
F 1 "33K" H 6425 2320 70  0000 L BNN
F 2 "nixkit_display:0207_7" H 6565 2240 70  0001 L TNN
F 3 "" H 6575 2450 60  0001 C CNN
	1    6575 2450
	1    0    0    -1  
$EndComp
$Comp
L R-EU_0207_7 R2
U 1 1 561C2BA7
P 6575 4150
F 0 "R2" H 6425 4209 70  0000 L BNN
F 1 "33K" H 6425 4020 70  0000 L BNN
F 2 "nixkit_display:0207_7" H 6565 3940 70  0001 L TNN
F 3 "" H 6575 4150 60  0001 C CNN
	1    6575 4150
	1    0    0    -1  
$EndComp
$Comp
L R-EU_0207_7 R3
U 1 1 561C2C6F
P 6575 5850
F 0 "R3" H 6425 5909 70  0000 L BNN
F 1 "33K" H 6425 5720 70  0000 L BNN
F 2 "nixkit_display:0207_7" H 6565 5640 70  0001 L TNN
F 3 "" H 6575 5850 60  0001 C CNN
	1    6575 5850
	1    0    0    -1  
$EndComp
$Comp
L R-EU_0207_7 R4
U 1 1 561C2D37
P 6575 7650
F 0 "R4" H 6425 7709 70  0000 L BNN
F 1 "33K" H 6425 7520 70  0000 L BNN
F 2 "nixkit_display:0207_7" H 6565 7440 70  0001 L TNN
F 3 "" H 6575 7650 60  0001 C CNN
	1    6575 7650
	1    0    0    -1  
$EndComp
$Comp
L R-EU_0207_7 R5
U 1 1 561C2DFF
P 2775 3850
F 0 "R5" H 2625 3908 70  0000 L BNN
F 1 "1M" H 2625 3720 70  0000 L BNN
F 2 "nixkit_display:0207_7" H 2765 3640 70  0001 L TNN
F 3 "" H 2775 3850 60  0001 C CNN
	1    2775 3850
	-1   0    0    1   
$EndComp
$Comp
L R-EU_0207_7 R6
U 1 1 561C2EC7
P 2775 4650
F 0 "R6" H 2625 4708 70  0000 L BNN
F 1 "1M" H 2625 4520 70  0000 L BNN
F 2 "nixkit_display:0207_7" H 2765 4440 70  0001 L TNN
F 3 "" H 2775 4650 60  0001 C CNN
	1    2775 4650
	-1   0    0    1   
$EndComp
Wire Wire Line
	6775 2450 7075 2450
Wire Wire Line
	2375 2450 1975 2450
Wire Wire Line
	6775 4150 7075 4150
Wire Wire Line
	2875 2450 3175 2450
Wire Wire Line
	6775 5850 7075 5850
Wire Wire Line
	2375 2550 1975 2550
Wire Wire Line
	6775 7650 7075 7650
Wire Wire Line
	2875 2550 3175 2550
Wire Wire Line
	5275 2850 5075 2850
Wire Wire Line
	5275 4550 5075 4550
Wire Wire Line
	5275 6250 5075 6250
Wire Wire Line
	5275 8050 5075 8050
Wire Wire Line
	2875 2250 3175 2250
Wire Wire Line
	5275 1950 5075 1950
Wire Wire Line
	5275 3650 5075 3650
Wire Wire Line
	5275 5350 5075 5350
Wire Wire Line
	5275 7150 5075 7150
Wire Wire Line
	2375 1850 1975 1850
Wire Wire Line
	5275 2050 5075 2050
Wire Wire Line
	5275 3750 5075 3750
Wire Wire Line
	5275 5450 5075 5450
Wire Wire Line
	5275 7250 5075 7250
Wire Wire Line
	2875 1850 3175 1850
Wire Wire Line
	5275 2150 5075 2150
Wire Wire Line
	5275 3850 5075 3850
Wire Wire Line
	5275 5550 5075 5550
Wire Wire Line
	5275 7350 5075 7350
Wire Wire Line
	2375 1950 1975 1950
Wire Wire Line
	5275 2250 5075 2250
Wire Wire Line
	5275 3950 5075 3950
Wire Wire Line
	5275 5650 5075 5650
Wire Wire Line
	5275 7450 5075 7450
Wire Wire Line
	2875 1950 3175 1950
Wire Wire Line
	5275 2350 5075 2350
Wire Wire Line
	5275 4050 5075 4050
Wire Wire Line
	5275 5750 5075 5750
Wire Wire Line
	5275 7550 5075 7550
Wire Wire Line
	2375 2050 1975 2050
Wire Wire Line
	5275 2450 5075 2450
Wire Wire Line
	5275 4150 5075 4150
Wire Wire Line
	5275 5850 5075 5850
Wire Wire Line
	5275 7650 5075 7650
Wire Wire Line
	2875 2050 3175 2050
Wire Wire Line
	5275 2550 5075 2550
Wire Wire Line
	5275 4250 5075 4250
Wire Wire Line
	5275 5950 5075 5950
Wire Wire Line
	5275 7750 5075 7750
Wire Wire Line
	2375 2150 1975 2150
Wire Wire Line
	5275 2650 5075 2650
Wire Wire Line
	5275 4350 5075 4350
Wire Wire Line
	5275 6050 5075 6050
Wire Wire Line
	5275 7850 5075 7850
Wire Wire Line
	2875 2150 3175 2150
Wire Wire Line
	5275 2750 5075 2750
Wire Wire Line
	5275 4450 5075 4450
Wire Wire Line
	5275 6150 5075 6150
Wire Wire Line
	5275 7950 5075 7950
Wire Wire Line
	2375 2250 1975 2250
Wire Wire Line
	6175 1950 6375 1950
Wire Wire Line
	6175 3650 6375 3650
Wire Wire Line
	6175 5350 6375 5350
Wire Wire Line
	6175 7150 6375 7150
Wire Wire Line
	2375 2350 1975 2350
Wire Wire Line
	6175 2450 6375 2450
Wire Wire Line
	6175 4150 6375 4150
Wire Wire Line
	6175 5850 6375 5850
Wire Wire Line
	6175 7650 6375 7650
Wire Wire Line
	2475 3850 2575 3850
Wire Wire Line
	2575 4650 2475 4650
Wire Wire Line
	2975 3850 3275 3850
Wire Wire Line
	3275 3850 3275 4650
Wire Wire Line
	3275 4650 2975 4650
Wire Wire Line
	3275 4250 3475 4250
Connection ~ 3275 4250
Wire Wire Line
	2375 2750 1975 2750
Wire Wire Line
	1875 3850 1575 3850
Wire Wire Line
	1575 3850 1575 4650
Wire Wire Line
	1575 4650 1875 4650
Wire Wire Line
	1575 4250 1375 4250
Connection ~ 1575 4250
Wire Wire Line
	2875 2750 3175 2750
Text Label 5275 4550 2    20   ~ 0
D0
Text Label 5275 3650 2    20   ~ 0
D1
Text Label 5275 3750 2    20   ~ 0
D2
Text Label 5275 3850 2    20   ~ 0
D3
Text Label 5275 3950 2    20   ~ 0
D4
Text Label 5275 4050 2    20   ~ 0
D5
Text Label 5275 4150 2    20   ~ 0
D6
Text Label 5275 4250 2    20   ~ 0
D7
Text Label 5275 4350 2    20   ~ 0
D8
Text Label 5275 4450 2    20   ~ 0
D9
Text Label 6175 3650 0    20   ~ 0
DP
Text GLabel 3175 1850 2    40   Input ~ 0
D2
Text GLabel 3175 1950 2    40   Input ~ 0
D4
Text GLabel 3175 2050 2    40   Input ~ 0
D6
Text GLabel 3175 2150 2    40   Input ~ 0
D8
Text GLabel 3175 2250 2    40   Input ~ 0
D0
Text GLabel 3175 2450 2    40   Input ~ 0
A2
Text GLabel 3175 2550 2    40   Input ~ 0
A4
Text GLabel 3175 2750 2    40   Input ~ 0
SEP_KATHODES
Text GLabel 1975 2750 0    40   Input ~ 0
SEP_ANODES
Text GLabel 1975 2550 0    40   Input ~ 0
A3
Text GLabel 1975 2450 0    40   Input ~ 0
A1
Text GLabel 1975 2350 0    40   Input ~ 0
DP
Text GLabel 1975 2250 0    40   Input ~ 0
D9
Text GLabel 1975 2150 0    40   Input ~ 0
D7
Text GLabel 1975 2050 0    40   Input ~ 0
D5
Text GLabel 1975 1950 0    40   Input ~ 0
D3
Text GLabel 1975 1850 0    40   Input ~ 0
D1
Text GLabel 3475 4250 2    40   Input ~ 0
SEP_ANODES
Text GLabel 1375 4250 0    40   Input ~ 0
SEP_KATHODES
Text GLabel 6375 1950 2    40   Input ~ 0
DP
Text GLabel 6375 3650 2    40   Input ~ 0
DP
Text GLabel 6375 5350 2    40   Input ~ 0
DP
Text GLabel 6375 7150 2    40   Input ~ 0
DP
Text GLabel 5075 1950 0    40   Input ~ 0
D1
Text GLabel 5075 3650 0    40   Input ~ 0
D1
Text GLabel 7075 2450 2    40   Input ~ 0
A1
Text GLabel 7075 4150 2    40   Input ~ 0
A2
Text GLabel 7075 5850 2    40   Input ~ 0
A3
Text GLabel 7075 7650 2    40   Input ~ 0
A4
Text GLabel 5075 2050 0    40   Input ~ 0
D2
Text GLabel 5075 3750 0    40   Input ~ 0
D2
Text GLabel 5075 2150 0    40   Input ~ 0
D3
Text GLabel 5075 3850 0    40   Input ~ 0
D3
Text GLabel 5075 2250 0    40   Input ~ 0
D4
Text GLabel 5075 3950 0    40   Input ~ 0
D4
Text GLabel 5075 2350 0    40   Input ~ 0
D5
Text GLabel 5075 4050 0    40   Input ~ 0
D5
Text GLabel 5075 2450 0    40   Input ~ 0
D6
Text GLabel 5075 4150 0    40   Input ~ 0
D6
Text GLabel 5075 2550 0    40   Input ~ 0
D7
Text GLabel 5075 4250 0    40   Input ~ 0
D7
Text GLabel 5075 2650 0    40   Input ~ 0
D8
Text GLabel 5075 2750 0    40   Input ~ 0
D9
Text GLabel 5075 2850 0    40   Input ~ 0
D0
Text GLabel 5075 4350 0    40   Input ~ 0
D8
Text GLabel 5075 4450 0    40   Input ~ 0
D9
Text GLabel 5075 4550 0    40   Input ~ 0
D0
Text GLabel 5075 5350 0    40   Input ~ 0
D1
Text GLabel 5075 5450 0    40   Input ~ 0
D2
Text GLabel 5075 5550 0    40   Input ~ 0
D3
Text GLabel 5075 5650 0    40   Input ~ 0
D4
Text GLabel 5075 5750 0    40   Input ~ 0
D5
Text GLabel 5075 5850 0    40   Input ~ 0
D6
Text GLabel 5075 5950 0    40   Input ~ 0
D7
Text GLabel 5075 6050 0    40   Input ~ 0
D8
Text GLabel 5075 6150 0    40   Input ~ 0
D9
Text GLabel 5075 6250 0    40   Input ~ 0
D0
Text GLabel 5075 7150 0    40   Input ~ 0
D1
Text GLabel 5075 7250 0    40   Input ~ 0
D2
Text GLabel 5075 7350 0    40   Input ~ 0
D3
Text GLabel 5075 7450 0    40   Input ~ 0
D4
Text GLabel 5075 7550 0    40   Input ~ 0
D5
Text GLabel 5075 7650 0    40   Input ~ 0
D6
Text GLabel 5075 7750 0    40   Input ~ 0
D7
Text GLabel 5075 7850 0    40   Input ~ 0
D8
Text GLabel 5075 7950 0    40   Input ~ 0
D9
Text GLabel 5075 8050 0    40   Input ~ 0
D0
$EndSCHEMATC
