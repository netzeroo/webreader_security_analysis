//#include <ipfs/client.h>
#include <drogon/drogon.h>
#include <controllers/MangaCtrl.h>

int main (int argc, char** argv) {
    
    drogon::app().loadConfigFile("./config.json");
    drogon::app().run();
    
    return 0;
    
}
