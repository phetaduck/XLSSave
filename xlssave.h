#ifndef XLSSAVE_H
#define XLSSAVE_H

#include <QMainWindow>
#include "xls_exporter.h"

#include <mqtt_impl.h>
#include <optional>

QT_BEGIN_NAMESPACE
namespace Ui { class XLSSave; }
QT_END_NAMESPACE

class QProgressDialog;
class XLSSave : public QMainWindow
{
    Q_OBJECT

public:
    XLSSave(QWidget *parent = nullptr);
    ~XLSSave();

public slots:
    void onMQTTMsgRecieved(std::string msg);

private slots:
    void on_pushButton_clicked();

    void on_actionExport_As_triggered();

    void on_actionExit_triggered();

private:
    Ui::XLSSave *ui;

    MQTT_Impl mqttImpl = {};
    std::optional<XLS_Exporter> m_exporter;
    QProgressDialog* m_xlsSavePD;
    LAS2XLS::Curves m_curves = {};
};
#endif // XLSSAVE_H
