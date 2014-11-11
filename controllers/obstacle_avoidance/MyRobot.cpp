/**
 * @file    main_obstacle_avoidance.cpp
 * @brief   A obtacle avoidance for webots projects.
 *
 * @author  Pilar Molina <100073815@alumnos.uc3m.es>
 * @date    2014-11-11
 */

#include "MyRobot.h"

//////////////////////////////////////////////

MyRobot::MyRobot() : DifferentialWheels()
{
    // Enable distance sensor and initialitation values speed

    _time_step = 64;
    // Initialitation speed
    _left_speed = 0;
    _right_speed = 0;

    _mode = FORWARD;
    //Enable distance sensor
    _distance_sensor[0] = getDistanceSensor("ds0");
    _distance_sensor[0]->enable(_time_step);
    _distance_sensor[1] = getDistanceSensor("ds1");
    _distance_sensor[1]->enable(_time_step);
    _distance_sensor[2] = getDistanceSensor("ds2");
    _distance_sensor[2]->enable(_time_step);
    _distance_sensor[3] = getDistanceSensor("ds3");
    _distance_sensor[3]->enable(_time_step);
    _distance_sensor[4] = getDistanceSensor("ds4");
    _distance_sensor[4]->enable(_time_step);
    _distance_sensor[5] = getDistanceSensor("ds5");
    _distance_sensor[5]->enable(_time_step);
    _distance_sensor[6] = getDistanceSensor("ds6");
    _distance_sensor[6]->enable(_time_step);
    _distance_sensor[7] = getDistanceSensor("ds7");
    _distance_sensor[7]->enable(_time_step);
    _distance_sensor[8] = getDistanceSensor("ds8");
    _distance_sensor[8]->enable(_time_step);
    _distance_sensor[9] = getDistanceSensor("ds9");
    _distance_sensor[9]->enable(_time_step);
    _distance_sensor[10] = getDistanceSensor("ds10");
    _distance_sensor[10]->enable(_time_step);
    _distance_sensor[11] = getDistanceSensor("ds11");
    _distance_sensor[11]->enable(_time_step);
    _distance_sensor[12] = getDistanceSensor("ds12");
    _distance_sensor[12]->enable(_time_step);
    _distance_sensor[13] = getDistanceSensor("ds13");
    _distance_sensor[13]->enable(_time_step);
    _distance_sensor[14] = getDistanceSensor("ds14");
    _distance_sensor[14]->enable(_time_step);
    _distance_sensor[15] = getDistanceSensor("ds15");
    _distance_sensor[15]->enable(_time_step);

}

//////////////////////////////////////////////

MyRobot::~MyRobot()
{
    //Disable sensor

    for (int i=0; i<NUM_DISTANCE_SENSOR; i++) {
        _distance_sensor[i]->disable();
    }
}

//////////////////////////////////////////////

void MyRobot::run()
{    
    // Initialitation the values sensors
    double ir0_val = 0.0, ir1_val = 0.0,ir2_val = 0.0,ir3_val = 0.0,ir4_val = 0.0,ir5_val = 0.0,ir6_val = 0.0,ir7_val = 0.0,ir8_val = 0.0,
            ir9_val = 0.0,ir10_val = 0.0,ir11_val = 0.0,ir12_val = 0.0,ir13_val = 0.0,ir14_val = 0.0,ir15_val = 0.0;

    while (step(_time_step) != -1) {
        // Read the sensors
        ir0_val = _distance_sensor[0]->getValue();
        ir1_val = _distance_sensor[1]->getValue();
        ir2_val = _distance_sensor[2]->getValue();
        ir3_val = _distance_sensor[3]->getValue();
        ir4_val = _distance_sensor[4]->getValue();
        ir5_val = _distance_sensor[5]->getValue();
        ir6_val = _distance_sensor[6]->getValue();
        ir7_val = _distance_sensor[7]->getValue();
        ir8_val = _distance_sensor[8]->getValue();
        ir9_val = _distance_sensor[9]->getValue();
        ir10_val = _distance_sensor[10]->getValue();
        ir11_val = _distance_sensor[11]->getValue();
        ir12_val = _distance_sensor[12]->getValue();
        ir13_val = _distance_sensor[13]->getValue();
        ir14_val = _distance_sensor[14]->getValue();
        ir15_val = _distance_sensor[15]->getValue();

        cout << "ds1: " << ir1_val << " ds14:" << ir14_val << endl;
        cout << "ds3: " << ir1_val << " ds4:" << ir14_val << endl;
        cout << "ds12: " << ir1_val << " ds11:" << ir14_val << endl;
        // Control logic of the robot
        // When we have an obstacle to right or left
        if ((ir1_val > DISTANCE_LIMIT) || (ir14_val > DISTANCE_LIMIT)||(ir0_val > DISTANCE_LIMIT)||(ir15_val > DISTANCE_LIMIT)) {
            if (ir13_val>ir2_val){
                _mode = OBSTACLE_AVOID_L;
                cout << "Backing up and turning left." << endl;
            }
            if (ir13_val<ir2_val){
                _mode = OBSTACLE_AVOID_R;
                cout << "Backing up and turning right." << endl;
            }

        }

        else {
            if(((ir12_val || ir11_val) > (ir13_val || ir14_val))||(ir9_val > DISTANCE_LIMIT)||(ir10_val > DISTANCE_LIMIT)||(ir8_val > DISTANCE_LIMIT)
                    ||(ir10_val<ir11_val)){
                _mode = TURN_LEFT;
                cout << "TURN LEFT." << endl;
            }
            if(((ir3_val|| ir4_val) > ir2_val)||(ir6_val > DISTANCE_LIMIT)||(ir5_val > DISTANCE_LIMIT)||(ir7_val > DISTANCE_LIMIT)|| (ir4_val>ir5_val)){
                _mode = TURN_RIGHT;
                cout << "TURN RIGHT" << endl;
            }

            if ((ir3_val && ir4_val && ir12_val && ir11_val)>= (DISTANCE_LIMIT-50)){
                _mode= OBSTACLE_TOTAL_FRONT;
                cout <<"Backing up"<<endl;
            }
            else {
                _mode = FORWARD;
                cout << "Moving forward." << endl;
            }
        }


        // Send actuators commands according to the mode
        switch (_mode){
        case STOP:
            _left_speed = 0;
            _right_speed = 0;
            break;
        case FORWARD:
            _left_speed = MAX_SPEED;
            _right_speed = MAX_SPEED;
            break;
        case TURN_LEFT:
            _left_speed = MAX_SPEED / 1.25;
            _right_speed = MAX_SPEED;
            break;
        case TURN_RIGHT:
            _left_speed = MAX_SPEED;
            _right_speed = MAX_SPEED / 1.25;
            break;
        case OBSTACLE_AVOID_L:
            _left_speed = -MAX_SPEED / 3.0;
            _right_speed = -MAX_SPEED / 20.0;
            break;
        case OBSTACLE_AVOID_R:
            _left_speed = -MAX_SPEED / 20.0;
            _right_speed = -MAX_SPEED / 3.0;
            break;
        case OBSTACLE_TOTAL_FRONT:
            _left_speed = -MAX_SPEED ;
            _right_speed = -MAX_SPEED;
            break;

        default:
            break;
        }

        // Set the motor speeds
        setSpeed(_left_speed, _right_speed);
    }
}

//////////////////////////////////////////////
