#include <gtest/gtest.h>
#include "Hamming.hpp"

namespace rosneuro {

class HammingTestSuite : public ::testing::Test {
    public:
        HammingTestSuite() {}
        ~HammingTestSuite() {}
        void SetUp() { hamming_filter = new Hamming <double>(); }
        void TearDown() { delete hamming_filter; }
        Hamming <double>* hamming_filter;
};

TEST_F(HammingTestSuite, Constructor) {
    ASSERT_EQ(hamming_filter->name_, "hamming");
    ASSERT_FALSE(hamming_filter->is_window_set_);
}

TEST_F(HammingTestSuite, Configure) {
    ASSERT_TRUE(hamming_filter->configure());
}

TEST_F(HammingTestSuite, ApplyWithValidWindow) {
    DynamicMatrix<double> inputMatrix(3, 3);
    inputMatrix << 1, 2, 3,
                   4, 5, 6,
                   7, 8, 9;
    DynamicMatrix<double> result = hamming_filter->apply(inputMatrix);

    ASSERT_EQ(result.rows(), inputMatrix.rows());
    ASSERT_EQ(result.cols(), inputMatrix.cols());

    DynamicMatrix<double> expected(3, 3);
    expected << 0.08, 0.16, 0.24,
                4,    5,    6,
                0.56, 0.64, 0.72;

    ASSERT_TRUE(result.isApprox(expected, 0.01));
}

TEST_F(HammingTestSuite, ApplyWithoutWindow) {
    DynamicMatrix<double> inputMatrix(-1, 0);
    ASSERT_THROW(hamming_filter->apply(inputMatrix), std::bad_alloc);
}

TEST_F(HammingTestSuite, CreateWindowWithValidSamples) {
    ASSERT_TRUE(hamming_filter->create_window(1));
}

TEST_F(HammingTestSuite, CreateWindowWithInvalidSamples) {
    ASSERT_THROW(hamming_filter->create_window(-1), std::bad_alloc);
}

}

int main(int argc, char **argv) {
    ros::init(argc, argv, "test_hamming");
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}