    #define INPUTPIN 23
    #define TIMEOUT 100
    #define WAIT_SENSOR_CHANGES 0
    #define WAIT_TIMEOUT 1

    uint8_t stateVar = WAIT_SENSOR_CHANGES;
    uint8_t pinStableValue;
    uint32_t oldTime;

    void setup() {
        Serial.begin(115200);
        pinMode(INPUTPIN, INPUT_PULLUP);
        pinStableValue = digitalRead(INPUTPIN);
    }

    void Task() {
    uint8_t pin;
    
        switch (stateVar) {
            case WAIT_SENSOR_CHANGES:
            pin = digitalRead(INPUTPIN);
            if (pin != pinStableValue) {
                stateVar = WAIT_TIMEOUT;
                oldTime = millis();
            }
            break;
            case WAIT_TIMEOUT:

                pin = digitalRead(INPUTPIN);
                if(pin == pinStableValue){
                stateVar = WAIT_SENSOR_CHANGES;
                }
                
                uint32_t newTime = millis();
                if( (newTime - oldTime) >= TIMEOUT ){
                pinStableValue = pin;
                Serial.println("Timout");
                stateVar = WAIT_SENSOR_CHANGES;
                }
            break;
        }
    }

    void loop() {
        Task();
    }
