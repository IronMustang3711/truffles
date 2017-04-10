#ifndef ReloadChoosers_H
#define ReloadChoosers_H

#include <Commands/InstantCommand.h>

class ReloadChoosers : public frc::InstantCommand {
public:
	ReloadChoosers();
	virtual	void Execute() override;

};

#endif  // ReloadChoosers_H
