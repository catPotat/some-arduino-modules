int IR[2] = {2, 3};
int ONorder[2] = {0, 0};
int OFForder[2] = {0, 0};
int people_inside = 1;
bool manual = false;


void process_detectors_data() {
  for (int i=0; i < 2; i++) {
    if(digitalRead(IR[i]) == LOW) {
      if (ONorder[0] == 0) {
        ONorder[0] = IR[i];
      }
      else {
        if (ONorder[0] != IR[i]) {
          ONorder[1] = IR[i];
        }
      }
    }
    
    if(digitalRead(IR[i]) == HIGH) {
      if (ONorder[1] != 0) {
        if (OFForder[0] == 0) {
          OFForder[0] = IR[i];
        }
        else {
          if (OFForder[0] != IR[i]) {
            OFForder[1] = IR[i];
          }
        }
      }
    }
    
    for (int i=0; i< 2; i++) {
      if ( (ONorder[i] !=0 or OFForder[i] !=0) and (digitalRead(IR[0]) == HIGH and digitalRead(IR[1]) == HIGH) ) {
        abort_();
      }
      if ( ONorder[i] != OFForder[i] and (ONorder[i] !=0 and OFForder[i] !=0) ) {
        abort_();
        //Serial.print("aborted");
      }
    }
  
  }

  if (ONorder[1] != 0 and OFForder[1] !=0) {
    if (OFForder[0] == IR[0]) {
      if (people_inside >0){
        people_inside--;
      }
    }
    if (OFForder[0] == IR[1]) {
      people_inside++;
    }
    abort_();
  }

}

void abort_() {
  for (int i=0; i< 2; i++) {
    ONorder[i] = 0;
    OFForder[i] = 0;
  }
}

void relay_control() {
  if (people_inside > 0) {
    //if (18 > hour > 6) {
        if (not manual) {
          digitalWrite(8, HIGH);
        }
    //}
  }
  if (people_inside == 0) {
    digitalWrite(8, LOW);
  }
}

void serial_sensorData() {
  Serial.print(digitalRead(IR[0]));
  Serial.print(digitalRead(IR[1]));
  Serial.print(ONorder[0]);
  Serial.print(ONorder[1]);
  Serial.print(OFForder[0]);
  Serial.print(OFForder[1]);
  Serial.println(people_inside);
}

void autoLighting() {
  while ( (digitalRead(IR[0])==LOW) or (digitalRead(IR[1])==LOW) ){
    process_detectors_data();
  }
  //serial_sensorData();
  relay_control();
}

void pins4Light() {
  pinMode(7, INPUT);
  pinMode(8, OUTPUT);
}

void toggleLight() {
  manual = not manual;
}

void lightON() {
  manual = false;
}

void lightOFF() {
  manual = true;
}

