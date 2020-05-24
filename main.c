#include <NodesetLoader/backendOpen62541.h>
#include <open62541/plugin/log_stdout.h>
#include <open62541/server.h>
#include <open62541/server_config_default.h>

static volatile UA_Boolean running = true;
static void stopHandler(int sign) {
  UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "received ctrl-c");
  running = false;
}

int main(int argc, const char *argv[]) {
  UA_Server *server = UA_Server_new();
  UA_ServerConfig_setDefault(UA_Server_getConfig(server));
  //provide the server and the path to nodeset
  //returns true in case of successful import
  if(!NodesetLoader_loadFile(server, "../Opc.Ua.Di.NodeSet2.xml", NULL))
  {
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "importing the xml nodeset failed");
  }
  UA_StatusCode retval = UA_Server_run(server, &running);
  UA_Server_delete(server);
  return retval == UA_STATUSCODE_GOOD ? EXIT_SUCCESS : EXIT_FAILURE;
}