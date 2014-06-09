// Standard includes
// SystemC includes
// ArchC includes

#include "roteador.h"

//////////////////////////////////////////////////////////////////////////////

/// Namespace to isolate memory from ArchC
using user::roteador;

/// Constructor
roteador::roteador( sc_module_name module_name, uint core_num ) :
  sc_module( module_name ), DM_port("DM_port", 5242880), LOCK_port("LOCK_port", 4)
{
    std::stringstream nome;
    char nome_str[100];

    //target_export = new sc_export< ac_tlm_transport_if > *[core_num];
    this->core_num = core_num;

    target_export(*this);
    /// Binds target_export to the router
    //for (int i = 0; i < core_num; i++)
    //{
	 //nome.str("iport");
	 //nome << i;WS
	 //nome.getline(nome_str, 100);
	 
         //target_export[i] = new sc_export< ac_tlm_transport_if >( nome_str );
	 //(*target_export[i])(*this);
   // }
}

roteador::~roteador()
{
    //int i;
    //for (i = 0; i < core_num; i++){
    //    delete target_export[i];
    //}

    //delete [] target_export;
}

