#ifndef XLSSAVE_H
#define XLSSAVE_H

#include <QMainWindow>
#include "xls_exporter.h"

#include <mqtt_impl.h>

QT_BEGIN_NAMESPACE
namespace Ui { class XLSSave; }
QT_END_NAMESPACE

class XLSSave : public QMainWindow
{
    Q_OBJECT

public:
    XLSSave(QWidget *parent = nullptr);
    ~XLSSave();

public slots:
    void onMQTTMsgRecieved(QString msg);

private slots:
    void on_pushButton_clicked();

private:
    Ui::XLSSave *ui;

    MQTT_Impl mqttImpl = {};
};
#endif // XLSSAVE_H
