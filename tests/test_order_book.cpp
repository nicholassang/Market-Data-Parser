#include "catch.hpp"

#include "order_book.hpp"

TEST_CASE("Order Book Test"){
    OrderBook book;

    book.addBid(100,10);
    book.addBid(105,20);
    book.addBid(101,5);
    
    REQUIRE(book.bestBid()==105);

    book.addAsk(110,10);
    book.addAsk(108,5);
    
    REQUIRE(book.bestAsk()==108);
}