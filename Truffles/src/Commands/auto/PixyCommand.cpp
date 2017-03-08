/*
 * PixyCommand.cpp
 *
 *  Created on: 6 Mar 2017
 *      Author: steffen
 */

#include "PixyCommand.h"

PixyCommand::PixyCommand() : Command() {
  this->widthAspect = 0.0;
  this->heightAspect = 0.0;
  this->marginAspect = 0.0;
  this->leftMargin = 0;
  this->rightMargin = 0;
  this->strafe = PixyMovement::NONE;
  this->rotate = PixyMovement::NONE;
}

void PixyCommand::Initialize() {
  SetTimeout(5);  // Time out command after 5 seconds
}

void PixyCommand::Execute() {
  uint16_t objectCount = RobotMap::pixy->getBlocks(10);
  SmartDashboard::PutNumber("Pixy: objectCount", objectCount);

  this->rotate = PixyMovement::NONE;
  this->strafe = PixyMovement::NONE;

  int firstBlockIndex = -1;
  int secondBlockIndex = -1;

  if (objectCount == 2) {
    // We assume that the two objects found are the two strips of tape
    firstBlockIndex = 0;
    secondBlockIndex = 1;
  } else if (objectCount > 2) {
    // There's some kind of interference or other objects found, so attempt to
    // find the find ones
    for (int i = 0; i < objectCount; i++) {
      double objectAspect =
          RobotMap::pixy->blocks[i].height / RobotMap::pixy->blocks[i].width;

      // Ideal aspect is 10/2.5=4, but let's be flexible to handle looking at it
      // from the side/rotated etc
      if ((objectAspect >= 2) && (objectAspect <= 4)) {
        if (firstBlockIndex == -1) {
          firstBlockIndex = i;
        } else {
          secondBlockIndex = i;
        }
      }
    }
  }

  // SmartDashboard::PutNumber("Pixy: 1st block index", firstBlockIndex);
  // SmartDashboard::PutNumber("Pixy: 2nd block index", secondBlockIndex);

  if (firstBlockIndex > -1 && secondBlockIndex > -1) {
    // We found what we think are the correct two blocks of reflective tape
    Block leftBlock;
    Block rightBlock;
    if (RobotMap::pixy->blocks[firstBlockIndex].x <
        RobotMap::pixy->blocks[secondBlockIndex].x) {
      leftBlock = RobotMap::pixy->blocks[firstBlockIndex];
      rightBlock = RobotMap::pixy->blocks[secondBlockIndex];
    } else {
      leftBlock = RobotMap::pixy->blocks[secondBlockIndex];
      rightBlock = RobotMap::pixy->blocks[firstBlockIndex];
    }

    this->widthAspect = (double)leftBlock.width / rightBlock.width;
    this->heightAspect = (double)leftBlock.height / rightBlock.height;

    // SmartDashboard::PutNumber("Pixy: widthAspect", this->widthAspect);
    SmartDashboard::PutNumber("Pixy: heightAspect", this->heightAspect);

    // Figure out if we need to turn around the z-axis
    if (this->heightAspect <= 0.97) {
      // Left block is shorter than the right
      SmartDashboard::PutString("TODO:Rotate", "Rotate Left");
      this->rotate = PixyMovement::LEFT;
    } else if (this->heightAspect >= 1.03) {
      // Right block is shorter than the left
      SmartDashboard::PutString("TODO:Rotate", "Rotate Right");
      this->rotate = PixyMovement::RIGHT;
    }

    // Figure out if we need to align
    this->leftMargin = leftBlock.x;
    this->rightMargin = PIXY_MAX_X - (rightBlock.x + rightBlock.width);

    SmartDashboard::PutNumber("Pixy: leftMargin", this->leftMargin);
    SmartDashboard::PutNumber("Pixy: rightMargin", this->rightMargin);

    this->marginAspect = (double)this->leftMargin / this->rightMargin;
    if (this->marginAspect <= 0.9) {
      SmartDashboard::PutString(
          "TODO:Strafe", "Strafe Left: " + std::to_string(this->marginAspect));
      this->strafe = PixyMovement::LEFT;
    } else if (this->marginAspect >= 1.1) {
      SmartDashboard::PutString(
          "TODO:Strafe", "Strafe Right: " + std::to_string(this->marginAspect));
      this->strafe = PixyMovement::RIGHT;
    }
  } else {
    SmartDashboard::PutString("TODO:Strafe", "");
    SmartDashboard::PutString("TODO:Rotate", "");
    // SmartDashboard::PutNumber("Pixy: widthAspect", 0);
    SmartDashboard::PutNumber("Pixy: heightAspect", 0);
    SmartDashboard::PutNumber("Pixy: leftMargin", 0);
    SmartDashboard::PutNumber("Pixy: rightMargin", 0);
  }
}

bool PixyCommand::IsFinished() {
  return true;
}

void PixyCommand::End() {
  Robot::chassis->AutoDrive(0, 0);
}

void PixyCommand::Interrupted() {
  End();
}

PixyCommand::~PixyCommand() {}
