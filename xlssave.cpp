#include "xlssave.h"
#include "ui_xlssave.h"
#include <QProgressDialog>
#include <QDir>
#include <QFileDialog>
#include <QThreadPool>


XLSSave::XLSSave(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::XLSSave)
{
    ui->setupUi(this);
    qRegisterMetaType< std::string >( "std::string"   );

}

XLSSave::~XLSSave()
{
    delete ui;
}

void XLSSave::onMQTTMsgRecieved(std::string msg)
{
    m_curves.ParseFromString(msg);
    for (const auto& curve : m_curves.curves())
    {
        ui->textEdit->append(QString::fromStdString(curve.m_name()));
        /*
        for (const auto& value : curve.m_values()) {
            ui->textEdit->append(QString::fromStdString(value));
        }
        */
    }
}


void XLSSave::on_pushButton_clicked()
{
    mqttImpl.connectToBroker(ui->leHost->text());
    connect(&mqttImpl, &MQTT_Impl::MessageRecieved,
            this, &XLSSave::onMQTTMsgRecieved);
    mqttImpl.subscribe(ui->leTopic->text());
    mqttImpl.start(true);
}

void XLSSave::on_actionExport_As_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this,
                                                    "Export as",
                                                    QDir::currentPath(),
                                                    "*.xlsx");
    m_exporter.emplace(filename, m_curves);
    m_exporter->setAutoDelete(false);
    m_xlsSavePD = new QProgressDialog("Exporting XLSX", "Cancel", 0, 100);
    m_xlsSavePD->setWindowModality(Qt::WindowModal);
    m_xlsSavePD->setAutoClose(true);
    m_xlsSavePD->show();
    QObject::connect(&m_exporter.value(), &XLS_Exporter::fileSaved,
                                     m_xlsSavePD, &QProgressDialog::reset);
    QObject::connect(&m_exporter.value(), &XLS_Exporter::progressNotifier,
                                     m_xlsSavePD, &QProgressDialog::setValue);
    QThreadPool::globalInstance()->start(&m_exporter.value());
}

void XLSSave::on_actionExit_triggered()
{
    exit(0);
}
