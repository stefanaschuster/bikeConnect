


#define BTN1 9
#define LED1 6

#ifdef BOX
  #define DIO_IN 3
  #define DIO_OUT 2
  #define LED2 7
  #define LED3 8
#else
  #define DIO_IN 2
  #define DIO_OUT 3
  #define LED2 8
  #define LED3 7
#endif

int cycle_cnt = 0;
int btn_on_count = 0;
bool box_in_request = 0;
bool driver_in_request = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(BTN1,INPUT);
  pinMode(DIO_OUT,OUTPUT);
  digitalWrite(DIO_OUT, LOW);
  pinMode(DIO_IN,INPUT);
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  delay(100);
}

void updateIO() {
  btn_on_count = digitalRead(BTN1) ? (btn_on_count+1):0;

  // sticky read of remote setting 
  if(digitalRead(DIO_IN))
    box_in_request = true;

  // dont do anything remote while button press
  if(!digitalRead(BTN1)){
    if(driver_in_request){
      if(!cycle_cnt) {
        // blink the remote signal
        digitalWrite(DIO_OUT,!digitalRead(DIO_OUT));
      }
    } else
      digitalWrite(DIO_OUT,LOW); 
  }
  digitalWrite(LED3,driver_in_request);
  digitalWrite(LED2,box_in_request);
  digitalWrite(LED1,!cycle_cnt);
}

void loop() {
  delay(50);
  cycle_cnt = cycle_cnt > 40 ? 0 : cycle_cnt+1;
  updateIO();
  if(btn_on_count > 0){ 
    // short press
    if(btn_on_count < 40){
      driver_in_request = true;
    // long press
    }else{
      driver_in_request = false;
      box_in_request = false;
    }
  }
}
