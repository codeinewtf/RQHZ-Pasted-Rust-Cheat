#pragma once

template <typename TS>
class archivex final
{
private:
	TS& stream;
public:
	constexpr explicit archivex ( TS& stream ) : stream{ stream } {}

	template <typename T>
	constexpr const auto& operator<<( const T& item ) const
	{
		stream.write ( (const char*)(&item), sizeof ( item ) );
		return *this;
	}

	template <typename T>
	constexpr const auto& operator>>( T& item ) const
	{
		stream.read ( (char*)(&item), sizeof ( item ) );
		return *this;
	}
};