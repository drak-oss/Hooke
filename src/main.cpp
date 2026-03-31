#include "app/app.h"
#include <iostream>

int main() {
    App app ;
    if(app.initApp() == false) {
        std::cout << "Falied To Initialise App !" << std::endl ;
        return -1 ;
    }
    
    app.runApp() ;
    app.shutdownApp() ;
    return 0 ;
}