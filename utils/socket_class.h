/*
  Copyrights reserved
  Written by Paul Hwang
*/

class socket_class {
  public:
    socket_class();
    ~socket_class();
    void start_server(int port_val);
    void start_client();

  private:
    void debug(int debug_val, char const* str0_val, char const* str1_val);
    void logit(char const* str0_val, char const* str1_val);
};
