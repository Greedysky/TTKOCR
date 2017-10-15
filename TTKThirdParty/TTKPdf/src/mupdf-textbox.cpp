#include "mupdf-textbox.h"
#include "mupdf-textbox_p.h"
#include <QRectF>
#include <QPointF>
#include <QString>

namespace MuPDF
{

TextBox::~TextBox()
{
    delete d;
}

/**
 * @brief Bounding box.
 */
QRectF TextBox::boundingBox() const
{
//	fz_rect all = fz_empty_rect, rect;
//
//	for (int i = 0; i < d->text_span->len; ++i) {
//		fz_text_char_bbox(&rect, d->text_span, i);
//		fz_union_rect(&all, &rect);
//	}

	return QRectF(QPointF(d->text_span->bbox.x0, d->text_span->bbox.y0),
                  QPointF(d->text_span->bbox.x1, d->text_span->bbox.y1));
}

/**
 * @brief Number of unicode chars.
 */
int TextBox::numChars() const
{
	return d->text_span->len;
}

/**
 * @brief Get bounding box of a unicode char.
 *
 * @param index index of the unicode char(start from 0)
 */
QRectF TextBox::charBoundingBox(int index) const
{
	fz_rect rect;

    fz_text_char_bbox(d->context, &rect, d->text_span, index);

	return QRectF(QPointF(rect.x0, rect.y0), QPointF(rect.x1, rect.y1));
}

/**
 * @brief Text string.
 */
QString TextBox::text() const
{
    QString ret;
    fz_text_char *ch;
    fz_text_char *end = d->text_span->text + d->text_span->len;

    for (ch = d->text_span->text; ch < end; ++ch) {
        ret.append(QChar(ch->c));
    }

    return ret;
}

} // end namespace MuPDF
