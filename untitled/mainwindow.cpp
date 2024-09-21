#include "mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), drawPoints(true)  // Инициализируем флаг в true (точки включены)
{
    // Устанавливаем размер окна
    resize(800, 600);

    // Создаем главный виджет и layout
    QWidget *centralWidget = new QWidget(this);
    layout = new QVBoxLayout(centralWidget);
    setCentralWidget(centralWidget);

    // Создаем кнопку для загрузки файла
    loadButton = new QPushButton("Загрузить файл", this);
    layout->addWidget(loadButton);

    // Создаем кнопку для очистки графика
    clearButton = new QPushButton("Очистить график", this);
    layout->addWidget(clearButton);

    // Создаем кнопку для включения/выключения точек
    togglePointsButton = new QPushButton("Выключить точки", this);
    layout->addWidget(togglePointsButton);

    // Создаем графический виджет для отображения графика
    graphWidget = new GraphWidget(this);
    layout->addWidget(graphWidget);

    // Привязываем нажатие кнопки к слотам
    connect(loadButton, &QPushButton::clicked, this, &MainWindow::onLoadFile);
    connect(clearButton, &QPushButton::clicked, this, &MainWindow::onClearGraph);
    connect(togglePointsButton, &QPushButton::clicked, this, &MainWindow::onTogglePoints);
}

MainWindow::~MainWindow() {
}

void MainWindow::onLoadFile() {
    QString fileName = QFileDialog::getOpenFileName(this, "Загрузить Touchstone файл", "", "Touchstone Files (*.s1p *.s2p)");
    if (fileName.isEmpty()) {
        return;
    }

    QVector<DataPoint> data = parser.parseFile(fileName);

    if (data.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Неверный формат файла или ошибка загрузки");
    } else {
        graphWidget->setData(data);  // Передаем данные в график
        graphWidget->setDrawPoints(drawPoints);  // Передаем текущее состояние отображения точек
    }
}

void MainWindow::onClearGraph() {
    graphWidget->setData(QVector<DataPoint>());  // Передаем пустой набор данных
}

void MainWindow::onTogglePoints() {
    drawPoints = !drawPoints;  // Меняем состояние отображения точек
    graphWidget->setDrawPoints(drawPoints);  // Обновляем график

    // Обновляем текст кнопки в зависимости от состояния
    if (drawPoints) {
        togglePointsButton->setText("Выключить точки");
    } else {
        togglePointsButton->setText("Включить точки");
    }
}
