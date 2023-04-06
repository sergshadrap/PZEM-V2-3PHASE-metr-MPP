# PZEM-V2-3PHASE-metr-MPP 
AM System related PZEM V2 3PHASE electricity metr 
It's been designed for using with PZEM V2 old modules , for 3 phase AC metr and reporting to AM Server.
The V2 and V3 are relatively different modules. V3 is aka Mod-Bus , V2 is pure Serial 9600 bps interface. 
The module reads 4 values from 3 PZEM module (1 per phase) for voltage,Current,Power and consumed Energy (kWt).
These module are quite slow , they could respond not often than 1 time per second , doesn't matter what parameter .
Therefore you need at least 12 second for quering 12 parameters .
