/**
 * @file    MyRobot.cpp
 * @brief   A MyRobot for webots projects.
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

    //Enable spherical camara
    _spherical_camera = getCamera("camera_s");
    _spherical_camera->enable(_time_step);
}

//////////////////////////////////////////////

MyRobot::~MyRobot()
{
    //Disable camara
    _spherical_camera->disable();
}

//////////////////////////////////////////////

void MyRobot::run()
{
    //initialitation counter pixel
    int sum = 0;
    //initialitation values RGB
    unsigned char green = 0, red = 0, blue = 0;
    //initialitation porcentage yellow
    double percentage_yellow = 0.0;


    // Get size of images for spherical camera
    int image_width_s = _spherical_camera->getWidth();
    int image_height_s = _spherical_camera->getHeight();


    while (step(_time_step) != -1) {
        sum = 0;

        // Get current image from forward camera
        const unsigned char *image_s = _spherical_camera->getImage();

        // Count number of pixels that are yellow

        for (int x = 0; x < image_width_s; x++) {
            for (int y = 0; y < image_height_s; y++) {
                //Values RGB
                green = _forward_camera->imageGetGreen(image_s, image_width_s, x, y);
                red = _forward_camera->imageGetRed(image_s, image_width_s, x, y);
                blue = _forward_camera->imageGetBlue(image_s, image_width_s, x, y);
                /// To detect the yellow RGB values ​​of red and green should be the maximums ( 255) and the blue value 0, but as the world has shadows down a bit values
                if ((green > 200) && (red > 200) && (blue < 10)) {
                    sum = sum + 1; // Cont pixel
                }

            }
        }
        //We calculate the percentage of yellow and printed on screen.
        //We use the number of pixels that we have displayed in the camera thanks to variable height and width
        percentage_yellow = (sum / (float) (image_width_s * image_height_s)) * 100;
        cout << "Percentage of yellow in forward camera image: " << percentage_yellow << endl;



        // Control logic of the robot (spherical camera)

        if ((percentage_yellow >=0.3)) {
            _mode = LINE;
            cout << "LINE YELLOW." << endl;
        }

        else {
            _mode = FORWARD;
            cout << "MOVING FORWARD." << endl;
        }



        // Send actuators commands according to the mode
        switch (_mode){

        case FORWARD:    //Moving in circles
            _left_speed = -MAX_SPEED/3.0;
            _right_speed = MAX_SPEED/3.0;
            break;
        case LINE:       //Moving in circles faster
            _left_speed = -MAX_SPEED ;
            _right_speed = MAX_SPEED ;
            break;

        default:
            break;
        }



        // Set the motor speeds
        setSpeed(_left_speed, _right_speed);
    }
}

//////////////////////////////////////////////
