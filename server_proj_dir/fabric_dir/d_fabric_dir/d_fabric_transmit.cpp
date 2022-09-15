/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_fabric_transmit.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../define_dir/fe_def.h"
#include "d_fabric_class.h"

void DFabricClass::transmitFunction (void *tp_transfer_object_val, char *data_val)
{
  if (*data_val != FE_DEF::FE_GET_LINK_DATA_RESPONSE) {
      phwangDebugS(true, "DFabricClass::transmitFunction", data_val);
    }

    phwangTpTransmit(tp_transfer_object_val, data_val);
}
