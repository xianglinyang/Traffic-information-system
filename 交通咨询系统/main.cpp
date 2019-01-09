#include"guidance.h"
using namespace std;
int main() {
	Graph city_system_car,city_system_plane;
	guidance_greeting();
	guidance_create_system(cin,city_system_car,city_system_plane);
	guidance_using();
	cout << endl;
	usage(city_system_car,city_system_plane,cin);
	return 0;
}