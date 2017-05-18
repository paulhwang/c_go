/*
  Copyrights reserved
  Written by Paul Hwang
*/

#include "../includes/common.h"

class transport_class {
  public:
    transport_class();
    ~transport_class();
    void start_server(ushort port_val);
    void start_client(ulong ip_addr_val, ushort port_val);

  private:
    void debug(int debug_val, char const* str0_val, char const* str1_val);
    void logit(char const* str0_val, char const* str1_val);
};
