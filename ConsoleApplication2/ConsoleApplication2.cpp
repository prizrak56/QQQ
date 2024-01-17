﻿#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

class Tower {
public:
    // конструктор и метод SetDisks нужны, чтобы правильно создать башни
    Tower(int disks_num) {
        FillTower(disks_num);
    }

    int GetDisksNum() const {
        return disks_.size();
    }

    void SetDisks(int disks_num) {
        FillTower(disks_num);
    }

    // добавляем диск на верх собственной башни
    // обратите внимание на исключение, которое выбрасывается этим методом
    void AddToTop(int disk) {
        int top_disk_num = disks_.size() - 1;
        if (0 != disks_.size() && disk >= disks_[top_disk_num]) {
            throw invalid_argument("Невозможно поместить большой диск на маленький");
        }
        else {
            // допишите этот метод и используйте его в вашем решении
        }
    }

    // вы можете дописывать необходимые для вашего решения методы

private:
    vector<int> disks_;

    // используем приватный метод FillTower, чтобы избежать дубликации кода
    void FillTower(int disks_num) {
        for (int i = disks_num; i > 0; i--) {
            disks_.push_back(i);
        }
    }
};

void SolveHanoi(vector<Tower>& towers) {
    int disks_num = towers[0].GetDisksNum();

    // допишите функцию, чтобы на towers[0] было 0 дисков,
    // на towers[1] 0 дисков,
    // и на towers[2] было disks_num дисков
}


int main() {
    int towers_num = 3;
    int disks_num = 3;
    vector<Tower> towers;
    // Добавим в вектор три пустые башни.
    for (int i = 0; i < towers_num; ++i) {
        towers.push_back(0);
    }
    // Добавим на первую башню три кольца.
    towers[0].SetDisks(disks_num);

    SolveHanoi(towers);
}



/*  Подсказка

1. Какие параметры принимает функция?
Здесь это самое интересное. Функция SolveHanoi сама по себе рекурсивной не будет. Используйте другую. Вам пригодится это:

 // disks_num - количество перемещаемых дисков
 // destination - конечная башня для перемещения
 // buffer - башня, которую нужно использовать в качестве буфера для дисков
 void MoveDisks(int disks_num, Tower& destination, Tower& buffer) {
     if (// условие выхода ещё не выполнено) {
         // действия из шага рекурсии
     }
 }

 void SolveHanoi(vector<Tower>& towers) {
     int disks_num = towers[0].GetDisksNum();
     // запускаем рекурсию
     // просим переложить все диски на последнюю башню
     // с использованием средней башни как буфера
     towers[0].MoveDisks(disks_num, towers[2], towers[1]);
 }

2. Какие действия должна совершить функция на каждом шаге?
Препарируйте задачу. Порисуйте диски, найдите повторяющийся паттерн. Скорее всего, он будет состоять из нескольких действий.


3. Каково условие завершения? 
Всё просто — как только дисков не осталось, не нужно ничего больше перемещать.

*/