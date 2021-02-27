//604c_feb
#include "main.h"
using namespace pros;

Motor leftFrontMotor(20);
Motor leftBackMotor(14);
Motor rightFrontMotor(10);
Motor rightBackMotor(17);
Motor leftIntake(18);
Motor rightIntake(15);
Motor indexer(9);
Motor roller(19);
ADIGyro gyro(1);
Controller master(E_CONTROLLER_MASTER);
/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */



void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  gyro.reset();
	delay(2000);
	pros::lcd::initialize();

	pros::lcd::set_text(1, "Hello PROS User!");

}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	//intake(1);
	//drivestraight(80, 2000, 'f' );

	driveStraight(50, 1260, 'f', 0.1);

//	delay(1000);
//	intake(0);


}
/**
}
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	while(true){

		lcd::print(1, "lfm_postion = &4.0f", leftFrontMotor.get_position());
		lcd::print(2, "gyro_value = &4.0f", gyro.get_value());

		int leftY = master.get_analog(ANALOG_LEFT_Y);
	  int leftX = master.get_analog(ANALOG_LEFT_X);
		
		setPower(leftY, leftX);

		if(master.get_digital(DIGITAL_R1) == 1){
			rightIntake = 127;
			leftIntake = - 127;

		}
		else if(master.get_digital(DIGITAL_L1) == 1){
			roller = 127;
			rightIntake = -127;
			leftIntake = 127;
		}

		else if(master. get_digital(DIGITAL_R2) == 1){
			indexer = 127;
			roller = -127;

		}
		else if(master.get_digital(DIGITAL_L2) == 1){
			indexer = -127;
			roller = 127;
		}
		else{
			roller = 0;
			leftIntake = 0;
			rightIntake = 0;
			indexer = 0;
		}
	}
}
