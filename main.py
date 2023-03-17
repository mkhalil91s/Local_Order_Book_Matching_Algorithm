#Simple script to generate test cases

# importing the random module
import random

orders = ["INSERT", "AMEND", "PULL"]
side = ["BUY", "SELL"]
symbols = ["APPLE", "TESLA", "HP", "MICROSOFT", "ASML", "CAC40", "NOKIA"]

#input.emplace_back("INSERT,8,AAPL,BUY,14.235,5");

for i in range (1,1000):
    order = '"' + orders[random.randint(0,0)] + "," + str(i) + "," + symbols[random.randint(0, 6)] +"," + \
    side[random.randint(0, 1)] + "," + str( round (random.uniform(1, 4) , 4) )+ "," + str(random.randint(0,10)) +'"'

    final = "input.emplace_back(" + order + ");"
    print (final)

print(random.randint(0, 9))
