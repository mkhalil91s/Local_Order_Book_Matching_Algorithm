#include "gtest/gtest.h"
#include "lob.h"

TEST(lobTest, testLob)
{

    Lob sell(1, 2.5, 50);
    EXPECT_EQ(sell.getSide(), 1);
    EXPECT_EQ(sell.getPrice(), 2.5);
    EXPECT_EQ(sell.getVolume(), 50);

    sell.setVolume(2);

    EXPECT_EQ(sell.getSide(), 1);
    EXPECT_EQ(sell.getPrice(), 2.5);
    EXPECT_EQ(sell.getVolume(), 2);
}

TEST(lobTest, testLob2)
{

    Lob sell(1, 2.5, 50);
    EXPECT_EQ(sell.getSide(), 1);
    EXPECT_EQ(sell.getPrice(), 2.5);
    EXPECT_EQ(sell.getVolume(), 50);

    sell.decreaseVolumeBy(45);

    EXPECT_EQ(sell.getSide(), 1);
    EXPECT_EQ(sell.getPrice(), 2.5);
    EXPECT_EQ(sell.getVolume(), 5);

    EXPECT_ANY_THROW(sell.decreaseVolumeBy(6));
}

TEST(lobTest, testUnknownOrderType)
{
    EXPECT_ANY_THROW(Lob sell(3, 2.5, 50));
}

TEST(lobTest, testOrderBookEmptyBuyOrders)
{

    Order orderbook;

    Lob sell3(1, 3.5, 20);
    Lob sell2(1, 2.5, 20);
    Lob sell1(1, 1.5, 20);
    Lob sell4(1, 1.5, 0);

    orderbook.AddOrder(sell1);
    orderbook.AddOrder(sell2);
    orderbook.AddOrder(sell3);

    auto sellbook = orderbook.getSellOrders();
    auto buybook = orderbook.getBuyOrders();

    EXPECT_EQ(sellbook.size(), 3);
    EXPECT_EQ(buybook.size(), 0);

    EXPECT_EQ(sellbook[0].getSide(), 1);
    EXPECT_EQ(sellbook[0].getVolume(), 20);
    EXPECT_EQ(sellbook[0].getPrice(), 1.5);

    EXPECT_EQ(sellbook[1].getSide(), 1);
    EXPECT_EQ(sellbook[1].getVolume(), 20);
    EXPECT_EQ(sellbook[1].getPrice(), 2.5);

    EXPECT_EQ(sellbook[2].getSide(), 1);
    EXPECT_EQ(sellbook[2].getVolume(), 20);
    EXPECT_EQ(sellbook[2].getPrice(), 3.5);
}

TEST(lobTest, testOrderBookEmptySellOrders)
{

    Order orderbook;

    Lob buy1(0, 3.5, 20);
    Lob buy2(0, 2.5, 20);
    Lob buy3(0, 1.5, 20);
    Lob buy4(1, 1.5, 0);

    orderbook.AddOrder(buy1);
    orderbook.AddOrder(buy2);
    orderbook.AddOrder(buy3);

    auto sellbook = orderbook.getSellOrders();
    auto buybook = orderbook.getBuyOrders();

    EXPECT_EQ(sellbook.size(), 0);
    EXPECT_EQ(buybook.size(), 3);

    EXPECT_EQ(buybook[0].getSide(), 0);
    EXPECT_EQ(buybook[0].getVolume(), 20);
    EXPECT_EQ(buybook[0].getPrice(), 3.5);

    EXPECT_EQ(buybook[1].getSide(), 0);
    EXPECT_EQ(buybook[1].getVolume(), 20);
    EXPECT_EQ(buybook[1].getPrice(), 2.5);

    EXPECT_EQ(buybook[2].getSide(), 0);
    EXPECT_EQ(buybook[2].getVolume(), 20);
    EXPECT_EQ(buybook[2].getPrice(), 1.5);
}

TEST(lobTest, testOrderBookSellOrders)
{
    Order orderbook;

    Lob buy1(0, 9.5, 10);
    Lob buy2(0, 20, 10);
    Lob sell1(1, 10.5, 20);

    orderbook.AddOrder(buy1);
    orderbook.AddOrder(buy2);
    orderbook.AddOrder(sell1);

    auto sellbook = orderbook.getSellOrders();
    auto buybook = orderbook.getBuyOrders();

    EXPECT_EQ(sellbook.size(), 1);
    EXPECT_EQ(buybook.size(), 1);

    EXPECT_EQ(sellbook[0].getSide(), 1);
    EXPECT_EQ(sellbook[0].getVolume(), 10);
    EXPECT_EQ(sellbook[0].getPrice(), 10.5);

    EXPECT_EQ(buybook[0].getSide(), 0);
    EXPECT_EQ(buybook[0].getVolume(), 10);
    EXPECT_EQ(buybook[0].getPrice(), 9.5);

    Lob sell2(1, 8, 5);
    orderbook.AddOrder(sell2);

    sellbook = orderbook.getSellOrders();
    buybook = orderbook.getBuyOrders();

    EXPECT_EQ(sellbook.size(), 1);
    EXPECT_EQ(buybook.size(), 1);

    EXPECT_EQ(sellbook[0].getSide(), 1);
    EXPECT_EQ(sellbook[0].getVolume(), 10);
    EXPECT_EQ(sellbook[0].getPrice(), 10.5);

    EXPECT_EQ(buybook[0].getSide(), 0);
    EXPECT_EQ(buybook[0].getVolume(), 5);
    EXPECT_EQ(buybook[0].getPrice(), 9.5);
}

TEST(lobTest, givenExampleTestCase)
{
    Order orderbook;

    Lob buy1(0, 10.3, 15);
    Lob buy2(0, 10.2, 10);
    Lob sell1(1, 10, 40);
    Lob buy3(0, 10.5, 50);
    Lob sell4(1, 11, 30);

    orderbook.AddOrder(buy1);
    orderbook.AddOrder(buy2);
    orderbook.AddOrder(sell1);
    orderbook.AddOrder(buy3);
    orderbook.AddOrder(sell4);

    auto sellbook = orderbook.getSellOrders();
    auto buybook = orderbook.getBuyOrders();

    EXPECT_EQ(sellbook.size(), 1);
    EXPECT_EQ(buybook.size(), 1);

    EXPECT_EQ(sellbook[0].getSide(), 1);
    EXPECT_EQ(sellbook[0].getVolume(), 30);
    EXPECT_EQ(sellbook[0].getPrice(), 11);

    EXPECT_EQ(buybook[0].getSide(), 0);
    EXPECT_EQ(buybook[0].getVolume(), 35);
    EXPECT_EQ(buybook[0].getPrice(), 10.5);
}

TEST(lobTest, givenExampleTestCase2)
{
    Order orderbook;

    orderbook.AddOrder(Lob(1, 10.2, 50));
    orderbook.AddOrder(Lob(1, 10.1, 5));
    orderbook.AddOrder(Lob(1, 10.1, 30));
    orderbook.AddOrder(Lob(0, 10.0, 100));

    orderbook.AddOrder(Lob(0, 10.1, 20));
    orderbook.AddOrder(Lob(0, 10.1, 30));


//Expected output

//         Order	Side	Price	Volume
//         A		Sell	10.2		50
//         E		Buy		10.1		15
//         D		Buy		10.0		100

    auto sellbook = orderbook.getSellOrders();
    auto buybook = orderbook.getBuyOrders();

    EXPECT_EQ(sellbook.size(), 1);
    EXPECT_EQ(buybook.size(), 2);

    EXPECT_EQ(sellbook[0].getSide(), 1);
    EXPECT_EQ(sellbook[0].getVolume(), 50);
    EXPECT_EQ(sellbook[0].getPrice(), 10.2);

    EXPECT_EQ(buybook[0].getSide(), 0);
    EXPECT_EQ(buybook[0].getVolume(), 15);
    EXPECT_EQ(buybook[0].getPrice(), 10.1);

    EXPECT_EQ(buybook[1].getSide(), 0);
    EXPECT_EQ(buybook[1].getVolume(), 100);
    EXPECT_EQ(buybook[1].getPrice(), 10);

}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}