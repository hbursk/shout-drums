#pragma once

#include "nod/nod.hpp"

#include <functional>

class AlwaysUpdatePolicy
{
public:
    template <typename T>
    bool operator()( const T&, const T& ) const
    {
        return true;
    }
};

template <typename T, typename UpdatePolicy = std::not_equal_to<T>>
class Property
{
public:
    Property() = default;
    Property( T value )
    : m_value( std::move( value ) )
    {
    }

    const T& get() const
    {
        return m_value;
    }
    T& get()
    {
        return m_value;
    }

    const T& operator()() const
    {
        return get();
    }
    T& operator()()
    {
        return get();
    }

    void set( const T& value )
    {
        if ( UpdatePolicy()( m_value, value ) )
        {
            m_value = value;
            changed( m_value );
        }
    }
    void operator()( const T& value )
    {
        set( value );
    }

    void set( T&& value )
    {
        if ( UpdatePolicy()( m_value, value ) )
        {
            m_value = std::forward<T>( value );
            changed( m_value );
        }
    }

    void operator()( T&& value )
    {
        set( std::forward<T>( value ) );
    }

    nod::unsafe_signal<void( const T& newValue )> changed;

    nod::connection onChanged( std::function<void( const T& )> callback )
    {
        return changed.connect( std::move( callback ) );
    }
    
    nod::connection onChangedAndNow( std::function<void( const T& )> callback )
    {
        callback( m_value );
        return changed.connect( std::move( callback ) );
    }

private:
    T m_value{};
};
