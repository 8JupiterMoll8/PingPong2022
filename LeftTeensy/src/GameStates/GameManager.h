#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include"Racket.hpp"
#include "Table.h"


#pragma once
// The Gamem
class GameManager
{
protected:

Racket  &m_leftRacket;
Racket &m_rightRacket;
Table       &m_leftTable;
Table       &m_rightTable;
int         m_totalBallWechselCounter = 0;

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
    m_leftRacket(leftRacket),
    m_rightRacket(rightRacket),
    m_leftTable(leftTable),
    m_rightTable(rightTable)
    {
    }

  

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
            Serial.println("State 1.) AUFSCHLAG : Warte dass, der Ball trift LEFT RACKET trift");

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
            if (m_leftRacket.hitSum() == 1)
            {
                Serial.println("AUFSCHLAG : BAll trift Left Racket");
                Serial.println("State 2.)AUFSCHLAG : Warte das BAll trift LEFT TABLE");
                
                lr_hitAufschlag();
                resetAllCounters();
                state = lt_AS;
                // printGameStatus();
            }
            break;

        case lt_AS:
            //Leave State Error Check:
            if (m_leftRacket.hitSum() == 1 || m_rightRacket.hitSum() == 1 ||m_rightTable.hitSum() == 1  )
                {
                    Serial.println("!!!!!!!!!!!!!!!!ERROR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
                    error();
                    state = START;
                    resetAllCounters();
                }
            //Leave State:
            if (m_leftTable.hitSum() == 1)
            {
                Serial.println("AUFSCHLAG : BAll trift Left Table");
                Serial.println("State 3.) AUFSCHLAG : Warte das BAll trift RIGHT TABLE");

                lt_hitAufschalg();
                // printGameStatus();

                resetAllCounters();
                state = rt_AS;
            }
            break;

        case rt_AS:
            //Leave State Error Check:
            if (m_leftRacket.hitSum() == 1 || m_rightRacket.hitSum() == 1 ||m_leftTable.hitSum() == 1  )
                {
                    Serial.println("!!!!!!!!!!!!!!!!ERROR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
                    error();
                    state = START;
                    resetAllCounters();
                }
            //Leave State:
            if (m_rightTable.hitSum() == 1)
            {
                
                Serial.println("AUFSCHLAG : BAll trift Right Table");
                Serial.println("AUFSCHLAG : Warte das BAll trift RIGHT RACKET");
                
                rt_hitAufschlag();
                 
                // printGameStatus();
                resetAllCounters();
                state = rr_AS;
            }
            break;

        case rr_AS:
            //Leave State Error Check:
            if (m_leftRacket.hitSum() == 1 || m_rightTable.hitSum() == 1 ||m_leftTable.hitSum() == 1  )
                {
                    Serial.println("!!!!!!!!!!!!!!!!ERROR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
                    error();
                    state = START;
                    resetAllCounters();
                }
            //Leave State:     
            if (m_rightRacket.hitSum() == 1)
            {
                rr_hitAufschlag();
                 
             
                Serial.println("AUFSCHLAG : BAll trift Right Racket");
                Serial.println("AUFSCHLAG Erfolgreich");
                Serial.println("Starte Ballwechsel");
                Serial.println("BAllWechsel : Warte das BAll trift LEFT TABLE");

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
            if (m_leftRacket.hitSum() == 1 || m_rightRacket.hitSum() == 1 ||m_rightTable.hitSum() == 1  )
                {
                    Serial.println("!!!!!!!!!!!!!!!!ERROR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
                    error();
                    state = START;
                    resetAllCounters();
                }
            //Leave State:
            if (m_leftTable.hitSum() == 1) // Hit Left Table
            {
                lt_hitBallwechsel();

                Serial.println("Ballwechsel : Warte das BAll trift LEFT RACKET");

                resetAllCounters();
                state = lr_BW;
            }
            break;

        case lr_BW:
            //Leave State Error Check:
            if (m_leftTable.hitSum() == 1 || m_rightRacket.hitSum() == 1 ||m_leftTable.hitSum() == 1  )
                {
                    Serial.println("!!!!!!!!!!!!!!!!ERROR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
                    error();
                    state = START;
                    resetAllCounters();
                }
            // Leave State:
            if (m_leftRacket.hitSum() == 1) // Hit Left RACket
            {
                lr_hitBallwechsel();
                Serial.println("Ballwechsel : Warte das BAll trift RIGHT TABLE");

                resetAllCounters();
                state = rt_BW;
            }
            break;

        case rt_BW:
            //Leave State Error Check:
            if (m_leftRacket.hitSum() == 1 || m_rightRacket.hitSum() == 1 ||m_leftTable.hitSum() == 1  )
                {
                    Serial.println("!!!!!!!!!!!!!!!!ERROR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
                    error();
                    state = START;
                    resetAllCounters();
                }
            // Leave State:
            if (m_rightTable.hitSum() == 1) // Hit Right Table
            {
                rt_hitBallwechsel();
                Serial.println("Ballwechsel : Warte das BAll trift RIGHT RACKET");

                resetAllCounters();
                state = rr_BW;
            }
            break;

        case rr_BW:
            //Leave State Error Check:
            if (m_leftRacket.hitSum() == 1 || m_rightTable.hitSum() == 1 ||m_leftTable.hitSum() == 1  )
                {
                    Serial.println("!!!!!!!!!!!!!!!!ERROR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
                    error();
                    state = START;
                    resetAllCounters();
                }
            //  Leave State:
            if (m_rightRacket.hitSum() == 1) // Hit Right Racket
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
            Serial.println(++m_totalBallWechselCounter);
            Serial.println("BAllWechsel : Warte das BAll trift LEFT TABLE");
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
        m_leftRacket.resetHitSum();
        m_rightRacket.resetHitSum();
        m_leftTable.resetHitSum();
        m_rightTable.resetHitSum();
    }

    void printGameStatus()
    {
        Serial.print(m_leftRacket.hitSum());
        Serial.print(m_leftTable.hitSum());
        Serial.print(m_rightRacket.hitSum());
        Serial.print(m_rightTable.hitSum());
        Serial.println("");
    }
};

#endif