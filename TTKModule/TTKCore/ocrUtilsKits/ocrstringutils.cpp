#include "ocrstringutils.h"

#include <QColor>

QString OCRUtils::String::removeStringBy(const QString &value, const QString &key)
{
    QString s = value;
    s.remove(key);
    if(s.contains(key))
    {
        s = removeStringBy(key);
    }
    return s;
}

QStringList OCRUtils::String::splitString(const QString &value, const QString &key)
{
    QStringList strings = value.split(QString(" %1 ").arg(key));
    if(strings.isEmpty() || strings.count() == 1)
    {
        strings = value.split(key);
    }
    return strings;
}

QStringList OCRUtils::String::illegalCharacters()
{
    QStringList acs;
    acs << "\\" << "/" << "?"  << "*" << "\"" << ":" << "<" << ">" << "|";
    return acs;
}

bool OCRUtils::String::illegalCharactersCheck(const QString &value)
{
    QStringList acs(illegalCharacters());

    for(const QString &ac : qAsConst(acs))
    {
        if(value.contains(ac))
        {
            return true;
        }
    }

    return false;
}

QString OCRUtils::String::illegalCharactersReplaced(const QString &value)
{
    QStringList acs(illegalCharacters());
    QString s(value);

    for(const QString &ac : qAsConst(acs))
    {
        if(s.contains(ac))
        {
            s.replace(ac, " ");
        }
    }

    return s;
}

QList<QColor> OCRUtils::String::readColorConfig(const QString &value)
{
    QList<QColor> colors;
#if TTK_QT_VERSION_CHECK(5,15,0)
    const QStringList &rgbs = value.split(';', Qt::SkipEmptyParts);
#else
    const QStringList &rgbs = value.split(';', QString::SkipEmptyParts);
#endif
    for(const QString &rgb : qAsConst(rgbs))
    {
        const QStringList &var = rgb.split(',');
        if(var.count() != 3)
        {
            continue;
        }
        colors << QColor(var[0].toInt(), var[1].toInt(), var[2].toInt());
    }
    return colors;
}

QString OCRUtils::String::writeColorConfig(const QColor &color)
{
    QString value;
    value.append(QString("%1,%2,%3").arg(color.red()).arg(color.green()).arg(color.blue()));
    return value;
}

QString OCRUtils::String::writeColorConfig(const QList<QColor> &colors)
{
    QString value;
    for(const QColor &rgb : qAsConst(colors))
    {
        value.append(writeColorConfig(rgb) + ";");
    }
    return value;
}
