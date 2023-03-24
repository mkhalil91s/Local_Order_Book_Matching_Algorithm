
#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <vector>
#include <list>
using namespace std;

#ifndef LOB
#define LOB

class Order
{
    int _orderId;
    string _symbole;
    string _side;
    string _price;
    int _volume;

    int _seqNo;
    long _createdTsMsec;

public:
    Order(int orderid, string symbole, string side, string price, int volume);

    const int getOrderId() const;
    const string getSymbole() const;
    const string getSide() const;
    const string getPrice() const;
    const int getVolume() const;
    const int getSequenceNumber() const;
    void incrementSequenceNumber();
    long getCreatedTsMsec() const;
    void setCreatedTsMsec();

    long current_time_msec();

    void setVolume(int volume);
    void setPrice(string price);
    void decreaseVolumeBy(int size);
    void increaseVolumeBy(int size);

    bool operator==(const Order &c);
};

class Lob
{

    void handleSellOrder(std::shared_ptr<Order> sellOrder);
    void handleBuyOrder(std::shared_ptr<Order> buyOrder);
    void DisplaySellOrders();
    void DisplayBuyOrders();
    bool DoesOrderExist(int orderid, string side);
    string DoesOrderExist(int orderid);
    void handleDeleteOrder(int orderid, string side);
    void handleAmendOrderBuy(int orderid, string price, int volume);
    void handleAmendOrderSell(int orderid, string price, int volume);

    struct SellComparator
    {
        bool operator()(const std::shared_ptr<Order> o1, const std::shared_ptr<Order> o2) const;
    };
    struct BuyComparator
    {
        bool operator()(const std::shared_ptr<Order> o1, const std::shared_ptr<Order> o2) const;
    };

    set<std::shared_ptr<Order>, SellComparator> _sellOrders; 
    set<std::shared_ptr<Order>, BuyComparator> _buyOrders;

    unordered_map<int, std::shared_ptr<Order>> _buyOrdersMap; // OrderNo --> Order
    unordered_map<int, std::shared_ptr<Order>> _sellOrdersMap; // OrderNo --> Order


    shared_ptr<std::vector<string> > _tradesRef;


public:
    Lob(shared_ptr<std::vector<string> > tradesRef);
    void AddOrder(int orderid, string symbole, string side, string price, int volume);
    void DeleteOrder(int orderid);
    void AmendOrder(int orderid, string price, int volume);
    void DisplayLob();
    void DeleteEmptyOrderIds();

    string printTade(string symbole, string price, int volume, int aggressiveOrder, int PassiveOrder);


    vector<string> GetBidValues();

    const set<std::shared_ptr<Order>, BuyComparator> &getBuyOrders() const;
    const set<std::shared_ptr<Order>, SellComparator> &getSellOrders() const;

    const unordered_map<int, std::shared_ptr<Order>> &getSellOrdersMap() const;
    const unordered_map<int, std::shared_ptr<Order>> &getBuyOrdersMap() const;
};


class MatchingEngine
{
    unordered_map<string, unique_ptr<Lob>> _matchingEngineLob;  // TESLA --> Lob(TESLA)
    unordered_map<int, string> _orderToSymbolMapHistory; // orderNo --> TESLA
    vector<string> _bids;

    vector<string> parseString(string input);
    shared_ptr<std::vector<string>> _trades;
    

public:
    MatchingEngine();
    void run(vector<string> inputs);
    void calculateBids();
    vector<string> getTrades();

    vector<string> getResults();
};

#endif // LOB