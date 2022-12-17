#include "EngineFactory.hpp"
#include "Engine.cpp"

std::unique_ptr<Engine> EngineFactory::createEngine() {
    std::unique_ptr<Engine> e =std::make_unique<myEngine>( myEngine());
    return e;
    //return nullptr;  make_unique
}
