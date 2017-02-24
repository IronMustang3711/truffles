//
// Created by Jason Markham on 2/21/17.
//

#ifndef TRUFFLES_HEXAPUS_H
#define TRUFFLES_HEXAPUS_H

#include <SpeedController.h>
#include "Commands/Subsystem.h"

class Hexapus : public Subsystem {
 public:
  Hexapus();

  /**
 * @param speed in [0,1]
 */
  void run(double speed);

  void run();
  void stop();
  void unjam();

  double getMotorCurrent();
  bool isJammed();

  std::shared_ptr<SpeedController> hexapusController;
};

#endif  // TRUFFLES_HEXAPUS_H
