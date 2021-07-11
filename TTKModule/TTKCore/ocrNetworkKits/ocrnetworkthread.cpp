#include "ocrnetworkthread.h"
#include "ocrobject.h"

#include <QHostInfo>
#if TTK_QT_VERSION_CHECK(5,0,0)
#  include <QtConcurrent/QtConcurrent>
#else
#  include <QtConcurrentRun>
#endif

#define NETWORK_DETECT_INTERVAL     5000             // second
#define NETWORK_REQUEST_ADDRESS     "www.baidu.com"  // ip

OCRNetworkThread::OCRNetworkThread()
    : QObject(nullptr), m_networkState(true)
{
    connect(&m_timer, SIGNAL(timeout()), SLOT(networkStateChanged()));
}

OCRNetworkThread::~OCRNetworkThread()
{
    m_timer.stop();
}

void OCRNetworkThread::start()
{
    TTK_LOGGER_INFO("Load NetworkThread");
    m_timer.start(NETWORK_DETECT_INTERVAL);
}

void OCRNetworkThread::networkStateChanged()
{
    const auto status = QtConcurrent::run([&]
    {
        QHostInfo info = QHostInfo::fromName(NETWORK_REQUEST_ADDRESS);
        m_networkState = !info.addresses().isEmpty();
        emit networkConnectionStateChanged(m_networkState);
    });
    Q_UNUSED(status);
}
