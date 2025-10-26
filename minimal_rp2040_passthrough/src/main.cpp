#include "global.h"

volatile u8 setupDone = 0b00;
volatile bool setup1CanStart = false;

void setup() {
	if (powerOnResetMagicNumber == 0xdeadbeefdeadbeef)
		bootReason = rebootReason;
	else
		bootReason = BootReason::POR;
	powerOnResetMagicNumber = 0xdeadbeefdeadbeef;
	rebootReason = BootReason::WATCHDOG;
	Serial.begin(115200);
	DEBUG_PRINTSLN("start");
#if HW_VERSION == 2
	/*initStandbySwitch();
	initSpeaker();
	ledInit();*/
#endif
	//initAnalog();
	//if (bootReason == BootReason::TO_ESC_PASSTHROUGH) {
		//initDisplay();
		u8 pins[4] = {PIN_MOTOR_BASE, PIN_MOTOR_BASE + 1, PIN_MOTOR_BASE + 2, PIN_MOTOR_BASE + 3};
		beginPassthrough(pins, 4);
		//triggerInit();
		/*tft.setFont(&FreeSans9pt7b);
		tft.fillScreen(ST77XX_BLACK);
		tft.setTextColor(ST77XX_WHITE);
		printCentered("ESC Passthrough", SCREEN_WIDTH / 2, 15, SCREEN_WIDTH, 1, 22, ClipBehavior::PRINT_LAST_LINE_CENTERED);
		SET_DEFAULT_FONT;*/
/*#if HW_VERSION == 1
		printCentered("Use BLHeliSuite32 to configure ESCs. Click disconnect or hold the trigger for 3 sec to boot into normal mode again.", SCREEN_WIDTH / 2, 30, SCREEN_WIDTH, 5, YADVANCE, ClipBehavior::PRINT_LAST_LINE_CENTERED);
#elif HW_VERSION == 2
		printCentered("Use AM32 Configurator to configure ESCs. Click disconnect or hold the trigger for 3 seconds to boot into normal mode again.", SCREEN_WIDTH / 2, 40, SCREEN_WIDTH, 5, YADVANCE_RELAXED, ClipBehavior::PRINT_LAST_LINE_CENTERED);
#endif*/
		elapsedMillis triggerTimer = 0;
		while (processPassthrough()) {
			/*triggerLoop();
			if (triggerState) {
				if (triggerUpdateFlag) {
					triggerUpdateFlag = false;
					triggerTimer = 0;
				}
				if (triggerTimer >= 3000)
					break;
			} else {
				triggerUpdateFlag = false;
			}*/
		}
		sleep_ms(100);
		rebootReason = BootReason::FROM_ESC_PASSTHROUGH;
		rp2040.reboot();
	//}
}

void loop() {

}

void setup1() {

}


void loop1() {
}
