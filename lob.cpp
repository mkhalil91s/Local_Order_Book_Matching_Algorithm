#include "lob.h"
#include <sstream>

vector<string> Lob::trades;

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

void Lob::DisplaySellOrders()
{

    // Order::Order(int orderid, string symbole, string side, string price, int volume)
    cout << "####### Sell #######" << endl;
    for (auto element : _sellOrders)
    {
        cout << element->getOrderId() << "  " << element->getSymbole() << "  " << element->getSide() << "  " << element->getPrice() << "  " << element->getVolume() << endl;
    }
    cout << "##########################" << endl;
}

void Lob::DisplayBuyOrders()
{
    cout << "####### Buy Orders #######" << endl;
    for (auto element : _buyOrders)
    {
        cout << element->getOrderId() << "  " << element->getSymbole() << "  " << element->getSide() << "  " << element->getPrice() << "  " << element->getVolume() << endl;
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

bool Lob::BuyComparator::operator()(const std::shared_ptr<Order> o1,
                                    const std::shared_ptr<Order> o2) const
{
    return (stof(o1->getPrice()) > stof(o2->getPrice())) // higher buy price wins
           || (stof(o1->getPrice()) == stof(o2->getPrice()) && o1->getOrderId() < o2->getOrderId());
}

bool Lob::SellComparator::operator()(const std::shared_ptr<Order> o1,
                                     const std::shared_ptr<Order> o2) const
{
    return (stof(o1->getPrice()) < stof(o2->getPrice())) // lower sale price wins
           || (stof(o1->getPrice()) == stof(o2->getPrice()) && o1->getOrderId() < o2->getOrderId());
}

void Lob::printTade(string symbole, string price, int volume, int aggressiveOrder, int PassiveOrder)
{
    string trade = symbole + "," + price + "," + to_string(volume) + "," + to_string(aggressiveOrder) + "," + to_string(PassiveOrder) + "\n";
    // cout << trade;
    Lob::trades.push_back(trade);
}

void Lob::printTrades()
{
    for (string trade : trades)
        cout << trade;
}
void Lob::handleBuyOrder(std::shared_ptr<Order> buyOrder)
{

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

            printTade(currentSellOrder->getSymbole(), currentSellOrder->getPrice(), buyVolume, buyOrder->getOrderId(), currentSellOrder->getOrderId());

            currentSellOrder->decreaseVolumeBy(buyVolume);
            buyOrder->decreaseVolumeBy(buyVolume);
        }

        if (!DoesOrderExist(buyOrder->getOrderId(), buyOrder->getSide()))
            _buyOrdersMap[buyOrder->getOrderId()] = buyOrder;
        _buyOrders.insert(buyOrder);
    }
}

void Lob::handleSellOrder(std::shared_ptr<Order> sellOrder)
{

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

            printTade(currentBuyOrder->getSymbole(), currentBuyOrder->getPrice(), sellVolume, sellOrder->getOrderId(), currentBuyOrder->getOrderId());

            sellOrder->decreaseVolumeBy(sellVolume);
            currentBuyOrder->decreaseVolumeBy(sellVolume);
        }

        _sellOrdersMap[sellOrder->getOrderId()] = sellOrder;
        _sellOrders.insert(sellOrder);
    }
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

void Lob::AddOrder(int orderid, string symbole, string side, string price, int volume)
{
    if (side == "BUY")
    {
        if (DoesOrderExist(orderid, side))
            throw("Order Already Exists");
        auto buyOrder = std::make_shared<Order>(Order{orderid, symbole, side, price, volume});
        handleBuyOrder(buyOrder);
    }
    else if (side == "SELL")
    {
        if (DoesOrderExist(orderid, side))
            throw("Order Already Exists");
        auto sellOrder = std::make_shared<Order>(Order{orderid, symbole, side, price, volume});
        handleSellOrder(sellOrder);
    }
    else
        throw("Unknown order type");
}

void Lob::handleAmendOrderBuy(int orderid, string price, int volume)
{
    if (stof(_buyOrdersMap[orderid]->getPrice()) == stof(price))
    {
        _buyOrdersMap[orderid]->setVolume(volume);
    }
    else
    {
        _buyOrders.erase(_buyOrdersMap[orderid]);
        _buyOrdersMap[orderid]->setVolume(volume);
        _buyOrdersMap[orderid]->setPrice(price);

        handleBuyOrder(_buyOrdersMap[orderid]);
    }
}

void Lob::handleAmendOrderSell(int orderid, string price, int volume)
{
    if (stof(_sellOrdersMap[orderid]->getPrice()) == stof(price))
    {
        _sellOrdersMap[orderid]->setVolume(volume);
    }
    else
    {
        _sellOrders.erase(_sellOrdersMap[orderid]);
        _sellOrdersMap[orderid]->setVolume(volume);
        _sellOrdersMap[orderid]->setPrice(price);

        handleSellOrder(_sellOrdersMap[orderid]);
    }
}
void Lob::DeleteOrder(int orderid)
{
    auto orderSide = DoesOrderExist(orderid);
    if (orderSide == "")
        throw("Error , order doesn't exist");

    handleDeleteOrder(orderid, orderSide);
}

void Lob::AmendOrder(int orderid, string price, int volume)
{
    auto orderSide = DoesOrderExist(orderid);
    if (orderSide == "")
        throw("Error , order doesn't exist");

    if (orderSide == "BUY")
        handleAmendOrderBuy(orderid, price, volume);
    else if (orderSide == "SELL")
        handleAmendOrderSell(orderid, price, volume);
}

void Lob::DeleteEmptyOrderIds()
{
    for (auto it = _buyOrdersMap.cbegin(); it != _buyOrdersMap.cend() /* not hoisted */; /* no increment */)
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

    for (auto it = _sellOrdersMap.cbegin(); it != _sellOrdersMap.cend() /* not hoisted */; /* no increment */)
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

void Lob::DisplayBidValues()
{
    DeleteEmptyOrderIds();
    auto buyit = _buyOrders.begin();
    auto sellit = _sellOrders.begin();

    while (buyit != _buyOrders.end() || sellit != _sellOrders.end())
    {
        if (buyit != _buyOrders.end())
        {
            cout << (*buyit)->getPrice() << "," << (*buyit)->getVolume();
            ++buyit;
        }
        else
        {
            cout << ",,";
        }

        if (sellit != _sellOrders.end())
        {
            cout << "," << (*sellit)->getPrice() << "," << (*sellit)->getVolume();
            ++sellit;
        }
        else
        {
            cout << ",,";
        }

        cout << endl;
    }
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

void MatchingEngine::run(vector<string> inputs)
{

    for (string input : inputs)
    {
        auto command = parseString(input);
        cout<<input<<endl;

        if (command[0] == "INSERT")
        {
            auto orderId = stoi(command[1]);
            auto symbole = command[2];
            auto side = command[3];
            auto price = command[4];
            auto volume = stoi(command[5]);

            if (_matchingEngineLob.find(symbole) != _matchingEngineLob.end())
            {
                _matchingEngineLob[symbole]->AddOrder(orderId, symbole, side, price, volume);
            }
            else
            {
                _matchingEngineLob[symbole] = make_unique<Lob>();
                _matchingEngineLob[symbole]->AddOrder(orderId, symbole, side, price, volume);
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
                _matchingEngineLob[orderSymboleIt->second]->AmendOrder(orderId, price, volume);
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

        _matchingEngineLob["WEBB"]->DisplayLob();

        cout<<"-----------------------------------"<<endl;
    }

    Lob::printTrades();
}