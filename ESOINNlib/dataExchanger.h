/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/
#ifndef PERSON_H
#define PERSON_H

#include <QObject>
#include <QQuickImageProvider>
#include <QImage>
#include "ESOINNLibSources/esoinn.h"
//![0] 

typedef QUrl imgType;

class dataExchanger : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString structureData READ structureData WRITE setStructureData)
    Q_PROPERTY(QList<QString> esoinnParams READ esoinnParams WRITE setEsoinnParams)

    Q_PROPERTY(QUrl im READ im WRITE sim)
    Q_PROPERTY(QUrl pointedImage READ pointedImage WRITE setPointedImage)
public:
    dataExchanger(QObject *parent = 0);
    //shared data
    QString structureData() const;
    void setStructureData(const QString &);

    QList<QString> esoinnParams() const;
    void setEsoinnParams(const QList<QString> &);

    imgType im() const;
    void sim(const imgType &);

    QUrl pointedImage() const;
    void setPointedImage(const QUrl &);

    //local data
    Esoinn * es;
    QImage * image;

private:
    QString m_structureData;
    QList<QString> m_esoinnParams;
    imgType m_im;
};
//![0]

#endif // PERSON_H
