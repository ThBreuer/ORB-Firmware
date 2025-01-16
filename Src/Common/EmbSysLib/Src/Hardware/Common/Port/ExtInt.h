//*******************************************************************
/*!
\file   ExtInt.h
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   23.03.2016

This file is released under the MIT License.
*/

//*******************************************************************
#ifndef _HW_EXTINT_H
#define _HW_EXTINT_H

//*******************************************************************
/*!
\class cHwExtInt

\brief ...


\example ...
*/
class cHwExtInt
{
  public:
//---------------------------------------------------------------
    /*! \enum PortId
        \brief GPIO port identification
    */
    typedef enum
    {
      NONE = 0,   //!< No Interrupt
      RISING,     //!< Interrupt with rising edge
      FALLING,    //!< Interrupt with falling edge
      BOTH        //!< Interrupt with both edges
    } Edge;
  public:
    //*******************************************************************
    /*!
    \class Task

    \brief Base class for external interrupt tasks
    */
    class Task : public EmbSysLib::Std::Sequence<Task>::Item
    {
      public:
        //---------------------------------------------------------
        /*! Method called by timer interrupt.
            The application has to override this method.
        */
        virtual void update( void ) = 0;

    }; //Timer::Task
    //*******************************************************************
//---------------------------------------------------------------
    /*! Add a new object to the update-list.
        After executing this method, the objects update()-method
        will been called periodically by timer interrupt
        \param ptr Pointer to the object
    */
    virtual void add( Task *ptr );

public:
    //---------------------------------------------------------------
    // Interrupt Service Routine of timer interrupt
    // This method has to been called by the hardware driven
    // interrupt service routine only
    //
    virtual void isrHandler( void );

    virtual void enable() = 0;
    virtual void disable() = 0;
    virtual void setEdge( Edge edge) = 0;

  private:
    //---------------------------------------------------------------
    EmbSysLib::Std::Sequence<Task> isrList; // list of callable objects

}; //cHwExtInt

#endif
