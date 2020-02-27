#pragma once

/*

Override std::stringstream and to give it better matching operators

You can write things like

std::string myString( NsStringBuilder::StringBuilder() << "my data " << 42 )

*/

#include <sstream>

namespace RPN {

    using namespace std;

    namespace NVR {
        template<typename T>  class basic_stringstream : public std::basic_stringstream<T>
        {
        public:
            basic_stringstream() {}

            operator const std::basic_string<T>() const { return std::basic_stringstream<T>::str(); }
            basic_stringstream<T>& operator<<   (bool _val) { std::basic_stringstream<T>::operator << (_val); return *this; }
            basic_stringstream<T>& operator<<   (char _val) { std::basic_stringstream<T>::operator << (_val); return *this; }
            basic_stringstream<T>& operator<<   (signed char _val) { std::basic_stringstream<T>::operator << (_val); return *this; }
            basic_stringstream<T>& operator<<   (unsigned char _val) { std::basic_stringstream<T>::operator << (_val); return *this; }
            basic_stringstream<T>& operator<<   (short _val) { std::basic_stringstream<T>::operator << (_val); return *this; }
            basic_stringstream<T>& operator<<   (unsigned short _val) { std::basic_stringstream<T>::operator << (_val); return *this; }
            basic_stringstream<T>& operator<<   (int _val) { std::basic_stringstream<T>::operator << (_val); return *this; }
            basic_stringstream<T>& operator<<   (unsigned int _val) { std::basic_stringstream<T>::operator << (_val); return *this; }
            basic_stringstream<T>& operator<<   (long _val) { std::basic_stringstream<T>::operator << (_val); return *this; }
            basic_stringstream<T>& operator<<   (unsigned long _val) { std::basic_stringstream<T>::operator << (_val); return *this; }
            basic_stringstream<T>& operator<<   (long long _val) { std::basic_stringstream<T>::operator << (_val); return *this; }
            basic_stringstream<T>& operator<<   (unsigned long long _val) { std::basic_stringstream<T>::operator << (_val); return *this; }
            basic_stringstream<T>& operator<<   (float _val) { std::basic_stringstream<T>::operator << (_val); return *this; }
            basic_stringstream<T>& operator<<   (double _val) { std::basic_stringstream<T>::operator << (_val); return *this; }
            basic_stringstream<T>& operator<<   (long double _val) { std::basic_stringstream<T>::operator << (_val); return *this; }
            basic_stringstream<T>& operator<<   (void* _val) { std::basic_stringstream<T>::operator << (_val); return *this; }
            basic_stringstream<T>& operator<<   (std::streambuf* _val) { std::basic_stringstream<T>::operator << (_val); return *this; }
            basic_stringstream<T>& operator<<   (std::ostream& (*_val)(std::ostream&)) { std::basic_stringstream<T>::operator << (_val); return *this; }
            basic_stringstream<T>& operator<<   (std::ios& (*_val)(std::ios&)) { std::basic_stringstream<T>::operator << (_val); return *this; }
            basic_stringstream<T>& operator<<   (std::ios_base& (*_val)(std::ios_base&)) { std::basic_stringstream<T>::operator << (_val); return *this; }
            basic_stringstream<T>& operator<<   (const T* _val) { return static_cast<basic_stringstream<T>&>(std::operator << (*this, _val)); }
            basic_stringstream<T>& operator<<   (const std::basic_string<T>& _val) { return static_cast<basic_stringstream<T>&>(std::operator << (*this, _val.c_str())); }


            basic_stringstream<T>& operator+=   (bool _val) { std::basic_stringstream<T>::operator << (_val); return *this; }
            basic_stringstream<T>& operator+=   (char _val) { std::basic_stringstream<T>::operator << (_val); return *this; }
            basic_stringstream<T>& operator+=   (signed char _val) { std::basic_stringstream<T>::operator << (_val); return *this; }
            basic_stringstream<T>& operator+=   (unsigned char _val) { std::basic_stringstream<T>::operator << (_val); return *this; }
            basic_stringstream<T>& operator+=   (short _val) { std::basic_stringstream<T>::operator << (_val); return *this; }
            basic_stringstream<T>& operator+=   (unsigned short _val) { std::basic_stringstream<T>::operator << (_val); return *this; }
            basic_stringstream<T>& operator+=   (int _val) { std::basic_stringstream<T>::operator << (_val); return *this; }
            basic_stringstream<T>& operator+=   (unsigned int _val) { std::basic_stringstream<T>::operator << (_val); return *this; }
            basic_stringstream<T>& operator+=   (long _val) { std::basic_stringstream<T>::operator << (_val); return *this; }
            basic_stringstream<T>& operator+=   (unsigned long _val) { std::basic_stringstream<T>::operator << (_val); return *this; }
            basic_stringstream<T>& operator+=   (long long _val) { std::basic_stringstream<T>::operator << (_val); return *this; }
            basic_stringstream<T>& operator+=   (unsigned long long _val) { std::basic_stringstream<T>::operator << (_val); return *this; }
            basic_stringstream<T>& operator+=   (float _val) { std::basic_stringstream<T>::operator << (_val); return *this; }
            basic_stringstream<T>& operator+=   (double _val) { std::basic_stringstream<T>::operator << (_val); return *this; }
            basic_stringstream<T>& operator+=   (long double _val) { std::basic_stringstream<T>::operator << (_val); return *this; }
            basic_stringstream<T>& operator+=   (void* _val) { std::basic_stringstream<T>::operator << (_val); return *this; }
            basic_stringstream<T>& operator+=   (std::streambuf* _val) { std::basic_stringstream<T>::operator << (_val); return *this; }
            basic_stringstream<T>& operator+=   (std::ostream& (*_val)(std::ostream&)) { std::basic_stringstream<T>::operator << (_val); return *this; }
            basic_stringstream<T>& operator+=   (std::ios& (*_val)(std::ios&)) { std::basic_stringstream<T>::operator << (_val); return *this; }
            basic_stringstream<T>& operator+=   (std::ios_base& (*_val)(std::ios_base&)) { std::basic_stringstream<T>::operator << (_val); return *this; }
            basic_stringstream<T>& operator+=   (const T* _val) { return static_cast<basic_stringstream<T>&>(std::operator << (*this, _val)); }
            basic_stringstream<T>& operator+=   (const std::basic_string<T>& _val) { return static_cast<basic_stringstream<T>&>(std::operator << (*this, _val.c_str())); }


        };

        typedef basic_stringstream<char>        StringBuilder;
        typedef basic_stringstream<wchar_t>     wStringBuilder;
    }

}

