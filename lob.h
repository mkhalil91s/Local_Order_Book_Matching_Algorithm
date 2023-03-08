
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

#ifndef LOB
#define LOB

class Lob
{
    int _side; // For simplicityV :  0 for buy , 1 for sell
    double _price;
    int _volume;

public:
    Lob(int side, double price, int volume);
    const int getSide() const;
    const double getPrice() const;
    const int getVolume() const;

    void setVolume(int volume);
    void decreaseVolumeBy(int size);

    bool operator==(const Lob &c);
};

class Order
{
    vector<Lob> _buyOrders;
    vector<Lob> _sellOrders;

    void printTade(int volume, double price);
    void eraseEmptyVolumeOrders();
    void handleSellOrder(Lob sellOrder);
    void handleBuyOrder(Lob order);

public:
    void AddOrder(Lob order);
    void DisplaySellOrders();
    void DisplayBuyOrders();
    void DisplayLob();

    // For testing purposes

    vector<Lob> getBuyOrders();
    vector<Lob> getSellOrders();
};

#endif // LOB