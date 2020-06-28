abstract class car {
    private:
    double fuelConsumption;
    string carID;
    string model;
    int year;
    public:
    virtual double getFuelConsumption(int speed) const =0;
};
class Road {
public:
 double length(); // km
 int speed(); // km per hour
};
double getPetrol(std::vector<Road> roads, const Car& car){
double totalFuel=0;
for(std::vector<int>::iterator it = vector.begin(); it!=vector.end();++it){
    totalFuel+=car.getFuelConsumption(*it.speed()) * (*it.length());
}
return totalFuel;
}
