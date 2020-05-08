#include <NodesetLoader/backendOpen62541.h>
#include <open62541/server.h>
#include <open62541/server_config_default.h>

int main(int argc, const char *argv[]) {
  UA_Server *server = UA_Server_new();
  UA_ServerConfig_setDefault(UA_Server_getConfig(server));
  NodesetLoader_loadFile(server, "unknownPath", NULL);
}