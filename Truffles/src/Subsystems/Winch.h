
#ifndef WINCH_H
#define WINCH_H

#include "Commands/Subsystem.h"
#include <SpeedController.h>

/**
 *
 *
 * @author ExampleAuthor
 */
class Winch : public Subsystem {
 private:
  std::shared_ptr<SpeedController> winchMotor;

 public:
  Winch();
  void InitDefaultCommand();

  void runWinchMotor(double speed);
};

#endif
