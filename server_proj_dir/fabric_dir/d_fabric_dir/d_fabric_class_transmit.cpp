/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_fabric_transmit.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../define_dir/fe_def.h"
#include "../../define_dir/size_def.h"
#include "d_fabric_class.h"

void DFabricClass::transmitData (void *port_obj_val, char *data_val)
{
    if ((data_val[SIZE_DEF::AJAX_ID_SIZE] != FE_DEF::GET_LINK_DATA_RESPONSE) || (strlen(data_val) > 18)) {
        if (true && this->debugOn()) {
            int len = 50;
            if (strlen(data_val) <= len) {
                printf("DFabricClass::transmitData() %s\n", data_val);
            }
            else {
                char data_buf[len + 1];
                memcpy(data_buf, data_val, len);
                data_buf[len] = 0;
                printf("DFabricClass::transmitData() %s\n", data_buf);
            }
        }
    }

    phwangPortTransmit(port_obj_val, data_val);
}
