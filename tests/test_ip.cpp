// #define BOOST_TEST_MODULE MainTests
// #include <boost/test/unit_test.hpp>


// template<class T>
// bool isEqual(const T& first, const T& second){
//     if(first.size()!= second.size()) return false;
//     for(size_t i = 0; i < first.size();++i){
//         if(first[i] != second[i]) return false;
//     }
//     return true;
// }

// BOOST_AUTO_TEST_CASE(isEqualTest){
//     std::vector<int> a = {1,2,3};
//     std::vector<int> b(a.begin(), a.end());
//     BOOST_TEST(isEqual(a, b));
//     b.pop_back();
//     BOOST_TEST(!isEqual(a,b));
//     b.push_back(1);
//     BOOST_TEST(!isEqual(a,b));

// }

// BOOST_AUTO_TEST_CASE(SplitTest) {
//     std::string input = "test_case";
//     std::vector<std::string> output = {"test", "case"};
//     BOOST_TEST(isEqual( output, split(input, '_') ));
//     BOOST_TEST(isEqual( {"11"}, split("11", '.')));
//     BOOST_TEST(isEqual( {"", "", ""}, split("..", '.')));
// }

// BOOST_AUTO_TEST_CASE(FiltersTest) {
    
//     BOOST_TEST(filter({1,1,1,1}, 1));
//     BOOST_TEST(filter({1,0,1,1}, -1, 0));
//     BOOST_TEST(!filter({0,1,1,1}, 1));

//     BOOST_TEST(filter_any({0,0,0,1}, 1));
//     BOOST_TEST(!filter_any({0,0,0,0}, 1));
// }
