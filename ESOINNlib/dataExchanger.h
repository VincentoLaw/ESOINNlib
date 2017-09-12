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
#include <string>
#include "ESOINNLibSources/esoinn.h"
#include "ESOINNLibSources/simpleam.h"
//![0]

typedef QUrl imgType;

class dataExchanger : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString structureData READ structureData WRITE setStructureData)
    Q_PROPERTY(QList<QString> esoinnParams READ esoinnParams WRITE setEsoinnParams)

    Q_PROPERTY(QUrl im READ im WRITE sim)
    Q_PROPERTY(QUrl pointedImage READ pointedImage WRITE setPointedImage)

    Q_PROPERTY(QUrl loadStructure READ loadStructure WRITE setLoadStructure)
    Q_PROPERTY(QUrl saveStructure READ saveStructure WRITE setSaveStructure)

    Q_PROPERTY(QUrl loadVector READ loadVector WRITE setLoadVector)

    Q_PROPERTY(int dimensionsCnt READ dimensionsCnt WRITE setDimensionsCnt)

    Q_PROPERTY(QString currentNNparams READ currentNNparams WRITE setCurrentNNparams)

    Q_PROPERTY(QString saveMainVectors READ saveMainVectors WRITE setSaveMainVectors)
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

    QUrl loadStructure() const;
    void setLoadStructure(const QUrl &);

    QUrl saveStructure() const;
    void setSaveStructure(const QUrl &);

    QUrl loadVector() const;
    void setLoadVector(const QUrl &);

    int dimensionsCnt() const;
    void setDimensionsCnt(const int &);
    //При реализации проекта по созданию портала используются средства государственной поддержки, выделенные в качестве гранта в соответствии с распоряжением Президента Российской Федерации от 17.01.2014 № 11-рп и на основании конкурса, проведенного Фондом ИСЭПИ.
    QString currentNNparams() const;
    void setCurrentNNparams(const QString &);

    QString saveMainVectors() const;
    void setSaveMainVectors(const QString &);


    //local data
    Esoinn * es;
    QImage * image;
    double ** vectors;
    double ** normalizedVectors;
    int dimSize;
    int vectorsCnt;

    //SimpleAM am;

private:
    QString m_structureData;
    QList<QString> m_esoinnParams;
    imgType m_im;
    string m_loadStructure;
    int m_dimensionsCnt;

    QString m_currentNNparams;
};
//![0]

#endif // PERSON_H
