/**
 * @file    straing_odometry.cpp
 * @brief   A simple example for maintaining a straight line with the compass.
 *
 * @author  Pilar Molina Delgado <100073815@alumnos.uc3m.es>
 * @date    2014-11-11
 */

#include "MyRobot.h"

/*
 * Main program.
 * The arguments of the main function can be specified by the
 * "controllerArgs" field of the Robot node
 */
int main(int argc, char **argv)
{
    MyRobot* my_robot = new MyRobot();

    my_robot->run();

    delete my_robot;

    return 0;
}
