//Adresse Serveur : 10.5.133.185

#include "libraries.h"

int main(int argc, char *argv[])
{
       QApplication app(argc, argv);

       MainWindow w;
       w.show();
       //Log l;
       //l.creerLog();

       return app.exec();
}

