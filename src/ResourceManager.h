
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "Tank2007.h"

//------------------------------------------------------------------------------

template <typename T> class ResourceManager
{
	protected:

		std::list<T*> mList;

	public:

		T* create(const std::string& name)
		{
			T* t = new T();

			mList.push_back(t);

			return t;
		}

		void destroy(T* t)
		{
			mList.remove(t);

			delete t;
		}
};

//------------------------------------------------------------------------------
