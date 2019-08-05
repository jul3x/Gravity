//
// Created by jprolejko on 22.07.19.
//

#include <cmath>

#include <gtest/gtest.h>

#include <physics/RungeKuttaSolver.h>

class SimpleEquation : public IEquation<float, float> {

public:
    SimpleEquation() { size_ = 1; }

    virtual std::vector<float> operator()(const std::vector<float> &values, 
                                          const EquationParameters<float> &parameters) {
        // y' = my
        return {parameters.get().front() * values.front()};
    }
};

class SimpleEquation2 : public IEquation<float, float> {

public:
    SimpleEquation2() { size_ = 2; }

    virtual std::vector<float> operator()(const std::vector<float> &values, 
                                          const EquationParameters<float> &parameters) {
        // x' = 0
        // y' = my
        std::vector<float> vec;
        vec.resize(2);
        vec.at(0) = 0.0f;
        vec.at(1) = parameters.get().front() * values.back();
        return vec;
    }
};



TEST(RungeKuttaSolverTest, EquationParameters) {
    EquationParameters<int> params_0;
    EXPECT_EQ(params_0.get().size(), std::vector<int>{}.size());

    EquationParameters<int> params_1(0);
    EXPECT_EQ(params_1.get().size(), std::vector<int>{0}.size());

    std::vector<int> values = {0, 1, 2};
    EquationParameters<int> params_2(values);
    EXPECT_EQ(params_2.get().size(), values.size());

    std::vector<float> values_f = {0.0, 1.0, 2.0, 3.0};
    EquationParameters<float> params_float(values_f);
    EXPECT_EQ(params_float.get().size(), values_f.size());
}

TEST(RungeKuttaSolverTest, RungeKuttaSolver) {
    SimpleEquation eq{};
    RungeKuttaSolver<float, float> solver{eq};
    
    std::vector<float> values;
    EXPECT_THROW(solver.apply(values, 0.0f, {0.0f}), std::invalid_argument);
    values.push_back(0.0f);
    EXPECT_NO_THROW(solver.apply(values, 0.0f, {0.0f}));

    // test if ODE works properly
    float err = 0.1f;

    values.clear();
    values.push_back(1.0f);

    for (int i = 0; i < 100; ++i)
    {
        solver.apply(values, 0.01, {0.0f});
    }
    EXPECT_NEAR(values.front(), 1.0f, err);

    values.clear();
    values.push_back(1.0f);

    for (int i = 0; i < 1000; ++i)
    {
        solver.apply(values, 0.001, {1.0f});
    }
    EXPECT_NEAR(values.front(), std::exp(1.0f), err);

    values.clear();
    values.push_back(1.0f);

    for (int i = 0; i < 1000; ++i)
    {
        solver.apply(values, 0.001, {2.0f});
    }
    EXPECT_NEAR(values.front(), std::exp(2.0f), err);

    // change equation
    SimpleEquation2 eq2{};
    solver.changeEquation(eq2);

    values.clear();
    values.push_back(1.0f);
    EXPECT_THROW(solver.apply(values, 0.001, {2.0f}), std::invalid_argument);

    values.clear();
    values.push_back(0.0f);
    values.push_back(1.0f);

    for (int i = 0; i < 1000; ++i)
    {
       solver.apply(values, 0.001, {2.0f});
    }
    EXPECT_NEAR(values.front(), 0.0f, err);
    EXPECT_NEAR(values.back(), std::exp(2.0f), err);
}


