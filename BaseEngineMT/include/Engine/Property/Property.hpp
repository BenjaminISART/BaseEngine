#ifndef __PROPERTY__
#define __PROPERTY__

#include <string>

namespace Core
{
	class Property
	{
	private:

#pragma region private attributes
#pragma endregion

#pragma region private methods
#pragma endregion

	public:

		Property() : id{ 0 }, name{ "" } {} // CTOR
		Property(const char* path) : id{ 0 }, name{ "" } {};
		//// TODO : pas mettre default ici parce qu'il faut change les id etc ...
		//Property(Property const& c) = default; // CPY CTOR
		//Property(Property && c) = default; // MV CTOR
		~Property() = default; // DTOR

#pragma region public attributes
		unsigned int id;
		std::string name;
#pragma endregion

#pragma region public methods
#pragma endregion
	};
}

#endif // __PROPERTY__