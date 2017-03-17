#ifndef JogBackSimple_H
#define JogBackSimple_H

#include "WPILib.h"

class JogBackSimple : public Command {
public:
	JogBackSimple();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;

};

#endif  // JogBackSimple_H
