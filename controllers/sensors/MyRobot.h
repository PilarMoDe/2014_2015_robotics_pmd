/**
 *
 * @author  Pilar molina Delgado
 * 
 */

#include <iostream>
#include <cmath>
#include <webots/DifferentialWheels.hpp>

using namespace std;
using namespace webots;

#define NUM_DISTANCE_SENSOR 6
#define MAX_SPEED       100
#define DISTANCE_LIMIT  150
#define DESIRED_ANGLE   45

class MyRobot : public DifferentialWheels {
    private:
        int _time_step;
        DistanceSensor * _distance_sensor[NUM_DISTANCE_SENSOR];
        Compass * _my_compass;
        double _left_speed, _right_speed;

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

        /**
          * @brief An example for converting bearing vector from compass to angle (in degrees).
          */
        double convert_bearing_to_degrees(const double* in_vector);
};
