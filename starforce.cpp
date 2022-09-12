
#include <iostream>
#include <cstdlib>
#include <random>
#include <math.h>
#include <string>
#include <cstring>
int success{0};
int fail{0};
int destroy{0};
int roll{0};
int temp{ 0 };

//psuedo random number gen
int ran1000() {
	//i found this on the internet
	//i was going to use srand but for some reason it didnt seem random? numbers kept increasing in weird patterns
	std::random_device rd; 
	std::mt19937 gen(rd()); 
	std::uniform_int_distribution<> distr(0, 1000); 
	return distr(gen);
}

//gives result of one tap
int result(int stars) {
	//2 -> 3 and 3 -> 4 have same success rate
	if (stars == 3) {
		stars == 2;
	}
	//success will be if the roll is less than the success
	success = 1000 - stars * 50;
	//success rate doesnt change after 14 -> 15 until 22 ->23
	if (stars > 14 && stars < 22) {
		success = 300;
	}
	//if greater than 22 it has weird behaviour
	else {
		switch (stars) {
		case 22:
			success = 30;
			break;
		case 23:
			success = 20;
			break;
		case 24:
			success = 10;
			break;
		}
	}
	//destroy will be if the roll is greater than 1000 - destroy;
	switch (stars) {
	case 12:
		destroy = 6;
		break;
	case 13:
		destroy = 13;
		break;
	case 14:
		destroy = 14;
		break;
	case 15:
	case 16:
	case 17:
		destroy = 21;
		break;
	case 18:
	case 19:
		destroy = 28;
		break;
	case 20:
	case 21:
		destroy = 70;
		break;
	case 22:
		destroy = 194;
		break;
	case 23:
		destroy = 294;
		break;
	case 24:
		destroy = 396;
		break;
	}
	//so for eg if stars = 21, the item will pass if roll is between 0 and 300, destroy if between 930 and 100, and fail between 301 and 929
	roll = ran1000();
	//destroy
	if (roll > (1000 - destroy)) {
		return 3;
	}
	//success
	else if (roll < success) {
		return 1;
	}
	//fail
	else {
		return 2;
	}

}

//for now ill just do 150 items(cra)
long long cost(int stars) {
	if (stars < 10) {
		temp = (pow(150, 3) * (stars + 1) / 2500 + 10);
	}
	else if (stars >= 10 && stars <= 14) {
		temp = (pow(150, 3) * pow(stars + 1, 2.7) / 40000 + 10);
	}
	else if (stars >= 15 && stars <= 17) {
		temp = (pow(150, 3) * pow(stars + 1, 2.7) / 12000 + 7.8);
		temp = 0.78 * temp;
	}
	else if (stars >= 18 && stars <= 19) {
		temp = (pow(150, 3) * pow(stars + 1, 2.7) / 11000 + 7.8);
		temp = 0.78 * temp;
	}
	else {
		temp = (pow(150, 3) * pow(stars + 1, 2.7) / 10000 + 7.8);
		temp = 0.78 * temp;
	}
	return 100 * temp;

}

std::string makeCute(std::string cost) {
	std::string newCost{};
	int length = cost.length();
	int returnLength = ((length - 1) / 3 + length);
	switch (length % 3) {
	case 0:
		for (int i = 0; i < length; i++) {
			if ((i) % 3 == 0 && i != 0) {
				newCost.push_back(',');
			}
			newCost.push_back(cost[i]);
		}
		break;
	case 1:
		for (int i = 0; i < length; i++) {
			if ((i + 2) % 3 == 0 && i != 0) {
				newCost.push_back(',');
			}
			newCost.push_back(cost[i]);
		}
		break;
	case 2:
		for (int i = 0; i < length; i++) {
			if ((i + 1) % 3 == 0 && i != 0) {
				newCost.push_back(',');
			}
			newCost.push_back(cost[i]);
		}
	}
	return newCost;
}


int main()
{
	int start{0};
	int desired{0};
	int tapresult{0};
	int count{ 0 };
	long long mesoTotal{ 0 };
	double trials{ 0.0 };
	long long mesoAverage{ 0 };
	double split{ 0.0 };
	int tempStart{ 0 };
	double avgBooms{ 0.0 };
	double booms{ 0.0 };
	std::cout << "Enter starting stars: ";
	std::cin >> start;
	start = tempStart;
	std::cout << "\n" << "Enter desired stars: ";
	std::cin >> desired;
	std::cout << "\n" << "Enter number of trials: ";
	std::cin >> trials;
	split = 1 / trials;
	for (int i = 0; i < trials; i++) {
		mesoTotal = 0;
		start = tempStart;
		while (start != desired) {
			tapresult = result(start);
			count++;
			mesoTotal += cost(start);
			if (tapresult == 3) {
				booms++;
				std::wcout << booms << "\n";
				break;
			}
			else if (tapresult == 1) {
				start++;
				//std::cout << "success, stars at " << start << "\n";
			}
			else if (tapresult == 2) {
				if (start > 10 && start != 15 && start != 20) {
					start--;
				}
				//std::cout << "failed, stars at " << start << "\n";
				//10,791,789
			}
			std::cout << mesoTotal << "\n";
		}
		mesoAverage += mesoTotal * split; 
	}
	avgBooms = booms / trials;
	std::string mesoTotalString = makeCute(std::to_string(mesoAverage));
	std::cout << "avg meso cost: " << mesoTotalString << "\n";
	std::wcout << "avg booms: " << avgBooms << "\n";
	
	
}
