#ifndef Accessory_h
#define Accessory_h

#include "Arduino.h"

#define I2C_ADDR		0x52
#define I2C_ADDR_R		((I2C_ADDR << 1) + 1)
#define I2C_ADDR_W		(I2C_ADDR << 1)

//#define THIRDPARTYWII 0
//#define OFFICIALWII 1
//#define WIICLASSIC 2
typedef enum _controllertype {NUNCHUCK,WIICLASSIC,GuitarHeroController,GuitarHeroWorldTourDrums,DrumController,DrawsomeTablet,Mystery} ControllerType;


class Accessory {
  public:
    Accessory(uint8_t bytes[6]);
    Accessory();
    
    uint8_t* getDataArray();
    void setDataArray(uint8_t data[6]);
  
    void printInputs(Stream& stream);
    
    int   decodeInt(uint8_t msbbyte,uint8_t msbstart,uint8_t msbend,
                           uint8_t csbbyte, uint8_t csbstart, uint8_t csbend,
                           uint8_t lsbbyte, uint8_t lsbstart, uint8_t lsbend);
    bool  decodeBit(uint8_t byte, uint8_t bit, bool activeLow); 
	  void begin();
	  void readData();
	  void initBytes();

	  boolean usePullUpClock;
	  ControllerType identifyController();
  private:
    uint8_t _dataarray[8];
	  uint8_t _scl_PIN;
	  uint8_t _sda_pin;
	  boolean _use_hw;
	  uint32_t _callCount;
	  uint32_t _clockSpacing;
	  uint32_t _timeoutCount;
	  int numMaps;
	
    unsigned long ackTimeout;
	  void _clockHigh();
	  void _clockLow();
	  void _dataHigh();
	  void _dataLow();
	  void _sendStart(byte addr);
	  void _sendStop();
	  void _sendAck();
	  void _sendNack();
	  void _waitForAck();
	  void _clockStallCheck();
	  uint8_t _readByte();
	  void _writeByte(uint8_t value);
	  void _burstRead();
	  void _burstReadWithAddress(uint8_t addr);

	  void _writeRegister(uint8_t reg, uint8_t value);
	  void _shiftOut(uint8_t val);



};

typedef enum _inType {ANALOG,DIGITAL} inType;

typedef struct _inputMapping {
  inType  type;
  
  // digital in params
  uint8_t dByte;
  uint8_t dBit;
  bool    dActiveLow;
  
  // analog in params
  uint8_t aMsbbyte;
  uint8_t aMsbstart;
  uint8_t aMsbend;
  
  uint8_t aCsbbyte;
  uint8_t aCsbstart;
  uint8_t aCsbend;
  
  uint8_t aLsbbyte;
  uint8_t aLsbstart;
  uint8_t aLsbend;
  
  // Analog Scaling info
  uint8_t aMax;
  uint8_t aZero;
  uint8_t aMin;
  
  // Servo Scaling Info
  uint8_t sevoMax;
  uint8_t servoZero;
  uint8_t servoMin;
  
  Servo   servo;
  
  input nextMap;
} input

#endif