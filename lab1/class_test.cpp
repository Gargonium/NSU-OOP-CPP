#include "class.h"
#include "gtest/gtest.h"

void FillFlatMap(FlatMap& a) {
	a["Hello"] = "World";
	a["Hell"] = "Worl";
	a["Hel"] = "Wor";
	a["He"] = "Wo";
	a["H"] = "W";
}

TEST(FMTest, InitSize) {
	FlatMap a;
	EXPECT_EQ(0, a.getSize());
}

TEST(FMTest, OpInitTest) {
	FlatMap a;
	FillFlatMap(a);
	EXPECT_EQ("World", a["Hello"]);
}

TEST(FMTest, ContainsTest) {
	FlatMap a;
	FillFlatMap(a);
	EXPECT_EQ(false, a.contains("World"));
	EXPECT_EQ(true, a.contains("Hello"));
}

TEST(FMTest, EraseTest) {
	FlatMap a;
	FillFlatMap(a);
	EXPECT_EQ(true, a.contains("Hell"));
	a.erase("Hell");
	EXPECT_EQ(false, a.contains("Hell"));
}

TEST(FMTest, ClearTest) {
	FlatMap a;
	FillFlatMap(a);
	a.clear();
	EXPECT_EQ(0, a.getSize());
}

TEST(FMTest, BeginTest) {
	FlatMap a;
	FillFlatMap(a);
	EXPECT_EQ("W", a.begin());
}

TEST(FMTest, EndTest) {
	FlatMap a;
	FillFlatMap(a);
	EXPECT_EQ("World", a.end());
}

TEST(FMTest, FindTest) {
	FlatMap a;
	FillFlatMap(a);

	EXPECT_EQ("World", a.find("Hello"));
	EXPECT_EQ("W", a.find("H"));
	EXPECT_EQ(a.end(), a.find("Shawarma"));
}
