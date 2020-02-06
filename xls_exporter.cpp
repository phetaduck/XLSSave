#include "xls_exporter.h"

#include "xlsxdocument.h"

#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QRunnable>

XLS_Exporter::~XLS_Exporter() = default;

XLS_Exporter::XLS_Exporter(QString fileName, const LAS2XLS::Curves &curves) :
    m_fileName(std::move(fileName)), m_curves(curves)
{

}

void XLS_Exporter::stop()
{
	QMutexLocker lock(&m_stop_signal);
	m_stop = true;
}

void XLS_Exporter::run()
{
	saveCurves();
	emit fileSaved();
}

void XLS_Exporter::saveCurves()
{
	QXlsx::Document xlsx;
    float totalSize = m_curves.curves_size() * m_curves.curves().Get(0).m_values_size();
	float currentProg = 1.0f;
	float adjProgress = 0.0f;
	int column = 1;
    for (const auto c : m_curves.curves()) {
		int row = 1;
        xlsx.write(row, column, QString::fromStdString(c.m_name()));
        for (const auto& v : c.m_values())
		{
			{
				QMutexLocker lock(&m_stop_signal);
				if (m_stop) return;
                xlsx.write(++row, column, QString::fromStdString(v));
				adjProgress = 100.0f * (currentProg++ / totalSize);
			}
			emit progressNotifier(int(adjProgress));
		}
		column++;
	}
	xlsx.saveAs(m_fileName);
}
