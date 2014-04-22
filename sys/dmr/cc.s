0000: f009           setd
0002: 1180           mov sp, r0
0004: 1226           mov (r0), -(sp)
0006: 0bd0           tst (r0)+
0008: 1036 0002      mov r0, 2(sp)
000c: 09f7 0008      jsr pc, 0018
0010: 100e           mov r0, (sp)
0012: 09df 18c6      jsr pc, *$18c6
0016: 8901           sys 0001
0018: 0977 1920      jsr r5, 193c
001c: e5c6 0010      sub $0010, sp
0020: 0a00           clr r0
0022: 1035 ffea      mov r0, -16(r5)
0026: 1035 ffec      mov r0, -14(r5)
002a: 1035 fff4      mov r0, -c(r5)
002e: 1035 fff6      mov r0, -a(r5)
0032: 1035 fff2      mov r0, -e(r5)
0036: 0ab5 fff2      inc -e(r5)
003a: 2d75 0004 fff2 cmp 4(r5), -e(r5)
0040: 0602           bgt
0042: 005f 01b6      jmp *$01b6
0046: 1d40 fff2      mov -e(r5), r0
004a: 0cc0           asl r0
004c: 6d40 0006      add 6(r5), r0
0050: 1200           mov (r0), r0
0052: a5c8 002d      cmpb $002d, (r0)
0056: 0302           beq
0058: 005f 0140      jmp *$0140
005c: 1d40 fff2      mov -e(r5), r0
0060: 0cc0           asl r0
0062: 6d40 0006      add 6(r5), r0
0066: 1200           mov (r0), r0
0068: 9c00 0001      movb 1(r0), r0
006c: 015b           br
006e: 0168           br
0070: 0ab7 2928      inc 299c
0074: 0ab7 2926      inc 299e
0078: 0162           br
007a: 0ab7 2922      inc 29a0
007e: 015f           br
0080: 0ab7 291e      inc 29a2
0084: 15f7 19d6 18e6 mov $19d6, 1970
008a: 0159           br
008c: 0ab7 290a      inc 299a
0090: 0ab7 290a      inc 299e
0094: 0154           br
0096: 15f7 19e3 18d4 mov $19e3, 1970
009c: 15f7 19f0 18c8 mov $19f0, 196a
00a2: 15f7 19f9 18c4 mov $19f9, 196c
00a8: 014a           br
00aa: 1d40 fff2      mov -e(r5), r0
00ae: 0cc0           asl r0
00b0: 6d40 0006      add 6(r5), r0
00b4: 1200           mov (r0), r0
00b6: 8bf0 0002      tstb 2(r0)
00ba: 0204           bne
00bc: 15f7 1a02 18ae mov $1a02, 1970
00c2: 0106           br
00c4: 15f7 1a0e 18a6 mov $1a0e, 1970
00ca: 15f5 0001 ffec mov $0001, -14(r5)
00d0: 0136           br
00d2: 1d40 fff2      mov -e(r5), r0
00d6: 0cc0           asl r0
00d8: 6d40 0006      add 6(r5), r0
00dc: 1200           mov (r0), r0
00de: a5f0 0030 0002 cmpb $0030, 2(r0)
00e4: 0203           bne
00e6: 15f7 1a1b 187e mov $1a1b, 196a
00ec: 1d40 fff2      mov -e(r5), r0
00f0: 0cc0           asl r0
00f2: 6d40 0006      add 6(r5), r0
00f6: 1200           mov (r0), r0
00f8: a5f0 0031 0002 cmpb $0031, 2(r0)
00fe: 0203           bne
0100: 15f7 1a25 1866 mov $1a25, 196c
0106: 1d40 fff2      mov -e(r5), r0
010a: 0cc0           asl r0
010c: 6d40 0006      add 6(r5), r0
0110: 1200           mov (r0), r0
0112: a5f0 0032 0002 cmpb $0032, 2(r0)
0118: 0203           bne
011a: 15f7 1a2f 184e mov $1a2f, 196e
0120: 010e           br
0122: 010d           br
0124: 1001           mov r0, r1
0126: 0a00           clr r0
0128: 7217 0002      div r0, $0002
012c: 0cc1           asl r1
012e: 65c1 1972      add $1972, r1
0132: 1019           mov r0, *(r1)+
0134: 1441           mov (r1)+, r1
0136: 2021           cmp r0, -(r1)
0138: 02fe           bne
013a: 0079 0014      jmp *14(r1)
013e: 0139           br
0140: 1d40 fff2      mov -e(r5), r0
0144: 0cc0           asl r0
0146: 6d40 0006      add 6(r5), r0
014a: 1235 fff8      mov (r0), -8(r5)
014e: 1d4e fff8      mov -8(r5), (sp)
0152: 09df 0d9e      jsr pc, *$0d9e
0156: 25c0 0063      cmp $0063, r0
015a: 0211           bne
015c: 1d40 fff6      mov -a(r5), r0
0160: 0cc0           asl r0
0162: 0ab5 fff6      inc -a(r5)
0166: 1d70 fff8 28d0 mov -8(r5), 28d0(r0)
016c: 15ce 006f      mov $006f, (sp)
0170: 1d66 fff8      mov -8(r5), -(sp)
0174: 09df 0ddc      jsr pc, *$0ddc
0178: 0bd6           tst (sp)+
017a: 1035 fff8      mov r0, -8(r5)
017e: 1d4e fff8      mov -8(r5), (sp)
0182: 15e6 2934      mov $2934, -(sp)
0186: 09df 0ecc      jsr pc, *$0ecc
018a: 0bd6           tst (sp)+
018c: 0bc0           tst r0
018e: 0311           beq
0190: 1d40 fff4      mov -c(r5), r0
0194: 0cc0           asl r0
0196: 0ab5 fff4      inc -c(r5)
019a: 1d70 fff8 2934 mov -8(r5), 2934(r0)
01a0: 1d4e fff8      mov -8(r5), (sp)
01a4: 09df 0d9e      jsr pc, *$0d9e
01a8: 25c0 006f      cmp $006f, r0
01ac: 0202           bne
01ae: 0ab5 ffea      inc -16(r5)
01b2: 005f 0036      jmp *$0036
01b6: 0bf5 fff6      tst -a(r5)
01ba: 0202           bne
01bc: 005f 0484      jmp *$0484
01c0: 0bf7 27d6      tst 299a
01c4: 0226           bne
01c6: 15ce 1a39      mov $1a39, (sp)
01ca: 09df 0eaa      jsr pc, *$0eaa
01ce: 1037 22a6      mov r0, 2478
01d2: 0a0e           clr (sp)
01d4: 1de6 22a0      mov 2478, -(sp)
01d8: 09df 169c      jsr pc, *$169c
01dc: 0bd6           tst (sp)+
01de: 1035 ffee      mov r0, -12(r5)
01e2: 0509           blt
01e4: 1d4e ffee      mov -12(r5), (sp)
01e8: 09df 1560      jsr pc, *$1560
01ec: 1dc0 2288      mov 2478, r0
01f0: 8ab0 0009      incb 9(r0)
01f4: 01ee           br
01f6: 15ce 0100      mov $0100, (sp)
01fa: 1de6 227a      mov 2478, -(sp)
01fe: 09df 1576      jsr pc, *$1576
0202: 0bd6           tst (sp)+
0204: 0bc0           tst r0
0206: 0405           bge
0208: 1dc0 226c      mov 2478, r0
020c: 8ab0 0009      incb 9(r0)
0210: 01f2           br
0212: 15ce 0001      mov $0001, (sp)
0216: 15e6 0002      mov $0002, -(sp)
021a: 09df 177e      jsr pc, *$177e
021e: 0bd6           tst (sp)+
0220: 35c0 0001      bit $0001, r0
0224: 0207           bne
0226: 15ce 0550      mov $0550, (sp)
022a: 15e6 0002      mov $0002, -(sp)
022e: 09df 177e      jsr pc, *$177e
0232: 0bd6           tst (sp)+
0234: 1dce 2240      mov 2478, (sp)
0238: 09df 0eaa      jsr pc, *$0eaa
023c: 1037 223a      mov r0, 247a
0240: 95f0 0031 0008 movb $0031, 8(r0)
0246: 1dce 222e      mov 2478, (sp)
024a: 09df 0eaa      jsr pc, *$0eaa
024e: 1037 222a      mov r0, 247c
0252: 95f0 0032 0008 movb $0032, 8(r0)
0258: 1dce 221c      mov 2478, (sp)
025c: 09df 0eaa      jsr pc, *$0eaa
0260: 1037 221a      mov r0, 247e
0264: 95f0 0033 0008 movb $0033, 8(r0)
026a: 0bf7 2732      tst 29a0
026e: 0309           beq
0270: 1dce 2204      mov 2478, (sp)
0274: 09df 0eaa      jsr pc, *$0eaa
0278: 1037 2206      mov r0, 2482
027c: 95f0 0035 0008 movb $0035, 8(r0)
0282: 0bf7 2714      tst 299a
0286: 0209           bne
0288: 1dce 21ec      mov 2478, (sp)
028c: 09df 0eaa      jsr pc, *$0eaa
0290: 1037 21ec      mov r0, 2480
0294: 95f0 0034 0008 movb $0034, 8(r0)
029a: 0a35 fff2      clr -e(r5)
029e: 2d75 fff6 fff2 cmp -a(r5), -e(r5)
02a4: 0602           bgt
02a6: 005f 0484      jmp *$0484
02aa: 25f5 0001 fff6 cmp $0001, -a(r5)
02b0: 040a           bge
02b2: 1d40 fff2      mov -e(r5), r0
02b6: 0cc0           asl r0
02b8: 1c0e 28d0      mov 28d0(r0), (sp)
02bc: 15e6 1a44      mov $1a44, -(sp)
02c0: 09df 133e      jsr pc, *$133e
02c4: 0bd6           tst (sp)+
02c6: 15f7 1a49 25a0 mov $1a49, 286c
02cc: 0bf7 26ca      tst 299a
02d0: 030c           beq
02d2: 15ce 0069      mov $0069, (sp)
02d6: 1d40 fff2      mov -e(r5), r0
02da: 0cc0           asl r0
02dc: 1c26 28d0      mov 28d0(r0), -(sp)
02e0: 09df 0ddc      jsr pc, *$0ddc
02e4: 0bd6           tst (sp)+
02e6: 1037 2196      mov r0, 2480
02ea: 1d40 fff2      mov -e(r5), r0
02ee: 0cc0           asl r0
02f0: 1c0e 28d0      mov 28d0(r0), (sp)
02f4: 09df 0598      jsr pc, *$0598
02f8: 1037 2572      mov r0, 286e
02fc: 0bf7 269a      tst 299a
0300: 0302           beq
0302: 005f 047c      jmp *$047c
0306: 0bf7 26aa      tst 29b4
030a: 0302           beq
030c: 005f 047c      jmp *$047c
0310: 0bf7 255a      tst 286e
0314: 0204           bne
0316: 0ab7 2684      inc 299e
031a: 005f 047c      jmp *$047c
031e: 1df7 2158 254c mov 247a, 2870
0324: 1df7 2154 2548 mov 247c, 2872
032a: 0bf7 2674      tst 29a2
032e: 0306           beq
0330: 15f7 1a4c 253e mov $1a4c, 2874
0336: 0a37 253c      clr 2876
033a: 0102           br
033c: 0a37 2534      clr 2874
0340: 15ce 286c      mov $286c, (sp)
0344: 1de6 1622      mov 196a, -(sp)
0348: 09df 0e08      jsr pc, *$0e08
034c: 0bd6           tst (sp)+
034e: 0bc0           tst r0
0350: 0304           beq
0352: 0ab7 2648      inc 299e
0356: 005f 047c      jmp *$047c
035a: 15f7 1a4f 250c mov $1a4f, 286c
0360: 1df7 2116 2508 mov 247a, 286e
0366: 1df7 2112 2504 mov 247c, 2870
036c: 0bf7 262c      tst 299c
0370: 030c           beq
0372: 15ce 0073      mov $0073, (sp)
0376: 1d40 fff2      mov -e(r5), r0
037a: 0cc0           asl r0
037c: 1c26 28d0      mov 28d0(r0), -(sp)
0380: 09df 0ddc      jsr pc, *$0ddc
0384: 0bd6           tst (sp)+
0386: 1037 20f4      mov r0, 247e
038a: 1df7 20f0 24e2 mov 247e, 2872
0390: 0bf7 260c      tst 29a0
0394: 0303           beq
0396: 1df7 20e8 24d6 mov 2482, 2872
039c: 0a37 24d4      clr 2874
03a0: 15ce 286c      mov $286c, (sp)
03a4: 1de6 15c4      mov 196c, -(sp)
03a8: 09df 0e08      jsr pc, *$0e08
03ac: 0bd6           tst (sp)+
03ae: 0bc0           tst r0
03b0: 0303           beq
03b2: 0ab7 25e8      inc 299e
03b6: 0162           br
03b8: 0bf7 25e4      tst 29a0
03bc: 0316           beq
03be: 15f7 1a52 24a8 mov $1a52, 286c
03c4: 1df7 20ba 24a4 mov 2482, 286e
03ca: 1df7 20b0 24a0 mov 247e, 2870
03d0: 0a37 249e      clr 2872
03d4: 15ce 286c      mov $286c, (sp)
03d8: 1de6 1592      mov 196e, -(sp)
03dc: 09df 0e08      jsr pc, *$0e08
03e0: 0bd6           tst (sp)+
03e2: 1dce 209c      mov 2482, (sp)
03e6: 09df 188c      jsr pc, *$188c
03ea: 0bf7 25ae      tst 299c
03ee: 0246           bne
03f0: 15f7 1a55 2476 mov $1a55, 286c
03f6: 15f7 1a58 2472 mov $1a58, 286e
03fc: 1df7 207e 246e mov 247e, 2870
0402: 0a37 246c      clr 2872
0406: 1dce 2070      mov 247a, (sp)
040a: 09df 0f1c      jsr pc, *$0f1c
040e: 1dce 206a      mov 247c, (sp)
0412: 09df 0f1c      jsr pc, *$0f1c
0416: 1dce 2066      mov 2480, (sp)
041a: 09df 0f1c      jsr pc, *$0f1c
041e: 15ce 286c      mov $286c, (sp)
0422: 15e6 1a5a      mov $1a5a, -(sp)
0426: 09df 0e08      jsr pc, *$0e08
042a: 0bd6           tst (sp)+
042c: 15ce 006f      mov $006f, (sp)
0430: 1d40 fff2      mov -e(r5), r0
0434: 0cc0           asl r0
0436: 1c26 28d0      mov 28d0(r0), -(sp)
043a: 09df 0ddc      jsr pc, *$0ddc
043e: 0bd6           tst (sp)+
0440: 1035 fff8      mov r0, -8(r5)
0444: 1d4e fff8      mov -8(r5), (sp)
0448: 09df 0f1c      jsr pc, *$0f1c
044c: 1d4e fff8      mov -8(r5), (sp)
0450: 15e6 1a62      mov $1a62, -(sp)
0454: 09df 167c      jsr pc, *$167c
0458: 0bd6           tst (sp)+
045a: 0bc0           tst r0
045c: 0206           bne
045e: 15ce 1a68      mov $1a68, (sp)
0462: 09df 0f1c      jsr pc, *$0f1c
0466: 0bc0           tst r0
0468: 0309           beq
046a: 1d4e fff8      mov -8(r5), (sp)
046e: 15e6 1a6e      mov $1a6e, -(sp)
0472: 09df 133e      jsr pc, *$133e
0476: 0bd6           tst (sp)+
0478: 0ab7 2522      inc 299e
047c: 0ab5 fff2      inc -e(r5)
0480: 005f 029e      jmp *$029e
0484: 0bf7 2516      tst 299e
0488: 025f           bne
048a: 0bf5 fff4      tst -c(r5)
048e: 035c           beq
0490: 0a35 fff2      clr -e(r5)
0494: 15f7 1a7f 23d2 mov $1a7f, 286c
049a: 15f7 1a82 23ce mov $1a82, 286e
04a0: 1df7 14cc 23ca mov 1970, 2870
04a6: 15f5 0003 fff0 mov $0003, -10(r5)
04ac: 2d75 fff4 fff2 cmp -c(r5), -e(r5)
04b2: 070e           ble
04b4: 1d40 fff0      mov -10(r5), r0
04b8: 0cc0           asl r0
04ba: 0ab5 fff0      inc -10(r5)
04be: 1d41 fff2      mov -e(r5), r1
04c2: 0cc1           asl r1
04c4: 0ab5 fff2      inc -e(r5)
04c8: 1c70 2934 286c mov 2934(r1), 286c(r0)
04ce: 01ee           br
04d0: 0bf5 ffec      tst -14(r5)
04d4: 0309           beq
04d6: 1d40 fff0      mov -10(r5), r0
04da: 0cc0           asl r0
04dc: 0ab5 fff0      inc -10(r5)
04e0: 15f0 1a85 286c mov $1a85, 286c(r0)
04e6: 0110           br
04e8: 1d40 fff0      mov -10(r5), r0
04ec: 0cc0           asl r0
04ee: 0ab5 fff0      inc -10(r5)
04f2: 15f0 1a89 286c mov $1a89, 286c(r0)
04f8: 1d40 fff0      mov -10(r5), r0
04fc: 0cc0           asl r0
04fe: 0ab5 fff0      inc -10(r5)
0502: 15f0 1a8d 286c mov $1a8d, 286c(r0)
0508: 1d40 fff0      mov -10(r5), r0
050c: 0cc0           asl r0
050e: 0ab5 fff0      inc -10(r5)
0512: 0a30 286c      clr 286c(r0)
0516: 15ce 286c      mov $286c, (sp)
051a: 15e6 1a90      mov $1a90, -(sp)
051e: 09df 0e08      jsr pc, *$0e08
0522: 0bd6           tst (sp)+
0524: 25f5 0001 fff6 cmp $0001, -a(r5)
052a: 020e           bne
052c: 25f5 0001 ffea cmp $0001, -16(r5)
0532: 020a           bne
0534: 15ce 006f      mov $006f, (sp)
0538: 1de6 2394      mov 28d0, -(sp)
053c: 09df 0ddc      jsr pc, *$0ddc
0540: 0bd6           tst (sp)+
0542: 100e           mov r0, (sp)
0544: 09df 0f1c      jsr pc, *$0f1c
0548: 09f7 0004      jsr pc, 0550
054c: 0077 13fa      jmp 194a
0550: 0977 13e8      jsr r5, 193c
0554: 0bf7 2442      tst 299a
0558: 021b           bne
055a: 1dce 1f1c      mov 247a, (sp)
055e: 09df 0f1c      jsr pc, *$0f1c
0562: 1dce 1f16      mov 247c, (sp)
0566: 09df 0f1c      jsr pc, *$0f1c
056a: 0bf7 242e      tst 299c
056e: 0204           bne
0570: 1dce 1f0a      mov 247e, (sp)
0574: 09df 0f1c      jsr pc, *$0f1c
0578: 1dce 1f04      mov 2480, (sp)
057c: 09df 0f1c      jsr pc, *$0f1c
0580: 1dce 1efe      mov 2482, (sp)
0584: 09df 0f1c      jsr pc, *$0f1c
0588: 1dce 1eec      mov 2478, (sp)
058c: 09df 0f1c      jsr pc, *$0f1c
0590: 09f7 1332      jsr pc, 18c6
0594: 0077 13b2      jmp 194a
0598: 0977 13a0      jsr r5, 193c
059c: e5c6 0ea6      sub $0ea6, sp
05a0: 0a37 2410      clr 29b4
05a4: 1140           mov r5, r0
05a6: 65c0 fdf4      add $fdf4, r0
05aa: 1037 23fa      mov r0, 29a8
05ae: 1037 23f4      mov r0, 29a6
05b2: 1140           mov r5, r0
05b4: 65c0 fbee      add $fbee, r0
05b8: 1037 23ee      mov r0, 29aa
05bc: 1dce 23e8      mov 29a8, (sp)
05c0: 1d66 0004      mov 4(r5), -(sp)
05c4: 09df 15d4      jsr pc, *$15d4
05c8: 0bd6           tst (sp)+
05ca: 0bc0           tst r0
05cc: 0404           bge
05ce: 1d40 0004      mov 4(r5), r0
05d2: 005f 075c      jmp *$075c
05d6: 1dce 23ce      mov 29a8, (sp)
05da: 09df 1638      jsr pc, *$1638
05de: 25c0 0023      cmp $0023, r0
05e2: 0308           beq
05e4: 1fce 23c0      mov *29a8, (sp)
05e8: 09df 1560      jsr pc, *$1560
05ec: 1d40 0004      mov 4(r5), r0
05f0: 005f 075c      jmp *$075c
05f4: 1dc0 23b0      mov 29a8, r0
05f8: 0ab0 0002      inc 2(r0)
05fc: 1dc0 23a8      mov 29a8, r0
0600: 0af0 0004      dec 4(r0)
0604: 1140           mov r5, r0
0606: 65c0 f9e8      add $f9e8, r0
060a: 1037 239e      mov r0, 29ac
060e: 1140           mov r5, r0
0610: 65c0 f218      add $f218, r0
0614: 1037 239e      mov r0, 29b6
0618: 0a04           clr r4
061a: 25c4 00c8      cmp $00c8, r4
061e: 070e           ble
0620: 1101           mov r4, r1
0622: 7057 000a      mul r1, $000a
0626: 6141           add r5, r1
0628: 8a31 f218      clrb -de8(r1)
062c: 1101           mov r4, r1
062e: 7057 000a      mul r1, $000a
0632: 6141           add r5, r1
0634: 0a31 f220      clr -de0(r1)
0638: 0a84           inc r4
063a: 01ef           br
063c: 15ce 1a98      mov $1a98, (sp)
0640: 15e6 29b8      mov $29b8, -(sp)
0644: 09df 0a44      jsr pc, *$0a44
0648: 0bd6           tst (sp)+
064a: 15ce 1a9f      mov $1a9f, (sp)
064e: 15e6 29ba      mov $29ba, -(sp)
0652: 09df 0a44      jsr pc, *$0a44
0656: 0bd6           tst (sp)+
0658: 15ce 1aa7      mov $1aa7, (sp)
065c: 15e6 29bc      mov $29bc, -(sp)
0660: 09df 0a44      jsr pc, *$0a44
0664: 0bd6           tst (sp)+
0666: 15ce 1aad      mov $1aad, (sp)
066a: 15e6 29be      mov $29be, -(sp)
066e: 09df 0a44      jsr pc, *$0a44
0672: 0bd6           tst (sp)+
0674: 15ce 1ab3      mov $1ab3, (sp)
0678: 15e6 29c0      mov $29c0, -(sp)
067c: 09df 0a44      jsr pc, *$0a44
0680: 0bd6           tst (sp)+
0682: 15ce 1aba      mov $1aba, (sp)
0686: 15e6 29c2      mov $29c2, -(sp)
068a: 09df 0a44      jsr pc, *$0a44
068e: 0bd6           tst (sp)+
0690: 15f7 1ca8 2332 mov $1ca8, 29c8
0696: 0a37 232a      clr 29c4
069a: 0a37 2328      clr 29c6
069e: 1140           mov r5, r0
06a0: 65c0 f154      add $f154, r0
06a4: 1037 2308      mov r0, 29b0
06a8: 0a37 2306      clr 29b2
06ac: 1dce 22fc      mov 29ac, (sp)
06b0: 1de6 1dcc      mov 2480, -(sp)
06b4: 09df 16ba      jsr pc, *$16ba
06b8: 0bd6           tst (sp)+
06ba: 0bc0           tst r0
06bc: 0409           bge
06be: 1dce 1dbe      mov 2480, (sp)
06c2: 15e6 1abf      mov $1abf, -(sp)
06c6: 09df 133e      jsr pc, *$133e
06ca: 0bd6           tst (sp)+
06cc: 09f7 fe80      jsr pc, 0550
06d0: 09f7 008c      jsr pc, 0760
06d4: 0bc0           tst r0
06d6: 0328           beq
06d8: 2df7 22ce 22c8 cmp 29aa, 29a6
06de: 020a           bne
06e0: 0bf7 22b6      tst 299a
06e4: 0207           bne
06e6: 1dce 22c2      mov 29ac, (sp)
06ea: 15e6 0001      mov $0001, -(sp)
06ee: 09df 1716      jsr pc, *$1716
06f2: 0bd6           tst (sp)+
06f4: a5f5 0023 f154 cmpb $0023, -eac(r5)
06fa: 030e           beq
06fc: 0bf7 22c6      tst 29c6
0700: 020b           bne
0702: 1dc3 22aa      mov 29b0, r3
0706: 94c4           movb (r3)+, r4
0708: 0307           beq
070a: 1dce 229e      mov 29ac, (sp)
070e: 1126           mov r4, -(sp)
0710: 09df 1716      jsr pc, *$1716
0714: 0bd6           tst (sp)+
0716: 01f7           br
0718: 1dce 2290      mov 29ac, (sp)
071c: 15e6 000a      mov $000a, -(sp)
0720: 09df 1716      jsr pc, *$1716
0724: 0bd6           tst (sp)+
0726: 01d4           br
0728: 1dc3 2284      mov 29b0, r3
072c: 94c4           movb (r3)+, r4
072e: 0307           beq
0730: 1dce 2278      mov 29ac, (sp)
0734: 1126           mov r4, -(sp)
0736: 09df 1716      jsr pc, *$1716
073a: 0bd6           tst (sp)+
073c: 01f7           br
073e: 1dce 226a      mov 29ac, (sp)
0742: 09df 173a      jsr pc, *$173a
0746: 1fce 2262      mov *29ac, (sp)
074a: 09df 1560      jsr pc, *$1560
074e: 1fce 2256      mov *29a8, (sp)
0752: 09df 1560      jsr pc, *$1560
0756: 1dc0 1d26      mov 2480, r0
075a: 0100           br
075c: 0077 11ea      jmp 194a
0760: 0977 11d8      jsr r5, 193c
0764: e5c6 0006      sub $0006, sp
0768: 2df7 223c 2238 cmp 29a8, 29a6
076e: 0202           bne
0770: 0ab7 223e      inc 29b2
0774: 1df7 2238 2234 mov 29b0, 29ae
077a: 8a3f 2230      clrb *29ae
077e: 0a02           clr r2
0780: 09f7 037c      jsr pc, 0b00
0784: 1004           mov r0, r4
0786: 25c4 0023      cmp $0023, r4
078a: 0202           bne
078c: 15c2 0001      mov $0001, r2
0790: 25c4 000a      cmp $000a, r4
0794: 0202           bne
0796: 005f 0a28      jmp *$0a28
079a: 0bc4           tst r4
079c: 0202           bne
079e: 005f 0a28      jmp *$0a28
07a2: 25c4 0061      cmp $0061, r4
07a6: 0603           bgt
07a8: 25c4 007a      cmp $007a, r4
07ac: 040b           bge
07ae: 25c4 0041      cmp $0041, r4
07b2: 0603           bgt
07b4: 25c4 005a      cmp $005a, r4
07b8: 0405           bge
07ba: 25c4 005f      cmp $005f, r4
07be: 0302           beq
07c0: 005f 095e      jmp *$095e
07c4: 1df5 21e6 fff6 mov 29ae, -a(r5)
07ca: 110e           mov r4, (sp)
07cc: 09df 0a98      jsr pc, *$0a98
07d0: 09f7 032c      jsr pc, 0b00
07d4: 1004           mov r0, r4
07d6: 25c4 0061      cmp $0061, r4
07da: 0603           bgt
07dc: 25c4 007a      cmp $007a, r4
07e0: 040f           bge
07e2: 25c4 0041      cmp $0041, r4
07e6: 0603           bgt
07e8: 25c4 005a      cmp $005a, r4
07ec: 0409           bge
07ee: 25c4 0030      cmp $0030, r4
07f2: 0603           bgt
07f4: 25c4 0039      cmp $0039, r4
07f8: 0403           bge
07fa: 25c4 005f      cmp $005f, r4
07fe: 0204           bne
0800: 110e           mov r4, (sp)
0802: 09df 0a98      jsr pc, *$0a98
0806: 01e4           br
0808: 0a0e           clr (sp)
080a: 09df 0a98      jsr pc, *$0a98
080e: 0af7 219c      dec 29ae
0812: 25c2 0003      cmp $0003, r2
0816: 0425           bge
0818: 0bf7 21aa      tst 29c6
081c: 0214           bne
081e: 15ce ffff      mov $ffff, (sp)
0822: 1d66 fff6      mov -a(r5), -(sp)
0826: 09df 0bf8      jsr pc, *$0bf8
082a: 0bd6           tst (sp)+
082c: 8bc8           tstb (r0)
082e: 0302           beq
0830: 0a00           clr r0
0832: 0102           br
0834: 15c0 0001      mov $0001, r0
0838: 6080           add r2, r0
083a: 25c0 0005      cmp $0005, r0
083e: 0203           bne
0840: 0ab7 2180      inc 29c4
0844: 0102           br
0846: 0ab7 217c      inc 29c6
084a: 25c4 000a      cmp $000a, r4
084e: 0306           beq
0850: 0bc4           tst r4
0852: 0304           beq
0854: 09f7 02a8      jsr pc, 0b00
0858: 1004           mov r0, r4
085a: 01f7           br
085c: 1100           mov r4, r0
085e: 005f 0a40      jmp *$0a40
0862: 25c2 0002      cmp $0002, r2
0866: 0203           bne
0868: 0bf7 215a      tst 29c6
086c: 020e           bne
086e: 110e           mov r4, (sp)
0870: 09df 0b82      jsr pc, *$0b82
0874: 108e           mov r2, (sp)
0876: 1d66 fff6      mov -a(r5), -(sp)
087a: 09df 0bf8      jsr pc, *$0bf8
087e: 0bd6           tst (sp)+
0880: 1035 fff8      mov r0, -8(r5)
0884: 09f7 0278      jsr pc, 0b00
0888: 1004           mov r0, r4
088a: 25c2 0001      cmp $0001, r2
088e: 0243           bne
0890: 2df5 2124 fff8 cmp 29b8, -8(r5)
0896: 0203           bne
0898: 15c2 0002      mov $0002, r2
089c: 013b           br
089e: 2df5 2118 fff8 cmp 29ba, -8(r5)
08a4: 0203           bne
08a6: 15c2 0003      mov $0003, r2
08aa: 0134           br
08ac: 2df5 2110 fff8 cmp 29c0, -8(r5)
08b2: 0203           bne
08b4: 15c2 0004      mov $0004, r2
08b8: 012d           br
08ba: 2df5 2100 fff8 cmp 29be, -8(r5)
08c0: 0203           bne
08c2: 15c2 0005      mov $0005, r2
08c6: 0126           br
08c8: 2df5 20f0 fff8 cmp 29bc, -8(r5)
08ce: 0212           bne
08d0: 0bf7 20f2      tst 29c6
08d4: 0303           beq
08d6: 0af7 20ec      dec 29c6
08da: 010a           br
08dc: 0bf7 20e4      tst 29c4
08e0: 0303           beq
08e2: 0af7 20de      dec 29c4
08e6: 0104           br
08e8: 15ce 1acf      mov $1acf, (sp)
08ec: 09df 0a64      jsr pc, *$0a64
08f0: 01ac           br
08f2: 0110           br
08f4: 15ce 1add      mov $1add, (sp)
08f8: 09df 0a64      jsr pc, *$0a64
08fc: 25c4 000a      cmp $000a, r4
0900: 0306           beq
0902: 0bc4           tst r4
0904: 0304           beq
0906: 09f7 01f6      jsr pc, 0b00
090a: 1004           mov r0, r4
090c: 01f7           br
090e: 1100           mov r4, r0
0910: 005f 0a40      jmp *$0a40
0914: 0121           br
0916: 25c2 0002      cmp $0002, r2
091a: 021e           bne
091c: 0bf7 20a6      tst 29c6
0920: 0294           bne
0922: 1d40 fff8      mov -8(r5), r0
0926: 1df0 209e 0008 mov 29c8, 8(r0)
092c: 110e           mov r4, (sp)
092e: 09df 0ad4      jsr pc, *$0ad4
0932: 09f7 01ca      jsr pc, 0b00
0936: 1004           mov r0, r4
0938: 25c4 000a      cmp $000a, r4
093c: 0306           beq
093e: 0bc4           tst r4
0940: 0304           beq
0942: 110e           mov r4, (sp)
0944: 09df 0ad4      jsr pc, *$0ad4
0948: 01f4           br
094a: 0a0e           clr (sp)
094c: 09df 0ad4      jsr pc, *$0ad4
0950: 15c0 0001      mov $0001, r0
0954: 005f 0a40      jmp *$0a40
0958: 005f 0790      jmp *$0790
095c: 015d           br
095e: 1103           mov r4, r3
0960: 25c3 0027      cmp $0027, r3
0964: 0303           beq
0966: 25c3 0022      cmp $0022, r3
096a: 0256           bne
096c: 10ce           mov r3, (sp)
096e: 09df 0a98      jsr pc, *$0a98
0972: 1df5 2038 fff4 mov 29ae, -c(r5)
0978: 0ab7 201c      inc 2998
097c: 09f7 0180      jsr pc, 0b00
0980: 1004           mov r0, r4
0982: 20c4           cmp r3, r4
0984: 0311           beq
0986: 25c4 000a      cmp $000a, r4
098a: 030e           beq
098c: 0bc4           tst r4
098e: 030c           beq
0990: 110e           mov r4, (sp)
0992: 09df 0a98      jsr pc, *$0a98
0996: 25c4 005c      cmp $005c, r4
099a: 0205           bne
099c: 09f7 0160      jsr pc, 0b00
09a0: 100e           mov r0, (sp)
09a2: 09df 0a98      jsr pc, *$0a98
09a6: 01ea           br
09a8: 0a37 1fec      clr 2998
09ac: 0bf7 2016      tst 29c6
09b0: 0302           beq
09b2: 005f 084a      jmp *$084a
09b6: 25c2 0003      cmp $0003, r2
09ba: 022e           bne
09bc: 0bf7 2006      tst 29c6
09c0: 0302           beq
09c2: 005f 084a      jmp *$084a
09c6: 8a3f 1fe4      clrb *29ae
09ca: 09f7 0132      jsr pc, 0b00
09ce: 1004           mov r0, r4
09d0: 25c4 000a      cmp $000a, r4
09d4: 0303           beq
09d6: 0bc4           tst r4
09d8: 0301           beq
09da: 01f7           br
09dc: 2df7 1fca 1fc4 cmp 29aa, 29a6
09e2: 0204           bne
09e4: 15ce 1aef      mov $1aef, (sp)
09e8: 09df 0a64      jsr pc, *$0a64
09ec: 1dce 1fba      mov 29aa, (sp)
09f0: 1d66 fff4      mov -c(r5), -(sp)
09f4: 09df 15d4      jsr pc, *$15d4
09f8: 0bd6           tst (sp)+
09fa: 0bc0           tst r0
09fc: 0408           bge
09fe: 1d4e fff4      mov -c(r5), (sp)
0a02: 15e6 1b00      mov $1b00, -(sp)
0a06: 09df 0a64      jsr pc, *$0a64
0a0a: 0bd6           tst (sp)+
0a0c: 0103           br
0a0e: 1df7 1f98 1f92 mov 29aa, 29a6
0a14: 1100           mov r4, r0
0a16: 0114           br
0a18: 110e           mov r4, (sp)
0a1a: 09df 0a98      jsr pc, *$0a98
0a1e: 09f7 00de      jsr pc, 0b00
0a22: 1004           mov r0, r4
0a24: 005f 0790      jmp *$0790
0a28: 0a0e           clr (sp)
0a2a: 09df 0a98      jsr pc, *$0a98
0a2e: 25c2 0001      cmp $0001, r2
0a32: 0404           bge
0a34: 15ce 1b10      mov $1b10, (sp)
0a38: 09df 0a64      jsr pc, *$0a64
0a3c: 1100           mov r4, r0
0a3e: 0100           br
0a40: 0077 0f06      jmp 194a
0a44: 0977 0ef4      jsr r5, 193c
0a48: 15ce 0001      mov $0001, (sp)
0a4c: 1d66 0006      mov 6(r5), -(sp)
0a50: 09df 0bf8      jsr pc, *$0bf8
0a54: 0bd6           tst (sp)+
0a56: 1004           mov r0, r4
0a58: 113d 0004      mov r4, *4(r5)
0a5c: 1134 0008      mov r4, 8(r4)
0a60: 0077 0ee6      jmp 194a
0a64: 0977 0ed4      jsr r5, 193c
0a68: 1dce 1f46      mov 29b2, (sp)
0a6c: 15e6 1b1f      mov $1b1f, -(sp)
0a70: 09df 133e      jsr pc, *$133e
0a74: 0bd6           tst (sp)+
0a76: 1d4e 0006      mov 6(r5), (sp)
0a7a: 1d66 0004      mov 4(r5), -(sp)
0a7e: 09df 133e      jsr pc, *$133e
0a82: 0bd6           tst (sp)+
0a84: 15ce 000a      mov $000a, (sp)
0a88: 09df 14f0      jsr pc, *$14f0
0a8c: 0ab7 1f24      inc 29b4
0a90: 0ab7 1f0a      inc 299e
0a94: 0077 0eb2      jmp 194a
0a98: 0977 0ea0      jsr r5, 193c
0a9c: 1dc4 1f0e      mov 29ae, r4
0aa0: 1dc0 1f0c      mov 29b0, r0
0aa4: 65c0 00c2      add $00c2, r0
0aa8: 2100           cmp r4, r0
0aaa: 0204           bne
0aac: 15ce 1b24      mov $1b24, (sp)
0ab0: 09df 0a64      jsr pc, *$0a64
0ab4: 9d54 0004      movb 4(r5), (r4)+
0ab8: 1dc0 1ef4      mov 29b0, r0
0abc: 65c0 00c3      add $00c3, r0
0ac0: 2100           cmp r4, r0
0ac2: 8304           blos
0ac4: 1dc4 1ee8      mov 29b0, r4
0ac8: 65c4 00c3      add $00c3, r4
0acc: 1137 1ede      mov r4, 29ae
0ad0: 0077 0e76      jmp 194a
0ad4: 0977 0e64      jsr r5, 193c
0ad8: 9d7f 0004 1eea movb 4(r5), *29c8
0ade: 0ab7 1ee6      inc 29c8
0ae2: 1dc0 1ee2      mov 29c8, r0
0ae6: e5c0 1ca8      sub $1ca8, r0
0aea: 25c0 07d0      cmp $07d0, r0
0aee: 0606           bgt
0af0: 15ce 1b32      mov $1b32, (sp)
0af4: 09df 0a64      jsr pc, *$0a64
0af8: 09f7 fa54      jsr pc, 0550
0afc: 0077 0e4a      jmp 194a
0b00: 0977 0e38      jsr r5, 193c
0b04: 09f7 008c      jsr pc, 0b94
0b08: 1004           mov r0, r4
0b0a: 25c4 002f      cmp $002f, r4
0b0e: 0235           bne
0b10: 0bf7 1e84      tst 2998
0b14: 0232           bne
0b16: 09f7 007a      jsr pc, 0b94
0b1a: 1004           mov r0, r4
0b1c: 25c4 002a      cmp $002a, r4
0b20: 0306           beq
0b22: 110e           mov r4, (sp)
0b24: 09df 0b82      jsr pc, *$0b82
0b28: 15c0 002f      mov $002f, r0
0b2c: 0128           br
0b2e: 09f7 0062      jsr pc, 0b94
0b32: 1004           mov r0, r4
0b34: 1100           mov r4, r0
0b36: 0118           br
0b38: 0a00           clr r0
0b3a: 0121           br
0b3c: 09f7 0054      jsr pc, 0b94
0b40: 1004           mov r0, r4
0b42: 25c4 002f      cmp $002f, r4
0b46: 03de           beq
0b48: 01f5           br
0b4a: 2df7 1e5a 1e56 cmp 29a8, 29a6
0b50: 0209           bne
0b52: 1dce 1e56      mov 29ac, (sp)
0b56: 15e6 000a      mov $000a, -(sp)
0b5a: 09df 1716      jsr pc, *$1716
0b5e: 0bd6           tst (sp)+
0b60: 0ab7 1e4e      inc 29b2
0b64: 01e4           br
0b66: 0108           br
0b68: 15c1 19a0      mov $19a0, r1
0b6c: 1037 0e36      mov r0, 19a6
0b70: 2011           cmp r0, (r1)+
0b72: 02fe           bne
0b74: 0079 0006      jmp *6(r1)
0b78: 01da           br
0b7a: 1100           mov r4, r0
0b7c: 0100           br
0b7e: 0077 0dc8      jmp 194a
0b82: 0977 0db6      jsr r5, 193c
0b86: 0ab7 0e26      inc 19b0
0b8a: 9d7f 0004 0e20 movb 4(r5), *19b0
0b90: 0077 0db6      jmp 194a
0b94: 0977 0da4      jsr r5, 193c
0b98: 8bff 0e14      tstb *19b0
0b9c: 0305           beq
0b9e: 9fc0 0e0e      movb *19b0, r0
0ba2: 0af7 0e0a      dec 19b0
0ba6: 0126           br
0ba8: 0a37 1df8      clr 29a4
0bac: 1dce 1df6      mov 29a6, (sp)
0bb0: 09df 1638      jsr pc, *$1638
0bb4: 1004           mov r0, r4
0bb6: 0bc4           tst r4
0bb8: 0417           bge
0bba: 2df7 1dec 1de6 cmp 29aa, 29a6
0bc0: 0213           bne
0bc2: 1fce 1de4      mov *29aa, (sp)
0bc6: 09df 1560      jsr pc, *$1560
0bca: 1df7 1dda 1dd6 mov 29a8, 29a6
0bd0: 1dce 1dd8      mov 29ac, (sp)
0bd4: 15e6 000a      mov $000a, -(sp)
0bd8: 09df 1716      jsr pc, *$1716
0bdc: 0bd6           tst (sp)+
0bde: 0ab7 1dd0      inc 29b2
0be2: 09f7 ffae      jsr pc, 0b94
0be6: 1004           mov r0, r4
0be8: 0bc4           tst r4
0bea: 0402           bge
0bec: 0a00           clr r0
0bee: 0102           br
0bf0: 1100           mov r4, r0
0bf2: 0100           br
0bf4: 0077 0d52      jmp 194a
0bf8: 0977 0d40      jsr r5, 193c
0bfc: e5c6 0006      sub $0006, sp
0c00: 1d44 0004      mov 4(r5), r4
0c04: 0a00           clr r0
0c06: 1035 fff8      mov r0, -8(r5)
0c0a: 1035 fff4      mov r0, -c(r5)
0c0e: 9500           movb (r4)+, r0
0c10: 1035 fff6      mov r0, -a(r5)
0c14: 0304           beq
0c16: 6d75 fff6 fff8 add -a(r5), -8(r5)
0c1c: 01f8           br
0c1e: 1d41 fff8      mov -8(r5), r1
0c22: 0dc0           sxt r0
0c24: 7237 0d40      div r0, 1968
0c28: 1075 fff8      mov r1, -8(r5)
0c2c: 1d41 fff8      mov -8(r5), r1
0c30: 7057 000a      mul r1, $000a
0c34: 1042           mov r1, r2
0c36: 6dc2 1d7c      add 29b6, r2
0c3a: 8bca           tstb (r2)
0c3c: 0333           beq
0c3e: 1083           mov r2, r3
0c40: 1d44 0004      mov 4(r5), r4
0c44: a313           cmpb (r4), (r3)+
0c46: 0214           bne
0c48: 8bd4           tstb (r4)+
0c4a: 0306           beq
0c4c: 1d40 0004      mov 4(r5), r0
0c50: 65c0 0008      add $0008, r0
0c54: 2100           cmp r4, r0
0c56: 020b           bne
0c58: 0bf5 0006      tst 6(r5)
0c5c: 0206           bne
0c5e: 108e           mov r2, (sp)
0c60: 1d66 0004      mov 4(r5), -(sp)
0c64: 09df 0cfc      jsr pc, *$0cfc
0c68: 0bd6           tst (sp)+
0c6a: 1080           mov r2, r0
0c6c: 012c           br
0c6e: 01ea           br
0c70: 65c2 000a      add $000a, r2
0c74: 1dc1 0cf0      mov 1968, r1
0c78: 7057 000a      mul r1, $000a
0c7c: 6dc1 1d36      add 29b6, r1
0c80: 2081           cmp r2, r1
0c82: 870f           bcs
0c84: 1d40 fff4      mov -c(r5), r0
0c88: 0ab5 fff4      inc -c(r5)
0c8c: 0bc0           tst r0
0c8e: 0307           beq
0c90: 15ce 1b44      mov $1b44, (sp)
0c94: 09df 0a64      jsr pc, *$0a64
0c98: 09f7 f8b4      jsr pc, 0550
0c9c: 0102           br
0c9e: 1dc2 1d14      mov 29b6, r2
0ca2: 01cb           br
0ca4: 0bf5 0006      tst 6(r5)
0ca8: 070c           ble
0caa: 1d43 0004      mov 4(r5), r3
0cae: 1084           mov r2, r4
0cb0: 1080           mov r2, r0
0cb2: 65c0 0008      add $0008, r0
0cb6: 2100           cmp r4, r0
0cb8: 8604           bcc
0cba: 92d4           movb (r3), (r4)+
0cbc: 0301           beq
0cbe: 0a83           inc r3
0cc0: 01f7           br
0cc2: 1080           mov r2, r0
0cc4: 0100           br
0cc6: 0077 0c80      jmp 194a
0cca: 0977 0c6e      jsr r5, 193c
0cce: 1dc0 1eec      mov 2bbe, r0
0cd2: e5c0 2af6      sub $2af6, r0
0cd6: 25c0 00c8      cmp $00c8, r0
0cda: 0409           bge
0cdc: 1dce 1ede      mov 2bbe, (sp)
0ce0: 0af7 1eda      dec 2bbe
0ce4: 15e6 1b55      mov $1b55, -(sp)
0ce8: 09df 0a64      jsr pc, *$0a64
0cec: 0bd6           tst (sp)+
0cee: 9d7f 0004 1eca movb 4(r5), *2bbe
0cf4: 0ab7 1ec6      inc 2bbe
0cf8: 0077 0c4e      jmp 194a
0cfc: 0977 0c3c      jsr r5, 193c
0d00: 1d77 0004 1ca8 mov 4(r5), 29ae
0d06: 15f7 2af6 1eb2 mov $2af6, 2bbe
0d0c: 1dc0 1c94      mov 29a4, r0
0d10: 0ab7 1c90      inc 29a4
0d14: 25c0 0064      cmp $0064, r0
0d18: 0405           bge
0d1a: 15ce 1b6e      mov $1b6e, (sp)
0d1e: 09df 0a64      jsr pc, *$0a64
0d22: 013b           br
0d24: 1d40 0006      mov 6(r5), r0
0d28: 1c04 0008      mov 8(r0), r4
0d2c: 0bc4           tst r4
0d2e: 0335           beq
0d30: 1d40 0006      mov 6(r5), r0
0d34: 1c0e 0008      mov 8(r0), (sp)
0d38: 1d66 0006      mov 6(r5), -(sp)
0d3c: 09df 130a      jsr pc, *$130a
0d40: 0bd6           tst (sp)+
0d42: 0bc0           tst r0
0d44: 0308           beq
0d46: 8bcc           tstb (r4)
0d48: 0305           beq
0d4a: 9500           movb (r4)+, r0
0d4c: 100e           mov r0, (sp)
0d4e: 09df 0a98      jsr pc, *$0a98
0d52: 01f9           br
0d54: 0122           br
0d56: 15ce 0020      mov $0020, (sp)
0d5a: 09df 0cca      jsr pc, *$0cca
0d5e: a5cc 0028      cmpb $0028, (r4)
0d62: 0204           bne
0d64: 110e           mov r4, (sp)
0d66: 09df 0f38      jsr pc, *$0f38
0d6a: 0107           br
0d6c: 8bcc           tstb (r4)
0d6e: 0305           beq
0d70: 9500           movb (r4)+, r0
0d72: 100e           mov r0, (sp)
0d74: 09df 0cca      jsr pc, *$0cca
0d78: 01f9           br
0d7a: 15ce 0020      mov $0020, (sp)
0d7e: 09df 0cca      jsr pc, *$0cca
0d82: 25f7 2af6 1e36 cmp $2af6, 2bbe
0d88: 8608           bcc
0d8a: 0af7 1e30      dec 2bbe
0d8e: 9fc0 1e2c      movb *2bbe, r0
0d92: 100e           mov r0, (sp)
0d94: 09df 0b82      jsr pc, *$0b82
0d98: 01f4           br
0d9a: 0077 0bac      jmp 194a
0d9e: 0977 0b9a      jsr r5, 193c
0da2: 1d43 0004      mov 4(r5), r3
0da6: 0a04           clr r4
0da8: 94c2           movb (r3)+, r2
0daa: 0307           beq
0dac: 25c2 002f      cmp $002f, r2
0db0: 0202           bne
0db2: 0a04           clr r4
0db4: 0101           br
0db6: 0a84           inc r4
0db8: 01f7           br
0dba: e5c3 0003      sub $0003, r3
0dbe: 25c4 000e      cmp $000e, r4
0dc2: 0508           blt
0dc4: 25c4 0002      cmp $0002, r4
0dc8: 0405           bge
0dca: a5d3 002e      cmpb $002e, (r3)+
0dce: 0202           bne
0dd0: 92c0           movb (r3), r0
0dd2: 0102           br
0dd4: 0a00           clr r0
0dd6: 0100           br
0dd8: 0077 0b6e      jmp 194a
0ddc: 0977 0b5c      jsr r5, 193c
0de0: 1d4e 0004      mov 4(r5), (sp)
0de4: 09df 0eaa      jsr pc, *$0eaa
0de8: 1003           mov r0, r3
0dea: 10c4           mov r3, r4
0dec: 8bcc           tstb (r4)
0dee: 0305           beq
0df0: a5d4 002f      cmpb $002f, (r4)+
0df4: 0201           bne
0df6: 1103           mov r4, r3
0df8: 01f9           br
0dfa: 9d74 0006 ffff movb 6(r5), -1(r4)
0e00: 10c0           mov r3, r0
0e02: 0100           br
0e04: 0077 0b42      jmp 194a
0e08: 0977 0b30      jsr r5, 193c
0e0c: e5c6 0004      sub $0004, sp
0e10: 09f7 07a8      jsr pc, 15bc
0e14: 1035 fff8      mov r0, -8(r5)
0e18: 0213           bne
0e1a: 1d4e 0006      mov 6(r5), (sp)
0e1e: 1d66 0004      mov 4(r5), -(sp)
0e22: 09df 1594      jsr pc, *$1594
0e26: 0bd6           tst (sp)+
0e28: 1d4e 0004      mov 4(r5), (sp)
0e2c: 15e6 1b85      mov $1b85, -(sp)
0e30: 09df 133e      jsr pc, *$133e
0e34: 0bd6           tst (sp)+
0e36: 15ce 0001      mov $0001, (sp)
0e3a: 09df 18c6      jsr pc, *$18c6
0e3e: 010b           br
0e40: 25f5 ffff fff8 cmp $ffff, -8(r5)
0e46: 0207           bne
0e48: 15ce 1b94      mov $1b94, (sp)
0e4c: 09df 133e      jsr pc, *$133e
0e50: 15c0 0001      mov $0001, r0
0e54: 0128           br
0e56: 114e           mov r5, (sp)
0e58: 65ce fff6      add $fff6, (sp)
0e5c: 09df 18a6      jsr pc, *$18a6
0e60: 2d40 fff8      cmp -8(r5), r0
0e64: 0301           beq
0e66: 01f7           br
0e68: 1d40 fff6      mov -a(r5), r0
0e6c: 45c0 ff00      bic $ff00, r0
0e70: 1035 fff8      mov r0, -8(r5)
0e74: 0311           beq
0e76: 25f5 000e fff8 cmp $000e, -8(r5)
0e7c: 030d           beq
0e7e: 25f5 0002 fff8 cmp $0002, -8(r5)
0e84: 0307           beq
0e86: 1d4e 0004      mov 4(r5), (sp)
0e8a: 15e6 1b9f      mov $1b9f, -(sp)
0e8e: 09df 133e      jsr pc, *$133e
0e92: 0bd6           tst (sp)+
0e94: 09f7 f6b8      jsr pc, 0550
0e98: 1d40 fff6      mov -a(r5), r0
0e9c: 7417 fff8      ash r0, $fff8
0ea0: 45c0 ff00      bic $ff00, r0
0ea4: 0100           br
0ea6: 0077 0aa0      jmp 194a
0eaa: 0977 0a8e      jsr r5, 193c
0eae: 1dc4 0ab4      mov 1966, r4
0eb2: 1d43 0004      mov 4(r5), r3
0eb6: 1dc0 0aac      mov 1966, r0
0eba: 0ab7 0aa8      inc 1966
0ebe: 94c8           movb (r3)+, (r0)
0ec0: 0301           beq
0ec2: 01f9           br
0ec4: 1100           mov r4, r0
0ec6: 0100           br
0ec8: 0077 0a7e      jmp 194a
0ecc: 0977 0a6c      jsr r5, 193c
0ed0: 1d43 0006      mov 6(r5), r3
0ed4: 10ce           mov r3, (sp)
0ed6: 09df 0d9e      jsr pc, *$0d9e
0eda: 25c0 006f      cmp $006f, r0
0ede: 0303           beq
0ee0: 15c0 0001      mov $0001, r0
0ee4: 0119           br
0ee6: 1d40 0004      mov 4(r5), r0
0eea: 65f5 0002 0004 add $0002, 4(r5)
0ef0: 1204           mov (r0), r4
0ef2: 030f           beq
0ef4: 94c2           movb (r3)+, r2
0ef6: 0304           beq
0ef8: 9500           movb (r4)+, r0
0efa: 2080           cmp r2, r0
0efc: 0201           bne
0efe: 01fa           br
0f00: 8bcc           tstb (r4)
0f02: 0204           bne
0f04: 0bc2           tst r2
0f06: 0202           bne
0f08: 0a00           clr r0
0f0a: 0106           br
0f0c: 1d43 0006      mov 6(r5), r3
0f10: 01ea           br
0f12: 15c0 0001      mov $0001, r0
0f16: 0100           br
0f18: 0077 0a2e      jmp 194a
0f1c: 0977 0a1c      jsr r5, 193c
0f20: 0bf5 0004      tst 4(r5)
0f24: 0202           bne
0f26: 0a00           clr r0
0f28: 0105           br
0f2a: 1d4e 0004      mov 4(r5), (sp)
0f2e: 09df 188c      jsr pc, *$188c
0f32: 0100           br
0f34: 0077 0a12      jmp 194a
0f38: 0977 0a00      jsr r5, 193c
0f3c: e5c6 013a      sub $013a, sp
0f40: 1140           mov r5, r0
0f42: 65c0 feca      add $feca, r0
0f46: 1035 fec8      mov r0, -138(r5)
0f4a: 1d40 fec8      mov -138(r5), r0
0f4e: 0ab5 fec8      inc -138(r5)
0f52: 1d41 0004      mov 4(r5), r1
0f56: 0ab5 0004      inc 4(r5)
0f5a: 9248           movb (r1), (r0)
0f5c: 0301           beq
0f5e: 01f5           br
0f60: 1140           mov r5, r0
0f62: 65c0 feca      add $feca, r0
0f66: 1035 0004      mov r0, 4(r5)
0f6a: 0a35 fec6      clr -13a(r5)
0f6e: 114e           mov r5, (sp)
0f70: 65ce 0004      add $0004, (sp)
0f74: 09df 10ba      jsr pc, *$10ba
0f78: 1d41 fec6      mov -13a(r5), r1
0f7c: 0cc1           asl r1
0f7e: 6141           add r5, r1
0f80: 1031 ff6e      mov r0, -92(r1)
0f84: 0303           beq
0f86: 0ab5 fec6      inc -13a(r5)
0f8a: 01f1           br
0f8c: 1140           mov r5, r0
0f8e: 65c0 ff96      add $ff96, r0
0f92: 1035 ff30      mov r0, -d0(r5)
0f96: 09f7 fb66      jsr pc, 0b00
0f9a: 1035 fec0      mov r0, -140(r5)
0f9e: 25c0 0020      cmp $0020, r0
0fa2: 0201           bne
0fa4: 01f8           br
0fa6: 25f5 0028 fec0 cmp $0028, -140(r5)
0fac: 0306           beq
0fae: 15ce 1bb2      mov $1bb2, (sp)
0fb2: 09df 0a64      jsr pc, *$0a64
0fb6: 005f 10b6      jmp *$10b6
0fba: 1d4e fec0      mov -140(r5), (sp)
0fbe: 09df 0b82      jsr pc, *$0b82
0fc2: 0a35 fec4      clr -13c(r5)
0fc6: 114e           mov r5, (sp)
0fc8: 65ce ff30      add $ff30, (sp)
0fcc: 09df 114a      jsr pc, *$114a
0fd0: 1d41 fec4      mov -13c(r5), r1
0fd4: 0cc1           asl r1
0fd6: 6141           add r5, r1
0fd8: 1031 ff46      mov r0, -ba(r1)
0fdc: 0303           beq
0fde: 0ab5 fec4      inc -13c(r5)
0fe2: 01f1           br
0fe4: 2d75 fec6 fec4 cmp -13a(r5), -13c(r5)
0fea: 0305           beq
0fec: 15ce 1bd6      mov $1bd6, (sp)
0ff0: 09df 0a64      jsr pc, *$0a64
0ff4: 0160           br
0ff6: 9f40 0004      movb *4(r5), r0
0ffa: 0ab5 0004      inc 4(r5)
0ffe: 1035 fec0      mov r0, -140(r5)
1002: 0359           beq
1004: 1d4e fec0      mov -140(r5), (sp)
1008: 09df 12a2      jsr pc, *$12a2
100c: 0bc0           tst r0
100e: 0205           bne
1010: 1d4e fec0      mov -140(r5), (sp)
1014: 09df 0cca      jsr pc, *$0cca
1018: 014d           br
101a: 1140           mov r5, r0
101c: 65c0 ff32      add $ff32, r0
1020: 1035 ff2e      mov r0, -d2(r5)
1024: 9d7d fec0 ff2e movb -140(r5), *-d2(r5)
102a: 0ab5 ff2e      inc -d2(r5)
102e: 9f40 0004      movb *4(r5), r0
1032: 100e           mov r0, (sp)
1034: 09df 12dc      jsr pc, *$12dc
1038: 0bc0           tst r0
103a: 0308           beq
103c: 9f7d 0004 ff2e movb *4(r5), *-d2(r5)
1042: 0ab5 ff2e      inc -d2(r5)
1046: 0ab5 0004      inc 4(r5)
104a: 01f1           br
104c: 8a3d ff2e      clrb *-d2(r5)
1050: 0a35 fec4      clr -13c(r5)
1054: 2d75 fec6 fec4 cmp -13a(r5), -13c(r5)
105a: 0711           ble
105c: 1d40 fec4      mov -13c(r5), r0
1060: 0cc0           asl r0
1062: 6140           add r5, r0
1064: 1c0e ff6e      mov -92(r0), (sp)
1068: 1166           mov r5, -(sp)
106a: 65ce ff32      add $ff32, (sp)
106e: 09df 130a      jsr pc, *$130a
1072: 0bd6           tst (sp)+
1074: 0bc0           tst r0
1076: 0203           bne
1078: 0ab5 fec4      inc -13c(r5)
107c: 01eb           br
107e: 2d75 fec6 fec4 cmp -13a(r5), -13c(r5)
1084: 0707           ble
1086: 1d40 fec4      mov -13c(r5), r0
108a: 0cc0           asl r0
108c: 6140           add r5, r0
108e: 1c00 ff46      mov -ba(r0), r0
1092: 0103           br
1094: 1140           mov r5, r0
1096: 65c0 ff32      add $ff32, r0
109a: 1035 ff2e      mov r0, -d2(r5)
109e: 8bfd ff2e      tstb *-d2(r5)
10a2: 0308           beq
10a4: 9f40 ff2e      movb *-d2(r5), r0
10a8: 100e           mov r0, (sp)
10aa: 0ab5 ff2e      inc -d2(r5)
10ae: 09df 0cca      jsr pc, *$0cca
10b2: 01f5           br
10b4: 01a0           br
10b6: 0077 0890      jmp 194a
10ba: 0977 087e      jsr r5, 193c
10be: e5c6 0004      sub $0004, sp
10c2: 1f40 0004      mov *4(r5), r0
10c6: 9200           movb (r0), r0
10c8: 1035 fff6      mov r0, -a(r5)
10cc: 1f40 0004      mov *4(r5), r0
10d0: 0abd 0004      inc *4(r5)
10d4: 8a08           clrb (r0)
10d6: 25f5 0029 fff6 cmp $0029, -a(r5)
10dc: 0202           bne
10de: 0a00           clr r0
10e0: 0132           br
10e2: 1f40 0004      mov *4(r5), r0
10e6: a5c8 0020      cmpb $0020, (r0)
10ea: 0203           bne
10ec: 0abd 0004      inc *4(r5)
10f0: 01f8           br
10f2: 1f75 0004 fff8 mov *4(r5), -8(r5)
10f8: 1f40 0004      mov *4(r5), r0
10fc: 9200           movb (r0), r0
10fe: 1035 fff6      mov r0, -a(r5)
1102: 25c0 002c      cmp $002c, r0
1106: 031c           beq
1108: 25f5 0029 fff6 cmp $0029, -a(r5)
110e: 0318           beq
1110: 1d4e fff6      mov -a(r5), (sp)
1114: 09df 12dc      jsr pc, *$12dc
1118: 0bc0           tst r0
111a: 030a           beq
111c: 2d7d fff8 0004 cmp -8(r5), *4(r5)
1122: 020b           bne
1124: 1d4e fff6      mov -a(r5), (sp)
1128: 09df 12a2      jsr pc, *$12a2
112c: 0bc0           tst r0
112e: 0205           bne
1130: 15ce 1bef      mov $1bef, (sp)
1134: 09df 0a64      jsr pc, *$0a64
1138: 0103           br
113a: 0abd 0004      inc *4(r5)
113e: 01dc           br
1140: 1d40 fff8      mov -8(r5), r0
1144: 0100           br
1146: 0077 0800      jmp 194a
114a: 0977 07ee      jsr r5, 193c
114e: e5c6 0008      sub $0008, sp
1152: 0a35 fff2      clr -e(r5)
1156: 1f75 0004 fff8 mov *4(r5), -8(r5)
115c: 09f7 f9a0      jsr pc, 0b00
1160: 25c0 0029      cmp $0029, r0
1164: 0203           bne
1166: 0a00           clr r0
1168: 005f 129e      jmp *$129e
116c: 09f7 f990      jsr pc, 0b00
1170: 1035 fff6      mov r0, -a(r5)
1174: 25c0 002c      cmp $002c, r0
1178: 0304           beq
117a: 25f5 0029 fff6 cmp $0029, -a(r5)
1180: 0205           bne
1182: 0bf5 fff2      tst -e(r5)
1186: 0602           bgt
1188: 005f 1286      jmp *$1286
118c: 25f5 0022 fff6 cmp $0022, -a(r5)
1192: 0304           beq
1194: 25f5 0027 fff6 cmp $0027, -a(r5)
119a: 0244           bne
119c: 1d75 fff6 fff4 mov -a(r5), -c(r5)
11a2: 25f5 0027 fff4 cmp $0027, -c(r5)
11a8: 0206           bne
11aa: 1f40 0004      mov *4(r5), r0
11ae: 0abd 0004      inc *4(r5)
11b2: 95c8 0027      movb $0027, (r0)
11b6: 09f7 f946      jsr pc, 0b00
11ba: 1035 fff6      mov r0, -a(r5)
11be: 2d40 fff4      cmp -c(r5), r0
11c2: 0325           beq
11c4: 25f5 000a fff6 cmp $000a, -a(r5)
11ca: 0205           bne
11cc: 15ce 1c0f      mov $1c0f, (sp)
11d0: 09df 0a64      jsr pc, *$0a64
11d4: 011c           br
11d6: 25f5 005c fff6 cmp $005c, -a(r5)
11dc: 0211           bne
11de: 09f7 f91e      jsr pc, 0b00
11e2: 1035 fff6      mov r0, -a(r5)
11e6: 2d40 fff4      cmp -c(r5), r0
11ea: 030a           beq
11ec: 25f5 005c fff6 cmp $005c, -a(r5)
11f2: 0306           beq
11f4: 1f40 0004      mov *4(r5), r0
11f8: 0abd 0004      inc *4(r5)
11fc: 95c8 005c      movb $005c, (r0)
1200: 1f40 0004      mov *4(r5), r0
1204: 0abd 0004      inc *4(r5)
1208: 9d48 fff6      movb -a(r5), (r0)
120c: 01d4           br
120e: 25f5 0027 fff4 cmp $0027, -c(r5)
1214: 0206           bne
1216: 1f40 0004      mov *4(r5), r0
121a: 0abd 0004      inc *4(r5)
121e: 95c8 0027      movb $0027, (r0)
1222: 012f           br
1224: 25f5 005c fff6 cmp $005c, -a(r5)
122a: 0219           bne
122c: 09f7 f8d0      jsr pc, 0b00
1230: 1035 fff6      mov r0, -a(r5)
1234: 25f5 0022 fff6 cmp $0022, -a(r5)
123a: 030a           beq
123c: 25f5 005c fff6 cmp $005c, -a(r5)
1242: 0306           beq
1244: 1f40 0004      mov *4(r5), r0
1248: 0abd 0004      inc *4(r5)
124c: 95c8 005c      movb $005c, (r0)
1250: 1f40 0004      mov *4(r5), r0
1254: 0abd 0004      inc *4(r5)
1258: 9d48 fff6      movb -a(r5), (r0)
125c: 0112           br
125e: 1f40 0004      mov *4(r5), r0
1262: 0abd 0004      inc *4(r5)
1266: 9d48 fff6      movb -a(r5), (r0)
126a: 25f5 0028 fff6 cmp $0028, -a(r5)
1270: 0202           bne
1272: 0ab5 fff2      inc -e(r5)
1276: 25f5 0029 fff6 cmp $0029, -a(r5)
127c: 0202           bne
127e: 0af5 fff2      dec -e(r5)
1282: 005f 116c      jmp *$116c
1286: 1f40 0004      mov *4(r5), r0
128a: 0abd 0004      inc *4(r5)
128e: 8a08           clrb (r0)
1290: 1d4e fff6      mov -a(r5), (sp)
1294: 09df 0b82      jsr pc, *$0b82
1298: 1d40 fff8      mov -8(r5), r0
129c: 0100           br
129e: 0077 06a8      jmp 194a
12a2: 0977 0696      jsr r5, 193c
12a6: 25f5 0061 0004 cmp $0061, 4(r5)
12ac: 0604           bgt
12ae: 25f5 007a 0004 cmp $007a, 4(r5)
12b4: 040c           bge
12b6: 25f5 0041 0004 cmp $0041, 4(r5)
12bc: 0604           bgt
12be: 25f5 005a 0004 cmp $005a, 4(r5)
12c4: 0404           bge
12c6: 25f5 005f 0004 cmp $005f, 4(r5)
12cc: 0203           bne
12ce: 15c0 0001      mov $0001, r0
12d2: 0102           br
12d4: 0a00           clr r0
12d6: 0100           br
12d8: 0077 066e      jmp 194a
12dc: 0977 065c      jsr r5, 193c
12e0: 1d4e 0004      mov 4(r5), (sp)
12e4: 09df 12a2      jsr pc, *$12a2
12e8: 0bc0           tst r0
12ea: 0208           bne
12ec: 25f5 0030 0004 cmp $0030, 4(r5)
12f2: 0607           bgt
12f4: 25f5 0039 0004 cmp $0039, 4(r5)
12fa: 0503           blt
12fc: 15c0 0001      mov $0001, r0
1300: 0102           br
1302: 0a00           clr r0
1304: 0100           br
1306: 0077 0640      jmp 194a
130a: 0977 062e      jsr r5, 193c
130e: 0be6           tst -(sp)
1310: 9f40 0004      movb *4(r5), r0
1314: 1035 fff8      mov r0, -8(r5)
1318: 0ab5 0004      inc 4(r5)
131c: 9f41 0006      movb *6(r5), r1
1320: 0ab5 0006      inc 6(r5)
1324: 2040           cmp r1, r0
1326: 0207           bne
1328: 0bf5 fff8      tst -8(r5)
132c: 0203           bne
132e: 15c0 0001      mov $0001, r0
1332: 0103           br
1334: 01ed           br
1336: 0a00           clr r0
1338: 0100           br
133a: 0077 060c      jmp 194a
133e: 0977 05fa      jsr r5, 193c
1342: e5c6 007e      sub $007e, sp
1346: 1d77 0004 187c mov 4(r5), 2bc8
134c: 1144           mov r5, r4
134e: 65c4 0006      add $0006, r4
1352: 9fc0 1872      movb *2bc8, r0
1356: 0309           beq
1358: 0ab7 186c      inc 2bc8
135c: 2017 0025      cmp r0, $0025
1360: 0306           beq
1362: 100e           mov r0, (sp)
1364: 09df 14f0      jsr pc, *$14f0
1368: 01f4           br
136a: 0077 05dc      jmp 194a
136e: 0a37 1858      clr 2bca
1372: 0a37 1858      clr 2bce
1376: afd7 184e 002d cmpb *2bc8, $002d
137c: 0204           bne
137e: 0ab7 1846      inc 2bc8
1382: 0ab7 1844      inc 2bca
1386: 08f7 0128      jsr r3, 14b2
138a: 1077 1838      mov r1, 2bc6
138e: 0a37 183a      clr 2bcc
1392: 2017 002e      cmp r0, $002e
1396: 0204           bne
1398: 08f7 0116      jsr r3, 14b2
139c: 1077 182e      mov r1, 2bce
13a0: 1183           mov sp, r3
13a2: 65c3 0004      add $0004, r3
13a6: 15c1 1c26      mov $1c26, r1
13aa: 1442           mov (r1)+, r2
13ac: 03da           beq
13ae: 2011           cmp r0, (r1)+
13b0: 02fc           bne
13b2: 004a           jmp (r2)
13b4: 1501           mov (r4)+, r1
13b6: 0405           bge
13b8: 0b01           neg r1
13ba: 95d3 002d      movb $002d, (r3)+
13be: 0101           br
13c0: 1501           mov (r4)+, r1
13c2: 09f7 0002      jsr pc, 13c8
13c6: 0152           br
13c8: 0a00           clr r0
13ca: 7217 000a      div r0, $000a
13ce: 1066           mov r1, -(sp)
13d0: 1001           mov r0, r1
13d2: 0302           beq
13d4: 09f7 fff0      jsr pc, 13c8
13d8: 1580           mov (sp)+, r0
13da: 65c0 0030      add $0030, r0
13de: 9013           movb r0, (r3)+
13e0: 0087           rts pc
13e2: 9513           movb (r4)+, (r3)+
13e4: 0201           bne
13e6: 0ac3           dec r3
13e8: 9513           movb (r4)+, (r3)+
13ea: 0240           bne
13ec: 0ac3           dec r3
13ee: 013e           br
13f0: 1dc1 17da      mov 2bce, r1
13f4: 0a03           clr r3
13f6: 1302           mov (r4), r2
13f8: 8bd2           tstb (r2)+
13fa: 0302           beq
13fc: 0a83           inc r3
13fe: 7e44           sob r1, 0004
1400: 1502           mov (r4)+, r2
1402: 0138           br
1404: 15c2 1c4e      mov $1c4e, r2
1408: 0102           br
140a: 15c2 1c52      mov $1c52, r2
140e: 1501           mov (r4)+, r1
1410: 0305           beq
1412: 0bf7 17b8      tst 2bce
1416: 0302           beq
1418: 95d3 0030      movb $0030, (r3)+
141c: 0a00           clr r0
141e: 09f7 0002      jsr pc, 1424
1422: 0124           br
1424: 1066           mov r1, -(sp)
1426: 760a           ashc r0, (r2)
1428: 0302           beq
142a: 09f7 fff6      jsr pc, 1424
142e: 1580           mov (sp)+, r0
1430: 4c80 0002      bic 2(r2), r0
1434: 65c0 0030      add $0030, r0
1438: 2017 0039      cmp r0, $0039
143c: 0702           ble
143e: 65c0 0007      add $0007, r0
1442: 9013           movb r0, (r3)+
1444: 0087           rts pc
1446: 1dc0 1784      mov 2bce, r0
144a: 1dc2 177e      mov 2bcc, r2
144e: 09f7 0094      jsr pc, 14e6
1452: 010c           br
1454: 1dc0 1776      mov 2bce, r0
1458: 1dc2 1770      mov 2bcc, r2
145c: 09f7 0086      jsr pc, 14e6
1460: 0105           br
1462: 1504           mov (r4)+, r4
1464: 1537 1760      mov (r4)+, 2bc8
1468: 0077 fee6      jmp 1352
146c: 1182           mov sp, r2
146e: 65c2 0004      add $0004, r2
1472: e083           sub r2, r3
1474: 1126           mov r4, -(sp)
1476: 15e6 0020      mov $0020, -(sp)
147a: 10c4           mov r3, r4
147c: 0b03           neg r3
147e: 6dc3 1744      add 2bc6, r3
1482: 0706           ble
1484: 0bf7 1742      tst 2bca
1488: 0203           bne
148a: 09df 14f0      jsr pc, *$14f0
148e: 7ec3           sob r3, 0003
1490: 0bc4           tst r4
1492: 0304           beq
1494: 948e           movb (r2)+, (sp)
1496: 09df 14f0      jsr pc, *$14f0
149a: 7f04           sob r4, 0004
149c: 0bc3           tst r3
149e: 0705           ble
14a0: 15ce 0020      mov $0020, (sp)
14a4: 09df 14f0      jsr pc, *$14f0
14a8: 7ec3           sob r3, 0003
14aa: 0bd6           tst (sp)+
14ac: 1584           mov (sp)+, r4
14ae: 0077 fea0      jmp 1352
14b2: 0a37 1716      clr 2bcc
14b6: 0a01           clr r1
14b8: 9fc0 170c      movb *2bc8, r0
14bc: 0ab7 1708      inc 2bc8
14c0: e5c0 0030      sub $0030, r0
14c4: 2017 fffa      cmp r0, $fffa
14c8: 0202           bne
14ca: 1500           mov (r4)+, r0
14cc: 0103           br
14ce: 2017 0009      cmp r0, $0009
14d2: 8206           bhi
14d4: 0ab7 16f4      inc 2bcc
14d8: 7057 000a      mul r1, $000a
14dc: 6001           add r0, r1
14de: 01ec           br
14e0: 65c0 0030      add $0030, r0
14e4: 0083           rts r3
14e6: 65c4 0008      add $0008, r4
14ea: 95d3 003f      movb $003f, (r3)+
14ee: 0087           rts pc
14f0: 1166           mov r5, -(sp)
14f2: 1185           mov sp, r5
14f4: 1dc0 16dc      mov 2bd4, r0
14f8: 0204           bne
14fa: 09f7 002c      jsr pc, 152a
14fe: 1dc0 16d2      mov 2bd4, r0
1502: 9d50 0004      movb 4(r5), (r0)+
1506: 0307           beq
1508: 0ab7 16c8      inc 2bd4
150c: 0af7 16c2      dec 2bd2
1510: 0602           bgt
1512: 09f7 0014      jsr pc, 152a
1516: 1d40 0004      mov 4(r5), r0
151a: 1585           mov (sp)+, r5
151c: 0087           rts pc
151e: 1166           mov r5, -(sp)
1520: 1185           mov sp, r5
1522: 09f7 0004      jsr pc, 152a
1526: 1585           mov (sp)+, r5
1528: 0087           rts pc
152a: 1dc0 16a6      mov 2bd4, r0
152e: 030a           beq
1530: e5c0 2bd6      sub $2bd6, r0
1534: 1037 0722      mov r0, 1c5a
1538: 1dc0 1694      mov 2bd0, r0
153c: 0201           bne
153e: 0a80           inc r0
1540: 8900           sys 0000
1542: 1c56 15f7      mov 15f7(r1), (sp)+
1546: 2bd6           cmp *-(pc), (sp)+
1548: 168a           mov *(r2)+, (r2)
154a: 15f7 0200 1682 mov $0200, 2bd2
1550: 2dd7 167c 0002 cmp 2bd0, $0002
1556: 8203           bhi
1558: 15f7 0001 1674 mov $0001, 2bd2
155e: 0087           rts pc
1560: 1166           mov r5, -(sp)
1562: 1185           mov sp, r5
1564: 1d40 0004      mov 4(r5), r0
1568: 8906           sys 0006
156a: 8602           bcc
156c: 0077 03e8      jmp 1958
1570: 0a00           clr r0
1572: 1585           mov (sp)+, r5
1574: 0087           rts pc
1576: 1166           mov r5, -(sp)
1578: 1185           mov sp, r5
157a: 1d77 0004 06de mov 4(r5), 1c5e
1580: 1d77 0006 06da mov 6(r5), 1c60
1586: 8900           sys 0000
1588: 1c5c 8602      mov -79fe(r1), *(r4)+
158c: 0077 03c8      jmp 1958
1590: 1585           mov (sp)+, r5
1592: 0087           rts pc
1594: 1166           mov r5, -(sp)
1596: 1185           mov sp, r5
1598: 1d77 0004 06c6 mov 4(r5), 1c64
159e: 1d77 0006 06c2 mov 6(r5), 1c66
15a4: 0bf7 1618      tst 2bc0
15a8: 0305           beq
15aa: 15e6 f010      mov $f010, -(sp)
15ae: 15e6 15b4      mov $15b4, -(sp)
15b2: 0006           rtt
15b4: 8900           sys 0000
15b6: 1c62 0077      mov 77(r1), -(r2)
15ba: 039c           beq
15bc: 1166           mov r5, -(sp)
15be: 1185           mov sp, r5
15c0: 8902           sys 0002
15c2: 0103           br
15c4: 8605           bcc
15c6: 0077 038e      jmp 1958
15ca: 1037 1808      mov r0, 2dd6
15ce: 0a00           clr r0
15d0: 1585           mov (sp)+, r5
15d2: 0087           rts pc
15d4: 1166           mov r5, -(sp)
15d6: 1185           mov sp, r5
15d8: 1d77 0004 068c mov 4(r5), 1c6a
15de: 8900           sys 0000
15e0: 1c68 874a      mov -78b6(r1), *-(r0)
15e4: 1d41 0006      mov 6(r5), r1
15e8: 1011           mov r0, (r1)+
15ea: 0a11           clr (r1)+
15ec: 0a00           clr r0
15ee: 1585           mov (sp)+, r5
15f0: 0087           rts pc
15f2: 0a37 15cc      clr 2bc2
15f6: 1166           mov r5, -(sp)
15f8: 1185           mov sp, r5
15fa: 1d41 0004      mov 4(r5), r1
15fe: e5f1 0002 0002 sub $0002, 2(r1)
1604: 040f           bge
1606: 2c57 0002 ffff cmp 2(r1), $ffff
160c: 0507           blt
160e: 9e66 0004      movb *4(r1), -(sp)
1612: 09f7 0042      jsr pc, 1658
1616: 1c40 0004      mov 4(r1), r0
161a: 0107           br
161c: 09f7 0038      jsr pc, 1658
1620: 0af1 0002      dec 2(r1)
1624: 1c40 0004      mov 4(r1), r0
1628: 9426           movb (r0)+, -(sp)
162a: 9436 0001      movb (r0)+, 1(sp)
162e: 1031 0004      mov r0, 4(r1)
1632: 1580           mov (sp)+, r0
1634: 1585           mov (sp)+, r5
1636: 0087           rts pc
1638: 1166           mov r5, -(sp)
163a: 1185           mov sp, r5
163c: 1d41 0004      mov 4(r5), r1
1640: 0af1 0002      dec 2(r1)
1644: 0402           bge
1646: 09f7 000e      jsr pc, 1658
164a: 0a00           clr r0
164c: de40 0004      bisb *4(r1), r0
1650: 0ab1 0004      inc 4(r1)
1654: 1585           mov (sp)+, r5
1656: 0087           rts pc
1658: 1040           mov r1, r0
165a: 65c0 0006      add $0006, r0
165e: 1037 060e      mov r0, 1c70
1662: 1031 0004      mov r0, 4(r1)
1666: 1240           mov (r1), r0
1668: 8900           sys 0000
166a: 1c6e 8705      mov -78fb(r1), *-(sp)
166e: 0ac0           dec r0
1670: 8103           bmi
1672: 1031 0002      mov r0, 2(r1)
1676: 0087           rts pc
1678: 0077 02dc      jmp 1958
167c: 1166           mov r5, -(sp)
167e: 1185           mov sp, r5
1680: 1d77 0004 05f0 mov 4(r5), 1c76
1686: 1d77 0006 05ec mov 6(r5), 1c78
168c: 8900           sys 0000
168e: 1c74 8602 0077 mov -79fe(r1), 77(r4)
1694: 02c2           bne
1696: 0a00           clr r0
1698: 1585           mov (sp)+, r5
169a: 0087           rts pc
169c: 1166           mov r5, -(sp)
169e: 1185           mov sp, r5
16a0: 1d77 0004 05d6 mov 4(r5), 1c7c
16a6: 1d77 0006 05d2 mov 6(r5), 1c7e
16ac: 8900           sys 0000
16ae: 1c7a 8602 0077 mov -79fe(r1), *77(r2)
16b4: 02a2           bne
16b6: 1585           mov (sp)+, r5
16b8: 0087           rts pc
16ba: 1166           mov r5, -(sp)
16bc: 1185           mov sp, r5
16be: 1d77 0004 05be mov 4(r5), 1c82
16c4: 1d41 0006      mov 6(r5), r1
16c8: 11c9           mov pc, (r1)
16ca: 8900           sys 0000
16cc: 1c80 8751      mov -78af(r2), r0
16d0: 1011           mov r0, (r1)+
16d2: 0a11           clr (r1)+
16d4: 0a11           clr (r1)+
16d6: 014f           br
16d8: 1166           mov r5, -(sp)
16da: 1185           mov sp, r5
16dc: 1d41 0006      mov 6(r5), r1
16e0: 0af1 0002      dec 2(r1)
16e4: 0404           bge
16e6: 09f7 005e      jsr pc, 1748
16ea: 0af1 0002      dec 2(r1)
16ee: 9d79 0004 0004 movb 4(r5), *4(r1)
16f4: 0ab1 0004      inc 4(r1)
16f8: 0af1 0002      dec 2(r1)
16fc: 0404           bge
16fe: 09f7 0046      jsr pc, 1748
1702: 0af1 0002      dec 2(r1)
1706: 9d79 0005 0004 movb 5(r5), *4(r1)
170c: 0ab1 0004      inc 4(r1)
1710: 1d40 0004      mov 4(r5), r0
1714: 0130           br
1716: 1166           mov r5, -(sp)
1718: 1185           mov sp, r5
171a: 1d41 0006      mov 6(r5), r1
171e: 0af1 0002      dec 2(r1)
1722: 0404           bge
1724: 09f7 0020      jsr pc, 1748
1728: 0af1 0002      dec 2(r1)
172c: 1d40 0004      mov 4(r5), r0
1730: 9039 0004      movb r0, *4(r1)
1734: 0ab1 0004      inc 4(r1)
1738: 011e           br
173a: 1166           mov r5, -(sp)
173c: 1185           mov sp, r5
173e: 1d41 0004      mov 4(r5), r1
1742: 09f7 0002      jsr pc, 1748
1746: 0117           br
1748: 1040           mov r1, r0
174a: 65c0 0006      add $0006, r0
174e: 1026           mov r0, -(sp)
1750: 1037 0534      mov r0, 1c88
1754: 1c77 0004 0530 mov 4(r1), 1c8a
175a: 0305           beq
175c: e037 052a      sub r0, 1c8a
1760: 1240           mov (r1), r0
1762: 8900           sys 0000
1764: 1c86 15b1      mov 15b1(r2), sp
1768: 0004           iot
176a: 15f1 0200 0002 mov $0200, 2(r1)
1770: 0087           rts pc
1772: 0077 01e2      jmp 1958
1776: 0a37 1448      clr 2bc2
177a: 1585           mov (sp)+, r5
177c: 0087           rts pc
177e: 1166           mov r5, -(sp)
1780: 1185           mov sp, r5
1782: 1d41 0004      mov 4(r5), r1
1786: 2057 0014      cmp r1, $0014
178a: 861f           bcc
178c: 1d40 0006      mov 6(r5), r0
1790: 1077 04fa      mov r1, 1c8e
1794: 0cc1           asl r1
1796: 1c66 2dd8      mov 2dd8(r1), -(sp)
179a: 1031 2dd8      mov r0, 2dd8(r1)
179e: 1037 04ee      mov r0, 1c90
17a2: 0309           beq
17a4: 35c0 0001      bit $0001, r0
17a8: 0206           bne
17aa: 0cc1           asl r1
17ac: 0cc1           asl r1
17ae: 65c1 17d6      add $17d6, r1
17b2: 1077 04da      mov r1, 1c90
17b6: 8900           sys 0000
17b8: 1c8c 870a      mov -78f6(r2), (r4)
17bc: 35c0 0001      bit $0001, r0
17c0: 0301           beq
17c2: 100e           mov r0, (sp)
17c4: 1580           mov (sp)+, r0
17c6: 1585           mov (sp)+, r5
17c8: 0087           rts pc
17ca: 15c0 0016      mov $0016, r0
17ce: 0a26           clr -(sp)
17d0: 0bd6           tst (sp)+
17d2: 0077 0182      jmp 1958
17d6: 1026           mov r0, -(sp)
17d8: 1dc0 15fc      mov 2dd8, r0
17dc: 014c           br
17de: 1026           mov r0, -(sp)
17e0: 1dc0 15f6      mov 2dda, r0
17e4: 0148           br
17e6: 1026           mov r0, -(sp)
17e8: 1dc0 15f0      mov 2ddc, r0
17ec: 0144           br
17ee: 1026           mov r0, -(sp)
17f0: 1dc0 15ea      mov 2dde, r0
17f4: 0140           br
17f6: 1026           mov r0, -(sp)
17f8: 1dc0 15e4      mov 2de0, r0
17fc: 013c           br
17fe: 1026           mov r0, -(sp)
1800: 1dc0 15de      mov 2de2, r0
1804: 0138           br
1806: 1026           mov r0, -(sp)
1808: 1dc0 15d8      mov 2de4, r0
180c: 0134           br
180e: 1026           mov r0, -(sp)
1810: 1dc0 15d2      mov 2de6, r0
1814: 0130           br
1816: 1026           mov r0, -(sp)
1818: 1dc0 15cc      mov 2de8, r0
181c: 012c           br
181e: 1026           mov r0, -(sp)
1820: 1dc0 15c6      mov 2dea, r0
1824: 0128           br
1826: 1026           mov r0, -(sp)
1828: 1dc0 15c0      mov 2dec, r0
182c: 0124           br
182e: 1026           mov r0, -(sp)
1830: 1dc0 15ba      mov 2dee, r0
1834: 0120           br
1836: 1026           mov r0, -(sp)
1838: 1dc0 15b4      mov 2df0, r0
183c: 011c           br
183e: 1026           mov r0, -(sp)
1840: 1dc0 15ae      mov 2df2, r0
1844: 0118           br
1846: 1026           mov r0, -(sp)
1848: 1dc0 15a8      mov 2df4, r0
184c: 0114           br
184e: 1026           mov r0, -(sp)
1850: 1dc0 15a2      mov 2df6, r0
1854: 0110           br
1856: 1026           mov r0, -(sp)
1858: 1dc0 159c      mov 2df8, r0
185c: 010c           br
185e: 1026           mov r0, -(sp)
1860: 1dc0 1596      mov 2dfa, r0
1864: 0108           br
1866: 1026           mov r0, -(sp)
1868: 1dc0 1590      mov 2dfc, r0
186c: 0104           br
186e: 1026           mov r0, -(sp)
1870: 1dc0 158a      mov 2dfe, r0
1874: 0100           br
1876: 1066           mov r1, -(sp)
1878: 10a6           mov r2, -(sp)
187a: 10e6           mov r3, -(sp)
187c: 1126           mov r4, -(sp)
187e: 09c8           jsr pc, (r0)
1880: 1584           mov (sp)+, r4
1882: 1583           mov (sp)+, r3
1884: 1582           mov (sp)+, r2
1886: 1581           mov (sp)+, r1
1888: 1580           mov (sp)+, r0
188a: 0006           rtt
188c: 1166           mov r5, -(sp)
188e: 1185           mov sp, r5
1890: 1d77 0004 03fe mov 4(r5), 1c94
1896: 8900           sys 0000
1898: 1c92 8602      mov -79fe(r2), (r2)+
189c: 0077 00b8      jmp 1958
18a0: 0a00           clr r0
18a2: 1585           mov (sp)+, r5
18a4: 0087           rts pc
18a6: 1166           mov r5, -(sp)
18a8: 1185           mov sp, r5
18aa: 09f7 0022      jsr pc, 18d0
18ae: 1026           mov r0, -(sp)
18b0: 8907           sys 0007
18b2: 8603           bcc
18b4: 0bd6           tst (sp)+
18b6: 0077 009e      jmp 1958
18ba: 0bd6           tst (sp)+
18bc: 0302           beq
18be: 107d 0004      mov r1, *4(r5)
18c2: 1585           mov (sp)+, r5
18c4: 0087           rts pc
18c6: 1166           mov r5, -(sp)
18c8: 1185           mov sp, r5
18ca: 1d40 0004      mov 4(r5), r0
18ce: 8901           sys 0001
18d0: 1166           mov r5, -(sp)
18d2: 1d41 0002      mov 2(r5), r1
18d6: 1185           mov sp, r5
18d8: 0a00           clr r0
18da: 2c77 fffc 03b6 cmp -4(r1), 1c96
18e0: 0202           bne
18e2: 15c0 0002      mov $0002, r0
18e6: 2277 03b0      cmp (r1), 1c9a
18ea: 0203           bne
18ec: 65c0 0002      add $0002, r0
18f0: 0122           br
18f2: 2277 03a6      cmp (r1), 1c9c
18f6: 0203           bne
18f8: 65c0 0004      add $0004, r0
18fc: 011c           br
18fe: 2277 039c      cmp (r1), 1c9e
1902: 0203           bne
1904: 6c40 0002      add 2(r1), r0
1908: 0116           br
190a: 2277 0394      cmp (r1), 1ca2
190e: 0205           bne
1910: 6c41 0002      add 2(r1), r1
1914: 65c1 0004      add $0004, r1
1918: 01e6           br
191a: ac77 0001 0387 cmpb 1(r1), 1ca7
1920: 020a           bne
1922: 1026           mov r0, -(sp)
1924: 1240           mov (r1), r0
1926: 00c0           swab r0
1928: 7417 fff9      ash r0, $fff9
192c: 6001           add r0, r1
192e: 65c1 0002      add $0002, r1
1932: 1580           mov (sp)+, r0
1934: 01d8           br
1936: 0c80           asr r0
1938: 1585           mov (sp)+, r5
193a: 0087           rts pc
193c: 1140           mov r5, r0
193e: 1185           mov sp, r5
1940: 1126           mov r4, -(sp)
1942: 10e6           mov r3, -(sp)
1944: 10a6           mov r2, -(sp)
1946: 0be6           tst -(sp)
1948: 0048           jmp (r0)
194a: 1141           mov r5, r1
194c: 1844           mov -(r1), r4
194e: 1843           mov -(r1), r3
1950: 1842           mov -(r1), r2
1952: 1146           mov r5, sp
1954: 1585           mov (sp)+, r5
1956: 0087           rts pc
1958: 1037 1266      mov r0, 2bc2
195c: 15c0 ffff      mov $ffff, r0
1960: 1146           mov r5, sp
1962: 1585           mov (sp)+, r5
1964: 0087           rts pc
1966: 2484           cmp (r2)+, r4
1968: 00c8           swab (r0)
196a: 19b2 19ba      mov -(sp), 19ba(r2)
196e: 19c2           mov -(pc), r2
1970: 19ca           mov -(pc), (r2)
1972: 1978 1984      mov -(r5), *1984(r0)
1976: 198c           mov -(sp), (r4)
1978: 0000           halt
197a: 0019           wait
197c: 0028           halt
197e: 0033           bpt
1980: 0038           halt
1982: 003a           rti
1984: 0000           halt
1986: 0027           (undefined)
1988: 0029           wait
198a: 0031           wait
198c: 006e           jmp *-(sp)
198e: 00aa           clnv
1990: 008c           (undefined)
1992: 0096           (undefined)
1994: 0080           rts r0
1996: 00d2           swab (r2)+
1998: 006e           jmp *-(sp)
199a: 007a 0070      jmp *70(r2)
199e: 0090           (undefined)
19a0: 0000           halt
19a2: 000a           rti
19a4: 002a           rti
19a6: 0000           halt
19a8: 0b38 0b4a      neg *b4a(r0)
19ac: 0b3c 0b78      neg *b78(r4)
19b0: 29ca           cmp -(pc), (r2)
19b2: 6c2f 6269      add 6269(r0), *-(pc)
19b6: 632f           add (r4), *-(pc)
19b8: 0030           halt
19ba: 6c2f 6269      add 6269(r0), *-(pc)
19be: 632f           add (r4), *-(pc)
19c0: 0031           wait
19c2: 6c2f 6269      add 6269(r0), *-(pc)
19c6: 632f           add (r4), *-(pc)
19c8: 0032           rti
19ca: 6c2f 6269      add 6269(r0), *-(pc)
19ce: 632f           add (r4), *-(pc)
19d0: 7472 2e30      ash r1, 2e30(r2)
19d4: 006f           jmp *-(pc)
19d6: 6c2f 6269      add 6269(r0), *-(pc)
19da: 6d2f 7263      add 7263(r4), *-(pc)
19de: 3074 6f2e      bit r1, 6f2e(r4)
19e2: 2f00 696c      cmp *696c(r4), r0
19e6: 2f62 6366      cmp *6366(r5), -(r2)
19ea: 7472 2e30      ash r1, 2e30(r2)
19ee: 006f           jmp *-(pc)
19f0: 6c2f 6269      add 6269(r0), *-(pc)
19f4: 662f           add *(r0)+, *-(pc)
19f6: 3063           bit r1, -(r3)
19f8: 2f00 696c      cmp *696c(r4), r0
19fc: 2f62 6366      cmp *6366(r5), -(r2)
1a00: 0031           wait
1a02: 6c2f 6269      add 6269(r0), *-(pc)
1a06: 632f           add (r4), *-(pc)
1a08: 7472 2e32      ash r1, 2e32(r2)
1a0c: 006f           jmp *-(pc)
1a0e: 6c2f 6269      add 6269(r0), *-(pc)
1a12: 632f           add (r4), *-(pc)
1a14: 7472 3032      ash r1, 3032(r2)
1a18: 6f2e 2f00      add *2f00(r4), *-(sp)
1a1c: 7375 2f72      div r5, 2f72(r5)
1a20: 2f63 3063      cmp *3063(r5), -(r3)
1a24: 2f00 7375      cmp *7375(r4), r0
1a28: 2f72 2f63 3163 cmp *2f63(r5), 3163(r2)
1a2e: 2f00 7375      cmp *7375(r4), r0
1a32: 2f72 2f63 3263 cmp *2f63(r5), 3263(r2)
1a38: 2f00 6d74      cmp *6d74(r4), r0
1a3c: 2f70 7463 306d cmp *7463(r5), 306d(r0)
1a42: 0061           jmp -(r1)
1a44: 7325           div r4, -(r5)
1a46: 0a3a 6300      clr *6300(r2)
1a4a: 0030           halt
1a4c: 502d           bis r0, *-(r5)
1a4e: 6300           add (r4), r0
1a50: 0031           wait
1a52: 3263           bit (r1), -(r3)
1a54: 6100           add r4, r0
1a56: 0073 002d      jmp 2d(r3)
1a5a: 622f           add (r0), *-(pc)
1a5c: 6e69 612f      add *612f(r1), *-(r1)
1a60: 0073 2e61      jmp 2e61(r3)
1a64: 756f           ash r5, *-(pc)
1a66: 0074 2e61      jmp 2e61(r4)
1a6a: 756f           ash r5, *-(pc)
1a6c: 0074 6f6d      jmp 6f6d(r4)
1a70: 6576 6620      add (r5)+, 6620(sp)
1a74: 6961           add -(r5), -(r1)
1a76: 656c           add (r5)+, *-(r4)
1a78: 3a64           bit *-(r1), -(r4)
1a7a: 2520           cmp (r4)+, -(r0)
1a7c: 0a73 6c00      com 6c00(r3)
1a80: 0064           jmp -(r4)
1a82: 582d           bis -(r0), *-(r5)
1a84: 2d00 326c      cmp 326c(r4), r0
1a88: 2d00 636c      cmp 636c(r4), r0
1a8c: 2d00 006c      cmp 6c(r4), r0
1a90: 622f           add (r0), *-(pc)
1a92: 6e69 6c2f      add *6c2f(r1), *-(r1)
1a96: 0064           jmp -(r4)
1a98: 6564           add (r5)+, -(r4)
1a9a: 6966           add -(r5), -(sp)
1a9c: 656e           add (r5)+, *-(sp)
1a9e: 6900           add -(r4), r0
1aa0: 636e           add (r5), *-(sp)
1aa2: 756c           ash r5, *-(r4)
1aa4: 6564           add (r5)+, -(r4)
1aa6: 6500           add (r4)+, r0
1aa8: 646e           add (r1)+, *-(sp)
1aaa: 6669           add *(r1)+, *-(r1)
1aac: 6900           add -(r4), r0
1aae: 6466           add (r1)+, -(sp)
1ab0: 6665           add *(r1)+, -(r5)
1ab2: 6900           add -(r4), r0
1ab4: 6e66 6564      add *6564(r1), -(sp)
1ab8: 0066           jmp -(sp)
1aba: 6e75 7869 4300 add *7869(r1), 4300(r5)
1ac0: 6e61 7427      add *7427(r1), -(r1)
1ac4: 6320           add (r4), -(r0)
1ac6: 6572 7461      add (r5)+, 7461(r2)
1aca: 2520           cmp (r4)+, -(r0)
1acc: 0a73 4900      com 4900(r3)
1ad0: 2d66 656c      cmp 656c(r5), -(sp)
1ad4: 7373 6520      div r5, 6520(r3)
1ad8: 646e           add (r1)+, *-(sp)
1ada: 6669           add *(r1)+, *-(r1)
1adc: 5500           bis (r4)+, r0
1ade: 646e           add (r1)+, *-(sp)
1ae0: 6665           add *(r1)+, -(r5)
1ae2: 6e69 6465      add *6465(r1), *-(r1)
1ae6: 6320           add (r4), -(r0)
1ae8: 6e6f 7274      add *7274(r1), *-(pc)
1aec: 6c6f 4e00      add 4e00(r1), *-(pc)
1af0: 7365           div r5, -(r5)
1af2: 6574 2064      add (r5)+, 2064(r4)
1af6: 6927           add -(r4), -(pc)
1af8: 636e           add (r5), *-(sp)
1afa: 756c           ash r5, *-(r4)
1afc: 6564           add (r5)+, -(r4)
1afe: 0027           (undefined)
1b00: 694d           add -(r5), (r5)
1b02: 7373 6e69      div r5, 6e69(r3)
1b06: 2067           cmp r1, -(pc)
1b08: 6966           add -(r5), -(sp)
1b0a: 656c           add (r5)+, *-(r4)
1b0c: 2520           cmp (r4)+, -(r0)
1b0e: 0073 6f43      jmp 6f43(r3)
1b12: 746e           ash r1, *-(sp)
1b14: 6f72 206c 7973 add *206c(r5), 7973(r2)
1b1a: 746e           ash r1, *-(sp)
1b1c: 7861           xor r1, -(r1)
1b1e: 2500           cmp (r4)+, r0
1b20: 3a64           bit *-(r1), -(r4)
1b22: 0020           halt
1b24: 694c           add -(r5), (r4)
1b26: 656e           add (r5)+, *-(sp)
1b28: 6f20 6576      add *6576(r4), -(r0)
1b2c: 6672 6f6c      add *(r1)+, 6f6c(r2)
1b30: 0077 6f54      jmp 8a88
1b34: 206f           cmp r1, *-(pc)
1b36: 756d           ash r5, *-(r5)
1b38: 6863           add -(r1), -(r3)
1b3a: 6420           add (r0)+, -(r0)
1b3c: 6665           add *(r1)+, -(r5)
1b3e: 6e69 6e69      add *6e69(r1), *-(r1)
1b42: 0067           jmp -(pc)
1b44: 6f74 206f 616d add *206f(r5), 616d(r4)
1b4a: 796e           xor r5, *-(sp)
1b4c: 6420           add (r0)+, -(r0)
1b4e: 6665           add *(r1)+, -(r5)
1b50: 6e69 7365      add *7365(r1), *-(r1)
1b54: 4500           bic (r4)+, r0
1b56: 6378 7365      add (r5), *7365(r0)
1b5a: 6973 6576      add -(r5), 6576(r3)
1b5e: 6420           add (r0)+, -(r0)
1b60: 6665           add *(r1)+, -(r5)
1b62: 6e69 2065      add *2065(r1), *-(r1)
1b66: 6f6c 706f      add *706f(r5), *-(r4)
1b6a: 6e69 0067      add *67(r1), *-(r1)
1b6e: 6564           add (r5)+, -(r4)
1b70: 6966           add -(r5), -(sp)
1b72: 656e           add (r5)+, *-(sp)
1b74: 7220           div r0, -(r0)
1b76: 6365           add (r5), -(r5)
1b78: 7275 6973      div r1, 6973(r5)
1b7c: 6e6f 6c20      add *6c20(r1), *-(pc)
1b80: 6f6f 0a70      add *a70(r5), *-(pc)
1b84: 4300           bic (r4), r0
1b86: 6e61 7427      add *7427(r1), -(r1)
1b8a: 6620           add *(r0)+, -(r0)
1b8c: 6e69 2064      add *2064(r1), *-(r1)
1b90: 7325           div r4, -(r5)
1b92: 000a           rti
1b94: 7254           div r1, (r4)+
1b96: 2079 6761      cmp r1, *6761(r1)
1b9a: 6961           add -(r5), -(r1)
1b9c: 0a6e           com *-(sp)
1b9e: 4600           bic *(r0)+, r0
1ba0: 7461           ash r1, -(r1)
1ba2: 6c61 6520      add 6520(r1), -(r1)
1ba6: 7272 726f      div r1, 726f(r2)
1baa: 6920           add -(r4), -(r0)
1bac: 206e           cmp r1, *-(sp)
1bae: 7325           div r4, -(r5)
1bb0: 000a           rti
1bb2: 6564           add (r5)+, -(r4)
1bb4: 6966           add -(r5), -(sp)
1bb6: 656e           add (r5)+, *-(sp)
1bb8: 2064           cmp r1, -(r4)
1bba: 7566           ash r5, -(sp)
1bbc: 636e           add (r5), *-(sp)
1bbe: 6974 6e6f      add -(r5), 6e6f(r4)
1bc2: 7220           div r0, -(r0)
1bc4: 7165           mul r5, -(r5)
1bc6: 6975 6572      add -(r5), 6572(r5)
1bca: 2073 7261      cmp r1, 7261(r3)
1bce: 7567           ash r5, -(pc)
1bd0: 656d           add (r5)+, *-(r5)
1bd2: 746e           ash r1, *-(sp)
1bd4: 0073 6564      jmp 6564(r3)
1bd8: 6966           add -(r5), -(sp)
1bda: 656e           add (r5)+, *-(sp)
1bdc: 6120           add r4, -(r0)
1bde: 6772 6d75      add *(r5)+, 6d75(r2)
1be2: 6e65 2074      add *2074(r1), -(r5)
1be6: 696d           add -(r5), *-(r5)
1be8: 6d73 7461 6863 add 7461(r5), 6863(r3)
1bee: 6400           add (r0)+, r0
1bf0: 6665           add *(r1)+, -(r5)
1bf2: 6e69 2065      add *2065(r1), *-(r1)
1bf6: 7270 746f      div r1, 746f(r0)
1bfa: 746f           ash r1, *-(pc)
1bfc: 7079 2065      mul r1, *2065(r1)
1c00: 7261           div r1, -(r1)
1c02: 7567           ash r5, -(pc)
1c04: 656d           add (r5)+, *-(r5)
1c06: 746e           ash r1, *-(sp)
1c08: 6520           add (r4)+, -(r0)
1c0a: 7272 726f      div r1, 726f(r2)
1c0e: 6e00 6e6f      add *6e6f(r0), r0
1c12: 742d           ash r0, *-(r5)
1c14: 7265           div r1, -(r5)
1c16: 696d           add -(r5), *-(r5)
1c18: 616e           add r5, *-(sp)
1c1a: 6574 2064      add (r5)+, 2064(r4)
1c1e: 7473 6972      ash r1, 6972(r3)
1c22: 676e           add *(r5)+, *-(sp)
1c24: 0000           halt
1c26: 13b4 0064      mov (sp), 64(r4)
1c2a: 140a           mov (r0)+, (r2)
1c2c: 006f           jmp *-(pc)
1c2e: 1404           mov (r0)+, r4
1c30: 0078 1446      jmp *1446(r0)
1c34: 0066           jmp -(sp)
1c36: 1454           mov (r1)+, (r4)+
1c38: 0065           jmp -(r5)
1c3a: 13e2           mov (pc), -(r2)
1c3c: 0063           jmp -(r3)
1c3e: 13f0 0073      mov (pc), 73(r0)
1c42: 13c0           mov (pc), r0
1c44: 006c           jmp *-(r4)
1c46: 1462           mov (r1)+, -(r2)
1c48: 0072 0000      jmp 0(r2)
1c4c: 0000           halt
1c4e: fffc           (undefined)
1c50: fff0           (undefined)
1c52: fffd           (undefined)
1c54: fff8           (undefined)
1c56: 8904           sys 0004
1c58: 2bd6           cmp *-(pc), (sp)+
1c5a: 0000           halt
1c5c: 8908           sys 0008
1c5e: 0000           halt
1c60: 0000           halt
1c62: 890b           sys 000b
1c64: 0000           halt
1c66: 0000           halt
1c68: 8905           sys 0005
1c6a: 0000           halt
1c6c: 0000           halt
1c6e: 8903           sys 0003
1c70: 0000           halt
1c72: 0200           bne
1c74: 8909           sys 0009
1c76: 0000           halt
1c78: 0000           halt
1c7a: 8905           sys 0005
1c7c: 0000           halt
1c7e: 0000           halt
1c80: 8908           sys 0008
1c82: 0000           halt
1c84: 01b6           br
1c86: 8904           sys 0004
1c88: 0000           halt
1c8a: 0000           halt
1c8c: 8930           sys 0030
1c8e: 0000           halt
1c90: 0000           halt
1c92: 890a           sys 000a
1c94: 0000           halt
1c96: 09df 0000      jsr pc, *$0000
1c9a: 0bd6           tst (sp)+
1c9c: 2596           cmp (sp)+, (sp)+
1c9e: 65c6 0000      add $0000, sp
1ca2: 0077 e35a      jmp 0000
1ca6: 01ff           br
undefined: 9
