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

    Lob orderbook;

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

    Lob orderbook;

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
    Lob orderbook;

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
    Lob orderbook;

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
    Lob orderbook;

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
    Lob orderbook;

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
    Lob orderbook;

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

    EXPECT_EQ(result.size() , 9);
    EXPECT_EQ(result[0] ,"WEBB,0.3854,4,11,1");
    EXPECT_EQ(result[1] ,"WEBB,0.3854,1,13,1");
    EXPECT_EQ(result[2] ,"===AAPL===");
    EXPECT_EQ(result[3] ,",,21,8");
    EXPECT_EQ(result[4] ,"===TSLA===");
    EXPECT_EQ(result[5] ,"412,31,,");
    EXPECT_EQ(result[6] ,"410.5,27,,");
    EXPECT_EQ(result[7] ,"===WEBB===");
    EXPECT_EQ(result[8] ,",,0.3853,5");
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



int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}