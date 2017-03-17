#ifndef OI_H
#define OI_H

#include "WPILib.h"

class Btn: public Button {
public:
	Btn(Joystick* joystick, int buttonNumber);

	bool Get() override;
	Joystick* joystick;
	int buttonNumber;
};
class DriverJoystick: public Joystick {
public:
	DriverJoystick();

	Btn* winchUp;
	Btn* ballIntake;
	Btn* changeFront;
	Btn* jogBack;
};
class ShooterJoystick: public Joystick {
public:
	ShooterJoystick();

	Btn* winchUp;
	Btn* winchDown;
	Btn* winchStop;
	Btn* runHexapus;
	Btn* runIntake;
	Btn* shoot;
	Btn* unjam;
	Btn* gearCatchToggle;
	// Btn* gearCatchOut;
};

class OI {
public:
	std::shared_ptr<DriverJoystick> driverJoystick;
	std::shared_ptr<ShooterJoystick> shooterJoystick;

	void initSmartDashboardCommands();

public:
	OI();
};

#endif
