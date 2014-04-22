#pragma once

#define CREATE_FUNC(CLASS_NAME) \
	static std::shared_ptr<CLASS_NAME> Create() \
{ \
	std::shared_ptr<CLASS_NAME> pInstance(new CLASS_NAME()); \
	return pInstance; \
}