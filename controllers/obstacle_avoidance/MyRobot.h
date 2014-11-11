/**
 * @file    main_obstacle_avoidance.cpp
 * @brief   A obtacle avoidance for webots projects.
 *
 * @author  Pilar Molina <100073815@alumnos.uc3m.es>
 * @date    2014-11-11
 */

#include <iostream>

#include <webots/DifferentialWheels.hpp>

using namespace std;
using namespace webots;

#define NUM_DISTANCE_SENSOR 16
#define DISTANCE_LIMIT      100
#define MAX_SPEED           40

class MyRobot : public DifferentialWheels {
    private:
        int _time_step;

        DistanceSensor * _distance_sensor[NUM_DISTANCE_SENSOR];
        double _left_speed, _right_speed;

        enum Mode {
            STOP,
            FORWARD,
            TURN_LEFT,
            TURN_RIGHT,
            OBSTACLE_TOTAL_FRONT,
            OBSTACLE_AVOID_L,
            OBSTACLE_AVOID_R
        };

        Mode _mode;

    public:

        /**
         * @brief Empty constructor of the class.
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
