/*
  Copyrights reserved
  Written by Paul Hwang
*/

class socket_class {
  public:
    socket_class();
    ~socket_class();
    void start_server ();
    void start_client ();

  private:
    void debug (int debug_val, char* str0_val, char* str1_val);
    void logit (char* str0_val, char* str1_val);
};
