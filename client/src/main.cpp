#include <QCoreApplication>

#include "MyHttpClient.h"

int main(int argc, char** argv)
{
  QCoreApplication app(argc, argv);
  MyHttpClient client(&app);
//  client.doDownload("http://10.8.0.1/index.php", "counter");
//  client.doUpload("http://10.8.0.1/index.php", QByteArray("{\"uid\":\"sdc_667\",\"counter_uid\":\"cdb_70\",\"value\":1123.321,\"meas_type_uid\":\"cdb_43\",\"datetime\": \"01.09.2015 10:00:00\"}"));
//  client.doDelete("table", "uid_11");
  client.doUpdate("table", "uid_1", QByteArray("{\"uid\":\"sdc_667\",\"counter_uid\":\"cdb_70\",\"value\":1123.321,\"meas_type_uid\":\"cdb_43\",\"datetime\": \"01.09.2015 10:00:00\"}"));
  client.doUpdate("table", "uid_1", QByteArray("{\"uid\":\"sdc_667\",\"counter_uid\":\"cdb_70\",\"value\":1123.321,\"meas_type_uid\":\"cdb_43\",\"datetime\": \"01.09.2015 10:00:00\"}"));
  client.doUpdate("table", "uid_1", QByteArray("{\"uid\":\"sdc_667\",\"counter_uid\":\"cdb_70\",\"value\":1123.321,\"meas_type_uid\":\"cdb_43\",\"datetime\": \"01.09.2015 10:00:00\"}"));
  client.doUpdate("table", "uid_1", QByteArray("{\"uid\":\"sdc_667\",\"counter_uid\":\"cdb_70\",\"value\":1123.321,\"meas_type_uid\":\"cdb_43\",\"datetime\": \"01.09.2015 10:00:00\"}"));

  return app.exec();
}
