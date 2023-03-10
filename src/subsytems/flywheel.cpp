#include "main.h"
#include "flywheel.hpp" //vs code has errors here but it compiles find idk why.
/*
control scheme 
holding L2 spins flywheel to max speed 
tapping L2 toggles flywheel at 350 rpm
*/
bool toggle=false; //toggles the motor on and off
bool held=false;
bool lock=false;//prevents the toggle spam (stuttering of the motor which is damaging)
bool reverse=false;
bool toggleRumble=true;
Motor flywheel(10,true,AbstractMotor::gearset::blue,AbstractMotor::encoderUnits::degrees);
void updateFlywheel(){
    
 if(controller.getDigital(ControllerDigital::L2) == 1){
    held=true;
    
    //using voltage instead of velocity to ignore pid and spin as fast as possible 
    if(!lock){ //lock is inverted to make more logical sense (easier to debug)
        toggle=!toggle; //swaps toggle 
    }
    lock=true;
 }
    if(controller.getDigital(ControllerDigital::L2) == 0){ //if the button is not being held, reset the lock to allow toggle to be changed
        lock=false;
        held=false;
    }

    //controll the flywheel based on toggling system above 
    if(flywheel.getActualVelocity()>350 && toggleRumble==true){
        controller.rumble(".");
        toggleRumble = false;
    }
    if(held){
        flywheel.moveVoltage(12000);//if button is held it goes to max rpm
        leftDrive.setBrakeMode(AbstractMotor::brakeMode::hold);
        rightDrive.setBrakeMode(AbstractMotor::brakeMode::hold);
    }
    else  if(toggle && held==false){
        flywheel.moveVelocity(360);
         //move the flywheel at 350 rpm if toggled 
         leftDrive.setBrakeMode(AbstractMotor::brakeMode::hold);
         rightDrive.setBrakeMode(AbstractMotor::brakeMode::hold); //set to hold to prevent moving while shooting 
    }
    
    else if(!toggle && held==false && !reverse){
        flywheel.moveVelocity(0); //stop the flywheel if toggle is off
        if(flywheel.getActualVelocity()<300){
            toggleRumble=true;
        }
        if(state==1){
            leftDrive.setBrakeMode(AbstractMotor::brakeMode::coast);
            rightDrive.setBrakeMode(AbstractMotor::brakeMode::coast);
        }
    }
         if(controller.getDigital(ControllerDigital::L1) == 1 && !toggle && !held){
        flywheel.moveVoltage(-12000);
        reverse=true;
    }
    if (controller.getDigital(ControllerDigital::L1)==0 && !held &&!toggle){
        flywheel.moveVelocity(0);
        reverse=false;
    }
    
   
    
 } //updateFlywheel Ends

   

       