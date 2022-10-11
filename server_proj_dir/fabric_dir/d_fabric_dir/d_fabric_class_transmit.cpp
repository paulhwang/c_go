/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_fabric_transmit.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../define_dir/fe_def.h"
#include "../../define_dir/size_def.h"
#include "d_fabric_class.h"

void DFabricClass::transmitFunction (void *port_object_val, char *data_val)
{
    if ((data_val[SIZE_DEF::AJAX_ID_SIZE] != FE_DEF::FE_GET_LINK_DATA_RESPONSE) || (strlen(data_val) > 18)) {
      phwangDebugS(true, "DFabricClass::transmitFunction", data_val);
    }

    phwangPortTransmit(port_object_val, data_val);
}
