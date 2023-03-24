#Simple script to generate test cases

# importing the random module
import random

orders = ["INSERT", "AMEND", "PULL"]
side = ["BUY", "SELL"]
symbols = ["APPLE", "TESLA", "HP", "MICROSOFT", "ASML", "CAC40", "NOKIA" , "EG" , "FR" , "NL" , "AMS" , "PAI"]

#input.emplace_back("INSERT,8,AAPL,BUY,14.235,5");
#input.emplace_back("AMEND,1,45.95,3");
ordersInPlace = list()
for i in range (1,10000000):
    orderType = random.randint(0,2)
    order = ""

    if orderType == 0:
        ordersInPlace.append(i)
        order +=  orders[orderType] + "," + str(i) + "," + symbols[random.randint(0, 11)] +"," + \
            side[random.randint(0, 1)] + "," + str( round (random.uniform(1, 4) , 4) )+ "," + str(random.randint(0,10)) 

    elif orderType == 1:
        amendOrder = random.randint(0,i-1)
        if amendOrder in ordersInPlace:
            order +=  orders[orderType] + "," + str(amendOrder) + "," +str( round (random.uniform(1, 4) , 4) ) \
               + "," + str(random.randint(0,10)) 
        else:
            continue

    elif orderType == 2:
        pullOrderNumber = random.randint(0,i-1)
        if pullOrderNumber in ordersInPlace:
            ordersInPlace.remove(pullOrderNumber)
            order +=  orders[orderType] + "," + str(pullOrderNumber) 
        else:
            continue

    if order != "":
        final = "input.emplace_back(" + order + ");"
        print(order)


