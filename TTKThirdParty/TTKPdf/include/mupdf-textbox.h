#ifndef MUPDF_TEXTBOX_H
#define MUPDF_TEXTBOX_H

class QRectF;
class QString;

namespace MuPDF
{

class TextBoxPrivate;

/**
 * @brief A text box.
 *
 * A text box contains a list of characters that share a common
 * baseline/transformation. In typical cases a single text box may be enough
 * to represent a complete line. In cases where the text has big gaps in
 * it (perhaps as it crosses columns or tables), a line may be represented
 * by multiple text boxes.
 */
class TextBox
{
public:
    ~TextBox();

    QRectF boundingBox() const;
    int numChars() const;
    QRectF charBoundingBox(int index) const;
//    bool hasSpaceAfter() const;
//    TextBox *nextWord() const;
    QString text() const;

private:
    TextBox(TextBoxPrivate *textboxp)
        : d(textboxp)
    {

    }

    TextBoxPrivate *d;

friend class Page;
};

} // end namespace Mu

#endif // end MUPDF_TEXTBOX_H
