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
 * @header      ID3v2-ExtendedHeader.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    ID3v2 extended header
 */

#include <ID3v2.h>
#include <ID3v2/ID3v2-PrivateTypes.h>

namespace ID3v2
{
    #ifdef __clang__
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wpadded"
    #endif
    
    class ExtendedHeader::IMPL
    {
        public:
            
            IMPL( void );
            ~IMPL( void );
            
            ID3v2ExtendedHeader header;
            std::size_t         headerSize;
    };
    
    #ifdef __clang__
    #pragma clang diagnostic pop
    #endif
    
    ExtendedHeader::ExtendedHeader( void ): impl( new IMPL )
    {}
    
    ExtendedHeader::~ExtendedHeader( void )
    {
        delete this->impl;
    }
    
    std::size_t ExtendedHeader::GetSize( void )
    {
        return this->impl->headerSize;
    }
    
    ExtendedHeader * ExtendedHeader::NewExtendedHeaderFromFileHandle( FILE * fh )
    {
        ExtendedHeader    * header;
        ID3v2ExtendedHeader exHeader;
        std::size_t         size;
        
        if( fh == NULL )
        {
            return NULL;
        }
        
        if( fread( &exHeader, 1, sizeof( ID3v2ExtendedHeader ), fh ) != sizeof( ID3v2ExtendedHeader ) )
        {
            return NULL;
        }
        
        {
            std::size_t s1;
            std::size_t s2;
            std::size_t s3;
            std::size_t s4;
            
            s1   = static_cast< std::size_t >( exHeader.size[ 0 ] );
            s2   = static_cast< std::size_t >( exHeader.size[ 1 ] );
            s3   = static_cast< std::size_t >( exHeader.size[ 2 ] );
            s4   = static_cast< std::size_t >( exHeader.size[ 3 ] );
            s1  &= 0x7F;
            s2  &= 0x7F;
            s3  &= 0x7F;
            s4  &= 0x7F;
            s1 <<= 21;
            s2 <<= 14;
            s3 <<= 7;
            
            size = s1 | s2 | s3 | s4;
        }
        
        if( fseek( fh, static_cast< long >( size ), SEEK_CUR ) != 0 )
        {
            return NULL;
        }
        
        header                   = new ExtendedHeader();
        header->impl->headerSize = size;
        
        memcpy( &( header->impl->header ), &exHeader, sizeof( ID3v2ExtendedHeader ) );
        
        return header;
    }
    
    ExtendedHeader::IMPL::IMPL( void )
    {
        this->headerSize = 0;
        
        memset( &( this->header ), 0, sizeof( ID3v2ExtendedHeader ) );
    }
    
    ExtendedHeader::IMPL::~IMPL( void )
    {}
}
