#include <iostream>

#include "worker.h"
#include "hourly-worker.h"

int main()
{
	Worker pesho("Pesho");
	Worker gosho("Gosho", 20);

	pesho.print();
	gosho.print();

	HourlyWorker stamat("Stamat", 30, 40, "Prodava zarzavat");

	stamat.print();

	HourlyWorker dinko = stamat;
	dinko.setWorkType("Dinko e bezdelnik");
	dinko.setHoursWorked(0);

	stamat.print();
	dinko.print();

	dinko = stamat;

	dinko.print();

	return 0;
}
