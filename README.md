# PZEM-V2-3PHASE-metr-MPP 
AM System related PZEM V2 3PHASE electricity metr 
It's been designed for using with PZEM V2 old modules , for 3 phase AC metr and reporting to AM Server.
The V2 and V3 are relatively different modules. V3 is aka Mod-Bus , V2 is pure Serial 9600 bps interface. 
The module reads 4 values from 3 PZEM module (1 per phase) for voltage,Current,Power and consumed Energy (kWt).
These module are quite slow , they could respond not often than 1 time per second , doesn't matter what parameter .
Therefore you need at least 12 second for quering 12 parameters .
Works with 3 different Software Serial ports :

PZEM004T pzem1(4, 5);    //D1,D2  Wemos D1 Mini              L1

PZEM004T pzem2(2, 0);    //D4,D3                             L2

PZEM004T pzem3(12, 14);  //D5,D6                             L3 

It's possible to work over one port , but this configuration turns to be more reliable with data reading.
