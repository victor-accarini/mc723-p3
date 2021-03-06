/**
 * @file      lock.cpp
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
 * @brief     Implements a ac_tlm memory.
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

#include "lock.h"

//////////////////////////////////////////////////////////////////////////////

/// Namespace to isolate memory from ArchC
using user::lock;

/// Constructor
lock::lock( sc_module_name module_name ) :
  sc_module( module_name ),
  target_export("iport")
{
    /// Binds target_export to the memory
    target_export( *this );

    /// Initialize memory vector
    int k = 4;
    memory = new uint8_t[ k ];
    for(k=k-1;k>0;k--) memory[k]=0;
    *((uint32_t *) &memory[0]) = 0;

}

/// Destructor
lock::~lock() {

  delete [] memory;
}

/** Internal Write
  * Note: Always write 32 bits
  * @param a is the address to write
  * @param d id the data being write
  * @returns A TLM response packet with SUCCESS
*/
ac_tlm_rsp_status lock::setlock()
{
  const uint32_t d = 0;
  *((uint32_t *) &memory[0]) = 0;
  return SUCCESS;
}

/** Internal Read
  * Note: Always read 32 bits
  * @param a is the address to read
  * @param d id the data that will be read
  * @returns A TLM response packet with SUCCESS and a modified d
*/
ac_tlm_rsp_status lock::getlock(const uint32_t &d )
{
  *((uint32_t *) &d) = *((uint32_t *) &memory[0]);
  *((uint32_t *) &memory[0]) = 1;
  return SUCCESS;
}



