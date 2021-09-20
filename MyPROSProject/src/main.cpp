#include "main.h"
pros::Motor left_mtr(2);
pros::Motor right_mtr(3);
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


void drive_forward(int distance, int speed){
//	left_mtr.move_relative(distance, speed);
//	right_mtr.move_relative(-distance, speed);
//	pros::delay(2000);
	return;
}

void drive_reverse(int distance, int speed){
//	left_mtr.move_relative(-distance, speed);
//	right_mtr.move_relative(distance, speed);
//	pros::delay(2000);
	return;
}

void turn_right(){
//	left_mtr.move_relative(445, 25);
//	right_mtr.move_relative(445, 25);
//	pros::delay(1000);
	return;
}

void turn_left(){
//	left_mtr.move_relative(-445, 25);
//	right_mtr.move_relative(-445, 25);
//	pros::delay(1000);
	return;
}

void drive_square(int size, int speed){
/*	drive_forward(size,speed);
	turn_right();
	drive_forward(size, speed);
	turn_right();
	drive_forward(size,speed);
	turn_right();
	drive_forward(size, speed);
	turn_right();*/
}
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	//pros::Motor left_mtr(2);
	//pros::Motor right_mtr(3);

//pros::Motor drive_left_initializer(2, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);

	pros::lcd::register_btn1_cb(on_center_button);
	autonomous();
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
void competition_initialize() {
pros::lcd::set_text(2, "comp init!");

}

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
	pros::Motor rightForward_mtrA(2);
	pros::Motor rightForward_mtrB(3);

	pros::Motor leftForward_mtrA(12);
	pros::Motor leftForward_mtrB(13);

	pros::Motor leftbackward_mtrA(18);
	pros::Motor leftbackward_mtrB(19);

	pros::Motor rightbackward_mtrA(8);
	pros::Motor rightbackward_mtrB(9);
//drive_square(1000, 75);
/*
rightForward_mtrA = 25;
rightForward_mtrB = 25;

//LF
leftForward_mtrA = 25;
leftForward_mtrB = 25;

//LB
leftbackward_mtrA = 25;
leftbackward_mtrB = 25;

//RB
rightbackward_mtrA = 25;
rightbackward_mtrB = 25;
pros::delay(2000);
*/
}




/**
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
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	//define all the motor ports
	pros::Motor rightForward_mtrA(2);
	pros::Motor rightForward_mtrB(3);

	pros::Motor leftForward_mtrA(12);
	pros::Motor leftForward_mtrB(13);

	pros::Motor leftbackward_mtrA(18);
	pros::Motor leftbackward_mtrB(19);

	pros::Motor rightbackward_mtrA(8);
	pros::Motor rightbackward_mtrB(9);
	int speed_mod = 2;

	//set all motors to 0 at start

	//RF 'right forward motors'
	rightForward_mtrA = 0;
	rightForward_mtrB = 0;

	//LF
	leftForward_mtrA = 0;
	leftForward_mtrB = 0;

	//LB
	leftbackward_mtrA = 0;
	leftbackward_mtrB = 0;

	//RB
	rightbackward_mtrA = 0;
	rightbackward_mtrB = 0;
	pros::delay(20);
	while (true) {
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);
		int power = master.get_analog(ANALOG_RIGHT_Y)/speed_mod;
		int strafe = master.get_analog(ANALOG_RIGHT_X)/speed_mod;
		int turn = master.get_analog(ANALOG_LEFT_X)/speed_mod;

		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {//nitro button
				speed_mod = 1;
		}
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {//standard speed
				speed_mod = 2;
		}
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {//slow
				speed_mod = 3;
		}
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {//slow
				turn_left();
		}
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {//slow
				turn_right();
		}
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {//slow
				turn_right();
		}

//		left_mtr = power+turn;
//		right_mtr = -power+turn;
//		pros::delay(20);

		//RF weel
		rightForward_mtrA = power -strafe -turn;
		rightForward_mtrB = power -strafe -turn;

		//LF
		leftForward_mtrA = -power -strafe -turn;
		leftForward_mtrB = -power -strafe -turn;

		//LB
		leftbackward_mtrA = -power +strafe -turn;
		leftbackward_mtrB = -power +strafe -turn;

		//RB
		rightbackward_mtrA = power +strafe -turn;
		rightbackward_mtrB = power +strafe -turn;
pros::delay(20);


	}

}
