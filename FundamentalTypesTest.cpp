#define CATCH_CONFIG_MAIN
#include<catch2/catch.hpp>

TEST_CASE("fundamental types", "") {
	REQUIRE(sizeof(bool) == 1);
	REQUIRE(sizeof(char) == 1);
	REQUIRE(sizeof(wchar_t) == 2);
	REQUIRE(sizeof(int) == 4);
	REQUIRE(sizeof(long long) == 8);
	REQUIRE(sizeof(double) == 8);
	REQUIRE(sizeof(long double) == 10);
}
