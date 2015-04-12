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
#include "dataExchanger.h"
#include <QtDebug>
#include <QTime>
#include <fstream>
//#include <random>

// ![0]
dataExchanger::dataExchanger(QObject *parent): QObject(parent)
{
    es = NULL;
    vectors = NULL;
    normalizedVectors = NULL;
}

QString dataExchanger::structureData() const
{
    return m_structureData;
}

void dataExchanger::setStructureData(const QString &n)
{
    m_structureData = n;
}

int dataExchanger::dimensionsCnt() const{
    return m_dimensionsCnt;

}
void dataExchanger::setDimensionsCnt(const int &number){
    m_dimensionsCnt = number;
}

QList<QString> dataExchanger::esoinnParams() const
{
    return m_esoinnParams;
}

imgType dataExchanger::im() const
{
    return m_im;
}

QString dataExchanger::currentNNparams() const
{
    return m_currentNNparams;
}

QString dataExchanger::saveMainVectors() const{
    return "";
}

void dataExchanger::setSaveMainVectors(const QString & str){
    double ** vects = es->getTopVectors(100);
    for (int i = 0; i < 100; i++){
        uchar * arr = new uchar[28*28*4];
        if (vects[i][0] != -1){
            for (int j = 0; j < 28*28*4; j+=4){
                arr[j + 3] = 255;
                arr[j + 2] = arr[j + 1] = arr[j] = vects[i][j/4];
            }
            QImage * qim = new QImage(arr,28,28,QImage::Format_ARGB32);
            qim->save("image" + QString::number(i) + ".png");
        }
    }
}

void dataExchanger::setCurrentNNparams(const QString &str){
    m_currentNNparams = str;
}

void dataExchanger::sim(const imgType &n)
{

    m_im = n;
    if (!image)
        delete image;
    image = new QImage(n.toLocalFile());

    double ** shuf_arr = new double*[image->width() * image->height()];
    int points_cnt = 0;
    for (int i = 0; i < image->height(); i++){
        for (int j = 0; j < image->width(); j++){
            QColor qc(image->pixel(j,i));
            if (qc.red() < 100 || qc.green() < 100 || qc.blue() < 100){
                shuf_arr[points_cnt] = new double[2];
                shuf_arr[points_cnt][0] = j;
                shuf_arr[points_cnt][1] = i;
                points_cnt++;
            }
        }
    }
    if (normalizedVectors){
        for (int i = 0; i < vectorsCnt; i++)
            delete[] normalizedVectors[i];
        delete[] normalizedVectors;
    }
    if (vectors){
        for (int i = 0; i < vectorsCnt; i++)
            delete[] vectors[i];
        delete[] vectors;
    }
    vectors = new double*[points_cnt];
    vectorsCnt = points_cnt;
    dimSize = 2;
    for (int i = 0; i < points_cnt; i++){
        vectors[i] = new double[2];
        vectors[i][0] = shuf_arr[i][0];
        vectors[i][1] = shuf_arr[i][1];
        delete[] shuf_arr[i];
    }
    delete[] shuf_arr;
    m_dimensionsCnt = dimSize;
}

QUrl dataExchanger::pointedImage() const
{
    return m_im;
}

void dataExchanger::setPointedImage(const QUrl &n)
{
    m_im = n;
    delete image;
    image = new QImage(n.toLocalFile());
    QString strs = "";
    for (int i = 0; i < image->height(); i++){
        for (int j = 0; j < image->width(); j++){
            QColor qc(image->pixel(j,i));
            if (qc.red() < 100 || qc.green() < 100 || qc.blue() < 100){
                strs += QString::number(j);
                strs += " ";
                strs += QString::number(i);
                strs += ",";
            }
        }
    }
    setStructureData(strs);
}

void dataExchanger::setLoadStructure(const QUrl &filePath){
    auto fileName = filePath.toLocalFile().toStdString();
    if (es == NULL){
        es = new Esoinn(fileName);
    }
    else {
        es->~Esoinn();
        es = new Esoinn(fileName);
    }
    QString qs = "";
    double ** str = es->getStructure();
    m_dimensionsCnt = str[0][1];
    for (int ii = 1; ii < str[0][0] + 1; ii++){
        for (int jj = 0; jj < str[0][0] + 4; jj++){
            if (jj > 1 && str[ii][jj] == -1)
                break;
            qs += QString::number(str[ii][jj]);
            qs += " " ;

        }
        qs += "/";
    }
    int n = str[0][0] + 1;
    for(int i = 0; i < n; ++i) delete[] str[i];
    delete[] str;
    qs += ";";
    setStructureData(qs);
}

QUrl dataExchanger::loadStructure() const{
    return m_im;
}

QUrl dataExchanger::saveStructure() const{
    return m_im;
}
void dataExchanger::setSaveStructure(const QUrl &filePath){
    auto fileName = filePath.toLocalFile().toStdString();
    es->saveStateToFile(fileName);
}

QUrl dataExchanger::loadVector() const{
    return m_im;
}
void dataExchanger::setLoadVector(const QUrl &filePath){
    auto fileName = filePath.toLocalFile().toStdString();
    //во-первых надо передать параметры как-то в инициализатор. во-вторых надо дописать кол-во итераций

    if (normalizedVectors){
        for (int i = 0; i < vectorsCnt; i++)
            delete[] normalizedVectors[i];
        delete[] normalizedVectors;
    }
    if (vectors){
        for (int i = 0; i < vectorsCnt; i++)
            delete[] vectors[i];
        delete[] vectors;
    }
    list<double> oneVect;
    ifstream in(fileName.c_str());
    char c; double num; in >> c;
    while (c != ')'){
        in >> num >> c;
        oneVect.push_back(num);
    }
    dimSize = oneVect.size();
    list<double *> vects;
    double * d = new double[dimSize];
    int i = 0;
    for (auto &it: oneVect)
        d[i++] = it;
    vects.push_back(d);
    while (in >> c){
        d = new double[dimSize];
        for (int i = 0; i < dimSize; i++)
            in >> d[i] >> c;
        vects.push_back(d);
    }
    vectorsCnt = vects.size();
    vectors = new double*[vectorsCnt];
    i = 0;
    for (auto &it: vects){
        vectors[i++] = it;
    }


    /*for (int i = 0; i < 10; i++){

    uchar * arr = new uchar[28*28*4];
    for (int j = 0; j < 28*28*4; j+=4){
        arr[j] = 255;
        arr[j + 2] = arr[j + 1] = arr[j + 3] = vectors[i][j/4];
    }
    QImage * qim = new QImage(arr,28,28,QImage::Format_ARGB32);
    qim->save("/home/vincento/Desktop/image0" + QString::number(i) +".png");
    }*/

    m_dimensionsCnt = dimSize;
}

void dataExchanger::setEsoinnParams(const QList<QString> &n){
    m_esoinnParams = n;
    QString qs;
    qsrand(0);
    bool randomizeDataOrder = m_esoinnParams[1] == "true" ? true : false;
    bool visualizeEveryStep = m_esoinnParams[2] == "true" ? true : false;
    bool normalizeInput = m_esoinnParams[5] == "true" ? true : false;
    if (m_esoinnParams[3].toDouble() == 1 || es == NULL)
        es = new Esoinn(m_dimensionsCnt, m_esoinnParams[6].toDouble(), m_esoinnParams[7].toDouble(), m_esoinnParams[8].toDouble(), m_esoinnParams[9].toDouble());

    double ** cur_vectors = vectors;
    if (normalizeInput){
        if (!normalizedVectors){
            double * max_vals = new double[dimSize];
            double * min_vals = new double[dimSize];
            for (int j = 0; j < dimSize; j++){
                max_vals[j] = vectors[0][j];
                min_vals[j] = vectors[0][j];
            }
            for (int i = 0; i < vectorsCnt; i++)
                for (int j = 0; j < dimSize; j++){
                    if (vectors[i][j] > max_vals[j])
                        max_vals[j] = vectors[i][j];
                    if (vectors[i][j] < min_vals[j])
                        min_vals[j] = vectors[i][j];
                }
            double * norma = new double[dimSize];
            double max = max_vals[0] - min_vals[0];
            for (int j = 0; j < dimSize; j++){
                norma[j] = max_vals[j] - min_vals[j];
                if (max < norma[j])
                    max = norma[j];
            }
            for (int j = 0; j < dimSize; j++)
                norma[j] = max / norma[j];
            normalizedVectors = new double * [vectorsCnt];
            for (int i = 0; i < vectorsCnt; i++){
                normalizedVectors[i] = new double[dimSize];
                for (int j = 0; j < dimSize; j++)
                    normalizedVectors[i][j] = (vectors[i][j] - min_vals[j]) * norma[j];
            }
        }
        cur_vectors = normalizedVectors;
    }

    //double values are situated in vectors array!
    double ** shuf_arr = new double*[vectorsCnt];
    for (int i = 0; i < vectorsCnt; i++)
        shuf_arr[i] = cur_vectors[i];
    for (int iter = 0; iter < m_esoinnParams[4].toDouble(); iter++)
    {
        if (randomizeDataOrder){
            for (int i = 0; i < vectorsCnt; i++){
                double * temp = shuf_arr[i];
                int swap_cell = qrand() % vectorsCnt;
                shuf_arr[i] = shuf_arr[swap_cell];
                shuf_arr[swap_cell] = temp;
            }
        }

        es->clearWinners();
        for (int i = 0; i < vectorsCnt; i++){
            double * w = new double[dimSize];
            for (int j = 0; j < dimSize; j++)
                w[j] = shuf_arr[i][j];
            es->inputSignal(w);
            delete[] w;
            if (visualizeEveryStep || (i == vectorsCnt - 1)){
                double ** str = es->getStructure();
                for (int ii = 1; ii < str[0][0] + 1; ii++){
                    for (int jj = 0; jj < str[0][0] + 4; jj++){
                        //qDebug() << str[i] << " ";
                        if (jj > 1 && str[ii][jj] == -1)
                            break;
                        qs += QString::number(str[ii][jj]);
                        qs += " " ;
                    }
                    qs += "/";
                }
                int n = str[0][0] + 1;
                for(int i = 0; i < n; ++i) delete[] str[i];
                delete[] str;
                qs += ";";
            }
        }
    }
    m_dimensionsCnt = dimSize;
    setCurrentNNparams(QString::fromStdString(es->getCurrentParams()));

    //generating random data for esoinn
    /*QTime time = QTime::currentTime();
    std::default_random_engine generator;
    generator.seed((uint)time.msec());
    std::uniform_int_distribution<int> distribution(0,150);*/
    /*for (int j = 0; j < 4; j++)
        for (int i = 0; i < 500; i++){
            double * w = new double[2];
            w[0] = distribution(generator) + (j < 2 ? 30 : -180);
            w[1] = distribution(generator) + (j % 2 == 1 ? 30 : -180);
            es->inputSignal(w);
        }*/


    //getting esoinn structure from double array
    delete[] shuf_arr;
    //Loading data to class. This data now will be available in QML
    setStructureData(qs);

}
