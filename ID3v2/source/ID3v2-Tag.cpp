/*******************************************************************************
 * Copyright (c) 2014, Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * Distributed under the Boost Software License, Version 1.0.
 * 
 * Boost Software License - Version 1.0 - August 17th, 2003
 * 
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 * 
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer,
 * must be included in all copies of the Software, in whole or in part, and
 * all derivative works of the Software, unless such copies or derivative
 * works are solely in the form of machine-executable object code generated by
 * a source language processor.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 ******************************************************************************/
 
/* $Id$ */

/*!
 * @header      ID3v2-Tag.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    ID3v2 tag
 */

#include <ID3v2.h>
#include <ID3v2/ID3v2-PrivateTypes.h>

namespace ID3v2
{
    #ifdef __clang__
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wpadded"
    #endif
    
    class Tag::IMPL
    {
        public:
            
            IMPL( void );
            ~IMPL( void );
            
            void ParseFile( std::string path );
            
            bool                   valid;
            ID3v2Header            header;
            std::size_t            headerSize;
            std::vector< Frame * > frames;
    };
    
    #ifdef __clang__
    #pragma clang diagnostic pop
    #endif
    
    Tag::Tag( std::string path ): impl( new IMPL )
    {
        this->impl->ParseFile( path );
    }
    
    Tag::Tag( const Tag & tag ): impl( new IMPL )
    {
        this->impl->valid = tag.impl->valid;
    }
    
    Tag::~Tag( void )
    {
        if( this->impl != NULL )
        {
            delete this->impl;
        }
    }
    
    Tag & Tag::operator =( const Tag & tag )
    {
        this->impl->valid = tag.impl->valid;
        
        return *( this );
    }
    
    bool Tag::IsValid( void ) const
    {
        return this->impl->valid;
    }
    
    Version Tag::GetVersion( void ) const
    {
        if( this->IsValid() == false )
        {
            return Version( 0, 0, 0 );
        }
        
        return Version
        (
            2,
            static_cast< unsigned int >( this->impl->header.version[ 0 ] ),
            static_cast< unsigned int >( this->impl->header.version[ 1 ] )
        );
    }
    
    unsigned char Tag::GetFlags( void ) const
    {
        if( this->IsValid() == false )
        {
            return 0;
        }
        
        return static_cast< unsigned char >( this->impl->header.flags );
    }
    
    bool Tag::HasFlag( Flag flag ) const
    {
        if( this->IsValid() == false )
        {
            return false;
        }
        
        switch( flag )
        {
            case FlagUnsynchronisation:     return ( this->impl->header.flags & 0x80 ) ? true : false;
            case FlagExtendedHeader:        return ( this->impl->header.flags & 0x40 ) ? true : false;
            case FlagExperimentalIndicator: return ( this->impl->header.flags & 0x20 ) ? true : false;
        }
        
        return false;
    }
    
    std::size_t Tag::GetSize( void )
    {
        if( this->IsValid() == false )
        {
            return 0;
        }
        
        return this->impl->headerSize;
    }
    
    std::vector< Frame * > Tag::GetFrames( void ) const
    {
        if( this->IsValid() == false )
        {
            return std::vector< Frame * >();
        }
        
        return this->impl->frames;
    }
    
    Frame * Tag::GetFrameWithName( std::string name ) const
    {
        std::vector< Frame * >::iterator it;
        Frame                          * frame;
        
        if( this->IsValid() == false )
        {
            return NULL;
        }
        
        for( it = this->impl->frames.begin(); it != this->impl->frames.end(); ++it )
        {
            frame = *( it );
            
            if( frame != NULL && frame->GetName() == name )
            {
                return frame;
            }
        }
        
        return NULL;
    }
    
    Tag::IMPL::IMPL( void )
    {
        this->valid      = false;
        this->headerSize = 0;
        
        memset( &( this->header ), 0, sizeof( ID3v2Header ) );
    }
    
    Tag::IMPL::~IMPL( void )
    {
        std::vector< Frame * >::iterator it;
        
        for( it = this->frames.begin(); it != this->frames.end(); ++it )
        {
            if( *( it ) != NULL )
            {
                delete *( it );
            }
        }
    }
    
    void Tag::IMPL::ParseFile( std::string path )
    {
        FILE      * fh;
        std::size_t bytes;
        
        this->valid = false;
        
        fh = fopen( path.c_str(), "rb" );
        
        if( fh == NULL )
        {
            return;
        }
        
        if( fread( &( this->header ), 1, sizeof( ID3v2Header ), fh ) != sizeof( ID3v2Header ) )
        {
            goto end;
        }
        
        if( this->header.id[ 0 ] != 'I' || this->header.id[ 1 ] != 'D' || this->header.id[ 2 ] != '3' )
        {
            goto end;
        }
        
        {
            std::size_t s1;
            std::size_t s2;
            std::size_t s3;
            std::size_t s4;
            
            s1   = static_cast< std::size_t >( this->header.size[ 0 ] );
            s2   = static_cast< std::size_t >( this->header.size[ 1 ] );
            s3   = static_cast< std::size_t >( this->header.size[ 2 ] );
            s4   = static_cast< std::size_t >( this->header.size[ 3 ] );
            s1  &= 0x7F;
            s2  &= 0x7F;
            s3  &= 0x7F;
            s4  &= 0x7F;
            s1 <<= 21;
            s2 <<= 14;
            s3 <<= 7;
            
            this->headerSize = s1 | s2 | s3 | s4;
        }
        
        bytes = 0;
        
        while( bytes < this->headerSize )
        {
            {
                Frame * frame;
                
                frame = Frame::NewFrameFromFileHandle( fh );
                
                if( frame == NULL )
                {
                    goto end;
                }
                
                if( frame->GetSize() == 0 )
                {
                    break;
                }
                
                this->frames.push_back( frame );
                
                bytes += frame->GetSize() + sizeof( ID3v2Frame );
            }
        }
        
        this->valid = true;
            
        end:
        
        fclose( fh );
    }
}
