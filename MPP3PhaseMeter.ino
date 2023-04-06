#include <Arduino.h>
#include <ESP.h>
#include <ESP8266WiFi.h>
//#include <SoftwareSerial.h>
#include <MppServer.h>
#include <MppDevice.h>
#include <MppHTTPCLient.h>
#include <stdio.h>
#include "PZEM004T.h"

const char *DeviceVersion = "MppPZEM 3.0.1";
static const char *P_PERIOD = "Period"; // Period - the frequency to read the analog input in sconds



static const char *properties[] = { //
        P_PERIOD, //
        NULL };
MppServer mppServer(DeviceVersion, properties);
class MppDevice volt1,volt2,volt3;
class MppDevice curr1,curr2,curr3;
class MppDevice powr1,powr2,powr3;
class MppDevice ener1,ener2,ener3;
class MppDevice totalpow,totalener;

IPAddress ip1(192,168,1,1);
IPAddress ip2(192,168,1,2);
IPAddress ip3(192,168,1,3);

unsigned long next,next250 = millis();

//PZEM004T pzem(14,12);  //SoftwareSerial(receivePin, transmitPin);

PZEM004T pzem1(4, 5);    //D1,D2  Wemos D1 Mini              L1
PZEM004T pzem2(2, 0);    //D4,D3                             L2
PZEM004T pzem3(12, 14);  //D5,D6                             L3 

void setup() {
  Serial.begin(115200);
  mppServer.setPropertyDefault(P_PERIOD, "10000");

  mppServer.manageDevice(&volt1, getDefaultUDN(MppAnalog)+"V1");
  mppServer.manageDevice(&volt2, getDefaultUDN(MppAnalog)+"V2");
  mppServer.manageDevice(&volt3, getDefaultUDN(MppAnalog)+"V3");
  
  mppServer.manageDevice(&curr1, getDefaultUDN(MppAnalog)+"I1");
  mppServer.manageDevice(&curr2, getDefaultUDN(MppAnalog)+"I2");
  mppServer.manageDevice(&curr3, getDefaultUDN(MppAnalog)+"I3");
  
  mppServer.manageDevice(&powr1, getDefaultUDN(MppAnalog)+"P1");
  mppServer.manageDevice(&powr2, getDefaultUDN(MppAnalog)+"P2");
  mppServer.manageDevice(&powr3, getDefaultUDN(MppAnalog)+"P3");
  
  mppServer.manageDevice(&ener1, getDefaultUDN(MppAnalog)+"E1");
  mppServer.manageDevice(&ener2, getDefaultUDN(MppAnalog)+"E2");
  mppServer.manageDevice(&ener3, getDefaultUDN(MppAnalog)+"E3");

   mppServer.manageDevice(&totalpow, getDefaultUDN(MppAnalog)+"P");
    mppServer.manageDevice(&totalener, getDefaultUDN(MppAnalog)+"E");
    
  Serial.printf("\nMppServer booting: %s, mode=%d, version=%d\n",
      ESP.getResetReason().c_str(), ESP.getBootMode(),
      ESP.getBootVersion());


      mppServer.begin();

}
 int Ncycle=0;
 float v1,v2,v3,i1,i2,i3,p1,p2,p3,e1,e2,e3,v,i,p,e=0; // declare it globally 
 
void loop() {
   bool notify;
  unsigned long now= millis();
  unsigned long LstRd;
 
 // float v1,v2,v3,i1,i2,i3,p1,p2,p3,e1,e2,e3,v,i,p,e;

  mppServer.handleClients(); // let the server handle any incoming requests
 mppServer.handleCommand(); // optional, handle user Serial input 

 if( millis() - LstRd > 1000)  {       //read each PZEMs parametr not often every 1s
   switch (Ncycle) {
      case 1:
    v1 = pzem1.voltage(ip1);
//    Serial.printf("Case number1 F1 Voltage :%.2fV\n",v1);
    break;
      case 2:
     i1 = pzem1.current(ip1);
//     Serial.printf("Case number2 F1 Current :%.2fA\n",i1);
     break;
      case 3:
       p1 = pzem1.power(ip1);
       break;
       case 4:
         e1= pzem1.energy(ip1);
         break;
  case 5:        
    v2 = pzem2.voltage(ip2);
    break;
  case 6:  
     i2 = pzem2.current(ip2);
     break;
  case 7: 
       p2 = pzem2.power(ip2);
       break;
  case 8:     
        e2= pzem2.energy(ip2);
        break;
  case 9:    
    v3 = pzem3.voltage(ip3);
    break;
     i3 = pzem3.current(ip3);
  case 10:   
       p3 = pzem3.power(ip3);
       break;
  case 11:
         e3= pzem3.energy(ip3); 
         break;
default:
      Ncycle=0;
      LstRd=0;
   }              
         Serial.flush(); 
         Ncycle++; LstRd = millis();
         
 }
  if (now > next) {
  

       if( v1!=PZEM_ERROR_VALUE || i1!=PZEM_ERROR_VALUE ){
        Serial.printf("F1 Voltage :%.2fV  Current:%.2fA Power:%.2fW Energy:%.2fkWt\n",v1,i1,p1,e1); 
        notify=volt1.put(VALUE,String(v1)); notify=volt1.put(STATE,"on"); 
        notify=curr1.put(VALUE,String(i1)); notify=curr1.put(STATE,"on");
        notify=powr1.put(VALUE,String(p1)); notify=powr1.put(STATE,"on");
        notify=ener1.put(VALUE,String(e1)); notify=ener1.put(STATE,"on");
    } else {
        Serial.println("Error reading F1");
        notify=volt1.put(STATE,"off");
         notify=curr1.put(STATE,"off");
          notify=powr1.put(STATE,"off");
           notify=ener1.put(STATE,"off");
    }

delay(50);

       if( v2!=PZEM_ERROR_VALUE || i2!=PZEM_ERROR_VALUE ){
        Serial.printf("F2 Voltage :%.2fV  Current:%.2fA Power:%.2fW Energy:%.2fkWt\n",v2,i2,p2,e2); 
        notify=volt2.put(VALUE,String(v2)); notify=volt2.put(STATE,"on"); 
        notify=curr2.put(VALUE,String(i2)); notify=curr2.put(STATE,"on");
        notify=powr2.put(VALUE,String(p2)); notify=powr2.put(STATE,"on");
        notify=ener2.put(VALUE,String(e2)); notify=ener2.put(STATE,"on");
    } else {
        Serial.println("Error reading  F2");
        notify=volt2.put(STATE,"off");
         notify=curr2.put(STATE,"off");
          notify=powr2.put(STATE,"off");
           notify=ener2.put(STATE,"off");
    }

delay(50);

       if( v3!=PZEM_ERROR_VALUE || i3!=PZEM_ERROR_VALUE ){
        Serial.printf("\nF3 Voltage :%.2fV  Current:%.2fA Power:%.2fW Energy:%.2fkWt\n",v3,i3,p3,e3); 
        notify=volt3.put(VALUE,String(v3)); notify=volt3.put(STATE,"on"); 
        notify=curr3.put(VALUE,String(i3)); notify=curr3.put(STATE,"on");
        notify=powr3.put(VALUE,String(p3)); notify=powr3.put(STATE,"on");
        notify=ener3.put(VALUE,String(e3)); notify=ener3.put(STATE,"on");
    } else {
        Serial.println("Error reading  F3");
        notify=volt3.put(STATE,"off");
         notify=curr3.put(STATE,"off");
          notify=powr3.put(STATE,"off");
           notify=ener3.put(STATE,"off");
    }             

    if(p1!=PZEM_ERROR_VALUE||p2!=PZEM_ERROR_VALUE||p3!=PZEM_ERROR_VALUE)  {
    float p=p1+p2+p3;
    totalpow.put(VALUE,String(p)); totalpow.put(STATE,"on");
    }
    
      if(e1!=PZEM_ERROR_VALUE||e2!=PZEM_ERROR_VALUE||e3!=PZEM_ERROR_VALUE)  {
         float e=e1+e2+e3;
         totalener.put(VALUE,String(e)); totalener.put(STATE,"on");
      }

/* 
 Serial.printf("Voltage V1: %.2fV V2: %.2fV V3: %.2fV\n",v1,v2,v3); 
Serial.printf(" Current I1: %.2fA I2: %.2fA I3: %.2fA\n",i1,i2,i3); 
Serial.printf(" Power P1: %.2fW P2: %.2fW P3: %.2fW\n",p1,p2,p3);*/


Serial.printf("heap=%d at %lus \n", ESP.getFreeHeap(), now / 1000);
 next = now + mppServer.getUnsignedProperty(P_PERIOD);
  }
}
