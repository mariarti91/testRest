#include <QCoreApplication>

#include "MyHttpClient.h"

int main(int argc, char** argv)
{
  QCoreApplication app(argc, argv);
  MyHttpClient client(&app);
  client.doDownload("http://10.8.0.1/index.php", "counter");
  //client.doUpload("http://10.8.0.1/index.php", QByteArray("Hello!!!"));
  return app.exec();
}
