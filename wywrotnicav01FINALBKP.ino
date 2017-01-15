#include <Bounce2.h>

#define ButtonZamknijSzczekiPIN A4
#define ButtonWysypWkladPIN A5
#define KrancowkaSzczekiOPIN 2
#define KrancowkaSzczekiZPIN 3

#define KrancowkaNasypOPIN 4
#define KrancowkaNasypZPIN 5

#define KrancowkaWysypOPIN 6
#define KrancowkaWysypZPIN 7

#define SzczekiZamknijSilownik 8
#define SzczekiOtworzSilownik 9
#define NasypZamknijSilownik 10
#define NasypOtworzSilownik 11
#define WysypZamknijSilownik 12
#define WysypOtworzSilownik 0

#define CzasNasypu A0 //Podstawic staly czas
#define CzasWysypu A1 //Podstawic staly czas

#define SyrenaZoltaPIN A2
#define SyrenaCzerwonaPIN A3

// Instantiate a Bounce object
Bounce debounceNasypButton = Bounce(); 
Bounce debounceWysypButton = Bounce(); 

void sygnal(boolean ss){
  if (ss){
  digitalWrite(SyrenaZoltaPIN, HIGH);
  } else {
    digitalWrite(SyrenaZoltaPIN, LOW);
  }
}

void alarm(boolean ss){
  if (ss){
  digitalWrite(SyrenaCzerwonaPIN, HIGH);
  } else {
    digitalWrite(SyrenaCzerwonaPIN, LOW);
  }
}
void SzczekiOtworz(){
    while (digitalRead(KrancowkaSzczekiOPIN) == HIGH){
    //sygnal(1);
    //delay(1000);
    digitalWrite(SzczekiOtworzSilownik, HIGH);}
    digitalWrite(SzczekiOtworzSilownik, LOW);
    //sygnal(0);
}
void SzczekiZamknij(){
    while (digitalRead(KrancowkaSzczekiZPIN) == HIGH){
    //sygnal(1);
    //delay(1000);
    digitalWrite(SzczekiZamknijSilownik, HIGH);}
    digitalWrite(SzczekiZamknijSilownik, LOW);
    //sygnal(0);
  }
void NasypOtworz(){
    while (digitalRead(KrancowkaNasypOPIN) == HIGH){
    //sygnal(1);
    //delay(1000);
    digitalWrite(NasypOtworzSilownik, HIGH);}
    digitalWrite(NasypOtworzSilownik, LOW);
    //sygnal(0);
}
void NasypZamknij(){
    while (digitalRead(KrancowkaNasypZPIN) == HIGH){
    //sygnal(1);
    //delay(1000);
    digitalWrite(NasypZamknijSilownik, HIGH);}
    digitalWrite(NasypZamknijSilownik, LOW);
    //sygnal(0);
  }    
void WysypOtworz(){
    while (digitalRead(KrancowkaWysypOPIN) == HIGH){
    //sygnal(1);
    //delay(1000);
    digitalWrite(WysypOtworzSilownik, HIGH);}
    digitalWrite(WysypOtworzSilownik, LOW);
    //sygnal(0);
}
void WysypZamknij(){
    while (digitalRead(KrancowkaWysypZPIN) == HIGH){
    digitalWrite(WysypZamknijSilownik, HIGH);}
    digitalWrite(WysypZamknijSilownik, LOW);
    //sygnal(0);
  }    

void nasypTrzep(){
  if (KrancowkaWysypOPIN && !KrancowkaWysypZPIN == LOW){
    sygnal(1);
    delay(1000);
    digitalWrite(NasypOtworzSilownik, HIGH);
    delay(25);
    digitalWrite(NasypOtworzSilownik, LOW);
    digitalWrite(NasypZamknijSilownik, HIGH);
    delay(25);
    digitalWrite(NasypZamknijSilownik, LOW);
    digitalWrite(NasypOtworzSilownik, HIGH);
    delay(25);
    digitalWrite(NasypOtworzSilownik, LOW);
    digitalWrite(NasypZamknijSilownik, HIGH);
    delay(25);
    digitalWrite(NasypZamknijSilownik, LOW);
    sygnal(0);
  }
}

void kalibracja() {
NasypOtworz();
WysypOtworz();
SzczekiOtworz();

  }

void testKrancowek(){
  if (digitalRead(KrancowkaNasypOPIN) && digitalRead(KrancowkaNasypZPIN) == LOW){
    alarm(1);
  }
  if (digitalRead(KrancowkaWysypOPIN) && digitalRead(KrancowkaWysypZPIN) == LOW){
    alarm(1);
  }
  if (digitalRead(KrancowkaSzczekiOPIN) && digitalRead(KrancowkaSzczekiZPIN) == LOW){
    alarm(1);
  }
  delay(5000);
  alarm(0);
  }

void setup() {
  pinMode(ButtonZamknijSzczekiPIN, INPUT_PULLUP);
  pinMode(ButtonWysypWkladPIN, INPUT_PULLUP);
  pinMode(KrancowkaSzczekiOPIN, INPUT_PULLUP);
  pinMode(KrancowkaSzczekiZPIN, INPUT_PULLUP);
  pinMode(KrancowkaNasypOPIN, INPUT_PULLUP);
  pinMode(KrancowkaNasypZPIN, INPUT_PULLUP);
  pinMode(KrancowkaWysypOPIN, INPUT_PULLUP);
  pinMode(KrancowkaWysypZPIN, INPUT_PULLUP);
  pinMode(SzczekiZamknijSilownik, OUTPUT);
  pinMode(SzczekiOtworzSilownik, OUTPUT);
  pinMode(NasypZamknijSilownik, OUTPUT);
  pinMode(NasypOtworzSilownik, OUTPUT);
  pinMode(WysypZamknijSilownik, OUTPUT);
  pinMode(WysypOtworzSilownik, OUTPUT);
  pinMode(CzasNasypu, INPUT_PULLUP);
  pinMode(SyrenaZoltaPIN, OUTPUT);
  pinMode(SyrenaCzerwonaPIN, OUTPUT);
 
  // After setting up the button, setup the Bounce instance :
  debounceNasypButton.attach(ButtonZamknijSzczekiPIN);
  debounceNasypButton.interval(100); // interval in ms
  debounceWysypButton.attach(ButtonWysypWkladPIN);
  debounceWysypButton.interval(100); // interval in ms
  
  kalibracja();
}


void loop() {
  debounceNasypButton.update();
  debounceWysypButton.update();
     digitalWrite(SyrenaZoltaPIN, HIGH); 
  //Obsługa przycisków kasety============================================================
      //Nasyp start +++++++++++++++++++++++++++++++++++++++
  if (debounceNasypButton.read() == LOW && digitalRead(KrancowkaWysypOPIN) == LOW){
    debounceNasypButton.update();
    SzczekiZamknij();
    NasypZamknij();
    delay(1000);
    NasypOtworz();
    delay(1000);
    SzczekiOtworz();
    debounceNasypButton.update();
    digitalWrite(SyrenaZoltaPIN, LOW);
    delay(2000);
  }
    digitalWrite(SyrenaZoltaPIN, HIGH);
      //Wysyp start +++++++++++++++++++++++++++++++++++++++
  if (debounceWysypButton.read() == LOW && digitalRead(KrancowkaNasypOPIN) == LOW){
    if (digitalRead(KrancowkaNasypOPIN) == LOW){
    debounceWysypButton.update();
    WysypZamknij();
    delay(5000);
    WysypOtworz();
    debounceWysypButton.update();
    digitalWrite(SyrenaZoltaPIN, LOW);
    delay(2000);
    } else {NasypOtworz();};
  }

  
}
