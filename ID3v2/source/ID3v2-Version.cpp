/*******************************************************************************
 * The MIT License (MIT)
 * 
 * Copyright (c) 2014 Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 ******************************************************************************/

/*!
 * @header      ID3v2-Tag.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    ID3v2 version
 */

#include <ID3v2.h>
#include <sstream>

namespace ID3v2
{
    class Version::IMPL
    {
        public:
            
            IMPL( void );
            
            unsigned int major;
            unsigned int minor;
            unsigned int revision;
    };
         
    Version::Version( unsigned int major, unsigned int minor, unsigned int revision ): impl( new IMPL )
    {
        this->impl->major    = major;
        this->impl->minor    = minor;
        this->impl->revision = revision;
    }
    
    Version::Version( const Version & version ): impl( new IMPL )
    {
        this->impl->major    = version.impl->major;
        this->impl->minor    = version.impl->minor;
        this->impl->revision = version.impl->revision;
    }
    
    Version::~Version( void )
    {
        delete this->impl;
    }
    
    Version & Version::operator =( const Version & version )
    {
        this->impl->major    = version.impl->major;
        this->impl->minor    = version.impl->minor;
        this->impl->revision = version.impl->revision;
        
        return *( this );
    }
    
    bool Version::operator ==( const Version & version ) const
    {
        return this->GetMajor() == version.GetMajor() && this->GetMinor() == version.GetMinor() && this->GetRevision() == version.GetRevision();
    }
    
    bool Version::operator !=( const Version & version ) const
    {
        return ( this->operator ==( version ) ) ? false : true;
    }
    
    bool Version::operator >=( const Version & version ) const
    {
        if( this->operator ==( version ) )
        {
            return true;
        }
        
        return this->operator >( version );
    }
    
    bool Version::operator <=( const Version & version ) const
    {
        if( this->operator ==( version ) )
        {
            return true;
        }
        
        return this->operator <( version );
    }
    
    bool Version::operator >( const Version & version ) const
    {
        if( this->GetMajor() > version.GetMajor() )
        {
            return true;
        }
        
        if( this->GetMinor() > version.GetMinor() )
        {
            return true;
        }
        
        if( this->GetRevision() > version.GetRevision() )
        {
            return true;
        }
        
        return false;
    }
    
    bool Version::operator <( const Version & version ) const
    {
        if( this->GetMajor() < version.GetMajor() )
        {
            return true;
        }
        
        if( this->GetMinor() < version.GetMinor() )
        {
            return true;
        }
        
        if( this->GetRevision() < version.GetRevision() )
        {
            return true;
        }
        
        return false;
    }
    
    std::string Version::GetStringValue( void ) const
    {
        std::stringstream ss;
        
        ss << this->impl->major;
        ss << ".";
        ss << this->impl->minor;
        ss << ".";
        ss << this->impl->revision;
        
        return ss.str();
    }
    
    unsigned int Version::GetMajor( void ) const
    {
        return this->impl->major;
    }
    
    unsigned int Version::GetMinor( void ) const
    {
        return this->impl->minor;
    }
    
    unsigned int Version::GetRevision( void ) const
    {
        return this->impl->revision;
    }
    
    Version::IMPL::IMPL( void )
    {
        this->major     = 0;
        this->minor     = 0;
        this->revision  = 0;
    }
}
