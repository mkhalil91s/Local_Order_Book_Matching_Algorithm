For building :

mkdir build
cd build
cmake ..
make


// /* 


// A limit order is an order to buy or sell a financial instrument for a specified price (or better). It contains these key parameters:
// * Side (Do you want to buy or sell this instrument?)
// * Volume (The maximum number of lots you want to trade)
// * Price (The highest (for a buy) or lowest (for a sell) price you want this order to trade at)

// All active limit orders in the market are maintained in a separate orderbook per instrument. For the purposes of this test, assume 
// all orders are for the same instrument, so you only need to be concerned with a single orderbook

// When a limit order for price P and volume V is entered into the market, it will immediately trade against any orders on the opposite 
// side that have a price better than P (e.g. Less than or equal to P if it's a buy order, or greater than or equal to P if it's a
// sell order), until either V lots have traded or there are no orders left that it can trade with. If the order has any volume left 
// over after it has traded against all viable orders, it will enter the market and stay there until another order trades with its 
// remaining volume

// Incoming orders trade against the best prices on the opposite side first, so for example an incoming buy order will first trade against 
// the sell order with the lowest price, then the next lowest etc. For the purposes of this test, if two orders in the book have the same 
// price, it doesn't matter which one trades first.

// Example:
//     Starting orderbook:
//         Order	Side	Price	Volume
//         A		Sell	10.2		50
//         B		Sell	10.1		5
//         C		Sell	10.1		30
//         D		Buy		10.0		100

//     A buy order arrives for 20 lots at a price of 10.1. It trades entirely against order C and never enters the orderbook.
//     C's volume is reduced by 20 lots:
//         Order	Side	Price	Volume
//         A		Sell	10.2		50
//         B		Sell	10.1		5
//         C		Sell	10.1		10
//         D		Buy		10.0		100

//     Another buy order (E) arrives, this time for 30 lots at a price of 10.1. It trades against orders B and C with 15 lots left over.
//     B and C are deleted. E enters the market with a volume of 15:
//         Order	Side	Price	Volume
//         A		Sell	10.2		50
//         E		Buy		10.1		15
//         D		Buy		10.0		100

// Your task is to simulate an orderbook. Your code must take as input a list of orders entering the market, each with a side,
// price and volume, and report any trades that happen as a result

// We're looking for clear and maintainable code first and foremost. The goal is to see how you would implement new functionality in
// a real codebase, not to test your knowledge of niche language features or performance optimisations. We expect this task to take 
// 1-2 hours

// There is an example template with sample inputs/outputs below that you can start from. Feel free to implement your logic however you
// like, e.g. adding functions, structs/classes or new test cases. To ensure we're able to run your entry, please don't make your code 
// rely on a specific platform/compiler/IDE/third-party library. Beyond that, use whatever tools and C++ version you would like
// */

// class Order
// {
//     //side (buy/sell)
//     //volume
//     //price
// };

// void AddOrder(/*order parameter*/)
// {
//     //This function should print the trades that happen when an order is added
// }

// void TestCase1()
// {
    
//                 // Side Volume  Price
//     AddOrder(); // Buy  15      10.3
//     AddOrder(); // Buy  10      10.2
//     AddOrder(); // Sell 40      10
//     AddOrder(); // Buy  50      10.5
//     AddOrder(); // Sell 30      11

//     /* Expected output:
//     - Order #1 - no trade
//     - Order #2 - no trade
//     - Order #3
//             - 15 lots trade at the price of 10.3
//             - 10 lots trade at the price of 10.2

//     - Order #4 - 15 lots trade at the price of 10
//     - Order #5 - no trades
//     */
// }

// int main()
// {
//     TestCase1();

//     //...

//     return 0;
// }
