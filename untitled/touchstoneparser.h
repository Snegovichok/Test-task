#ifndef TOUCHSTONEPARSER_H
#define TOUCHSTONEPARSER_H

#include <QString>
#include <QVector>
#include "datapoint.h"

class TouchstoneParser
{
public:
    QVector<DataPoint> parseFile(const QString& fileName);
    double calculateLogMag(double s11_real, double s11_imag);
};

#endif // TOUCHSTONEPARSER_H
