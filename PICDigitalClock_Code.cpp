int count[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
int d1 = 0;
int d2 = 0;
int d3 = 0;
int d4 = 0;
int start;

int switch1_state = 1; 
int switch2_state = 1;
int switch3_state = 1; 
int switch4_state = 1; 

int clock_enabled = 1;

int is_minutes_selected = 1; 

void display() {
    PORTB = count[d1];
    PORTC.B3 = 1;
    delay_ms(1);
    PORTC.B3 = 0;

    PORTB = count[d2];
    PORTC.B2 = 1;
    delay_ms(1);
    PORTC.B2 = 0;

    PORTB = count[d3];
    PORTC.B1 = 1;
    delay_ms(1);
    PORTC.B1 = 0;

    PORTB = count[d4];
    PORTC.B0 = 1;
    delay_ms(1);
    PORTC.B0 = 0;
}

void clock() {
    if (clock_enabled) {
        d1++;
        if (d1 > 9) {
            d1 = 0;
            d2++;
            if (d2 > 5) {
                d2 = 0;
                d3++;
                if (d3 > 9) {
                    d3 = 0;
                    d4++;
                    if ((d4 == 2 && d3 > 3) || d4 > 2) {
                        d4 = 0;
                    }
                }
            }
        }
    }
}

void main() {
    TRISB = 0x00;
    TRISC = 0x00;
    TRISD = 0xFF;
    PORTB = 0;
    PORTC = 0;

    while (1) {
        clock();
        switch1_state = PORTD.B0;
        switch2_state = PORTD.B1;
        switch3_state = PORTD.B2;
        switch4_state = PORTD.B3;

        if (switch1_state == 0) {
            while (!PORTD.B0) {
            }
            clock_enabled = !clock_enabled;
            start = !start;
        }

        if (!clock_enabled && switch2_state == 0) {
            while (!PORTD.B1) {
            }
            is_minutes_selected = !is_minutes_selected;
            delay_ms(200); 

        if (!clock_enabled && switch3_state == 0) {
            while (!PORTD.B2) {
            }

            if (is_minutes_selected) {
                d1++;
                if (d1 == 10) {
                    d1 = 0;
                    d2++;
                    if (d2 == 6) {
                        d2 = 0;
                    }
                }
            } else {
                d3++;
                if (d3 == 10) {
                    d3 = 0;
                    d4++;
                    if (d4 == 3 && d3 > 2) {
                        d4 = 0;
                    }
                }
            }
            delay_ms(500);
        }

        if (!clock_enabled && switch4_state == 0) {
            while (!PORTD.B3) {
            }

            if (is_minutes_selected) {
                if (d1 == 0) {
                    if (d2 == 0) {
                        d2 = 5;
                        d1 = 9;
                    } else {
                        d2--;
                        d1 = 9;
                    }
                } else {
                    d1--;
                }
            } else {
                if (d3 == 0) {
                    if (d4 == 0) {
                        d4 = 2;
                        d3 = 3;
                    } else {
                        d4--;
                        d3 = 9;
                    }
                } else if (d3 == 3 && d4 == 0 && d1 == 0 && d2 == 0) {
                    d3 = 2;
                    d4 = 3;
                } else {
                    d3--;
                }
            }
            delay_ms(500);
        }

        if (d4 > 2 || (d4 == 2 && d3 > 3)) {
            d4 = 0;
            d3 = 0;
        }
        if (d2 > 5 || (d2 == 5 && d1 > 9)) {
            d2 = 0;
            d1 = 0;
        }

        display(); // Display the current time

        delay_ms(40);
    }
}

