/** \file legacy_serial_spinner.hpp
 * \brief Serial spinner class to interface with the boards
 *
 * \author Sébastien Darche <sebastien.darche@polymtl.ca>
 */

#ifndef _POLYSTAR_SERIAL_SPINNER_H
#define _POLYSTAR_SERIAL_SPINNER_H

// Std includes

#include <string>

// ROS includes

#include <ros/ros.h>

#include "serial/Rune.h"
#include "serial/Target.h"

namespace legacy {

/** \class SerialSpinner
 */
class [[deprecated]] SerialSpinner {
  public:
    /** \brief Constructor
     */
    SerialSpinner(ros::NodeHandle& nh, const std::string& device, int baud_rate,
                  int length, int stop_bits, bool parity,
                  double frequency = 100.);

    /** \brief Destructor
     */
    ~SerialSpinner();

    /** \fn callbackTarget
     * \brief Callback for new target coordinates
     */
    void callbackTarget(const serial::TargetConstPtr&);

    /** \fn callbackRune
     * \brief Callback for rune coordinates
     * \deprecated This feature is not used as of today
     */
    void callbackRune(const serial::RuneConstPtr&);

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

    ros::NodeHandle& nh;
    ros::Publisher pub_hp, pub_switch;
    ros::Subscriber sub_target, sub_rune;

    int fd = -1;
    int baud_rate, length, stop_bits;
    bool parity;
    double frequency;
};

} // namespace legacy

#endif
