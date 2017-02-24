//
// Created by Jason Markham on 2/20/17.
//

#include "SimpleCommand.h"

bool SimpleCommand::IsFinished() {
  return IsTimedOut() || IsCanceled();
}

void SimpleCommand::Interrupted() {
  End();
}

SimpleCommand::SimpleCommand(const std::string& name) : Command(name) {}

SimpleCommand::SimpleCommand(const std::string& name, double timeout)
    : Command(name, timeout) {}
