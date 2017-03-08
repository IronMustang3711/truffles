/*
 * PixyRotate.h
 *
 *  Created on: 6 Mar 2017
 *      Author: steffen
 */

#ifndef SRC_COMMANDS_AUTO_PIXYROTATE_H_
#define SRC_COMMANDS_AUTO_PIXYROTATE_H_

#include "PixyCommand.h"

class PixyRotate : public PixyCommand {
 public:
  PixyRotate();
  virtual ~PixyRotate();

  virtual void Initialize();
  virtual void Execute();
  virtual bool IsFinished();
};

#endif /* SRC_COMMANDS_AUTO_PIXYROTATE_H_ */
