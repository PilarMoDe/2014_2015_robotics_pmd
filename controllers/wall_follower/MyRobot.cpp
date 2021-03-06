/**
 * @file    MyRobot.cpp
 * @author Pilar Molina Delgado
 */

#include "MyRobot.h"

//////////////////////////////////////////////

MyRobot::MyRobot() : DifferentialWheels()
{
    _time_step = 64;

    _left_speed = 0;
    _right_speed = 0;

    // Get and enable the compass device
    _my_compass = getCompass("compass");
    _my_compass->enable(_time_step);
   // Sensor
    _distance_sensor[0] = getDistanceSensor("ds0");
    _distance_sensor[0]->enable(_time_step);
    _distance_sensor[1] = getDistanceSensor("ds1");
    _distance_sensor[1]->enable(_time_step);
    _distance_sensor[2] = getDistanceSensor("ds2");
    _distance_sensor[2]->enable(_time_step);
    _distance_sensor[5] = getDistanceSensor("ds15");
    _distance_sensor[5]->enable(_time_step);
    _distance_sensor[4] = getDistanceSensor("ds14");
    _distance_sensor[4]->enable(_time_step);
    _distance_sensor[3] = getDistanceSensor("ds13");
    _distance_sensor[3]->enable(_time_step);

}


//////////////////////////////////////////////

MyRobot::~MyRobot()
{
    _my_compass->disable();
}

//////////////////////////////////////////////

void MyRobot::run()
{
    double compass_angle;

    double ir0_val = 0.0, ir1_val = 0.0, ir2_val = 0.0, ir14_val = 0.0,ir15_val = 0.0,ir13_val = 0.0;
    int cont=0;
    while (step(_time_step) != -1) {
        // Read the sensors
        const double *compass_val = _my_compass->getValues();
       
	ir0_val = _distance_sensor[0]->getValue();
	ir1_val = _distance_sensor[1]->getValue();
	ir2_val = _distance_sensor[2]->getValue();
	ir15_val = _distance_sensor[5]->getValue();
	ir14_val = _distance_sensor[4]->getValue();
        ir13_val = _distance_sensor[3]->getValue();

        // Convert compass bearing vector to angle, in degrees
        compass_angle = convert_bearing_to_degrees(compass_val);

        // Print sensor values to console
        cout << "Compass angle (degrees): " << compass_angle << endl;
        
	cout<< "Value sensor front (right): Ds0:"<<ir0_val<<"Ds1:"<<ir1_val<< "Ds2:"<<ir2_val<<endl;
	cout<< "Value sensor front (left): Ds15:"<<ir15_val<<"Ds14:"<<ir14_val<< "Ds13:"<<ir13_val<<endl;
      
        
       
          
       	 if (cont==0) {
		_left_speed = MAX_SPEED;
        	_right_speed = MAX_SPEED;
		
            
		if ((ir1_val > DISTANCE_LIMIT)|| (ir14_val > DISTANCE_LIMIT)){
		cont=1;
                cout<<"Backing up and turning left."<<endl;
		_left_speed = - MAX_SPEED / 3.0;
          	_right_speed = - MAX_SPEED / 20.0;
      		}
		}
		
		else {
			if ((ir1_val > DISTANCE_LIMIT)|| (ir14_val > DISTANCE_LIMIT)){
			cont=1;
		        cout<<"Backing up and turning left."<<endl;
			_left_speed = - MAX_SPEED / 3.0;
		  	_right_speed = - MAX_SPEED / 20.0;
      			}
		
      			else{
        			if (ir13_val > DISTANCE_LIMIT) {
          		
           			cout << "Turning left." << endl;
          			_left_speed = MAX_SPEED / 2.0;
          			_right_speed = MAX_SPEED;
       			 	} 
          		else {
        
         		 if (ir13_val < (DISTANCE_LIMIT+50)) {
           		 
		      		cout << "Turning right." << endl;
		   		 _left_speed = MAX_SPEED;
          		        	_right_speed = MAX_SPEED / 2.0;
          			} 
          	
				else{
  				cont=0;
					// Move straight forward
					cout << "Moving forward." << endl;
					_left_speed = MAX_SPEED;
					_right_speed = MAX_SPEED;
					cont=0;
					}
			      }
			     }
            		}
        
        
        // Set the motor speeds
        setSpeed(_left_speed, _right_speed);
    }
}




//////////////////////////////////////////////

double MyRobot::convert_bearing_to_degrees(const double* in_vector)
{
    double rad = atan2(in_vector[0], in_vector[2]);
    double deg = rad * (180.0 / M_PI);

    return deg;
    
}

//////////////////////////////////////////////
