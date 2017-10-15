#ifndef MUPDF_PAGE_H
#define MUPDF_PAGE_H

#include <QList>

class QImage;
class QString;
class QPointF;
class QSizeF;
class QRectF;

namespace MuPDF
{
class Page;
class PagePrivate;
class Document;
class TextBox;

/**
 * @brief Map from a transformed point to the original point.
 *
 * @return The original point.
 */
QPointF mapToOrigin(const QPointF &pos, float scaleX, float scaleY, float rotation = 0.0f);
/**
 * @brief Map from a transformed size to the original size.
 *
 * @return The original size.
 */
QSizeF mapToOrigin(const QSizeF &size, float scaleX, float scaleY, float rotation = 0.0f);
/**
 * @brief Map from a transformed rect to the original rect.
 *
 * @return The original rect.
 */
QRectF mapToOrigin(const QRectF &rect, float scaleX, float scaleY, float rotation = 0.0f);
/**
 * @brief Map from a original point to the transformed point.
 *
 * @return The transformed point.
 */
QPointF mapFromOrigin(const QPointF &pos, float scaleX, float scaleY, float rotation = 0.0f);
/**
 * @brief Map from a original size to the transformed size.
 *
 * @return The transformed size.
 */
QSizeF mapFromOrigin(const QSizeF &size, float scaleX, float scaleY, float rotation = 0.0f);
/**
 * @brief Map from a original rect to the transformed rect.
 *
 * @return The transformed rect.
 */
QRectF mapFromOrigin(const QRectF &rect, float scaleX, float scaleY, float rotation = 0.0f);

/**
 * @brief A page.
 *
 * @note When you are doing something with this page, make sure the Document
 * who generate this page is valid.
 */
class Page
{
public:
    ~Page();
    bool isValid() const;
    QImage renderImage(float scaleX = 1.0f, float scaleY = 1.0f, float rotation = 0.0f) const;
    QSizeF size() const;
    void setTransparentRendering(bool enable);
    void setBackgroundColor(int r, int g, int b, int a = 255);
    QString text(const QRectF &rect) const;
    QList<TextBox *> textList() const;

private:
    Page(PagePrivate *pagep)
        : d(pagep)
    {

    }

    PagePrivate *d;

friend class Document;
};

} // end namespace MuPDF

#endif // end MUPDF_PAGE_H
