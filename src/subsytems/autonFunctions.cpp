#include "main.h"
#include "intake.hpp"
#include <utility>
okapi::IMU  inertial = IMU(7);
double initAngle=0;
void roller(){
    leftDrive.moveVelocity(-25);//set the drivetrain to move back at 25rpm
    rightDrive.moveVelocity(-25);//we do 25 rpm to reduce the torque needed to do the roller.
    intakeMotor.moveVelocity(300); //move the roller at max speed
    pros::delay(300); //wait half a second to allow roller to spin to our color 
    leftDrive.moveVelocity(0);
    rightDrive.moveVelocity(0);
    intakeMotor.moveVelocity(0); //cut everyting besides flywheel
}
void driveForward(double distance) {
    okapi::IterativePosPIDController drivePID = okapi::IterativeControllerFactory::posPID(0.8, 0., 0.007); //create a new drive object with specified pid

    const double target = distance; //idk why not just use distance

    drivePID.setTarget(target); //tels PROS: to move the drive using pid to distance

    double orgPosX = drive->getState().x.convert(okapi::foot); //store the orginal position
    double orgPosY = drive->getState().y.convert(okapi::foot);

    double distTravelled = 0;

    while (abs(target-distTravelled) >= 0.2 || abs(leftDrive.getActualVelocity())>10) {//pid shit i think idk
    // condition :abs(target-distTravelled) >= 0.2
        double dx = drive->getState().x.convert(okapi::foot) - orgPosX;
        double dy = drive->getState().y.convert(okapi::foot) - orgPosY;

        distTravelled = sqrt(dx*dx + dy*dy);
        
        double vel = drivePID.step(distTravelled);

        drive -> getModel() -> tank(vel, vel);

        pros::delay(10);
         pros::lcd::set_text(1, std::to_string(drive->getState().x.convert(okapi::foot))); //displays the X coordinate on the LCD of the screen per tick
         pros::lcd::set_text(2, std::to_string(drive->getState().y.convert(okapi::foot))); //displays the X coordinate on the LCD of the screen per tick

    }
}

  


void driveBlorward(double distance, double scalar) {
    okapi::IterativePosPIDController drivePID = okapi::IterativeControllerFactory::posPID(0.75, 0.01, 0.01); //create a new drive object with specified pid

    const double target = distance; //idk why not just use distance

    drivePID.setTarget(target); //tels PROS: to move the drive using pid to distance

    double orgPosX = drive->getState().x.convert(okapi::foot); //store the orginal position
    double orgPosY = drive->getState().y.convert(okapi::foot);

    double distTravelled = 69696.420; //idk what this does but jad has it

    while (abs(target-distTravelled) >= 0.2) { //pid shit i think idk
        double dx = drive->getState().x.convert(okapi::foot) - orgPosX;
        double dy = drive->getState().y.convert(okapi::foot) - orgPosY;

        distTravelled = sqrt(dx*dx + dy*dy);
        
        double vel = drivePID.step(distTravelled);

        drive -> getModel() -> tank(vel * scalar, vel * scalar);

        pros::delay(10);
    }

    drivePID.reset(); //reset everything to move relitive 
    drive -> getModel() -> tank(0, 0); //stop the drive once target is met
}

void index( int target){ //turn on indexer at max rpm for 10 ms 
while(flywheel.getActualVelocity()>target-10){ //allow 20 rpm diff
   intakeMotor.moveVelocity(-600);
   pros::delay(100);
   intakeMotor.moveVelocity(0);
   pros::delay(100);

}
intakeMotor.moveVelocity(0);
}
void indexLast(int target){
   while(flywheel.getActualVelocity()> target-20){ //allow 20 rpm diff
   intakeMotor.moveVelocity(-600);
}
intakeMotor.moveVelocity(0);
    
}
void turnToAngle(double targetAngle){ //turn non-relitive to given target (degrees)
   // angle in degrees

    okapi::IterativePosPIDController rotatePID = okapi::IterativeControllerFactory::posPID(0.03, 0.0004, 0.0003);
    //ani: 0.4553769998, 0.001, 0.01049997
    
    rotatePID.setTarget(targetAngle);

    // double initAngle = drive->getState().theta.convert(okapi::degree);
    double initAngle = inertial.controllerGet(); 

    while (abs(targetAngle - initAngle) >= 3 || abs(leftDrive.getActualVelocity())>10) {
        //condition: abs(targetAngle - initAngle) >= 3 || abs(leftDrive.getActualVelocity())>300
        // initAngle = drive->getState().theta.convert(okapi::degree);
        initAngle = inertial.controllerGet(); 
        double vel = rotatePID.step(initAngle);
        drive -> getModel() -> tank(vel, -vel);//turn faster by moving the other side the oppisite way
        pros::delay(20);
    }
    
    rotatePID.reset();


    drive -> getModel() -> tank(0, 0);

}
