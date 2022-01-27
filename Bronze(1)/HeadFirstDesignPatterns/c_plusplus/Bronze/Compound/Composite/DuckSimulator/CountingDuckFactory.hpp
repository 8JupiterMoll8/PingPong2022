#ifndef	_HEAD_FIRST_DESIGN_PATTERNS_COMPOUND_COMPOSITE_COUNTING_DUCK_FACTORY_HPP_
#define _HEAD_FIRST_DESIGN_PATTERNS_COMPOUND_COMPOSITE_COUNTING_DUCK_FACTORY_HPP_

#include "DuckSimulator.hpp"

namespace HeadFirstDesignPatterns {
namespace Compound {
namespace Composite {

class CountingDuckFactory : public AbstractDuckFactory {
 	public: virtual Quackable* createMallardDuck() {
		return new QuackCounter(new MallardDuck());
	}
  	public: virtual Quackable* createRedheadDuck() {
		return new QuackCounter(new RedheadDuck());
	}
  	public: virtual Quackable* createDuckCall() {
		return new QuackCounter(new DuckCall());
	}
  	public: virtual Quackable* createRubberDuck() {
		return new QuackCounter(new RubberDuck());
	}
};

} // namespace Composite
} // namespace Compound
} // namespace HeadFirstDesignPatterns

#endif

