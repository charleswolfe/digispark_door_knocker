const float pi = 3.14;

int knock_count = 0;
int current_phase = 0;
int timer = 0;

int SERVO_PIN = 1;
int RED_LED_PIN = 4;
int BLUE_LED_PIN = 5;
int GREEN_LEDPIN = 0;
int LED_WARM_UP_PHASE = 0;
int KNOCK_PHASE = 1;
int LED_SWELL_PHASE = 2;
int KNOCK_PHASE_TWO = 3;
int PAUSE_PHASE = 4;
int MAX_PHASE = 4;

int LED_WARM_UP_PHASE_MAX_TIME = 0;
int KNOCK_PHASE_MAX_TIME = 0;
int LED_SWELL_PHASE_MAX_TIME = 5;
int PAUSE_PHASE_MAX_TIME = 10000;

void setup()
{
        pinMode(SERVO_PIN, OUTPUT);
        //pinMode(2,OUTPUT);
        digitalWrite(SERVO_PIN, LOW);
}

void loop()
{
        //establish a count
	timer += 1;

        if (current_phase ==  LED_WARM_UP_PHASE) {
                slow_buildup_led();
        }

        //knocker  --------------------
        if (current_phase == KNOCK_PHASE || current_phase == KNOCK_PHASE_TWO) {
                //turn on LED?
                analogWrite(RED_LED_PIN, 75);
                away_from_door();
                towards_door_fast();
                knock_count += 1;
                if (knock_count >= 3) { //this does not seem to work

                        delay(1200);
                        knock_count = 0;
                        increment_phase();
                        //turn off LED?
                        analogWrite(RED_LED_PIN, 0);
                }
        //end of knocker -------------------------
        }

        //swell phase
        if (current_phase == LED_SWELL_PHASE) {
                // check if time is max
                if (timer >= LED_SWELL_PHASE_MAX_TIME)
                        increment_phase();
                //do phase activities
                swell_led();
        }

        if (current_phase == PAUSE_PHASE) {
                delay(1);
                if (timer >= PAUSE_PHASE_MAX_TIME)
                        increment_phase();
        }

}

void increment_phase() {
        timer = 0;
        if (current_phase >= MAX_PHASE)
                current_phase = 0;
        else
                current_phase += 1;
}

void slow_buildup_led() {
        for (int i = 0; i < 10; i++) {
                //i want to go from 20 to 120 for brightness
                int brightness = (10*i) + 20;
                //i want to go from 100 down to maybe 5 for delay
                int my_delay = 100 - (10 * i) ;
                mod_swell(brightness, my_delay);
        }
        increment_phase();
}

void mod_swell(int max_bright, int my_delay) {
        for (int i = 0; i < max_bright; i++) {
                analogWrite(RED_LED_PIN, i);
                delay(my_delay);
        }
        for (int i = max_bright; i > 0; i--) {
                analogWrite(RED_LED_PIN, i);
                delay(my_delay);
        }
        analogWrite(RED_LED_PIN, 0);
        delay(3000);
}

void swell_led() {
        for (int i = 0; i < 100; i++) {
                analogWrite(RED_LED_PIN, i);
                delay(10);
        }
        for (int i = 100; i > 0; i--) {
                analogWrite(RED_LED_PIN, i);
                delay(10);
        }
        analogWrite(RED_LED_PIN, 0);
        delay(2000);
}

void towards_door() {
        for(int pos = 1200; pos < 1900; pos +=15)
        {
                digitalWrite(SERVO_PIN, HIGH);
                delayMicroseconds(pos);
                digitalWrite(SERVO_PIN, LOW);
                delayMicroseconds(pos);
                delay(10);
        }
}

void towards_door_fast() {
        for(int pos = 1200; pos < 1900; pos +=50)
        {
                digitalWrite(SERVO_PIN, HIGH);
                delayMicroseconds(pos);
                digitalWrite(SERVO_PIN, LOW);
                delayMicroseconds(pos);
                delay(10);
        }
}

void away_from_door() {
        for(int pos = 1900; pos > 1200; pos -=15)
        {
                digitalWrite(SERVO_PIN, HIGH);
                delayMicroseconds(pos);
                digitalWrite(SERVO_PIN, LOW);
                delayMicroseconds(pos);
                delay(10);
        }
}


