#pragma once

#include <cassert>

template <typename T>
class Service
{
public:
	static void SetService(T* p_service)
	{
		ms_service = p_service;
	};
	static T* GetService()
	{
		assert(ms_service != nullptr);
		return ms_service;
	};
private:
	static T* ms_service;
	Service() = delete;
};

template <typename T>
T* Service<T>::ms_service = nullptr;