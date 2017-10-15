#ifndef MUPDF_TEXTBOX_P_H
#define MUPDF_TEXTBOX_P_H

extern "C" {
#include <mupdf/fitz.h>
}

namespace MuPDF
{

class TextBoxPrivate
{
public:
    TextBoxPrivate(fz_context *ct, fz_text_span *ts)
        : context(ct), text_span(ts)
    {

    }

    fz_context *context;
    fz_text_span *text_span;
};

} // end namespace MuPDF

#endif // end MUPDF_TEXTBOX_P_H
