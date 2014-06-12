/**
 * @file      factorial.cpp
 * @author    Grupo
 *
 * @author    The ArchC Team
 *            http://www.archc.org/
 *
 *            Computer Systems Laboratory (LSC)
 *            IC-UNICAMP
 *            http://www.lsc.ic.unicamp.br/
 *
 * @version   0.1
 * @date      Sun, 02 Apr 2006 08:07:46 -0200
 *
 * @brief     Implements a periferic.
 *
 * @attention Copyright (C) 2002-2005 --- The ArchC Team
 *
 *   This library is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU Lesser General Public
 *   License as published by the Free Software Foundation; either
 *   version 2.1 of the License, or (at your option) any later version.
 *
 *   This library is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *   Lesser General Public License for more details.
 *
 *
 */

//////////////////////////////////////////////////////////////////////////////
// Standard includes
// SystemC includes
// ArchC includes

#include "fatorial.h"
#include <endian.h>

//////////////////////////////////////////////////////////////////////////////

/// Namespace to isolate memory from ArchC
using user::factorial;

/// Constructor
factorial::factorial( sc_module_name module_name ) :
  sc_module( module_name ),
  target_export("iport")
{
    /// Binds target_export to the memory
    target_export( *this );

    /// Initialize memory vector
    factorial_numbers = new uint32_t[20];
    factorial_numbers[0] = 1U;
    factorial_numbers[1] = 1U;
    factorial_numbers[2] = 2U;
    factorial_numbers[3] = 6U;
    factorial_numbers[4] = 24U;
    factorial_numbers[5] = 120U;
    factorial_numbers[6] = 720U;
    factorial_numbers[7] = 5040U;
    factorial_numbers[8] = 40320U;
    factorial_numbers[9] = 362880U;
    factorial_numbers[10] = 3628800U;
    factorial_numbers[11] = 39916800U;
    factorial_numbers[12] = 479001600U;
/*    factorial_numbers[13] = 6227020800U;
    factorial_numbers[14] = 87178291200U;
    factorial_numbers[15] = 1307674368000U;
    factorial_numbers[16] = 20922789888000;
    factorial_numbers[17] = 355687428096000;
    factorial_numbers[18] = 6402373705728000;
    factorial_numbers[19] = 121645100408832000;
    factorial_numbers[20] = 2432902008176640000;
*/

}

/// Destructor
factorial::~factorial() {
  delete [] factorial_numbers;
}

/** Get Factorial
  * Note: Return a double
  * @param a is the number
  * @param d id the factorial of the number
  * @returns A TLM response packet with SUCCESS
*/
ac_tlm_rsp_status factorial::getfactorial( const uint32_t &a , uint32_t &d )
{
  //cout << "Endereço: " << a << " -- Valor: " << factorial_numbers[a] << "\n";
  d = factorial_numbers[a];
  d = be32toh(d);
  return SUCCESS;
}
