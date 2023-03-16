#include "gtest/gtest.h"
#include "lob.h"

// TEST(lobTest, testLob)
// {

//     Order buy1(1, "A", "BUY", "2.5", 50);
//     EXPECT_EQ(buy1.getOrderId(), 1);
//     EXPECT_EQ(buy1.getSymbole(), "A");
//     EXPECT_EQ(buy1.getSide(), "BUY");
//     EXPECT_EQ(buy1.getPrice(), "2.5");
//     EXPECT_EQ(buy1.getVolume(), 50);

//     Order buy2(1, "A", "BUY", "2.1234567", 50);
//     EXPECT_EQ(buy2.getOrderId(), 1);
//     EXPECT_EQ(buy2.getSymbole(), "A");
//     EXPECT_EQ(buy2.getSide(), "BUY");
//     EXPECT_EQ(buy2.getPrice(), "2.1234");
//     EXPECT_EQ(buy2.getVolume(), 50);

//     Order sell3(1, "A", "SELL", "2.123", 50);
//     EXPECT_EQ(sell3.getOrderId(), 1);
//     EXPECT_EQ(sell3.getSymbole(), "A");
//     EXPECT_EQ(sell3.getSide(), "SELL");
//     EXPECT_EQ(sell3.getPrice(), "2.123");
//     EXPECT_EQ(sell3.getVolume(), 50);

//     Order sell4(1, "A", "SELL", "2.12", 50);
//     EXPECT_EQ(sell4.getOrderId(), 1);
//     EXPECT_EQ(sell4.getSymbole(), "A");
//     EXPECT_EQ(sell4.getSide(), "SELL");
//     EXPECT_EQ(sell4.getPrice(), "2.12");
//     EXPECT_EQ(sell4.getVolume(), 50);
// }

// TEST(lobTest, testLob2)
// {

//     Order sell3(1, "A", "SELL", "2.123", 50);
//     EXPECT_EQ(sell3.getOrderId(), 1);
//     EXPECT_EQ(sell3.getSymbole(), "A");
//     EXPECT_EQ(sell3.getSide(), "SELL");
//     EXPECT_EQ(sell3.getPrice(), "2.123");
//     EXPECT_EQ(sell3.getVolume(), 50);

//     sell3.decreaseVolumeBy(45);

//     EXPECT_EQ(sell3.getOrderId(), 1);
//     EXPECT_EQ(sell3.getSymbole(), "A");
//     EXPECT_EQ(sell3.getSide(), "SELL");
//     EXPECT_EQ(sell3.getPrice(), "2.123");
//     EXPECT_EQ(sell3.getVolume(), 5);

//     EXPECT_ANY_THROW(sell3.decreaseVolumeBy(6));
// }

// TEST(lobTest, testOrderBookEmptyBuyOrders)
// {

//     Lob orderbook;

//     orderbook.AddOrder(1, "A", "SELL", "8.5", 20);
//     orderbook.AddOrder(2, "A", "SELL", "9.5", 20);
//     orderbook.AddOrder(3, "A", "SELL", "10.5", 20);
//     orderbook.AddOrder(4, "A", "SELL", "8.5", 20);

//     auto sellbook = orderbook.getSellOrders();
//     auto buybook = orderbook.getBuyOrders();

//     auto sellbookmap = orderbook.getSellOrdersMap();
//     auto buybookmap = orderbook.getBuyOrdersMap();

//     EXPECT_EQ(sellbook.size(), 4);
//     EXPECT_EQ(buybook.size(), 0);

//     EXPECT_EQ(sellbookmap.size(), 4);
//     EXPECT_EQ(buybookmap.size(), 0);

//     auto it = sellbook.begin();
//     std::advance(it, 0);

//     EXPECT_EQ((*it)->getOrderId(), 1);
//     EXPECT_EQ((*it)->getSymbole(), "A");
//     EXPECT_EQ((*it)->getSide(), "SELL");
//     EXPECT_EQ((*it)->getPrice(), "8.5");
//     EXPECT_EQ((*it)->getVolume(), 20);

//     std::advance(it, 1);

//     EXPECT_EQ((*it)->getOrderId(), 4);
//     EXPECT_EQ((*it)->getSymbole(), "A");
//     EXPECT_EQ((*it)->getSide(), "SELL");
//     EXPECT_EQ((*it)->getPrice(), "8.5");
//     EXPECT_EQ((*it)->getVolume(), 20);

//     std::advance(it, 1);

//     EXPECT_EQ((*it)->getOrderId(), 2);
//     EXPECT_EQ((*it)->getSymbole(), "A");
//     EXPECT_EQ((*it)->getSide(), "SELL");
//     EXPECT_EQ((*it)->getPrice(), "9.5");
//     EXPECT_EQ((*it)->getVolume(), 20);

//     std::advance(it, 1);

//     EXPECT_EQ((*it)->getOrderId(), 3);
//     EXPECT_EQ((*it)->getSymbole(), "A");
//     EXPECT_EQ((*it)->getSide(), "SELL");
//     EXPECT_EQ((*it)->getPrice(), "10.5");
//     EXPECT_EQ((*it)->getVolume(), 20);

//     EXPECT_ANY_THROW(orderbook.AddOrder(4, "A", "SELL", "5.5", 0));
// }

// TEST(lobTest, testOrderBookEmptySellOrders)
// {

//     Lob orderbook;

//     orderbook.AddOrder(0, "A", "BUY", "4.5", 0);
//     orderbook.AddOrder(1, "A", "BUY", "3.5", 20);
//     orderbook.AddOrder(2, "A", "BUY", "2.5", 20);
//     orderbook.AddOrder(3, "A", "BUY", "1.5", 20);
//     orderbook.AddOrder(4, "A", "BUY", "1.5", 0);
//     orderbook.AddOrder(5, "A", "BUY", "3.5", 20);

//     auto sellbook = orderbook.getSellOrders();
//     auto buybook = orderbook.getBuyOrders();

//     auto sellbookmap = orderbook.getSellOrdersMap();
//     auto buybookmap = orderbook.getBuyOrdersMap();

//     EXPECT_EQ(sellbook.size(), 0);
//     EXPECT_EQ(buybook.size(), 6);
//     EXPECT_EQ(sellbookmap.size(), 0);
//     EXPECT_EQ(buybookmap.size(), 6);

//     auto it = buybook.begin();
//     std::advance(it, 0);

//     EXPECT_EQ((*it)->getOrderId(), 0);
//     EXPECT_EQ((*it)->getSymbole(), "A");
//     EXPECT_EQ((*it)->getSide(), "BUY");
//     EXPECT_EQ((*it)->getPrice(), "4.5");
//     EXPECT_EQ((*it)->getVolume(), 0);

//     std::advance(it, 1);

//     EXPECT_EQ((*it)->getOrderId(), 1);
//     EXPECT_EQ((*it)->getSymbole(), "A");
//     EXPECT_EQ((*it)->getSide(), "BUY");
//     EXPECT_EQ((*it)->getPrice(), "3.5");
//     EXPECT_EQ((*it)->getVolume(), 20);

//     std::advance(it, 1);

//     EXPECT_EQ((*it)->getOrderId(), 5);
//     EXPECT_EQ((*it)->getSymbole(), "A");
//     EXPECT_EQ((*it)->getSide(), "BUY");
//     EXPECT_EQ((*it)->getPrice(), "3.5");
//     EXPECT_EQ((*it)->getVolume(), 20);

//     std::advance(it, 1);

//     EXPECT_EQ((*it)->getOrderId(), 2);
//     EXPECT_EQ((*it)->getSymbole(), "A");
//     EXPECT_EQ((*it)->getSide(), "BUY");
//     EXPECT_EQ((*it)->getPrice(), "2.5");
//     EXPECT_EQ((*it)->getVolume(), 20);

//     std::advance(it, 1);

//     EXPECT_EQ((*it)->getOrderId(), 3);
//     EXPECT_EQ((*it)->getSymbole(), "A");
//     EXPECT_EQ((*it)->getSide(), "BUY");
//     EXPECT_EQ((*it)->getPrice(), "1.5");
//     EXPECT_EQ((*it)->getVolume(), 20);

//     std::advance(it, 1);

//     EXPECT_EQ((*it)->getOrderId(), 4);
//     EXPECT_EQ((*it)->getSymbole(), "A");
//     EXPECT_EQ((*it)->getSide(), "BUY");
//     EXPECT_EQ((*it)->getPrice(), "1.5");
//     EXPECT_EQ((*it)->getVolume(), 0);

//     EXPECT_ANY_THROW(orderbook.AddOrder(5, "A", "BUY", "3.5", 20));
// }

// TEST(lobTest, testOrderBookSellOrders)
// {
//     Lob orderbook;

//     orderbook.AddOrder(1, "A", "BUY", "9.5", 10);
//     orderbook.AddOrder(2, "A", "BUY", "20", 10);
//     orderbook.AddOrder(3, "A", "SELL", "10.5", 20);

//     auto sellbook = orderbook.getSellOrders();
//     auto buybook = orderbook.getBuyOrders();

//     auto sellbookmap = orderbook.getSellOrdersMap();
//     auto buybookmap = orderbook.getBuyOrdersMap();

//     EXPECT_EQ(sellbook.size(), 1);
//     EXPECT_EQ(buybook.size(), 2);
//     EXPECT_EQ(sellbookmap.size(), 1);
//     EXPECT_EQ(buybookmap.size(), 2);

//     auto it = sellbook.begin();
//     std::advance(it, 0);

//     EXPECT_EQ((*it)->getOrderId(), 3);
//     EXPECT_EQ((*it)->getSymbole(), "A");
//     EXPECT_EQ((*it)->getSide(), "SELL");
//     EXPECT_EQ((*it)->getPrice(), "10.5");
//     EXPECT_EQ((*it)->getVolume(), 10);

//     auto it2 = buybook.begin();
//     std::advance(it, 0);

//     EXPECT_EQ((*it2)->getOrderId(), 2);
//     EXPECT_EQ((*it2)->getSymbole(), "A");
//     EXPECT_EQ((*it2)->getSide(), "BUY");
//     EXPECT_EQ((*it2)->getPrice(), "20");
//     EXPECT_EQ((*it2)->getVolume(), 0);

//     std::advance(it2, 1);

//     EXPECT_EQ((*it2)->getOrderId(), 1);
//     EXPECT_EQ((*it2)->getSymbole(), "A");
//     EXPECT_EQ((*it2)->getSide(), "BUY");
//     EXPECT_EQ((*it2)->getPrice(), "9.5");
//     EXPECT_EQ((*it2)->getVolume(), 10);

//     orderbook.AddOrder(4, "A", "SELL", "8", 5);

//     sellbook = orderbook.getSellOrders();
//     buybook = orderbook.getBuyOrders();

//     sellbookmap = orderbook.getSellOrdersMap();
//     buybookmap = orderbook.getBuyOrdersMap();
//     EXPECT_EQ(sellbook.size(), 2);
//     EXPECT_EQ(buybook.size(), 2);
//     EXPECT_EQ(sellbookmap.size(), 2);
//     EXPECT_EQ(buybookmap.size(), 2);

//     it = sellbook.begin();
//     std::advance(it, 0);

//     EXPECT_EQ((*it)->getOrderId(), 4);
//     EXPECT_EQ((*it)->getSymbole(), "A");
//     EXPECT_EQ((*it)->getSide(), "SELL");
//     EXPECT_EQ((*it)->getPrice(), "8");
//     EXPECT_EQ((*it)->getVolume(), 0);

//     std::advance(it, 1);

//     EXPECT_EQ((*it)->getOrderId(), 3);
//     EXPECT_EQ((*it)->getSymbole(), "A");
//     EXPECT_EQ((*it)->getSide(), "SELL");
//     EXPECT_EQ((*it)->getPrice(), "10.5");
//     EXPECT_EQ((*it)->getVolume(), 10);

//     it2 = buybook.begin();
//     std::advance(it, 0);

//     EXPECT_EQ((*it2)->getOrderId(), 2);
//     EXPECT_EQ((*it2)->getSymbole(), "A");
//     EXPECT_EQ((*it2)->getSide(), "BUY");
//     EXPECT_EQ((*it2)->getPrice(), "20");
//     EXPECT_EQ((*it2)->getVolume(), 0);

//     std::advance(it2, 1);

//     EXPECT_EQ((*it2)->getOrderId(), 1);
//     EXPECT_EQ((*it2)->getSymbole(), "A");
//     EXPECT_EQ((*it2)->getSide(), "BUY");
//     EXPECT_EQ((*it2)->getPrice(), "9.5");
//     EXPECT_EQ((*it2)->getVolume(), 5);
// }

// TEST(lobTest, testDeleteOrder)
// {
//     Lob orderbook;

//     orderbook.AddOrder(1, "A", "BUY", "9.5", 10);
//     orderbook.AddOrder(2, "A", "BUY", "20", 10);
//     orderbook.AddOrder(3, "A", "SELL", "10.5", 20);

//     auto sellbook = orderbook.getSellOrders();
//     auto buybook = orderbook.getBuyOrders();

//     auto sellbookmap = orderbook.getSellOrdersMap();
//     auto buybookmap = orderbook.getBuyOrdersMap();

//     EXPECT_EQ(sellbook.size(), 1);
//     EXPECT_EQ(buybook.size(), 2);
//     EXPECT_EQ(sellbookmap.size(), 1);
//     EXPECT_EQ(buybookmap.size(), 2);

//     orderbook.DeleteOrder(1);
//     orderbook.DeleteOrder(2);
//     orderbook.DeleteOrder(3);

//     sellbook = orderbook.getSellOrders();
//     buybook = orderbook.getBuyOrders();

//     sellbookmap = orderbook.getSellOrdersMap();
//     buybookmap = orderbook.getBuyOrdersMap();

//     EXPECT_EQ(sellbook.size(), 0);
//     EXPECT_EQ(buybook.size(), 0);
//     EXPECT_EQ(sellbookmap.size(), 0);
//     EXPECT_EQ(buybookmap.size(), 0);

//     EXPECT_ANY_THROW(orderbook.DeleteOrder(3));
// }

// TEST(lobTest, testDeleteOrder2)
// {
//     Lob orderbook;

//     orderbook.AddOrder(1, "A", "BUY", "9.5", 10);
//     orderbook.AddOrder(2, "A", "BUY", "20", 10);
//     orderbook.AddOrder(3, "A", "SELL", "10.5", 20);

//     auto sellbook = orderbook.getSellOrders();
//     auto buybook = orderbook.getBuyOrders();

//     auto sellbookmap = orderbook.getSellOrdersMap();
//     auto buybookmap = orderbook.getBuyOrdersMap();

//     EXPECT_EQ(sellbook.size(), 1);
//     EXPECT_EQ(buybook.size(), 2);
//     EXPECT_EQ(sellbookmap.size(), 1);
//     EXPECT_EQ(buybookmap.size(), 2);

//     orderbook.DeleteOrder(2);

//     sellbook = orderbook.getSellOrders();
//     buybook = orderbook.getBuyOrders();

//     sellbookmap = orderbook.getSellOrdersMap();
//     buybookmap = orderbook.getBuyOrdersMap();

//     EXPECT_EQ(sellbook.size(), 1);
//     EXPECT_EQ(buybook.size(), 1);
//     EXPECT_EQ(sellbookmap.size(), 1);
//     EXPECT_EQ(buybookmap.size(), 1);

//     auto it = buybook.begin();
//     std::advance(it, 0);

//     EXPECT_EQ((*it)->getOrderId(), 1);
//     EXPECT_EQ((*it)->getSymbole(), "A");
//     EXPECT_EQ((*it)->getSide(), "BUY");
//     EXPECT_EQ((*it)->getPrice(), "9.5");
//     EXPECT_EQ((*it)->getVolume(), 10);

//     auto it2 = sellbook.begin();
//     std::advance(it2, 0);

//     EXPECT_EQ((*it2)->getOrderId(), 3);
//     EXPECT_EQ((*it2)->getSymbole(), "A");
//     EXPECT_EQ((*it2)->getSide(), "SELL");
//     EXPECT_EQ((*it2)->getPrice(), "10.5");
//     EXPECT_EQ((*it2)->getVolume(), 10);

//     EXPECT_ANY_THROW(orderbook.DeleteOrder(2));
// }

// TEST(lobTest, givenExampleTestCase)
// {
//     Lob orderbook;

//     orderbook.AddOrder(1, "A", "BUY", "10.3", 15);
//     orderbook.AddOrder(2, "A", "BUY", "10.2", 10);
//     orderbook.AddOrder(3, "A", "SELL", "10", 40);
//     orderbook.AddOrder(4, "A", "BUY", "10.5", 50);
//     orderbook.AddOrder(5, "A", "SELL", "11", 30);

//     auto sellbook = orderbook.getSellOrders();
//     auto buybook = orderbook.getBuyOrders();

//     auto sellbookmap = orderbook.getSellOrdersMap();
//     auto buybookmap = orderbook.getBuyOrdersMap();

//     auto it = buybook.begin();
//     std::advance(it, 0);

//     EXPECT_EQ((*it)->getOrderId(), 4);
//     EXPECT_EQ((*it)->getSymbole(), "A");
//     EXPECT_EQ((*it)->getSide(), "BUY");
//     EXPECT_EQ((*it)->getPrice(), "10.5");
//     EXPECT_EQ((*it)->getVolume(), 35);

//     std::advance(it, 1);

//     EXPECT_EQ((*it)->getOrderId(), 1);
//     EXPECT_EQ((*it)->getSymbole(), "A");
//     EXPECT_EQ((*it)->getSide(), "BUY");
//     EXPECT_EQ((*it)->getPrice(), "10.3");
//     EXPECT_EQ((*it)->getVolume(), 0);

//     std::advance(it, 1);

//     EXPECT_EQ((*it)->getOrderId(), 2);
//     EXPECT_EQ((*it)->getSymbole(), "A");
//     EXPECT_EQ((*it)->getSide(), "BUY");
//     EXPECT_EQ((*it)->getPrice(), "10.2");
//     EXPECT_EQ((*it)->getVolume(), 0);

//     auto it2 = sellbook.begin();
//     std::advance(it2, 0);

//     EXPECT_EQ((*it2)->getOrderId(), 3);
//     EXPECT_EQ((*it2)->getSymbole(), "A");
//     EXPECT_EQ((*it2)->getSide(), "SELL");
//     EXPECT_EQ((*it2)->getPrice(), "10");
//     EXPECT_EQ((*it2)->getVolume(), 0);

//     std::advance(it2, 1);

//     EXPECT_EQ((*it2)->getOrderId(), 5);
//     EXPECT_EQ((*it2)->getSymbole(), "A");
//     EXPECT_EQ((*it2)->getSide(), "SELL");
//     EXPECT_EQ((*it2)->getPrice(), "11");
//     EXPECT_EQ((*it2)->getVolume(), 30);

//     orderbook.DisplayLob();
//     orderbook.DisplayBidValues();

// }

// TEST(lobTest, testAmendOrder)
// {
//     Lob orderbook;

//     orderbook.AddOrder(1, "A", "BUY", "9.5", 10);
//     orderbook.AddOrder(2, "A", "BUY", "20", 10);
//     orderbook.AddOrder(3, "A", "SELL", "10.5", 20);

//     auto sellbook = orderbook.getSellOrders();
//     auto buybook = orderbook.getBuyOrders();

//     auto sellbookmap = orderbook.getSellOrdersMap();
//     auto buybookmap = orderbook.getBuyOrdersMap();

//     EXPECT_EQ(sellbook.size(), 1);
//     EXPECT_EQ(buybook.size(), 2);
//     EXPECT_EQ(sellbookmap.size(), 1);
//     EXPECT_EQ(buybookmap.size(), 2);

//     orderbook.AmendOrder(1, "10.5", 5);

//     sellbook = orderbook.getSellOrders();
//     buybook = orderbook.getBuyOrders();

//     sellbookmap = orderbook.getSellOrdersMap();
//     buybookmap = orderbook.getBuyOrdersMap();

//     EXPECT_EQ(sellbook.size(), 1);
//     EXPECT_EQ(buybook.size(), 2);
//     EXPECT_EQ(sellbookmap.size(), 1);
//     EXPECT_EQ(buybookmap.size(), 2);

//     auto it = buybook.begin();
//     std::advance(it, 0);

//     EXPECT_EQ((*it)->getOrderId(), 2);
//     EXPECT_EQ((*it)->getSymbole(), "A");
//     EXPECT_EQ((*it)->getSide(), "BUY");
//     EXPECT_EQ((*it)->getPrice(), "20");
//     EXPECT_EQ((*it)->getVolume(), 0);

//     std::advance(it, 1);

//     EXPECT_EQ((*it)->getOrderId(), 1);
//     EXPECT_EQ((*it)->getSymbole(), "A");
//     EXPECT_EQ((*it)->getSide(), "BUY");
//     EXPECT_EQ((*it)->getPrice(), "10.5");
//     EXPECT_EQ((*it)->getVolume(), 0);

//     auto it2 = sellbook.begin();
//     std::advance(it2, 0);

//     EXPECT_EQ((*it2)->getOrderId(), 3);
//     EXPECT_EQ((*it2)->getSymbole(), "A");
//     EXPECT_EQ((*it2)->getSide(), "SELL");
//     EXPECT_EQ((*it2)->getPrice(), "10.5");
//     EXPECT_EQ((*it2)->getVolume(), 5);

//     orderbook.DeleteEmptyOrderIds();

//     sellbook = orderbook.getSellOrders();
//     buybook = orderbook.getBuyOrders();

//     sellbookmap = orderbook.getSellOrdersMap();
//     buybookmap = orderbook.getBuyOrdersMap();

//     EXPECT_EQ(sellbook.size(), 1);
//     EXPECT_EQ(buybook.size(), 0);
//     EXPECT_EQ(sellbookmap.size(), 1);
//     EXPECT_EQ(buybookmap.size(), 0);

//     it2 = sellbook.begin();
//     std::advance(it2, 0);

//     EXPECT_EQ((*it2)->getOrderId(), 3);
//     EXPECT_EQ((*it2)->getSymbole(), "A");
//     EXPECT_EQ((*it2)->getSide(), "SELL");
//     EXPECT_EQ((*it2)->getPrice(), "10.5");
//     EXPECT_EQ((*it2)->getVolume(), 5);


// }

TEST(lobTest, testParsing)
{
    MatchingEngine m;

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




    m.run(input);    
}
// TEST(lobTest, givenExampleTestCase2)
// {
//     Lob orderbook;

//     orderbook.AddOrder(Order(1, 10.2, 50));
//     orderbook.AddOrder(Order(1, 10.1, 5));
//     orderbook.AddOrder(Order(1, 10.1, 30));
//     orderbook.AddOrder(Order(0, 10.0, 100));

//     orderbook.AddOrder(Order(0, 10.1, 20));
//     orderbook.AddOrder(Order(0, 10.1, 30));

//     // Expected output

//     //         Order	Side	Price	Volume
//     //         A		Sell	10.2		50
//     //         E		Buy		10.1		15
//     //         D		Buy		10.0		100

//     auto sellbook = orderbook.getSellOrders();
//     auto buybook = orderbook.getBuyOrders();

//     EXPECT_EQ(sellbook.size(), 1);
//     EXPECT_EQ(buybook.size(), 2);

//     EXPECT_EQ(sellbook[0].getSide(), 1);
//     EXPECT_EQ(sellbook[0].getVolume(), 50);
//     EXPECT_EQ(sellbook[0].getPrice(), 10.2);

//     EXPECT_EQ(buybook[0].getSide(), 0);
//     EXPECT_EQ(buybook[0].getVolume(), 15);
//     EXPECT_EQ(buybook[0].getPrice(), 10.1);

//     EXPECT_EQ(buybook[1].getSide(), 0);
//     EXPECT_EQ(buybook[1].getVolume(), 100);
//     EXPECT_EQ(buybook[1].getPrice(), 10);
// }

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}