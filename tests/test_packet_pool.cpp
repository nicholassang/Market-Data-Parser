#include "catch.hpp"

#include "packet_pool.hpp"

TEST_CASE("Acquire Release")
{
    PacketPool<4> pool;

    auto* p1 = pool.acquire();

    REQUIRE(p1 != nullptr);

    pool.release(p1);

    auto* p2 = pool.acquire();

    REQUIRE(p2 != nullptr);
}

TEST_CASE("Pool Full")
{
    PacketPool<4> pool;

    [[maybe_unused]] auto* a = pool.acquire();
    [[maybe_unused]] auto* b = pool.acquire();
    [[maybe_unused]] auto* c = pool.acquire();
    [[maybe_unused]] auto* d = pool.acquire();

    REQUIRE(pool.acquire() == nullptr);

    pool.release(a);

    REQUIRE(pool.acquire() != nullptr);
}