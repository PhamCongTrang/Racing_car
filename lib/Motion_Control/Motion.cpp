// FUNCTION DIEU KHIEN 2 DONG CO
// DONG CO DC GAN VOI BANH SAU THONG QUA L298N
// DONG CO SERVO DIEU HUONG PHIA TRUOC DIEU KHIEN TRUC TIEP QUA ARDUINO UNO
#include "Motion.h"

void Motion::Motion(int speed, int theta)
{
    // DC MOTOR
    
    motorController.move(speed);
    //SERVO MOTOR  
    
    myservo.write(theta);
}