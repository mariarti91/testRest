#include <QCoreApplication>

#include "MyHttpServer.h"

int main(int argc, char** argv)
{
  QCoreApplication app(argc, argv);
  MyHttpServer server(&app);
  return app.exec();
}
