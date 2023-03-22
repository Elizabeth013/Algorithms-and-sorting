#include <iostream>
#include <thread>
#include <time.h>
using namespace std;

// Функция быстрой сортировки
void quickSort(int* numbers, int left, int right)
{
    int pivot; // разрешающий элемент
    int l_hold = left; //левая граница
    int r_hold = right; // правая граница
    pivot = numbers[left];
    while (left < right) // пока границы не сомкнутся
    {
        while ((numbers[right] >= pivot) && (left < right))
            right--; // сдвигаем правую границу пока элемент [right] больше [pivot]
        if (left != right) // если границы не сомкнулись
        {
            numbers[left] = numbers[right]; // перемещаем элемент [right] на место разрешающего
            left++; // сдвигаем левую границу вправо
        }
        while ((numbers[left] <= pivot) && (left < right))
            left++; // сдвигаем левую границу пока элемент [left] меньше [pivot]
        if (left != right) // если границы не сомкнулись
        {
            numbers[right] = numbers[left]; // перемещаем элемент [left] на место [right]
            right--; // сдвигаем правую границу влево
        }
    }
    numbers[left] = pivot; // ставим разрешающий элемент на место
    pivot = left;
    left = l_hold;
    right = r_hold;
    thread th1;
    thread th2;
    // Рекурсивно вызываем сортировку для левой и правой части массива
    if (left < pivot)
    {
        // clock_t EndTime = clock();
        thread th1(quickSort, numbers, left, pivot - 1);
        // cout << this_thread::get_id() << endl;
        th1.join();
        //  cout << "Time of executing threads: " << (double)(clock() - EndTime) / CLOCKS_PER_SEC << endl;

    }
    if (right > pivot)
    {
        thread th2(quickSort, numbers, pivot + 1, right);
        th2.join();
    }
}

int main()
{
    int size;
    cout << "Size:";
    cin >> size;
    int* a;
    a = new int[size];
    // Заполнение массива случайными числами
    cout << "Generated array: ";
    for (int i = 0; i < size; i++)    a[i] = rand() % 201 - 100;
    // Вывод элементов массива до сортировки
    for (int i = 0; i < size; i++) cout << a[i] << " ";
    cout << endl;

    quickSort(a, 0, size - 1); // вызов функции сортировки

    // Вывод элементов массива после сортировки
    cout << "Sorted array: ";
    for (int i = 0; i < size; i++) cout << a[i] << " ";
    cout << endl;
    return 0;
}