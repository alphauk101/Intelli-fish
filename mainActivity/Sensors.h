#ifndef Sensors_h
#define Sensors_h

class Sensors
{
  public:
  void SetPins(int,int); 
  void init(void);
  bool getStatus(int);
  int LDR;
  int PIR;
  int getLDRValue(void);
  private:
  int _getLDRValue();
};

#endif

