#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cb.h"


#define	BUTTON1_SET			(PINC & _BV(5))
#define	BUTTON2_SET			(PINC & _BV(4))
#define ALARM_SWITCH_SET	(PINC & _BV(3))

typedef enum {
	NONE = 0x00, 
	UPDATE_TIME = 0x01,
	BLINK = 0x02,
	ALARM_BEEP = 0x04,
	RUN_COUCOU = 0x08
} Events;
volatile static Events events;

typedef struct {
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
} Time;
static Time time;
static Time alarm;


typedef enum {
	SHOW_TIME = 0,
	SET_ALARM = 1,
	SET_TIME = 2,
	SET_BRIGHTNESS = 3,
	SET_COUCOU = 4,
	CYCLE_TUBES = 5,
	SET_ALARM_HOURS = 6,
	SET_ALARM_MINUTES = 7,
	SET_TIME_HOURS = 8,
	SET_TIME_MINUTES = 9,
	SELECT_BRIGHTNESS = 10,
	ENABLE_COUCOU = 11
} Input_state;

static Input_state input_state = SHOW_TIME;

typedef enum {
	DEC_POINT_0 = 0x01,
	DEC_POINT_1 = 0x02,
	DEC_POINT_2 = 0x04,
	DEC_POINT_3 = 0x08,
} Decimal_points;

Decimal_points decimal_points;

struct Settings {
	uint8_t brightness;
	bool time_mode;
} settings;

int8_t display_digits[4] = {0,1,2,3};
int8_t setting_digits[4] = {0,0,0,0};
uint8_t time_digits[6] = {0,0,0,0,0,0};
uint8_t alarm_digits[4] = {0, 0, 0, 0};

bool time_is_set = false;

bool alarm_active = false;
bool alarm_on = false;



void setup_io(void) 
{
	/**
	 * Outputs
	 */

	// Nixie Anodes
	DDRC |= _BV(2) | _BV(1) | _BV(0);
	PORTC &= ~(_BV(2) | _BV(1) | _BV(0));
	
	DDRB |= _BV(5);
	PORTB &= ~_BV(5);

	PORTC |= _BV(2);

	// 74141 Decoder
	DDRB |= _BV(1) | _BV(3) | _BV(4) | _BV(2);
	PORTB &= ~(_BV(1) | _BV(3) | _BV(4) | _BV(2));

	// Decimal point
	DDRB |= _BV(0);
	PORTB &= ~_BV(0);
	//DDRD |=_BV(5);
	//PORTB &= ~_BV(5);

	// INS-1 // Seperator
	DDRD |= _BV(2);
	PORTD |= _BV(2);

	//Speaker
	DDRD |= _BV(3);
	PORTD &= ~_BV(3);

	/**
	 * Inputs
	 */

	 // Button 1
	 DDRC &= ~_BV(5);
	 PORTC |= _BV(5); // Pullup active

	 // Button 2
	 DDRC &= ~_BV(4);
	 PORTC |= _BV(4); // Pullup active

	 // Switch
	 DDRC &= ~_BV(3);
	 PORTC |= _BV(3); // Pullup active

	 // AIN1 Comparator
	 DDRD &= ~_BV(7);
	 PORTD &= ~_BV(7); // Pullup inactive

}

void setup_pwm(void)
{

	// PWM output for boost converter
	//DDRD |= _BV(6); // OC0A
	DDRD |= _BV(5); // OC0B

	// OC0A
	//TCCR0A = _BV(COM0A1); // Clear OC0A on comp match.
	TCCR0A = _BV(COM0B1); // Clear OC0B on comp match.
	//TCCR0A |= _BV(WGM00) | _BV(WGM02); // Fast PWM Phase corect
	TCCR0A |= _BV(WGM00) | _BV(WGM01);
	TCCR0B = _BV(CS00); // No prescaling
	//OCR0A = 45;
	OCR0B = 55;
}

void setup_timers(void)
{

	/* Timer 2 */
	ASSR |= _BV(AS2); // use crystal
	TCCR2B = _BV(CS22) | _BV(CS20); // div by 128

	OCR2A=0;

	// enable interrupt
	TIMSK2 = _BV(TOIE2) | _BV(OCIE2A); // Overflow interupt
	// Will overflow once a second

	/* Timer 1 */

	//ICR1 = 0xAFFF;

	TCCR1A = 0;     // set entire TCCR1A register to 0
    TCCR1B = 0;     // same for TCCR1B

	OCR1A = 30000;

	TCCR1B = _BV(WGM12);
	TCCR1B |= _BV(CS10);
	//TIMSK1 = _BV(TOIE1); // oveflow interupt
	TIMSK1 = _BV(OCIE1A);

}

void setup_comparator()
{
	ACSR = _BV(ACBG) | _BV(ACIE); // use bandgap, intr. on toggle!
	_delay_ms(1); // settle
	if (ACSR & _BV(ACO)) {
		ACSR |= _BV(ACI);
	}
}

void beep(void)
{
	uint16_t i;
	for(i=0;i!=75;++i) {
		PORTD |= _BV(3);
		_delay_us(500);
		PORTD &= ~_BV(3);
		_delay_us(500); // 350
	}
	_delay_ms(80);
	for(i=0;i!=75;++i) {
		PORTD |= _BV(3);
		_delay_us(350);
		PORTD &= ~_BV(3);
		_delay_us(350); // 350
	}
}

/**
 * Delay for button debounce with a little audible click;
 */
void delay_tic( void )
{
	PORTD |= _BV(3);
	_delay_ms(75);
	PORTD &= ~_BV(3);
}

bool check_eeprom()
{
	// Check eeprom to see  if it has been initialized with default values
	if ((eeprom_read_byte(0)=='o')&&(eeprom_read_byte(1)=='k')) {
		return true;
	} else {
		return false;
	}
}

void init_eeprom()
{
	uint8_t i;
	eeprom_update_byte ( ( uint8_t *)0, 'o');
	eeprom_update_byte ( ( uint8_t *)1, 'k');
	for(i=2;i!=16;++i) {
		eeprom_update_byte ( i, 0 );
	}
}

void save_alarm() 
{
	eeprom_update_byte ( ( uint8_t *)2, alarm.hour);
	eeprom_update_byte ( ( uint8_t *)3, alarm.minute);
}

void load_alarm()
{
	alarm.hour = eeprom_read_byte(( uint8_t *)2);
	alarm.minute = eeprom_read_byte(( uint8_t *)3);
	alarm.second = 0;
}

void check_alarm( void )
{
	//serial_write('b');
	if (
		(alarm.hour == time.hour) 
		&& (alarm.minute == time.minute) 
		&& (alarm.second == time.second)
		&& !(PINC & _BV(3)) )
	{
		alarm_active = true;
	}
}

void load_brightness()
{
	settings.brightness = eeprom_read_byte(( uint8_t *)4);
}

void save_brightness()
{
	eeprom_update_byte(( uint8_t *)4, settings.brightness);
}

void set_brightness()
{
	switch (settings.brightness) {
		case 0: OCR0B = 40; break;
		case 1: OCR0B = 45; break;
		case 2: OCR0B = 50; break;
		case 3: OCR0B = 55; break;
		case 4: OCR0B = 60; break;
		case 5: OCR0B = 65; break;
		case 6: OCR0B = 70; break;
		default: OCR0B = 45;
	}
}

void time_to_digits( void )
{
	time_digits[0] = time.hour / 10;
	time_digits[1] = time.hour % 10;
	time_digits[2] = time.minute / 10;
	time_digits[3] = time.minute % 10;
	time_digits[4] = time.second / 10;
	time_digits[5] = time.second % 10;
}

void alarm_to_digits( void )
{
	alarm_digits[0] = alarm.hour / 10;
	alarm_digits[1] = alarm.hour % 10;
	alarm_digits[2] = alarm.minute / 10;
	alarm_digits[3] =  alarm.minute % 10;
}

void process_command_line( uint8_t *line)
{
	//uint8_t i;
	uint8_t command;
	//uint8_t arg[14];
	uint8_t *arg;

	if(line[0] == ':') {
		
		command = line[1];

		// for(i=0;i!=14;++i) {
		// 	arg[i] = line[i+2];
		// }
		arg = &line[2];


		serial_writeln(line);
		switch (command) {
			case 'h': time.hour = atoi(arg) % 24; break;
			case 'm': time.minute = atoi(arg) % 60; break;
			case 's': time.second = atoi(arg) % 60; break;
			default: break;
		}
	}
}

void read_serial( void )
{
	uint8_t incoming_data;
	static uint8_t command_line[16];
	static uint8_t i = 0;

	while(cb_read(&cb, &incoming_data)) {
		switch(incoming_data) {
			case '\r': break;
				command_line[i++] = '\0';
			case '\n': 
				process_command_line(command_line);
				i = 0;
			break;
			default:
				command_line[i++] = incoming_data;
				i %= 16;
				break; 
		}
	}
}

void process_events( void )
{
	static bool blinky;
	if(events & UPDATE_TIME) {
		time_to_digits();
		events &= ~UPDATE_TIME;
	}

	if (events & BLINK) {
		blinky = !blinky;
		events &= ~BLINK;
		if(alarm_active ) {
			beep();
		}
		

		if (!time_is_set) {
			if (blinky) {
				decimal_points = 0b1111;
			} else {
				decimal_points = 0b0000;
			}
		}
		
	}
}

int main()
{
	//DIDR1 &= ~_BV(AIN1D);
	//ADCSRB = 0;
	//ADCSRB |= _BV(ACME);
	setup_comparator();

	time.hour = 0;
	time.minute = 0;
	time.second = 0;

	uint8_t hours, minutes;


	setup_io();
	setup_pwm();
	setup_timers();
	uart_init();

	if(!check_eeprom()) {
		init_eeprom();
	}

	load_brightness();
	set_brightness();

	load_alarm();
	
	serial_writeln("h");

	if (!ALARM_SWITCH_SET) {
		alarm_on = true;
	}

	alarm_active = true;
	sei(); // Enable interupts
	
	while(1) {
		//beep();
		process_events();

		// Stop the alarm.
		if (alarm_active && ALARM_SWITCH_SET ) {
			alarm_active = false;
		}

		// Show alarm time when the alarm is switched on
		if ( (alarm_on == false) && (ALARM_SWITCH_SET == false) ) {
			load_alarm();
			alarm_to_digits();
			display_digits[0] = alarm_digits[0];
			display_digits[1] = alarm_digits[1];
			display_digits[2] = alarm_digits[2];
			display_digits[3] = alarm_digits[3];
			alarm_on = true;
			_delay_ms(1000);
		}

		// Switch alarm off
		if ( alarm_on && ALARM_SWITCH_SET) {
			alarm_on = false;
		}

		if (!BUTTON1_SET)
		{
			uint8_t hours; 
			delay_tic();
			while( !BUTTON1_SET )
				__asm__("nop");
			_delay_ms(75);

			switch(input_state) {
				case SET_ALARM_HOURS:
					hours = setting_digits[0] * 10 + setting_digits[1];
					++hours;
					hours %= 24;
					setting_digits[0] = hours / 10;
					setting_digits[1] = hours % 10;
					break;
				case SET_ALARM_MINUTES:
					minutes = setting_digits[2] * 10 + setting_digits[3];
					++minutes;
					minutes %= 60;
					setting_digits[2] = minutes / 10;
					setting_digits[3] = minutes % 10;
					break;
				case SET_TIME_HOURS:
					hours = setting_digits[0] * 10 + setting_digits[1];
					++hours;
					hours %= 24;
					setting_digits[0] = hours / 10;
					setting_digits[1] = hours % 10;
					break;
				case SET_TIME_MINUTES:
					minutes = setting_digits[2] * 10 + setting_digits[3];
					++minutes;
					minutes %= 60;
					setting_digits[2] = minutes / 10;
					setting_digits[3] = minutes % 10;
					break;
				case SELECT_BRIGHTNESS:
					settings.brightness++;
					setting_digits[3] = settings.brightness;
					settings.brightness%=7;
					set_brightness();
					break;
				default:
					input_state++;
				break;
			}
		}

		if (!BUTTON2_SET)
		{
			delay_tic();
			while( !BUTTON2_SET )
				__asm__("nop");
			_delay_ms(75);
			switch(input_state) {
				case SET_ALARM:
					input_state = SET_ALARM_HOURS;
					load_alarm();
					alarm_to_digits();
					setting_digits[0] = alarm_digits[0];
					setting_digits[1] = alarm_digits[1];
					setting_digits[2] = alarm_digits[2];
					setting_digits[3] = alarm_digits[3];
					break;
				case SET_TIME:
					input_state = SET_TIME_HOURS;
					setting_digits[0] = time_digits[0];
					setting_digits[1] = time_digits[1];
					setting_digits[2] = time_digits[2];
					setting_digits[3] = time_digits[3];
					break;
				case SET_ALARM_HOURS:
					input_state = SET_ALARM_MINUTES;
					break;
				case SET_ALARM_MINUTES:
					alarm.hour = setting_digits[0] * 10 + setting_digits[1];
					alarm.minute = setting_digits[2] * 10 + setting_digits[3];
					alarm.second = 0;
					decimal_points = 0b0000;
					save_alarm();
					input_state = SHOW_TIME;
					break;
				case SET_TIME_HOURS:
					input_state = SET_TIME_MINUTES;
					break;
				case SET_TIME_MINUTES:
					time_is_set = true;
					time.hour = setting_digits[0] * 10 + setting_digits[1];
					time.minute = setting_digits[2] * 10 + setting_digits[3];
					time.second = 0;
					decimal_points = 0b0000;
					input_state = SHOW_TIME;
					break;
				case SET_BRIGHTNESS:
					setting_digits[0] = 5;
					setting_digits[1] = 5;
					setting_digits[2] = 5;
					setting_digits[3] = settings.brightness;
					input_state=SELECT_BRIGHTNESS;
					break;
				case SELECT_BRIGHTNESS:
					save_brightness();
					input_state = SHOW_TIME;
					break;
			}
		}

		switch(input_state) {
			case SHOW_TIME:	
				display_digits[0] = time_digits[0];
				display_digits[1] = time_digits[1];
				display_digits[2] = time_digits[2];
				display_digits[3] = time_digits[3];
				if(time_is_set) {
					decimal_points = 0b0000;	
				}
				break;
			case SET_ALARM:
				decimal_points = 0b1111;
				display_digits[0] = 3;
				display_digits[1] = 3;
				display_digits[2] = 3;
				display_digits[3] = 3;
				break;
			case SET_TIME:
				decimal_points = 0b1111;
				display_digits[0] = 4;
				display_digits[1] = 4;
				display_digits[2] = 4;
				display_digits[3] = 4;
				break;
			case SET_ALARM_HOURS:
				decimal_points = 0b0011;
				display_digits[0] = setting_digits[0];
				display_digits[1] = setting_digits[1];
				display_digits[2] = setting_digits[2];
				display_digits[3] = setting_digits[3];
				break;
			case SET_ALARM_MINUTES:
				decimal_points = 0b1100;
				display_digits[0] = setting_digits[0];
				display_digits[1] = setting_digits[1];
				display_digits[2] = setting_digits[2];
				display_digits[3] = setting_digits[3];
				break;
			case SET_TIME_HOURS:
				decimal_points = 0b0011;
				display_digits[0] = setting_digits[0];
				display_digits[1] = setting_digits[1];
				display_digits[2] = setting_digits[2];
				display_digits[3] = setting_digits[3];
				break;
			case SET_TIME_MINUTES:
				decimal_points = 0b1100;
				display_digits[0] = setting_digits[0];
				display_digits[1] = setting_digits[1];
				display_digits[2] = setting_digits[2];
				display_digits[3] = setting_digits[3];
				break;
			case SET_BRIGHTNESS:
				display_digits[0] = 5;
				display_digits[1] = 5;
				display_digits[2] = 5;
				display_digits[3] = 5;
				break;
			case SELECT_BRIGHTNESS:
				display_digits[0] = setting_digits[0];
				display_digits[1] = setting_digits[1];
				display_digits[2] = setting_digits[2];
				display_digits[3] = setting_digits[3];
				break;
			default:
				input_state = SHOW_TIME;
				break;

		}

		read_serial();
	}
}


/**
 * This goes off once a second.
 */
ISR(TIMER2_OVF_vect)
{
	if(++time.second >= 60) {
		time.second = 0;
		if(++time.minute >= 60) {
			time.minute = 0;
			if(++time.hour >= 24) {
				time.hour = 0;
			}
		}
	}
	events |= UPDATE_TIME;
	check_alarm();
	//PORTD ^= _BV(2);

}

ISR(TIMER2_COMPA_vect)
{
	// Show that the alarm is on
	if(PINC & _BV(3)) {
		PORTD |= _BV(2);
	} else {
		PORTD ^= _BV(2);
	}

	events |= BLINK;

	OCR2A += 128;
}

ISR(TIMER1_COMPA_vect)
{
	static uint8_t display_digit;

	PORTC &= ~(_BV(2) | _BV(1) | _BV(0));
	PORTB &= ~_BV(5);

	display_digit++;
	display_digit%=4;

	switch(abs(display_digits[display_digit])) {
		case 0: 
			PORTB &= ~(_BV(1) | _BV(3) | _BV(4) | _BV(2));
			break;
		case 1:
			PORTB |= _BV(1);
			PORTB &= ~_BV(3);
			PORTB &= ~_BV(4);
			PORTB &= ~_BV(2);
			break;
		case 2:
			PORTB &= ~_BV(1);
			PORTB |= _BV(3);
			PORTB &= ~_BV(4);
			PORTB &= ~_BV(2);
			break;
		case 3:
			PORTB |= _BV(1);
			PORTB |= _BV(3);
			PORTB &= ~_BV(4);
			PORTB &= ~_BV(2);
			break;
		case 4:
			PORTB &= ~_BV(1);
			PORTB &= ~_BV(3);
			PORTB |= _BV(4);
			PORTB &= ~_BV(2);
			break;
		case 5:
			PORTB |= _BV(1);
			PORTB &= ~_BV(3);
			PORTB |= _BV(4);
			PORTB &= ~_BV(2);
			break;
		case 6:
			PORTB &= ~_BV(1);
			PORTB |= _BV(3);
			PORTB |= _BV(4);
			PORTB &= ~_BV(2);
			break;
		case 7:
			PORTB |= _BV(1);
			PORTB |= _BV(3);
			PORTB |= _BV(4);
			PORTB &= ~_BV(2);
			break;
		case 8: 
			PORTB &= ~_BV(1);
			PORTB &= ~_BV(3);
			PORTB &= ~_BV(4);
			PORTB |= _BV(2);
			break;
		case 9:
			PORTB |= _BV(1);
			PORTB &= ~_BV(3);
			PORTB &= ~_BV(4);
			PORTB |= _BV(2);
			break;
		default: break;
	}

	if(decimal_points & (1 << display_digit)) {
		PORTB |= _BV(0);
	} else {
		PORTB &= ~_BV(0);
	}

	_delay_us(200);

	switch(display_digit)
	{
		case 0:
			PORTC |= _BV(2);
			break;
		case 1:
			PORTC |= _BV(1);
			break;
		case 2:
			PORTC |= _BV(0);
			break;
		case 3:
			PORTB |= _BV(5);
			break;
	}
}

 ISR (ANALOG_COMP_vect)
 {
 	if (ACSR & _BV(ACO)) {
 		// Device is unpluged
 		OCR0B = 0;
 		serial_writeln("un\r\n");
 	} else {
 		// Device is pluged in
 		set_brightness();
 		serial_writeln("pluged\r\n");
 	}
 }
