#ifndef	_HEAD_FIRST_DESIGN_PATTERNS_STRATEGY_DUCK_HPP_
#define _HEAD_FIRST_DESIGN_PATTERNS_STRATEGY_DUCK_HPP_

#include "MiniDuckSimulator.hpp"

namespace HeadFirstDesignPatterns {
namespace Strategy {

class Duck {
	protected: FlyBehavior* m_flyBehavior;
	protected: QuackBehavior* m_quackBehavior;

	protected: Duck() : m_flyBehavior(0), m_quackBehavior(0) {
	}
	public:	virtual void setFlyBehavior(FlyBehavior* fb) {
		m_flyBehavior = fb;
	}
	public: virtual void setQuackBehavior(QuackBehavior* qb) {
		m_quackBehavior = qb;
	}
	public: virtual void performFly() {
		m_flyBehavior->fly();
	}
	public: virtual void performQuack() {
		m_quackBehavior->quack();
	}
	public: virtual void swim() {
		std::cout << "All ducks float, even decoys!" << std::endl;
	}
	public: virtual void display() = 0;
};

} // namespace Strategy
} // namespace HeadFirstDesignPatterns

#endif