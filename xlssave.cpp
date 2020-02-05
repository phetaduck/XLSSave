#include "xlssave.h"
#include "ui_xlssave.h"

XLSSave::XLSSave(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::XLSSave)
{
    ui->setupUi(this);
}

XLSSave::~XLSSave()
{
    delete ui;
}

void XLSSave::onMQTTMsgRecieved(QString msg)
{
    ui->textEdit->append(msg);
}


void XLSSave::on_pushButton_clicked()
{
    mqttImpl.connectToBroker(ui->leHost->text());
    connect(&mqttImpl, &MQTT_Impl::MessageRecieved,
            this, &XLSSave::onMQTTMsgRecieved);
    mqttImpl.subscribe(ui->leTopic->text());
    mqttImpl.start(true);
}
