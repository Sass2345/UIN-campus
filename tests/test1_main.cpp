#include <catch2/catch_test_macros.hpp>

#include "uincampus/version.hpp"

TEST_CASE("La version du système est valide", "[version]") {
    std::string_view ver = uin::version();

    REQUIRE_FALSE(ver.empty());
    REQUIRE(ver == "0.1.0");
}