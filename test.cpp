#include "gtest/gtest.h"
#include "lob.h"

TEST(lobTest, testLob)
{

    Order buy1(1, "A", "BUY", "2.5", 50);
    EXPECT_EQ(buy1.getOrderId(), 1);
    EXPECT_EQ(buy1.getSymbole(), "A");
    EXPECT_EQ(buy1.getSide(), "BUY");
    EXPECT_EQ(buy1.getPrice(), "2.5");
    EXPECT_EQ(buy1.getVolume(), 50);

    Order buy2(1, "A", "BUY", "2.1234567", 50);
    EXPECT_EQ(buy2.getOrderId(), 1);
    EXPECT_EQ(buy2.getSymbole(), "A");
    EXPECT_EQ(buy2.getSide(), "BUY");
    EXPECT_EQ(buy2.getPrice(), "2.1234");
    EXPECT_EQ(buy2.getVolume(), 50);

    Order sell3(1, "A", "SELL", "2.123", 50);
    EXPECT_EQ(sell3.getOrderId(), 1);
    EXPECT_EQ(sell3.getSymbole(), "A");
    EXPECT_EQ(sell3.getSide(), "SELL");
    EXPECT_EQ(sell3.getPrice(), "2.123");
    EXPECT_EQ(sell3.getVolume(), 50);

    Order sell4(1, "A", "SELL", "2.12", 50);
    EXPECT_EQ(sell4.getOrderId(), 1);
    EXPECT_EQ(sell4.getSymbole(), "A");
    EXPECT_EQ(sell4.getSide(), "SELL");
    EXPECT_EQ(sell4.getPrice(), "2.12");
    EXPECT_EQ(sell4.getVolume(), 50);
}

TEST(lobTest, testLob2)
{

    Order sell3(1, "A", "SELL", "2.123", 50);
    EXPECT_EQ(sell3.getOrderId(), 1);
    EXPECT_EQ(sell3.getSymbole(), "A");
    EXPECT_EQ(sell3.getSide(), "SELL");
    EXPECT_EQ(sell3.getPrice(), "2.123");
    EXPECT_EQ(sell3.getVolume(), 50);

    sell3.decreaseVolumeBy(45);

    EXPECT_EQ(sell3.getOrderId(), 1);
    EXPECT_EQ(sell3.getSymbole(), "A");
    EXPECT_EQ(sell3.getSide(), "SELL");
    EXPECT_EQ(sell3.getPrice(), "2.123");
    EXPECT_EQ(sell3.getVolume(), 5);

    EXPECT_ANY_THROW(sell3.decreaseVolumeBy(6));
}

TEST(lobTest, testOrderBookEmptyBuyOrders)
{

    std::shared_ptr<std::vector<string> > trades = std::make_shared<std::vector<string>>();
    Lob orderbook(trades);

    orderbook.AddOrder(1, "A", "SELL", "8.5", 20);
    orderbook.AddOrder(2, "A", "SELL", "9.5", 20);
    orderbook.AddOrder(3, "A", "SELL", "10.5", 20);
    orderbook.AddOrder(4, "A", "SELL", "8.5", 20);

    auto sellbook = orderbook.getSellOrders();
    auto buybook = orderbook.getBuyOrders();

    auto sellbookmap = orderbook.getSellOrdersMap();
    auto buybookmap = orderbook.getBuyOrdersMap();

    EXPECT_EQ(sellbook.size(), 4);
    EXPECT_EQ(buybook.size(), 0);

    EXPECT_EQ(sellbookmap.size(), 4);
    EXPECT_EQ(buybookmap.size(), 0);

    auto it = sellbook.begin();
    std::advance(it, 0);

    EXPECT_EQ((*it)->getOrderId(), 1);
    EXPECT_EQ((*it)->getSymbole(), "A");
    EXPECT_EQ((*it)->getSide(), "SELL");
    EXPECT_EQ((*it)->getPrice(), "8.5");
    EXPECT_EQ((*it)->getVolume(), 20);

    std::advance(it, 1);

    EXPECT_EQ((*it)->getOrderId(), 4);
    EXPECT_EQ((*it)->getSymbole(), "A");
    EXPECT_EQ((*it)->getSide(), "SELL");
    EXPECT_EQ((*it)->getPrice(), "8.5");
    EXPECT_EQ((*it)->getVolume(), 20);

    std::advance(it, 1);

    EXPECT_EQ((*it)->getOrderId(), 2);
    EXPECT_EQ((*it)->getSymbole(), "A");
    EXPECT_EQ((*it)->getSide(), "SELL");
    EXPECT_EQ((*it)->getPrice(), "9.5");
    EXPECT_EQ((*it)->getVolume(), 20);

    std::advance(it, 1);

    EXPECT_EQ((*it)->getOrderId(), 3);
    EXPECT_EQ((*it)->getSymbole(), "A");
    EXPECT_EQ((*it)->getSide(), "SELL");
    EXPECT_EQ((*it)->getPrice(), "10.5");
    EXPECT_EQ((*it)->getVolume(), 20);

    EXPECT_ANY_THROW(orderbook.AddOrder(4, "A", "SELL", "5.5", 0));
}

TEST(lobTest, testOrderBookEmptySellOrders)
{

    std::shared_ptr<std::vector<string> > trades = std::make_shared<std::vector<string>>();
    Lob orderbook(trades);

    orderbook.AddOrder(0, "A", "BUY", "4.5", 0);
    orderbook.AddOrder(1, "A", "BUY", "3.5", 20);
    orderbook.AddOrder(2, "A", "BUY", "2.5", 20);
    orderbook.AddOrder(3, "A", "BUY", "1.5", 20);
    orderbook.AddOrder(4, "A", "BUY", "1.5", 0);
    orderbook.AddOrder(5, "A", "BUY", "3.5", 20);

    auto sellbook = orderbook.getSellOrders();
    auto buybook = orderbook.getBuyOrders();

    auto sellbookmap = orderbook.getSellOrdersMap();
    auto buybookmap = orderbook.getBuyOrdersMap();

    EXPECT_EQ(sellbook.size(), 0);
    EXPECT_EQ(buybook.size(), 6);
    EXPECT_EQ(sellbookmap.size(), 0);
    EXPECT_EQ(buybookmap.size(), 6);

    auto it = buybook.begin();
    std::advance(it, 0);

    EXPECT_EQ((*it)->getOrderId(), 0);
    EXPECT_EQ((*it)->getSymbole(), "A");
    EXPECT_EQ((*it)->getSide(), "BUY");
    EXPECT_EQ((*it)->getPrice(), "4.5");
    EXPECT_EQ((*it)->getVolume(), 0);

    std::advance(it, 1);

    EXPECT_EQ((*it)->getOrderId(), 1);
    EXPECT_EQ((*it)->getSymbole(), "A");
    EXPECT_EQ((*it)->getSide(), "BUY");
    EXPECT_EQ((*it)->getPrice(), "3.5");
    EXPECT_EQ((*it)->getVolume(), 20);

    std::advance(it, 1);

    EXPECT_EQ((*it)->getOrderId(), 5);
    EXPECT_EQ((*it)->getSymbole(), "A");
    EXPECT_EQ((*it)->getSide(), "BUY");
    EXPECT_EQ((*it)->getPrice(), "3.5");
    EXPECT_EQ((*it)->getVolume(), 20);

    std::advance(it, 1);

    EXPECT_EQ((*it)->getOrderId(), 2);
    EXPECT_EQ((*it)->getSymbole(), "A");
    EXPECT_EQ((*it)->getSide(), "BUY");
    EXPECT_EQ((*it)->getPrice(), "2.5");
    EXPECT_EQ((*it)->getVolume(), 20);

    std::advance(it, 1);

    EXPECT_EQ((*it)->getOrderId(), 3);
    EXPECT_EQ((*it)->getSymbole(), "A");
    EXPECT_EQ((*it)->getSide(), "BUY");
    EXPECT_EQ((*it)->getPrice(), "1.5");
    EXPECT_EQ((*it)->getVolume(), 20);

    std::advance(it, 1);

    EXPECT_EQ((*it)->getOrderId(), 4);
    EXPECT_EQ((*it)->getSymbole(), "A");
    EXPECT_EQ((*it)->getSide(), "BUY");
    EXPECT_EQ((*it)->getPrice(), "1.5");
    EXPECT_EQ((*it)->getVolume(), 0);

    EXPECT_ANY_THROW(orderbook.AddOrder(5, "A", "BUY", "3.5", 20));
}

TEST(lobTest, testOrderBookSellOrders)
{
    std::shared_ptr<std::vector<string> > trades = std::make_shared<std::vector<string>>();
    Lob orderbook(trades);

    orderbook.AddOrder(1, "A", "BUY", "9.5", 10);
    orderbook.AddOrder(2, "A", "BUY", "20", 10);
    orderbook.AddOrder(3, "A", "SELL", "10.5", 20);

    auto sellbook = orderbook.getSellOrders();
    auto buybook = orderbook.getBuyOrders();

    auto sellbookmap = orderbook.getSellOrdersMap();
    auto buybookmap = orderbook.getBuyOrdersMap();

    EXPECT_EQ(sellbook.size(), 1);
    EXPECT_EQ(buybook.size(), 2);
    EXPECT_EQ(sellbookmap.size(), 1);
    EXPECT_EQ(buybookmap.size(), 2);

    auto it = sellbook.begin();
    std::advance(it, 0);

    EXPECT_EQ((*it)->getOrderId(), 3);
    EXPECT_EQ((*it)->getSymbole(), "A");
    EXPECT_EQ((*it)->getSide(), "SELL");
    EXPECT_EQ((*it)->getPrice(), "10.5");
    EXPECT_EQ((*it)->getVolume(), 10);

    auto it2 = buybook.begin();
    std::advance(it, 0);

    EXPECT_EQ((*it2)->getOrderId(), 2);
    EXPECT_EQ((*it2)->getSymbole(), "A");
    EXPECT_EQ((*it2)->getSide(), "BUY");
    EXPECT_EQ((*it2)->getPrice(), "20");
    EXPECT_EQ((*it2)->getVolume(), 0);

    std::advance(it2, 1);

    EXPECT_EQ((*it2)->getOrderId(), 1);
    EXPECT_EQ((*it2)->getSymbole(), "A");
    EXPECT_EQ((*it2)->getSide(), "BUY");
    EXPECT_EQ((*it2)->getPrice(), "9.5");
    EXPECT_EQ((*it2)->getVolume(), 10);

    orderbook.AddOrder(4, "A", "SELL", "8", 5);

    sellbook = orderbook.getSellOrders();
    buybook = orderbook.getBuyOrders();

    sellbookmap = orderbook.getSellOrdersMap();
    buybookmap = orderbook.getBuyOrdersMap();
    EXPECT_EQ(sellbook.size(), 2);
    EXPECT_EQ(buybook.size(), 2);
    EXPECT_EQ(sellbookmap.size(), 2);
    EXPECT_EQ(buybookmap.size(), 2);

    it = sellbook.begin();
    std::advance(it, 0);

    EXPECT_EQ((*it)->getOrderId(), 4);
    EXPECT_EQ((*it)->getSymbole(), "A");
    EXPECT_EQ((*it)->getSide(), "SELL");
    EXPECT_EQ((*it)->getPrice(), "8");
    EXPECT_EQ((*it)->getVolume(), 0);

    std::advance(it, 1);

    EXPECT_EQ((*it)->getOrderId(), 3);
    EXPECT_EQ((*it)->getSymbole(), "A");
    EXPECT_EQ((*it)->getSide(), "SELL");
    EXPECT_EQ((*it)->getPrice(), "10.5");
    EXPECT_EQ((*it)->getVolume(), 10);

    it2 = buybook.begin();
    std::advance(it, 0);

    EXPECT_EQ((*it2)->getOrderId(), 2);
    EXPECT_EQ((*it2)->getSymbole(), "A");
    EXPECT_EQ((*it2)->getSide(), "BUY");
    EXPECT_EQ((*it2)->getPrice(), "20");
    EXPECT_EQ((*it2)->getVolume(), 0);

    std::advance(it2, 1);

    EXPECT_EQ((*it2)->getOrderId(), 1);
    EXPECT_EQ((*it2)->getSymbole(), "A");
    EXPECT_EQ((*it2)->getSide(), "BUY");
    EXPECT_EQ((*it2)->getPrice(), "9.5");
    EXPECT_EQ((*it2)->getVolume(), 5);
}

TEST(lobTest, testDeleteOrder)
{
    std::shared_ptr<std::vector<string> > trades = std::make_shared<std::vector<string>>();
    Lob orderbook(trades);

    orderbook.AddOrder(1, "A", "BUY", "9.5", 10);
    orderbook.AddOrder(2, "A", "BUY", "20", 10);
    orderbook.AddOrder(3, "A", "SELL", "10.5", 20);

    auto sellbook = orderbook.getSellOrders();
    auto buybook = orderbook.getBuyOrders();

    auto sellbookmap = orderbook.getSellOrdersMap();
    auto buybookmap = orderbook.getBuyOrdersMap();

    EXPECT_EQ(sellbook.size(), 1);
    EXPECT_EQ(buybook.size(), 2);
    EXPECT_EQ(sellbookmap.size(), 1);
    EXPECT_EQ(buybookmap.size(), 2);

    orderbook.DeleteOrder(1);
    orderbook.DeleteOrder(2);
    orderbook.DeleteOrder(3);

    sellbook = orderbook.getSellOrders();
    buybook = orderbook.getBuyOrders();

    sellbookmap = orderbook.getSellOrdersMap();
    buybookmap = orderbook.getBuyOrdersMap();

    EXPECT_EQ(sellbook.size(), 0);
    EXPECT_EQ(buybook.size(), 0);
    EXPECT_EQ(sellbookmap.size(), 0);
    EXPECT_EQ(buybookmap.size(), 0);

    EXPECT_ANY_THROW(orderbook.DeleteOrder(3));
}

TEST(lobTest, testDeleteOrder2)
{
    std::shared_ptr<std::vector<string> > trades = std::make_shared<std::vector<string>>();
    Lob orderbook(trades);

    orderbook.AddOrder(1, "A", "BUY", "9.5", 10);
    orderbook.AddOrder(2, "A", "BUY", "20", 10);
    orderbook.AddOrder(3, "A", "SELL", "10.5", 20);

    auto sellbook = orderbook.getSellOrders();
    auto buybook = orderbook.getBuyOrders();

    auto sellbookmap = orderbook.getSellOrdersMap();
    auto buybookmap = orderbook.getBuyOrdersMap();

    EXPECT_EQ(sellbook.size(), 1);
    EXPECT_EQ(buybook.size(), 2);
    EXPECT_EQ(sellbookmap.size(), 1);
    EXPECT_EQ(buybookmap.size(), 2);

    orderbook.DeleteOrder(2);

    sellbook = orderbook.getSellOrders();
    buybook = orderbook.getBuyOrders();

    sellbookmap = orderbook.getSellOrdersMap();
    buybookmap = orderbook.getBuyOrdersMap();

    EXPECT_EQ(sellbook.size(), 1);
    EXPECT_EQ(buybook.size(), 1);
    EXPECT_EQ(sellbookmap.size(), 1);
    EXPECT_EQ(buybookmap.size(), 1);

    auto it = buybook.begin();
    std::advance(it, 0);

    EXPECT_EQ((*it)->getOrderId(), 1);
    EXPECT_EQ((*it)->getSymbole(), "A");
    EXPECT_EQ((*it)->getSide(), "BUY");
    EXPECT_EQ((*it)->getPrice(), "9.5");
    EXPECT_EQ((*it)->getVolume(), 10);

    auto it2 = sellbook.begin();
    std::advance(it2, 0);

    EXPECT_EQ((*it2)->getOrderId(), 3);
    EXPECT_EQ((*it2)->getSymbole(), "A");
    EXPECT_EQ((*it2)->getSide(), "SELL");
    EXPECT_EQ((*it2)->getPrice(), "10.5");
    EXPECT_EQ((*it2)->getVolume(), 10);

    EXPECT_ANY_THROW(orderbook.DeleteOrder(2));
}

TEST(lobTest, givenExampleTestCase)
{
    std::shared_ptr<std::vector<string> > trades = std::make_shared<std::vector<string>>();
    Lob orderbook(trades);

    orderbook.AddOrder(1, "A", "BUY", "10.3", 15);
    orderbook.AddOrder(2, "A", "BUY", "10.2", 10);
    orderbook.AddOrder(3, "A", "SELL", "10", 40);
    orderbook.AddOrder(4, "A", "BUY", "10.5", 50);
    orderbook.AddOrder(5, "A", "SELL", "11", 30);

    auto sellbook = orderbook.getSellOrders();
    auto buybook = orderbook.getBuyOrders();

    auto sellbookmap = orderbook.getSellOrdersMap();
    auto buybookmap = orderbook.getBuyOrdersMap();

    auto it = buybook.begin();
    std::advance(it, 0);

    EXPECT_EQ((*it)->getOrderId(), 4);
    EXPECT_EQ((*it)->getSymbole(), "A");
    EXPECT_EQ((*it)->getSide(), "BUY");
    EXPECT_EQ((*it)->getPrice(), "10.5");
    EXPECT_EQ((*it)->getVolume(), 35);

    std::advance(it, 1);

    EXPECT_EQ((*it)->getOrderId(), 1);
    EXPECT_EQ((*it)->getSymbole(), "A");
    EXPECT_EQ((*it)->getSide(), "BUY");
    EXPECT_EQ((*it)->getPrice(), "10.3");
    EXPECT_EQ((*it)->getVolume(), 0);

    std::advance(it, 1);

    EXPECT_EQ((*it)->getOrderId(), 2);
    EXPECT_EQ((*it)->getSymbole(), "A");
    EXPECT_EQ((*it)->getSide(), "BUY");
    EXPECT_EQ((*it)->getPrice(), "10.2");
    EXPECT_EQ((*it)->getVolume(), 0);

    auto it2 = sellbook.begin();
    std::advance(it2, 0);

    EXPECT_EQ((*it2)->getOrderId(), 3);
    EXPECT_EQ((*it2)->getSymbole(), "A");
    EXPECT_EQ((*it2)->getSide(), "SELL");
    EXPECT_EQ((*it2)->getPrice(), "10");
    EXPECT_EQ((*it2)->getVolume(), 0);

    std::advance(it2, 1);

    EXPECT_EQ((*it2)->getOrderId(), 5);
    EXPECT_EQ((*it2)->getSymbole(), "A");
    EXPECT_EQ((*it2)->getSide(), "SELL");
    EXPECT_EQ((*it2)->getPrice(), "11");
    EXPECT_EQ((*it2)->getVolume(), 30);

    orderbook.DisplayLob();
}

TEST(lobTest, testAmendOrder)
{
    std::shared_ptr<std::vector<string> > trades = std::make_shared<std::vector<string>>();
    Lob orderbook(trades);

    orderbook.AddOrder(1, "A", "BUY", "9.5", 10);
    orderbook.AddOrder(2, "A", "BUY", "20", 10);
    orderbook.AddOrder(3, "A", "SELL", "10.5", 20);

    auto sellbook = orderbook.getSellOrders();
    auto buybook = orderbook.getBuyOrders();

    auto sellbookmap = orderbook.getSellOrdersMap();
    auto buybookmap = orderbook.getBuyOrdersMap();

    EXPECT_EQ(sellbook.size(), 1);
    EXPECT_EQ(buybook.size(), 2);
    EXPECT_EQ(sellbookmap.size(), 1);
    EXPECT_EQ(buybookmap.size(), 2);

    orderbook.AmendOrder(1, "10.5", 5);

    sellbook = orderbook.getSellOrders();
    buybook = orderbook.getBuyOrders();

    sellbookmap = orderbook.getSellOrdersMap();
    buybookmap = orderbook.getBuyOrdersMap();

    EXPECT_EQ(sellbook.size(), 1);
    EXPECT_EQ(buybook.size(), 2);
    EXPECT_EQ(sellbookmap.size(), 1);
    EXPECT_EQ(buybookmap.size(), 2);

    auto it = buybook.begin();
    std::advance(it, 0);

    EXPECT_EQ((*it)->getOrderId(), 2);
    EXPECT_EQ((*it)->getSymbole(), "A");
    EXPECT_EQ((*it)->getSide(), "BUY");
    EXPECT_EQ((*it)->getPrice(), "20");
    EXPECT_EQ((*it)->getVolume(), 0);

    std::advance(it, 1);

    EXPECT_EQ((*it)->getOrderId(), 1);
    EXPECT_EQ((*it)->getSymbole(), "A");
    EXPECT_EQ((*it)->getSide(), "BUY");
    EXPECT_EQ((*it)->getPrice(), "10.5");
    EXPECT_EQ((*it)->getVolume(), 0);

    auto it2 = sellbook.begin();
    std::advance(it2, 0);

    EXPECT_EQ((*it2)->getOrderId(), 3);
    EXPECT_EQ((*it2)->getSymbole(), "A");
    EXPECT_EQ((*it2)->getSide(), "SELL");
    EXPECT_EQ((*it2)->getPrice(), "10.5");
    EXPECT_EQ((*it2)->getVolume(), 5);

    orderbook.DeleteEmptyOrderIds();

    sellbook = orderbook.getSellOrders();
    buybook = orderbook.getBuyOrders();

    sellbookmap = orderbook.getSellOrdersMap();
    buybookmap = orderbook.getBuyOrdersMap();

    EXPECT_EQ(sellbook.size(), 1);
    EXPECT_EQ(buybook.size(), 0);
    EXPECT_EQ(sellbookmap.size(), 1);
    EXPECT_EQ(buybookmap.size(), 0);

    it2 = sellbook.begin();
    std::advance(it2, 0);

    EXPECT_EQ((*it2)->getOrderId(), 3);
    EXPECT_EQ((*it2)->getSymbole(), "A");
    EXPECT_EQ((*it2)->getSide(), "SELL");
    EXPECT_EQ((*it2)->getPrice(), "10.5");
    EXPECT_EQ((*it2)->getVolume(), 5);
}

TEST(lobTest, testEngine2)
{
    auto input = std::vector<std::string>();

    input.emplace_back("INSERT,1,AAPL,BUY,12.2,5");

    MatchingEngine m;
    m.run(input);

    auto result = m.getResults();

    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], "===AAPL===");
    EXPECT_EQ(result[1], "12.2,5,,");
}

TEST(lobTest, testEngine3)
{
    auto input = std::vector<std::string>();

    input.emplace_back("INSERT,1,AAPL,BUY,12.2,5");
    input.emplace_back("INSERT,2,AAPL,SELL,12.1,8");

    MatchingEngine m;
    m.run(input);

    auto result = m.getResults();

    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], "AAPL,12.2,5,2,1");
    EXPECT_EQ(result[1], "===AAPL===");
    EXPECT_EQ(result[2], ",,12.1,3");
}

TEST(lobTest, testEngine4)
{
    auto input = std::vector<std::string>();

    input.emplace_back("INSERT,1,AAPL,SELL,12.1,8");
    input.emplace_back("INSERT,2,AAPL,BUY,12.2,5");

    MatchingEngine m;
    m.run(input);

    auto result = m.getResults();

    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], "AAPL,12.1,5,2,1");
    EXPECT_EQ(result[1], "===AAPL===");
    EXPECT_EQ(result[2], ",,12.1,3");
}

TEST(lobTest, testEngine5)
{
    auto input = std::vector<std::string>();

    input.emplace_back("INSERT,8,AAPL,BUY,14.235,5");
    input.emplace_back("INSERT,6,AAPL,BUY,14.235,6");
    input.emplace_back("INSERT,7,AAPL,BUY,14.235,12");
    input.emplace_back("INSERT,2,AAPL,BUY,14.234,5");
    input.emplace_back("INSERT,1,AAPL,BUY,14.23,3");
    input.emplace_back("INSERT,5,AAPL,SELL,14.237,8");
    input.emplace_back("INSERT,3,AAPL,SELL,14.24,9");
    input.emplace_back("PULL,8");
    input.emplace_back("INSERT,4,AAPL,SELL,14.234,25");

    MatchingEngine m;
    m.run(input);

    auto result = m.getResults();

    EXPECT_EQ(result.size(), 7);
    EXPECT_EQ(result[0], "AAPL,14.235,6,4,6");
    EXPECT_EQ(result[1], "AAPL,14.235,12,4,7");
    EXPECT_EQ(result[2], "AAPL,14.234,5,4,2");
    EXPECT_EQ(result[3], "===AAPL===");
    EXPECT_EQ(result[4], "14.23,3,14.234,2");
    EXPECT_EQ(result[5], ",,14.237,8");
    EXPECT_EQ(result[6], ",,14.24,9");
}
TEST(lobTest, multiSymbole)
{
    auto input = std::vector<std::string>();

    input.emplace_back("INSERT,1,WEBB,BUY,0.3854,5");
    input.emplace_back("INSERT,2,TSLA,BUY,412,31");
    input.emplace_back("INSERT,3,TSLA,BUY,410.5,27");
    input.emplace_back("INSERT,4,AAPL,SELL,21,8");
    input.emplace_back("INSERT,11,WEBB,SELL,0.3854,4");
    input.emplace_back("INSERT,13,WEBB,SELL,0.3853,6");

    MatchingEngine m;
    m.run(input);

    auto result = m.getResults();

    EXPECT_EQ(result.size(), 9);
    EXPECT_EQ(result[0], "WEBB,0.3854,4,11,1");
    EXPECT_EQ(result[1], "WEBB,0.3854,1,13,1");
    EXPECT_EQ(result[2], "===AAPL===");
    EXPECT_EQ(result[3], ",,21,8");
    EXPECT_EQ(result[4], "===TSLA===");
    EXPECT_EQ(result[5], "412,31,,");
    EXPECT_EQ(result[6], "410.5,27,,");
    EXPECT_EQ(result[7], "===WEBB===");
    EXPECT_EQ(result[8], ",,0.3853,5");
}

TEST(lobTest, amend)
{

    auto input = std::vector<std::string>();

    input.emplace_back("INSERT,1,WEBB,BUY,45.95,5");
    input.emplace_back("INSERT,2,WEBB,BUY,45.95,6");
    input.emplace_back("INSERT,3,WEBB,BUY,45.95,12");
    input.emplace_back("INSERT,4,WEBB,SELL,46,8");
    input.emplace_back("AMEND,2,46,3");
    input.emplace_back("INSERT,5,WEBB,SELL,45.95,1");
    input.emplace_back("AMEND,1,45.95,3");
    input.emplace_back("INSERT,6,WEBB,SELL,45.95,1");
    input.emplace_back("AMEND,1,45.95,5");
    input.emplace_back("INSERT,7,WEBB,SELL,45.95,1");

    MatchingEngine m;
    m.run(input);

    auto result = m.getResults();

    EXPECT_EQ(result.size(), 6);
    EXPECT_EQ(result[0], "WEBB,46,3,2,4");
    EXPECT_EQ(result[1], "WEBB,45.95,1,5,1");
    EXPECT_EQ(result[2], "WEBB,45.95,1,6,1");
    EXPECT_EQ(result[3], "WEBB,45.95,1,7,1");
    EXPECT_EQ(result[4], "===WEBB===");
    EXPECT_EQ(result[5], "45.95,16,46,5");
}

TEST(lobTest, randomTest)
{
    auto input = std::vector<std::string>();

    input.emplace_back("INSERT,1,HP,SELL,1.0613,1");
    input.emplace_back("INSERT,2,TESLA,SELL,2.6355,0");
    input.emplace_back("INSERT,3,NOKIA,BUY,2.7828,6");
    input.emplace_back("INSERT,4,MICROSOFT,SELL,1.0436,6");
    input.emplace_back("INSERT,5,HP,SELL,3.8264,6");
    input.emplace_back("INSERT,6,ASML,BUY,3.8775,7");
    input.emplace_back("INSERT,7,APPLE,BUY,1.211,0");
    input.emplace_back("INSERT,8,NOKIA,BUY,3.0873,9");
    input.emplace_back("INSERT,9,MICROSOFT,BUY,2.9109,6");
    input.emplace_back("INSERT,10,TESLA,BUY,2.2065,4");
    input.emplace_back("INSERT,11,ASML,BUY,1.7028,3");
    input.emplace_back("INSERT,12,APPLE,BUY,1.5416,1");
    input.emplace_back("INSERT,13,MICROSOFT,BUY,1.6491,6");
    input.emplace_back("INSERT,14,APPLE,SELL,3.6032,0");
    input.emplace_back("INSERT,15,NOKIA,SELL,3.1225,0");
    input.emplace_back("INSERT,16,MICROSOFT,BUY,3.6436,2");
    input.emplace_back("INSERT,17,APPLE,BUY,3.3832,1");
    input.emplace_back("INSERT,18,NOKIA,BUY,1.4029,2");
    input.emplace_back("INSERT,19,NOKIA,SELL,3.9472,6");
    input.emplace_back("INSERT,20,NOKIA,BUY,1.3853,0");
    input.emplace_back("INSERT,21,ASML,SELL,2.6721,1");
    input.emplace_back("INSERT,22,ASML,BUY,1.6271,6");
    input.emplace_back("INSERT,23,TESLA,BUY,1.9369,5");
    input.emplace_back("INSERT,24,CAC40,BUY,3.2176,7");
    input.emplace_back("INSERT,25,HP,BUY,1.7695,6");
    input.emplace_back("INSERT,26,APPLE,BUY,3.1178,10");
    input.emplace_back("INSERT,27,CAC40,BUY,3.739,8");
    input.emplace_back("INSERT,28,CAC40,BUY,2.3146,0");
    input.emplace_back("INSERT,29,CAC40,BUY,3.3786,0");
    input.emplace_back("INSERT,30,MICROSOFT,SELL,1.5642,0");
    input.emplace_back("INSERT,31,HP,SELL,3.6231,5");
    input.emplace_back("INSERT,32,ASML,BUY,3.7188,0");
    input.emplace_back("INSERT,33,HP,BUY,2.8348,0");
    input.emplace_back("INSERT,34,NOKIA,SELL,3.6334,2");
    input.emplace_back("INSERT,35,MICROSOFT,BUY,1.4015,4");
    input.emplace_back("INSERT,36,TESLA,BUY,1.3516,0");
    input.emplace_back("INSERT,37,APPLE,BUY,2.3292,7");
    input.emplace_back("INSERT,38,MICROSOFT,SELL,3.6234,4");
    input.emplace_back("INSERT,39,ASML,SELL,1.0522,10");
    input.emplace_back("INSERT,40,HP,SELL,2.0258,8");
    input.emplace_back("INSERT,41,NOKIA,BUY,3.1547,9");
    input.emplace_back("INSERT,42,NOKIA,BUY,2.0874,5");
    input.emplace_back("INSERT,43,MICROSOFT,BUY,3.6416,8");
    input.emplace_back("INSERT,44,APPLE,BUY,2.8277,8");
    input.emplace_back("INSERT,45,NOKIA,SELL,3.9224,4");
    input.emplace_back("INSERT,46,NOKIA,BUY,2.2393,0");
    input.emplace_back("INSERT,47,TESLA,BUY,3.0655,7");
    input.emplace_back("INSERT,48,APPLE,SELL,1.7156,0");
    input.emplace_back("INSERT,49,TESLA,BUY,1.3637,9");
    input.emplace_back("INSERT,50,CAC40,SELL,2.565,4");
    input.emplace_back("INSERT,51,HP,BUY,1.415,5");
    input.emplace_back("INSERT,52,HP,SELL,1.4728,10");
    input.emplace_back("INSERT,53,APPLE,SELL,2.8766,1");
    input.emplace_back("INSERT,54,NOKIA,BUY,2.607,7");
    input.emplace_back("INSERT,55,NOKIA,SELL,3.9141,6");
    input.emplace_back("INSERT,56,CAC40,BUY,3.6572,5");
    input.emplace_back("INSERT,57,TESLA,BUY,2.808,5");
    input.emplace_back("INSERT,58,APPLE,SELL,1.2905,5");
    input.emplace_back("INSERT,59,HP,BUY,2.2052,6");
    input.emplace_back("INSERT,60,HP,SELL,1.5743,6");
    input.emplace_back("INSERT,61,CAC40,BUY,3.7222,5");
    input.emplace_back("INSERT,62,TESLA,BUY,1.6089,5");
    input.emplace_back("INSERT,63,HP,BUY,2.1634,5");
    input.emplace_back("INSERT,64,CAC40,SELL,3.2039,0");
    input.emplace_back("INSERT,65,NOKIA,SELL,2.4973,5");
    input.emplace_back("INSERT,66,ASML,BUY,3.0211,6");
    input.emplace_back("INSERT,67,TESLA,SELL,1.0926,2");
    input.emplace_back("INSERT,68,HP,SELL,1.9584,2");
    input.emplace_back("INSERT,69,HP,BUY,1.4506,2");
    input.emplace_back("INSERT,70,HP,SELL,1.7141,8");
    input.emplace_back("INSERT,71,HP,BUY,3.4761,6");
    input.emplace_back("INSERT,72,CAC40,BUY,3.3944,9");
    input.emplace_back("INSERT,73,ASML,SELL,1.9574,6");
    input.emplace_back("INSERT,74,HP,SELL,3.5997,7");
    input.emplace_back("INSERT,75,HP,SELL,1.1708,2");
    input.emplace_back("INSERT,76,ASML,SELL,3.9167,10");
    input.emplace_back("INSERT,77,MICROSOFT,BUY,2.6471,5");
    input.emplace_back("INSERT,78,ASML,BUY,3.6699,0");
    input.emplace_back("INSERT,79,APPLE,BUY,2.5487,10");
    input.emplace_back("INSERT,80,TESLA,SELL,3.5616,0");
    input.emplace_back("INSERT,81,ASML,SELL,2.842,3");
    input.emplace_back("INSERT,82,MICROSOFT,BUY,1.2582,5");
    input.emplace_back("INSERT,83,ASML,SELL,3.0768,4");
    input.emplace_back("INSERT,84,CAC40,BUY,3.5264,1");
    input.emplace_back("INSERT,85,HP,BUY,3.066,6");
    input.emplace_back("INSERT,86,HP,SELL,2.6113,9");
    input.emplace_back("INSERT,87,HP,SELL,2.9013,7");
    input.emplace_back("INSERT,88,HP,BUY,3.2993,1");
    input.emplace_back("INSERT,89,TESLA,SELL,1.2884,5");
    input.emplace_back("INSERT,90,APPLE,SELL,1.4946,1");
    input.emplace_back("INSERT,91,APPLE,SELL,2.5984,8");
    input.emplace_back("INSERT,92,MICROSOFT,BUY,2.6786,5");
    input.emplace_back("INSERT,93,CAC40,SELL,2.9397,0");
    input.emplace_back("INSERT,94,CAC40,SELL,1.9655,0");
    input.emplace_back("INSERT,95,NOKIA,SELL,3.6359,3");
    input.emplace_back("INSERT,96,MICROSOFT,SELL,3.3161,6");
    input.emplace_back("INSERT,97,APPLE,SELL,1.2378,9");
    input.emplace_back("INSERT,98,CAC40,SELL,2.7558,0");
    input.emplace_back("INSERT,99,TESLA,SELL,1.6886,8");
    input.emplace_back("INSERT,100,CAC40,SELL,1.4937,9");
    input.emplace_back("INSERT,101,APPLE,SELL,3.0666,2");
    input.emplace_back("INSERT,102,APPLE,SELL,3.3789,5");
    input.emplace_back("INSERT,103,CAC40,SELL,3.2832,4");
    input.emplace_back("INSERT,104,TESLA,SELL,2.5159,5");
    input.emplace_back("INSERT,105,APPLE,SELL,3.0339,4");
    input.emplace_back("INSERT,106,TESLA,SELL,2.533,7");
    input.emplace_back("INSERT,107,ASML,BUY,1.5162,5");
    input.emplace_back("INSERT,108,ASML,SELL,1.8263,5");
    input.emplace_back("INSERT,109,HP,SELL,3.7054,7");
    input.emplace_back("INSERT,110,CAC40,SELL,3.5761,3");
    input.emplace_back("INSERT,111,MICROSOFT,SELL,1.6395,3");
    input.emplace_back("INSERT,112,MICROSOFT,BUY,1.7494,6");
    input.emplace_back("INSERT,113,TESLA,BUY,2.3163,4");
    input.emplace_back("INSERT,114,CAC40,BUY,1.979,5");
    input.emplace_back("INSERT,115,NOKIA,SELL,3.6093,1");
    input.emplace_back("INSERT,116,TESLA,BUY,2.2871,2");
    input.emplace_back("INSERT,117,ASML,SELL,1.69,8");
    input.emplace_back("INSERT,118,ASML,SELL,3.0716,9");
    input.emplace_back("INSERT,119,CAC40,SELL,2.2574,5");
    input.emplace_back("INSERT,120,MICROSOFT,SELL,3.5302,0");
    input.emplace_back("INSERT,121,APPLE,BUY,3.9815,10");
    input.emplace_back("INSERT,122,APPLE,SELL,1.4882,6");
    input.emplace_back("INSERT,123,NOKIA,BUY,1.0521,0");
    input.emplace_back("INSERT,124,APPLE,SELL,3.0859,1");
    input.emplace_back("INSERT,125,MICROSOFT,SELL,3.7978,4");
    input.emplace_back("INSERT,126,APPLE,BUY,3.3273,4");
    input.emplace_back("INSERT,127,MICROSOFT,SELL,2.4984,10");
    input.emplace_back("INSERT,128,CAC40,BUY,3.7039,4");
    input.emplace_back("INSERT,129,MICROSOFT,BUY,2.265,9");
    input.emplace_back("INSERT,130,ASML,BUY,1.7097,1");
    input.emplace_back("INSERT,131,ASML,SELL,3.6162,4");
    input.emplace_back("INSERT,132,TESLA,SELL,3.295,7");
    input.emplace_back("INSERT,133,APPLE,BUY,1.713,0");
    input.emplace_back("INSERT,134,MICROSOFT,BUY,1.4272,10");
    input.emplace_back("INSERT,135,MICROSOFT,BUY,3.0006,5");
    input.emplace_back("INSERT,136,TESLA,SELL,3.6836,2");
    input.emplace_back("INSERT,137,TESLA,SELL,2.8542,4");
    input.emplace_back("INSERT,138,MICROSOFT,SELL,2.8004,6");
    input.emplace_back("INSERT,139,TESLA,BUY,2.93,5");
    input.emplace_back("INSERT,140,HP,BUY,1.4012,2");
    input.emplace_back("INSERT,141,APPLE,SELL,3.0325,8");
    input.emplace_back("INSERT,142,TESLA,BUY,2.0409,10");
    input.emplace_back("INSERT,143,APPLE,BUY,1.5694,10");
    input.emplace_back("INSERT,144,NOKIA,SELL,1.8145,3");
    input.emplace_back("INSERT,145,NOKIA,SELL,3.7499,9");
    input.emplace_back("INSERT,146,HP,SELL,3.8763,5");
    input.emplace_back("INSERT,147,NOKIA,SELL,2.0024,10");
    input.emplace_back("INSERT,148,APPLE,BUY,3.8994,7");
    input.emplace_back("INSERT,149,NOKIA,BUY,3.0864,6");
    input.emplace_back("INSERT,150,HP,SELL,3.8119,4");
    input.emplace_back("INSERT,151,NOKIA,SELL,1.9316,2");
    input.emplace_back("INSERT,152,HP,SELL,2.418,7");
    input.emplace_back("INSERT,153,APPLE,SELL,3.3444,3");
    input.emplace_back("INSERT,154,TESLA,SELL,1.3116,9");
    input.emplace_back("INSERT,155,MICROSOFT,BUY,3.6566,0");
    input.emplace_back("INSERT,156,CAC40,BUY,3.5151,0");
    input.emplace_back("INSERT,157,CAC40,SELL,3.8721,1");
    input.emplace_back("INSERT,158,TESLA,BUY,3.9875,1");
    input.emplace_back("INSERT,159,TESLA,SELL,1.5074,5");
    input.emplace_back("INSERT,160,ASML,SELL,2.7448,3");
    input.emplace_back("INSERT,161,HP,BUY,1.6596,4");
    input.emplace_back("INSERT,162,APPLE,BUY,2.1911,0");
    input.emplace_back("INSERT,163,HP,SELL,3.2131,7");
    input.emplace_back("INSERT,164,APPLE,SELL,3.2049,4");
    input.emplace_back("INSERT,165,CAC40,SELL,2.4681,3");
    input.emplace_back("INSERT,166,TESLA,SELL,2.1437,1");
    input.emplace_back("INSERT,167,NOKIA,BUY,2.4416,3");
    input.emplace_back("INSERT,168,HP,SELL,1.6152,8");
    input.emplace_back("INSERT,169,MICROSOFT,SELL,1.7979,2");
    input.emplace_back("INSERT,170,CAC40,SELL,2.2745,6");
    input.emplace_back("INSERT,171,CAC40,SELL,2.1345,9");
    input.emplace_back("INSERT,172,APPLE,SELL,2.9193,0");
    input.emplace_back("INSERT,173,ASML,BUY,1.7545,10");
    input.emplace_back("INSERT,174,HP,BUY,2.5044,10");
    input.emplace_back("INSERT,175,APPLE,SELL,1.1406,9");
    input.emplace_back("INSERT,176,HP,BUY,3.5457,0");
    input.emplace_back("INSERT,177,NOKIA,SELL,1.2591,1");
    input.emplace_back("INSERT,178,MICROSOFT,BUY,2.2517,4");
    input.emplace_back("INSERT,179,MICROSOFT,SELL,2.2331,4");
    input.emplace_back("INSERT,180,NOKIA,SELL,3.4501,8");
    input.emplace_back("INSERT,181,MICROSOFT,BUY,1.777,9");
    input.emplace_back("INSERT,182,NOKIA,SELL,3.0116,7");
    input.emplace_back("INSERT,183,MICROSOFT,BUY,3.7465,7");
    input.emplace_back("INSERT,184,TESLA,SELL,1.0022,9");
    input.emplace_back("INSERT,185,APPLE,BUY,1.7421,9");
    input.emplace_back("INSERT,186,ASML,SELL,3.0936,7");
    input.emplace_back("INSERT,187,TESLA,SELL,2.7444,9");
    input.emplace_back("INSERT,188,APPLE,SELL,1.2833,10");
    input.emplace_back("INSERT,189,MICROSOFT,BUY,2.8941,8");
    input.emplace_back("INSERT,190,MICROSOFT,SELL,1.9476,4");
    input.emplace_back("INSERT,191,ASML,SELL,2.0459,9");
    input.emplace_back("INSERT,192,ASML,BUY,2.8792,0");
    input.emplace_back("INSERT,193,MICROSOFT,SELL,3.9724,9");
    input.emplace_back("INSERT,194,APPLE,BUY,2.6833,9");
    input.emplace_back("INSERT,195,ASML,SELL,2.8793,2");
    input.emplace_back("INSERT,196,NOKIA,SELL,2.791,2");
    input.emplace_back("INSERT,197,NOKIA,BUY,1.9476,8");
    input.emplace_back("INSERT,198,APPLE,SELL,2.2812,1");
    input.emplace_back("INSERT,199,APPLE,SELL,3.4511,3");
    input.emplace_back("INSERT,200,MICROSOFT,SELL,1.2083,8");
    input.emplace_back("INSERT,201,MICROSOFT,BUY,3.8068,6");
    input.emplace_back("INSERT,202,APPLE,BUY,3.3105,5");
    input.emplace_back("INSERT,203,CAC40,SELL,3.1699,10");
    input.emplace_back("INSERT,204,MICROSOFT,SELL,1.269,8");
    input.emplace_back("INSERT,205,NOKIA,SELL,2.8324,7");
    input.emplace_back("INSERT,206,NOKIA,SELL,2.4021,2");
    input.emplace_back("INSERT,207,HP,SELL,3.6355,8");
    input.emplace_back("INSERT,208,TESLA,BUY,3.3777,3");
    input.emplace_back("INSERT,209,ASML,SELL,3.4113,10");
    input.emplace_back("INSERT,210,MICROSOFT,SELL,1.7395,2");
    input.emplace_back("INSERT,211,TESLA,SELL,1.5025,2");
    input.emplace_back("INSERT,212,APPLE,BUY,3.2538,3");
    input.emplace_back("INSERT,213,HP,SELL,2.5054,5");
    input.emplace_back("INSERT,214,CAC40,BUY,1.8555,5");
    input.emplace_back("INSERT,215,TESLA,BUY,2.9324,2");
    input.emplace_back("INSERT,216,HP,SELL,3.6647,5");
    input.emplace_back("INSERT,217,ASML,BUY,1.5952,7");
    input.emplace_back("INSERT,218,NOKIA,BUY,3.6305,5");
    input.emplace_back("INSERT,219,HP,BUY,1.5201,2");
    input.emplace_back("INSERT,220,NOKIA,SELL,1.2321,4");
    input.emplace_back("INSERT,221,APPLE,BUY,1.3696,6");
    input.emplace_back("INSERT,222,CAC40,BUY,3.8533,10");
    input.emplace_back("INSERT,223,HP,SELL,1.5518,6");
    input.emplace_back("INSERT,224,MICROSOFT,SELL,2.7203,2");
    input.emplace_back("INSERT,225,APPLE,SELL,3.8917,5");
    input.emplace_back("INSERT,226,NOKIA,BUY,3.2325,6");
    input.emplace_back("INSERT,227,CAC40,SELL,2.1932,6");
    input.emplace_back("INSERT,228,ASML,BUY,3.0547,8");
    input.emplace_back("INSERT,229,ASML,BUY,1.6953,2");
    input.emplace_back("INSERT,230,APPLE,SELL,1.1045,4");
    input.emplace_back("INSERT,231,CAC40,BUY,1.4901,6");
    input.emplace_back("INSERT,232,NOKIA,BUY,1.2152,7");
    input.emplace_back("INSERT,233,HP,SELL,3.6277,1");
    input.emplace_back("INSERT,234,HP,BUY,3.1785,0");
    input.emplace_back("INSERT,235,MICROSOFT,BUY,1.9505,1");
    input.emplace_back("INSERT,236,NOKIA,BUY,1.6975,7");
    input.emplace_back("INSERT,237,TESLA,SELL,2.0221,6");
    input.emplace_back("INSERT,238,MICROSOFT,BUY,2.3823,2");
    input.emplace_back("INSERT,239,TESLA,BUY,2.3829,6");
    input.emplace_back("INSERT,240,CAC40,BUY,1.4967,2");
    input.emplace_back("INSERT,241,NOKIA,SELL,2.6254,3");
    input.emplace_back("INSERT,242,HP,SELL,1.0551,9");
    input.emplace_back("INSERT,243,ASML,BUY,3.4586,8");
    input.emplace_back("INSERT,244,APPLE,SELL,1.3329,0");
    input.emplace_back("INSERT,245,MICROSOFT,SELL,3.1115,10");
    input.emplace_back("INSERT,246,ASML,SELL,3.9123,2");
    input.emplace_back("INSERT,247,APPLE,BUY,1.5786,5");
    input.emplace_back("INSERT,248,NOKIA,BUY,3.6385,3");
    input.emplace_back("INSERT,249,APPLE,SELL,1.8448,1");
    input.emplace_back("INSERT,250,APPLE,SELL,3.2934,2");
    input.emplace_back("INSERT,251,TESLA,SELL,3.2204,6");
    input.emplace_back("INSERT,252,MICROSOFT,SELL,2.6576,8");
    input.emplace_back("INSERT,253,TESLA,SELL,3.7133,4");
    input.emplace_back("INSERT,254,CAC40,SELL,2.3577,2");
    input.emplace_back("INSERT,255,HP,BUY,3.6337,10");
    input.emplace_back("INSERT,256,MICROSOFT,SELL,2.4839,6");
    input.emplace_back("INSERT,257,ASML,SELL,3.7897,7");
    input.emplace_back("INSERT,258,TESLA,BUY,2.4411,3");
    input.emplace_back("INSERT,259,HP,BUY,2.0687,9");
    input.emplace_back("INSERT,260,ASML,SELL,1.5164,1");
    input.emplace_back("INSERT,261,MICROSOFT,SELL,1.4577,10");
    input.emplace_back("INSERT,262,MICROSOFT,SELL,1.5395,7");
    input.emplace_back("INSERT,263,NOKIA,SELL,1.14,2");
    input.emplace_back("INSERT,264,CAC40,SELL,3.0014,9");
    input.emplace_back("INSERT,265,TESLA,SELL,2.1679,7");
    input.emplace_back("INSERT,266,APPLE,SELL,2.3199,7");
    input.emplace_back("INSERT,267,NOKIA,BUY,2.1766,1");
    input.emplace_back("INSERT,268,TESLA,BUY,3.5995,10");
    input.emplace_back("INSERT,269,ASML,SELL,1.7618,1");
    input.emplace_back("INSERT,270,ASML,BUY,2.5676,3");
    input.emplace_back("INSERT,271,ASML,SELL,1.766,2");
    input.emplace_back("INSERT,272,HP,SELL,1.304,2");
    input.emplace_back("INSERT,273,HP,BUY,2.7573,2");
    input.emplace_back("INSERT,274,APPLE,SELL,3.9333,2");
    input.emplace_back("INSERT,275,TESLA,BUY,2.2578,9");
    input.emplace_back("INSERT,276,ASML,SELL,3.6667,4");
    input.emplace_back("INSERT,277,TESLA,BUY,1.5595,0");
    input.emplace_back("INSERT,278,TESLA,BUY,3.1911,10");
    input.emplace_back("INSERT,279,TESLA,BUY,2.839,5");
    input.emplace_back("INSERT,280,MICROSOFT,SELL,3.9233,0");
    input.emplace_back("INSERT,281,HP,BUY,3.286,10");
    input.emplace_back("INSERT,282,ASML,SELL,1.7705,1");
    input.emplace_back("INSERT,283,ASML,BUY,2.5391,10");
    input.emplace_back("INSERT,284,CAC40,BUY,1.8631,6");
    input.emplace_back("INSERT,285,ASML,BUY,2.4035,8");
    input.emplace_back("INSERT,286,MICROSOFT,BUY,3.9807,1");
    input.emplace_back("INSERT,287,APPLE,BUY,1.8042,2");
    input.emplace_back("INSERT,288,TESLA,SELL,2.5988,8");
    input.emplace_back("INSERT,289,MICROSOFT,SELL,1.6631,6");
    input.emplace_back("INSERT,290,ASML,BUY,2.403,10");
    input.emplace_back("INSERT,291,TESLA,SELL,1.3021,6");
    input.emplace_back("INSERT,292,ASML,BUY,2.1105,0");
    input.emplace_back("INSERT,293,CAC40,BUY,2.4334,10");
    input.emplace_back("INSERT,294,APPLE,SELL,3.7731,9");
    input.emplace_back("INSERT,295,CAC40,BUY,3.3236,7");
    input.emplace_back("INSERT,296,ASML,BUY,2.591,7");
    input.emplace_back("INSERT,297,APPLE,SELL,1.3057,0");
    input.emplace_back("INSERT,298,CAC40,SELL,1.2121,10");
    input.emplace_back("INSERT,299,MICROSOFT,BUY,1.7114,3");
    input.emplace_back("INSERT,300,MICROSOFT,SELL,2.2779,3");
    input.emplace_back("INSERT,301,NOKIA,BUY,1.9426,0");
    input.emplace_back("INSERT,302,ASML,SELL,3.5986,3");
    input.emplace_back("INSERT,303,CAC40,BUY,2.5311,6");
    input.emplace_back("INSERT,304,HP,BUY,3.5101,8");
    input.emplace_back("INSERT,305,TESLA,BUY,2.7225,9");
    input.emplace_back("INSERT,306,CAC40,BUY,1.6767,5");
    input.emplace_back("INSERT,307,CAC40,SELL,1.4793,2");
    input.emplace_back("INSERT,308,MICROSOFT,BUY,1.5273,10");
    input.emplace_back("INSERT,309,MICROSOFT,BUY,3.488,9");
    input.emplace_back("INSERT,310,NOKIA,BUY,3.7808,7");
    input.emplace_back("INSERT,311,MICROSOFT,BUY,3.1491,4");
    input.emplace_back("INSERT,312,MICROSOFT,BUY,2.4553,5");
    input.emplace_back("INSERT,313,CAC40,SELL,1.4185,0");
    input.emplace_back("INSERT,314,CAC40,BUY,1.3422,7");
    input.emplace_back("INSERT,315,CAC40,BUY,3.06,0");
    input.emplace_back("INSERT,316,CAC40,SELL,3.758,5");
    input.emplace_back("INSERT,317,MICROSOFT,BUY,1.6868,5");
    input.emplace_back("INSERT,318,MICROSOFT,SELL,1.4417,2");
    input.emplace_back("INSERT,319,ASML,BUY,2.0185,0");
    input.emplace_back("INSERT,320,CAC40,SELL,3.2052,4");
    input.emplace_back("INSERT,321,CAC40,BUY,1.3721,8");
    input.emplace_back("INSERT,322,APPLE,BUY,2.2454,9");
    input.emplace_back("INSERT,323,ASML,BUY,2.6788,3");
    input.emplace_back("INSERT,324,CAC40,BUY,2.3801,3");
    input.emplace_back("INSERT,325,NOKIA,BUY,1.6332,8");
    input.emplace_back("INSERT,326,TESLA,SELL,1.8581,7");
    input.emplace_back("INSERT,327,CAC40,SELL,3.2472,2");
    input.emplace_back("INSERT,328,NOKIA,BUY,1.7266,4");
    input.emplace_back("INSERT,329,APPLE,SELL,1.5636,1");
    input.emplace_back("INSERT,330,NOKIA,SELL,1.7113,4");
    input.emplace_back("INSERT,331,TESLA,BUY,1.0092,6");
    input.emplace_back("INSERT,332,CAC40,BUY,1.2265,6");
    input.emplace_back("INSERT,333,NOKIA,BUY,3.905,5");
    input.emplace_back("INSERT,334,CAC40,SELL,1.0827,8");
    input.emplace_back("INSERT,335,CAC40,BUY,2.1901,6");
    input.emplace_back("INSERT,336,TESLA,BUY,3.5705,8");
    input.emplace_back("INSERT,337,APPLE,SELL,1.2569,6");
    input.emplace_back("INSERT,338,CAC40,BUY,3.793,8");
    input.emplace_back("INSERT,339,APPLE,SELL,1.7209,6");
    input.emplace_back("INSERT,340,ASML,SELL,2.8161,9");
    input.emplace_back("INSERT,341,MICROSOFT,SELL,2.5311,0");
    input.emplace_back("INSERT,342,ASML,SELL,1.8776,5");
    input.emplace_back("INSERT,343,TESLA,BUY,2.3832,4");
    input.emplace_back("INSERT,344,MICROSOFT,BUY,3.7265,7");
    input.emplace_back("INSERT,345,CAC40,SELL,2.5312,8");
    input.emplace_back("INSERT,346,MICROSOFT,BUY,1.617,1");
    input.emplace_back("INSERT,347,APPLE,BUY,1.9512,5");
    input.emplace_back("INSERT,348,CAC40,BUY,2.4775,2");
    input.emplace_back("INSERT,349,NOKIA,SELL,2.535,2");
    input.emplace_back("INSERT,350,TESLA,SELL,2.161,2");
    input.emplace_back("INSERT,351,APPLE,SELL,3.6892,9");
    input.emplace_back("INSERT,352,HP,SELL,3.8905,6");
    input.emplace_back("INSERT,353,ASML,SELL,3.4528,9");
    input.emplace_back("INSERT,354,MICROSOFT,BUY,3.5407,7");
    input.emplace_back("INSERT,355,HP,SELL,1.1383,9");
    input.emplace_back("INSERT,356,HP,SELL,2.1266,2");
    input.emplace_back("INSERT,357,MICROSOFT,BUY,3.0678,4");
    input.emplace_back("INSERT,358,APPLE,SELL,1.2704,6");
    input.emplace_back("INSERT,359,CAC40,SELL,3.8981,1");
    input.emplace_back("INSERT,360,CAC40,BUY,2.4295,7");
    input.emplace_back("INSERT,361,NOKIA,BUY,2.7693,1");
    input.emplace_back("INSERT,362,CAC40,SELL,2.5418,6");
    input.emplace_back("INSERT,363,APPLE,SELL,2.2754,2");
    input.emplace_back("INSERT,364,TESLA,SELL,3.832,4");
    input.emplace_back("INSERT,365,APPLE,SELL,3.7371,8");
    input.emplace_back("INSERT,366,TESLA,BUY,2.6338,2");
    input.emplace_back("INSERT,367,ASML,SELL,2.7948,5");
    input.emplace_back("INSERT,368,NOKIA,BUY,2.3501,3");
    input.emplace_back("INSERT,369,NOKIA,SELL,3.3461,10");
    input.emplace_back("INSERT,370,ASML,SELL,3.4733,7");
    input.emplace_back("INSERT,371,CAC40,BUY,2.0779,4");
    input.emplace_back("INSERT,372,ASML,BUY,2.0817,0");
    input.emplace_back("INSERT,373,APPLE,BUY,3.5798,6");
    input.emplace_back("INSERT,374,HP,SELL,2.4826,5");
    input.emplace_back("INSERT,375,NOKIA,BUY,2.2602,0");
    input.emplace_back("INSERT,376,TESLA,BUY,1.8187,1");
    input.emplace_back("INSERT,377,TESLA,SELL,1.8572,5");
    input.emplace_back("INSERT,378,NOKIA,SELL,3.0862,10");
    input.emplace_back("INSERT,379,NOKIA,BUY,3.1291,8");
    input.emplace_back("INSERT,380,TESLA,BUY,1.022,8");
    input.emplace_back("INSERT,381,CAC40,BUY,1.1019,4");
    input.emplace_back("INSERT,382,MICROSOFT,BUY,2.8637,9");
    input.emplace_back("INSERT,383,CAC40,BUY,1.306,9");
    input.emplace_back("INSERT,384,MICROSOFT,BUY,1.135,2");
    input.emplace_back("INSERT,385,NOKIA,SELL,3.3271,2");
    input.emplace_back("INSERT,386,TESLA,BUY,3.5262,9");
    input.emplace_back("INSERT,387,MICROSOFT,BUY,2.4141,4");
    input.emplace_back("INSERT,388,APPLE,BUY,1.9786,6");
    input.emplace_back("INSERT,389,MICROSOFT,SELL,1.3934,4");
    input.emplace_back("INSERT,390,HP,SELL,1.2823,3");
    input.emplace_back("INSERT,391,HP,BUY,3.8123,0");
    input.emplace_back("INSERT,392,MICROSOFT,SELL,3.5493,0");
    input.emplace_back("INSERT,393,HP,SELL,1.5472,0");
    input.emplace_back("INSERT,394,NOKIA,SELL,2.8579,8");
    input.emplace_back("INSERT,395,APPLE,BUY,3.2991,8");
    input.emplace_back("INSERT,396,MICROSOFT,BUY,1.0265,3");
    input.emplace_back("INSERT,397,HP,SELL,2.5958,2");
    input.emplace_back("INSERT,398,CAC40,BUY,2.1309,1");
    input.emplace_back("INSERT,399,CAC40,SELL,3.1809,8");
    input.emplace_back("INSERT,400,ASML,SELL,1.7527,6");
    input.emplace_back("INSERT,401,HP,SELL,2.6689,3");
    input.emplace_back("INSERT,402,MICROSOFT,SELL,3.5248,9");
    input.emplace_back("INSERT,403,MICROSOFT,BUY,1.5198,10");
    input.emplace_back("INSERT,404,TESLA,BUY,1.866,10");
    input.emplace_back("INSERT,405,APPLE,BUY,2.9061,2");
    input.emplace_back("INSERT,406,CAC40,SELL,2.1846,0");
    input.emplace_back("INSERT,407,ASML,BUY,1.3033,8");
    input.emplace_back("INSERT,408,APPLE,SELL,3.5759,4");
    input.emplace_back("INSERT,409,ASML,SELL,1.0736,1");
    input.emplace_back("INSERT,410,APPLE,SELL,1.1571,4");
    input.emplace_back("INSERT,411,HP,BUY,1.9465,8");
    input.emplace_back("INSERT,412,MICROSOFT,SELL,1.7309,1");
    input.emplace_back("INSERT,413,CAC40,BUY,1.1609,3");
    input.emplace_back("INSERT,414,ASML,SELL,3.1011,3");
    input.emplace_back("INSERT,415,NOKIA,BUY,3.8134,1");
    input.emplace_back("INSERT,416,HP,BUY,3.4258,4");
    input.emplace_back("INSERT,417,MICROSOFT,SELL,3.3866,3");
    input.emplace_back("INSERT,418,TESLA,BUY,2.3502,9");
    input.emplace_back("INSERT,419,CAC40,BUY,2.3956,2");
    input.emplace_back("INSERT,420,MICROSOFT,BUY,3.3865,9");
    input.emplace_back("INSERT,421,HP,SELL,1.9035,8");
    input.emplace_back("INSERT,422,NOKIA,BUY,2.6271,8");
    input.emplace_back("INSERT,423,ASML,SELL,1.7708,6");
    input.emplace_back("INSERT,424,HP,SELL,2.557,9");
    input.emplace_back("INSERT,425,NOKIA,SELL,1.5598,4");
    input.emplace_back("INSERT,426,APPLE,SELL,3.1602,0");
    input.emplace_back("INSERT,427,ASML,SELL,2.3802,8");
    input.emplace_back("INSERT,428,APPLE,BUY,2.5279,3");
    input.emplace_back("INSERT,429,NOKIA,BUY,1.5644,0");
    input.emplace_back("INSERT,430,TESLA,SELL,1.7772,2");
    input.emplace_back("INSERT,431,ASML,BUY,1.8529,10");
    input.emplace_back("INSERT,432,NOKIA,SELL,2.6651,0");
    input.emplace_back("INSERT,433,HP,SELL,1.441,7");
    input.emplace_back("INSERT,434,ASML,SELL,1.5855,6");
    input.emplace_back("INSERT,435,TESLA,SELL,3.3103,0");
    input.emplace_back("INSERT,436,APPLE,BUY,1.8894,6");
    input.emplace_back("INSERT,437,CAC40,BUY,1.7613,8");
    input.emplace_back("INSERT,438,CAC40,SELL,1.8809,4");
    input.emplace_back("INSERT,439,NOKIA,BUY,1.202,7");
    input.emplace_back("INSERT,440,CAC40,SELL,2.4888,9");
    input.emplace_back("INSERT,441,HP,SELL,2.7738,8");
    input.emplace_back("INSERT,442,NOKIA,SELL,1.424,7");
    input.emplace_back("INSERT,443,MICROSOFT,BUY,3.0258,1");
    input.emplace_back("INSERT,444,ASML,SELL,1.9113,0");
    input.emplace_back("INSERT,445,HP,SELL,3.3476,0");
    input.emplace_back("INSERT,446,HP,SELL,3.2217,8");
    input.emplace_back("INSERT,447,ASML,SELL,3.6101,3");
    input.emplace_back("INSERT,448,ASML,BUY,2.9415,3");
    input.emplace_back("INSERT,449,MICROSOFT,BUY,2.983,7");
    input.emplace_back("INSERT,450,ASML,BUY,1.54,7");
    input.emplace_back("INSERT,451,TESLA,SELL,3.7377,10");
    input.emplace_back("INSERT,452,HP,BUY,3.9484,9");
    input.emplace_back("INSERT,453,MICROSOFT,SELL,2.3711,2");
    input.emplace_back("INSERT,454,MICROSOFT,BUY,3.7011,1");
    input.emplace_back("INSERT,455,ASML,SELL,3.9748,7");
    input.emplace_back("INSERT,456,MICROSOFT,BUY,3.753,2");
    input.emplace_back("INSERT,457,APPLE,BUY,1.0248,7");
    input.emplace_back("INSERT,458,MICROSOFT,SELL,3.9105,6");
    input.emplace_back("INSERT,459,NOKIA,SELL,3.5313,8");
    input.emplace_back("INSERT,460,MICROSOFT,SELL,2.4228,3");
    input.emplace_back("INSERT,461,NOKIA,BUY,1.3767,1");
    input.emplace_back("INSERT,462,HP,SELL,1.7467,5");
    input.emplace_back("INSERT,463,HP,SELL,1.1384,0");
    input.emplace_back("INSERT,464,ASML,SELL,1.4848,4");
    input.emplace_back("INSERT,465,APPLE,SELL,1.2384,6");
    input.emplace_back("INSERT,466,MICROSOFT,SELL,1.2522,10");
    input.emplace_back("INSERT,467,NOKIA,BUY,2.1403,2");
    input.emplace_back("INSERT,468,HP,SELL,1.5391,7");
    input.emplace_back("INSERT,469,HP,BUY,3.1597,9");
    input.emplace_back("INSERT,470,CAC40,BUY,3.7125,0");
    input.emplace_back("INSERT,471,MICROSOFT,SELL,3.6657,1");
    input.emplace_back("INSERT,472,NOKIA,SELL,2.0469,5");
    input.emplace_back("INSERT,473,MICROSOFT,BUY,2.6646,6");
    input.emplace_back("INSERT,474,MICROSOFT,BUY,3.7022,0");
    input.emplace_back("INSERT,475,MICROSOFT,SELL,3.2247,1");
    input.emplace_back("INSERT,476,NOKIA,SELL,2.2471,5");
    input.emplace_back("INSERT,477,ASML,BUY,3.8444,9");
    input.emplace_back("INSERT,478,APPLE,BUY,2.1469,2");
    input.emplace_back("INSERT,479,MICROSOFT,SELL,3.3587,0");
    input.emplace_back("INSERT,480,ASML,BUY,3.6941,9");
    input.emplace_back("INSERT,481,APPLE,BUY,3.3025,8");
    input.emplace_back("INSERT,482,NOKIA,BUY,1.3674,2");
    input.emplace_back("INSERT,483,ASML,SELL,1.523,4");
    input.emplace_back("INSERT,484,HP,SELL,3.2342,1");
    input.emplace_back("INSERT,485,APPLE,SELL,3.7291,8");
    input.emplace_back("INSERT,486,HP,SELL,1.0341,6");
    input.emplace_back("INSERT,487,TESLA,SELL,2.2058,3");
    input.emplace_back("INSERT,488,ASML,BUY,2.7247,10");
    input.emplace_back("INSERT,489,HP,BUY,2.8397,4");
    input.emplace_back("INSERT,490,TESLA,SELL,2.2458,7");
    input.emplace_back("INSERT,491,NOKIA,BUY,3.2057,7");
    input.emplace_back("INSERT,492,APPLE,SELL,1.341,4");
    input.emplace_back("INSERT,493,TESLA,BUY,2.007,5");
    input.emplace_back("INSERT,494,NOKIA,BUY,3.4736,8");
    input.emplace_back("INSERT,495,TESLA,BUY,2.0268,0");
    input.emplace_back("INSERT,496,APPLE,SELL,3.4106,9");
    input.emplace_back("INSERT,497,ASML,SELL,3.1408,0");
    input.emplace_back("INSERT,498,ASML,SELL,2.4992,2");
    input.emplace_back("INSERT,499,NOKIA,SELL,3.6045,5");
    input.emplace_back("INSERT,500,ASML,SELL,2.3061,6");
    input.emplace_back("INSERT,501,APPLE,SELL,2.2295,2");
    input.emplace_back("INSERT,502,CAC40,SELL,1.8851,9");
    input.emplace_back("INSERT,503,NOKIA,SELL,2.7888,10");
    input.emplace_back("INSERT,504,CAC40,SELL,3.6152,6");
    input.emplace_back("INSERT,505,APPLE,SELL,3.044,4");
    input.emplace_back("INSERT,506,TESLA,BUY,3.068,9");
    input.emplace_back("INSERT,507,TESLA,BUY,2.274,4");
    input.emplace_back("INSERT,508,NOKIA,SELL,2.1313,5");
    input.emplace_back("INSERT,509,ASML,BUY,1.3438,8");
    input.emplace_back("INSERT,510,MICROSOFT,SELL,3.0011,9");
    input.emplace_back("INSERT,511,TESLA,BUY,3.2111,0");
    input.emplace_back("INSERT,512,APPLE,BUY,2.6921,1");
    input.emplace_back("INSERT,513,APPLE,SELL,1.2994,0");
    input.emplace_back("INSERT,514,HP,SELL,3.2421,4");
    input.emplace_back("INSERT,515,ASML,SELL,2.8554,7");
    input.emplace_back("INSERT,516,NOKIA,BUY,2.8631,9");
    input.emplace_back("INSERT,517,NOKIA,BUY,1.2067,8");
    input.emplace_back("INSERT,518,ASML,SELL,2.9481,4");
    input.emplace_back("INSERT,519,TESLA,BUY,3.9297,7");
    input.emplace_back("INSERT,520,NOKIA,SELL,2.2464,9");
    input.emplace_back("INSERT,521,NOKIA,SELL,2.4008,8");
    input.emplace_back("INSERT,522,CAC40,BUY,2.7355,6");
    input.emplace_back("INSERT,523,TESLA,SELL,1.2512,4");
    input.emplace_back("INSERT,524,APPLE,SELL,3.7385,6");
    input.emplace_back("INSERT,525,HP,BUY,1.2559,7");
    input.emplace_back("INSERT,526,MICROSOFT,BUY,3.6143,5");
    input.emplace_back("INSERT,527,NOKIA,SELL,3.3799,3");
    input.emplace_back("INSERT,528,NOKIA,SELL,1.2676,10");
    input.emplace_back("INSERT,529,MICROSOFT,BUY,1.947,0");
    input.emplace_back("INSERT,530,APPLE,SELL,1.6003,6");
    input.emplace_back("INSERT,531,NOKIA,BUY,3.0573,6");
    input.emplace_back("INSERT,532,ASML,SELL,1.8417,5");
    input.emplace_back("INSERT,533,MICROSOFT,SELL,3.7414,1");
    input.emplace_back("INSERT,534,MICROSOFT,BUY,1.8809,5");
    input.emplace_back("INSERT,535,NOKIA,SELL,3.2543,1");
    input.emplace_back("INSERT,536,NOKIA,SELL,3.2537,5");
    input.emplace_back("INSERT,537,APPLE,SELL,1.9594,7");
    input.emplace_back("INSERT,538,MICROSOFT,BUY,1.2361,1");
    input.emplace_back("INSERT,539,HP,BUY,3.9531,7");
    input.emplace_back("INSERT,540,MICROSOFT,SELL,1.1999,2");
    input.emplace_back("INSERT,541,TESLA,BUY,2.7136,7");
    input.emplace_back("INSERT,542,ASML,SELL,3.2816,9");
    input.emplace_back("INSERT,543,ASML,BUY,2.371,5");
    input.emplace_back("INSERT,544,HP,BUY,3.2509,8");
    input.emplace_back("INSERT,545,CAC40,BUY,2.8662,1");
    input.emplace_back("INSERT,546,NOKIA,BUY,1.3394,0");
    input.emplace_back("INSERT,547,CAC40,BUY,1.2647,8");
    input.emplace_back("INSERT,548,MICROSOFT,SELL,3.811,4");
    input.emplace_back("INSERT,549,MICROSOFT,SELL,2.9259,3");
    input.emplace_back("INSERT,550,HP,SELL,3.0529,3");
    input.emplace_back("INSERT,551,CAC40,SELL,2.4383,5");
    input.emplace_back("INSERT,552,TESLA,BUY,1.5759,8");
    input.emplace_back("INSERT,553,TESLA,BUY,2.3776,8");
    input.emplace_back("INSERT,554,HP,SELL,1.3391,4");
    input.emplace_back("INSERT,555,HP,SELL,1.4941,6");
    input.emplace_back("INSERT,556,ASML,BUY,1.0676,2");
    input.emplace_back("INSERT,557,HP,BUY,1.5577,4");
    input.emplace_back("INSERT,558,MICROSOFT,BUY,3.6263,1");
    input.emplace_back("INSERT,559,APPLE,BUY,3.4006,8");
    input.emplace_back("INSERT,560,CAC40,BUY,2.2062,3");
    input.emplace_back("INSERT,561,CAC40,BUY,1.8745,7");
    input.emplace_back("INSERT,562,APPLE,BUY,2.1775,6");
    input.emplace_back("INSERT,563,APPLE,SELL,1.8852,4");
    input.emplace_back("INSERT,564,HP,SELL,2.052,0");
    input.emplace_back("INSERT,565,CAC40,BUY,3.3213,9");
    input.emplace_back("INSERT,566,TESLA,BUY,1.7532,0");
    input.emplace_back("INSERT,567,TESLA,BUY,1.9018,2");
    input.emplace_back("INSERT,568,TESLA,SELL,2.2619,5");
    input.emplace_back("INSERT,569,CAC40,SELL,1.3378,6");
    input.emplace_back("INSERT,570,MICROSOFT,SELL,3.886,1");
    input.emplace_back("INSERT,571,CAC40,BUY,3.6407,4");
    input.emplace_back("INSERT,572,NOKIA,SELL,3.5113,8");
    input.emplace_back("INSERT,573,NOKIA,SELL,3.1452,5");
    input.emplace_back("INSERT,574,APPLE,SELL,1.0661,6");
    input.emplace_back("INSERT,575,MICROSOFT,SELL,2.1915,8");
    input.emplace_back("INSERT,576,NOKIA,BUY,3.9836,5");
    input.emplace_back("INSERT,577,CAC40,SELL,3.6206,7");
    input.emplace_back("INSERT,578,CAC40,BUY,1.3551,1");
    input.emplace_back("INSERT,579,MICROSOFT,SELL,3.8402,1");
    input.emplace_back("INSERT,580,ASML,SELL,3.0466,7");
    input.emplace_back("INSERT,581,HP,BUY,3.7078,1");
    input.emplace_back("INSERT,582,HP,BUY,3.6868,10");
    input.emplace_back("INSERT,583,NOKIA,SELL,3.1424,6");
    input.emplace_back("INSERT,584,APPLE,SELL,1.7262,7");
    input.emplace_back("INSERT,585,HP,BUY,2.4364,5");
    input.emplace_back("INSERT,586,HP,SELL,1.4898,4");
    input.emplace_back("INSERT,587,NOKIA,BUY,3.9725,2");
    input.emplace_back("INSERT,588,MICROSOFT,BUY,3.2948,3");
    input.emplace_back("INSERT,589,ASML,SELL,3.9119,4");
    input.emplace_back("INSERT,590,HP,BUY,3.0012,10");
    input.emplace_back("INSERT,591,APPLE,SELL,1.7018,9");
    input.emplace_back("INSERT,592,CAC40,BUY,3.6908,3");
    input.emplace_back("INSERT,593,HP,BUY,3.6661,6");
    input.emplace_back("INSERT,594,NOKIA,SELL,1.1978,5");
    input.emplace_back("INSERT,595,MICROSOFT,BUY,1.4702,0");
    input.emplace_back("INSERT,596,TESLA,BUY,2.8227,6");
    input.emplace_back("INSERT,597,MICROSOFT,SELL,2.5826,3");
    input.emplace_back("INSERT,598,MICROSOFT,SELL,2.3882,8");
    input.emplace_back("INSERT,599,CAC40,SELL,1.4277,5");
    input.emplace_back("INSERT,600,HP,BUY,3.5228,7");
    input.emplace_back("INSERT,601,CAC40,SELL,2.1379,0");
    input.emplace_back("INSERT,602,CAC40,BUY,1.5543,6");
    input.emplace_back("INSERT,603,HP,BUY,1.3078,5");
    input.emplace_back("INSERT,604,APPLE,SELL,3.8545,9");
    input.emplace_back("INSERT,605,HP,SELL,1.0816,5");
    input.emplace_back("INSERT,606,NOKIA,BUY,1.814,2");
    input.emplace_back("INSERT,607,NOKIA,BUY,1.6197,10");
    input.emplace_back("INSERT,608,HP,SELL,2.7997,8");
    input.emplace_back("INSERT,609,APPLE,BUY,3.432,1");
    input.emplace_back("INSERT,610,APPLE,SELL,3.6102,6");
    input.emplace_back("INSERT,611,MICROSOFT,BUY,2.5611,2");
    input.emplace_back("INSERT,612,APPLE,BUY,3.9592,5");
    input.emplace_back("INSERT,613,ASML,BUY,3.41,2");
    input.emplace_back("INSERT,614,TESLA,SELL,2.0187,6");
    input.emplace_back("INSERT,615,ASML,BUY,1.3981,8");
    input.emplace_back("INSERT,616,MICROSOFT,SELL,3.0473,6");
    input.emplace_back("INSERT,617,MICROSOFT,SELL,2.763,3");
    input.emplace_back("INSERT,618,TESLA,BUY,1.8024,1");
    input.emplace_back("INSERT,619,TESLA,BUY,2.6652,9");
    input.emplace_back("INSERT,620,CAC40,SELL,1.2477,4");
    input.emplace_back("INSERT,621,ASML,BUY,2.4181,1");
    input.emplace_back("INSERT,622,ASML,SELL,1.1216,9");
    input.emplace_back("INSERT,623,MICROSOFT,BUY,2.0279,4");
    input.emplace_back("INSERT,624,TESLA,SELL,1.8883,9");
    input.emplace_back("INSERT,625,ASML,SELL,3.3536,6");
    input.emplace_back("INSERT,626,NOKIA,BUY,3.7375,10");
    input.emplace_back("INSERT,627,TESLA,SELL,3.6107,10");
    input.emplace_back("INSERT,628,ASML,BUY,2.9047,0");
    input.emplace_back("INSERT,629,APPLE,SELL,2.1068,5");
    input.emplace_back("INSERT,630,CAC40,SELL,1.0224,3");
    input.emplace_back("INSERT,631,ASML,BUY,3.8509,9");
    input.emplace_back("INSERT,632,ASML,BUY,2.9723,0");
    input.emplace_back("INSERT,633,MICROSOFT,BUY,3.7227,1");
    input.emplace_back("INSERT,634,TESLA,BUY,3.2587,2");
    input.emplace_back("INSERT,635,ASML,SELL,3.8389,6");
    input.emplace_back("INSERT,636,HP,SELL,3.0758,10");
    input.emplace_back("INSERT,637,TESLA,BUY,1.6476,4");
    input.emplace_back("INSERT,638,HP,BUY,3.2117,6");
    input.emplace_back("INSERT,639,TESLA,BUY,1.6424,3");
    input.emplace_back("INSERT,640,ASML,SELL,2.5794,10");
    input.emplace_back("INSERT,641,APPLE,SELL,2.1662,2");
    input.emplace_back("INSERT,642,NOKIA,SELL,1.8507,9");
    input.emplace_back("INSERT,643,CAC40,SELL,3.5996,10");
    input.emplace_back("INSERT,644,HP,SELL,2.9543,7");
    input.emplace_back("INSERT,645,NOKIA,BUY,3.4087,3");
    input.emplace_back("INSERT,646,CAC40,SELL,2.0606,3");
    input.emplace_back("INSERT,647,CAC40,BUY,2.5819,5");
    input.emplace_back("INSERT,648,CAC40,SELL,1.8038,8");
    input.emplace_back("INSERT,649,CAC40,BUY,1.3498,8");
    input.emplace_back("INSERT,650,HP,SELL,1.6274,8");
    input.emplace_back("INSERT,651,NOKIA,SELL,1.6517,9");
    input.emplace_back("INSERT,652,NOKIA,BUY,1.8076,8");
    input.emplace_back("INSERT,653,HP,SELL,2.0737,3");
    input.emplace_back("INSERT,654,HP,SELL,2.5832,5");
    input.emplace_back("INSERT,655,CAC40,SELL,1.8323,0");
    input.emplace_back("INSERT,656,TESLA,SELL,3.2057,0");
    input.emplace_back("INSERT,657,TESLA,SELL,1.1893,5");
    input.emplace_back("INSERT,658,CAC40,SELL,3.1081,7");
    input.emplace_back("INSERT,659,ASML,SELL,1.1366,6");
    input.emplace_back("INSERT,660,NOKIA,BUY,3.3161,9");
    input.emplace_back("INSERT,661,MICROSOFT,SELL,1.7914,0");
    input.emplace_back("INSERT,662,ASML,BUY,3.8116,7");
    input.emplace_back("INSERT,663,TESLA,SELL,3.1598,6");
    input.emplace_back("INSERT,664,TESLA,SELL,1.3324,1");
    input.emplace_back("INSERT,665,CAC40,SELL,3.0805,8");
    input.emplace_back("INSERT,666,APPLE,BUY,1.7442,6");
    input.emplace_back("INSERT,667,TESLA,SELL,2.9861,8");
    input.emplace_back("INSERT,668,TESLA,SELL,1.4037,6");
    input.emplace_back("INSERT,669,ASML,BUY,1.3986,5");
    input.emplace_back("INSERT,670,MICROSOFT,SELL,2.8499,5");
    input.emplace_back("INSERT,671,MICROSOFT,SELL,2.0452,2");
    input.emplace_back("INSERT,672,MICROSOFT,SELL,3.4095,2");
    input.emplace_back("INSERT,673,APPLE,SELL,2.4704,0");
    input.emplace_back("INSERT,674,MICROSOFT,BUY,1.9992,10");
    input.emplace_back("INSERT,675,APPLE,BUY,3.8124,0");
    input.emplace_back("INSERT,676,MICROSOFT,SELL,2.4682,5");
    input.emplace_back("INSERT,677,APPLE,BUY,1.6799,9");
    input.emplace_back("INSERT,678,CAC40,SELL,2.0868,6");
    input.emplace_back("INSERT,679,CAC40,BUY,3.7678,10");
    input.emplace_back("INSERT,680,TESLA,BUY,3.0732,8");
    input.emplace_back("INSERT,681,MICROSOFT,BUY,1.6682,0");
    input.emplace_back("INSERT,682,CAC40,BUY,1.1716,8");
    input.emplace_back("INSERT,683,NOKIA,SELL,2.0389,8");
    input.emplace_back("INSERT,684,HP,BUY,2.9108,6");
    input.emplace_back("INSERT,685,NOKIA,SELL,3.3658,6");
    input.emplace_back("INSERT,686,CAC40,BUY,3.6142,5");
    input.emplace_back("INSERT,687,NOKIA,SELL,3.3087,3");
    input.emplace_back("INSERT,688,CAC40,SELL,1.2214,9");
    input.emplace_back("INSERT,689,APPLE,BUY,1.7963,7");
    input.emplace_back("INSERT,690,APPLE,BUY,3.1683,4");
    input.emplace_back("INSERT,691,CAC40,SELL,1.0739,5");
    input.emplace_back("INSERT,692,NOKIA,SELL,1.9861,4");
    input.emplace_back("INSERT,693,NOKIA,SELL,3.2816,7");
    input.emplace_back("INSERT,694,HP,BUY,1.7317,1");
    input.emplace_back("INSERT,695,MICROSOFT,SELL,3.8563,2");
    input.emplace_back("INSERT,696,MICROSOFT,SELL,1.1532,9");
    input.emplace_back("INSERT,697,TESLA,BUY,1.7055,9");
    input.emplace_back("INSERT,698,ASML,BUY,2.5434,2");
    input.emplace_back("INSERT,699,CAC40,SELL,3.7889,6");
    input.emplace_back("INSERT,700,CAC40,BUY,1.5132,1");
    input.emplace_back("INSERT,701,TESLA,SELL,2.1753,5");
    input.emplace_back("INSERT,702,HP,SELL,3.3201,3");
    input.emplace_back("INSERT,703,APPLE,SELL,1.4517,6");
    input.emplace_back("INSERT,704,NOKIA,SELL,2.4806,7");
    input.emplace_back("INSERT,705,TESLA,SELL,1.6084,5");
    input.emplace_back("INSERT,706,MICROSOFT,BUY,1.7608,5");
    input.emplace_back("INSERT,707,TESLA,SELL,3.0553,6");
    input.emplace_back("INSERT,708,CAC40,SELL,2.6061,8");
    input.emplace_back("INSERT,709,NOKIA,BUY,2.8085,5");
    input.emplace_back("INSERT,710,CAC40,SELL,3.7205,3");
    input.emplace_back("INSERT,711,APPLE,SELL,3.3951,7");
    input.emplace_back("INSERT,712,TESLA,BUY,2.0529,0");
    input.emplace_back("INSERT,713,NOKIA,BUY,1.7883,2");
    input.emplace_back("INSERT,714,TESLA,BUY,1.7055,10");
    input.emplace_back("INSERT,715,MICROSOFT,BUY,3.8347,10");
    input.emplace_back("INSERT,716,APPLE,BUY,1.8114,1");
    input.emplace_back("INSERT,717,CAC40,SELL,2.5769,6");
    input.emplace_back("INSERT,718,NOKIA,BUY,3.8756,5");
    input.emplace_back("INSERT,719,HP,BUY,3.2919,6");
    input.emplace_back("INSERT,720,HP,SELL,3.2675,2");
    input.emplace_back("INSERT,721,MICROSOFT,BUY,2.9865,4");
    input.emplace_back("INSERT,722,TESLA,BUY,2.4385,1");
    input.emplace_back("INSERT,723,ASML,SELL,2.3063,6");
    input.emplace_back("INSERT,724,ASML,SELL,1.6848,4");
    input.emplace_back("INSERT,725,HP,SELL,2.0113,2");
    input.emplace_back("INSERT,726,APPLE,SELL,3.7494,4");
    input.emplace_back("INSERT,727,MICROSOFT,BUY,3.8312,7");
    input.emplace_back("INSERT,728,MICROSOFT,SELL,2.7534,7");
    input.emplace_back("INSERT,729,APPLE,SELL,3.4373,10");
    input.emplace_back("INSERT,730,HP,BUY,1.8245,9");
    input.emplace_back("INSERT,731,HP,BUY,1.3496,9");
    input.emplace_back("INSERT,732,ASML,SELL,2.0162,4");
    input.emplace_back("INSERT,733,ASML,SELL,1.07,1");
    input.emplace_back("INSERT,734,APPLE,BUY,3.9014,7");
    input.emplace_back("INSERT,735,TESLA,SELL,1.3968,4");
    input.emplace_back("INSERT,736,MICROSOFT,BUY,2.2649,4");
    input.emplace_back("INSERT,737,TESLA,BUY,3.3749,7");
    input.emplace_back("INSERT,738,TESLA,SELL,2.6695,6");
    input.emplace_back("INSERT,739,APPLE,BUY,2.1654,3");
    input.emplace_back("INSERT,740,HP,BUY,2.0906,9");
    input.emplace_back("INSERT,741,MICROSOFT,BUY,2.9953,1");
    input.emplace_back("INSERT,742,ASML,BUY,1.7687,0");
    input.emplace_back("INSERT,743,TESLA,BUY,2.1343,8");
    input.emplace_back("INSERT,744,APPLE,SELL,1.5883,10");
    input.emplace_back("INSERT,745,MICROSOFT,SELL,1.25,2");
    input.emplace_back("INSERT,746,APPLE,SELL,2.1166,5");
    input.emplace_back("INSERT,747,TESLA,SELL,1.2814,4");
    input.emplace_back("INSERT,748,CAC40,BUY,2.5874,9");
    input.emplace_back("INSERT,749,HP,BUY,3.4225,0");
    input.emplace_back("INSERT,750,MICROSOFT,SELL,3.8526,6");
    input.emplace_back("INSERT,751,MICROSOFT,BUY,2.1357,4");
    input.emplace_back("INSERT,752,CAC40,SELL,2.3619,0");
    input.emplace_back("INSERT,753,HP,BUY,2.2672,9");
    input.emplace_back("INSERT,754,NOKIA,BUY,1.7174,4");
    input.emplace_back("INSERT,755,APPLE,BUY,1.625,8");
    input.emplace_back("INSERT,756,MICROSOFT,SELL,2.5017,9");
    input.emplace_back("INSERT,757,NOKIA,BUY,2.2415,8");
    input.emplace_back("INSERT,758,CAC40,SELL,2.4959,0");
    input.emplace_back("INSERT,759,MICROSOFT,BUY,3.0148,0");
    input.emplace_back("INSERT,760,HP,BUY,1.6381,9");
    input.emplace_back("INSERT,761,MICROSOFT,BUY,2.5595,0");
    input.emplace_back("INSERT,762,MICROSOFT,SELL,3.6859,1");
    input.emplace_back("INSERT,763,ASML,BUY,2.1481,10");
    input.emplace_back("INSERT,764,NOKIA,SELL,3.1777,5");
    input.emplace_back("INSERT,765,ASML,BUY,2.3601,2");
    input.emplace_back("INSERT,766,MICROSOFT,SELL,3.8259,1");
    input.emplace_back("INSERT,767,NOKIA,BUY,3.9369,0");
    input.emplace_back("INSERT,768,HP,BUY,3.766,10");
    input.emplace_back("INSERT,769,APPLE,SELL,3.9511,7");
    input.emplace_back("INSERT,770,CAC40,BUY,3.7134,7");
    input.emplace_back("INSERT,771,ASML,SELL,3.9637,9");
    input.emplace_back("INSERT,772,CAC40,BUY,1.8546,7");
    input.emplace_back("INSERT,773,CAC40,SELL,1.1822,6");
    input.emplace_back("INSERT,774,MICROSOFT,BUY,2.7836,1");
    input.emplace_back("INSERT,775,NOKIA,BUY,2.4788,2");
    input.emplace_back("INSERT,776,MICROSOFT,BUY,2.5205,2");
    input.emplace_back("INSERT,777,TESLA,BUY,3.2603,2");
    input.emplace_back("INSERT,778,NOKIA,BUY,1.7397,4");
    input.emplace_back("INSERT,779,TESLA,BUY,3.2454,10");
    input.emplace_back("INSERT,780,TESLA,SELL,3.7879,2");
    input.emplace_back("INSERT,781,APPLE,BUY,3.8493,0");
    input.emplace_back("INSERT,782,CAC40,SELL,1.8747,10");
    input.emplace_back("INSERT,783,CAC40,BUY,2.6007,3");
    input.emplace_back("INSERT,784,TESLA,BUY,2.4728,5");
    input.emplace_back("INSERT,785,NOKIA,BUY,2.9751,9");
    input.emplace_back("INSERT,786,MICROSOFT,SELL,3.4482,4");
    input.emplace_back("INSERT,787,HP,SELL,1.1452,9");
    input.emplace_back("INSERT,788,HP,BUY,2.0457,3");
    input.emplace_back("INSERT,789,APPLE,SELL,3.2442,2");
    input.emplace_back("INSERT,790,TESLA,BUY,3.5169,6");
    input.emplace_back("INSERT,791,HP,SELL,1.9621,8");
    input.emplace_back("INSERT,792,HP,SELL,2.6277,10");
    input.emplace_back("INSERT,793,HP,BUY,1.3697,2");
    input.emplace_back("INSERT,794,HP,BUY,2.7633,3");
    input.emplace_back("INSERT,795,ASML,BUY,2.5172,6");
    input.emplace_back("INSERT,796,MICROSOFT,BUY,3.0762,2");
    input.emplace_back("INSERT,797,ASML,BUY,1.6685,7");
    input.emplace_back("INSERT,798,APPLE,BUY,3.3319,9");
    input.emplace_back("INSERT,799,MICROSOFT,SELL,2.1766,10");
    input.emplace_back("INSERT,800,APPLE,SELL,1.7665,2");
    input.emplace_back("INSERT,801,APPLE,BUY,2.4139,8");
    input.emplace_back("INSERT,802,NOKIA,BUY,3.4495,3");
    input.emplace_back("INSERT,803,HP,SELL,1.2195,5");
    input.emplace_back("INSERT,804,CAC40,BUY,1.5693,1");
    input.emplace_back("INSERT,805,NOKIA,SELL,1.7633,8");
    input.emplace_back("INSERT,806,APPLE,SELL,3.2234,4");
    input.emplace_back("INSERT,807,ASML,BUY,3.6108,1");
    input.emplace_back("INSERT,808,NOKIA,BUY,1.9287,2");
    input.emplace_back("INSERT,809,TESLA,SELL,3.5161,0");
    input.emplace_back("INSERT,810,NOKIA,SELL,1.3408,2");
    input.emplace_back("INSERT,811,TESLA,BUY,3.723,6");
    input.emplace_back("INSERT,812,HP,SELL,1.2093,4");
    input.emplace_back("INSERT,813,MICROSOFT,SELL,1.4858,6");
    input.emplace_back("INSERT,814,MICROSOFT,BUY,3.9884,9");
    input.emplace_back("INSERT,815,CAC40,BUY,2.3259,4");
    input.emplace_back("INSERT,816,TESLA,SELL,1.1689,6");
    input.emplace_back("INSERT,817,MICROSOFT,BUY,3.9492,8");
    input.emplace_back("INSERT,818,MICROSOFT,SELL,2.6622,7");
    input.emplace_back("INSERT,819,TESLA,BUY,1.0789,2");
    input.emplace_back("INSERT,820,NOKIA,BUY,1.3824,1");
    input.emplace_back("INSERT,821,APPLE,BUY,2.3833,6");
    input.emplace_back("INSERT,822,TESLA,BUY,1.7786,0");
    input.emplace_back("INSERT,823,NOKIA,BUY,2.8436,5");
    input.emplace_back("INSERT,824,NOKIA,BUY,3.4218,5");
    input.emplace_back("INSERT,825,MICROSOFT,SELL,2.2008,9");
    input.emplace_back("INSERT,826,ASML,SELL,1.4371,10");
    input.emplace_back("INSERT,827,HP,BUY,2.5233,10");
    input.emplace_back("INSERT,828,APPLE,BUY,1.659,6");
    input.emplace_back("INSERT,829,TESLA,BUY,1.9328,0");
    input.emplace_back("INSERT,830,MICROSOFT,BUY,3.2138,4");
    input.emplace_back("INSERT,831,ASML,SELL,2.9528,3");
    input.emplace_back("INSERT,832,NOKIA,BUY,3.6103,7");
    input.emplace_back("INSERT,833,TESLA,SELL,3.7274,5");
    input.emplace_back("INSERT,834,TESLA,SELL,1.4501,2");
    input.emplace_back("INSERT,835,APPLE,BUY,1.5784,10");
    input.emplace_back("INSERT,836,NOKIA,SELL,3.6177,9");
    input.emplace_back("INSERT,837,CAC40,SELL,1.0734,4");
    input.emplace_back("INSERT,838,MICROSOFT,BUY,1.1882,7");
    input.emplace_back("INSERT,839,CAC40,SELL,2.6575,6");
    input.emplace_back("INSERT,840,HP,SELL,3.4357,1");
    input.emplace_back("INSERT,841,CAC40,BUY,1.9724,10");
    input.emplace_back("INSERT,842,MICROSOFT,SELL,3.2313,7");
    input.emplace_back("INSERT,843,ASML,SELL,3.512,6");
    input.emplace_back("INSERT,844,ASML,BUY,3.6606,4");
    input.emplace_back("INSERT,845,NOKIA,SELL,1.3735,10");
    input.emplace_back("INSERT,846,NOKIA,SELL,3.6071,4");
    input.emplace_back("INSERT,847,CAC40,BUY,1.4396,10");
    input.emplace_back("INSERT,848,MICROSOFT,SELL,2.751,2");
    input.emplace_back("INSERT,849,TESLA,SELL,1.5579,4");
    input.emplace_back("INSERT,850,NOKIA,SELL,1.4066,2");
    input.emplace_back("INSERT,851,CAC40,BUY,1.6697,0");
    input.emplace_back("INSERT,852,MICROSOFT,SELL,2.4208,1");
    input.emplace_back("INSERT,853,TESLA,BUY,1.9534,9");
    input.emplace_back("INSERT,854,APPLE,BUY,1.5966,8");
    input.emplace_back("INSERT,855,HP,BUY,3.1824,9");
    input.emplace_back("INSERT,856,CAC40,SELL,2.5931,10");
    input.emplace_back("INSERT,857,CAC40,BUY,1.2288,7");
    input.emplace_back("INSERT,858,APPLE,SELL,1.9244,10");
    input.emplace_back("INSERT,859,MICROSOFT,SELL,2.7706,2");
    input.emplace_back("INSERT,860,APPLE,BUY,1.8901,7");
    input.emplace_back("INSERT,861,TESLA,SELL,2.514,6");
    input.emplace_back("INSERT,862,MICROSOFT,BUY,3.3045,2");
    input.emplace_back("INSERT,863,MICROSOFT,SELL,1.5534,4");
    input.emplace_back("INSERT,864,NOKIA,BUY,3.202,5");
    input.emplace_back("INSERT,865,NOKIA,SELL,1.4053,6");
    input.emplace_back("INSERT,866,HP,SELL,2.0981,9");
    input.emplace_back("INSERT,867,TESLA,SELL,2.5127,7");
    input.emplace_back("INSERT,868,TESLA,BUY,3.3671,1");
    input.emplace_back("INSERT,869,TESLA,SELL,1.9294,4");
    input.emplace_back("INSERT,870,HP,BUY,1.6443,10");
    input.emplace_back("INSERT,871,APPLE,SELL,2.5965,6");
    input.emplace_back("INSERT,872,HP,SELL,1.291,0");
    input.emplace_back("INSERT,873,TESLA,BUY,3.9294,3");
    input.emplace_back("INSERT,874,NOKIA,SELL,1.4739,6");
    input.emplace_back("INSERT,875,CAC40,BUY,2.9004,0");
    input.emplace_back("INSERT,876,ASML,BUY,2.2756,1");
    input.emplace_back("INSERT,877,HP,BUY,3.4868,7");
    input.emplace_back("INSERT,878,NOKIA,SELL,1.418,10");
    input.emplace_back("INSERT,879,HP,BUY,3.0102,6");
    input.emplace_back("INSERT,880,APPLE,BUY,1.6488,2");
    input.emplace_back("INSERT,881,HP,SELL,1.1072,1");
    input.emplace_back("INSERT,882,NOKIA,SELL,2.8472,9");
    input.emplace_back("INSERT,883,MICROSOFT,BUY,3.5872,6");
    input.emplace_back("INSERT,884,NOKIA,SELL,3.8289,3");
    input.emplace_back("INSERT,885,TESLA,BUY,3.6672,9");
    input.emplace_back("INSERT,886,NOKIA,BUY,1.7032,8");
    input.emplace_back("INSERT,887,ASML,SELL,2.1977,0");
    input.emplace_back("INSERT,888,ASML,SELL,2.4987,8");
    input.emplace_back("INSERT,889,APPLE,BUY,1.3388,1");
    input.emplace_back("INSERT,890,MICROSOFT,BUY,3.7502,10");
    input.emplace_back("INSERT,891,APPLE,BUY,1.7969,9");
    input.emplace_back("INSERT,892,APPLE,BUY,1.7324,3");
    input.emplace_back("INSERT,893,ASML,BUY,1.6524,8");
    input.emplace_back("INSERT,894,MICROSOFT,BUY,1.042,7");
    input.emplace_back("INSERT,895,ASML,SELL,2.6288,10");
    input.emplace_back("INSERT,896,APPLE,BUY,3.8653,10");
    input.emplace_back("INSERT,897,ASML,BUY,3.5076,3");
    input.emplace_back("INSERT,898,HP,BUY,1.5433,0");
    input.emplace_back("INSERT,899,TESLA,BUY,2.8335,4");
    input.emplace_back("INSERT,900,ASML,SELL,3.351,9");
    input.emplace_back("INSERT,901,NOKIA,BUY,2.8703,1");
    input.emplace_back("INSERT,902,CAC40,SELL,1.9029,2");
    input.emplace_back("INSERT,903,MICROSOFT,BUY,3.4854,2");
    input.emplace_back("INSERT,904,NOKIA,SELL,1.8127,3");
    input.emplace_back("INSERT,905,TESLA,BUY,3.9568,8");
    input.emplace_back("INSERT,906,NOKIA,SELL,3.6166,7");
    input.emplace_back("INSERT,907,HP,SELL,2.8849,5");
    input.emplace_back("INSERT,908,NOKIA,SELL,1.7902,1");
    input.emplace_back("INSERT,909,ASML,BUY,2.7129,10");
    input.emplace_back("INSERT,910,HP,SELL,3.9833,7");
    input.emplace_back("INSERT,911,APPLE,SELL,3.0348,9");
    input.emplace_back("INSERT,912,NOKIA,BUY,3.208,3");
    input.emplace_back("INSERT,913,ASML,SELL,3.8695,7");
    input.emplace_back("INSERT,914,ASML,BUY,1.0401,9");
    input.emplace_back("INSERT,915,NOKIA,SELL,1.7022,10");
    input.emplace_back("INSERT,916,TESLA,BUY,1.4672,7");
    input.emplace_back("INSERT,917,CAC40,BUY,1.8448,10");
    input.emplace_back("INSERT,918,MICROSOFT,BUY,3.1019,0");
    input.emplace_back("INSERT,919,APPLE,SELL,3.8192,5");
    input.emplace_back("INSERT,920,CAC40,SELL,1.0148,3");
    input.emplace_back("INSERT,921,TESLA,SELL,2.2582,0");
    input.emplace_back("INSERT,922,NOKIA,BUY,1.4793,0");
    input.emplace_back("INSERT,923,TESLA,BUY,1.8042,0");
    input.emplace_back("INSERT,924,HP,SELL,3.6464,8");
    input.emplace_back("INSERT,925,APPLE,SELL,3.3848,6");
    input.emplace_back("INSERT,926,TESLA,BUY,2.1065,3");
    input.emplace_back("INSERT,927,TESLA,BUY,2.0681,2");
    input.emplace_back("INSERT,928,MICROSOFT,SELL,3.492,4");
    input.emplace_back("INSERT,929,APPLE,BUY,3.4294,1");
    input.emplace_back("INSERT,930,HP,SELL,2.9845,1");
    input.emplace_back("INSERT,931,TESLA,SELL,3.9059,10");
    input.emplace_back("INSERT,932,TESLA,BUY,2.2132,5");
    input.emplace_back("INSERT,933,HP,BUY,1.1034,0");
    input.emplace_back("INSERT,934,TESLA,BUY,2.9413,5");
    input.emplace_back("INSERT,935,TESLA,BUY,3.566,6");
    input.emplace_back("INSERT,936,NOKIA,SELL,2.957,10");
    input.emplace_back("INSERT,937,ASML,BUY,3.1393,0");
    input.emplace_back("INSERT,938,HP,BUY,3.7691,7");
    input.emplace_back("INSERT,939,TESLA,SELL,1.8725,1");
    input.emplace_back("INSERT,940,TESLA,BUY,3.3228,10");
    input.emplace_back("INSERT,941,APPLE,SELL,1.9298,4");
    input.emplace_back("INSERT,942,NOKIA,BUY,1.632,10");
    input.emplace_back("INSERT,943,HP,SELL,3.7701,6");
    input.emplace_back("INSERT,944,HP,BUY,2.0331,6");
    input.emplace_back("INSERT,945,APPLE,SELL,2.6497,7");
    input.emplace_back("INSERT,946,CAC40,SELL,3.2691,9");
    input.emplace_back("INSERT,947,APPLE,BUY,2.7774,7");
    input.emplace_back("INSERT,948,TESLA,SELL,1.2533,6");
    input.emplace_back("INSERT,949,ASML,BUY,2.9517,4");
    input.emplace_back("INSERT,950,APPLE,BUY,2.0574,9");
    input.emplace_back("INSERT,951,NOKIA,BUY,3.2875,3");
    input.emplace_back("INSERT,952,CAC40,BUY,2.463,4");
    input.emplace_back("INSERT,953,APPLE,SELL,3.8486,6");
    input.emplace_back("INSERT,954,ASML,SELL,3.6923,9");
    input.emplace_back("INSERT,955,MICROSOFT,SELL,2.2598,3");
    input.emplace_back("INSERT,956,ASML,BUY,3.8393,7");
    input.emplace_back("INSERT,957,ASML,BUY,3.3264,0");
    input.emplace_back("INSERT,958,TESLA,SELL,3.4621,7");
    input.emplace_back("INSERT,959,TESLA,BUY,3.937,2");
    input.emplace_back("INSERT,960,CAC40,BUY,3.9848,5");
    input.emplace_back("INSERT,961,HP,BUY,2.8049,0");
    input.emplace_back("INSERT,962,TESLA,SELL,1.0998,1");
    input.emplace_back("INSERT,963,ASML,BUY,2.9898,7");
    input.emplace_back("INSERT,964,HP,SELL,3.7775,0");
    input.emplace_back("INSERT,965,NOKIA,BUY,2.0148,6");
    input.emplace_back("INSERT,966,NOKIA,SELL,3.6527,4");
    input.emplace_back("INSERT,967,NOKIA,SELL,3.5939,1");
    input.emplace_back("INSERT,968,ASML,SELL,2.2905,5");
    input.emplace_back("INSERT,969,ASML,SELL,3.6635,2");
    input.emplace_back("INSERT,970,CAC40,SELL,1.0988,1");
    input.emplace_back("INSERT,971,HP,BUY,2.424,10");
    input.emplace_back("INSERT,972,CAC40,SELL,1.2954,5");
    input.emplace_back("INSERT,973,HP,BUY,2.5596,8");
    input.emplace_back("INSERT,974,HP,SELL,3.0694,8");
    input.emplace_back("INSERT,975,TESLA,SELL,1.8149,7");
    input.emplace_back("INSERT,976,APPLE,BUY,2.6063,6");
    input.emplace_back("INSERT,977,MICROSOFT,BUY,2.3534,3");
    input.emplace_back("INSERT,978,TESLA,BUY,3.1306,10");
    input.emplace_back("INSERT,979,APPLE,SELL,2.6153,9");
    input.emplace_back("INSERT,980,NOKIA,BUY,2.7579,9");
    input.emplace_back("INSERT,981,HP,BUY,2.3563,7");
    input.emplace_back("INSERT,982,APPLE,SELL,1.2089,7");
    input.emplace_back("INSERT,983,MICROSOFT,BUY,2.0926,2");
    input.emplace_back("INSERT,984,MICROSOFT,SELL,3.5102,6");
    input.emplace_back("INSERT,985,CAC40,SELL,3.245,7");
    input.emplace_back("INSERT,986,APPLE,SELL,3.3398,9");
    input.emplace_back("INSERT,987,TESLA,BUY,3.6698,3");
    input.emplace_back("INSERT,988,HP,BUY,3.6701,2");
    input.emplace_back("INSERT,989,CAC40,SELL,3.6714,1");
    input.emplace_back("INSERT,990,TESLA,SELL,1.6991,9");
    input.emplace_back("INSERT,991,APPLE,BUY,3.9357,0");
    input.emplace_back("INSERT,992,HP,BUY,3.5837,6");
    input.emplace_back("INSERT,993,ASML,SELL,1.556,5");
    input.emplace_back("INSERT,994,TESLA,BUY,3.1565,4");
    input.emplace_back("INSERT,995,NOKIA,BUY,1.3959,0");
    input.emplace_back("INSERT,996,TESLA,SELL,1.6677,8");
    input.emplace_back("INSERT,997,MICROSOFT,SELL,1.1605,3");
    input.emplace_back("INSERT,998,ASML,BUY,1.3855,7");
    input.emplace_back("INSERT,999,TESLA,SELL,1.2775,6");

    MatchingEngine m;
    m.run(input);

    auto result = m.getResults();
}

TEST(lobTest, randomTest2)
{
    auto input = std::vector<std::string>();
    input.emplace_back("INSERT,4,MICROSOFT,SELL,1.0045,4");
    input.emplace_back("AMEND,4,1.4657,8");
    input.emplace_back("INSERT,9,PAI,BUY,2.8686,10");
    input.emplace_back("INSERT,13,MICROSOFT,SELL,3.0369,6");
    input.emplace_back("PULL,9");
    input.emplace_back("PULL,13");
    input.emplace_back("INSERT,16,MICROSOFT,BUY,3.8543,7");
    input.emplace_back("INSERT,18,PAI,BUY,1.7156,1");
    input.emplace_back("INSERT,19,NL,BUY,2.4096,9");
    input.emplace_back("AMEND,4,1.3123,0");
    input.emplace_back("INSERT,21,NOKIA,BUY,2.9457,6");
    input.emplace_back("INSERT,24,TESLA,SELL,3.0582,2");
    input.emplace_back("PULL,4");
    input.emplace_back("INSERT,28,HP,BUY,2.6815,8");
    input.emplace_back("AMEND,16,1.6192,2");
    input.emplace_back("INSERT,31,NL,BUY,2.7595,7");
    input.emplace_back("INSERT,33,PAI,SELL,1.5652,4");
    input.emplace_back("AMEND,16,1.3089,0");
    input.emplace_back("INSERT,37,NL,SELL,3.724,0");
    input.emplace_back("PULL,21");
    input.emplace_back("PULL,24");
    input.emplace_back("PULL,19");
    input.emplace_back("AMEND,33,2.0517,4");
    input.emplace_back("INSERT,51,ASML,BUY,3.0375,9");
    input.emplace_back("INSERT,53,MICROSOFT,BUY,3.0421,10");
    input.emplace_back("INSERT,54,TESLA,BUY,2.5903,10");
    input.emplace_back("INSERT,55,TESLA,BUY,2.293,0");
    input.emplace_back("PULL,16");
    input.emplace_back("INSERT,58,TESLA,BUY,1.4322,7");
    input.emplace_back("INSERT,60,NL,BUY,3.0371,0");
    input.emplace_back("INSERT,61,HP,BUY,3.8218,4");
    input.emplace_back("INSERT,65,CAC40,BUY,2.146,4");
    input.emplace_back("INSERT,66,HP,SELL,2.9219,10");
    input.emplace_back("INSERT,70,AMS,SELL,2.3666,7");
    input.emplace_back("AMEND,33,1.7451,9");
    input.emplace_back("INSERT,73,FR,BUY,2.7217,9");
    input.emplace_back("PULL,54");
    input.emplace_back("INSERT,76,ASML,BUY,1.6663,2");
    input.emplace_back("AMEND,76,2.3766,1");
    input.emplace_back("INSERT,78,MICROSOFT,SELL,2.3024,5");
    input.emplace_back("INSERT,79,NL,BUY,1.1049,2");
    input.emplace_back("AMEND,70,2.2343,2");
    input.emplace_back("AMEND,18,1.9867,6");
    input.emplace_back("INSERT,85,ASML,SELL,1.7236,5");
    input.emplace_back("INSERT,87,CAC40,BUY,2.4959,4");
    input.emplace_back("PULL,58");
    input.emplace_back("INSERT,90,HP,BUY,1.3751,10");
    input.emplace_back("PULL,31");
    input.emplace_back("INSERT,94,MICROSOFT,BUY,1.6154,8");
    input.emplace_back("INSERT,100,NOKIA,BUY,3.2338,10");
    input.emplace_back("INSERT,101,AMS,SELL,2.2585,8");
    input.emplace_back("INSERT,102,AMS,BUY,1.3213,7");
    input.emplace_back("PULL,51");
    input.emplace_back("INSERT,109,ASML,BUY,3.4337,9");
    input.emplace_back("INSERT,110,NL,BUY,3.0436,1");
    input.emplace_back("PULL,100");
    input.emplace_back("INSERT,116,APPLE,BUY,3.6896,7");
    input.emplace_back("INSERT,117,FR,BUY,2.6712,9");
    input.emplace_back("INSERT,118,HP,SELL,1.3821,4");
    input.emplace_back("INSERT,119,NOKIA,BUY,3.2937,6");
    input.emplace_back("INSERT,122,ASML,BUY,3.4331,0");
    input.emplace_back("INSERT,128,NL,SELL,1.7555,1");
    input.emplace_back("PULL,85");
    input.emplace_back("INSERT,133,EG,BUY,3.4247,3");
    input.emplace_back("INSERT,134,HP,SELL,1.793,4");
    input.emplace_back("INSERT,137,TESLA,BUY,2.0867,0");
    input.emplace_back("INSERT,138,APPLE,SELL,2.4029,3");
    input.emplace_back("INSERT,142,HP,BUY,1.9552,8");
    input.emplace_back("AMEND,94,3.3582,1");
    input.emplace_back("INSERT,144,NL,BUY,3.6414,8");
    input.emplace_back("PULL,109");
    input.emplace_back("INSERT,147,CAC40,BUY,2.7674,8");
    input.emplace_back("INSERT,149,HP,SELL,3.0606,4");
    input.emplace_back("AMEND,144,3.8314,6");
    input.emplace_back("INSERT,153,HP,SELL,2.6331,10");
    input.emplace_back("INSERT,154,CAC40,BUY,1.3122,4");
    input.emplace_back("INSERT,162,ASML,SELL,2.0104,10");
    input.emplace_back("INSERT,164,EG,SELL,2.9974,7");
    input.emplace_back("INSERT,168,ASML,BUY,1.1934,10");
    input.emplace_back("INSERT,171,AMS,BUY,1.7006,8");
    input.emplace_back("INSERT,174,EG,BUY,2.0399,3");
    input.emplace_back("PULL,76");
    input.emplace_back("INSERT,176,ASML,SELL,1.346,7");
    input.emplace_back("INSERT,177,HP,SELL,2.724,1");
    input.emplace_back("PULL,153");
    input.emplace_back("INSERT,179,ASML,BUY,1.8123,9");
    input.emplace_back("INSERT,181,ASML,BUY,3.8729,10");
    input.emplace_back("INSERT,182,NOKIA,BUY,2.271,10");
    input.emplace_back("AMEND,60,1.9148,2");
    input.emplace_back("INSERT,186,NOKIA,SELL,2.81,0");
    input.emplace_back("INSERT,188,PAI,BUY,2.7057,4");
    input.emplace_back("AMEND,101,2.0142,10");
    input.emplace_back("INSERT,190,NOKIA,BUY,2.6162,1");
    input.emplace_back("INSERT,191,NOKIA,SELL,1.0525,5");
    input.emplace_back("PULL,171");
    input.emplace_back("INSERT,196,PAI,SELL,2.8136,4");
    input.emplace_back("INSERT,197,HP,SELL,3.1902,9");
    input.emplace_back("INSERT,198,NL,SELL,3.0598,1");
    input.emplace_back("INSERT,200,HP,BUY,3.0863,9");
    input.emplace_back("INSERT,203,FR,BUY,1.5148,10");
    input.emplace_back("INSERT,204,HP,SELL,1.1923,10");
    input.emplace_back("PULL,197");
    input.emplace_back("PULL,33");
    input.emplace_back("PULL,60");
    input.emplace_back("INSERT,210,NOKIA,BUY,2.6138,9");
    input.emplace_back("INSERT,211,HP,BUY,3.3396,4");
    input.emplace_back("AMEND,55,3.6809,8");
    input.emplace_back("PULL,162");
    input.emplace_back("INSERT,215,APPLE,SELL,1.5338,3");
    input.emplace_back("AMEND,190,3.5356,8");
    input.emplace_back("AMEND,102,3.9427,8");
    input.emplace_back("INSERT,219,ASML,BUY,1.5943,1");
    input.emplace_back("INSERT,221,MICROSOFT,BUY,3.7123,10");
    input.emplace_back("INSERT,222,TESLA,SELL,2.955,10");
    input.emplace_back("INSERT,227,ASML,SELL,3.3162,0");
    input.emplace_back("INSERT,228,PAI,SELL,1.3974,8");
    input.emplace_back("PULL,182");
    input.emplace_back("INSERT,232,NOKIA,BUY,2.5084,9");
    input.emplace_back("INSERT,237,AMS,BUY,1.1334,3");
    input.emplace_back("AMEND,87,1.045,8");
    input.emplace_back("INSERT,240,NL,SELL,2.3519,1");
    input.emplace_back("AMEND,117,3.4904,5");
    input.emplace_back("INSERT,242,APPLE,BUY,1.1499,1");
    input.emplace_back("AMEND,37,1.2035,2");
    input.emplace_back("INSERT,244,PAI,BUY,2.7226,9");
    input.emplace_back("INSERT,245,FR,BUY,2.8793,0");
    input.emplace_back("INSERT,249,NL,BUY,2.8016,9");
    input.emplace_back("INSERT,251,EG,SELL,1.2591,3");
    input.emplace_back("PULL,164");
    input.emplace_back("INSERT,254,AMS,BUY,1.378,4");
    input.emplace_back("INSERT,255,EG,BUY,2.9828,3");
    input.emplace_back("INSERT,257,EG,BUY,3.5736,3");
    input.emplace_back("INSERT,258,CAC40,BUY,2.7431,9");
    input.emplace_back("INSERT,259,PAI,BUY,2.5061,0");
    input.emplace_back("INSERT,262,CAC40,SELL,1.2354,5");
    input.emplace_back("INSERT,264,PAI,SELL,1.9963,5");
    input.emplace_back("INSERT,266,TESLA,SELL,1.9924,8");
    input.emplace_back("AMEND,177,1.1227,4");
    input.emplace_back("INSERT,268,PAI,BUY,2.7053,1");
    input.emplace_back("INSERT,273,AMS,SELL,1.9644,9");
    input.emplace_back("INSERT,276,FR,SELL,1.4727,5");
    input.emplace_back("INSERT,278,EG,SELL,1.4089,9");
    input.emplace_back("PULL,242");
    input.emplace_back("INSERT,281,EG,BUY,2.622,5");
    input.emplace_back("PULL,244");
    input.emplace_back("INSERT,285,APPLE,SELL,3.6632,4");
    input.emplace_back("INSERT,286,APPLE,SELL,1.5341,9");
    input.emplace_back("INSERT,287,ASML,SELL,3.1439,8");
    input.emplace_back("AMEND,122,1.6695,1");
    input.emplace_back("PULL,190");
    input.emplace_back("INSERT,290,PAI,SELL,1.89,1");
    input.emplace_back("INSERT,291,ASML,SELL,2.7525,0");
    input.emplace_back("PULL,101");
    input.emplace_back("INSERT,296,TESLA,BUY,3.7243,8");
    input.emplace_back("INSERT,300,APPLE,SELL,3.2691,3");
    input.emplace_back("INSERT,301,APPLE,SELL,1.879,8");
    input.emplace_back("INSERT,304,FR,SELL,3.9787,0");
    input.emplace_back("INSERT,306,PAI,SELL,1.914,5");
    input.emplace_back("INSERT,307,NL,BUY,3.5335,0");
    input.emplace_back("INSERT,312,APPLE,BUY,1.6245,1");
    input.emplace_back("INSERT,313,EG,BUY,1.1971,8");
    input.emplace_back("INSERT,315,NL,SELL,1.8934,9");
    input.emplace_back("INSERT,317,AMS,BUY,2.7013,0");
    input.emplace_back("PULL,262");
    input.emplace_back("INSERT,319,CAC40,BUY,3.8152,9");
    input.emplace_back("INSERT,320,HP,SELL,1.3021,0");
    input.emplace_back("INSERT,321,MICROSOFT,BUY,1.3247,0");
    input.emplace_back("AMEND,312,1.2029,6");
    input.emplace_back("AMEND,215,2.3048,9");
    input.emplace_back("PULL,211");
    input.emplace_back("INSERT,327,TESLA,BUY,3.4506,5");
    input.emplace_back("INSERT,331,APPLE,SELL,2.2904,9");
    input.emplace_back("INSERT,332,EG,SELL,3.0648,7");
    input.emplace_back("INSERT,334,CAC40,BUY,3.0439,7");
    input.emplace_back("PULL,138");
    input.emplace_back("INSERT,337,ASML,SELL,3.8273,5");
    input.emplace_back("INSERT,338,CAC40,SELL,1.6867,5");
    input.emplace_back("AMEND,281,1.8132,1");
    input.emplace_back("AMEND,133,1.4473,10");
    input.emplace_back("AMEND,200,1.1534,4");
    input.emplace_back("PULL,266");
    input.emplace_back("AMEND,191,2.1291,7");
    input.emplace_back("INSERT,346,APPLE,SELL,2.3919,7");
    input.emplace_back("AMEND,237,2.9179,4");
    input.emplace_back("AMEND,331,2.4141,8");
    input.emplace_back("INSERT,352,CAC40,BUY,3.5503,6");
    input.emplace_back("INSERT,353,APPLE,SELL,2.2331,1");
    input.emplace_back("PULL,273");
    input.emplace_back("INSERT,356,EG,SELL,1.4471,3");
    input.emplace_back("AMEND,65,1.0,1");
    input.emplace_back("INSERT,362,NOKIA,BUY,1.8887,2");
    input.emplace_back("PULL,313");
    input.emplace_back("INSERT,368,APPLE,BUY,3.4533,0");
    input.emplace_back("INSERT,369,NL,BUY,2.8484,4");
    input.emplace_back("INSERT,372,ASML,BUY,3.7098,6");
    input.emplace_back("AMEND,188,2.1853,5");
    input.emplace_back("AMEND,307,3.0934,4");
    input.emplace_back("INSERT,377,EG,BUY,1.1394,3");
    input.emplace_back("INSERT,378,TESLA,BUY,2.0852,3");
    input.emplace_back("INSERT,379,ASML,SELL,2.0703,8");
    input.emplace_back("INSERT,383,EG,BUY,2.6848,3");
    input.emplace_back("INSERT,385,ASML,BUY,3.5036,8");
    input.emplace_back("INSERT,389,PAI,SELL,2.7667,7");
    input.emplace_back("INSERT,390,MICROSOFT,BUY,3.3708,5");
    input.emplace_back("INSERT,394,NL,BUY,2.7705,9");
    input.emplace_back("INSERT,395,FR,BUY,1.2176,9");
    input.emplace_back("INSERT,396,NOKIA,SELL,2.2013,0");
    input.emplace_back("PULL,53");
    input.emplace_back("INSERT,399,AMS,SELL,3.1366,9");
    input.emplace_back("PULL,200");
    input.emplace_back("INSERT,404,FR,SELL,2.2368,8");
    input.emplace_back("AMEND,281,2.2311,6");
    input.emplace_back("PULL,122");
    input.emplace_back("INSERT,411,EG,BUY,1.7165,4");
    input.emplace_back("INSERT,412,NL,SELL,1.875,7");
    input.emplace_back("INSERT,417,NL,BUY,2.3141,6");
    input.emplace_back("INSERT,420,CAC40,BUY,3.8989,1");
    input.emplace_back("AMEND,181,2.0356,8");
    input.emplace_back("PULL,312");
    input.emplace_back("INSERT,425,APPLE,BUY,3.7866,8");
    input.emplace_back("INSERT,426,EG,BUY,3.0023,7");
    input.emplace_back("INSERT,428,APPLE,BUY,3.3709,7");
    input.emplace_back("INSERT,430,ASML,BUY,3.7247,8");
    input.emplace_back("INSERT,431,TESLA,SELL,3.8688,10");
    input.emplace_back("INSERT,433,TESLA,SELL,2.7203,9");
    input.emplace_back("INSERT,440,MICROSOFT,BUY,3.8195,7");
    input.emplace_back("PULL,203");
    input.emplace_back("AMEND,142,2.5744,8");
    input.emplace_back("INSERT,449,FR,SELL,1.4762,5");
    input.emplace_back("INSERT,451,NOKIA,SELL,2.8938,1");
    input.emplace_back("PULL,362");
    input.emplace_back("INSERT,456,ASML,SELL,1.311,0");
    input.emplace_back("INSERT,457,TESLA,SELL,2.6817,10");
    input.emplace_back("PULL,255");
    input.emplace_back("INSERT,465,NL,BUY,1.3644,4");
    input.emplace_back("INSERT,467,NL,BUY,1.8863,3");
    input.emplace_back("PULL,404");
    input.emplace_back("INSERT,469,FR,SELL,3.0726,7");
    input.emplace_back("PULL,428");
    input.emplace_back("INSERT,473,HP,BUY,1.8616,8");
    input.emplace_back("INSERT,478,MICROSOFT,SELL,2.8286,0");
    input.emplace_back("INSERT,479,NOKIA,BUY,1.6356,6");
    input.emplace_back("AMEND,251,1.5901,7");
    input.emplace_back("AMEND,196,2.3805,3");
    input.emplace_back("INSERT,482,HP,SELL,3.8911,5");
    input.emplace_back("INSERT,484,HP,BUY,1.022,7");
    input.emplace_back("INSERT,485,FR,BUY,1.3147,3");
    input.emplace_back("INSERT,487,NOKIA,BUY,1.1694,10");
    input.emplace_back("INSERT,489,NL,BUY,2.3485,5");
    input.emplace_back("AMEND,485,2.62,7");
    input.emplace_back("INSERT,493,CAC40,SELL,1.2331,2");
    input.emplace_back("AMEND,119,3.9148,2");
    input.emplace_back("INSERT,500,CAC40,SELL,1.9115,10");
    input.emplace_back("AMEND,281,2.4455,3");
    input.emplace_back("INSERT,504,FR,SELL,3.9215,5");
    input.emplace_back("INSERT,505,NOKIA,SELL,1.8612,10");
    input.emplace_back("INSERT,506,TESLA,SELL,2.6791,8");
    input.emplace_back("AMEND,378,2.8051,7");
    input.emplace_back("INSERT,508,NL,SELL,2.5956,7");
    input.emplace_back("AMEND,251,3.4573,5");
    input.emplace_back("INSERT,511,ASML,BUY,3.2975,10");
    input.emplace_back("INSERT,514,AMS,SELL,2.0262,0");
    input.emplace_back("INSERT,517,APPLE,BUY,3.764,10");
    input.emplace_back("INSERT,518,EG,BUY,2.5045,2");
    input.emplace_back("PULL,118");
    input.emplace_back("INSERT,521,NOKIA,SELL,1.3228,1");
    input.emplace_back("INSERT,523,NOKIA,SELL,2.2456,2");
    input.emplace_back("INSERT,525,FR,BUY,1.1365,6");
    input.emplace_back("AMEND,245,3.4727,5");
    input.emplace_back("INSERT,529,MICROSOFT,BUY,3.5106,0");
    input.emplace_back("AMEND,28,2.7816,1");
    input.emplace_back("INSERT,534,TESLA,BUY,3.5781,8");
    input.emplace_back("INSERT,537,NOKIA,BUY,3.0387,9");
    input.emplace_back("INSERT,538,NOKIA,BUY,3.826,4");
    input.emplace_back("AMEND,338,3.5503,1");
    input.emplace_back("PULL,188");
    input.emplace_back("INSERT,545,CAC40,BUY,3.7197,7");
    input.emplace_back("INSERT,547,ASML,SELL,2.6853,5");
    input.emplace_back("INSERT,549,ASML,SELL,3.876,3");
    input.emplace_back("INSERT,550,HP,BUY,1.7955,9");
    input.emplace_back("INSERT,551,NL,SELL,3.4238,7");
    input.emplace_back("AMEND,228,1.5755,0");
    input.emplace_back("AMEND,90,1.6732,2");
    input.emplace_back("INSERT,559,CAC40,SELL,3.2717,0");
    input.emplace_back("INSERT,561,APPLE,SELL,1.4938,1");
    input.emplace_back("INSERT,562,FR,SELL,1.1965,6");
    input.emplace_back("INSERT,563,CAC40,BUY,3.6857,2");
    input.emplace_back("INSERT,565,APPLE,BUY,3.7079,1");
    input.emplace_back("INSERT,568,PAI,BUY,2.887,4");
    input.emplace_back("INSERT,571,NOKIA,SELL,3.8857,6");
    input.emplace_back("INSERT,575,NOKIA,BUY,3.2784,6");
    input.emplace_back("AMEND,478,3.4674,10");
    input.emplace_back("INSERT,581,TESLA,SELL,3.8874,3");
    input.emplace_back("INSERT,582,NOKIA,BUY,2.2324,1");
    input.emplace_back("INSERT,583,FR,SELL,3.1188,9");
    input.emplace_back("INSERT,585,FR,BUY,2.2937,1");
    input.emplace_back("INSERT,586,ASML,BUY,3.6083,8");
    input.emplace_back("INSERT,588,ASML,SELL,2.1579,7");
    input.emplace_back("INSERT,589,HP,BUY,2.4366,8");
    input.emplace_back("INSERT,590,APPLE,SELL,2.8607,3");
    input.emplace_back("INSERT,591,AMS,BUY,3.773,10");
    input.emplace_back("PULL,254");
    input.emplace_back("AMEND,219,2.4732,9");
    input.emplace_back("AMEND,61,3.0463,3");
    input.emplace_back("INSERT,596,NL,SELL,2.3084,1");
    input.emplace_back("INSERT,597,MICROSOFT,BUY,1.7417,5");
    input.emplace_back("PULL,591");
    input.emplace_back("INSERT,604,HP,BUY,2.6585,8");
    input.emplace_back("INSERT,605,NL,SELL,1.3818,5");
    input.emplace_back("INSERT,606,CAC40,SELL,1.1942,4");
    input.emplace_back("PULL,473");
    input.emplace_back("INSERT,609,EG,BUY,3.1102,1");
    input.emplace_back("INSERT,610,CAC40,SELL,1.4258,5");
    input.emplace_back("INSERT,611,AMS,BUY,3.9098,3");
    input.emplace_back("INSERT,612,NL,BUY,1.3908,6");
    input.emplace_back("INSERT,616,HP,BUY,1.5654,7");
    input.emplace_back("AMEND,149,3.6638,3");
    input.emplace_back("INSERT,619,MICROSOFT,BUY,1.8984,6");
    input.emplace_back("INSERT,621,PAI,BUY,3.4,1");
    input.emplace_back("PULL,149");
    input.emplace_back("PULL,264");
    input.emplace_back("INSERT,627,NL,SELL,3.7762,9");
    input.emplace_back("INSERT,628,FR,BUY,3.8791,10");
    input.emplace_back("INSERT,629,NOKIA,SELL,2.5565,9");
    input.emplace_back("AMEND,79,1.1384,1");
    input.emplace_back("AMEND,611,1.5262,10");
    input.emplace_back("PULL,385");
    input.emplace_back("AMEND,426,1.8278,4");
    input.emplace_back("INSERT,636,CAC40,SELL,2.524,10");
    input.emplace_back("INSERT,637,HP,SELL,1.9306,5");
    input.emplace_back("INSERT,639,TESLA,BUY,2.871,1");
    input.emplace_back("INSERT,643,APPLE,SELL,1.254,2");
    input.emplace_back("INSERT,644,EG,BUY,2.4358,2");
    input.emplace_back("INSERT,645,FR,BUY,2.2726,1");
    input.emplace_back("INSERT,646,CAC40,BUY,3.6725,8");
    input.emplace_back("INSERT,649,AMS,SELL,3.2562,6");
    input.emplace_back("PULL,204");
    input.emplace_back("INSERT,652,CAC40,SELL,1.6169,10");
    input.emplace_back("PULL,590");
    input.emplace_back("PULL,337");
    input.emplace_back("INSERT,658,AMS,SELL,1.5001,0");
    input.emplace_back("INSERT,660,AMS,BUY,2.3798,8");
    input.emplace_back("INSERT,663,ASML,SELL,2.9995,3");
    input.emplace_back("AMEND,79,2.9745,1");
    input.emplace_back("AMEND,581,2.8582,6");
    input.emplace_back("INSERT,673,NL,BUY,2.707,10");
    input.emplace_back("INSERT,674,FR,BUY,3.3642,2");
    input.emplace_back("AMEND,37,3.8402,2");
    input.emplace_back("INSERT,678,PAI,BUY,1.8056,9");
    input.emplace_back("INSERT,680,FR,SELL,1.6083,6");
    input.emplace_back("INSERT,681,APPLE,SELL,2.2402,8");
    input.emplace_back("INSERT,682,AMS,SELL,1.4147,4");
    input.emplace_back("INSERT,683,NL,SELL,1.4054,0");
    input.emplace_back("INSERT,684,EG,SELL,2.0901,7");
    input.emplace_back("INSERT,687,NL,BUY,1.3338,4");
    input.emplace_back("INSERT,689,PAI,SELL,2.85,1");
    input.emplace_back("INSERT,690,APPLE,SELL,2.4494,7");
    input.emplace_back("INSERT,691,NOKIA,SELL,1.1743,7");
    input.emplace_back("INSERT,692,PAI,BUY,2.5699,3");
    input.emplace_back("INSERT,694,APPLE,SELL,1.1826,0");
    input.emplace_back("PULL,285");
    input.emplace_back("INSERT,697,NL,SELL,1.3402,5");
    input.emplace_back("INSERT,698,NL,SELL,2.6833,10");
    input.emplace_back("INSERT,699,FR,SELL,3.6835,9");
    input.emplace_back("AMEND,186,2.9399,4");
    input.emplace_back("INSERT,703,PAI,BUY,1.5354,7");
    input.emplace_back("INSERT,704,FR,SELL,1.4224,8");
    input.emplace_back("INSERT,705,EG,SELL,3.3716,5");
    input.emplace_back("INSERT,708,EG,BUY,3.3022,9");
    input.emplace_back("PULL,399");
    input.emplace_back("AMEND,449,3.1146,5");
    input.emplace_back("INSERT,713,MICROSOFT,BUY,3.0867,8");
    input.emplace_back("AMEND,627,2.6165,1");
    input.emplace_back("INSERT,716,PAI,SELL,3.1874,9");
    input.emplace_back("INSERT,717,NOKIA,SELL,3.1422,8");
    input.emplace_back("INSERT,718,EG,BUY,2.041,6");
    input.emplace_back("INSERT,720,NOKIA,SELL,3.5907,10");
    input.emplace_back("INSERT,721,HP,BUY,3.4095,3");
    input.emplace_back("INSERT,724,HP,BUY,1.708,8");
    input.emplace_back("PULL,658");
    input.emplace_back("INSERT,727,PAI,SELL,3.1546,1");
    input.emplace_back("INSERT,729,EG,BUY,3.9445,7");
    input.emplace_back("INSERT,732,HP,SELL,1.7916,9");
    input.emplace_back("INSERT,735,NL,SELL,2.8874,0");
    input.emplace_back("PULL,660");
    input.emplace_back("PULL,320");
    input.emplace_back("INSERT,742,CAC40,SELL,1.0669,6");
    input.emplace_back("INSERT,746,HP,BUY,2.4147,6");
    input.emplace_back("AMEND,704,2.655,8");
    input.emplace_back("INSERT,750,AMS,BUY,3.1045,7");
    input.emplace_back("INSERT,752,ASML,BUY,1.5692,1");
    input.emplace_back("INSERT,753,CAC40,BUY,1.122,1");
    input.emplace_back("INSERT,754,ASML,BUY,2.2246,9");
    input.emplace_back("INSERT,757,HP,SELL,2.2706,5");
    input.emplace_back("INSERT,759,FR,SELL,1.2526,4");
    input.emplace_back("INSERT,760,CAC40,SELL,2.7132,6");
    input.emplace_back("INSERT,761,NOKIA,BUY,1.5798,7");
    input.emplace_back("AMEND,549,3.8399,7");
    input.emplace_back("PULL,704");
    input.emplace_back("INSERT,768,NOKIA,SELL,2.2272,4");
    input.emplace_back("INSERT,769,FR,SELL,3.5255,2");
    input.emplace_back("PULL,678");
    input.emplace_back("AMEND,346,3.2772,1");
    input.emplace_back("INSERT,774,ASML,SELL,2.5449,10");
    input.emplace_back("AMEND,596,1.374,8");
    input.emplace_back("PULL,478");
    input.emplace_back("INSERT,780,MICROSOFT,SELL,2.4292,4");
    input.emplace_back("INSERT,781,FR,BUY,2.4973,3");
    input.emplace_back("INSERT,782,EG,BUY,3.8986,8");
    input.emplace_back("INSERT,784,NL,SELL,2.4911,9");
    input.emplace_back("AMEND,485,1.6668,9");
    input.emplace_back("AMEND,549,1.5317,7");
    input.emplace_back("INSERT,789,EG,BUY,2.1707,1");
    input.emplace_back("INSERT,790,TESLA,SELL,2.052,2");
    input.emplace_back("PULL,720");
    input.emplace_back("INSERT,792,CAC40,SELL,2.7822,2");
    input.emplace_back("INSERT,793,HP,SELL,1.5277,5");
    input.emplace_back("INSERT,795,AMS,BUY,1.4149,4");
    input.emplace_back("PULL,278");
    input.emplace_back("INSERT,799,AMS,SELL,1.5346,4");
    input.emplace_back("INSERT,800,FR,BUY,1.715,10");
    input.emplace_back("INSERT,802,AMS,BUY,3.2629,5");
    input.emplace_back("PULL,426");
    input.emplace_back("INSERT,808,EG,SELL,3.0123,2");
    input.emplace_back("INSERT,810,NL,SELL,3.8438,6");
    input.emplace_back("INSERT,811,MICROSOFT,BUY,2.0118,4");
    input.emplace_back("INSERT,813,NOKIA,SELL,3.0259,10");
    input.emplace_back("INSERT,814,FR,SELL,1.2528,3");
    input.emplace_back("AMEND,611,1.9893,6");
    input.emplace_back("PULL,793");
    input.emplace_back("PULL,705");
    input.emplace_back("INSERT,820,NOKIA,SELL,3.0514,1");
    input.emplace_back("AMEND,440,2.9272,0");
    input.emplace_back("INSERT,822,NL,SELL,3.8077,6");
    input.emplace_back("INSERT,824,HP,BUY,1.7685,2");
    input.emplace_back("PULL,420");
    input.emplace_back("PULL,550");
    input.emplace_back("INSERT,831,MICROSOFT,BUY,3.93,8");
    input.emplace_back("INSERT,832,EG,SELL,3.2616,9");
    input.emplace_back("INSERT,834,ASML,SELL,2.9924,4");
    input.emplace_back("AMEND,222,2.9004,1");
    input.emplace_back("INSERT,836,NL,BUY,1.0107,4");
    input.emplace_back("INSERT,837,MICROSOFT,SELL,2.3095,6");
    input.emplace_back("PULL,610");
    input.emplace_back("PULL,703");
    input.emplace_back("INSERT,842,NOKIA,SELL,1.248,5");
    input.emplace_back("INSERT,846,FR,SELL,3.5018,5");
    input.emplace_back("INSERT,847,HP,BUY,1.8594,4");
    input.emplace_back("AMEND,346,2.2934,8");
    input.emplace_back("AMEND,637,2.9863,7");
    input.emplace_back("PULL,663");
    input.emplace_back("INSERT,856,TESLA,BUY,2.2409,2");
    input.emplace_back("INSERT,862,NOKIA,BUY,2.1249,2");
    input.emplace_back("AMEND,698,1.3467,2");
    input.emplace_back("AMEND,482,3.1081,4");
    input.emplace_back("INSERT,875,PAI,BUY,3.9425,7");
    input.emplace_back("PULL,511");
    input.emplace_back("AMEND,482,2.5453,3");
    input.emplace_back("AMEND,549,3.4644,0");
    input.emplace_back("INSERT,881,NOKIA,SELL,3.86,4");
    input.emplace_back("PULL,291");
    input.emplace_back("INSERT,889,NOKIA,SELL,2.4354,7");
    input.emplace_back("INSERT,893,PAI,BUY,1.2278,1");
    input.emplace_back("INSERT,894,MICROSOFT,SELL,1.5737,10");
    input.emplace_back("AMEND,469,2.1041,6");
    input.emplace_back("INSERT,896,HP,BUY,1.8064,4");
    input.emplace_back("INSERT,902,NL,SELL,3.4759,4");
    input.emplace_back("INSERT,903,MICROSOFT,BUY,1.4933,1");
    input.emplace_back("INSERT,905,FR,SELL,3.6186,9");
    input.emplace_back("AMEND,433,1.9163,1");
    input.emplace_back("INSERT,907,MICROSOFT,BUY,2.8877,5");
    input.emplace_back("INSERT,908,NOKIA,SELL,2.6463,2");
    input.emplace_back("PULL,181");
    input.emplace_back("INSERT,910,FR,SELL,2.2408,0");
    input.emplace_back("INSERT,911,CAC40,BUY,1.4554,5");
    input.emplace_back("INSERT,912,PAI,BUY,2.392,4");
    input.emplace_back("PULL,781");
    input.emplace_back("INSERT,916,CAC40,SELL,1.8871,3");
    input.emplace_back("AMEND,467,2.2331,6");
    input.emplace_back("INSERT,921,NL,SELL,1.8251,9");
    input.emplace_back("PULL,581");
    input.emplace_back("INSERT,924,NL,SELL,1.9903,9");
    input.emplace_back("INSERT,925,EG,BUY,1.6086,6");
    input.emplace_back("PULL,690");
    input.emplace_back("INSERT,929,ASML,BUY,2.2595,5");
    input.emplace_back("INSERT,933,EG,SELL,3.7061,2");
    input.emplace_back("AMEND,682,3.5471,3");
    input.emplace_back("INSERT,940,PAI,SELL,1.5684,1");
    input.emplace_back("INSERT,941,FR,SELL,2.3469,7");
    input.emplace_back("INSERT,942,ASML,SELL,1.1957,5");
    input.emplace_back("INSERT,943,NL,SELL,3.888,7");
    input.emplace_back("INSERT,945,APPLE,SELL,2.7283,5");
    input.emplace_back("INSERT,949,APPLE,BUY,1.8379,0");
    input.emplace_back("AMEND,760,2.5237,8");
    input.emplace_back("INSERT,957,ASML,SELL,3.9879,4");
    input.emplace_back("INSERT,960,MICROSOFT,BUY,2.8181,1");
    input.emplace_back("PULL,451");
    input.emplace_back("PULL,240");
    input.emplace_back("INSERT,963,ASML,BUY,2.5791,8");
    input.emplace_back("INSERT,964,CAC40,SELL,1.8332,10");
    input.emplace_back("INSERT,967,FR,SELL,2.9468,5");
    input.emplace_back("INSERT,968,PAI,BUY,2.2518,7");
    input.emplace_back("AMEND,147,1.8882,7");
    input.emplace_back("INSERT,970,MICROSOFT,BUY,3.2404,10");
    input.emplace_back("AMEND,724,2.9898,3");
    input.emplace_back("INSERT,975,EG,BUY,1.2567,5");
    input.emplace_back("PULL,489");
    input.emplace_back("INSERT,977,TESLA,SELL,3.9725,7");
    input.emplace_back("INSERT,978,TESLA,BUY,3.992,8");
    input.emplace_back("INSERT,979,FR,BUY,1.3432,2");
    input.emplace_back("INSERT,982,HP,BUY,1.5661,9");
    input.emplace_back("PULL,215");
    input.emplace_back("INSERT,985,PAI,BUY,2.4935,5");
    input.emplace_back("PULL,198");
    input.emplace_back("INSERT,988,EG,BUY,3.9027,4");
    input.emplace_back("INSERT,992,TESLA,BUY,3.7062,2");
    input.emplace_back("INSERT,995,EG,SELL,1.711,4");
    input.emplace_back("PULL,629");
    

    MatchingEngine m;
    m.run(input);

    auto result = m.getResults();
}
int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}