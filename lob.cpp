#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <vector>
#include <chrono>
#include <sstream>
#include <memory>
#include "lob.h"
using namespace std;

Order::Order(int orderid, string symbole, string side, string price, int volume)
{
    if (side != "BUY" && side != "SELL")
        throw("Unknown order type");
    _orderId = orderid;
    _symbole = symbole;

    auto index = price.find(".");

    if (index == string::npos)
    {
        _price = price;
    }
    else if (index + 5 >= price.size())
    {
        _price = price;
    }
    else
    {
        price.erase(index + 5, price.size() - 1);
        _price = price;
    }
    _side = side;
    _price = price;
    _volume = volume;
    _seqNo = 1;
    _createdTsMsec = current_time_msec();
}

long Order::current_time_msec()
{
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

long Order::getCreatedTsMsec() const
{
    return _createdTsMsec;
}

void Order::setCreatedTsMsec()
{
    _createdTsMsec = current_time_msec();
}
bool Order::operator==(const Order &c)
{
    if (_orderId == c.getOrderId())
        return true;
    return false;
}

const int Order::getSequenceNumber() const
{
    return _seqNo;
}
void Order::incrementSequenceNumber()
{
    _seqNo++;
}

const int Order::getOrderId() const
{
    return _orderId;
}
const string Order::getSymbole() const
{
    return _symbole;
}

const string Order::getSide() const
{
    return _side;
}

const string Order::getPrice() const
{
    return _price;
}

const int Order::getVolume() const
{
    return _volume;
}

void Order::setVolume(int volume)
{
    _volume = volume;
}
void Order::setPrice(string price)
{
    _price = price;
}

void Order::decreaseVolumeBy(int size)
{
    if (size > _volume)
        throw("Size is greater than volume");

    _volume = _volume - size;
}

void Order::increaseVolumeBy(int size)
{
    _volume = _volume + size;
}

bool Lob::BuyComparator::operator()(const std::shared_ptr<Order> o1,
                                    const std::shared_ptr<Order> o2) const
{

    if (stof(o1->getPrice()) > stof(o2->getPrice()))
    {
        return true;
    }
    else if (stof(o1->getPrice()) == stof(o2->getPrice()))
    {
        if ((o1->getSequenceNumber() < o2->getSequenceNumber()))
        {
            return true;
        }
        else if ((o1->getSequenceNumber() == o2->getSequenceNumber()))
        {

            if (o1->getCreatedTsMsec() < o2->getCreatedTsMsec())
            {
                return true;
            }
            else if (o1->getCreatedTsMsec() == o2->getCreatedTsMsec())
            {
                if (o1->getOrderId() < o2->getOrderId())
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool Lob::SellComparator::operator()(const std::shared_ptr<Order> o1,
                                     const std::shared_ptr<Order> o2) const
{

    if (stof(o1->getPrice()) < stof(o2->getPrice()))
    {
        return true;
    }
    else if (stof(o1->getPrice()) == stof(o2->getPrice()))
    {
        if ((o1->getSequenceNumber() < o2->getSequenceNumber()))
        {
            return true;
        }
        else if ((o1->getSequenceNumber() == o2->getSequenceNumber()))
        {

            if (o1->getCreatedTsMsec() < o2->getCreatedTsMsec())
            {
                return true;
            }
            else if (o1->getCreatedTsMsec() == o2->getCreatedTsMsec())
            {
                if (o1->getOrderId() < o2->getOrderId())
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

void Lob::DisplaySellOrders()
{

    cout << "####### Sell #######" << endl;
    for (auto element : _sellOrders)
    {
        cout << element->getOrderId() << "  " << element->getSymbole() << "  " << element->getSide() << "  " << element->getPrice() << "  " << element->getVolume()
             << "  " << element->getCreatedTsMsec() << "  " << element->getSequenceNumber() << endl;
    }
    cout << "##########################" << endl;
}

void Lob::DisplayBuyOrders()
{
    cout << "####### Buy Orders #######" << endl;
    for (auto element : _buyOrders)
    {
        cout << element->getOrderId() << "  " << element->getSymbole() << "  " << element->getSide() << "  " << element->getPrice() << "  " << element->getVolume()
             << "  " << element->getCreatedTsMsec() << "  " << element->getSequenceNumber() << endl;
    }
    cout << "##########################" << endl;
}

bool Lob::DoesOrderExist(int orderid, string side)
{
    if (side == "BUY")
    {
        return _buyOrdersMap.find(orderid) != _buyOrdersMap.end();
    }
    else
    {
        return _sellOrdersMap.find(orderid) != _sellOrdersMap.end();
    }
}

string Lob::DoesOrderExist(int orderid)
{
    if (_buyOrdersMap.find(orderid) != _buyOrdersMap.end())
    {
        return "BUY";
    }
    else if (_sellOrdersMap.find(orderid) != _sellOrdersMap.end())
    {
        return "SELL";
    }
    return "";
}

void Lob::DisplayLob()
{
    DisplayBuyOrders();
    DisplaySellOrders();
}

const set<std::shared_ptr<Order>, Lob::BuyComparator> &Lob::getBuyOrders() const
{
    return _buyOrders;
}

const set<std::shared_ptr<Order>, Lob::SellComparator> &Lob::getSellOrders() const
{
    return _sellOrders;
}

const map<int, std::shared_ptr<Order>> &Lob::getBuyOrdersMap() const
{
    return _buyOrdersMap;
}

const map<int, std::shared_ptr<Order>> &Lob::getSellOrdersMap() const
{
    return _sellOrdersMap;
}

string Lob::printTade(string symbole, string price, int volume, int aggressiveOrder, int PassiveOrder)
{
    string trade = symbole + "," + price + "," + to_string(volume) + "," + to_string(aggressiveOrder) + "," + to_string(PassiveOrder);
    cout << "Trade : " << trade << endl;
    return trade;
}

vector<string> Lob::handleBuyOrder(std::shared_ptr<Order> buyOrder)
{
    vector<string> tradesWithIn;

    if (_sellOrders.size() == 0)
    {
        _buyOrdersMap[buyOrder->getOrderId()] = buyOrder;
        _buyOrders.insert(buyOrder);
    }
    else
    {
        for (auto currentSellOrder : _sellOrders)
        {
            if (buyOrder->getVolume() <= 0)
                break;

            if (stof(currentSellOrder->getPrice()) > stof(buyOrder->getPrice()))
                break;

            if (currentSellOrder->getVolume() <= 0)
                continue;

            int buyVolume = 0;
            if (buyOrder->getVolume() > currentSellOrder->getVolume())
                buyVolume = currentSellOrder->getVolume();
            else
                buyVolume = buyOrder->getVolume();

            tradesWithIn.push_back(printTade(currentSellOrder->getSymbole(), currentSellOrder->getPrice(), buyVolume, buyOrder->getOrderId(), currentSellOrder->getOrderId()));

            currentSellOrder->decreaseVolumeBy(buyVolume);
            buyOrder->decreaseVolumeBy(buyVolume);
        }

        if (!DoesOrderExist(buyOrder->getOrderId(), buyOrder->getSide()))
            _buyOrdersMap[buyOrder->getOrderId()] = buyOrder;
        _buyOrders.insert(buyOrder);
    }
    return tradesWithIn;
}

vector<string> Lob::handleSellOrder(std::shared_ptr<Order> sellOrder)
{
    vector<string> tradesWithIn;

    if (_buyOrders.size() == 0)
    {
        _sellOrdersMap[sellOrder->getOrderId()] = sellOrder;
        _sellOrders.insert(sellOrder);
    }
    else
    {
        for (auto currentBuyOrder : _buyOrders)
        {

            if (sellOrder->getVolume() <= 0)
                break;

            if (currentBuyOrder->getVolume() <= 0)
                continue;

            if (stof(currentBuyOrder->getPrice()) < stof(sellOrder->getPrice()))
                break;

            int sellVolume = 0;
            if (sellOrder->getVolume() <= currentBuyOrder->getVolume())
                sellVolume = sellOrder->getVolume();
            else
                sellVolume = currentBuyOrder->getVolume();

            tradesWithIn.push_back(printTade(currentBuyOrder->getSymbole(), currentBuyOrder->getPrice(), sellVolume, sellOrder->getOrderId(), currentBuyOrder->getOrderId()));

            sellOrder->decreaseVolumeBy(sellVolume);
            currentBuyOrder->decreaseVolumeBy(sellVolume);
        }

        _sellOrdersMap[sellOrder->getOrderId()] = sellOrder;
        _sellOrders.insert(sellOrder);
    }

    return tradesWithIn;
}

void Lob::handleDeleteOrder(int orderid, string side)
{
    if (side == "BUY")
    {
        _buyOrders.erase(_buyOrdersMap[orderid]);
        _buyOrdersMap.erase(orderid);
    }
    else
    {
        _sellOrders.erase(_sellOrdersMap[orderid]);
        _sellOrdersMap.erase(orderid);
    }
}

vector<string> Lob::AddOrder(int orderid, string symbole, string side, string price, int volume)
{
    if (side == "BUY")
    {
        if (DoesOrderExist(orderid, side))
            throw("Order Already Exists");
        auto buyOrder = std::make_shared<Order>(Order{orderid, symbole, side, price, volume});
        return handleBuyOrder(buyOrder);
    }
    else if (side == "SELL")
    {
        if (DoesOrderExist(orderid, side))
            throw("Order Already Exists");
        auto sellOrder = std::make_shared<Order>(Order{orderid, symbole, side, price, volume});
        return handleSellOrder(sellOrder);
    }
    else
        throw("Unknown order type");
}

vector<string> Lob::handleAmendOrderBuy(int orderid, string price, int volume)
{
    if (stof(_buyOrdersMap[orderid]->getPrice()) == stof(price))
    {
        _buyOrdersMap[orderid]->setVolume(volume);
        return vector<string>();
    }
    else
    {
        _buyOrders.erase(_buyOrdersMap[orderid]);
        _buyOrdersMap[orderid]->setVolume(volume);
        _buyOrdersMap[orderid]->setPrice(price);
        _buyOrdersMap[orderid]->incrementSequenceNumber();
        _buyOrdersMap[orderid]->setCreatedTsMsec();

        return handleBuyOrder(_buyOrdersMap[orderid]);
    }
}

vector<string> Lob::handleAmendOrderSell(int orderid, string price, int volume)
{
    if (stof(_sellOrdersMap[orderid]->getPrice()) == stof(price))
    {
        _sellOrdersMap[orderid]->setVolume(volume);

        return vector<string>();
    }
    else
    {
        _sellOrders.erase(_sellOrdersMap[orderid]);
        _sellOrdersMap[orderid]->setVolume(volume);
        _sellOrdersMap[orderid]->setPrice(price);
        _sellOrdersMap[orderid]->incrementSequenceNumber();
        _sellOrdersMap[orderid]->setCreatedTsMsec();

        return handleSellOrder(_sellOrdersMap[orderid]);
    }
}
void Lob::DeleteOrder(int orderid)
{
    auto orderSide = DoesOrderExist(orderid);
    if (orderSide == "")
        throw("Error , order doesn't exist");

    handleDeleteOrder(orderid, orderSide);
}

vector<string> Lob::AmendOrder(int orderid, string price, int volume)
{
    auto orderSide = DoesOrderExist(orderid);
    if (orderSide == "")
        throw("Error , order doesn't exist");

    if (orderSide == "BUY")
        return handleAmendOrderBuy(orderid, price, volume);
    else if (orderSide == "SELL")
        return handleAmendOrderSell(orderid, price, volume);
    else
        return vector<string>();
}

void Lob::DeleteEmptyOrderIds()
{
    for (auto it = _buyOrdersMap.cbegin(); it != _buyOrdersMap.cend();)
    {
        if (it->second->getVolume() == 0)
        {
            _buyOrders.erase(it->second);
            _buyOrdersMap.erase(it++);
        }
        else
        {
            ++it;
        }
    }

    for (auto it = _sellOrdersMap.cbegin(); it != _sellOrdersMap.cend();)
    {
        if (it->second->getVolume() == 0)
        {
            _sellOrders.erase(it->second);
            _sellOrdersMap.erase(it++);
        }
        else
        {
            ++it;
        }
    }
}

vector<string> Lob::GetBidValues()
{
    std::map<float, int, std::greater<float>> bidOrdersBuy;
    std::map<float, int> bidOrdersSell;
    vector<string> output;
    DeleteEmptyOrderIds();

    auto buyit = _buyOrders.begin();
    while (buyit != _buyOrders.end())
    {
        bidOrdersBuy[stof((*buyit)->getPrice())] += (*buyit)->getVolume();
        ++buyit;
    }

    auto sellit = _sellOrders.begin();
    while (sellit != _sellOrders.end())
    {
        bidOrdersSell[stof((*sellit)->getPrice())] += (*sellit)->getVolume();
        ++sellit;
    }

    auto buyit2 = bidOrdersBuy.begin();
    auto sellit2 = bidOrdersSell.begin();

    while (buyit2 != bidOrdersBuy.end() || sellit2 != bidOrdersSell.end())
    {
        string bid = "", a = "", b = "", c = "", d = "";
        if (buyit2 != bidOrdersBuy.end())
        {
            stringstream s;
            s << buyit2->first;

            a += (s.str());

            stringstream ss;
            ss << buyit2->second;
            b += (ss.str());

            ++buyit2;
        }

        if (sellit2 != bidOrdersSell.end())
        {

            stringstream s;
            s << sellit2->first;
            c += (s.str());

            stringstream ss;
            ss << sellit2->second;
            d += (ss.str());
            ++sellit2;
        }

        bid = a + "," + b + "," + c + "," + d;
        output.push_back(bid);

    }
    return output;
}



    vector<string> MatchingEngine::parseString(string input)
    {
        vector<string> output;
        string T;

        stringstream X(input);

        while (getline(X, T, ','))
        {
            output.push_back(T);
        }
        return output;
    }
    vector<string> MatchingEngine::getTrades()
    {
        return _trades;
    }

    vector<string> MatchingEngine::getResults()
    {
        vector<string> results;

        results.insert(results.end(), _trades.begin(), _trades.end());
        results.insert(results.end(), _bids.begin(), _bids.end());
        return results;
    }

    void MatchingEngine::run(vector<string> inputs)
    {

        for (string input : inputs)
        {
            auto command = parseString(input);
            //cout << "-Order : " << input << endl;

            if (command[0] == "INSERT")
            {
                auto orderId = stoi(command[1]);
                auto symbole = command[2];
                auto side = command[3];
                auto price = command[4];
                auto volume = stoi(command[5]);

                if (_matchingEngineLob.find(symbole) != _matchingEngineLob.end())
                {
                    vector<string> tradesOccured = _matchingEngineLob[symbole]->AddOrder(orderId, symbole, side, price, volume);

                    if (tradesOccured.size() != 0)
                        _trades.insert(_trades.end(), tradesOccured.begin(), tradesOccured.end());
                }
                else
                {
                    _matchingEngineLob[symbole] = make_unique<Lob>();
                    vector<string> tradesOccured = _matchingEngineLob[symbole]->AddOrder(orderId, symbole, side, price, volume);

                    if (tradesOccured.size() != 0)
                        _trades.insert(_trades.end(), tradesOccured.begin(), tradesOccured.end());
                }
                _orderToSymbolMapHistory[orderId] = symbole;
            }
            else if (command[0] == "AMEND")
            {

                auto orderId = stoi(command[1]);
                auto price = command[2];
                auto volume = stoi(command[3]);

                auto orderSymboleIt = _orderToSymbolMapHistory.find(orderId);

                if (orderSymboleIt != _orderToSymbolMapHistory.end())
                {
                    vector<string> tradesOccured = _matchingEngineLob[orderSymboleIt->second]->AmendOrder(orderId, price, volume);

                    if (tradesOccured.size() != 0)
                        _trades.insert(_trades.end(), tradesOccured.begin(), tradesOccured.end());
                }
                else
                {
                    throw("Order not found");
                }
            }
            else if (command[0] == "PULL")
            {
                auto orderId = stoi(command[1]);

                auto orderSymboleIt = _orderToSymbolMapHistory.find(orderId);

                if (orderSymboleIt != _orderToSymbolMapHistory.end())
                {
                    _matchingEngineLob[orderSymboleIt->second]->DeleteOrder(orderId);
                }
                else
                {
                    throw("Order not found");
                }
            }
        }

        calculateBids();
    }

    void MatchingEngine::calculateBids()
    {
        for (auto it = _matchingEngineLob.begin(); it != _matchingEngineLob.end(); ++it)
        {
            vector<string> bids = it->second->GetBidValues();

            if (bids.size() > 0)
            {
                string temp = "===" + it->first + "===";
                _bids.push_back(temp);
                _bids.insert(_bids.end(), bids.begin(), bids.end());
            }
        }
    }


// std::vector<std::string> run(std::vector<std::string> const& input) {

//     MatchingEngine m;
//     m.run(input);

//     auto result = m.getResults();
//     return result;
// }
