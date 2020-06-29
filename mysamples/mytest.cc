//
// Created by houtuanxu on 2020/3/2.
//

#include <memory>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

class TestA {
 public:
  virtual int func1(int x, std::string s1, std::string& s2) { return 5; }

  virtual int func2(int x, std::string s1, std::string& s2) { return 5; }
  virtual ~TestA() {}
};

class MockTestA : public TestA {
 public:
  MOCK_METHOD(int, func1, (int x, std::string s1, std::string& s2), (override));
  MOCK_METHOD(int, func2, (int x, std::string s1, std::string& s2), (override));
};

class A {
 public:
  A(const std::string& str) : _str(str) {}
  void print() { printf("%s\n", _str.c_str()); }
  const std::string& _str;
};

TEST(testmock, basic) {
  A a("eeee");
  a.print();
  std::shared_ptr<const int> sp(new int(3));
  std::string s;
  MockTestA mock;
  EXPECT_CALL(mock, func1).Times(testing::AtLeast(1));
  EXPECT_CALL(mock, func1(testing::_, testing::_, testing::_))
      .Times(testing::AtLeast(1));
  EXPECT_CALL(mock, func2(1, testing::_, testing::_))
      .Times(testing::AtLeast(1));

  mock.func1(3, s, s);
}
