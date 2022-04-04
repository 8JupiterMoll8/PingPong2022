#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include"Racket.hpp"
#include "Table.h"


#pragma once
// The Gamem
class GameManager
{
protected:

Racket &_leftRacket;
Racket &_rightRacket;
Table  &_leftTable;
Table  &_rightTable;

int _totalBallWechselCounter = 0;

protected:
virtual void lr_hitAufschlag() = 0;
virtual void lt_hitAufschalg() = 0;
virtual void rr_hitAufschlag() = 0;
virtual void rt_hitAufschlag() = 0;

virtual void lr_hitBallwechsel() = 0;
virtual void lt_hitBallwechsel() = 0;
virtual void rr_hitBallwechsel() = 0;
virtual void rt_hitBallwechsel() = 0;

virtual void error()          = 0;
virtual void ok_Ballwachsel() = 0;


    /*
    ███████╗████████╗ █████╗ ████████╗███████╗███████╗
    ██╔════╝╚══██╔══╝██╔══██╗╚══██╔══╝██╔════╝██╔════╝
    ███████╗   ██║   ███████║   ██║   █████╗  ███████╗
    ╚════██║   ██║   ██╔══██║   ██║   ██╔══╝  ╚════██║
    ███████║   ██║   ██║  ██║   ██║   ███████╗███████║
    ╚══════╝   ╚═╝   ╚═╝  ╚═╝   ╚═╝   ╚══════╝╚══════╝

    */
    enum States
    {
        START,
        lr_AS,
        lt_AS,
        rt_AS,
        rr_AS, // Aufschlag von Links
        lt_BW,
        lr_BW,
        rt_BW,
        rr_BW,    // Ballwechsel
        count_BW, // Counter
        FINISH_GAME
    };

    States state = START;


public:
    GameManager(Racket &leftRacket, Racket &rightRacket, Table &leftTable, Table&rightTable):
    _leftRacket(leftRacket),
    _rightRacket(rightRacket),
    _leftTable(leftTable),
    _rightTable(rightTable)
    {}

  

    void loop()
    {
  
     

    switch (state)
        {
        /*
      ███████╗████████╗ █████╗ ██████╗ ████████╗
      ██╔════╝╚══██╔══╝██╔══██╗██╔══██╗╚══██╔══╝
      ███████╗   ██║   ███████║██████╔╝   ██║
      ╚════██║   ██║   ██╔══██║██╔══██╗   ██║
      ███████║   ██║   ██║  ██║██║  ██║   ██║
      ╚══════╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝

      */
        case START:

            Serial.println("STARTE SPIEL");
            Serial.println("State 1.) AUFSCHLAG : Warte dass, der Ball trifft LEFT RACKET trifft");

            // printGameStatus();
            resetAllCounters();

            // Leave State:
            state = lr_AS;

            // Leave State:
            break;


/*            
██╗     ███████╗███████╗████████╗     █████╗ ██╗   ██╗███████╗ ██████╗██╗  ██╗██╗      █████╗  ██████╗ 
██║     ██╔════╝██╔════╝╚══██╔══╝    ██╔══██╗██║   ██║██╔════╝██╔════╝██║  ██║██║     ██╔══██╗██╔════╝ 
██║     █████╗  █████╗     ██║       ███████║██║   ██║███████╗██║     ███████║██║     ███████║██║  ███╗
██║     ██╔══╝  ██╔══╝     ██║       ██╔══██║██║   ██║╚════██║██║     ██╔══██║██║     ██╔══██║██║   ██║
███████╗███████╗██║        ██║       ██║  ██║╚██████╔╝███████║╚██████╗██║  ██║███████╗██║  ██║╚██████╔╝
╚══════╝╚══════╝╚═╝        ╚═╝       ╚═╝  ╚═╝ ╚═════╝ ╚══════╝ ╚═════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝ ╚═════╝ 
 */
        // States: Hit Left Racket >> Hit Left Table >> Hit Right Table >> Hit Right Racket
        // >> Succseful Aufschlag
        case lr_AS:
            // Do
            // Leave State:
            if (_leftRacket.hitSum() == 1){
                Serial.println("AUFSCHLAG : BAll trifft Left Racket");
                Serial.println("State 2.)AUFSCHLAG : Warte das BAll trifft LEFT TABLE");
                
                lr_hitAufschlag();
                resetAllCounters();
                state = lt_AS;
                // printGameStatus();
            }
            break;

        case lt_AS:
            //Leave State Error Check:
            if (_leftRacket.hitSum() == 1 || _rightRacket.hitSum() == 1 || _rightTable.hitSum() == 1  ){
                    Serial.println("!!!!!!!!!!!!!!!!ERROR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
                    error();
                    state = START;
                    resetAllCounters();
                }
            //Leave State:
            if (_leftTable.hitSum() == 1){
                Serial.println("AUFSCHLAG : BAll trifft Left Table");
                Serial.println("State 3.) AUFSCHLAG : Warte das BAll trifft RIGHT TABLE");

                lt_hitAufschalg();
                // printGameStatus();
                resetAllCounters();
                state = rt_AS;
            }
            break;

        case rt_AS:
            //Leave State Error Check:
            if ( _leftRacket.hitSum() == 1 || _rightRacket.hitSum() == 1 || _leftTable.hitSum() == 1  )
                {
                    Serial.println("!!!!!!!!!!!!!!!!ERROR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
                    error();
                    state = START;
                    resetAllCounters();
                }
            //Leave State:
            if (_rightTable.hitSum() == 1)
            {
                
                Serial.println("AUFSCHLAG : BAll trifft Right Table");
                Serial.println("AUFSCHLAG : Warte das BAll trifft RIGHT RACKET");
                
                rt_hitAufschlag();
                 
                // printGameStatus();
                resetAllCounters();
                state = rr_AS;
            }
            break;

        case rr_AS:
            //Leave State Error Check:
            if (_leftRacket.hitSum() == 1 || _rightTable.hitSum() == 1 || _leftTable.hitSum() == 1)
            {
                Serial.println("!!!!!!!!!!!!!!!!ERROR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
                error();
                state = START;
                resetAllCounters();
            }
            //Leave State:     
            if ( _rightRacket.hitSum() == 1 )
            {
                rr_hitAufschlag();
                 
             
                Serial.println("AUFSCHLAG : BAll trifft Right Racket");
                Serial.println("AUFSCHLAG Erfolgreich");
                Serial.println("Starte Ballwechsel");
                Serial.println("BAllWechsel : Warte das BAll trifft LEFT TABLE");

                // printGameStatus();
                resetAllCounters();
                state = lt_BW;
            }
            break;

        /*
      ██████╗  █████╗ ██╗     ██╗     ██╗    ██╗███████╗ ██████╗██╗  ██╗███████╗███████╗██╗
      ██╔══██╗██╔══██╗██║     ██║     ██║    ██║██╔════╝██╔════╝██║  ██║██╔════╝██╔════╝██║
      ██████╔╝███████║██║     ██║     ██║ █╗ ██║█████╗  ██║     ███████║███████╗█████╗  ██║
      ██╔══██╗██╔══██║██║     ██║     ██║███╗██║██╔══╝  ██║     ██╔══██║╚════██║██╔══╝  ██║
      ██████╔╝██║  ██║███████╗███████╗╚███╔███╔╝███████╗╚██████╗██║  ██║███████║███████╗███████╗
      ╚═════╝ ╚═╝  ╚═╝╚══════╝╚══════╝ ╚══╝╚══╝ ╚══════╝ ╚═════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝
      */
        case lt_BW:
            //Leave State Error Check:
            if (_leftRacket.hitSum() == 1 || _rightRacket.hitSum() == 1 ||_rightTable.hitSum() == 1  )
                {
                    Serial.println("!!!!!!!!!!!!!!!!ERROR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
                    error();
                    state = START;
                    resetAllCounters();
                }
            //Leave State:
            if (_leftTable.hitSum() == 1) // Hit Left Table
            {
                lt_hitBallwechsel();

                Serial.println("Ballwechsel : Warte das BAll trifft LEFT RACKET");

                resetAllCounters();
                state = lr_BW;
            }
            break;

        case lr_BW:
            //Leave State Error Check:
            if (_leftTable.hitSum() == 1 || _rightRacket.hitSum() == 1 ||_leftTable.hitSum() == 1  )
                {
                    Serial.println("!!!!!!!!!!!!!!!!ERROR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
                    error();
                    state = START;
                    resetAllCounters();
                }
            // Leave State:
            if (_leftRacket.hitSum() == 1) // Hit Left RACket
            {
                lr_hitBallwechsel();
                Serial.println("Ballwechsel : Warte das BAll trifft RIGHT TABLE");

                resetAllCounters();
                state = rt_BW;
            }
            break;

        case rt_BW:
            //Leave State Error Check:
            if (_leftRacket.hitSum() == 1 || _rightRacket.hitSum() == 1 ||_leftTable.hitSum() == 1  )
                {
                    Serial.println("!!!!!!!!!!!!!!!!ERROR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
                    error();
                    state = START;
                    resetAllCounters();
                }
            // Leave State:
            if (_rightTable.hitSum() == 1) // Hit Right Table
            {
                rt_hitBallwechsel();
                Serial.println("Ballwechsel : Warte das BAll trifft RIGHT RACKET");

                resetAllCounters();
                state = rr_BW;
            }
            break;

        case rr_BW:
            //Leave State Error Check:
            if (_leftRacket.hitSum() == 1 || _rightTable.hitSum() == 1 ||_leftTable.hitSum() == 1  )
                {
                    Serial.println("!!!!!!!!!!!!!!!!ERROR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
                    error();
                    state = START;
                    resetAllCounters();
                }
            //  Leave State:
            if (_rightRacket.hitSum() == 1) // Hit Right Racket
            {
               rr_hitBallwechsel();
                Serial.println("Ballwechsel : Erfolgreich");

                resetAllCounters();
                state = count_BW;
            }
            break;

        case count_BW:
            // Do

            Serial.print("TOTAL- Ballwechsel : ");
            Serial.println(++_totalBallWechselCounter);
            Serial.println("BAllWechsel : Warte das BAll trifft LEFT TABLE");
            ok_Ballwachsel();
          
            // Leave State:
            state = lt_BW;
            break;

        default:
            break;
        } // end switch
    }

private:

    /*
    ██████╗ ███████╗███████╗███████╗████████╗
    ██╔══██╗██╔════╝██╔════╝██╔════╝╚══██╔══╝
    ██████╔╝█████╗  ███████╗█████╗     ██║
    ██╔══██╗██╔══╝  ╚════██║██╔══╝     ██║
    ██║  ██║███████╗███████║███████╗   ██║
    ╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝   ╚═╝

    */
    // Reset all Counters to Zero(0)
    void resetAllCounters()
    {
        _leftRacket.resetHitSum();
        _rightRacket.resetHitSum();
        _leftTable.resetHitSum();
        _rightTable.resetHitSum();
    }

    void printGameStatus()
    {
        Serial.print(_leftRacket.hitSum());
        Serial.print(_leftTable.hitSum());
        Serial.print(_rightRacket.hitSum());
        Serial.print(_rightTable.hitSum());
        Serial.println("");
    }
};

#endif