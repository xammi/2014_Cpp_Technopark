#include "NetManagers/NetProcessor.h"
#include <QApplication>

using NetManagers::NetProcessor;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    NetProcessor::get_self();
    return a.exec();
}

/*
 * Надо ли выставлять пустую область работы сети? Амперсанд вполне себе символ. МОжно по нему сравнение в Тестере проводить
 * Зачем в тестере нужен DataSet? Хватит одних Input'ов. Разве что для проверок размеров. Подумать
 * Отстойное сохранение сети
 * Загрузка данных для tester.test в проверке происходит по указателям. Неудобно
 * Нужно делать вывод топологии каждый раз после обучения
 * Вставил кучу вещей для отладки Перенаправление сигнала сделал
 *
 *
 *
 */
