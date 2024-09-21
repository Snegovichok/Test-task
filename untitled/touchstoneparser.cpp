#include "touchstoneparser.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <cmath>

QVector<DataPoint> TouchstoneParser::parseFile(const QString& fileName) {
    QVector<DataPoint> data;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(nullptr, "Ошибка", "Не удалось открыть файл");
        return data;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.startsWith('#') || line.startsWith('!')) {
            continue; // Пропускаем заголовок и комментарии
        }

        QStringList elements = line.split(" ", Qt::SkipEmptyParts);
        if (elements.size() != 3) {
            QMessageBox::critical(nullptr, "Ошибка", "Некорректный формат данных");
            return QVector<DataPoint>();
        }

        bool ok1, ok2, ok3;
        double frequency = elements[0].toDouble(&ok1);
        double s11_real = elements[1].toDouble(&ok2);
        double s11_imag = elements[2].toDouble(&ok3);

        if (!ok1 || !ok2 || !ok3) {
            QMessageBox::critical(nullptr, "Ошибка", "Некорректные значения в файле");
            return QVector<DataPoint>();
        }

        data.append({frequency, s11_real, s11_imag});
    }

    file.close();
    return data;
}

double TouchstoneParser::calculateLogMag(double s11_real, double s11_imag) {
    double magnitude = std::sqrt(s11_real * s11_real + s11_imag * s11_imag);
    return 20 * std::log10(magnitude);
}
