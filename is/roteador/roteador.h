//////////////////////////////////////////////////////////////////////////////

#ifndef ROTEADOR_H_
#define ROTEADOR_H_

//////////////////////////////////////////////////////////////////////////////

// Standard includes
// SystemC includes
#include <systemc>
// ArchC includes
#include "ac_tlm_protocol.H"
#include "ac_tlm_port.H"

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

  ac_tlm_port DM_port;
  ac_tlm_port LOCK_port;
  ac_tlm_port F_port;

  /**
     * Implementation of TLM transport method that
     * handle packets of the protocol doing apropriate actions.
     * This method must be implemented (required by SystemC TLM).
     * @param request is a received request packet
     * @return A response packet to be send
    */
  ac_tlm_rsp transport( const ac_tlm_req &request ) {

    ac_tlm_rsp response;
    ac_tlm_req *req_arrumada;

    if (request.addr < 5242880 ){
      response = DM_port->transport(request);
    } else if (request.addr <= 5242884){
      req_arrumada = arruma(request, 0);
      response = LOCK_port->transport(*req_arrumada);
    } else {
      errs() << "Request para o Fatorial\n";
      req_arrumada = arruma(request, request.addr - 5242888);
      response = F_port->transport(*req_arrumada);
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
  ac_tlm_req req;

  ac_tlm_req* arruma(const ac_tlm_req &request, int m)
  {
    ac_tlm_req *arruma_req = &req;
    memcpy(arruma_req, &request, sizeof(ac_tlm_req));
    arruma_req->addr = m;
    return arruma_req;
  }

};

}

#endif //ROTEADOR_H_
