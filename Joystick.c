/*
Nintendo Switch Fightstick - Proof-of-Concept

Based on the LUFA library's Low-Level Joystick Demo
	(C) Dean Camera
Based on the HORI's Pokken Tournament Pro Pad design
	(C) HORI

This project implements a modified version of HORI's Pokken Tournament Pro Pad
USB descriptors to allow for the creation of custom controllers for the
Nintendo Switch. This also works to a limited degree on the PS3.

Since System Update v3.0.0, the Nintendo Switch recognizes the Pokken
Tournament Pro Pad as a Pro Controller. Physical design limitations prevent
the Pokken Controller from functioning at the same level as the Pro
Controller. However, by default most of the descriptors are there, with the
exception of Home and Capture. Descriptor modification allows us to unlock
these buttons for our use.
*/

#include "Joystick.h"

typedef enum {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	R_UP,
	R_DOWN,
	R_LEFT,
	R_RIGHT,
	X,
	Y,
	A,
	B,
	L,
	R,
	ZR,
	PLUS,
	CAPTURE,
	NOTHING,
	TRIGGERS
} Buttons_t;

typedef struct {
	Buttons_t button;
	uint16_t duration;
} command; 

static const command step[] = {
	// メトロ車内にいて、Xボタンでマップを開いたときにバツチー郡駅にカーソルが合っている状態からスタートさせる。
	// コントローラ接続
  	{ NOTHING,  250 },
  	{ TRIGGERS,  20 },
  	{ NOTHING,  150 },
  	{ TRIGGERS,  20 },
  	{ NOTHING,  150 },
  	{ A,         20 },
  	{ NOTHING,  250 },
  
  	// バツチー郡駅クリアループを25回。もっと綺麗にfor文とかで書きたいんですけどやり方が分かりませんでした助けて
  	{ X,         20 }, 
  	{ NOTHING,   10 },
  	{ A,         10 },
  	{ NOTHING,   10 },
  	{ A,         20 },
  	{ NOTHING,  360 },
  	{ A,         20 },
  	{ NOTHING,   30 },
  	{ UP,        80 },
  	{ A,         20 },
  	{ NOTHING,  180 },
  	// 少しだけ左に視点をずらす。これは往復してきた風船を狙うため。往復なしでもクリア可能だが、タイミングがシビアすぎてプログラミングでは対応不可能。
  	// スティックを右に入力するか左に入力するかは、ノーマルカメラかリバースカメラかによって変更する
  	{ R_RIGHT,  0.8 },
  	{ ZR,       177 },
  	{ NOTHING,  640 },
  	
  	{ X,         20 }, 
  	{ NOTHING,   10 },
  	{ A,         10 },
  	{ NOTHING,   10 },
  	{ A,         20 },
  	{ NOTHING,  360 },
  	{ A,         20 },
  	{ NOTHING,   30 },
  	{ UP,        80 },
  	{ A,         20 },
  	{ NOTHING,  180 },
  	{ R_RIGHT,  0.8 },
  	{ ZR,       177 },
  	{ NOTHING,  640 },
  	
  	{ X,         20 }, 
  	{ NOTHING,   10 },
  	{ A,         10 },
  	{ NOTHING,   10 },
  	{ A,         20 },
  	{ NOTHING,  360 },
  	{ A,         20 },
  	{ NOTHING,   30 },
  	{ UP,        80 },
  	{ A,         20 },
  	{ NOTHING,  180 },
  	{ R_RIGHT,  0.8 },
  	{ ZR,       177 },
  	{ NOTHING,  640 },
  
  	{ X,         20 }, 
  	{ NOTHING,   10 },
  	{ A,         10 },
  	{ NOTHING,   10 },
  	{ A,         20 },
  	{ NOTHING,  360 },
  	{ A,         20 },
  	{ NOTHING,   30 },
  	{ UP,        80 },
  	{ A,         20 },
  	{ NOTHING,  180 },
  	{ R_RIGHT,  0.8 },
  	{ ZR,       177 },
  	{ NOTHING,  640 },
  
  	{ X,         20 }, 
  	{ NOTHING,   10 },
  	{ A,         10 },
  	{ NOTHING,   10 },
  	{ A,         20 },
  	{ NOTHING,  360 },
  	{ A,         20 },
  	{ NOTHING,   30 },
  	{ UP,        80 },
  	{ A,         20 },
  	{ NOTHING,  180 },
  	{ R_RIGHT,  0.8 },
  	{ ZR,       177 },
  	{ NOTHING,  640 },
  
  	{ X,         20 }, 
  	{ NOTHING,   10 },
  	{ A,         10 },
  	{ NOTHING,   10 },
  	{ A,         20 },
  	{ NOTHING,  360 },
  	{ A,         20 },
  	{ NOTHING,   30 },
  	{ UP,        80 },
  	{ A,         20 },
  	{ NOTHING,  180 },
  	{ R_RIGHT,  0.8 },
  	{ ZR,       177 },
  	{ NOTHING,  640 },
  
  	{ X,         20 }, 
  	{ NOTHING,   10 },
  	{ A,         10 },
  	{ NOTHING,   10 },
  	{ A,         20 },
  	{ NOTHING,  360 },
  	{ A,         20 },
  	{ NOTHING,   30 },
  	{ UP,        80 },
  	{ A,         20 },
  	{ NOTHING,  180 },
  	{ R_RIGHT,  0.8 },
  	{ ZR,       177 },
  	{ NOTHING,  640 },
  
  	{ X,         20 }, 
  	{ NOTHING,   10 },
  	{ A,         10 },
  	{ NOTHING,   10 },
  	{ A,         20 },
  	{ NOTHING,  360 },
  	{ A,         20 },
  	{ NOTHING,   30 },
  	{ UP,        80 },
  	{ A,         20 },
  	{ NOTHING,  180 },
  	{ R_RIGHT,  0.8 },
  	{ ZR,       177 },
  	{ NOTHING,  640 },
  
  	{ X,         20 }, 
  	{ NOTHING,   10 },
  	{ A,         10 },
  	{ NOTHING,   10 },
  	{ A,         20 },
  	{ NOTHING,  360 },
  	{ A,         20 },
  	{ NOTHING,   30 },
  	{ UP,        80 },
  	{ A,         20 },
  	{ NOTHING,  180 },
  	{ R_RIGHT,  0.8 },
  	{ ZR,       177 },
  	{ NOTHING,  640 },
  
  	{ X,         20 }, 
  	{ NOTHING,   10 },
  	{ A,         10 },
  	{ NOTHING,   10 },
  	{ A,         20 },
  	{ NOTHING,  360 },
  	{ A,         20 },
  	{ NOTHING,   30 },
  	{ UP,        80 },
  	{ A,         20 },
  	{ NOTHING,  180 },
  	{ R_RIGHT,  0.8 },
  	{ ZR,       177 },
  	{ NOTHING,  640 },
  
  	{ X,         20 }, 
  	{ NOTHING,   10 },
  	{ A,         10 },
  	{ NOTHING,   10 },
  	{ A,         20 },
  	{ NOTHING,  360 },
  	{ A,         20 },
  	{ NOTHING,   30 },
  	{ UP,        80 },
  	{ A,         20 },
  	{ NOTHING,  180 },
  	{ R_RIGHT,  0.8 },
  	{ ZR,       177 },
  	{ NOTHING,  640 },
  
  	{ X,         20 }, 
  	{ NOTHING,   10 },
  	{ A,         10 },
  	{ NOTHING,   10 },
  	{ A,         20 },
  	{ NOTHING,  360 },
  	{ A,         20 },
  	{ NOTHING,   30 },
  	{ UP,        80 },
  	{ A,         20 },
  	{ NOTHING,  180 },
  	{ R_RIGHT,  0.8 },
  	{ ZR,       177 },
  	{ NOTHING,  640 },
  
  	{ X,         20 }, 
  	{ NOTHING,   10 },
  	{ A,         10 },
  	{ NOTHING,   10 },
  	{ A,         20 },
  	{ NOTHING,  360 },
  	{ A,         20 },
  	{ NOTHING,   30 },
  	{ UP,        80 },
  	{ A,         20 },
  	{ NOTHING,  180 },
  	{ R_RIGHT,  0.8 },
  	{ ZR,       177 },
  	{ NOTHING,  640 },
  
  	{ X,         20 }, 
  	{ NOTHING,   10 },
  	{ A,         10 },
  	{ NOTHING,   10 },
  	{ A,         20 },
  	{ NOTHING,  360 },
  	{ A,         20 },
  	{ NOTHING,   30 },
  	{ UP,        80 },
  	{ A,         20 },
  	{ NOTHING,  180 },
  	{ R_RIGHT,  0.8 },
  	{ ZR,       177 },
  	{ NOTHING,  640 },
  	
  	{ X,         20 }, 
  	{ NOTHING,   10 },
  	{ A,         10 },
  	{ NOTHING,   10 },
  	{ A,         20 },
  	{ NOTHING,  360 },
  	{ A,         20 },
  	{ NOTHING,   30 },
  	{ UP,        80 },
  	{ A,         20 },
  	{ NOTHING,  180 },
  	{ R_RIGHT,  0.8 },
  	{ ZR,       177 },
  	{ NOTHING,  640 },
  
  	{ X,         20 }, 
  	{ NOTHING,   10 },
  	{ A,         10 },
  	{ NOTHING,   10 },
  	{ A,         20 },
  	{ NOTHING,  360 },
  	{ A,         20 },
  	{ NOTHING,   30 },
  	{ UP,        80 },
  	{ A,         20 },
  	{ NOTHING,  180 },
  	{ R_RIGHT,  0.8 },
  	{ ZR,       177 },
  	{ NOTHING,  640 },
  
  	{ X,         20 }, 
  	{ NOTHING,   10 },
  	{ A,         10 },
  	{ NOTHING,   10 },
  	{ A,         20 },
  	{ NOTHING,  360 },
  	{ A,         20 },
  	{ NOTHING,   30 },
  	{ UP,        80 },
  	{ A,         20 },
  	{ NOTHING,  180 },
  	{ R_RIGHT,  0.8 },
  	{ ZR,       177 },
  	{ NOTHING,  640 },
  
  	{ X,         20 }, 
  	{ NOTHING,   10 },
  	{ A,         10 },
  	{ NOTHING,   10 },
  	{ A,         20 },
  	{ NOTHING,  360 },
  	{ A,         20 },
  	{ NOTHING,   30 },
  	{ UP,        80 },
  	{ A,         20 },
  	{ NOTHING,  180 },
  	{ R_RIGHT,  0.8 },
  	{ ZR,       177 },
  	{ NOTHING,  640 },
  
  	{ X,         20 }, 
  	{ NOTHING,   10 },
  	{ A,         10 },
  	{ NOTHING,   10 },
  	{ A,         20 },
  	{ NOTHING,  360 },
  	{ A,         20 },
  	{ NOTHING,   30 },
  	{ UP,        80 },
  	{ A,         20 },
  	{ NOTHING,  180 },
  	{ R_RIGHT,  0.8 },
  	{ ZR,       177 },
  	{ NOTHING,  640 },
  
  	{ X,         20 }, 
  	{ NOTHING,   10 },
  	{ A,         10 },
  	{ NOTHING,   10 },
  	{ A,         20 },
  	{ NOTHING,  360 },
  	{ A,         20 },
  	{ NOTHING,   30 },
  	{ UP,        80 },
  	{ A,         20 },
  	{ NOTHING,  180 },
  	{ R_RIGHT,  0.8 },
  	{ ZR,       177 },
  	{ NOTHING,  640 },
  
  	{ X,         20 }, 
  	{ NOTHING,   10 },
  	{ A,         10 },
  	{ NOTHING,   10 },
  	{ A,         20 },
  	{ NOTHING,  360 },
  	{ A,         20 },
  	{ NOTHING,   30 },
  	{ UP,        80 },
  	{ A,         20 },
  	{ NOTHING,  180 },
  	{ R_RIGHT,  0.8 },
  	{ ZR,       177 },
  	{ NOTHING,  640 },
  
  	{ X,         20 }, 
  	{ NOTHING,   10 },
  	{ A,         10 },
  	{ NOTHING,   10 },
  	{ A,         20 },
  	{ NOTHING,  360 },
  	{ A,         20 },
  	{ NOTHING,   30 },
  	{ UP,        80 },
  	{ A,         20 },
  	{ NOTHING,  180 },
  	{ R_RIGHT,  0.8 },
  	{ ZR,       177 },
  	{ NOTHING,  640 },
  
  	{ X,         20 }, 
  	{ NOTHING,   10 },
  	{ A,         10 },
  	{ NOTHING,   10 },
  	{ A,         20 },
  	{ NOTHING,  360 },
  	{ A,         20 },
  	{ NOTHING,   30 },
  	{ UP,        80 },
  	{ A,         20 },
  	{ NOTHING,  180 },
  	{ R_RIGHT,  0.8 },
  	{ ZR,       177 },
  	{ NOTHING,  640 },
  
  	{ X,         20 }, 
  	{ NOTHING,   10 },
  	{ A,         10 },
  	{ NOTHING,   10 },
  	{ A,         20 },
  	{ NOTHING,  360 },
  	{ A,         20 },
  	{ NOTHING,   30 },
  	{ UP,        80 },
  	{ A,         20 },
  	{ NOTHING,  180 },
  	{ R_RIGHT,  0.8 },
  	{ ZR,       177 },
  	{ NOTHING,  640 },
  
  	{ X,         20 }, 
  	{ NOTHING,   10 },
  	{ A,         10 },
  	{ NOTHING,   10 },
  	{ A,         20 },
  	{ NOTHING,  360 },
  	{ A,         20 },
  	{ NOTHING,   30 },
  	{ UP,        80 },
  	{ A,         20 },
  	{ NOTHING,  180 },
  	{ R_RIGHT,  0.8 },
  	{ ZR,       177 },
  	{ NOTHING,  640 },
  	
  	// バツチー郡駅から自販機まで移動
  	// マップを開く
  	{ X,         20 }, 
  	{ NOTHING,   10 },
  	// 中央駅までカーソル移動
  	{ LEFT,       5 }, 
  	{ NOTHING,   10 },
  	{ DOWN,       5 }, 
  	{ NOTHING,   10 },
  	{ DOWN,       5 }, 
  	{ NOTHING,   10 },
  	{ RIGHT,      5 }, 
  	{ NOTHING,   10 },
  	{ RIGHT,      5 }, 
  	{ NOTHING,   10 },
  	{ DOWN,       5 }, 
  	{ NOTHING,   10 },
  	// 中央駅選択
  	{ A,          5 },
  	{ NOTHING,   10 },
  	{ A,          5 },
  	// ロード
  	{ NOTHING,  250 },
  	// 前進
  	{ UP,        80 },
  	{ NOTHING,   20 },
  	// 右を向く
  	{ RIGHT,     10 },
  	{ Y,          5 },
  	{ NOTHING,   20 },
  	// ロッカーにぶつかるまで前進
  	{ UP,       400 },
  	// 左を向く
  	{ LEFT,      10 },
  	{ Y,          5 },
  	{ NOTHING,   20 },
  	// 段ボールにぶつかるまで前進
  	{ UP,        30 },
	// 自販機の方を向く
  	{ RIGHT,     10 },
  	
  	// ポイント交換
  	{ A,          5 },
  	{ NOTHING,   10 },
  	{ RIGHT,      5 },
  	{ NOTHING,   10 },
  	{ A,          5 },
  	{ NOTHING,  150 },
  	{ CAPTURE,   10 },
  	{ A,          5 },
  	{ NOTHING,   20 },
	
	// 中央駅からバツチー郡駅に移動
	{ PLUS,       5 },
	{ NOTHING,   15 },
	{ DOWN,       5 },
	{ NOTHING,   15 },
	{ A,          5 },
	{ NOTHING,  240 },
	{ X,         20 },
	{ NOTHING,   20 },
	{ UP,         5 },
	{ NOTHING,   10 },
	{ LEFT,       5 },
	{ NOTHING,   10 },
	{ LEFT,       5 },
	{ NOTHING,   10 },
	{ UP,         5 },
	{ NOTHING,   10 },
	{ UP,         5 },
	{ NOTHING,   10 },
	{ RIGHT,      5 },
	{ NOTHING,   10 },
	{ A,          5 },
	{ NOTHING,   10 },
	{ A,         20 },
	{ NOTHING,  360 },
	{ A,          5 },
	{ NOTHING,   30 },
	{ PLUS,       5 },
	{ NOTHING,   10 },
	{ DOWN,       5 },
	{ NOTHING,   10 },
	{ A,         20 },
	{ NOTHING,  200 }
};

// Main entry point.
int main(void) {
	// We'll start by performing hardware and peripheral setup.
	SetupHardware();
	// We'll then enable global interrupts for our use.
	GlobalInterruptEnable();
	// Once that's done, we'll enter an infinite loop.
	for (;;)
	{
		// We need to run our task to process and deliver data for our IN and OUT endpoints.
		HID_Task();
		// We also need to run the main USB management task.
		USB_USBTask();
	}
}

// Configures hardware and peripherals, such as the USB peripherals.
void SetupHardware(void) {
	// We need to disable watchdog if enabled by bootloader/fuses.
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	// We need to disable clock division before initializing the USB hardware.
	clock_prescale_set(clock_div_1);
	// We can then initialize our hardware and peripherals, including the USB stack.

	#ifdef ALERT_WHEN_DONE
	// Both PORTD and PORTB will be used for the optional LED flashing and buzzer.
	#warning LED and Buzzer functionality enabled. All pins on both PORTB and \
PORTD will toggle when printing is done.
	DDRD  = 0xFF; //Teensy uses PORTD
	PORTD =  0x0;
                  //We'll just flash all pins on both ports since the UNO R3
	DDRB  = 0xFF; //uses PORTB. Micro can use either or, but both give us 2 LEDs
	PORTB =  0x0; //The ATmega328P on the UNO will be resetting, so unplug it?
	#endif
	// The USB stack should be initialized last.
	USB_Init();
}

// Fired to indicate that the device is enumerating.
void EVENT_USB_Device_Connect(void) {
	// We can indicate that we're enumerating here (via status LEDs, sound, etc.).
}

// Fired to indicate that the device is no longer connected to a host.
void EVENT_USB_Device_Disconnect(void) {
	// We can indicate that our device is not ready (via status LEDs, sound, etc.).
}

// Fired when the host set the current configuration of the USB device after enumeration.
void EVENT_USB_Device_ConfigurationChanged(void) {
	bool ConfigSuccess = true;

	// We setup the HID report endpoints.
	ConfigSuccess &= Endpoint_ConfigureEndpoint(JOYSTICK_OUT_EPADDR, EP_TYPE_INTERRUPT, JOYSTICK_EPSIZE, 1);
	ConfigSuccess &= Endpoint_ConfigureEndpoint(JOYSTICK_IN_EPADDR, EP_TYPE_INTERRUPT, JOYSTICK_EPSIZE, 1);

	// We can read ConfigSuccess to indicate a success or failure at this point.
}

// Process control requests sent to the device from the USB host.
void EVENT_USB_Device_ControlRequest(void) {
	// We can handle two control requests: a GetReport and a SetReport.

	// Not used here, it looks like we don't receive control request from the Switch.
}

// Process and deliver data from IN and OUT endpoints.
void HID_Task(void) {
	// If the device isn't connected and properly configured, we can't do anything here.
	if (USB_DeviceState != DEVICE_STATE_Configured)
		return;

	// We'll start with the OUT endpoint.
	Endpoint_SelectEndpoint(JOYSTICK_OUT_EPADDR);
	// We'll check to see if we received something on the OUT endpoint.
	if (Endpoint_IsOUTReceived())
	{
		// If we did, and the packet has data, we'll react to it.
		if (Endpoint_IsReadWriteAllowed())
		{
			// We'll create a place to store our data received from the host.
			USB_JoystickReport_Output_t JoystickOutputData;
			// We'll then take in that data, setting it up in our storage.
			while(Endpoint_Read_Stream_LE(&JoystickOutputData, sizeof(JoystickOutputData), NULL) != ENDPOINT_RWSTREAM_NoError);
			// At this point, we can react to this data.

			// However, since we're not doing anything with this data, we abandon it.
		}
		// Regardless of whether we reacted to the data, we acknowledge an OUT packet on this endpoint.
		Endpoint_ClearOUT();
	}

	// We'll then move on to the IN endpoint.
	Endpoint_SelectEndpoint(JOYSTICK_IN_EPADDR);
	// We first check to see if the host is ready to accept data.
	if (Endpoint_IsINReady())
	{
		// We'll create an empty report.
		USB_JoystickReport_Input_t JoystickInputData;
		// We'll then populate this report with what we want to send to the host.
		GetNextReport(&JoystickInputData);
		// Once populated, we can output this data to the host. We do this by first writing the data to the control stream.
		while(Endpoint_Write_Stream_LE(&JoystickInputData, sizeof(JoystickInputData), NULL) != ENDPOINT_RWSTREAM_NoError);
		// We then send an IN packet on this endpoint.
		Endpoint_ClearIN();
	}
}

typedef enum {
	SYNC_CONTROLLER,
	SYNC_POSITION,
	BREATHE,
	PROCESS,
	CLEANUP,
	DONE
} State_t;
State_t state = SYNC_CONTROLLER;

#define ECHOES 2
int echoes = 0;
USB_JoystickReport_Input_t last_report;

int report_count = 0;
int xpos = 0;
int ypos = 0;
int bufindex = 0;
int duration_count = 0;
int portsval = 0;

// Prepare the next report for the host.
void GetNextReport(USB_JoystickReport_Input_t* const ReportData) {

	// Prepare an empty report
	memset(ReportData, 0, sizeof(USB_JoystickReport_Input_t));
	ReportData->LX = STICK_CENTER;
	ReportData->LY = STICK_CENTER;
	ReportData->RX = STICK_CENTER;
	ReportData->RY = STICK_CENTER;
	ReportData->HAT = HAT_CENTER;

	// Repeat ECHOES times the last report
	if (echoes > 0)
	{
		memcpy(ReportData, &last_report, sizeof(USB_JoystickReport_Input_t));
		echoes--;
		return;
	}

	// States and moves management
	switch (state)
	{

		case SYNC_CONTROLLER:
			state = BREATHE;
			break;

		// case SYNC_CONTROLLER:
		// 	if (report_count > 550)
		// 	{
		// 		report_count = 0;
		// 		state = SYNC_POSITION;
		// 	}
		// 	else if (report_count == 250 || report_count == 300 || report_count == 325)
		// 	{
		// 		ReportData->Button |= SWITCH_L | SWITCH_R;
		// 	}
		// 	else if (report_count == 350 || report_count == 375 || report_count == 400)
		// 	{
		// 		ReportData->Button |= SWITCH_A;
		// 	}
		// 	else
		// 	{
		// 		ReportData->Button = 0;
		// 		ReportData->LX = STICK_CENTER;
		// 		ReportData->LY = STICK_CENTER;
		// 		ReportData->RX = STICK_CENTER;
		// 		ReportData->RY = STICK_CENTER;
		// 		ReportData->HAT = HAT_CENTER;
		// 	}
		// 	report_count++;
		// 	break;

		case SYNC_POSITION:
			bufindex = 0;


			ReportData->Button = 0;
			ReportData->LX = STICK_CENTER;
			ReportData->LY = STICK_CENTER;
			ReportData->RX = STICK_CENTER;
			ReportData->RY = STICK_CENTER;
			ReportData->HAT = HAT_CENTER;


			state = BREATHE;
			break;

		case BREATHE:
			state = PROCESS;
			break;

		case PROCESS:

			switch (step[bufindex].button)
			{

				case UP:
					ReportData->LY = STICK_MIN;				
					break;

				case LEFT:
					ReportData->LX = STICK_MIN;				
					break;

				case DOWN:
					ReportData->LY = STICK_MAX;				
					break;

				case RIGHT:
					ReportData->LX = STICK_MAX;				
					break;

				case R_UP:
					ReportData->RY = STICK_MIN;				
					break;

				case R_LEFT:
					ReportData->RX = STICK_MIN;				
					break;

				case R_DOWN:
					ReportData->RY = STICK_MAX;				
					break;

				case R_RIGHT:
					ReportData->RX = STICK_MAX;				
					break;

				case A:
					ReportData->Button |= SWITCH_A;
					break;

				case B:
					ReportData->Button |= SWITCH_B;
					break;

				case X:
					ReportData->Button |= SWITCH_X;
					break;

				case Y:
					ReportData->Button |= SWITCH_Y;
					break;

				case R:
					ReportData->Button |= SWITCH_R;
					break;

				case ZR:
					ReportData->Button |= SWITCH_ZR;
					break;

				case PLUS:
					ReportData->Button |= SWITCH_PLUS;
					break;

				case CAPTURE:
					ReportData->Button |= SWITCH_CAPTURE;
					break;

				case TRIGGERS:
					ReportData->Button |= SWITCH_L | SWITCH_R;
					break;

				default:
					ReportData->LX = STICK_CENTER;
					ReportData->LY = STICK_CENTER;
					ReportData->RX = STICK_CENTER;
					ReportData->RY = STICK_CENTER;
					ReportData->HAT = HAT_CENTER;
					break;
			}

			duration_count++;

			if (duration_count > step[bufindex].duration)
			{
				bufindex++;
				duration_count = 0;				
			}


			if (bufindex > (int)( sizeof(step) / sizeof(step[0])) - 1)
			{

				// state = CLEANUP;

				bufindex = 7;
				duration_count = 0;

				state = BREATHE;

				ReportData->LX = STICK_CENTER;
				ReportData->LY = STICK_CENTER;
				ReportData->RX = STICK_CENTER;
				ReportData->RY = STICK_CENTER;
				ReportData->HAT = HAT_CENTER;


				// state = DONE;
//				state = BREATHE;

			}

			break;

		case CLEANUP:
			state = DONE;
			break;

		case DONE:
			#ifdef ALERT_WHEN_DONE
			portsval = ~portsval;
			PORTD = portsval; //flash LED(s) and sound buzzer if attached
			PORTB = portsval;
			_delay_ms(250);
			#endif
			return;
	}

	// // Inking
	// if (state != SYNC_CONTROLLER && state != SYNC_POSITION)
	// 	if (pgm_read_byte(&(image_data[(xpos / 8) + (ypos * 40)])) & 1 << (xpos % 8))
	// 		ReportData->Button |= SWITCH_A;

	// Prepare to echo this report
	memcpy(&last_report, ReportData, sizeof(USB_JoystickReport_Input_t));
	echoes = ECHOES;

}
