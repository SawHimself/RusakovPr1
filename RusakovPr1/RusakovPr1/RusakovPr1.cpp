#include <iostream>
#include "AdapterQueue.h"
using namespace std;

Adapter4queueStl merge(Adapter4queueStl m1, Adapter4queueStl m2, int len_1, int len_2) {
	Adapter4queueStl ret;
	int n = 0; // Сливаем массивы, пока один не закончится
	int i1 = 0;
	int i2 = 0;
	while (len_1 && len_2) {
		if (m1.getElement(i1) < m2.getElement(i2)) {
			//ret[n] = *m1;
			ret.setElement(n, m1.getElement(i1));
			i1++;
			--len_1;
		}
		else {
			//ret[n] = *m2;
			ret.setElement(n, m2.getElement(i2));
			++i2;
			--len_2;
		}
		++n;
	} // Если закончился первый массив
	if (len_1 == 0) {
		for (int i = 0; i < len_2; ++i) {
			//ret[n++] = *m2++;
			ret.setElement(n++, m2.getElement(i2++));
		}
	}
	else { // Если закончился второй массив
		for (int i = 0; i < len_1; ++i) {
			//ret[n++] = *m1++;
			ret.setElement(n++, m1.getElement(i1++));
		}
	}
	return ret;
}

void mergeSort(Adapter4queueStl mas, int len) {
	int n = 1, k, ost; Adapter4queueStl mas1; while (n < len) {
		k = 0;
		while (k < len) {
			if (k + n >= len) break;
			ost = (k + n * 2 > len) ? (len - (k + n)) : n;
			
			Adapter4queueStl Queue1; Adapter4queueStl Queue2;

			for (int i = k; i < mas.size(); i++)
			{
				Queue1.push(mas.getElement(i));
			}
			for (int i = k + n; i < mas.size(); i++)
			{
				Queue2.push(mas.getElement(i));
			}
			
			//mas1 = merge(mas + k, mas + k + n, n, ost);
			mas1 = merge(Queue1, Queue2, n, ost);
			for (int i = 0; i < n + ost; ++i)
				//mas[k + i] = mas1[i];
				mas.setElement(k + i, mas1.getElement(i));
			//delete[] mas1;
			k += n * 2;
		}
		n *= 2;
	}
}
int main() {
	const int SIZE = 10;
	Adapter4queueStl QueueMain;
	setlocale(LC_ALL, "");
	// Заполняем элементы массива
	for (int i = 0; i < SIZE; i++) 
	{
		QueueMain.push(rand() % 100);
	}

	cout << "Изначальные элементы" << endl;
	QueueMain.display();
	cout << endl << "Теперь сортировка" << endl;
	mergeSort(QueueMain, SIZE);
	QueueMain.display();
	return 0;
}