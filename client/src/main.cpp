#include <QCoreApplication>

#include "MyHttpClient.h"

int main(int argc, char** argv)
{
  QCoreApplication app(argc, argv);
  MyHttpClient client(&app);
  client.doDownload("http://localhost:8080");
  client.doUpload("http://localhost:8080/tables/data", QByteArray("Hello!!!"));
  return app.exec();
}
