#ifndef Sensors_h
#define Sensors_h

class Sensors
{
  public:
  void SetPins(int,int); 
  void init(void);
  bool getStatus(int);
  static int _pir;
  static int _ldr;
  
  private:

};

#endif
