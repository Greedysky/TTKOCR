#include "ocrurlutils.h"

#include <QUrl>
#include <QProcess>
#include <QDesktopServices>
#ifdef Q_OS_WIN
#include <qt_windows.h>
#include <shellapi.h>
#endif

bool OCRUtils::Url::openUrl(const QString &exe, const QString &path)
{
#ifdef Q_OS_WIN
    HINSTANCE value = ShellExecuteW(0, exe.toStdWString().c_str(), path.toStdWString().c_str(), nullptr, nullptr, SW_SHOWNORMAL);
    return value->unused >= 32;
#else
    Q_UNUSED(exe);
    return QProcess::startDetached(path, QStringList());
#endif
}

bool OCRUtils::Url::openUrl(const QString &path, bool local)
{
#ifdef Q_OS_WIN
    if(path.isEmpty())
    {
        return false;
    }

    if(local)
    {
        QString p = path;
        p.replace('/', "\\");
        p = "/select," + p;
        HINSTANCE value = ShellExecuteW(0, L"open", L"explorer.exe", p.toStdWString().c_str(), nullptr, SW_SHOWNORMAL);
        return value->unused >= 32;
    }
#else
    Q_UNUSED(local);
#endif
    return QDesktopServices::openUrl(QUrl(path, QUrl::TolerantMode));
}

void OCRUtils::Url::urlEncode(QString &data)
{
    data.replace('+', "%2B");
    data.replace('/', "%2F");
    data.replace('=', "%3D");
}

void OCRUtils::Url::urlDecode(QString &data)
{
    data.replace("%2B", "+");
    data.replace("%2F", "/");
    data.replace("%3D", "=");
}

void OCRUtils::Url::urlEncode(QByteArray &data)
{
    data.replace('+', "%2B");
    data.replace('/', "%2F");
    data.replace('=', "%3D");
}

void OCRUtils::Url::urlDecode(QByteArray &data)
{
    data.replace("%2B", "+");
    data.replace("%2F", "/");
    data.replace("%3D", "=");
}
