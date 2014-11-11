/**
 * @file    MyRobot.h
 * @brief   A straight odometry for webots projects.
 *
 * @author  Pilar Molina Delgado <100073815@alumnos.uc3m.es>
 * @date    2014-11-11
 */

// General include files such as

#include <iostream>

// Webots include files such as

#include <webots/DifferentialWheels.hpp>

// All the webots classes are defined in the "webots" namespace
using namespace webots;
using namespace std;

// Define some macros
  #define MAX_SPEED 100


// Here is the declaration class of your controller.
// This class declares how to initialize and how to run your controller.

class MyRobot : public DifferentialWheels {
    private:

        double _left_encoder, _right_encoder;

        double _left_speed, _right_speed;

        double _distance, desired_distance;

        //  Compass* _my_compass;
        int _time_step;

    public:
        // You may need to define your private methods or variables, like
        //  Constructors, helper functions, etc.
    
        /**
         * @brief Empty constructor of the class
         */
        MyRobot();
        
        /**
         * @brief Destructor of the class.
         */
        ~MyRobot();

        /**
         * @brief User defined function for initializing and running the template class.
         */
        void run();
};
