// Imports for writing to screen, Proteus I/O, motors
#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHMotor.h>
#include <FEHServo.h>
#include <FEHRCS.h>
#include <FEHUtility.h>
#define LINE_ON_RIGHT 0 
#define ON_LINE_FIRST 1
#define LINE_ON_LEFT 2
#define ON_LINE_SECOND 3

// Initialize analog input for cdS, digital input for microswitches, motors to move robot
AnalogInputPin cds1(FEHIO::P0_0);
DigitalEncoder right_encoder(FEHIO::P1_0);
DigitalEncoder left_encoder(FEHIO::P2_0);
FEHMotor left_motor(FEHMotor::Motor0,9);
FEHMotor right_motor(FEHMotor::Motor1,9);
FEHServo servo(FEHServo::Servo0);
AnalogInputPin optosensor(FEHIO::P3_0);

double counts = 550.0;

double degree_const = 112.5;

// Initialize motor power % (L:R ratio = 123:137)
double left_motor_power = 41.5;                                                                                                                                                                                                
double right_motor_power = 41.5;

// Initialize whether the motors move in reverse
bool left_reverse = true;
bool right_reverse = false;

// Function prototypes
void pauseMotors();
void move(double feet, bool left_rev, bool right_rev);
bool readMove(double feet, bool left_rev, bool right_rev);
void moveToPushLever(double feet, bool left_rev, bool right_rev);
void moveForTime(double feet, bool left_rev, bool right_rev);
void moveWithForce(double feet, bool left_rev, bool right_rev);
void rotate(int direction, double degrees, bool left_rev, bool right_rev);
void rotate_reverse(int direction, double degrees, bool left_rev, bool right_rev);
void moveUntilFrontHit(bool left_rev, bool right_rev);
int getReversePower(int power, bool reverse);
void flipRobotMovement();
void stopMotors();
void printCDSValuesIndefinitely();
void waitForLight();
void moveUpRamp(double feet, bool left_rev, bool right_rev);
void waitForSeconds(double seconds);
void wtfl();

// Non-main functions

// Pauses motors by setting their power to 0 followed by a brief pause
void pauseMotors() {
    left_motor.SetPercent(0);
    right_motor.SetPercent(0);
    Sleep(0.1);
}

// Turns motors on, moving robot as long as the input time 'time'; pauses robot afterwards
void move(double feet, bool left_rev, bool right_rev) {
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    int left_power = getReversePower(left_motor_power, left_rev);
    int right_power = getReversePower(right_motor_power, right_rev);
    left_motor.SetPercent(left_power * 0.95);
    right_motor.SetPercent(right_power * (1/0.95));
    // (avg power of 2 motors) * constant = 46.15
    while((left_encoder.Counts() + right_encoder.Counts()) / 1. < feet * counts * 1.451) {
        // LCD.WriteLine("left: ");
        // LCD.WriteLine(left_encoder.Counts());
        // LCD.WriteLine("right: ");
        // LCD.WriteLine(right_encoder.Counts());
        
    }
    pauseMotors();
}

// Turns motors on, moving robot as long as the input time 'time'; pauses robot afterwards
bool readMove(double feet, bool left_rev, bool right_rev) {
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    int left_power = getReversePower(left_motor_power, left_rev);
    int right_power = getReversePower(right_motor_power, right_rev);
    left_motor.SetPercent(left_power * 0.98);
    right_motor.SetPercent(right_power * (1/0.98));
    double min = 26.0;
    // (avg power of 2 motors) * constant = 46.15
    while((left_encoder.Counts() + right_encoder.Counts()) / 1. < feet * counts * 1.451) {
        // LCD.WriteLine("left: ");
        // LCD.WriteLine(left_encoder.Counts());
        // LCD.WriteLine("right: ");
        // LCD.WriteLine(right_encoder.Counts());
        double value = cds1.Value();
        if (value < min) {
            min = value;
        }
    }
    pauseMotors();
    LCD.Clear();
    if (min < 0.95) {
        // true = red
        LCD.Write("readMove: ");
        LCD.Write(min);
        Sleep(1.0);
        return true;
    } else {
        // default
        LCD.Write("readMove: ");
        LCD.Write(min);
        Sleep(1.0);
        return false;
    }
}

// Turns motors on, moving robot as long as the input time 'time'; pauses robot afterwards
void moveToPushLever(double feet, bool left_rev, bool right_rev) {
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    int left_power = getReversePower(left_motor_power, left_rev);
    int right_power = getReversePower(right_motor_power, right_rev);
    left_motor.SetPercent(left_power * 0.98);
    right_motor.SetPercent(right_power * (1/0.98));
    // (avg power of 2 motors) * constant = 46.15
    while((left_encoder.Counts() + right_encoder.Counts()) / 1. < feet * counts * 1.451) {
        // LCD.WriteLine("left: ");
        // LCD.WriteLine(left_encoder.Counts());
        // LCD.WriteLine("right: ");
        // LCD.WriteLine(right_encoder.Counts());
        
    }
    pauseMotors();
}

void moveForTime(double feet, bool left_rev, bool right_rev) {
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    int left_power = getReversePower(left_motor_power, left_rev);
    int right_power = getReversePower(right_motor_power, right_rev);
    left_motor.SetPercent(left_power);
    right_motor.SetPercent(right_power);
    // (avg power of 2 motors) * constant = 46.15
    Sleep(feet);
    pauseMotors();
}

void moveSlowForTime(double feet, bool left_rev, bool right_rev) {
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    int left_power = getReversePower(left_motor_power, left_rev);
    int right_power = getReversePower(right_motor_power, right_rev);
    left_motor.SetPercent(left_power * 0.5 * 0.98);
    right_motor.SetPercent(right_power * 0.5 * (1/0.98));
    // (avg power of 2 motors) * constant = 46.15
    Sleep(feet);
    pauseMotors();
}

// Turns motors on, moving robot as long as the input time 'time'; pauses robot afterwards
void moveBackwards(double feet, bool left_rev, bool right_rev) {
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    int left_power = getReversePower(left_motor_power, left_rev);
    int right_power = getReversePower(right_motor_power, right_rev);
    left_motor.SetPercent(left_power * 0.94);
    right_motor.SetPercent(right_power * (1/0.94));
    // (avg power of 2 motors) * constant = 46.15
    while((left_encoder.Counts() + right_encoder.Counts()) / 1. < feet * counts * 1.451) {
        // LCD.WriteLine("left: ");
        // LCD.WriteLine(left_encoder.Counts());
        // LCD.WriteLine("right: ");
        // LCD.WriteLine(right_encoder.Counts());
        
    }
    pauseMotors();
}

// Turns motors on, moving robot as long as the input time 'time'; pauses robot afterwards
void moveSlow(double feet, bool left_rev, bool right_rev) {
    int left_power = getReversePower(left_motor_power, left_rev);
    int right_power = getReversePower(right_motor_power, right_rev);
    left_motor.SetPercent(left_power * 0.5 * (1/0.95));
    right_motor.SetPercent(right_power * 0.5 * 0.975);
    // (avg power of 2 motors) * constant = 46.15
    while((left_encoder.Counts() + right_encoder.Counts()) / 1. < feet * counts * 1.451) {
        // LCD.WriteLine("left: ");
        // LCD.WriteLine(left_encoder.Counts());
        // LCD.WriteLine("right: ");
        // LCD.WriteLine(right_encoder.Counts());
        
    }
    pauseMotors();
}

// Turns motors on, moving robot as long as the input time 'time'; pauses robot afterwards
void moveWithForce(double feet, bool left_rev, bool right_rev) {
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    int left_power = getReversePower(left_motor_power * 2.2, left_rev);
    int right_power = getReversePower(right_motor_power * 2.2, right_rev);
    left_motor.SetPercent(left_power);
    right_motor.SetPercent(right_power);
    // (avg power of 2 motors) * constant = 46.15
    Sleep(feet);
    pauseMotors();
}

// Turns motors on, moving robot as long as the input time 'time'; pauses robot afterwards
void moveUpRamp(double feet, bool left_rev, bool right_rev) {
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    int left_power = getReversePower(left_motor_power, left_rev);
    int right_power = getReversePower(right_motor_power, right_rev);
    left_motor.SetPercent(left_power * 1.2);
    right_motor.SetPercent(right_power * 1.3);
    // (avg power of 2 motors) * constant = 46.15
    while((left_encoder.Counts() + right_encoder.Counts()) / 1. < feet * counts * 1.154) {
        // LCD.WriteLine("left: ");
        // LCD.WriteLine(left_encoder.Counts());
        // LCD.WriteLine("right: ");
        // LCD.WriteLine(right_encoder.Counts());
        
    }
    pauseMotors();
}

/*  Rotates the robot either counter-clockwise (-1) or clockwise (1) based on the input 'direction';
    rotates the robot to the degree parameter 'degrees' */
void rotate(int direction, double degrees, bool left_rev, bool right_rev) {
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    LCD.Clear();
    int left_power = getReversePower(left_motor_power, left_rev);
    int right_power = getReversePower(right_motor_power, right_rev);
    if (direction == -1) {
        right_motor.SetPercent(right_power);
        // (right motor power) * constant = 0.62335
        while((left_encoder.Counts() + right_encoder.Counts()) / 1. < degrees * counts / 112.5) {
            // LCD.WriteLine("left: ");
            // LCD.WriteLine(left_encoder.Counts());
            // LCD.WriteLine("right: ");
            // LCD.WriteLine(right_encoder.Counts());
        }
    } else {
        left_motor.SetPercent(left_power);
        // (left motor power) * constant = 0.64575
        while((left_encoder.Counts() + right_encoder.Counts()) / 1. < degrees * counts / 112.5) {
            // LCD.WriteLine("left: ");
            // LCD.WriteLine(left_encoder.Counts());
            // LCD.WriteLine("right: ");
            // LCD.WriteLine(right_encoder.Counts());
            
        }
    }
    pauseMotors();
}

// Rotates robot with 1 wheel moving backward instead of forward
void rotate_reverse(int direction, double degrees, bool left_rev, bool right_rev) {
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    int left_power = getReversePower(left_motor_power, left_rev);
    int right_power = getReversePower(right_motor_power, right_rev);
    if (direction == -1) {
        left_motor.SetPercent(left_power * -1);
        // (left motor power) * constant = 0.64575
        while((left_encoder.Counts() + right_encoder.Counts()) / 1. < degrees * counts / 112.5) {
            // LCD.WriteLine("left: ");
            // LCD.WriteLine(left_encoder.Counts());
            // LCD.WriteLine("right: ");
            // LCD.WriteLine(right_encoder.Counts());
            
        }
    } else {
        right_motor.SetPercent(right_power * -1);
        // (right motor power) * constant = 0.62335
        while((left_encoder.Counts() + right_encoder.Counts()) / 1. < degrees * counts / 115.0) {
            // LCD.WriteLine("left: ");
            // LCD.WriteLine(left_encoder.Counts());
            // LCD.WriteLine("right: ");
            // LCD.WriteLine(right_encoder.Counts());
            
        }
    }
    pauseMotors();
}

// Returns the negative power of motor if it is in reverse
int getReversePower(int power, bool reverse) {
    int returnPower = power;
    if (reverse) {
        returnPower *= -1;
    }
    return returnPower;
}

// Flips movement direction of robot
void flipRobotMovement() {
    left_reverse = !left_reverse;
    right_reverse = !right_reverse;
}

// Turns robot off
void stopMotors() {
    left_motor.Stop();
    right_motor.Stop();
    Sleep(0.1);
}

// Prints value detected by cdS cell forever
void printCDSValuesIndefinitely() {
    while (true) {
        LCD.Clear();
        LCD.WriteLine(cds1.Value());
        Sleep(0.1);
    }
}

// Pauses robot until a light has been detected by the cdS cell
void waitForLight() {
    while (cds1.Value() > 1.5) {
        LCD.Clear();
        LCD.Write(cds1.Value());
        Sleep(0.1);
    }
}

// Pauses robot until a light has been detected by the cdS cell
void waitForSeconds(double seconds) {
    double counter = 0.0;
    while (counter < seconds) {
        LCD.Clear();
        LCD.Write(cds1.Value());
        Sleep(0.1);
        counter += 0.1;
    }
}

enum LineStates {
    MIDDLE,
    RIGHT,
    LEFT
};


void followLine() {
    int state = MIDDLE; // Set the initial state
	while (optosensor.Value() > 0.2) { // I will follow this line forever!
		if (optosensor.Value() < 1.5) {
            left_motor.SetPercent(12.5);
            right_motor.SetPercent(37.5);
        } else {
            left_motor.SetPercent(37.5);
            right_motor.SetPercent(12.5);
        }
		// Sleep a bit
	}


}

void wtfl(){
    servo.SetDegree(30.0);
    Sleep(0.5);


    servo.SetDegree(60.0);
    Sleep(0.5);


    //turn right 10 degrees
    rotate(-1, 10.0, left_reverse, right_reverse);


    //Arm Down
    servo.SetDegree(30.0);
    Sleep(0.5);


    //Arm Up
    servo.SetDegree(60.0);
    Sleep(0.5);


    //turn left 20 degrees
    rotate(1, 20.0, left_reverse, right_reverse);


    //Arm down
    servo.SetDegree(30.0);
    Sleep(0.5);


    //Arm Up
    servo.SetDegree(60.0);
    Sleep(0.5);


    //turn right 10 degrees
    rotate(-1, 10.0, left_reverse, right_reverse);


    //drive back
    flipRobotMovement();
    moveBackwards(0.2, left_reverse, right_reverse);
    flipRobotMovement();
    Sleep(5);


    //Move Arm down
    servo.SetDegree(0);


    // Move forwards
    move(0.2125, left_reverse, right_reverse);


    //Arm up
    servo.SetDegree(45);


    //Arm down
    servo.SetDegree(0);


    //turn right 10 degrees
    rotate(-1, 10.0, left_reverse, right_reverse);


    //Arm Down
    servo.SetDegree(45);


    //Arm Up
    servo.SetDegree(0.0);
    Sleep(0.5);


    //turn left 20 degrees
    rotate(1, 20.0, left_reverse, right_reverse);


    //Arm down
    servo.SetDegree(45.0);


    //Arm Up
    servo.SetDegree(0.0);
    Sleep(0.5);


    //turn right 10 degrees
    rotate(-1, 10.0, left_reverse, right_reverse);


    // Move forwards
    move(0.2125, left_reverse, right_reverse);


    //Arm up
    servo.SetDegree(45);


    //Arm down
    servo.SetDegree(0);


    //turn right 10 degrees
    rotate(-1, 10.0, left_reverse, right_reverse);


    //Arm Down
    servo.SetDegree(30.0);


    //Arm Up
    servo.SetDegree(60.0);
    Sleep(0.5);


    //turn left 20 degrees
    rotate(1, 20.0, left_reverse, right_reverse);


    //Arm down
    servo.SetDegree(30.0);


    //Arm Up
    servo.SetDegree(60.0);
    Sleep(0.5);


    //turn right 10 degrees
    rotate(-1, 10.0, left_reverse, right_reverse);
}





// Main Function
int main(void) {

    // while (true) {
    //     LCD.Clear();
    //     LCD.Write(optosensor.Value());
    //     Sleep(0.1);
    // }


    // BEFORE RUN: Orient robot so it is facing northeast
    char team_key[] = "B8kqmgOaf";
    RCS.InitializeTouchMenu(team_key);
    // Adjust servo min and max
    servo.SetMin(520);
    servo.SetMax(2177);

    servo.SetDegree(180.0);

    // Code to test is arm rotates to correct min/median/max positions
//     servo.SetDegree(0.0);
//     LCD.Clear();
//     LCD.Write("0.0 deg");
//     Sleep(1.0);
//     servo.SetDegree(90.0);
//     LCD.Clear();
//     LCD.Write("90.0 deg");
//     Sleep(0.5);
//     servo.SetDegree(180.0);
//     LCD.Clear();
//     LCD.Write("180.0 deg");
//     Sleep(0.5);

    // CHECKPOINT 5

    // Wait for start light

    float x_position, y_position;
    float x_trash, y_trash;
    /* Clear the touch buffer so touches made before
           this call are discarded */
        LCD.ClearBuffer();
        /* Wait until the user touches the screen */
        while(!LCD.Touch(&x_position,&y_position)) {};
        /* Wait until the touch releases */
        while(LCD.Touch(&x_trash,&y_trash)) {};

    waitForLight();
    // Back up onto start light
    flipRobotMovement();
    moveBackwards(0.25, left_reverse, right_reverse);
    flipRobotMovement();
    // Move forwards
    move(1.0, left_reverse, right_reverse);
    // Rotate to face left
    rotate(-1, 48.0, left_reverse, right_reverse);
    // Back up onto right wall
    flipRobotMovement();
    moveBackwards(1.75, left_reverse, right_reverse);
    flipRobotMovement();
    // Move forwards
    move(0.61, left_reverse, right_reverse);
    // Rotate in reverse to face ramp
    rotate_reverse(1, 104.0, left_reverse, right_reverse);
    // Move up ramp
    moveUpRamp(3.1, left_reverse, right_reverse);
    // Rotate 90 degrees to the left
    rotate(-1, 87.0, left_reverse, right_reverse);
    // Move backwards into wall
    flipRobotMovement();
    moveForTime(1.0, left_reverse, right_reverse);
    flipRobotMovement();
    // Move left until above luggage deposit
    move(1.8525, left_reverse, right_reverse);
    // Rotate backwards so arm faces luggage deposit
    rotate_reverse(-1, 86.0, left_reverse, right_reverse);
    // Move forwards into luggage deposit
    moveForTime(0.9, left_reverse, right_reverse);

    flipRobotMovement();
    moveBackwards(0.2, left_reverse, right_reverse);
    flipRobotMovement();

    // Rotate arm down to deposit luggage and wait 1 second
    servo.SetDegree(90.0);
    Sleep(1.0);
    // Rotate arm back to 180 degrees
    servo.SetDegree(180.0);

    // Move backwards
    flipRobotMovement();
    moveBackwards(0.3, left_reverse, right_reverse);
    flipRobotMovement();

    // Rotate forwards to face left
    rotate(1, 96.0, left_reverse, right_reverse);
    // Back up into wall
    flipRobotMovement();
    moveSlowForTime(6.0, left_reverse, right_reverse);
    flipRobotMovement();

    rotate(1, 2.0, left_reverse, right_reverse);

    move(1.03, left_reverse, right_reverse);

    // Rotate backwards to face passport
    rotate_reverse(1, 106.0, left_reverse, right_reverse);

    // flipRobotMovement();
    // moveBackwards(0.05, left_reverse, right_reverse);
    // flipRobotMovement();

    // CHECKPOINT 4

    //Move arm down
    servo.SetDegree(0.0);
    Sleep(1.0);
    // Move forwards to go under passport stamp
    moveForTime(0.5, left_reverse, right_reverse);
    rotate(1, 1.0, left_reverse, right_reverse);

    // Flip Arm Up
    servo.SetDegree(60.0);
    Sleep(1.0);
    // Move fast for a short amount of time to flip passport stamp
    moveWithForce(0.15, left_reverse, right_reverse);
    Sleep(0.5);
    // Move backwards
    // flipRobotMovement();
    // moveBackwards(0.075, left_reverse, right_reverse);
    // flipRobotMovement();

    rotate_reverse(-1, 95.0, left_reverse, right_reverse);

    flipRobotMovement();
    moveBackwards(1.0, left_reverse, right_reverse);
    flipRobotMovement();

    move(0.525, left_reverse, right_reverse);
    
    // CHECKPOINT with CDS

    // Rotate to face ticket kiosk light
    rotate(1, 49.0, left_reverse, right_reverse);

    servo.SetDegree(180.0);

    // Move to ticket kiosk light
    
    bool forwardColor = readMove(1.75, left_reverse, right_reverse); 
    LCD.Clear();
    LCD.Write(forwardColor);
    moveForTime(0.5, left_reverse, right_reverse);
    Sleep(1.0);
    flipRobotMovement();
    bool backwardColor = readMove(0.34, left_reverse, right_reverse);
    flipRobotMovement();
    LCD.Clear();
    LCD.Write(forwardColor);
    Sleep(1.0);

    // Pause for a second and then read light to cdS cell
    waitForSeconds(1.0);
    double cdSValue = cds1.Value();
    // Set distance for robot to move based on cdS value
    double distToMove;
    if (!(forwardColor || backwardColor)) {
        LCD.Clear();
        LCD.Write("Blue");
        Sleep(0.1);
        distToMove = 0.53;
    } else {
        LCD.Clear();
        LCD.Write("Red");
        Sleep(0.1);
        distToMove = 1.125;
    }
    // Move robot forward into wall to align with it perpendicularly
    moveForTime(0.75, left_reverse, right_reverse); 

    flipRobotMovement();
    moveBackwards(0.1, left_reverse, right_reverse);
    flipRobotMovement();

    // Turn so robot is perpendicular to ticket kiosk
    rotate_reverse(-1, 41.0, left_reverse, right_reverse);

    // Move robot backwards a certain distance so it is either in front of red or blue button
    flipRobotMovement();
    moveBackwards(distToMove, left_reverse, right_reverse);
    flipRobotMovement();

    // Turn robot so it's rear is facing desired button
    rotate(-1, 84.0, left_reverse, right_reverse);

    // Move backwards to hit button
    flipRobotMovement();
    moveBackwards(1.0, left_reverse, right_reverse);
    flipRobotMovement();

    rotate(1, 10.0, left_reverse, right_reverse);

    // Move forward off of button
    move(1.25, left_reverse, right_reverse);

    // Turn backwards so back is facing right wall
    rotate_reverse(1, 82.0, left_reverse, right_reverse);

    // Move into left wall
    moveForTime(2.0, left_reverse, right_reverse);

    // Move backwards
    flipRobotMovement();
    moveBackwards(0.325, left_reverse, right_reverse);
    flipRobotMovement();
    // Rotate to face ramp
    rotate(-1, 84.0, left_reverse, right_reverse);

    // Move down ramp 
    move(1.8, left_reverse, right_reverse);

    // Rotate so back faces left wall
    rotate(-1, 86.0, left_reverse, right_reverse);

    // Back up into left wall
    flipRobotMovement();
    moveBackwards(1.0, left_reverse, right_reverse);
    flipRobotMovement();

    // Get lever value
    // int lever = RCS.GetCorrectLever();
    int lever = 2; 
    // Change distance to move based on lever value
    LCD.Write("Lever " + lever);
    double distToLever = 1.4;
    double extra = 0.125;
    if (lever == 2) {
        distToLever = 1.29;
    } else if (lever == 1) {
        distToLever = 1.0;
    } else {
        distToLever = 0.75;
    }
    // Move until north of desired lever
    move(distToLever, left_reverse, right_reverse);
    
    // Rotate backwards so arm aligns with lever
    rotate_reverse(1, 103.0, left_reverse, right_reverse);

    flipRobotMovement();
    moveBackwards(0.6, left_reverse, right_reverse);
    flipRobotMovement();

    move(0.39, left_reverse, right_reverse);
    
    // Turn arm to push lever down
    servo.SetDegree(30.0);
    Sleep(0.5);

    // Move arm up off lever
    servo.SetDegree(60.0);
    Sleep(0.5);

    // Move backwards
    flipRobotMovement();
    moveBackwards(0.2, left_reverse, right_reverse);
    flipRobotMovement();

    // Wait 5 seconds
    Sleep(5.0);

    // Turn arm down
    servo.SetDegree(0.0);
    Sleep(0.5);

    rotate(1, 1.0, left_reverse, right_reverse);

    // Move forwards
    move(0.2, left_reverse, right_reverse);

    // Move arm up to flip lever
    servo.SetDegree(45.0);
    Sleep(0.5);

    // Back up from levers
    flipRobotMovement();
    moveBackwards(0.5, left_reverse, right_reverse);
    flipRobotMovement();

    // Move arm up
    servo.SetDegree(180.0);

    rotate(-1, 42.0, left_reverse, right_reverse);

    // Move to press end button
    moveForTime(2.5, left_reverse, right_reverse);

    flipRobotMovement();
    moveBackwards(0.5, left_reverse, right_reverse);
    flipRobotMovement();

    moveForTime(1.0, left_reverse, right_reverse);

    flipRobotMovement();
    moveBackwards(0.5, left_reverse, right_reverse);
    flipRobotMovement();

    stopMotors();
    // End program
    return 0;
}