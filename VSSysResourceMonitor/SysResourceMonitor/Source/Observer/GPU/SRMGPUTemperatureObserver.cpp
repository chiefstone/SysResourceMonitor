#include "Observer/GPU/SRMGPUTemperatureObserver.h"
#include "Observer/SRMModuleSubject.h"
#include "Observer/GPU/Nvidia/SRMNvidiaGPUInfo.h"
#include "Observer\GPU\ATI\SRMATIGPUInfo.h"

REG_SRM_OBSERVER(SRMGPUTemperatureObserver);
SRMGPUTemperatureObserver::SRMGPUTemperatureObserver()
	: SRMObserverBase("SRMGPUTemperatureObserver")
	, m_pGPUInfoInf(nullptr)
{

}

SRMGPUTemperatureObserver::~SRMGPUTemperatureObserver()
{

}

bool SRMGPUTemperatureObserver::init()
{
	m_pGPUInfoInf = SRMNvidiaGPUInfo::createGPUInfoInf();
    if (!m_pGPUInfoInf)
        m_pGPUInfoInf = SRMATIGPUInfo::createGPUInfoInf();

	if (!m_pGPUInfoInf)
		return false;

	return true;
}

void SRMGPUTemperatureObserver::update(int nIndex, VSSharedMemStruct* pSharedMemStruct, QList<QLabel*>& oLabelList)
{
	int nCurGPUTemperature = m_pGPUInfoInf->getTemperature(0);

	static VSShareMemTextNode oValueNode(0, 0, 0, L"0��");
	QColor oCurColor = fillCollorByValue(nCurGPUTemperature, &oValueNode);
	oValueNode.m_sInfo = QString::fromStdWString(L"%1��").arg(nCurGPUTemperature, 2, 10, QChar(' ')).toStdWString();
	pSharedMemStruct->setTextNode(0, nIndex, oValueNode);

	static VSShareMemTextNode oNameNode(0, 0, 0, L"GPU");
	fillCollorByValue(nCurGPUTemperature, &oNameNode);
	pSharedMemStruct->setTextNode(1, nIndex, oNameNode);

	static QPalette oPalette = oLabelList[nIndex]->palette();
	oPalette.setColor(QPalette::WindowText, oCurColor);
	oLabelList[nIndex]->setPalette(oPalette);
	oLabelList[nIndex]->setText(QString::fromStdWString(L"GPU:%1��").arg(nCurGPUTemperature, 2, 10, QChar(' ')));
}

void SRMGPUTemperatureObserver::regTrayMenu(QMenu* pTrayMenu)
{
	__super::regTrayMenu(pTrayMenu, QString::fromStdWString(L"GPU�¶�"));
}

int SRMGPUTemperatureObserver::order()
{
	return 50;
}

QString SRMGPUTemperatureObserver::customSettingDescription()
{
	return QString::fromStdWString(L"GPU�¶�:");
}