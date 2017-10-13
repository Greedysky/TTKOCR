#ifndef OCRPRIVATE_H
#define OCRPRIVATE_H

/* =================================================
 * This file is part of the TTK OCR project
 * Copyright (C) 2015 - 2017 Greedysky Studio

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; If not, see <http://www.gnu.org/licenses/>.
 ================================================= */


#define OCR_DECLARE_PRIVATE(Class) \
    friend class Class##Private; \
    OCRPrivateInterface<Class, Class##Private> ocr_d;

#define OCR_DECLARE_PUBLIC(Class) \
    friend class Class;

#define OCR_INIT_PRIVATE \
    ocr_d.setPublic(this);

#define OCR_D(Class) Class##Private *const d = ocr_d()
#define OCR_Q(Class) Class *const q = ocr_q()

template <typename PUB>
/*! @brief The class of the private base.
 * @author Greedysky <greedysky@163.com>
 */
class OCRPrivate
{
public:
    virtual ~OCRPrivate() { }
    inline void setPublic(PUB* pub) { ocr_q_ptr = pub; }

protected:
    inline PUB *ocr_q() const { return ocr_q_ptr; }

private:
    PUB* ocr_q_ptr;

};

template <typename PUB, typename PVT>
/*! @brief The class of the ttk private interface.
 * @author Greedysky <greedysky@163.com>
 */
class OCRPrivateInterface
{
    friend class OCRPrivate<PUB>;
public:
    OCRPrivateInterface() { pvt = new PVT; }
    ~OCRPrivateInterface() { delete pvt; }

    inline void setPublic(PUB* pub) { pvt->setPublic(pub); }
    inline PVT *operator()() const { return static_cast<PVT*>(pvt); }

private:
    OCRPrivateInterface(const OCRPrivateInterface&) { }
    OCRPrivateInterface& operator=(const OCRPrivateInterface&) { }
    OCRPrivate<PUB>* pvt;

};


#endif // OCRPRIVATE_H
