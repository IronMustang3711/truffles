/*
 * Pixy.cpp
 *
 * Author: Steffen Furholm, based on non-working code from https://github.com/Robodox-599
 */
#include "Pixy.h"

/**
 * Gets an int (two bytes) from Pixy
 */
uint16_t Pixy::getWord() {
	unsigned char buffer[2] = { 0, 0 };

	i2c->ReadOnly(2, buffer);
	return (buffer[1] << 8) | buffer[0];
}

/**
 * Gets a single byte from Pixy
 */
uint8_t Pixy::getByte() {
	unsigned char buffer[1] = { 0 };

	i2c->ReadOnly(1, buffer);
	return buffer[0];
}

/**
 * Checks whether it is the start of the normal frame, CC frame, or the data is out of sync
 */
bool Pixy::getStart() {
	uint16_t w, lastw;

	lastw = 0xffff;

	while (true) {
		w = getWord();
		if (w == 0 && lastw == 0) {
			//delayMicroseconds(10);
			return false;
		} else if (w == PIXY_START_WORD && lastw == PIXY_START_WORD) {
			blockType = NORMAL_BLOCK;
			return true;
		} else if (w == PIXY_START_WORD_CC && lastw == PIXY_START_WORD) {
			blockType = CC_BLOCK;
			return true;
		} else if (w == PIXY_START_WORDX) {
			// When byte received was 0x55aa instead of other way around, the code syncs the byte
			printf("Pixy: reorder");
			getByte(); // Resync
		}
		lastw = w;
	}
}

uint16_t Pixy::getBlocks(uint16_t maxBlocks) {
	blocks[0] = {0}; // Resets the array - clears out data from previous reading
	uint8_t i;
	uint16_t w, checksum, sum;
	Block *block;

	if (!skipStart) {
		// We'll read/block until we see the Pixy starting frame identifier (0xaa55)
		if (getStart() == false) {
			return 0;
		}
	} else {
		skipStart = false;
	}

	for (blockCount=0; blockCount < maxBlocks && blockCount < PIXY_MAXIMUM_ARRAYSIZE;) {
		checksum = getWord();
		if (checksum == PIXY_START_WORD) {
			// We've reached the beginning of the next frame
			skipStart = true;
			blockType = NORMAL_BLOCK;
			return blockCount;
		} else {
			if (checksum == PIXY_START_WORD_CC) {
				// We've reached the beginning of the next frame
				skipStart = true;
				blockType = CC_BLOCK;
				return blockCount;
			} else {
				if (checksum==0) {
					return blockCount;
				}
			}
		}

		block = blocks + blockCount;

		for (i=0, sum=0; i < sizeof(Block)/sizeof(uint16_t); i++) {
			if (blockType == NORMAL_BLOCK && i >= 5) {
				// If it's not a color-code block, there's no need to consider angle, so skip it
				block->angle = 0;
				break;
			}
			w = getWord();
			sum += w;
			*((uint16_t *)block + i) = w;  // Converts block to integer value
		}
		if (checksum == sum) {
			blockCount++;
		} else {
			printf("Pixy: cs error");
		}

		w = getWord();
		if (w == PIXY_START_WORD) {
			blockType = NORMAL_BLOCK;
		} else {
			if (w==PIXY_START_WORD_CC) {
				blockType = CC_BLOCK;
			} else {
				return blockCount;
			}
		}
	}

	return blockCount;
}

Pixy::Pixy(I2C::Port port, int i2cAddress) {
	i2c = new I2C(port, i2cAddress); // I2C::Port::kOnboard or kMXP, Pixy Address

	blockType = BlockType::NORMAL_BLOCK;
	skipStart = false; // Make sure we start by looking for a new frame
	blockCount = 0;
}

Pixy::~Pixy() {
	delete i2c;

	i2c = nullptr;
}
