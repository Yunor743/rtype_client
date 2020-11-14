#ifndef RTYPE_SYSTEM_INPUT_HANDLER_H_
#define RTYPE_SYSTEM_INPUT_HANDLER_H_

#include "Modules.hpp"
#include "System.hpp"

template <typename Fn>
System createInputHandler(Input key, Fn f);

#include "InputHandler.tpp"

#endif // RTYPE_SYSTEM_INPUT_HANDLER_H_
