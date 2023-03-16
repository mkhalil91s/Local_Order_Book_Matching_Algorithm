
#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <vector>
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
    /**
     * seqNo specifies the sequential order of LobOrder object being added into LOB
     */
    int _seqNo{0};

public:
    Order(int orderid, string symbole, string side, string price, int volume);

    const int getOrderId() const;
    const string getSymbole() const;
    const string getSide() const;
    const string getPrice() const;
    const int getVolume() const;
    const int getSequenceNumber() const;
    void incrementSequenceNumber();

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

    map<int, std::shared_ptr<Order>> _buyOrdersMap;
    map<int, std::shared_ptr<Order>> _sellOrdersMap;

    static vector<string> trades;

public:
    void AddOrder(int orderid, string symbole, string side, string price, int volume);
    void DeleteOrder(int orderid);
    void AmendOrder(int orderid, string price, int volume);
    void DisplayLob();
    void DeleteEmptyOrderIds();
    void DisplayBidValues();


    static void printTade(string symbole, string price, int volume, int aggressiveOrder, int PassiveOrder);
    static void printTrades();

    const set<std::shared_ptr<Order>, BuyComparator> &getBuyOrders() const;
    const set<std::shared_ptr<Order>, SellComparator> &getSellOrders() const;

    const map<int, std::shared_ptr<Order>> &getSellOrdersMap() const;
    const map<int, std::shared_ptr<Order>> &getBuyOrdersMap() const;
};

class MatchingEngine
{
    map<string, unique_ptr<Lob>> _matchingEngineLob;
    map<int, string> _orderToSymbolMapHistory;

public:

    void run(vector<string> inputs);
    vector<string> parseString(string input);
};
#endif // LOB