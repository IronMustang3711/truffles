/*
 * Pixy.h
 *
 * Author: Steffen Furholm, based on non-working code from
 * https://github.com/Robodox-599
 */

#ifndef SRC_PIXY_H_
#define SRC_PIXY_H_

#include "WPILib.h"

/**
 * Pixy data format:
 *
 * Bytes    16-bit word    Description
 * ----------------------------------------------------------------
 * 0, 1     y              sync: 0xaa55=normal object, 0xaa56=color code object
 * 2, 3     y              checksum (sum of all 16-bit words 2-6, that is, bytes
 * 4-13)
 * 4, 5     y              signature number
 * 6, 7     y              x center of object
 * 8, 9     y              y center of object
 * 10, 11   y              width of object
 * 12, 13   y              height of object
 */

#define PIXY_MAXIMUM_ARRAYSIZE 10
#define PIXY_START_WORD 0xaa55  // For regular color recognition
#define PIXY_START_WORD_CC \
  0xaa56                         // For color code - angle rotation recognition
#define PIXY_START_WORDX 0x55aa  // Regular color another way around
#define PIXY_MAX_SIGNATURE 7
#define PIXY_DEFAULT_ARGVAL 0xffff

// Pixy x/y position values
#define PIXY_MIN_X 0L
#define PIXY_MAX_X 319L
#define PIXY_MIN_Y 0L
#define PIXY_MAX_Y 199L

enum BlockType {
  NORMAL_BLOCK,  // Normal color recognition
  CC_BLOCK       // Color-code recognition (change in angle)
};

struct Block {
  void print() {
    int i, j;
    char sig[6], d;
    bool flag;
    if (signature > PIXY_MAX_SIGNATURE) {  // Color-code! (CC)
      // Convert signature number to an octal string
      for (i = 12, j = 0, flag = false; i >= 0;
           i -=
           3) {  // Assigns value to signature, x, y, width, height, and angle
        d = (signature >> i) & 0x07;
        if (d > 0 && !flag) {
          flag = true;
        }
        if (flag) {
          sig[j++] = d + '0';
        }
      }
      sig[j] = '\0';
      printf(
          "CC block! sig: %s (%d decimal) x: %d y: %d width: %d height: %d "
          "angle %d\n",
          sig, signature, x, y, width, height, angle);
    } else {
      // Regular block. Note, angle is always zero.
      printf("sig: %d x: %d y: %d width: %d height: %d\n", signature, x, y,
             width, height);
    }
  }
  uint16_t signature;  // Identification number for your object - set it in the
                       // PixyMon
  uint16_t x;          // 0-320
  uint16_t y;          // 0-200
  uint16_t width;
  uint16_t height;
  uint16_t angle;  // Only applicable to color-code recognition
};

class Pixy {
 private:
  I2C* i2c;
  BlockType blockType;
  bool skipStart;  // Skips to check for 0xaa55, which is the identifier that
                   // tells that Pixy is at the start of new frame
  uint16_t blockCount;  // The number of matched signature objects

  uint16_t getWord();
  uint8_t getByte();
  bool getStart();

 public:
  Pixy(I2C::Port port, int i2cAddress);
  ~Pixy();
  /**
   *
   * @param maxBlocks the maximum number of blocks we are interested in, up to PIXY_MAXIMUM_ARRAYSIZE
   * @return the number of blocks available
   */
  uint16_t getBlocks(uint16_t maxBlocks);
  uint16_t getBlocks();
  Block blocks[PIXY_MAXIMUM_ARRAYSIZE];  // Array that stores the matched
                                         // signature objects
};

#endif /* SRC_PIXY_H_ */
