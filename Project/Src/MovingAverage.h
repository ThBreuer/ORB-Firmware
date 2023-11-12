//*******************************************************************
/*!
\file   MovingAverage.h
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   03.02.2021
*/

//*******************************************************************
#ifndef _MOVING_AVERAGE_H
#define _MOVING_AVERAGE_H

//*******************************************************************
/*!
\class MovingAverage
\brief
*/
template <unsigned AVG_SIZE> class MovingAverage
{
  private:
    //---------------------------------------------------------------
    float     faktor;
    unsigned  index;
    float     sum;
    float     samples[AVG_SIZE];

  public:
    //---------------------------------------------------------------
    MovingAverage( void )
    {
      index  = 0;
      sum    = 0;
      faktor = 1.0/AVG_SIZE;
    }

    //---------------------------------------------------------------
    float get(float val)
    {
      //Moving Average Filter
      if( index >= AVG_SIZE )
      {
        index = 0;
      }
      sum = sum - samples[index];
      samples[index] = val;
      sum = sum + val;

      index++;
      return faktor*sum;
    }
};

#endif
