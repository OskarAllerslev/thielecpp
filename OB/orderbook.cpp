#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <cstdlib>
#include <ctime>

enum class OrderType {BUY, SELL};

struct Order {
    int id;
    double price;
    int quantity;
    OrderType type;

    Order(int id, double price, int quantity, OrderType type)
    : id(id), price(price), quantity(quantity), type(type) {}
};

class OrderBook {
    private:
        std::map<double, std::vector<Order>, std::greater<double>> buyOrders; // Max-heap for BUY orders
        std::map<double, std::vector<Order>> sellOrders; // Min-heap for SELL orders
        int orderId = 1;
    
    public:
        void addOrder(double price, int quantity, OrderType type) {
            Order order(orderId++, price, quantity, type);
            if (type == OrderType::BUY) {
                buyOrders[price].push_back(order);
            } else {
                sellOrders[price].push_back(order);
            }
        }
    
        void matchOrders() {
            while (!buyOrders.empty() && !sellOrders.empty()) {
                auto bestBuy = buyOrders.begin();  // Highest bid price
                auto bestSell = sellOrders.begin(); // Lowest ask price
    
                if (bestBuy->first >= bestSell->first) { // Match found
                    int tradedQty = std::min(bestBuy->second.front().quantity, bestSell->second.front().quantity);
    
                    std::cout << "Trade executed: " << tradedQty << " units at $" << bestSell->first << std::endl;
    
                    // Reduce quantity or remove order
                    bestBuy->second.front().quantity -= tradedQty;
                    bestSell->second.front().quantity -= tradedQty;
    
                    if (bestBuy->second.front().quantity == 0) bestBuy->second.erase(bestBuy->second.begin());
                    if (bestSell->second.front().quantity == 0) bestSell->second.erase(bestSell->second.begin());
    
                    if (bestBuy->second.empty()) buyOrders.erase(bestBuy);
                    if (bestSell->second.empty()) sellOrders.erase(bestSell);
                } else {
                    break; // No matching orders
                }
            }
        }

        void printOrderBook() {
            std::cout << "\nOrder Book:\n";
            std::cout << "SELL Orders:\n";
            for (const auto& entry : sellOrders) {
                std::cout << "Price: " << entry.first << ", Qty: " << entry.second.front().quantity << std::endl;
            }
            std::cout << "----------------\n";
            std::cout << "BUY Orders:\n";
            for (const auto& entry : buyOrders) {
                std::cout << "Price: " << entry.first << ", Qty: " << entry.second.front().quantity << std::endl;
            }
            std::cout << "----------------\n";
        }
    };

    void simulateMarket(OrderBook& orderBook, int numOrders) {
        std::srand(std::time(0)); // Seed for randomness
    
        for (int i = 0; i < numOrders; i++) {
            double price = 100 + (std::rand() % 100) / 10.0; // Random price from 100 to 110
            int quantity = (std::rand() % 10) + 1; // Random quantity from 1 to 10
            OrderType type = (std::rand() % 2) ? OrderType::BUY : OrderType::SELL;
    
            orderBook.addOrder(price, quantity, type);
        }
    
        orderBook.matchOrders();
        orderBook.printOrderBook();
    }
    
    int main() {
        OrderBook orderBook;
        simulateMarket(orderBook, 10);
        return 0;
    }
    