#include "catch.hpp"

#include "ring_buffer.hpp"

TEST_CASE("Push Pop")
{
    RingBuffer<int,4> rb;

    REQUIRE(rb.push(1));
    REQUIRE(rb.push(2));

    int x;

    REQUIRE(rb.pop(x));
    REQUIRE(x == 1);

    REQUIRE(rb.pop(x));
    REQUIRE(x == 2);

    REQUIRE(rb.empty());
}

TEST_CASE("FIFO")
{
    RingBuffer<int,8> rb;

    for(int i=0;i<5;i++)
        REQUIRE(rb.push(i));

    int x;

    for(int i=0;i<5;i++)
    {
        REQUIRE(rb.pop(x));
        REQUIRE(x==i);
    }
}

TEST_CASE("Empty")
{
    RingBuffer<int,4> rb;

    int x;

    REQUIRE_FALSE(rb.pop(x));
}

TEST_CASE("Full")
{
    RingBuffer<int,4> rb;

    REQUIRE(rb.push(1));
    REQUIRE(rb.push(2));
    REQUIRE(rb.push(3));

    REQUIRE_FALSE(rb.push(4));
}

TEST_CASE("WrapAround")
{
    RingBuffer<int,4> rb;

    int x;

    rb.push(1);
    rb.push(2);

    rb.pop(x);
    rb.pop(x);

    rb.push(3);
    rb.push(4);

    REQUIRE(rb.pop(x));
    REQUIRE(x==3);

    REQUIRE(rb.pop(x));
    REQUIRE(x==4);
}