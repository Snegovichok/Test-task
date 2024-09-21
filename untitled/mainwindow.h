#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include "touchstoneparser.h"
#include "graphwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onLoadFile();      // Слот для загрузки файла
    void onClearGraph();    // Слот для очистки графика
    void onTogglePoints();  // Слот для включения/выключения отрисовки точек

private:
    QPushButton *loadButton;   // Кнопка для загрузки файла
    QPushButton *clearButton;  // Кнопка для очистки графика
    QPushButton *togglePointsButton;  // Кнопка для управления точками
    GraphWidget *graphWidget;  // Виджет для отрисовки графика
    TouchstoneParser parser;   // Парсер файлов Touchstone
    QVBoxLayout *layout;       // Layout для размещения элементов
    bool drawPoints;           // Флаг для отслеживания состояния отображения точек
};

#endif // MAINWINDOW_H
