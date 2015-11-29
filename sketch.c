#include <LiquidCrystal.h>

// initialise LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Set red LED to pin 9
int red = 9;

void setup() {
	// Set baud rate of 115200
	Serial.begin(115200);
	// Set 'red' LED as output
	pinMode(red, OUTPUT);
	// Set debug LED as output
	pinMode(13, OUTPUT);

	digitalWrite(red, LOW);

	// Write 'block:' to first line
	lcd.begin(16, 2);
	lcd.print("Block: ");
}

// write writes out the buffer to the LCD.
void write(byte *b, int length) {
	// turn the debug light on
	digitalWrite(13, HIGH);
	// turn the red light on
	digitalWrite(red, HIGH);

	// little endian
	unsigned int number = byte(b[0]) | byte(b[1])<<8 | byte(b[2])<<16 | byte(b[3])<<24;
	// set cursor to second line
	lcd.setCursor(0, 1);
	// write out the number to the LCD
	lcd.print(number);

	// Turn light off
	delay(400);
	digitalWrite(red, LOW);
	digitalWrite(13, LOW);
}

int length = 0;
byte buffer[255];
byte rx = 0;

void loop() {
	if( Serial.available() > 0) {
		rx = Serial.read();

		// LB is control sequence. Finilise buffer and call write
		if( rx == '\n' ) {
			write(buffer, length);
			length = 0;
		} else {
			// set data to buffer
			buffer[length++] = rx;
		}
	}
}
