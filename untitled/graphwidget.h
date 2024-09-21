#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>
#include <QVector>
#include "datapoint.h"

class GraphWidget : public QWidget
{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = nullptr);
    void setData(const QVector<DataPoint>& dataPoints);  // Метод для задания данных
    void setDrawPoints(bool enable);  // Метод для включения/выключения точек

protected:
    void paintEvent(QPaintEvent *event) override;  // Отрисовка графика

private:
    QVector<DataPoint> data;  // Хранение данных для графика
    bool drawPoints;  // Флаг для включения/выключения отрисовки точек
};

#endif // GRAPHWIDGET_H
