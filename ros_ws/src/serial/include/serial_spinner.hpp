/** \file serial_spinner.hpp
 * \brief Serial spinner class to interface with the boards
 *
 * \author Sébastien Darche <sebastien.darche@polymtl.ca>
 */

#pragma once

// Local includes

#include "protocol.hpp"

// Std includes

#include <string>

// ROS includes

#include <ros/ros.h>

#include "serial/Movement.h"
#include "serial/Target.h"

class SerialSpinner {
  public:
    /** \brief Constructor
     */
    SerialSpinner(ros::NodeHandle& nh, const std::string& device, int baud_rate,
                  int length, int stop_bits, bool parity,
                  double frequency = 500.);

    /** \brief Destructor
     */
    ~SerialSpinner();

    /** \fn callbackTarget
     * \brief Callback for new target coordinates
     */
    void callbackTarget(const serial::TargetConstPtr&);

    /** \fn callbackTarget
     * \brief Callback for new target coordinates
     */
    void callbackMovement(const serial::MovementConstPtr&);

    /** \fn spin
     * \brief Spins, waiting for requests and listens to the serial port
     */
    void spin();

  private:
    /** \fn initSerial
     * \brief Initializes the serial file descriptor. To be called by the
     * constructor
     */
    void initSerial(const std::string& device);

    /** \fn handleSerial
     * \brief Attempts to read incoming messages from the serial port and
     * dispatches them
     */
    void handleSerial();

    template <typename T> void handleMessage(const T& message);

    void sendMessage(const serial::OutgoingMessage& message);

    ros::NodeHandle& nh;
    ros::Publisher pub_hp, pub_switch;
    ros::Subscriber sub_target, sub_movement;

    int fd = -1;
    int baud_rate, length, stop_bits;
    bool parity;
    double frequency;
};
