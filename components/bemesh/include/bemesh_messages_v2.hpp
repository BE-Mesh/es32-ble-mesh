/*
 * bemesh_messages_v2.hpp
 * its bemesh_messages but messages are treated like classes
 * as they should
 */

#pragma once

#include "routing.hpp"

namespace bemesh {
  class MessageHeader {
  protected:
    dev_addr_t m_dest_addr;
    dev_addr_t m_src_addr;
    uint8_t m_id;
    uint8_t m_hops;
    uint8_t m_seq;
    uint8_t m_psize;
  public:
    MessageHeader(dev_addr_t t_dest, dev_addr_t t_src, uint8_t t_id,
		  uint8_t t_hops, uint8_t t_seq, uint8_t t_psize);
    
    dev_addr_t& destination(void);
    dev_addr_t& source(void);
    uint8_t id(void);
    uint8_t hops(void);
    uint8_t seq(void);
    uint8_t psize(void);
    void setHops(uint8_t t_hops);
  };

  class IndexedMessage : public MessageHeader {
  protected:
    std::size_t m_entries;
  public:
    IndexedMessage(std::size_t t_entries, dev_addr_t t_dest, dev_addr_t t_src, uint8_t t_id,
		  uint8_t t_hops, uint8_t t_seq, uint8_t t_psize);
    std::size_t entries(void);    
  };

#define ROUTING_DISCOVERY_REQ_ID 0x00
  class RoutingDiscoveryRequest : public MessageHeader {
    RoutingDiscoveryRequest(dev_addr_t t_dest, dev_addr_t t_src);
  };

#define ROUTING_DISCOVERY_RES_ID 0x01
#define ROUTING_DISCOVERY_RES_ENTRIES_MAX 16
  class RoutingDiscoveryResponse : public IndexedMessage {
    std::array<routing_params_t, ROUTING_DISCOVERY_RES_ENTRIES_MAX> m_payload;
  public:
    RoutingDiscoveryResponse(dev_addr_t t_dest, dev_addr_t t_src,
			     std::array<routing_params_t,
			     ROUTING_DISCOVERY_RES_ENTRIES_MAX> t_payload,
			     std::size_t t_pentries);
    std::array<routing_params_t, ROUTING_DISCOVERY_RES_ENTRIES_MAX> payload(void);
  };
  
#define ROUTING_UPDATE_ID 0x02
#define ROUTING_UPDATE_ENTRIES_MAX 13
  class RoutingUpdateMessage : public IndexedMessage {
    std::array<routing_update_t, ROUTING_UPDATE_ENTRIES_MAX> m_payload;
  public:
    RoutingUpdateMessage(dev_addr_t t_dest, dev_addr_t t_src,
			 std::array<routing_update_t,
			 ROUTING_UPDATE_ENTRIES_MAX> t_payload,
			 std::size_t t_pentries);
    std::array<routing_update_t, ROUTING_UPDATE_ENTRIES_MAX> payload(void);
  };  
}
