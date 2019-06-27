//
// Created by jprolejko on 27.06.19.
//

#ifndef GRAVITY_PHYSICS_RUNGEKUTTASOLVER_H
#define GRAVITY_PHYSICS_RUNGEKUTTASOLVER_H

#include <vector>


template<class T>
class EquationParameters {

public:
    EquationParameters() = default;
    EquationParameters(const std::vector<T> &parameters) : parameters_(parameters) {}
    EquationParameters(const T &parameter) {
        parameters_.push_back(parameter);
    }

    const std::vector<T>& get() const {
        return parameters_;
    }

private:
    std::vector<T> parameters_;

};

template<class T, class K>
class IEquation {

public:
    virtual std::vector<T> operator()(const std::vector<T> &values, 
                                      const EquationParameters<K> &parameters) = 0;
    
    size_t getSize() {
        return size_;
    }

protected:
    size_t size_;

};

template<class T, class K>
class RungeKuttaSolver {

public:
    RungeKuttaSolver() = delete;
    RungeKuttaSolver(const RungeKuttaSolver&) = delete;
    RungeKuttaSolver& operator=(const RungeKuttaSolver&) = delete;

    RungeKuttaSolver(IEquation<T, K> &equation) : equation_(equation) {       
        changeEquation(equation);
    }

    inline void changeEquation(IEquation<T, K> &equation) {
        equation_ = equation;
        k1_.resize(equation_.getSize());
        k2_.resize(equation_.getSize());
        k3_.resize(equation_.getSize());
        k4_.resize(equation_.getSize());
        helper_.resize(equation_.getSize());
    }

    inline void apply(std::vector<T> &values,
                      const float step,
                      const EquationParameters<K> &parameters) {
        if (values.size() != equation_.getSize())
        {
            throw std::invalid_argument("[RungeKuttaSolver] Vector with initial values for ODE"
                                        " solving has size incompatible with given equation.");
        }

        k1_ = equation_(values, parameters);

        for (size_t i = 0; i < k1_.size(); ++i)
        {
            k1_.at(i) = k1_.at(i) * step;
            helper_.at(i) = values.at(i) + k1_.at(i) / 2.0f;
        }

        k2_ = equation_(values, parameters);

        for (size_t i = 0; i < k2_.size(); ++i)
        {
            k2_.at(i) = k2_.at(i) * step;
            helper_.at(i) = values.at(i) + k2_.at(i) / 2.0f;
        }

        k3_ = equation_(values, parameters);

        for (size_t i = 0; i < k3_.size(); ++i)
        {
            k3_.at(i) = k3_.at(i) * step;
            helper_.at(i) = values.at(i) + k3_.at(i);
        }

        k4_ = equation_(values, parameters);

        for (auto &k : k4_)
        {
            k = k * step;
        }

        for (size_t i = 0; i < values.size(); ++i)
        {
            values.at(i) = values.at(i) +
                           (k1_.at(i) + 2.0f * k2_.at(i) + 2.0f * k3_.at(i) + k4_.at(i)) / 6.0f;
        }
    }

private:
    IEquation<T, K> &equation_;

    std::vector<T> k1_;
    std::vector<T> k2_;
    std::vector<T> k3_;
    std::vector<T> k4_;
    std::vector<T> helper_;
};


#endif // GRAVITY_PHYSICS_RUNGEKUTTASOLVER_H