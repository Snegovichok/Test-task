#ifndef DATAPOINT_H
#define DATAPOINT_H

#include <cmath>  // Для математических операций

// Структура для хранения частоты и комплексных значений S11
struct DataPoint {
    double frequency;  // Частота
    double s11_real;   // Реальная часть S11
    double s11_imag;   // Мнимая часть S11
};

// Функция для вычисления LogMag
inline double calculateLogMag(double s11_real, double s11_imag) {
    // Вычисление модуля комплексного числа
    double magnitude = std::sqrt(s11_real * s11_real + s11_imag * s11_imag);
    // Преобразование в логарифмическую шкалу (в дБ)
    return 20 * std::log10(magnitude);
}

#endif // DATAPOINT_H
