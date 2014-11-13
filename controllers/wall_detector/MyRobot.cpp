/**
 * @file    MyRobot.cpp
 * @brief   A wall detector for webots projects.
 *
 * @author  Pilar Molina Delgado <100073815@alumnos.uc3m.es>
 * @date    2014-11-13
 */

#include "MyRobot.h"

//////////////////////////////////////////////

MyRobot::MyRobot() : DifferentialWheels()
{
    _time_step = 64;

    _mode = FORWARD;
    //Enable forward camara
    _forward_camera = getCamera("camera_f");
    _forward_camera->enable(_time_step);

}

//////////////////////////////////////////////

MyRobot::~MyRobot()
{   //Disable camara
    _forward_camera->disable();

}

//////////////////////////////////////////////

void MyRobot::run()
{
    //initialitation counter pixel
    int sum = 0;
    //initialitation values RGB
    unsigned char green = 0, red = 0, blue = 0;
    //initialitation porcentage white
    double percentage_white = 0.0;

    // Get size of images for forward camera
    int image_width_f = _forward_camera->getWidth();
    int image_height_f = _forward_camera->getHeight();
    cout << "Size of forward camera image: " << image_width_f << ", " <<  image_height_f << endl;



    while (step(_time_step) != -1) {
        sum = 0;

        // Get current image from forward camera
        const unsigned char *image_f = _forward_camera->getImage();

        // Count number of pixels that are white
        // (here assumed to have pixel value > 245 out of 255 for all color components)
        for (int x = 0; x < image_width_f; x++) {
            for (int y = 0; y < image_height_f; y++) {
                green = _forward_camera->imageGetGreen(image_f, image_width_f, x, y);
                red = _forward_camera->imageGetRed(image_f, image_width_f, x, y);
                blue = _forward_camera->imageGetBlue(image_f, image_width_f, x, y);

                if ((green > 195) && (red > 195) && (blue > 195)) {
                    sum = sum + 1;
                }

            }
        }

        percentage_white = (sum / (float) (image_width_f * image_height_f)) * 100;
        cout << "Percentage of white in forward camera image: " << percentage_white << endl;



        // Control logic of the robot (FRONTAL ZONE)

        if ((percentage_white >=80)) {
            _mode = OBSTACLE_AVOID1;
            cout << "NEAREST WALL." << endl;
        }
        else {
            _mode = FORWARD;
            cout << "MOVING FORWARD." << endl;
        }



        // Send actuators commands according to the mode
        switch (_mode){

            case FORWARD:
                _left_speed = MAX_SPEED;
                _right_speed = MAX_SPEED;
                break;
            case OBSTACLE_AVOID1:       //  MOVING BACK FACING LEFT
                _left_speed = -MAX_SPEED / 3.0;
                _right_speed = -MAX_SPEED / 20.0;
                break;

            default:
                break;
        }



        // Set the motor speeds
        setSpeed(_left_speed, _right_speed);
    }
}

//////////////////////////////////////////////
