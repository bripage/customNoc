//
// Created by tokth on 7/11/23.
//

#ifndef _RTREVENT_CONVERTER_H_
#define _RTREVENT_CONVERTER_H_

#include "eventConverter.h"
#include <sst/core/event.h>
#include <sst/core/link.h>
#include <sst/core/interfaces/simpleNetwork.h>
#include <sst/core/interfaces/stdMem.h>
#include <sst/elements/merlin/router.h>
#include "memToRtr.h"

using namespace SST;
using namespace SST::eventConverter;

class rtrToMem : public baseSubComponent {
    public:
        SST_ELI_REGISTER_SUBCOMPONENT(
            rtrToMem,
            "eventConverter",
            "rtrToMem",
            SST_ELI_ELEMENT_VERSION(1,0,0),
            "rtrToMem : accepts router events and passes them to the memory subcomponent",
            SST::eventConverter::baseSubComponent
        )

        SST_ELI_DOCUMENT_PARAMS()

        SST_ELI_DOCUMENT_PORTS(
            {"rtrPort", "Link to another component which uses SST::Interfaces::SimpleNetwork.", {"simpleNetworkExample.nicEvent"} }
        )

        SST_ELI_DOCUMENT_SUBCOMPONENT_SLOTS(
            {"iface", "SimpleNetwork interface to a network", "SST::Interfaces::SimpleNetwork"}
        )

        rtrToMem(ComponentId_t id, Params& params);
        ~rtrToMem();
        void send(SST::Event*);
        bool handleEvent(int vn);
        void init(unsigned int phase) = 0;

    private:
        // Params
        SST::Output* out;           // SST Output object for printing, messaging, etc
        SST::Interfaces::SimpleNetwork* iFace; // SST network interface
        SSST::Interfaces::SimpleNetwork::nid_t memContCompID;
};

#endif