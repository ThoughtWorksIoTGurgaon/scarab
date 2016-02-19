#ifndef CHARACTERISTIC_H
#define CHARACTERISTIC_H

#define ON 0x01
#define OFF 0x02

class Characteristic {
  protected:
    int portNumber;
    char *status;
  public:
    Characteristic(int portNumber);
    virtual void write(int, char *, int (* digitalWriteCallback)(int, int))=0 ;
};

#endif
