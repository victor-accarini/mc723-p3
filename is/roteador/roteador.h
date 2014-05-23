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
    sc_export< ac_tlm_transport_if > target_export;
    /// Internal write
    ac_tlm_rsp_status writem( const uint32_t & , const uint32_t & );
    /// Internal read
    ac_tlm_rsp_status readm( const uint32_t & , uint32_t & );

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
      cout << "Transport READ at 0x" << hex << request.addr << " value ";
      cout << response.data << endl;
        #endif
        response.status = readm( request.addr , response.data );
        break;
      case WRITE:     // Packet is sent from Slave to Master
        #ifdef DEBUG
      cout << "Transport WRITE at 0x" << hex << request.addr << " value ";
      cout << request.data << endl;
        #endif
        response.status = writem( request.addr , request.data );
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
     * @param k Memory size in kilowords.
     *
     */
    ac_tlm_mem( sc_module_name module_name );

  private:
    uint8_t *memory;

  };

}

#endif //AC_TLM_MEM_H_
