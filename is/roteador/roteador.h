//////////////////////////////////////////////////////////////////////////////

#ifndef ROTEADOR_H_
#define ROTEADOR_H_

//////////////////////////////////////////////////////////////////////////////

// Standard includes
// SystemC includes
#include <systemc>
// ArchC includes
#include "ac_tlm_protocol.H"

//////////////////////////////////////////////////////////////////////////////

// using statements
using tlm::tlm_transport_if;

//////////////////////////////////////////////////////////////////////////////

//#define DEBUG

/// Namespace to isolate memory from ArchC
namespace user
{

/// A TLM memory
class roteador :
  public sc_module,
  public ac_tlm_transport_if // Using ArchC TLM protocol
  {
    public:
    /// Exposed port with ArchC interface
    sc_export< ac_tlm_transport_if > **target_export;

    ac_tlm_port DM_port;

    /**
     * Implementation of TLM transport method that
     * handle packets of the protocol doing apropriate actions.
     * This method must be implemented (required by SystemC TLM).
     * @param request is a received request packet
     * @return A response packet to be send
    */
    ac_tlm_rsp transport( const ac_tlm_req &request ) {

      ac_tlm_rsp response;

      switch( request.type ) {
      case READ :     // Packet is sent from Master to Slave
        #ifdef DEBUG  // Turn it on to print transport level messages
        response = DM_port->transport(request);
        #endif
        break;
      case WRITE:     // Packet is sent from Slave to Master
        #ifdef DEBUG
        response = DM_port->transport(request);
        #endif
        break;
      default :
        response.status = ERROR;
        break;
      }

      return response;
    }


    /**
     * Default constructor.
     *
     * @param k .
     *
     */
    roteador( sc_module_name module_name, uint core_num );

    /**
     * Default destructor.
     */
    ~roteador();
    
    private:
      uint core_num;
  };

}

#endif //ROTEADOR_H_
