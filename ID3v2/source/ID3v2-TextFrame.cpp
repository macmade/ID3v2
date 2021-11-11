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
 * @header      ID3v2-TextFrame.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    ID3v2 text frame
 */

#include <ID3v2.h>

namespace ID3v2
{
    #ifdef __clang__
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wpadded"
    #endif
    
    class TextFrame::IMPL
    {
        public:
            
            IMPL( void );
            
            std::string  str;
            const char * cStr;
            int          enc;
    };
    
    #ifdef __clang__
    #pragma clang diagnostic pop
    #endif
         
    TextFrame::TextFrame( void ): impl( new IMPL )
    {}
    
    TextFrame::~TextFrame( void )
    {
        delete this->impl;
    }
    
    void TextFrame::ProcessData( void )
    {
        const char * data;
        
        data = reinterpret_cast< const char * >( this->GetData() );
        
        if( data == NULL || this->GetSize() == 0 )
        {
            return;
        }
        
        this->impl->str  = std::string( data + 1, this->GetSize() - 1 );
        this->impl->cStr = data + 1;
        this->impl->enc  = data[ 0 ];
    }
    
    std::string TextFrame::GetStringValue( void ) const
    {
        return this->impl->str;
    }
    
    const char * TextFrame::GetCStringValue( void ) const
    {
        return this->impl->cStr;
    }
    
    int TextFrame::GetStringEncoding( void ) const
    {
        return this->impl->enc;
    }
    
    TextFrame::IMPL::IMPL( void ): cStr( NULL ), enc( 0 )
    {}
}

