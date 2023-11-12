//*******************************************************************
/*!
\file   ORB.h
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   03.02.2021
\brief
*/

//*******************************************************************
#ifndef _ORB_H
#define _ORB_H

//*******************************************************************
#include <stdarg.h>
#include <inttypes.h>

//*******************************************************************
/*! Datentypen
*/
typedef uint8_t        BYTE;  //!<  8-Bit Ganzzahl, vorzeichenlos
typedef uint16_t       WORD;  //!< 16-Bit Ganzzahl, vorzeichenlos
typedef unsigned long  DWORD; //!< 32-Bit Ganzzahl, vorzeichenlos


//*******************************************************************
/*!
\class ORB
\brief ORB-API

    Schnittstelle zwischen Anwendungssoftware bzw. Middleware und
    Laufzeitumgebung
*/
class ORB
{
  public:
    //***************************************************************
    /*!
    \class ORB::Motor
    \brief
    */
    class Motor
    {
      public:
        float pwr;    //!< Motorspannung (1/100 Betriebsspannung)
        float speed;  //!< Drehzahl (1/1000 Umdrehungen/Sekunde)
        int   pos;    //!< Absolute Position (1/1000 Umdrehungen)
    };

  public:
    //***************************************************************
    /*!
    \class ORB::Sensor
    \brief
    */
    class Sensor
    {
      public:
        //-----------------------------------------------------------
        // TDOD parameter beschreiben
        DWORD value[2];
        BYTE  type;
        BYTE  option;
        BYTE  lenExp;
    };

  public:
    //---------------------------------------------------------------
    /*! Betriebsmodi für Motoren
    */
    typedef enum
    {
      POWER_MODE  = 0, //!< Motor wird mit konstanter Spannung betrieben, keine Regelung
      BRAKE_MODE  = 1, //!< Kurzschlussbremse
      SPEED_MODE  = 2, //!< Drehzahlregelung
      MOVETO_MODE = 3  //!< Anfahren einer Zielposition mit Drehzahlregelung.
                       //!  Die Drehzahl wird ab der Startposition und vor der
                       //!  Zielposition rampenförmig angepasst. Die
                       //!  Rampensteilheit kann mit configMotor() eingestellt werden.
                       //!  Die maximale Drehzahl wird als Parameter in setMotor() übergeben.
    } MotorMode;

    //---------------------------------------------------------------
    /*! Sensortypen
    */
    typedef enum
    {
      ANALOG = 0, //!< Analog-Sensor
      UART   = 1, //!< EV3-UART-Sensor
      I2C    = 2, //!< I2C-Sensor
      TOF    = 3, //!< Ultraschall-Sensor (Time Of Flight)
      TOUCH  = 4  //!< NXT/EV3-Touch-Sensor
    } SensorType;

    //---------------------------------------------------------------
    /*! Erzeugt ein ORB-Objekt
        
        Das Objekt wird von der Firmware erzeugt und der Anwendungssoftware
        zur Verfügung gestellt. 
    */
    ORB( void )
    {
    }

    //---------------------------------------------------------------
    /// @name Motor
    //---------------------------------------------------------------
    ///@{
    //---------------------------------------------------------------
    /*! Konfiguration eines Motors

        An den Motor-Port können unterschiedliche Motoren angeschlossen werden.
        Für die Messung und Regelung der Motoren ist ein Encoder erforderlich.
        Mit der Konfiguration werden auch Regelparameter (PI-Regelung) eingestellt.

        \param id ID des Motor-Ports (0,...,3)
        \param ticsPerRotation 1/10 der Encoder-Tics pro Umdrehung
        \param acc Beschleunigung der Drehzahl im MOVETO_MODE (0,...,255)
        \param Kp Regelparameter der Drehzahlregelung, proportionaler Anteil (0,...,255).
                  Ein größerer Wert macht die Regelung schneller, kann aber auch
                  zu Schwingungen führen.
        \param Ki Regelparameter der Drehzahlregelung, integraler Anteil (0,...,255).
                  Ein größerer Wert verringert die Regelabweichung, kann zum
                  Überschwingen bei Lastwechsel führen.
    */
    virtual void configMotor( BYTE id,
                              WORD ticsPerRotation,
                              BYTE acc,
                              BYTE Kp,
                              BYTE Ki ) = 0;

    //---------------------------------------------------------------
    /*! Stellt den Motor auf die Betriebsart ein
        \param id ID des Motor-Ports (0,...,3)
        \param mode Betriebsart (MotorMode)
        \param speed Je nach Betriebsart:
                     <UL>
                     <LI>POWER_MODE<br>Motorspannung (1/1000 Betriebsspannung)</LI>
                     <LI>BRAKE_MODE<br>nicht verwendet</LI>
                     <LI>SPEED_MODE<br>Drehzahl (1/1000 Umdrehungen/Sekunde)</LI>
                     <LI>MOVETO_MODE<br>Max. Drehzahl (1/1000 Umdrehungen/Sekunde)</LI>
                     </UL>
        \param pos   Nur in der Betriebsart MOVETO_MODE: <br>Absolute Zielposition (1/1000 Umdrehungen)
    */
    virtual void setMotor ( BYTE  id,
                            BYTE  mode,
                            short speed,
                            int   pos ) = 0;

    //---------------------------------------------------------------
    /*! Liefert aktuelle Motordaten
        \param id ID des Motor-Ports (0,...,3)
        \return Motordaten
    */
    virtual ORB::Motor getMotor( BYTE id ) = 0;

    ///@}

    //---------------------------------------------------------------
    /// @name ModelServo
    //---------------------------------------------------------------
    ///@{
    //---------------------------------------------------------------
    /*! Stellt Modellbau-Servo
        \param id ID des Servo-Ports (0,1)
        \param speed Geschwindigkeit, mit der das Steuersignal vom
                     ursprünglichen Winkel auf den neuen Winkel
                     umgestellt wird (1/10 Aussteuerung/Sekunde, 0:aus,...,100:sofort)
        \param pos   Pulsbreite des Steuersignals mit dem der Servo
                     gesteuert wird (0,...,100), Einheit: (pos/100 + 1)*ms.
    */
    virtual void setModelServo( BYTE id,
                                BYTE speed,
                                BYTE pos ) = 0;
    ///@}

    //---------------------------------------------------------------
    /// @name Sensor
    //---------------------------------------------------------------
    ///@{
    //---------------------------------------------------------------
    /*! Konfiguriert Sensor
        \param id ID des Sensor-Ports (0,...,3)
        \param type Sensortyp (SensorType)
        \param mode Betriebsmode, Verwendung abhängig vom Sensortyp
        \param option Zusätzlich Optionen, sensorabhängig
    */
    virtual void configSensor( BYTE id,
                               BYTE type,
                               BYTE mode,
                               WORD option ) = 0;



    //---------------------------------------------------------------
    /*! Liefert Sensordaten
        \param id ID des Sensor-Ports (0,...,3)
        \return Sensordaten
    */
    virtual ORB::Sensor getSensor( BYTE id ) = 0;

    //---------------------------------------------------------------
    /*! Liefert die zusätzlichen, konfigurations<b>un</b>abhängigen Sensorwerte
        \param id ID des Sensor-Ports (0,...,3)
        \param ch Port-Pin, dessen Messwert geliefert werden soll
        \return Zusätzlicher Messwert:
        <UL>
        <LI>ch=0: Analog / Pin 1</LI>
        <LI>ch=1: Analog / Pin 2</LI>
        <LI>ch=2: Digital / Pin 5</LI>
        <LI>ch=3: Digital / Pin 6</LI>
        </UL>
    */
    virtual WORD getSensorValueExt( BYTE id, BYTE ch ) = 0;

    //---------------------------------------------------------------
    /*! Liefert Sensorwerte der zusätzlichen digitalen Ports
        \param id ID des digitalen Sensor-Ports (0,1)
        \return Digitalwert (0,1)
    */
    virtual BYTE getSensorDigital( BYTE id ) = 0;

    ///@}

    //---------------------------------------------------------------
    /// @name Monitor
    //---------------------------------------------------------------
    ///@{
    //---------------------------------------------------------------
    /*! Sendet eine Textzeile an den ORB-Monitor
        \param line Zeilennummer (0,...,3)
        \param format Format ensprechend der ANSI-C Funktion printf()
        \param va Parameterliste
    */
    virtual void setMonitorText( BYTE        line,
                                 const char *format,
                                 va_list     va ) = 0;

    //---------------------------------------------------------------
    /*! Liefert Keycode der auf dem ORB-Monitor betätigten Taste
        \return Keycode (0:keine Taste,...)
    */
    virtual BYTE getMonitorKey( void ) = 0;

    ///@}

    //---------------------------------------------------------------
    /// @name Time
    //---------------------------------------------------------------
    ///@{
    //---------------------------------------------------------------
    /*! Liefert Zeit seit Start der Laufzeitumgebung
        \return Laufzeit (ms)
    */
    virtual DWORD getTime( void ) = 0;

    //---------------------------------------------------------------
    /*! Unterbricht die Programmausführung für die angegebene Zeit
        \param time Unterbrechungsfdauer (ms)
    */
    virtual void wait( DWORD time ) = 0;

    ///@}

    //---------------------------------------------------------------
    /// @name Memory
    //---------------------------------------------------------------
    ///@{
    //---------------------------------------------------------------
    /*! Löscht den persistenten Speicher

        Muss einmalig vor setMemory() aufgerufen werden, da nur blockweise
        geschrieben werden kann.
    */
    virtual void clearMemory( void ) = 0;

    //---------------------------------------------------------------
    /*! Schreibt einen Datenblock auf den persistenten Speicher

        Vor erstmaligem Aufruf dieser Methode muss der Speicher mit
        clearMemory() gelöscht werden.
        \param addr Startadresse
        \param data Zeiger auf Datenbereich, der gespeichert werden soll
        \param size Anzahl zu schreibender Datenbytes
    */
    virtual void setMemory( DWORD  addr,
                            BYTE  *data,
                            DWORD  size ) = 0;

    //---------------------------------------------------------------
    /*! Liest einen Datenblock vom persistenten Speicher

        Falls der Speicher gelöscht wurde, enthalten alle Datenbytes
        den Wert 0xFF
        \param addr Startadresse
        \param data Zeiger auf Datenbereich für Speicherinhalte
        \param size Anzahl zu lesender Datenbytes
    */
    virtual void getMemory( DWORD  addr,
                            BYTE  *data,
                            DWORD  size ) = 0;

    ///@}

    //---------------------------------------------------------------
    /// @name Miscellaneous
    //---------------------------------------------------------------
    ///@{
    //---------------------------------------------------------------
    /*! Liefert den Wert der Versorgungsspannung
        \return Versorgungsspannung (Volt)
    */
    virtual float getVcc( void ) = 0;

    ///@}


    unsigned *prog;

};

#endif // _ORB_H
