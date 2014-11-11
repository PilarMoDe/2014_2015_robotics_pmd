/**
 * @file    MyRobot.cpp
 * @brief   A straight for webots projects.
 *
 * @author  Pilar Molina Delgado <100073815@alumnos.uc3m.es>
 * @date    2014-11-11
 */

#include "MyRobot.h"

//////////////////////////////////////////////

MyRobot::MyRobot() : DifferentialWheels()
{
    _time_step = 64;
    //The world between the two yellow lines are 16m but the robot starts one meter before the yellow line
    desired_distance=17;
    // Enable encoders
    enableEncoders(_time_step);

    _left_speed = MAX_SPEED;
    _right_speed = MAX_SPEED;
    _distance = 0;
}

//////////////////////////////////////////////

MyRobot::~MyRobot()
{
    disableEncoders();
}

//////////////////////////////////////////////

void MyRobot::run()
{
    while (step(_time_step) != -1)
    {

        _left_encoder = getLeftEncoder();
        _right_encoder = getRightEncoder();
        /// Distance measured from the encoders,1m 60.61 is that one encoder per revolution is 31416 and 0.5183 meters per lap or 6.28 rad if speed is 10rad / sec
        _distance = _left_encoder/60.61;
        // If the distance is less than the total distance you want is 17m
        if (_distance < desired_distance)
        {
            if(_left_encoder > _right_encoder)
            {
                _left_speed = (MAX_SPEED-10);
                _right_speed = MAX_SPEED;
            }
            else
            {
                _left_speed = MAX_SPEED;
                _right_speed = (MAX_SPEED-10);
            }
        }
        else
        {
            _left_speed = 0;
            _right_speed = 0;
        }
        setSpeed(_left_speed, _right_speed);
    }
}

//////////////////////////////////////////////
