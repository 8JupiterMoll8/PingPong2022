#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include"RacketRight.hpp"
#include "RacketLeft.h"
#include "Table.h"
#pragma once
// The Gamem
class GameManager
{
private:

RacketLeft  &m_leftRacket;
RacketRight &m_rightRacket;
Table       &m_leftTable;
Table       &m_rightTable;
int totalBallWechselCounter = 0;

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
    GameManager(RacketLeft &leftRacket, RacketRight &rightRacket, Table &leftTable, Table&rightTable):
    m_leftRacket(leftRacket),
    m_rightRacket(rightRacket),
    m_leftTable(leftTable),
    m_rightTable(rightTable)
    {
    }

    void setup()
    {
    }

    void loop()
    {
     m_leftRacket.loop();
     m_rightRacket.loop();
     m_leftTable.loop();
     m_rightTable.loop();

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
            Serial.println("State 1.) AUFSCHLAG : Warte dass, der Ball trift Left Racket trift");

            // printGameStatus();
            resetAllCounters();

            // Leave State:
            state = lr_AS;

            // Leave State:
            break;
        /*
       █████╗ ██╗   ██╗███████╗███████╗ ██████╗██╗  ██╗██╗      █████╗  ██████╗
      ██╔══██╗██║   ██║██╔════╝██╔════╝██╔════╝██║  ██║██║     ██╔══██╗██╔════╝
      ███████║██║   ██║█████╗  ███████╗██║     ███████║██║     ███████║██║  ███╗
      ██╔══██║██║   ██║██╔══╝  ╚════██║██║     ██╔══██║██║     ██╔══██║██║   ██║
      ██║  ██║╚██████╔╝██║     ███████║╚██████╗██║  ██║███████╗██║  ██║╚██████╔╝
      ╚═╝  ╚═╝ ╚═════╝ ╚═╝     ╚══════╝ ╚═════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝ ╚═════╝
      */
        // States: Hit Left Racket >> Hit Left Table >> Hit Right Table >> Hit Right Racket
        // >> Succseful Aufschlag
        case lr_AS:
            // Do

            // Leave State:
            if (m_leftRacket.hitSum() == 1)
            {
                Serial.println("AUFSCHLAG : BAll trift Left Racket");
                Serial.println("State 2.)AUFSCHLAG : Warte das BAll trift Left Table");

                // printGameStatus();
                resetAllCounters();
                state = lt_AS;
            }

            break;

        case lt_AS:
            // Do
            //  Leave State:
            if (m_leftTable.hitSum() == 1)
            {
                Serial.println("AUFSCHLAG : BAll trift Left Table");
                Serial.println("State 3.) AUFSCHLAG : Warte das BAll trift Right Table");

                // printGameStatus();
                resetAllCounters();
                state = rt_AS;
            }

            break;

        case rt_AS:
            // Do
            //  Leave State:
            if (m_rightTable.hitSum() == 1)
            {

                Serial.println("AUFSCHLAG : BAll trift Right Table");
                Serial.println("AUFSCHLAG : Warte das BAll trift Right Racket");

                // printGameStatus();
                resetAllCounters();
                state = rr_AS;
            }
            break;

        case rr_AS:
            // Do
            //  Leave State:
            if (m_rightRacket.hitSum() == 1)
            {
                Serial.println("AUFSCHLAG : BAll trift Right Racket");
                Serial.println("AUFSCHLAG Erfolgreich");
                Serial.println("Starte Ballwechsel");
                Serial.println("BAllWechsel : Warte das BAll trift Left Table");

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
            // Do
            //  Leave State:
            if (m_leftTable.hitSum() == 1) // Hit Left Table
            {
                usbMIDI.sendNoteOff(74, 127, 2);

                Serial.println("Ballwechsel : Warte das BAll trift Left Racket");

                resetAllCounters();
                state = lr_BW;
            }
            break;

        case lr_BW:
            // Dou
            //  Leave State:
            if (m_leftRacket.hitSum() == 1) // Hit Left RACket
            {
                usbMIDI.sendNoteOn(54, 127, 2);
                Serial.println("Ballwechsel : Warte das BAll trift Right Table");

                resetAllCounters();
                state = rt_BW;
            }
            break;

        case rt_BW:
            // Do

            // Leave State:
            if (m_rightTable.hitSum() == 1) // Hit Right Table
            {
                usbMIDI.sendNoteOff(54, 0, 2);
                Serial.println("Ballwechsel : Warte das BAll trift Right RAcket");

                resetAllCounters();
                state = rr_BW;
            }
            break;

        case rr_BW:
            // Do
            //  Leave State:
            if (m_rightRacket.hitSum() == 1) // Hit Right Racket
            {
                usbMIDI.sendNoteOn(74, 127, 2);
                Serial.println("Ballwechsel : Erfolgreich");

                resetAllCounters();
                state = count_BW;
            }
            break;

        case count_BW:
            // Do

            Serial.print("TOTAL- Ballwechsel : ");
            Serial.println(++totalBallWechselCounter);
            Serial.println("BAllWechsel : Warte das BAll trift Left Table");

            // Leave State:
            state = lt_BW;
            break;

        default:
            break;
        } // end switch
    }

private:
    /*
    ███████╗███████╗██╗  ██╗██╗     ███████╗██████╗
    ██╔════╝██╔════╝██║  ██║██║     ██╔════╝██╔══██╗
    █████╗  █████╗  ███████║██║     █████╗  ██████╔╝
    ██╔══╝  ██╔══╝  ██╔══██║██║     ██╔══╝  ██╔══██╗
    ██║     ███████╗██║  ██║███████╗███████╗██║  ██║
    ╚═╝     ╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚═╝  ╚═╝
    */
    // Restart Game
    // Rule: The Ball does never hit two times at the Table or Racket and does fall to earth
    boolean isFehler()
    {
        
        if (m_leftRacket.hitSum() > 1 || m_leftTable.hitSum() > 1 || m_rightTable.hitSum() > 1 || m_rightRacket.hitSum() > 1)
        {

            return true;
        }
        else
        {
            return false;
        }
    }
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