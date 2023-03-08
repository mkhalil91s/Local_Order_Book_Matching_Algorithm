#include "lob.h"

Lob::Lob(int side, double price, int volume)
{
    if (side != 0 && side != 1)
        throw("Unknown order type");
    _side = side;
    _price = price;
    _volume = volume;
}

bool Lob::operator==(const Lob &c)
{
    if (_side == c.getSide() && _price == c.getPrice() && _volume == c.getVolume())
        return true;
    return false;
}

const int Lob::getSide() const
{
    return _side;
}

const double Lob::getPrice() const
{
    return _price;
}

const int Lob::getVolume() const
{
    return _volume;
}

void Lob::setVolume(int volume)
{
    _volume = volume;
}

void Lob::decreaseVolumeBy(int size)
{
    if (size > _volume)
        throw("Size is greater than volume");

    _volume = _volume - size;
}

void Order::DisplaySellOrders()
{
    cout << "####### Sell #######" << endl;
    for (auto &element : _sellOrders)
    {
        cout << element.getSide() << "  " << element.getVolume() << "  " << element.getPrice() << "  "<<endl;
    }
    cout << "##########################" << endl;
}

void Order::DisplayBuyOrders()
{
    cout << "####### Buy Orders #######" << endl;
    for (auto &element : _buyOrders)
    {
        cout << element.getSide() << "  " << element.getVolume() << "  " << element.getPrice() << "  " <<endl;
    }
    cout << "##########################" << endl;
}

void Order::DisplayLob()
{
    DisplayBuyOrders();
    DisplaySellOrders();
}

vector<Lob> Order::getBuyOrders()
{
    return _buyOrders;
}
vector<Lob> Order::getSellOrders()
{
    return _sellOrders;
}

void Order::eraseEmptyVolumeOrders()
{

    _sellOrders.erase(std::remove_if(
                          _sellOrders.begin(), _sellOrders.end(),
                          [](const Lob &order)
                          {
                              return order.getVolume() <= 0;
                          }),
                      _sellOrders.end());

    _buyOrders.erase(std::remove_if(
                         _buyOrders.begin(), _buyOrders.end(),
                         [](const Lob &order)
                         {
                             return order.getVolume() <= 0;
                         }),
                     _buyOrders.end());
}

void Order::printTade(int volume, double price)
{
    cout << "  " << volume << " lots trade at the price of  " << price << endl;
}
void Order::handleBuyOrder(Lob buyOrder)
{

    if (buyOrder.getVolume() > 0)
    {
        if (_sellOrders.size() == 0)
        {
            _buyOrders.push_back(buyOrder);
        }
        else
        {
            for (unsigned int i = 0; i < _sellOrders.size(); i++)
            {
                if (buyOrder.getVolume() <= 0)
                    break;

                if (_sellOrders[i].getPrice() > buyOrder.getPrice())
                    break;

                if (_sellOrders[i].getVolume() <= 0)
                    continue;

                int buyVolume = 0;
                if (buyOrder.getVolume() > _sellOrders[i].getVolume())
                {
                    buyVolume = _sellOrders[i].getVolume();
                    printTade(buyVolume, _sellOrders[i].getPrice());
                }
                else
                {
                    buyVolume = _sellOrders[i].getVolume() - buyOrder.getVolume();
                    printTade(buyVolume, _sellOrders[i].getPrice());
                }
                _sellOrders[i].decreaseVolumeBy(buyVolume);
                buyOrder.decreaseVolumeBy(buyVolume);
            }

            if (buyOrder.getVolume() > 0)
            {
                _buyOrders.push_back(buyOrder);
            }
        }
    }
    eraseEmptyVolumeOrders();
    sort(_buyOrders.begin(), _buyOrders.end(), [](const Lob &lhs, const Lob &rhs)
         { return lhs.getPrice() > rhs.getPrice(); });
}

void Order::handleSellOrder(Lob sellOrder)
{
    if (sellOrder.getVolume() > 0)
    {
        if (_buyOrders.size() == 0)
        {
            _sellOrders.push_back(sellOrder);
        }

        else
        {
            for (unsigned int i = 0; i < _buyOrders.size(); i++)
            {
                if (sellOrder.getVolume() <= 0)
                    break;

                if (_buyOrders[i].getPrice() < sellOrder.getPrice())
                    break;

                if (_buyOrders[i].getVolume() <= 0)
                    continue;

                int sellVolume = 0;
                if (sellOrder.getVolume() <= _buyOrders[i].getVolume())
                {
                    sellVolume = _buyOrders[i].getVolume() - sellOrder.getVolume();
                    printTade(sellVolume, _buyOrders[i].getPrice());
                }
                else
                {
                    sellVolume = _buyOrders[i].getVolume();
                    printTade(sellVolume, _buyOrders[i].getPrice());
                }

                sellOrder.decreaseVolumeBy(sellVolume);
                _buyOrders[i].decreaseVolumeBy(sellVolume);
            }

            if (sellOrder.getVolume() > 0)
            {
                _sellOrders.push_back(sellOrder);
            }
        }
    }

    eraseEmptyVolumeOrders();
    sort(_sellOrders.begin(), _sellOrders.end(), [](const Lob &lhs, const Lob &rhs)
         { return lhs.getPrice() < rhs.getPrice(); });
}

void Order::AddOrder(Lob order)
{
    if (order.getSide() == 0)
        handleBuyOrder(order);
    else if (order.getSide() == 1)
        handleSellOrder(order);
}
