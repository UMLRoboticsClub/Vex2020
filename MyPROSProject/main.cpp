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
	left_mtr.move_relative(distance, speed);
	right_mtr.move_relative(-distance, speed);
	pros::delay(2000);
	return;
}

void drive_reverse(int distance, int speed){
	left_mtr.move_relative(-distance, speed);
	right_mtr.move_relative(distance, speed);
	pros::delay(2000);
	return;
}

void turn_right(){
	left_mtr.move_relative(440, 50);
	right_mtr.move_relative(440, 50);
	pros::delay(1000);
	return;
}

void turn_left(){
	left_mtr.move_relative(-440, 50);
	right_mtr.move_relative(-440, 50);
	pros::delay(1000);
	return;
}

void drive_square(int size, int speed){
	drive_forward(size,speed);
	turn_right();
	drive_forward(size, speed);
	turn_right();
	drive_forward(size,speed);
	turn_right();
	drive_forward(size, speed);
	turn_right();
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
drive_square(2000, 75);

	drive_forward(1000,75);
	turn_right();
	drive_reverse(1000, 75);
	turn_right();
	drive_forward(1000,75);
	turn_left();
	drive_forward(1000, 75);
	turn_left();
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
	pros::Motor left_mtr(2);
	pros::Motor right_mtr(3);

	while (false) {
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);
		int power = master.get_analog(ANALOG_LEFT_Y)/2;
		int turn = master.get_analog(ANALOG_RIGHT_X);

		left_mtr = power+turn;
		right_mtr = -power+turn;
		pros::delay(20);
	}

}
