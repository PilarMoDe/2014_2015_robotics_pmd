/**
 * @file    MyRobot.cpp
 * @brief   A obstacle_odometry for webots projects.
 *
 * @author  Pilar Molina Delgado <100073815@alumnos.uc3m.es>
 * @date    2014-11-11
 */

#include "MyRobot.h"

//////////////////////////////////////////////

MyRobot::MyRobot() : DifferentialWheels()
{
    _time_step = 64;

    desired_distance=0;
    desired_angle=0;

    enableEncoders(_time_step);

    // Get and enable the compass device
    _my_compass = getCompass("compass");
    _my_compass->enable(_time_step);

    _left_speed = 0;
    _right_speed = 0;
    _distance = 0;
    _status=0;
}

//////////////////////////////////////////////

MyRobot::~MyRobot()
{
    disableEncoders();

    _my_compass->disable();
}

//////////////////////////////////////////////

void MyRobot::run()
{
    double compass_angle;

    while (step(_time_step) != -1)
    {

        switch (_status)
        {
        //Place the robot
        case 0:
            desired_angle=85;
            break;
        //Diagonal movement a distance of 5.50 m
        case 1:
            desired_distance=5.50;
            desired_angle=85;
            break;
        //With the compass we are at 45 degrees to the straight movement
        case 2:
            desired_distance=0;
            desired_angle=45;
            break;
        //Straight movement whith comppas we are at 45 degrees
        case 3:
            desired_distance=12.50;
            desired_angle=45;
            break;
        //Stop when the robot has reached the yellow line that is to travel the distance we will have preset
        default:
            desired_distance=0;
            desired_angle=0;
            break;
        }

        // Read the sensors
        const double *compass_val = _my_compass->getValues();

        // Convert compass bearing vector to angle, in degrees
        compass_angle = convert_bearing_to_degrees(compass_val);

        _left_encoder = getLeftEncoder();
        _right_encoder = getRightEncoder();
        /// Distance measured from the encoders,1m 60.61 is that one encoder per revolution is 31416 and 0.5183 meters per lap or 6.28 rad if speed is 10rad / sec
        _distance = _left_encoder/60.61;

        //By screen printing grades , the distance traveled and the condition in which we find
        cout<< "Distance:   "<<_distance<< endl;
        cout<< "Angle:    "<< compass_angle<<endl;
        cout<< "Status:   "<< _status<< endl;

        if (_status<4)
        {
            if (((compass_angle<desired_angle-1)||(compass_angle>desired_angle+1)) && (_status==0))
            {
                //Inicialitation values encoders, spin in the same axis right.
                _left_speed = 10;
                _right_speed = 0;
                setEncoders(0,0);
                _distance = 0;
            }
            else if (((compass_angle<desired_angle-1)||(compass_angle>desired_angle+1)) && (_status==2))
            {
                //Inicialitation values encoders, spin in the same axis left.
                _left_speed = 0;
                _right_speed = 10;
                setEncoders(0,0);
                _distance = 0;
            }
            else if (_distance < desired_distance)
            {
                // Encoder control to go straight
                if(_left_encoder > _right_encoder)
                {
                    _left_speed = MAX_SPEED-10;
                    _right_speed = MAX_SPEED;
                }
                else
                {
                    _left_speed = MAX_SPEED;
                    _right_speed = MAX_SPEED-10;
                }
            }
            else
            {
                // Reset values and change of state
                _left_speed = 0;
                _right_speed = 0;
                setEncoders(0,0);
                _distance = 0;
                _status ++;
            }
        }
        setSpeed(_left_speed, _right_speed);
    }
}

//////////////////////////////////////////////

double MyRobot::convert_bearing_to_degrees(const double* in_vector)
{
    //Conversion to degrees radiones
    double rad = atan2(in_vector[0], in_vector[2]);
    double deg = rad * (180.0 / M_PI);

    return deg;
}

//////////////////////////////////////////////
