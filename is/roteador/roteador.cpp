// Standard includes
// SystemC includes
// ArchC includes

#include "roteador.h"

//////////////////////////////////////////////////////////////////////////////

/// Namespace to isolate memory from ArchC
using user::roteador;

/// Constructor
roteador::roteador( sc_module_name module_name ) :
  sc_module( module_name ),
  target_export("iport")
{
    /// Binds target_export to the memory
    target_export( *this );
}



