/*
  Copyrights reserved
  Written by Paul Hwang
  File name: game_u_server_test.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "u_theme_class.h"

void GameUServerClass::baseMgrTest (void)
{
	return;

    char *buf = (char *) malloc(BASE_MGR_DATA_BUFFER_SIZE + 4);
    buf[0] = BASE_MGR_PROTOCOL_COMMAND_IS_MALLOC_BASE;
    buf[1] = BASE_MGR_PROTOCOL_GAME_NAME_IS_GO;
    buf[2] = 0;
    this->transmitFunction(buf);
}
