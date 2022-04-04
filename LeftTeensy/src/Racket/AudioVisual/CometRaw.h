#ifndef COMETRAW_H
#define COMETRAW_H

#include <FastLED.h>
#pragma once
extern const int NUM_LEDS;
class CometRaw
{

public:
  CometRaw(CRGB (&ledStrip)[360]) : _leds(ledStrip)
  {
  }

  public: void loop()
  {
    if (ms > 10)
    {
      ms = 0;

    _speed = _speed + _acceleration; 
    _iPos += _iDirection * _speed;   

     if (this->hitWall())
      {
        this->setStartPosition(359.0);
        
      }else
      {
        this->move();
        this->fade();

      }

       
     
    }
  }
      


/**
 * Comet Behaviours
 * 
 */
public:
  void setStartPosition(float position ) { _iPos = position;    }
  void setSpeed(float speed)     { _speed       = speed;        }
  void setFadeSize(int fadeSize) { _fadeAmt     = fadeSize;     }
  void setSize(int size)         { _size        = size;         }
  void reverseDirection()        { _iDirection *= -1;           }
  void setMidiVelocity(int v)    { _midiVelocity = v;           }

  auto getPosition(){ return _iPos;}

/**
 * Move and accelerate the Comet
 * 
 */
private:
  void move()
  {
    for (int i = 0; i < _size; i++)
    {
      _leds[(int)_iPos + i] = CRGB(255, 255, 255); 
      usbMIDI.sendNoteOn(map(_iPos, 0, 360, 0, 127), _midiVelocity, 2);
    }
  }

/**
 * Fade the End of the Comet
 * This makes a COmet diferent from a constant line
 * 
 */
private:
  void fade()
  {
    for (int j = 0; j < _numLeds; j++)
    {
      if (random(10) > 5)
      {
        _leds[j] = _leds[j].fadeToBlackBy(_fadeAmt);
      }
      usbMIDI.sendNoteOff(map(j, 0, 360, 0, 127), 75, 2);
    }
  }

/**
 * Check if Comet Hit the end of the Boundaries'
 * ! Important _iPos does never be -1.0 or 361.0
 * 
 */
private:
  boolean hitWall()
  {
    if (int(_iPos) >= 360 || int(_iPos) <= 0)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  

private:
  CRGB (&_leds)[360];
  int      _numLeds           = 360;
  float   _startPosition       = 0.0;
  byte    _fadeAmt             = 200;
  int     _size                = 7;
  float   _speed               = 1.25;
  float   _acceleration        = 0.001;
  float   _iPos                = 0.0;
  float   _iDirection          = 1.0;
  byte    _midiVelocity        = 75;
  boolean _animationCometStart = false;

  elapsedMillis ms;

};

#endif