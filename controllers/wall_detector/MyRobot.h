/**
 * @file    MyRobot.h
 * @brief   A wall detector for webots projects.
 *
 * @author  Pilar Molina Delgado <100073815@alumnos.uc3m.es>
 * @date    2014-11-13
 */

#include <iostream>

#include <webots/DifferentialWheels.hpp>

using namespace std;
using namespace webots;

// Define constant values
#define DISTANCE_LIMIT      100
#define MAX_SPEED           60

class MyRobot : public DifferentialWheels {
private:
    int _time_step;
    //statement of forward camara
    Camera * _forward_camera;
    //Starring robot modes
    enum Mode {

        FORWARD,
        OBSTACLE_AVOID1


    };

    Mode _mode;
    //Values of wheel speeds
    double _left_speed, _right_speed;

public:
    // You may need to define your private methods or variables, like

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
