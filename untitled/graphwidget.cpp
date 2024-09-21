#include "graphwidget.h"
#include "datapoint.h"
#include <QPainter>
#include <cmath>

GraphWidget::GraphWidget(QWidget *parent)
    : QWidget(parent), drawPoints(true)  // Инициализируем отрисовку точек в true
{
}

void GraphWidget::setData(const QVector<DataPoint>& dataPoints) {
    data = dataPoints;
    update();  // Перерисовать график
}

void GraphWidget::setDrawPoints(bool enable) {
    drawPoints = enable;
    update();  // Перерисовать график после изменения состояния
}

void GraphWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Отрисовка осей
    painter.drawLine(50, height() - 50, width() - 50, height() - 50); // ось X (частота)
    painter.drawLine(50, height() - 50, 50, 50); // ось Y (S11 в дБ)

    if (data.isEmpty()) return;  // Не рисуем график, если нет данных

    double maxFreq = data.last().frequency;
    double minFreq = data.first().frequency;

    double minY = 1e10;
    double maxY = -1e10;

    QVector<double> logMagData;
    for (const auto& point : data) {
        // Используем функцию для расчета LogMag
        double logMag = calculateLogMag(point.s11_real, point.s11_imag);
        logMagData.append(logMag);
        if (logMag > maxY) maxY = logMag;
        if (logMag < minY) minY = logMag;
    }

    double xScale = (width() - 100) / (maxFreq - minFreq);
    double yScale = (height() - 100) / (maxY - minY);

    // Отрисовка данных: соединенные линии
    painter.setPen(Qt::blue);
    for (int i = 0; i < data.size() - 1; ++i) {
        double x1 = 50 + (data[i].frequency - minFreq) * xScale;
        double y1 = height() - 50 - (logMagData[i] - minY) * yScale;
        double x2 = 50 + (data[i + 1].frequency - minFreq) * xScale;
        double y2 = height() - 50 - (logMagData[i + 1] - minY) * yScale;

        painter.drawLine(QPointF(x1, y1), QPointF(x2, y2));
    }

    // Отрисовка точек, если включено
    if (drawPoints) {
        painter.setPen(Qt::red);
        for (int i = 0; i < data.size(); ++i) {
            double x = 50 + (data[i].frequency - minFreq) * xScale;
            double y = height() - 50 - (logMagData[i] - minY) * yScale;
            painter.drawEllipse(QPointF(x, y), 3, 3);  // маленькие кружки для обозначения точек
        }
    }
}
